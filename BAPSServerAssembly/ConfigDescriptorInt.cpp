#include "stdafx.h"
#include "ConfigManager.h"
#include "ConfigDescriptorInt.h"

using namespace BAPSServerAssembly;

bool ConfigDescriptorInt::setValue(int value)
{
	ConfigManager::setConfigValue(getRegistryKey(), value);
	return true;
}
bool ConfigDescriptorInt::setValue(int index, int value)
{
	ConfigManager::setConfigValue(getRegistryKey(index), value);
	return true;
}
int ConfigDescriptorInt::getValueInt()
{
	return ConfigManager::getConfigValueInt(getRegistryKey(), getDefaultInt());
}
int ConfigDescriptorInt::getValueInt(int index)
{
	return ConfigManager::getConfigValueInt(getRegistryKey(index), getDefaultInt());
}