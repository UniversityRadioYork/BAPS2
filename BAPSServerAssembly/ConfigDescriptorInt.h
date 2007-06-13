#pragma once
#include "ConfigDescriptor.h"

namespace BAPSServerAssembly
{
	ref class ConfigDescriptorInt : public ConfigDescriptor
	{
	public:
		ConfigDescriptorInt(
			System::String^ _registryKey,
			ConfigOption _indexOption,
			System::String^ _description,
			int _defaultInt,
			ConfigAccess _accessRights)
		:	defaultInt(_defaultInt),
			ConfigDescriptor(CONFIG_TYPE_INT, _registryKey, _indexOption, _description, _accessRights)
		{};

		ConfigDescriptorInt(
			System::String^ _registryKey,
			System::String^ _description,
			int _defaultInt,
			ConfigAccess _accessRights)
		:	defaultInt(_defaultInt),
			ConfigDescriptor(CONFIG_TYPE_INT, _registryKey, _description, _accessRights)
		{};
		virtual int getDefaultInt() override
		{
			return defaultInt;
		}
		virtual bool setValue(int value) override;
		virtual bool setValue(int index, int value) override;
		virtual int getValueInt() override;
		virtual int getValueInt(int index) override;
	private:
		int defaultInt;
	};
};