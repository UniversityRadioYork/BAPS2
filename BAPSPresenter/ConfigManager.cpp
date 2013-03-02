#include "stdafx.h"
#include "ConfigManager.h"

/**
 *  This class provides global configuration variables
 *  and their accessors
**/

/**
	WORK NEEDED: Each accessor needs checking to see what exception it should
				 raise and how it should react to exceptions being thrown
**/

void ConfigManager::initConfigManager()
{
	Microsoft::Win32::RegistryKey ^localMachine;
	try
	{
		/** Open HKEY_LOCAL_MACHINE **/
		localMachine = Microsoft::Win32::Registry::CurrentUser;
		/** Software **/
		software = localMachine->OpenSubKey("Software", true);
		if (software == nullptr)
		{
			software = localMachine->CreateSubKey("Software");
			if (software == nullptr)
			{
				throw gcnew System::Exception("Create of Software key failed");
			}
		}
		/** URY **/
		ury = software->OpenSubKey("URY", true);
		if (ury == nullptr)
		{
			ury = software->CreateSubKey("URY");
			if (ury == nullptr)
			{
				throw gcnew System::Exception("Create of URY key failed");
			}
		}
		/** BAPS **/
		bapsClient = ury->OpenSubKey("BAPSClient", true);
		if (bapsClient == nullptr)
		{
			bapsClient = ury->CreateSubKey("BAPSClient");
			if (bapsClient == nullptr)
			{
				throw gcnew System::Exception("Create of BAPSClient key failed");
			}
		}
	}
	catch (System::Exception^ )
	{
		// WORK NEEDED: error opening config manager
	}
}

void ConfigManager::closeConfigManager()
{
	try
	{
		if (bapsClient != nullptr)
		{
			bapsClient->Close();
		}
		if (ury != nullptr)
		{
			ury->Close();
		}
		if (software != nullptr)
		{
			software->Close();
		}
	}
	catch (System::Exception^ )
	{
		// WORK NEEDED: failed to close log manager exception
	}
}
int ConfigManager::getConfigValueInt(System::String^ name, int defaultValue)
{
	return safe_cast<int>(bapsClient->GetValue(name, defaultValue));
}

int ConfigManager::getConfigValueInt(System::String^ name)
{
	/** Get requested value **/
	int value = getConfigValueInt(name, -1);
	if (value == -1)
	{
		// WORK NEEDED: value not found
	}
	return value;
}

System::String^ ConfigManager::getConfigValueString(System::String^ name)
{
	/** Get requested value **/
	System::String^ value = getConfigValueString(name, nullptr);
	if (value == nullptr)
	{
		// WORK NEEDED: value not found
	}
	return value;
}
System::String^ ConfigManager::getConfigValueString(System::String^ name, System::String^ defaultValue)
{
	return static_cast<System::String^>(bapsClient->GetValue(name, defaultValue));
}

void ConfigManager::setConfigValue(System::String^ name, int value)
{
	bapsClient->SetValue(name, value);
}
/** WORK NEEDED: attempt a setx at startup to check for write access **/
void ConfigManager::setConfigValue(System::String^ name, System::String^ value)
{
	bapsClient->SetValue(name, value);
}
