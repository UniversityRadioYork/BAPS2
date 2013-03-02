#include "stdafx.h"
#include "ConfigManager.h"
#include "ConfigDescriptorString.h"

using namespace BAPSServerAssembly;

bool ConfigDescriptorString::setValue(System::String^ value)
{
	ConfigManager::setConfigValue(getRegistryKey(), value);
	return true;
}
bool ConfigDescriptorString::setValue(int index, System::String^ value)
{
	ConfigManager::setConfigValue(getRegistryKey(index), value);
	return true;
}
System::String^ ConfigDescriptorString::getValueString()
{
	return ConfigManager::getConfigValueString(getRegistryKey(), getDefaultString());
}
System::String^ ConfigDescriptorString::getValueString(int index)
{
	return ConfigManager::getConfigValueString(getRegistryKey(index), getDefaultString());
}