#pragma once

#include "ConfigDescriptor.h"

ref class ConfigDescriptorString : public ConfigDescriptor
{
public:
	ConfigDescriptorString(
		System::String^ _registryKey,
		ConfigOption _indexOption,
		System::String^ _description,
		System::String^ _defaultString,
		ConfigAccess _accessRights)
	:	defaultString(_defaultString),
		ConfigDescriptor(CONFIG_TYPE_STR, _registryKey, _indexOption, _description, _accessRights)
	{}
		ConfigDescriptorString(
		System::String^ _registryKey,
		System::String^ _description,
		System::String^ _defaultString,
		ConfigAccess _accessRights)
	:	defaultString(_defaultString),
		ConfigDescriptor(CONFIG_TYPE_STR, _registryKey, _description, _accessRights)
	{}
	
	virtual System::String^ getDefaultString() override
	{
		return defaultString;
	}
	virtual bool setValue(System::String^ value) override;
	virtual bool setValue(int index, System::String^ value) override;
	virtual System::String^ getValueString() override;
	virtual System::String^ getValueString(int index) override;

private:
	System::String^ defaultString;
};