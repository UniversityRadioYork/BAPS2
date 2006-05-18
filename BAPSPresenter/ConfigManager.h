#pragma once

/**
 *  This class provides global configuration variables
 *  and their accessors
**/

ref class ConfigManager
{
public:
	static void initConfigManager();
	static void closeConfigManager();
	static int  getConfigValueInt(System::String^ name);
	static int  getConfigValueInt(System::String^ name, int defaultValue);
	static System::String^ getConfigValueString(System::String^ name);
	static System::String^ getConfigValueString(System::String^ name, System::String^ defaultValue);
	static void setConfigValue(System::String^ name, int value);
	static void setConfigValue(System::String^ name, System::String^ value);

private:
	static Microsoft::Win32::RegistryKey ^software, ^ury, ^bapsClient;
};