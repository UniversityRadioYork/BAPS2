#include "stdafx.h"
#include "BAPSPresenterMain.h"
#include "ConfigCache.h"
#include "UtilityMacros.h"

using namespace BAPSPresenter;

/** All these functions firstly retrieve all the data the command needs and then (if possible)
	update the configDialog... exceptions to the rule exist... read on
**/

void BAPSPresenterMain::processChoice(int optionid, int choiceIndex, System::String^ choiceDescription)
{
	/** Cache this info **/
	ConfigCache::addOptionChoice(optionid, choiceIndex, choiceDescription);
	/** Ignore if the config dialog is closed **/
	ConfigDialog^ cd = configDialog;
	if (cd != nullptr)
	{
		try
		{
			cd->closeMutex->WaitOne();
			if (cd->Visible)
			{
				MethodInvokerObjObjStr^ mi = gcnew MethodInvokerObjObjStr(configDialog, &ConfigDialog::addChoice);
				array<System::Object^>^ dd = gcnew array<System::Object^>(3) {optionid, choiceIndex, choiceDescription};
				configDialog->Invoke(mi, dd);
			}
		}
		catch (System::Exception^ e)
		{
			System::String^ error = System::String::Concat("Failed to process choice:\n", e->Message, "\nStack Trace:\n", e->StackTrace);
			logError(error);
		}
		finally
		{
			cd->closeMutex->ReleaseMutex();
		}
	}
}

void BAPSPresenterMain::processChoiceCount(int optionid, int count)
{
	/** Ignore if the config dialog is closed **/
	ConfigDialog^ cd = configDialog;
	if (cd != nullptr)
	{
		try
		{
			cd->closeMutex->WaitOne();
			if (cd->Visible)
			{
				MethodInvokerObjObj^ mi = gcnew MethodInvokerObjObj(configDialog, &ConfigDialog::setChoiceCount);
				array<System::Object^>^ dd = gcnew array<System::Object^>(2) {optionid, count};
				configDialog->Invoke(mi,dd);
			}
		}
		catch (System::Exception^ e)
		{
			System::String^ error = System::String::Concat("Failed to process choice count:\n", e->Message, "\nStack Trace:\n", e->StackTrace);
			logError(error);
		}
		finally
		{
			cd->closeMutex->ReleaseMutex();
		}
	}
}

void BAPSPresenterMain::processOption(Command cmdReceived, int optionid, System::String^ description, int type)
{
	/** Cache this info **/
	ConfigCache::addOptionDescription(optionid, type, description, ((cmdReceived & BAPSNET_CONFIG_USEVALUEMASK) != 0));
	/** Pass onto the config dialog if available **/
	ConfigDialog^ cd = configDialog;
	if (cd != nullptr)
	{
		try
		{
			cd->closeMutex->WaitOne();
			if (cd->Visible)
			{
				/** Check for an indexed option **/
				if (ISFLAGSET(cmdReceived,BAPSNET_CONFIG_USEVALUEMASK))
				{
					/** Indexed option - does not update the form UI just data **/
					int indexid = (cmdReceived&BAPSNET_CONFIG_VALUEMASK);
					configDialog->addOption(gcnew ConfigOptionInfo(optionid, description, type, indexid));
				}
				else
				{
					/** Non indexed option - does not update the form ui just data **/
					configDialog->addOption(gcnew ConfigOptionInfo(optionid, description, type));
				}
				/** The configDialog form knows how many options it is expecting and
					will report true when it has them all, at this point it is able to
					draw itself
				**/
				if (configDialog->isReadyToShow())
				{
					/** Tell the form to draw its controls **/
					System::Windows::Forms::MethodInvoker^ mi = gcnew System::Windows::Forms::MethodInvoker(configDialog, &ConfigDialog::updateUI);
					configDialog->Invoke(mi);
				}
			}
		}
		catch (System::Exception^ e)
		{
			System::String^ error = System::String::Concat("Failed to process option:\n", e->Message, "\nStack Trace:\n", e->StackTrace);
			logError(error);
		}
		finally
		{
			cd->closeMutex->ReleaseMutex();
		}
	}
}

void BAPSPresenterMain::processOptionCount(int count)
{
	/** Let the config dialog know how many options to expect **/
	ConfigDialog^ cd = configDialog;
	if (cd != nullptr)
	{
		try
		{
			cd->closeMutex->WaitOne();
			if (cd->Visible)
			{
				configDialog->setNumberOfOptions(count);
			}
		}
		catch (System::Exception^ e)
		{
			System::String^ error = System::String::Concat("Failed to process option count:\n", e->Message, "\nStack Trace:\n", e->StackTrace);
			logError(error);
		}
		finally
		{
			cd->closeMutex->ReleaseMutex();
		}
	}
}

