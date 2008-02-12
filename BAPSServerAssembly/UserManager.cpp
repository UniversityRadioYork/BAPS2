#include "stdafx.h"
#include "UserManager.h"

using namespace BAPSServerAssembly;

UserManager::UserManager()
{
	username = nullptr;
	address = nullptr;
	seed = nullptr;
}
UserManager::~UserManager()
{
	username = nullptr;
	address = nullptr;
	seed = nullptr;
}

void UserManager::initUserManager()
{
	/** Client connection limit **/
	clientLimit = CONFIG_GETINT(CONFIG_CLIENTCONNLIMIT);
	if (countUsersInList() == 0)
	{
		System::String^ user = "admin";
		addUserToList(user);
		SETPASS(user, md5sum("1234"));
		SETPERM(user,UP_SUPERUSER);
	}
}

void UserManager::closeUserManager()
{
	// Nothing to close
}

System::String^ UserManager::getSeed(bool recreate)
{
	if (recreate || seed == nullptr)
	{
		seed = getRandomString();
	}
	return seed;
}
System::String^ UserManager::getSeed()
{
	return getSeed(false);
}
LoginResult UserManager::login(System::String^ _username, System::String^ password, System::Net::IPAddress^ _address)
{
	/** Password is md5sum(concat('seed',md5sum(password)))
			This enables the password to be safely transmitted accross an unsecure network
		Username is simply the username
	**/
	if (_username == nullptr || _username->Length == 0 ||
		password == nullptr || password->Length == 0)
	{
		LogManager::write("UserManager::login -- Username or Password has zero length.", LOG_WARNING, LOG_SECURITY);
		return LR_BADARGS;
	}
	else if (seed == nullptr || seed->Length == 0)
	{
		LogManager::write("UserManager::login -- length of seed is 0. Program error.", LOG_ERROR, LOG_OBJECTS);
		return LR_SYSTEMERROR;
	}
	System::String^ dbPassword = GETPASS(_username);
	if (dbPassword == nullptr || dbPassword->Length == 0)
	{
		LogManager::write(System::String::Concat("UserManager::login -- User does not exist: ", _username), LOG_WARNING, LOG_SECURITY);
		return LR_USERNOTEXIST;
	}
	/** Generate the encrypted password for the designated user **/
	System::String^ currentSecurePassword = md5sum(System::String::Concat(seed, dbPassword));
	
	if (System::String::Compare(password,currentSecurePassword) == 0)
	{
		username = _username;
		if (!isSuperuser() && isLockedOut())
		{
			LogManager::write(System::String::Concat("UserManager::login -- Login denied, user is locked out: ", _username), LOG_INFO, LOG_SECURITY);
			return LR_LOCKEDOUT;
		}
		else
		{
			LoginResult result = LR_SUCCESS;
			if (!isSuperuser())
			{
				result = checkRestrictions(_address);
			}
			if (result == LR_SUCCESS)
			{
				LogManager::write(System::String::Concat("UserManager::login -- ", _username, " has logged in."), LOG_INFO, LOG_SECURITY);	
			}
			else
			{
				username = nullptr;
			}
			return result;
		}
	}
	else
	{
		LogManager::write(System::String::Concat("UserManager::login -- Bad password for user: ", _username), LOG_WARNING, LOG_SECURITY);
		return LR_WRONGPASSWORD;
	}
}
LoginResult UserManager::checkRestrictions(System::Net::IPAddress^ _address)
{
	/** Convert the address to an unsigned integer (4 bytes) **/
	unsigned int remoteAddress = System::BitConverter::ToInt32(_address->GetAddressBytes(), 0);
	/** 
		We have an allow and a deny list in the registry.
		They are stored as binary values as follows:
		4-byte address, 1-byte mask value (ie representing 10.0.0.0/24)
	**/
	array<System::Byte>^ allowList = ConfigManager::getConfigValueBytes("IPAllowList", nullptr);
	array<System::Byte>^ denyList = ConfigManager::getConfigValueBytes("IPDenyList", nullptr);	

	if (isInIPMaskArray(remoteAddress, allowList, true))
	{
		if (isInIPMaskArray(remoteAddress, denyList, false))
		{
			LogManager::write(System::String::Concat("UserManager::checkRestrictions -- Client IP denied: ", _address->ToString()), LOG_WARNING, LOG_SECURITY);
			return LR_IPDENIED;
		}
		else
		{
			address = _address;
			return LR_SUCCESS;
		}
	}
	else
	{
		LogManager::write(System::String::Concat("UserManager::checkRestrictions -- Client IP not allowed: ", _address->ToString()), LOG_WARNING, LOG_SECURITY);
		return LR_IPNOTALLOWED;
	}
}

