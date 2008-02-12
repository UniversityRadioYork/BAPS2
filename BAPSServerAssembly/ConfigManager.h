#pragma once
#include "LogManager.h"
#include "ConfigDescriptor.h"
#include "ConfigDescriptorStringChoice.h"
#include "ConfigDescriptorIntChoice.h"


namespace BAPSServerAssembly
{
	/**
	 *  This class provides global configuration variables
	 *  and their accessors
	**/
	ref class ConfigManager;


	#define CONFIG_KEY(x) ConfigManager::configDescriptions[x]->getRegistryKey()
	#define CONFIG_DESC(x) ConfigManager::configDescriptions[x]->getDescription()
	#define CONFIG_TYPE(x) ConfigManager::configDescriptions[x]->getType()
	#define CONFIG_CHOICE_TYPE(x) ConfigManager::configDescriptions[x]->getChoiceType()
	#define CONFIG_ACCESS_RIGHTS(x) ConfigManager::configDescriptions[x]->getAccessRights()

	#define CONFIG_DEFAULTINT(x) ConfigManager::configDescriptions[x]->getDefaultInt()
	#define CONFIG_DEFAULTSTR(x) ConfigManager::configDescriptions[x]->getDefaultString()
	#define CONFIG_INDEXOPTION(x) ConfigManager::configDescriptions[x]->getIndexOption() 

	#define CONFIG_INT_CHOICE(x) static_cast<ConfigDescriptorIntChoice^>(ConfigManager::configDescriptions[x])
	#define CONFIG_STR_CHOICE(x) static_cast<ConfigDescriptorStringChoice^>(ConfigManager::configDescriptions[x])
	#define CONFIG_CHOICE(x) static_cast<ConfigDescriptorChoice^>(ConfigManager::configDescriptions[x])

	#define CONFIG_GETINT(x) ConfigManager::configDescriptions[x]->getValueInt()
	#define CONFIG_GETSTR(x) ConfigManager::configDescriptions[x]->getValueString()

	#define CONFIG_GETINTn(x,n) ConfigManager::configDescriptions[x]->getValueInt(n)
	#define CONFIG_GETSTRn(x,n) ConfigManager::configDescriptions[x]->getValueString(n)

	/** WORK NEEDED: make setting registry keys typesafe at compile time (setConfigValueInt... etc ) or maybe setOptionValue which is responsible for all checks, return code is success/fail **/
	#define CONFIG_SET(x,y) ConfigManager::configDescriptions[x]->setValue(y)
	#define CONFIG_SETn(x,n,y) ConfigManager::configDescriptions[x]->setValue(n,y)


	#define CONFIG_ISINDEXED(x) (ConfigManager::configDescriptions[x]->isIndexed())
	#define CONFIG_COUNTINDICES(x) ((CONFIG_ISINDEXED(x))?CONFIG_GETINT(CONFIG_INDEXOPTION(x)):1)

	enum ConfigError
	{
		CE_NOERROR,
		CE_PERMISSIONDENIED,
		CE_OPTIONNOTEXIST,
		CE_BADADDRESSFORMAT,
		CE_BADMASK,
		CE_RESTRICTIONEXISTS,
		CE_RESTRICTIONNOTEXIST,
		CE_LASTERROR
	};
	enum YesNoEnum
	{
		CONFIG_NO_VALUE = 0,
		CONFIG_YES_VALUE = 1
	};
	enum RepeatEnum
	{
		CONFIG_REPEAT_NONE_VALUE = 0,
		CONFIG_REPEAT_ONE_VALUE = 1,
		CONFIG_REPEAT_ALL_VALUE = 2
	};
	enum ControllerEnum
	{
		CONFIG_CONTROLLER_PLAYBACK = 0,
		CONFIG_CONTROLLER_TEXTSCREEN = 1
	};
	enum StorePlaybackEventEnum
	{
		CONFIG_PLAYBACKEVENT_STORE_NONE = 0,
		CONFIG_PLAYBACKEVENT_STORE_BUTTONSTART = 1,
		CONFIG_PLAYBACKEVENT_STORE_ALL =2
	};

	ref class ConfigManager
	{
	public:
		static void initConfigManager();
		static void closeConfigManager();
		static int  getConfigValueInt(System::String^ name);
		static int  getConfigValueInt(System::String^ name, int defaultValue);
		static System::String^ getConfigValueString(System::String^ name);
		static System::String^ getConfigValueString(System::String^ name, System::String^ defaultValue);
		static array<System::Byte>^ getConfigValueBytes(System::String^ name) ;
		static array<System::Byte>^ getConfigValueBytes(System::String^ name, array<System::Byte>^ defaultValue) ;
		static void setConfigValue(System::String^ name, int value);
		static void setConfigValue(System::String^ name, System::String^ value);
		static void setConfigValue(System::String^ name, array<System::Byte>^ value);
		static void removeValue(System::String^ name);

		static int getChannelCount()
		{
			if (channelCount == 0)
			{
				channelCount = CONFIG_GETINT(CONFIG_CHANNELCOUNT);
				if (channelCount < 1)
				{
					setChannelCount(1);
				}
			}
			return channelCount;
		}
		static void setChannelCount(int count)
		{
			if (count < 1)
			{
				count = 1;
			}
			setConfigValue("ChannelCount", count);
			channelCount = count;
		}
		
		static array<ConfigDescriptor^>^ configDescriptions;

		static array<System::String^>^ configErrors;
	private:
		static int channelCount = 0;
		static Microsoft::Win32::RegistryKey ^software, ^ury, ^baps;
	};
}