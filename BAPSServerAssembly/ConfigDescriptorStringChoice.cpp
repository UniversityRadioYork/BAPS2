#include "stdafx.h"
#include "ConfigManager.h"
#include "ConfigDescriptorStringChoice.h"

using namespace BAPSServerAssembly;

bool ConfigDescriptorStringChoice::setValue(System::String^ value)
{
	int choiceIndex = choices->indexOf(value);
	return setValueUsingChoice(choiceIndex);
}
bool ConfigDescriptorStringChoice::setValue(int index, System::String^ value)
{
	int choiceIndex = choices->indexOf(value);
	return setValueUsingChoice(index, choiceIndex);
}
System::String^ ConfigDescriptorStringChoice::getValueString()
{
	return choices->getChoice(getValueAsChoice());
}
System::String^ ConfigDescriptorStringChoice::getValueString(int index)
{
	return choices->getChoice(getValueAsChoice(index));
}
bool ConfigDescriptorStringChoice::setValueUsingChoice(int _choiceIndex)
{
	return setValueUsingChoice(getRegistryKey(), _choiceIndex);
}
bool ConfigDescriptorStringChoice::setValueUsingChoice(int index, int _choiceIndex)
{
	return setValueUsingChoice(getRegistryKey(index), _choiceIndex);
}
bool ConfigDescriptorStringChoice::setValueUsingChoice(System::String^ regKey, int _choiceIndex)
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

int ConfigDescriptorStringChoice::getValueAsChoice()
{
	return getValueAsChoice(getRegistryKey());
}
int ConfigDescriptorStringChoice::getValueAsChoice(int index)
{
	return getValueAsChoice(getRegistryKey(index));
}
int ConfigDescriptorStringChoice::getValueAsChoice(System::String^ regKey)
{
	System::String^ value = ConfigManager::getConfigValueString(regKey, getDefaultString());
	int choiceIndex = choices->indexOf(value);
	if (choiceIndex == -1)
	{
		choiceIndex = choices->getDefaultIndex();
		ConfigManager::setConfigValue(regKey, getDefaultString());
	}
	return choiceIndex;
}