System::Collections::ArrayList^ UserManager::getAllowedIPList()
{
	return getIPMaskList(ConfigManager::getConfigValueBytes("IPAllowList", gcnew array<System::Byte>(0)));
}
System::Collections::ArrayList^ UserManager::getDeniedIPList()
{
	return getIPMaskList(ConfigManager::getConfigValueBytes("IPDenyList", gcnew array<System::Byte>(0)));
}
System::Collections::ArrayList^ UserManager::getIPMaskList(array<System::Byte>^ bytes)
{
	System::Collections::ArrayList^ list = gcnew System::Collections::ArrayList();
	if (bytes == nullptr || bytes->Length <5)
	{
		return list;
	}
	int count = (int)System::Math::Round(bytes->Length / 5, 0);
	int i = 0;

	for ( i = 0 ; i < count ; i++ )
	{
		array<System::Object^>^ addrbytes = gcnew array<System::Object^>(4);
		addrbytes[0] = bytes[(i*5)];
		addrbytes[1] = bytes[(i*5)+1];
		addrbytes[2] = bytes[(i*5)+2];
		addrbytes[3] = bytes[(i*5)+3];
		list->Add(gcnew IPRestriction(System::String::Format("{0}.{1}.{2}.{3}",addrbytes), bytes[(i*5)+4]));
	}
	return list;
}

ConfigError UserManager::addIPMaskToAllowList(System::String^ ipaddress, int mask)
{
	return addIPMaskToList("IPAllowList", ipaddress, mask);
}
ConfigError UserManager::addIPMaskToDenyList(System::String^ ipaddress, int mask)
{
	return addIPMaskToList("IPDenyList", ipaddress, mask);
}
ConfigError UserManager::removeIPMaskFromAllowList(System::String^ ipaddress, int mask)
{
	return removeIPMaskFromList("IPAllowList", ipaddress, mask);
}
ConfigError UserManager::removeIPMaskFromDenyList(System::String^ ipaddress, int mask)
{
	return removeIPMaskFromList("IPDenyList", ipaddress, mask);
}

ConfigError UserManager::addIPMaskToList(System::String^ listName, System::String^ ipaddress, int mask)
{
	array<System::Byte>^ listBytes = ConfigManager::getConfigValueBytes(listName, gcnew array<System::Byte>(0));
	array<System::Byte>^ ipBytes;
	System::String^ delim = ".";
	ipaddress = ipaddress->TrimEnd(delim->ToCharArray());
	try
	{
		ipBytes = convertIPStringToBytes(ipaddress);
	}
	catch (System::Exception^)
	{
		return CE_BADADDRESSFORMAT;
	}
	if (mask > 32)
	{
		return CE_BADMASK;
	}
	
	/** check it is not already in the list **/
	int i = 0;
	System::Collections::ArrayList^ list = getIPMaskList(listBytes);
	for ( i = 0 ; i < list->Count; i++)
	{
		IPRestriction^ ipRestriction = static_cast<IPRestriction^>(list[i]);
		if (System::String::Compare(ipaddress, ipRestriction->ipaddress) == 0 &&
			mask == ipRestriction->mask)
		{
			return CE_RESTRICTIONEXISTS;
		}
	}
	int newLength = listBytes->Length;
	if (newLength%5 != 0)
	{
		newLength -= newLength%5;
	}
	newLength += 5;
	array<System::Byte>^ newArray = gcnew array<System::Byte>(newLength);
	listBytes->CopyTo(newArray, 0);
	ipBytes->CopyTo(newArray, newLength-5);
	newArray[newLength-1] = mask;
	ConfigManager::setConfigValue(listName, newArray);
	return CE_NOERROR;
}

