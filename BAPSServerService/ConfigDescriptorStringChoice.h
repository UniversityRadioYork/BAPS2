#pragma once
#include "ConfigDescriptorChoice.h"
#include "ConfigStringChoices.h"

ref class ConfigDescriptorStringChoice : public ConfigDescriptorChoice
{
public:
	
	ConfigDescriptorStringChoice(
		System::String^ _registryKey,
		ConfigOption _indexOption,
		System::String^ _description,
		ConfigStringChoices^ _choices,
		ConfigAccess _accessRights)
		: ConfigDescriptorChoice(CONFIG_TYPE_STR, _registryKey, _indexOption, _description, _accessRights),
		  choices(_choices)
	{};

	ConfigDescriptorStringChoice(
		System::String^ _registryKey,
		System::String^ _description,
		ConfigStringChoices^ _choices,
		ConfigAccess _accessRights)
		: ConfigDescriptorChoice(CONFIG_TYPE_STR, _registryKey, _description, _accessRights),
		  choices(_choices)
	{};

	virtual bool setValue(System::String^ value) override;
	virtual bool setValue(int index, System::String^ value) override;
	virtual bool setValueUsingChoice(int _choiceIndex) override;
	virtual bool setValueUsingChoice(int index, int _choiceIndex) override;
	virtual System::String^ getValueString() override;
	virtual System::String^ getValueString(int index) override;
	virtual int getValueAsChoice() override;
	virtual int getValueAsChoice(int index) override;
	virtual System::String^ getDefaultString() override
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
	virtual int getValueAsChoice(System::String^ regKey) override;	
	virtual bool setValueUsingChoice(System::String^ regKey, int _choiceIndex) override;
	ConfigStringChoices^ choices;
};