#pragma once
#include "ConfigDescriptor.h"

namespace BAPSServerAssembly
{
	ref class ConfigDescriptorChoice abstract : public ConfigDescriptor
	{
	public:
		
		ConfigDescriptorChoice(
			ConfigType choiceType,
			System::String^ _registryKey,
			ConfigOption _indexOption,
			System::String^ _description,
			ConfigAccess _accessRights)
			: ConfigDescriptor(CONFIG_TYPE_CHOICE, choiceType, _registryKey, _indexOption, _description, _accessRights)
		{};

		ConfigDescriptorChoice(
			ConfigType choiceType,
			System::String^ _registryKey,
			System::String^ _description,
			ConfigAccess _accessRights)
			: ConfigDescriptor(CONFIG_TYPE_CHOICE, choiceType, _registryKey, _description, _accessRights)
		{};

		virtual bool setValueUsingChoice(int _choiceIndex) abstract;
		virtual bool setValueUsingChoice(int index, int _choiceIndex) abstract;
		virtual int getValueAsChoice() abstract;
		virtual int getValueAsChoice(int index) abstract;
		virtual System::String^ getChoiceDescription(int _choiceIndex) abstract;
		virtual int getChoiceCount() abstract;
	protected:
		virtual int getValueAsChoice(System::String^ regKey) abstract;	
		virtual bool setValueUsingChoice(System::String^ regKey, int _choiceIndex) abstract;
	};
};