ConfigError UserManager::removeIPMaskFromList(System::String^ listName, System::String^ ipaddress, int mask)
{
	array<System::Byte>^ listBytes = ConfigManager::getConfigValueBytes(listName, gcnew array<System::Byte>(0));
	array<System::Byte>^ ipBytes;
	System::String^ delim = ".";
	ipaddress = ipaddress->TrimEnd(delim->ToCharArray());
	try
	{
		ipBytes = convertIPStringToBytes(ipaddress);
	}
	catch (System::Exception^)
	{
		return CE_BADADDRESSFORMAT;
	}
	if (mask > 32)
	{
		return CE_BADMASK;
	}
	
	/** check it is in the list **/
	int i = 0;
	int position = -1;
	System::Collections::ArrayList^ list = getIPMaskList(listBytes);
	for ( i = 0 ; i < list->Count; i++)
	{
		IPRestriction^ ipRestriction = static_cast<IPRestriction^>(list[i]);
		if (System::String::Compare(ipaddress, ipRestriction->ipaddress) == 0 &&
			mask == ipRestriction->mask)
		{
			position = i;
		}
	}
	if (position == -1)
	{
		return CE_RESTRICTIONNOTEXIST;
	}
	int newLength = listBytes->Length;
	if (newLength%5 != 0)
	{
		newLength -= newLength%5;
	}
	newLength -= 5;
	array<System::Byte>^ newArray = gcnew array<System::Byte>(newLength);

	System::Array::Copy(listBytes, 0, newArray, 0, position*5);
	System::Array::Copy(listBytes, (position+1)*5, newArray, position*5, listBytes->Length-((position+1)*5));

	ConfigManager::setConfigValue(listName, newArray);
	return CE_NOERROR;
}

array<System::Byte>^ UserManager::convertIPStringToBytes(System::String^ ipaddress)
{
	array<System::Byte>^ bytes = gcnew array<System::Byte>(4);
	int startIndex = 0;
	int i =0;
	/** This will raise an exception if the address is invalid caller is responsible for catching this **/
	for (i = 0 ; i < 4 ; i++)
	{
		int endIndex = ipaddress->IndexOf(".", startIndex);
		if (endIndex == -1)
		{
			endIndex = ipaddress->Length;
		}
		bytes[i] = System::Convert::ToByte(ipaddress->Substring(startIndex, endIndex-startIndex));
		startIndex = endIndex+1;
	}
	return bytes;
}

bool UserManager::isInIPMaskArray(unsigned int _address, array<System::Byte>^ list, bool defaultResult)
{
	if (list == nullptr || list->Length < 5)
	{
		return defaultResult;
	}
	bool inList = false;
	int count = (int)System::Math::Round(list->Length / 5, 0);
	int i = 0;

	for ( i = 0 ; i < count && !inList ; i++ )
	{
		unsigned int mask = -1;
		if (list[(i*5)+4] == 0)
		{
			mask = 0;
		}
		else
		{
			mask = mask >> (32 - list[(i*5)+4]);
		}
		unsigned int ruleip = System::BitConverter::ToInt32(list,i*5);
		ruleip &= mask;
		unsigned int testip = _address & mask;
		inList = (ruleip == testip);
	}
	return inList;
}
UserResult UserManager::addUser(System::String^ _username, System::String^ password)
{
	/** WORK NEEDED: validate usernames much more rigorously or we will fall over **/
	if (!isSuperuser())
	{
		return UR_NOPERMISSION;
	}
	if (_username->Length == 0)
	{
		return UR_USERNAMEERROR;
	}
	if (password == nullptr || password->Length == 0)
	{
		return UR_PASSWORDERROR;
	}
	if (addUserToList(_username))
	{
		SETPASS(_username, md5sum(password));
		SETPERM(_username, UP_NONE);
		return UR_SUCCESS;
	}
	else
	{
		return UR_USEREXISTS;
	}
}
UserResult UserManager::removeUser(System::String^ _username)
{
	if (!isSuperuser())
	{
		return UR_NOPERMISSION;
	}
	if (System::String::Compare(_username, "admin") == 0)
	{
		return UR_NOPERMISSION;
	}
	if (removeUserFromList(_username))
	{
		ConfigManager::removeValue(PASSKEY(_username));
		ConfigManager::removeValue(PERMKEY(_username));
		return UR_SUCCESS;
	}
	else
	{
		return UR_USERNOTEXIST;
	}
}
UserResult UserManager::setPassword(System::String^ _username, System::String^ password)
{
	if ((System::String::Compare(_username, username) != 0) && !isSuperuser())
	{
		return UR_NOPERMISSION;
	}
	if (password == nullptr || password->Length == 0)
	{
		return UR_PASSWORDERROR;
	}
	if (_username != nullptr && userExists(_username))
	{
		SETPASS(_username, md5sum(password));
		return UR_SUCCESS;
	}
	else
	{
		return UR_USERNOTEXIST;
	}
}
UserResult UserManager::grantPermission(System::String^ _username, UserPermission permission)
{
	if (!isSuperuser())
	{
		return UR_NOPERMISSION;
	}
	if (!isPermissionValid(permission))
	{
		return UR_INVALIDPERMISSION;
	}
	if (userExists(_username))
	{
		SETPERM(_username,GETPERM(_username) | permission);
		return UR_SUCCESS;
	}
	else
	{
		return UR_USERNOTEXIST;
	}
}
UserResult UserManager::revokePermission(System::String^ _username, UserPermission permission)
{
	if (!isSuperuser())
	{
		return UR_NOPERMISSION;
	}
	if (!isPermissionValid(permission))
	{
		return UR_INVALIDPERMISSION;
	}
	if (System::String::Compare(_username, "admin") == 0 && permission == UP_SUPERUSER)
	{
		return UR_NOPERMISSION;
	}
	if (userExists(_username))
	{
		SETPERM(_username,GETPERM(_username) & ~permission);
		return UR_SUCCESS;
	}
	else
	{
		return UR_USERNOTEXIST;
	}
}

