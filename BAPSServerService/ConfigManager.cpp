#include "stdafx.h"
#include "ConfigManager.h"
#include "Exceptions.h"
#include "LogManager.h"
#include "BAPSAudioOutputDevices.h"
#include "ConfigDescriptorInt.h"
#include "ConfigDescriptorIntChoice.h"
#include "ConfigDescriptorString.h"
#include "ConfigDescriptorStringChoice.h"
#include "utility.h"
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
		localMachine = Microsoft::Win32::Registry::LocalMachine;
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
		baps = ury->OpenSubKey("BAPS", true);
		if (baps == nullptr)
		{
			baps = ury->CreateSubKey("BAPS");
			if (baps == nullptr)
			{
				throw gcnew System::Exception("Create of BAPS key failed");
			}
		}
	}
	catch (System::Exception^ e)
	{
		throw gcnew BAPSTerminateException(System::String::Concat("ConfigManager failed to initialize:\n", e->Message, "Stack Trace:\n",e->StackTrace));
	}
	CBAPSAudioOutputDevices* devices = new CBAPSAudioOutputDevices();
	if (devices->Initialise() == FALSE)
	{
		// WORK NEEDED: better exception system
		throw gcnew System::Exception("device enumeration failed");
	}
	
	ConfigStringChoices^ deviceChoices = gcnew ConfigStringChoices();
	int i = 0;
	bool isDefault = true;

	for (i = 0 ; i < devices->GetCount() ; i++)
	{
		if (i != 0)
		{
			isDefault = false;
		}
		
		deviceChoices->add(LPCWSTRToString(devices->GetDevice(i)->GetDescription()),
						   LPCWSTRToString(devices->GetDevice(i)->GetID()),
						   isDefault);
	}
	ConfigIntChoices^ yesNoChoices = gcnew ConfigIntChoices();
	yesNoChoices->add("Yes", CONFIG_YES_VALUE, true);
	yesNoChoices->add("No", CONFIG_NO_VALUE);
	ConfigIntChoices^ noYesChoices = gcnew ConfigIntChoices();
	noYesChoices->add("Yes", CONFIG_YES_VALUE);
	noYesChoices->add("No", CONFIG_NO_VALUE, true);
	ConfigIntChoices^ repeatChoices = gcnew ConfigIntChoices();
	/** These values are hard coded in other parts of the server **/
	repeatChoices->add("No repeat", CONFIG_REPEAT_NONE_VALUE, true);
	repeatChoices->add("Repeat one", CONFIG_REPEAT_ONE_VALUE);
	repeatChoices->add("Repeat all", CONFIG_REPEAT_ALL_VALUE);
	/** The modes in which the paddle can operate **/
	ConfigIntChoices^ paddleChoices = gcnew ConfigIntChoices();
	paddleChoices->add("Playback Controller", CONFIG_CONTROLLER_PLAYBACK);
	paddleChoices->add("Text Controller", CONFIG_CONTROLLER_TEXTSCREEN, true);

	configDescriptions = gcnew array<ConfigDescriptor^>(CONFIG_LASTOPTION);
	configDescriptions[CONFIG_CHANNELCOUNT] = gcnew ConfigDescriptorInt("ChannelCount", "Number of Channels", 1, CA_RD_ONLY);
	configDescriptions[CONFIG_DEVICE] = gcnew ConfigDescriptorStringChoice("Device", CONFIG_CHANNELCOUNT, "Output device", deviceChoices, CA_SU_ONLY);
	configDescriptions[CONFIG_CHANNELNAME] = gcnew ConfigDescriptorString("ChannelName", CONFIG_CHANNELCOUNT, "Channel Name", "[set-me]", CA_RD_ONLY);
	configDescriptions[CONFIG_AUTOADVANCE] = gcnew ConfigDescriptorIntChoice("AutoAdvance", CONFIG_CHANNELCOUNT, "Automatically advance", noYesChoices, CA_ANY);
	configDescriptions[CONFIG_AUTOPLAY] = gcnew ConfigDescriptorIntChoice("AutoPlay", CONFIG_CHANNELCOUNT, "Play on load", noYesChoices, CA_ANY);
	configDescriptions[CONFIG_REPEAT] = gcnew ConfigDescriptorIntChoice("Repeat", CONFIG_CHANNELCOUNT, "Repeat", repeatChoices, CA_ANY);
	configDescriptions[CONFIG_DIRECTORYCOUNT] = gcnew ConfigDescriptorInt("DirectoryCount", "Number of directories", 3, CA_RD_ONLY);
	configDescriptions[CONFIG_NICEDIRECTORYNAME] = gcnew ConfigDescriptorString("NiceDirectoryName", CONFIG_DIRECTORYCOUNT, "Nice directory name", "[set-me]", CA_RD_ONLY);
	configDescriptions[CONFIG_DIRECTORYLOCATION] = gcnew ConfigDescriptorString("Directory", CONFIG_DIRECTORYCOUNT, "Directory location", "[set-me]", CA_SU_ONLY);
	configDescriptions[CONFIG_SERVERID] = gcnew ConfigDescriptorString("ServerID", "Server Identifier", "unspecified", CA_SU_ONLY);
	configDescriptions[CONFIG_PORT] = gcnew ConfigDescriptorInt("Port", "Server port", 1350, CA_SU_ONLY);
	configDescriptions[CONFIG_MAXQUEUECONNS] = gcnew ConfigDescriptorInt("MaxQueueConnections", "Maximum connections to queue", 10, CA_SU_ONLY);
	configDescriptions[CONFIG_CLIENTCONNLIMIT] = gcnew ConfigDescriptorInt("ClientConnectionLimit", "Maximum connected clients", 10, CA_SU_ONLY);
	configDescriptions[CONFIG_DBSERVER] = gcnew ConfigDescriptorString("LibraryDBServer", "Database server name", "[set-me]", CA_SU_ONLY);
	configDescriptions[CONFIG_DBPORT] = gcnew ConfigDescriptorString("LibraryDBPort", "Database server port", "5432", CA_SU_ONLY);
	configDescriptions[CONFIG_LIBRARYDBNAME] = gcnew ConfigDescriptorString("LibraryDBDatabase", "Database name", "recordlib", CA_SU_ONLY);
	configDescriptions[CONFIG_BAPSDBNAME] = gcnew ConfigDescriptorString("BAPSDBDatabase", "BAPS Database name", "baps", CA_SU_ONLY);
	configDescriptions[CONFIG_DBUSERNAME] = gcnew ConfigDescriptorString("LibraryDBUsername", "Database Username", "web", CA_SU_ONLY);
	configDescriptions[CONFIG_DBPASSWORD] = gcnew ConfigDescriptorString("LibraryDBPassword", "Database Password", "spider", CA_SU_ONLY);
	configDescriptions[CONFIG_LIBRARYLOCATION] = gcnew ConfigDescriptorString("LibraryLocation", "Music Library location", "[set-me]", CA_SU_ONLY);
	configDescriptions[CONFIG_SAVEINTROPOSITIONS] = gcnew ConfigDescriptorIntChoice("SaveIntroPositions", "Save Intro Positions", noYesChoices, CA_SU_ONLY);
	configDescriptions[CONFIG_STOREPLAYCOUNTS] = gcnew ConfigDescriptorIntChoice("StorePlayCounts", "Store Play Counts", noYesChoices, CA_SU_ONLY);
	configDescriptions[CONFIG_LOGNAME] = gcnew ConfigDescriptorString("LogName", "System Log Name", "BAPS Log", CA_SU_ONLY);
	configDescriptions[CONFIG_LOGSOURCE] = gcnew ConfigDescriptorString("LogSource", "System Log Source", "BAPS", CA_SU_ONLY);
	configDescriptions[CONFIG_SUPPORTADDRESS] = gcnew ConfigDescriptorString("SupportAddress", "Support E-mail address", "baps@ury.york.ac.uk", CA_RD_ONLY);
	configDescriptions[CONFIG_SMTPSERVER] = gcnew ConfigDescriptorString("SMTP Server", "SMTP server IP address", "<none>", CA_SU_ONLY);
	configDescriptions[CONFIG_BAPSCONTROLLERENABLED] = gcnew ConfigDescriptorIntChoice("BAPSControllerEnabled", "BAPS Controller Enabled", noYesChoices, CA_SU_ONLY);
	configDescriptions[CONFIG_BAPSCONTROLLERBUTTONCOUNT] = gcnew ConfigDescriptorInt("BAPSControllerButtonCount", "BAPS Controller Button Count", 6, CA_SU_ONLY);
	configDescriptions[CONFIG_BAPSCONTROLLERBUTTONCODE] = gcnew ConfigDescriptorInt("BAPSControllerButtonCode", CONFIG_BAPSCONTROLLERBUTTONCOUNT, "Button Code", 255, CA_SU_ONLY);
	configDescriptions[CONFIG_BAPSPADDLEMODE] = gcnew ConfigDescriptorIntChoice("BAPSPaddleMode", "BAPS Paddle Mode", paddleChoices ,CA_ANY);
	configDescriptions[CONFIG_CLEANMUSICONLY] = gcnew ConfigDescriptorIntChoice("OnlyAllowCleanMusic", "Only Allow Clean Music", noYesChoices ,CA_SU_ONLY);

	configErrors = gcnew array<System::String^>(CE_LASTERROR);
	configErrors[CE_NOERROR] = "No error";
	configErrors[CE_PERMISSIONDENIED] = "Insufficient Privilidge";
	configErrors[CE_OPTIONNOTEXIST] = "The requested option does not exist";
	configErrors[CE_BADADDRESSFORMAT] = "Badly formatted address";
	configErrors[CE_BADMASK] = "Badly formatted mask";
	configErrors[CE_RESTRICTIONEXISTS] = "IP restriction already exists";
	configErrors[CE_RESTRICTIONNOTEXIST] = "IP restriction does not exist";
	
}

