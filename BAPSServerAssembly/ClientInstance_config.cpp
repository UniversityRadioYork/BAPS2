#include "stdafx.h"
#include "ClientInstance.h"
#include "Exceptions.h"
#include "BAPSController.h"
#include "ConfigDescriptorString.h"

using namespace BAPSServerAssembly;

#define BEGIN_CONFIG_BLOCK() ClientManager::getConfigLock();
#define END_CONFIG_BLOCK() ClientManager::releaseConfigLock();

/** 
 *  WORK NEEDED: validation functions, post-set functions for refreshing server
 *				 services with the new config values, security stuff
**/

/**
 *  This file contains the implementations of all the CONFIG functionality
**/
BEGIN_ACTION_BLOCKED1(sendOption,int optionid)
{
	/** The mode mask flips the bit to say this is an option not a count **/
	Command cmd = BAPSNET_CONFIG | BAPSNET_OPTION | BAPSNET_CONFIG_MODEMASK;
	/** 
		*  If the option is an indexed option the value field is set to the
		*  controlling option's id. (This value is arbitrary using this value
		*  is easiest
	**/
	if (CONFIG_ISINDEXED(optionid))
	{
		cmd |= BAPSNET_CONFIG_USEVALUEMASK;	
		cmd |= CONFIG_INDEXOPTION(optionid);
	}
	/** Send the optionid, optionDescription and optionType **/
	ClientManager::send(this, cmd, optionid, CONFIG_DESC(optionid), CONFIG_TYPE(optionid));
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED0(sendAllOptions)
{
	/** 
	 *  Number of options is always CONFIG_LASTOPTION as it
	 *  is at the end of the enum
	**/
	int count = CONFIG_LASTOPTION;
	/** Only list options which are editable by anyone **/
	int i = 0;
	if (!userInfo->isSuperuser())
	{
		count = 0;
		for ( i = 0 ; i < CONFIG_LASTOPTION ; i++ )
		{
			if (CONFIG_ACCESS_RIGHTS(i) == CA_ANY)
			{
				count++;
			}
		}
	}
	/** Send the number of options about to be sent **/
	Command cmd = (Command)(BAPSNET_CONFIG | BAPSNET_OPTION | count);
	ClientManager::send(this, cmd, (u32int)count);

	/** Loop through the options sending each one **/
	for ( i = 0 ; i < CONFIG_LASTOPTION ; i++ )
	{
		if (userInfo->isSuperuser() || CONFIG_ACCESS_RIGHTS(i) == CA_ANY)
		{
			sendOption(i);
		}
	}
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED1(sendAllOptionChoices, u32int optionid)
{
	/* Some configuration options have choices that change over time
	 * and some have defaults. Update them here */
	if (optionid == CONFIG_BAPSCONTROLLER2SERIAL)
	{
		ConfigStringChoices^ bapsController2Choices = gcnew ConfigStringChoices();
		
		array<System::String^>^ serials = gcnew array<System::String^>(1);
		if (CONFIG_GETINT(CONFIG_BAPSCONTROLLER2ENABLED) == CONFIG_YES_VALUE) {
			array<System::String^>^ serials = BAPSController::getBAPSController2Serials();
		}

		for (int i = 0 ; i < serials->Length ; i++)
		{
			bapsController2Choices->add(serials[i], serials[i], (i==0));
		}
		bapsController2Choices->add("none","none", (serials->Length==0));
		safe_cast<ConfigDescriptorStringChoice^>(ConfigManager::configDescriptions[CONFIG_BAPSCONTROLLER2SERIAL])->setChoices(bapsController2Choices);
		if (CONFIG_GETINT(CONFIG_BAPSCONTROLLER2DEVICECOUNT) < ((serials->Length==0)?1:serials->Length))
		{
			CONFIG_SET(CONFIG_BAPSCONTROLLER2DEVICECOUNT, (serials->Length==0)?1:serials->Length);
		}
	}

	/** 
	 *  Should be called for any CONFIG_TYPE_CHOICE option
	 *  returns all the possible choices the option can be.
	**/
	/** 
	 *  If the specified option:
	 *  a) is not a valid option
	 *  b) is not a CHOICE type
	 *  then say there are no choices
	**/
	Command cmd;
	if ((optionid >= CONFIG_LASTOPTION) || (CONFIG_TYPE(optionid) != CONFIG_TYPE_CHOICE))
	{
		cmd = BAPSNET_CONFIG | BAPSNET_OPTIONCHOICE;
		ClientManager::send(this, cmd, (u32int)optionid, (u32int)0);
		return;
	}

	/** 
	 *  We are certain now that the option is of CHOICE type, so cast
	 *  its descriptor to the choice superclass
	**/
	ConfigDescriptorChoice^ choice = CONFIG_CHOICE(optionid);
	/** Send the number of choices which will follow **/
	cmd = BAPSNET_CONFIG | BAPSNET_OPTIONCHOICE;
	int count = choice->getChoiceCount();
	ClientManager::send(this, cmd, (u32int)optionid, (u32int)count);
	/** Loop through all the choices sending each one's description and id **/
	int i = 0;
	for ( i = 0 ; i < count ; i++ )
	{
		/** The MODEMASK says that this is a choice not a choice count **/
		cmd = BAPSNET_CONFIG | BAPSNET_OPTIONCHOICE | BAPSNET_CONFIG_MODEMASK;
		/** send the optionid, choiceid and choiceDescription **/
		ClientManager::send(this, cmd, optionid, (u32int)i, choice->getChoiceDescription(i));
	}
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED3(sendOptionConfigSettings, int optionid, bool shouldBroadcast, ClientInstance^ c)
{
	/** Set up the basic command, MODEMASK says that this is a setting not a count **/
	Command cmd = BAPSNET_CONFIG | BAPSNET_CONFIGSETTING | BAPSNET_CONFIG_MODEMASK;
	if (CONFIG_ISINDEXED(optionid))
	{
		/**
			*  For indexed options we use the value field to say which
			*  index this setting is for
		**/
		cmd |= BAPSNET_CONFIG_USEVALUEMASK;
		/** Get the number of (indices) in this option **/
		int thisOptionCount = CONFIG_COUNTINDICES(optionid);
		if (thisOptionCount > 0x3F)
		{
			thisOptionCount = 1;
			/** WORK NEEDED: range checks on the controlling options **/
			LogManager::write(System::String::Concat("The option controlling the indices of the folling option is set to more than 0x3f:\n", CONFIG_KEY(optionid), CONFIG_DESC(optionid)), LOG_ERROR, LOG_CONFIG);
		}
		/** Loop through all the indices for this option **/
		int j = 0;
		for (j = 0 ; j < thisOptionCount ; j++)
		{
			/** Clear the value field **/
			cmd &= ~BAPSNET_CONFIG_VALUEMASK;
			/** Set the value field to the current index **/
			cmd |= j;
			/** 
				*  Send the correct type of data, the CONFIG_TYPE informs the
				*  client of what to expect
			**/
			switch (CONFIG_TYPE(optionid))
			{
			case CONFIG_TYPE_STR:
				if (shouldBroadcast)
				{
					ClientManager::broadcast(cmd, optionid, CONFIG_TYPE(optionid), CONFIG_GETSTRn(optionid,j));
				}
				else
				{
					ClientManager::send(c, cmd, optionid, CONFIG_TYPE(optionid), CONFIG_GETSTRn(optionid,j));
				}
				break;
			case CONFIG_TYPE_INT:
				if (shouldBroadcast)
				{
					ClientManager::broadcast(cmd, optionid, CONFIG_TYPE(optionid), CONFIG_GETINTn(optionid,j));
				}
				else
				{
					ClientManager::send(c, cmd, optionid, CONFIG_TYPE(optionid), CONFIG_GETINTn(optionid,j));
				}
				break;
			case CONFIG_TYPE_CHOICE:
				{
					ConfigDescriptorChoice^ choice = CONFIG_CHOICE(optionid);
					if (shouldBroadcast)
					{
						ClientManager::broadcast(cmd, optionid, CONFIG_TYPE_CHOICE, choice->getValueAsChoice(j));
					}
					else
					{
						ClientManager::send(c, cmd, optionid, CONFIG_TYPE_CHOICE, choice->getValueAsChoice(j));
					}
				}
				break;
			default:
				/** This case will cause a client and/or server to hang, it will be a programming error server side **/ 
				LogManager::write(System::String::Concat("The following option has an invalid type:\n", CONFIG_KEY(optionid), CONFIG_DESC(optionid)), LOG_ERROR, LOG_CONFIG);
				break;
			}
		}
	}
	else
	{
		/** Non indexed options come here **/
		switch (CONFIG_TYPE(optionid))
		{
		case CONFIG_TYPE_STR:
			if (shouldBroadcast)
			{
				ClientManager::broadcast(cmd, optionid, CONFIG_TYPE(optionid), CONFIG_GETSTR(optionid));
			}
			else
			{
				ClientManager::send(c, cmd, optionid, CONFIG_TYPE(optionid), CONFIG_GETSTR(optionid));
			}
			break;
		case CONFIG_TYPE_INT:
			if (shouldBroadcast)
			{
				ClientManager::broadcast(cmd, optionid, CONFIG_TYPE(optionid), CONFIG_GETINT(optionid));
			}
			else
			{
				ClientManager::send(c, cmd, optionid, CONFIG_TYPE(optionid), CONFIG_GETINT(optionid));
			}
			break;
		case CONFIG_TYPE_CHOICE:
			{
				ConfigDescriptorChoice^ choice = CONFIG_CHOICE(optionid);
				if (shouldBroadcast)
				{
					ClientManager::broadcast(cmd, optionid, CONFIG_TYPE_CHOICE, choice->getValueAsChoice());
				}
				else
				{
					ClientManager::send(c, cmd, optionid, CONFIG_TYPE_CHOICE, choice->getValueAsChoice());
				}

			}
			break;
		default:
			/** This case will cause a client and/or server to hang, it will be a programming error server side **/ 
			LogManager::write(System::String::Concat("The following option has an invalid type:\n", CONFIG_KEY(optionid), CONFIG_DESC(optionid)), LOG_ERROR, LOG_CONFIG);
			break;
		}
	}
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED0(sendAllConfigSettings)
{
	/** Finds all valid settings and sends them to the client **/
	/** 
	 *  The count is more complex as we do not know easily how many settings
	 *  there are due to indexed options, this short loop works this out
	**/
	int count = 0;
	int i = 0;
	for ( i = 0 ; i < CONFIG_LASTOPTION ; i++ )
	{
		/** For non indexed options this will be just +1 **/
		/** For indexed options this is +[value of controlling option] **/
		if (userInfo->isSuperuser() || CONFIG_ACCESS_RIGHTS(i) == CA_ANY)
		{
			count += CONFIG_COUNTINDICES(i);
		}
	}
	/** Send setting count to client **/
	Command cmd = (Command)(BAPSNET_CONFIG | BAPSNET_CONFIGSETTING);
	ClientManager::send(this, cmd, (u32int)count);
	/** Loop through all the options and indices sending each setting **/
	for ( i = 0 ; i < CONFIG_LASTOPTION ; i++ )
	{
		if (userInfo->isSuperuser() || CONFIG_ACCESS_RIGHTS(i) == CA_ANY)
		{
			sendOptionConfigSettings(i, false, this);
		}
	}
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED1(sendConfigOption, System::String^ optionName)
{
	int i = 0;
	/** Start with an invalid option **/
	int optionid = -1;
	for ( i = 0 ; i < CONFIG_LASTOPTION ; i++ )
	{
		/** If we find the corrent option return it otherwise we error **/
		if (System::String::Compare(CONFIG_KEY(i), optionName) == 0)
		{
			optionid=i;
			break;
		}
	}
	if (optionid != -1)
	{
		sendOption(optionid);
		/** Send setting count to client **/
		int count = CONFIG_COUNTINDICES(optionid);
		Command cmd = (Command)(BAPSNET_CONFIG | BAPSNET_CONFIGSETTING);
		ClientManager::send(this, cmd, (u32int)count);
		if (count != 0)
		{
			sendOptionConfigSettings(optionid, false, this);
		}
	}
	else
	{
		Command cmd = (Command)(BAPSNET_CONFIG | BAPSNET_CONFIGERROR | 1);
		ClientManager::send(this, cmd, "Option not found");
	}
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED3(setConfigValue,u32int optionid, int index, u32int type)
{
	/** This function encompasses all the work required to set a config value **/
	/**
	 *  The server is tolerant of disobedient clients who send valid commands
	 *  but with invalid data therein. E.g. client sets option 1 to an int when
	 *  it is a string value. Collect the rest of the command first.
	**/
	System::String^ strValue = nullptr;
	int intValue = 0;
	switch (type)
	{
	case CONFIG_TYPE_STR:
		strValue = connection->receiveS();
		break;
	case CONFIG_TYPE_INT:
	case CONFIG_TYPE_CHOICE:
		intValue = connection->receiveI();
		break;
	default:
		dead = true;
		/** Client has sent an invalid command, kill it and log the error **/
		LogManager::write(System::String::Concat("Received CONFIG|SETVALUE Command, with a deformed type field: ", type.ToString()), LOG_ERROR, LOG_COMMS);
		break;
	}
	/** All the data is received now, we assume success and await something failing **/
	ConfigResult result = CONFIG_RESULT_SUCCESS;
	/** Check that the option is valid **/
	if (optionid >= CONFIG_LASTOPTION)
	{
		result = CONFIG_RESULT_BADOPTION;
	}
	/**
	 *  If the option is claimed to be indexed and in reality is not
	 *  or vice versa, then an index error occurs.
	**/
	else if ((index != -1) ^ (CONFIG_ISINDEXED(optionid)))
	{
		result = CONFIG_RESULT_INDEXINGERROR;
	}
	/** If the index specified is not valid for this option then OOR error occurs**/
	else if ((index != -1) && (index >= CONFIG_GETINT(CONFIG_INDEXOPTION(optionid))))
	{
		result = CONFIG_RESULT_INDEXOUTOFRANGE;
	}
	/** Ready to start type based checks **/
	else
	{
		switch (type)
		{
		case CONFIG_TYPE_STR:
			{
				/** Type mismatch, option was not a string **/
				if (CONFIG_TYPE(optionid) != CONFIG_TYPE_STR)
				{
					result = CONFIG_RESULT_BADTYPE;
				}
				else
				{
					/** By this point we know that the index value is correct **/
					if (index != -1)
					{
						/** When setting the value validation checks are run **/
						if (!CONFIG_SETn(optionid, index, strValue) )
						{
							result = CONFIG_RESULT_VALIDATIONERROR;
						}
					}
					else
					{
						/** non indexed version of above **/
						if (!CONFIG_SET(optionid, strValue))
						{
							result = CONFIG_RESULT_VALIDATIONERROR;
						}
					}
				}
			}
			break;
		case CONFIG_TYPE_INT:
			{
				/** Type mismatch, option was not an int **/
				if (CONFIG_TYPE(optionid) != CONFIG_TYPE_INT)
				{
					result = CONFIG_RESULT_BADTYPE;
				}
				else
				{
					/** By this point we know that the index value is correct **/
					if (index != -1)
					{
						/** When setting the value validation checks are run **/
						if (!CONFIG_SETn(optionid, index, intValue))
						{
							result = CONFIG_RESULT_VALIDATIONERROR;
						}
					}
					else
					{
						/** non indexed version of above **/
						if (!CONFIG_SET(optionid, intValue))
						{
							result = CONFIG_RESULT_VALIDATIONERROR;
						}
					}
				}
			}
			break;
		case CONFIG_TYPE_CHOICE:
			{
				/** Type mismatch, option was not a choice **/
				if (CONFIG_TYPE(optionid) != CONFIG_TYPE_CHOICE)
				{
					result = CONFIG_RESULT_BADTYPE;
				}
				else
				{
					/** Get the option as a choice object **/
					ConfigDescriptorChoice^ cdc = CONFIG_CHOICE(optionid);
					/** By this point we know that the index value is correct **/
					if (index != -1)
					{
						/** When setting the value validation checks are run **/
						if (!cdc->setValueUsingChoice(index, intValue))
						{
							result = CONFIG_RESULT_VALIDATIONERROR;
						}
					}
					else
					{
						/** non indexed version of above **/
						if (!cdc->setValueUsingChoice(intValue))
						{
							result = CONFIG_RESULT_VALIDATIONERROR;
						}
					}
				}
			}
			break;
		}
	}
	/** Inform the client of the result **/
	Command cmd = BAPSNET_CONFIG | BAPSNET_CONFIGRESULT;
	ClientManager::send(this, cmd, optionid, result);
	if (CONFIG_ACCESS_RIGHTS(optionid) != CA_SU_ONLY)
	{
		sendOptionConfigSettings(optionid, true, nullptr);
	}
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED0(sendAllUsers)
{
	if (!userInfo->isSuperuser())
	{
		/** Inform the client of the result **/
		Command cmd = BAPSNET_CONFIG | BAPSNET_USERRESULT | UR_NOPERMISSION;
		ClientManager::send(this, cmd, const_cast<System::String^>(UserManager::UserResultText[UR_NOPERMISSION]));
		return;
	}
	System::Collections::ArrayList^ uList = UserManager::getUserList();

	Command cmd = BAPSNET_CONFIG | BAPSNET_USER;
	ClientManager::send(this, cmd, (u32int)uList->Count);
	int i = 0;
	for (i = 0; i < uList->Count ; i++)
	{
		Command cmd = BAPSNET_CONFIG | BAPSNET_USER | BAPSNET_CONFIG_MODEMASK;
		ClientManager::send(this, cmd, static_cast<System::String^>(uList[i]), GETPERM(static_cast<System::String^>(uList[i])));
	}
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED0(sendAllPermissionCodes)
{
	if (!userInfo->isSuperuser())
	{
		/** Inform the client of the result **/
		Command cmd = BAPSNET_CONFIG | BAPSNET_USERRESULT | UR_NOPERMISSION;
		ClientManager::send(this, cmd, const_cast<System::String^>(UserManager::UserResultText[UR_NOPERMISSION]));
		return;
	}

	Command cmd = BAPSNET_CONFIG | BAPSNET_PERMISSION;
	ClientManager::send(this, cmd, (u32int)UserManager::permissions->Length);
	int i = 0;
	for (i = 0; i < UserManager::permissions->Length ; i++)
	{
		Command cmd = BAPSNET_CONFIG | BAPSNET_PERMISSION | BAPSNET_CONFIG_MODEMASK;
		ClientManager::send(this, cmd, UserManager::permissions[i]->permission, UserManager::permissions[i]->description);
	}
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED1(sendUser, System::String^ username)
{
	if (!userInfo->isSuperuser() && System::String::Compare(userInfo->getUsername(),username)!=0)
	{
		/** Inform the client of the result **/
		Command cmd = BAPSNET_CONFIG | BAPSNET_USERRESULT | UR_NOPERMISSION;
		ClientManager::send(this, cmd, const_cast<System::String^>(UserManager::UserResultText[UR_NOPERMISSION]));
		return;
	}

	System::Collections::ArrayList^ uList = UserManager::getUserList();

	if (!uList->Contains(username))
	{
		/** Inform the client of the result **/
		Command cmd = BAPSNET_CONFIG | BAPSNET_USERRESULT | UR_USERNOTEXIST;
		ClientManager::send(this, cmd, const_cast<System::String^>(UserManager::UserResultText[UR_USERNOTEXIST]));
		return;
	}
	
	Command cmd = BAPSNET_CONFIG | BAPSNET_USER | BAPSNET_CONFIG_MODEMASK;
	ClientManager::send(this, cmd, username, GETPERM(username));
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED2(addUser, System::String^ username, System::String^ password)
{
	UserResult ur = userInfo->addUser(username, password);
	/** Inform the client of the result **/
	Command cmd = BAPSNET_CONFIG | BAPSNET_USERRESULT | ur;
	ClientManager::send(this, cmd, const_cast<System::String^>(UserManager::UserResultText[ur]));
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED1(removeUser, System::String^ username)
{
	UserResult ur = userInfo->removeUser(username);
	/** Inform the client of the result **/
	Command cmd = BAPSNET_CONFIG | BAPSNET_USERRESULT | ur;
	ClientManager::send(this, cmd, const_cast<System::String^>(UserManager::UserResultText[ur]));
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED2(setPassword, System::String^ username, System::String^ password)
{
	UserResult ur = userInfo->setPassword(username, password);
	/** Inform the client of the result **/
	Command cmd = BAPSNET_CONFIG | BAPSNET_USERRESULT | ur;
	ClientManager::send(this, cmd, const_cast<System::String^>(UserManager::UserResultText[ur]));
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED2(grantPermission, System::String^ username, UserPermission permission)
{
	UserResult ur = userInfo->grantPermission(username, permission);
	/** Inform the client of the result **/
	Command cmd = BAPSNET_CONFIG | BAPSNET_USERRESULT | ur;
	ClientManager::send(this, cmd, const_cast<System::String^>(UserManager::UserResultText[ur]));
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED2(revokePermission, System::String^ username, UserPermission permission)
{
	UserResult ur = userInfo->revokePermission(username, permission);
	/** Inform the client of the result **/
	Command cmd = BAPSNET_CONFIG | BAPSNET_USERRESULT | ur;
	ClientManager::send(this, cmd, const_cast<System::String^>(UserManager::UserResultText[ur]));
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED0(getIPRestrictions)
{
	System::Collections::ArrayList^ allowList = UserManager::getAllowedIPList();
	System::Collections::ArrayList^ denyList = UserManager::getDeniedIPList();

	Command cmd = BAPSNET_CONFIG | BAPSNET_IPRESTRICTION;
	ClientManager::send(this, cmd, (u32int)allowList->Count);
	int i;
	for (i = 0 ; i < allowList->Count ; i++)
	{
		IPRestriction^ ipRestriction = static_cast<IPRestriction^>(allowList[i]);
		cmd = BAPSNET_CONFIG | BAPSNET_IPRESTRICTION | BAPSNET_CONFIG_MODEMASK;
		ClientManager::send(this, cmd, ipRestriction->ipaddress, ipRestriction->mask);
	}
	cmd = BAPSNET_CONFIG | BAPSNET_IPRESTRICTION | BAPSNET_CONFIG_USEVALUEMASK;
	ClientManager::send(this, cmd, (u32int)denyList->Count);
	for (i = 0 ; i < denyList->Count ; i++)
	{
		IPRestriction^ ipRestriction = static_cast<IPRestriction^>(denyList[i]);
		cmd = BAPSNET_CONFIG | BAPSNET_IPRESTRICTION | BAPSNET_CONFIG_MODEMASK | BAPSNET_CONFIG_USEVALUEMASK;
		ClientManager::send(this, cmd, ipRestriction->ipaddress, ipRestriction->mask);
	}
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED3(alterIPRestriction, Command cmd, System::String^ ipaddress, u32int mask)
{
	ConfigError ce = CE_NOERROR;
	if (ISFLAGSET(cmd, BAPSNET_CONFIG_MODEMASK))
	{
		if (ISFLAGSET(cmd, BAPSNET_CONFIG_USEVALUEMASK))
		{
			ce = UserManager::removeIPMaskFromDenyList(ipaddress, mask);
		}
		else
		{
			ce = UserManager::removeIPMaskFromAllowList(ipaddress, mask);
		}
	}
	else
	{
		if (ISFLAGSET(cmd, BAPSNET_CONFIG_USEVALUEMASK))
		{
			ce = UserManager::addIPMaskToDenyList(ipaddress, mask);
		}
		else
		{
			ce = UserManager::addIPMaskToAllowList(ipaddress, mask);
		}
	}
	cmd = BAPSNET_CONFIG | BAPSNET_CONFIGERROR | ce;
	ClientManager::send(this, cmd, ConfigManager::configErrors[ce]);
}
END_ACTION_UNBLOCK();