bool UserManager::userExists(System::String^ _username)
{
	return getUserList()->Contains(_username);
}
bool UserManager::addUserToList(System::String^ _username)
{
	System::Collections::ArrayList^ list = getUserList();
	if (list->Contains(_username))
	{
		return false;
	}
	list->Add(_username);
	list->Sort();
	setUserList(list);
	return true;
}
bool UserManager::removeUserFromList(System::String^ _username)
{
	System::Collections::ArrayList^ list = getUserList();
	if (!list->Contains(_username))
	{
		return false;
	}
	list->Remove(_username);
	setUserList(list);
	return true;
}
int UserManager::countUsersInList()
{
	System::Collections::ArrayList^ list = getUserList();
	return list->Count;
}
System::Collections::ArrayList^ UserManager::getUserList()
{
	System::Collections::ArrayList^ userList = gcnew System::Collections::ArrayList();
	int startIndex = 0;
	int stringLength = 0;
	int index = 0;
	array<System::Byte>^ registryList = ConfigManager::getConfigValueBytes("UserList", nullptr);
	while (registryList != nullptr && index != -1 && startIndex < registryList->Length)
	{
		index = System::Array::IndexOf(registryList, (System::Byte)0, startIndex);
		if (index == -1)
		{
			stringLength = registryList->Length - startIndex;
		}
		else
		{
			stringLength = index - startIndex;
		}
		if (stringLength > 0)
		{
			System::String^ user = System::Text::Encoding::ASCII->GetString(registryList, startIndex, stringLength);
			userList->Add(user);
		}
		startIndex = index+1;
	}
	return userList;
}
void UserManager::setUserList(System::Collections::ArrayList^ list)
{
	int totalLength = 0;
	int i = 0;
	for ( i = 0 ; i < list->Count ; i++ )
	{
		totalLength += static_cast<System::String^>(list[i])->Length + 1;
	}
	array<System::Byte>^ registryArray = gcnew array<System::Byte>(totalLength);
	int currentPosition = 0;
	for ( i = 0 ; i < list->Count ; i++ )
	{
		array<System::Byte>^ _username =System::Text::Encoding::ASCII->GetBytes(static_cast<System::String^>(list[i])); 
		_username->CopyTo(registryArray, currentPosition);
		currentPosition += _username->Length +1;
	}
	ConfigManager::setConfigValue("UserList", registryArray);
}

bool UserManager::isPermissionValid(UserPermission up)
{
	int i = 0;
	for (i = 0 ; i < permissions->Length ; i++)
	{
		if (permissions[i]->permission == up)
		{
			return true;
		}
	}
	return false;
}