void BAPSPresenterMain::processConfigSetting(Command cmdReceived, int optionid, int type)
{
	int valueInt;
	System::String^ valueStr = nullptr;
	/** Determine what the final argument is going to be and retrieve it **/
	switch (type)
	{
	case CONFIG_TYPE_INT:
	case CONFIG_TYPE_CHOICE:
		valueInt = clientSocket->receiveI();
		break;
	case CONFIG_TYPE_STR:
		valueStr = clientSocket->receiveS();
		break;
	default:
		{
			sendQuit("Invalid type received in processConfigSetting", false);
		}
		break;
	}

	/** Cache this setting **/
	/** Use index=-1 to represent a non indexed setting **/
	int index = -1;
	if (ISFLAGSET(cmdReceived,BAPSNET_CONFIG_USEVALUEMASK))
	{
		index = (cmdReceived&BAPSNET_CONFIG_VALUEMASK);
	}
	switch (type)
	{
	case CONFIG_TYPE_INT:
	case CONFIG_TYPE_CHOICE:
		ConfigCache::addOptionValue(optionid, index, valueInt);
		break;
	case CONFIG_TYPE_STR:
		ConfigCache::addOptionValue(optionid, index, valueStr);
		break;
	}
	/** 
		In order to support fetching single config options for use in normal
		operation and also to retrieve all options (to change their values)
		We test if the configDialog handle is null, if it is we assume the
		config setting is intended for the cache.
	**/
	ConfigDialog^ cd = configDialog;
	if (cd != nullptr)
	{
		try
		{
			cd->closeMutex->WaitOne();
			if (cd->Visible)
			{
				/** If Config Dialog is visible at this point then it cannot close as we hold the closeMutex
				    this means we no longer have to use our copy of the objects handle (cd) **/
				/** THE ABOVE STATEMENT IS NOT TRUE! We may receive a value after the form has closed
				    but not yet know it is closed. We just catch the exception and continue! nasty
				**/
				/** If the value mask is used it means that the setting is for an indexed
					option and the specified index is in the value
				**/
				if (ISFLAGSET(cmdReceived,BAPSNET_CONFIG_USEVALUEMASK))
				{
					/** Extract the index from the command **/
					int index = (cmdReceived&BAPSNET_CONFIG_VALUEMASK);
					switch (type)
					{
					case CONFIG_TYPE_INT:
					case CONFIG_TYPE_CHOICE:
						{
							/** Box it up and send it off, choices can be treated as
								just ints because that is the underlying datatype
							**/
							MethodInvokerObjObjObj^ mi = gcnew MethodInvokerObjObjObj(configDialog, &ConfigDialog::setValue);
							array<System::Object^>^ dd = gcnew array<System::Object^>(3) {optionid, index, valueInt};
							configDialog->Invoke(mi, dd);
						}
						break;
					case CONFIG_TYPE_STR:
						{
							MethodInvokerObjObjStr^ mi = gcnew MethodInvokerObjObjStr(configDialog, &ConfigDialog::setValue);
							array<System::Object^>^ dd = gcnew array<System::Object^>(3) {optionid, index, valueStr};
							configDialog->Invoke(mi, dd);
						}
						break;
					}
				}
				else
				{
					/** Non indexed settings, just box them up and send them off **/
					switch (type)
					{
					case CONFIG_TYPE_INT:
					case CONFIG_TYPE_CHOICE:
						{
							MethodInvokerObjObj^ mi = gcnew MethodInvokerObjObj(configDialog, &ConfigDialog::setValue);
							array<System::Object^>^ dd = gcnew array<System::Object^>(2) {optionid, valueInt};
							configDialog->Invoke(mi, dd);
						}
						break;
					case CONFIG_TYPE_STR:
						{
							MethodInvokerObjStr^ mi = gcnew MethodInvokerObjStr(configDialog, &ConfigDialog::setValue);
							array<System::Object^>^ dd = gcnew array<System::Object^>(2) {optionid, valueStr};
							configDialog->Invoke(mi, dd);
						}
						break;
					}
				}
			}
		}
		catch (System::Exception^ e)
		{
			System::String^ error = System::String::Concat("Failed to process config setting: ",optionid.ToString(), ":\n", e->Message, "\nStack Trace:\n", e->StackTrace);
			logError(error);
		}
		finally
		{
			cd->closeMutex->ReleaseMutex();
		}
	}
}

void BAPSPresenterMain::processConfigResult(Command cmdReceived, int optionid, int result)
{
	/** We receive a result for every config setting we try to update **/
	/** Only report these if the form is still open, it is a serious error, if
	    we receive one of these when the form is closing **/
	if (configDialog != nullptr)
	{
		try
		{
			/** Check for an indexed option and deal with appropriately **/
			if (ISFLAGSET(cmdReceived,BAPSNET_CONFIG_USEVALUEMASK))
			{
				/** Indexed results **/
				int index = cmdReceived & BAPSNET_CONFIG_VALUEMASK;
				MethodInvokerObjObj^ mi = gcnew MethodInvokerObjObj(configDialog, &ConfigDialog::setResult);
				array<System::Object^>^ dd = gcnew array<System::Object^>(2) {optionid, result};
				configDialog->Invoke(mi, dd);
			}
			else
			{
				/** Non indexed results **/
				MethodInvokerObjObj^ mi = gcnew MethodInvokerObjObj(configDialog, &ConfigDialog::setResult);
				array<System::Object^>^ dd = gcnew array<System::Object^>(2) {optionid, result};
				configDialog->Invoke(mi, dd);
			}
		}
		catch (System::Exception^ e)
		{
			System::String^ error = System::String::Concat("Failed to process config result:\n", e->Message, "\nStack Trace:\n", e->StackTrace);
			logError(error);
		}
	}
}

