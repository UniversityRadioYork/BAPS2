#pragma once

#include "ConfigOptions.h"
#include "Exceptions.h"

enum ConfigAccess
{
	CA_SU_ONLY,
	CA_RD_ONLY,
	CA_ANY
};


ref class ConfigDescriptor abstract
{
public:
	ConfigDescriptor(
		ConfigType _type,
		System::String^ _registryKey,
		ConfigOption _indexOption,
		System::String^ _description,
		ConfigAccess _accessRights)
	:	registryKey(_registryKey),
		indexOption(_indexOption),
		indexed(true),
		description(_description),
		type(_type),
		accessRights(_accessRights)
	{}
	ConfigDescriptor(
		ConfigType _type,
		System::String^ _registryKey,
		System::String^ _description,
		ConfigAccess _accessRights)
	:	registryKey(_registryKey),
		indexed(false),
		description(_description),
		type(_type),
		accessRights(_accessRights)
	{}
	ConfigDescriptor(
		ConfigType _type,
		ConfigType _choiceType,
		System::String^ _registryKey,
		ConfigOption _indexOption,
		System::String^ _description,
		ConfigAccess _accessRights)
	:	registryKey(_registryKey),
		indexOption(_indexOption),
		indexed(true),
		description(_description),
		type(_type),
		choiceType(_choiceType),
		accessRights(_accessRights)
	{}
	ConfigDescriptor(
		ConfigType _type,
		ConfigType _choiceType,
		System::String^ _registryKey,
		System::String^ _description,
		ConfigAccess _accessRights)
	:	registryKey(_registryKey),
		indexed(false),
		description(_description),
		type(_type),
		choiceType(_choiceType),
		accessRights(_accessRights)
	{}

	virtual System::String^ getDefaultString()
	{
		throw gcnew BAPSProgramErrorException(System::String::Concat("String value not available for: ", getRegistryKey(), ":", getDescription()));
		return "-1";
	}
	virtual int getDefaultInt()
	{
		throw gcnew BAPSProgramErrorException(System::String::Concat("Integer value not available for: ", getRegistryKey(), ":", getDescription()));
		return -1;
	}
	inline System::String^ getRegistryKey()
	{
		// WORK  NEEDED: assert not indexed
		return registryKey;
	}
	inline System::String^ getRegistryKey(int index)
	{
		// WORK NEEDED: assert indexed and index valid
		return System::String::Concat(registryKey, index.ToString());
	}
	inline ConfigOption getIndexOption()
	{
		return indexOption;
	}
	inline bool isIndexed()
	{
		return indexed;
	}
	inline System::String^ getDescription()
	{
		return description;
	}
	inline ConfigType getType()
	{
		return type;
	}
	inline ConfigType getChoiceType()
	{
		return choiceType;
	}
	inline ConfigAccess getAccessRights()
	{
		return accessRights;
	}
	virtual bool setValue(int value)
	{
		return false;
	}
	virtual bool setValue(System::String^ value)
	{
		return false;
	}
	virtual bool setValue(int index, int value)
	{
		return false;
	}
	virtual bool setValue(int index, System::String^ value)
	{
		return false;
	}
	virtual int getValueInt()
	{
		// WORK NEEDED: raise exception
		return -1;
	}
	virtual System::String^ getValueString()
	{
		// WORK NEEDED: raise exception
		return "-1";
	}
	virtual int getValueInt(int index)
	{
		// WORK NEEDED: raise exception
		return -1;
	}
	virtual System::String^ getValueString(int index)
	{
		// WORK NEEDED: raise exception
		return "-1";
	}
private:
	System::String^ registryKey;
	ConfigOption indexOption;
	bool indexed;
	System::String^ description;
	ConfigType type;
	ConfigType choiceType;
	ConfigAccess accessRights;
};