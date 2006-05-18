#pragma once
#include "ConfigDescriptorChoice.h"
#include "ConfigIntChoices.h"

ref class ConfigDescriptorIntChoice : public ConfigDescriptorChoice
{
public:
	
	ConfigDescriptorIntChoice(
		System::String^ _registryKey,
		ConfigOption _indexOption,
		System::String^ _description,
		ConfigIntChoices^ _choices,
		ConfigAccess _accessRights)
		: ConfigDescriptorChoice(CONFIG_TYPE_INT, _registryKey, _indexOption, _description, _accessRights),
		  choices(_choices)
	{};

	ConfigDescriptorIntChoice(
		System::String^ _registryKey,
		System::String^ _description,
		ConfigIntChoices^ _choices,
		ConfigAccess _accessRights)
		: ConfigDescriptorChoice(CONFIG_TYPE_INT, _registryKey, _description, _accessRights),
		  choices(_choices)
	{};

	virtual bool setValue(int value) override;
	virtual bool setValue(int index, int value) override;
	virtual bool setValueUsingChoice(int _choiceIndex) override;
	virtual bool setValueUsingChoice(int index, int _choiceIndex) override;
	virtual int getValueInt() override;
	virtual int getValueInt(int index) override;
	virtual int getValueAsChoice() override;
	virtual int getValueAsChoice(int index) override;
	virtual int getDefaultInt() override
	{
		return choices->getDefaultChoice();
	}
	virtual System::String^ getChoiceDescription(int _choiceIndex) override
	{
		return choices->getChoiceDescription(_choiceIndex);
	}
	virtual int getChoiceCount() override
	{
		return choices->getChoiceCount();
	}
protected:
	virtual int getValueAsChoice(System::String^ regKey) sealed override;	
	virtual bool setValueUsingChoice(System::String^ regKey, int _choiceIndex) sealed override;
	ConfigIntChoices^ choices;
};