void BAPSPresenterMain::processConfigError(int errorCode, System::String^ description)
{
	if (securityDialog != nullptr)
	{
		// send to security dialog
		MethodInvokerObjStr^ mi = gcnew MethodInvokerObjStr(securityDialog, &SecurityDialog::receiveConfigError);
		array<System::Object^>^ dd = gcnew array<System::Object^>(2) {errorCode, description};
		securityDialog->Invoke(mi, dd);
	}
	else if (configDialog != nullptr)
	{
		// send to config dialog
	}
}

void BAPSPresenterMain::processUserInfo(System::String^ username, int permissions)
{
	if (securityDialog != nullptr)
	{
		MethodInvokerStrObj^ mi = gcnew MethodInvokerStrObj(securityDialog, &SecurityDialog::receiveUserInfo);
		array<System::Object^>^ dd = gcnew array<System::Object^>(2) {username, permissions};
		securityDialog->Invoke(mi, dd);
	}
}
void BAPSPresenterMain::processUserCount(int userCount)
{
	if (securityDialog != nullptr)
	{
		MethodInvokerObj^ mi = gcnew MethodInvokerObj(securityDialog, &SecurityDialog::receiveUserCount);
		array<System::Object^>^ dd = gcnew array<System::Object^>(1) {userCount};
		securityDialog->Invoke(mi, dd);
	}
}
void BAPSPresenterMain::processUserResult(int resultCode, System::String^ description)
{
	if (securityDialog != nullptr)
	{
		MethodInvokerObjStr^ mi = gcnew MethodInvokerObjStr(securityDialog, &SecurityDialog::receiveUserResult);
		array<System::Object^>^ dd = gcnew array<System::Object^>(2) {resultCode, description};
		securityDialog->Invoke(mi, dd);
	}
}
void BAPSPresenterMain::processPermissionInfo(int permissionCode, System::String^ description)
{
	if (securityDialog != nullptr)
	{
		MethodInvokerObjStr^ mi = gcnew MethodInvokerObjStr(securityDialog, &SecurityDialog::receivePermissionInfo);
		array<System::Object^>^ dd = gcnew array<System::Object^>(2) {permissionCode, description};
		securityDialog->Invoke(mi, dd);
	}
}
void BAPSPresenterMain::processPermissionCount(int permissionCount)
{
	if (securityDialog != nullptr)
	{
		MethodInvokerObj^ mi = gcnew MethodInvokerObj(securityDialog, &SecurityDialog::receivePermissionCount);
		array<System::Object^>^ dd = gcnew array<System::Object^>(1) {permissionCount};
		securityDialog->Invoke(mi, dd);
	}
}
void BAPSPresenterMain::processIPRestrictionCount(Command cmd, int count)
{
	if (securityDialog != nullptr)
	{
		if (ISFLAGSET(cmd, BAPSNET_CONFIG_USEVALUEMASK))
		{
			MethodInvokerObj^ mi = gcnew MethodInvokerObj(securityDialog, &SecurityDialog::receiveIPDenyCount);
			array<System::Object^>^ dd = gcnew array<System::Object^>(1) {count};
			securityDialog->Invoke(mi, dd);
		}
		else
		{
			MethodInvokerObj^ mi = gcnew MethodInvokerObj(securityDialog, &SecurityDialog::receiveIPAllowCount);
			array<System::Object^>^ dd = gcnew array<System::Object^>(1) {count};
			securityDialog->Invoke(mi, dd);
		}
	}
}
void BAPSPresenterMain::processIPRestriction(Command cmd, System::String^ ipaddress, int mask)
{
	if (securityDialog != nullptr)
	{
		if (ISFLAGSET(cmd, BAPSNET_CONFIG_USEVALUEMASK))
		{
			MethodInvokerStrObj^ mi = gcnew MethodInvokerStrObj(securityDialog, &SecurityDialog::receiveIPDeny);
			array<System::Object^>^ dd = gcnew array<System::Object^>(2) {ipaddress, mask};
			securityDialog->Invoke(mi, dd);
		}
		else
		{
			MethodInvokerStrObj^ mi = gcnew MethodInvokerStrObj(securityDialog, &SecurityDialog::receiveIPAllow);
			array<System::Object^>^ dd = gcnew array<System::Object^>(2) {ipaddress, mask};
			securityDialog->Invoke(mi, dd);
		}
	}
}