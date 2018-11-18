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
#include "BAPSController.h"

using namespace BAPSServerAssembly;
using namespace BAPSControllerAssembly;

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
		throw gcnew System::Exception("Audio device enumeration failed.");
	}

	ConfigStringChoices^ deviceChoices = gcnew ConfigStringChoices();

	for (int i = 0 ; i < devices->GetCount() ; i++)
	{
		// The first option is the default.
		deviceChoices->add(LPCWSTRToString(devices->GetDevice(i)->GetDescription()),
						   LPCWSTRToString(devices->GetDevice(i)->GetID()),
						   i == 0);
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
	/** The modes for storing play counts **/
	ConfigIntChoices^ playbackEventChoices = gcnew ConfigIntChoices();
	playbackEventChoices->add("Do not store", CONFIG_PLAYBACKEVENT_STORE_NONE, true);
	playbackEventChoices->add("Button start only", CONFIG_PLAYBACKEVENT_STORE_BUTTONSTART);
	playbackEventChoices->add("All play events", CONFIG_PLAYBACKEVENT_STORE_ALL);

	configDescriptions = gcnew array<ConfigDescriptor^>(CONFIG_LASTOPTION);
	configDescriptions[CONFIG_CHANNELCOUNT] = gcnew ConfigDescriptorInt("ChannelCount", "Number of Channels", 3, CA_RD_ONLY);
	configDescriptions[CONFIG_DEVICE] = gcnew ConfigDescriptorStringChoice("Device", CONFIG_CHANNELCOUNT, "Device", deviceChoices, CA_SU_ONLY);
	configDescriptions[CONFIG_CHANNELNAME] = gcnew ConfigDescriptorString("ChannelName", CONFIG_CHANNELCOUNT, "Name", "[set-me]", CA_RD_ONLY);
	configDescriptions[CONFIG_AUTOADVANCE] = gcnew ConfigDescriptorIntChoice("AutoAdvance", CONFIG_CHANNELCOUNT, "Auto Advance", noYesChoices, CA_ANY);
	configDescriptions[CONFIG_AUTOPLAY] = gcnew ConfigDescriptorIntChoice("AutoPlay", CONFIG_CHANNELCOUNT, "Play on load", noYesChoices, CA_ANY);
	configDescriptions[CONFIG_REPEAT] = gcnew ConfigDescriptorIntChoice("Repeat", CONFIG_CHANNELCOUNT, "Repeat", repeatChoices, CA_ANY);
	configDescriptions[CONFIG_DIRECTORYCOUNT] = gcnew ConfigDescriptorInt("DirectoryCount", "Number of directories", 3, CA_RD_ONLY);
	configDescriptions[CONFIG_NICEDIRECTORYNAME] = gcnew ConfigDescriptorString("NiceDirectoryName", CONFIG_DIRECTORYCOUNT, "Name", "[set-me]", CA_RD_ONLY);
	configDescriptions[CONFIG_DIRECTORYLOCATION] = gcnew ConfigDescriptorString("Directory", CONFIG_DIRECTORYCOUNT, "Location", "[set-me]", CA_SU_ONLY);
	configDescriptions[CONFIG_SERVERID] = gcnew ConfigDescriptorString("ServerID", "Server Identifier", "unspecified", CA_SU_ONLY);
	configDescriptions[CONFIG_PORT] = gcnew ConfigDescriptorInt("Port", "Server port", 1350, CA_SU_ONLY);
	configDescriptions[CONFIG_MAXQUEUECONNS] = gcnew ConfigDescriptorInt("MaxQueueConnections", "Maximum connections to queue", 10, CA_SU_ONLY);
	configDescriptions[CONFIG_CLIENTCONNLIMIT] = gcnew ConfigDescriptorInt("ClientConnectionLimit", "Maximum connected clients", 10, CA_SU_ONLY);
	configDescriptions[CONFIG_DBSERVER] = gcnew ConfigDescriptorString("LibraryDBServer", "Database server name", "[set-me]", CA_SU_ONLY);
	configDescriptions[CONFIG_DBPORT] = gcnew ConfigDescriptorString("LibraryDBPort", "Database server port", "5432", CA_SU_ONLY);
	configDescriptions[CONFIG_LIBRARYDBNAME] = gcnew ConfigDescriptorString("LibraryDBDatabase", "Library Database name", "[set-me]", CA_SU_ONLY);
	configDescriptions[CONFIG_BAPSDBNAME] = gcnew ConfigDescriptorString("BAPSDBDatabase", "BAPS Database name", "[set-me]", CA_SU_ONLY);
	configDescriptions[CONFIG_DBUSERNAME] = gcnew ConfigDescriptorString("LibraryDBUsername", "Database Username", "[set-me]", CA_SU_ONLY);
	configDescriptions[CONFIG_DBPASSWORD] = gcnew ConfigDescriptorString("LibraryDBPassword", "Database Password", "[set-me]", CA_SU_ONLY);
	configDescriptions[CONFIG_LIBRARYLOCATION] = gcnew ConfigDescriptorString("LibraryLocation", "Music Library location", "[set-me]", CA_SU_ONLY);
	configDescriptions[CONFIG_CLEANMUSICONLY] = gcnew ConfigDescriptorIntChoice("OnlyAllowCleanMusic", "Only Allow Clean Music", noYesChoices, CA_SU_ONLY);
	configDescriptions[CONFIG_SAVEINTROPOSITIONS] = gcnew ConfigDescriptorIntChoice("SaveIntroPositions", "Save Intro Positions", noYesChoices, CA_SU_ONLY);
	configDescriptions[CONFIG_STOREPLAYBACKEVENTS] = gcnew ConfigDescriptorIntChoice("StorePlaybackEvents", "Log/Tracklist Playbacks", playbackEventChoices, CA_SU_ONLY);
	configDescriptions[CONFIG_LOGNAME] = gcnew ConfigDescriptorString("LogName", "System Log Name", "BAPS Log", CA_SU_ONLY);
	configDescriptions[CONFIG_LOGSOURCE] = gcnew ConfigDescriptorString("LogSource", "System Log Source", "BAPS", CA_SU_ONLY);
	configDescriptions[CONFIG_SUPPORTADDRESS] = gcnew ConfigDescriptorString("SupportAddress", "Support E-mail address", "baps@ury.org.uk", CA_RD_ONLY);
	configDescriptions[CONFIG_SMTPSERVER] = gcnew ConfigDescriptorString("SMTP Server", "SMTP server IP address", "<none>", CA_SU_ONLY);
	
	BAPSControllerAssembly::BAPSController^ bc = gcnew BAPSControllerAssembly::BAPSController();

	/** Get the serial port options for BAPSController (1) on startup **/
	ConfigStringChoices^ controllerPortChoices = gcnew ConfigStringChoices();

	try {
		array<System::String^>^ serialPortNames = System::IO::Ports::SerialPort::GetPortNames();

		for (int i = 0; i < serialPortNames->Length; i++)
		{
			// The first option is the default.
			controllerPortChoices->add(serialPortNames[i],
				serialPortNames[i],
				i == 0);
		}
	}
	catch (System::Exception^ e) {
		throw gcnew BAPSTerminateException(System::String::Concat("Failed to enumerate Serial Port Names:\n", e->Message, "Stack Trace:\n", e->StackTrace));
	}

	/** Get the serial numbers of BAPSController2 devices **/
	ConfigStringChoices^ bapsController2Choices = gcnew ConfigStringChoices();

	array<System::String^>^ serials = bc->getSerialNumbers();
	for (int i = 0; i < serials->Length; i++)
	{
		bapsController2Choices->add(serials[i], serials[i], (i == 0));
	}

	bapsController2Choices->add("none", "none", (serials->Length == 0));

	delete bc;

	configDescriptions[CONFIG_BAPSCONTROLLERENABLED] = gcnew ConfigDescriptorIntChoice("BAPSControllerEnabled", "COM Controller Enabled", noYesChoices, CA_SU_ONLY);
	configDescriptions[CONFIG_BAPSCONTROLLERPORT] = gcnew ConfigDescriptorStringChoice("BAPSControllerPort", "COM Controller Port", controllerPortChoices, CA_SU_ONLY);
	configDescriptions[CONFIG_BAPSCONTROLLERBUTTONCOUNT] = gcnew ConfigDescriptorInt("BAPSControllerButtonCount", "COM Controller Button Count", 6, CA_SU_ONLY);
	configDescriptions[CONFIG_BAPSCONTROLLERBUTTONCODE] = gcnew ConfigDescriptorInt("BAPSControllerButtonCode", CONFIG_BAPSCONTROLLERBUTTONCOUNT, "Button Code", 255, CA_SU_ONLY);
	configDescriptions[CONFIG_BAPSPADDLEMODE] = gcnew ConfigDescriptorIntChoice("BAPSPaddleMode", "COM Controller Paddle Mode", paddleChoices, CA_ANY);


	configDescriptions[CONFIG_BAPSCONTROLLER2ENABLED] = gcnew ConfigDescriptorIntChoice("BAPSController2Enabled", "USB Controller Enabled", noYesChoices, CA_SU_ONLY);
	configDescriptions[CONFIG_BAPSCONTROLLER2DEVICECOUNT] = gcnew ConfigDescriptorInt("BAPSController2DeviceCount", "USB Controller Device Count", (serials->Length==0)?1:serials->Length, CA_SU_ONLY);
	CONFIG_SET(CONFIG_BAPSCONTROLLER2DEVICECOUNT, (serials->Length==0)?1:serials->Length);

	/* work needed: force the device count */
	configDescriptions[CONFIG_BAPSCONTROLLER2SERIAL] = gcnew ConfigDescriptorStringChoice("BAPSController2Serial", CONFIG_BAPSCONTROLLER2DEVICECOUNT, "Serial", bapsController2Choices, CA_SU_ONLY);
	configDescriptions[CONFIG_BAPSCONTROLLER2OFFSET] = gcnew ConfigDescriptorInt("BAPSController2Offset", CONFIG_BAPSCONTROLLER2DEVICECOUNT, "Signal Offset", 0, CA_SU_ONLY);
	configDescriptions[CONFIG_BAPSCONTROLLER2BUTTONCOUNT] = gcnew ConfigDescriptorInt("BAPSController2ButtonCount", "USB Controller Button Count", 6, CA_SU_ONLY);
	configDescriptions[CONFIG_BAPSCONTROLLER2BUTTONCODE] = gcnew ConfigDescriptorInt("BAPSController2ButtonCode", CONFIG_BAPSCONTROLLER2BUTTONCOUNT, "Button Code", 255, CA_SU_ONLY);

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