void ConfigManager::closeConfigManager()
{
	try
	{
		if (baps != nullptr)
		{
			baps->Close();
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
	catch (System::Exception^ e)
	{
		LogManager::emergency(System::String::Concat("ConfigManager failed to close:\n", e->Message, "Stack Trace:\n",e->StackTrace));
	}
}
int ConfigManager::getConfigValueInt(System::String^ name, int defaultValue)
{
	return *static_cast<int^>(baps->GetValue(name, defaultValue));
}

int ConfigManager::getConfigValueInt(System::String^ name)
{
	/** Get requested value **/
	int value = getConfigValueInt(name, -1);
	if (value == -1)
	{
		/** Failed to find value - do config system exception handling **/
		throw gcnew BAPSConfigException(System::String::Concat("BAPS Config - ",name," value not found in registry"));
	}
	return value;
}

System::String^ ConfigManager::getConfigValueString(System::String^ name)
{
	/** Get requested value **/
	System::String^ value = getConfigValueString(name, nullptr);
	if (value == nullptr)
	{
		/** Failed to find value - do config system exception handling **/
		throw gcnew BAPSConfigException(System::String::Concat("BAPS Config - ",name," value not found in registry"));
	}
	return value;
}
System::String^ ConfigManager::getConfigValueString(System::String^ name, System::String^ defaultValue)
{
	return static_cast<System::String^>(baps->GetValue(name, defaultValue));
}
array<System::Byte>^ ConfigManager::getConfigValueBytes(System::String^ name)
{
	/** Get requested value **/
	array<System::Byte>^ value = getConfigValueBytes(name, nullptr);
	if (value == nullptr)
	{
		/** Failed to find value - do config system exception handling **/
		throw gcnew BAPSConfigException(System::String::Concat("BAPS Config - ",name," value not found in registry"));
	}
	return value;
}

array<System::Byte>^ ConfigManager::getConfigValueBytes(System::String^ name, array<System::Byte>^ defaultValue)
{
	return static_cast<array<System::Byte>^>(baps->GetValue(name, defaultValue));
}

void ConfigManager::setConfigValue(System::String^ name, int value)
{
	baps->SetValue(name, value);
}
/** WORK NEEDED: attempt a setx at startup to check for write access **/
void ConfigManager::setConfigValue(System::String^ name, System::String^ value)
{
	baps->SetValue(name, value);
}
void ConfigManager::setConfigValue(System::String^ name, array<System::Byte>^ value)
{
	baps->SetValue(name, value);
}
void ConfigManager::removeValue(System::String^ name)
{
	baps->DeleteValue(name, false);
}