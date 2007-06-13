#include "stdafx.h"
#include "ConfigManager.h"
#include "ConfigDescriptorIntChoice.h"

using namespace BAPSServerAssembly;

bool ConfigDescriptorIntChoice::setValue(int value)
{
	int choiceIndex = choices->indexOf(value);
	return setValueUsingChoice(choiceIndex);
}
bool ConfigDescriptorIntChoice::setValue(int index, int value)
{
	int choiceIndex = choices->indexOf(value);
	return setValueUsingChoice(index, choiceIndex);
}
int ConfigDescriptorIntChoice::getValueInt()
{
	return choices->getChoice(getValueAsChoice());
}
int ConfigDescriptorIntChoice::getValueInt(int index)
{
	return choices->getChoice(getValueAsChoice(index));
}
bool ConfigDescriptorIntChoice::setValueUsingChoice(int _choiceIndex)
{
	return setValueUsingChoice(getRegistryKey(), _choiceIndex);
}
bool ConfigDescriptorIntChoice::setValueUsingChoice(int index, int _choiceIndex)
{
	return setValueUsingChoice(getRegistryKey(index), _choiceIndex);
}
bool ConfigDescriptorIntChoice::setValueUsingChoice(System::String^ regKey, int _choiceIndex)
{
	if (choices->indexExists(_choiceIndex))
	{
		ConfigManager::setConfigValue(regKey, choices->getChoice(_choiceIndex));
		return true;
	}
	else
	{
		return false;
	}
}

int ConfigDescriptorIntChoice::getValueAsChoice()
{
	return getValueAsChoice(getRegistryKey());
}
int ConfigDescriptorIntChoice::getValueAsChoice(int index)
{
	return getValueAsChoice(getRegistryKey(index));
}
int ConfigDescriptorIntChoice::getValueAsChoice(System::String^ regKey)
{
	int value = ConfigManager::getConfigValueInt(regKey, getDefaultInt());
	int choiceIndex = choices->indexOf(value);
	if (choiceIndex == -1)
	{
		choiceIndex = choices->getDefaultIndex();
		ConfigManager::setConfigValue(regKey, getDefaultInt());
	}
	return choiceIndex;
}