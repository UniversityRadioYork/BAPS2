#pragma once

#include "ConfigChoices.h"

namespace BAPSServerAssembly
{
	ref struct ConfigStringChoice : ConfigChoice
	{
		ConfigStringChoice(System::String^ _description, System::String^ _choice)
			: ConfigChoice(_description), choice(_choice)
		{}
		System::String^ choice;
	};

	ref class ConfigStringChoices : ConfigChoices
	{
	public:
		ConfigStringChoices() : ConfigChoices()
		{
		}
		void add(System::String^ description, System::String^ choice, bool isDefault)
		{
			choiceTable->Add(gcnew ConfigStringChoice(description, choice));
			if (isDefault)
			{
				defaultIndex = (choiceTable->Count -1);
			}
		}
		System::String^ getDefaultChoice()
		{
			if (choiceTable->Count > 0)
			{
				return static_cast<ConfigStringChoice^>(choiceTable->default[defaultIndex])->choice;
			}
			else
			{
				return "";
			}
		}
		System::String^ getChoice(int index)
		{
			if (indexExists(index))
			{
				return static_cast<ConfigStringChoice^>(choiceTable->default[index])->choice;
			}
			else
			{
				//WORK NEEDED: exception here
				return nullptr;
			}
		}
		void add(System::String^ description, System::String^ choice)
		{
			add(description, choice, false);
		}

		bool contains(System::String^ _choice)
		{
			return (indexOf(_choice) != -1);
		}
		int indexOf(System::String^ _choice)
		{
			int i = 0;
			for ( i = 0 ; i < choiceTable->Count ; i++ )
			{
				if (System::String::Compare(static_cast<ConfigStringChoice^>(choiceTable->default[i])->choice, _choice) == 0)
				{
					return i;
				}
			}
			return -1;
		}
	};
};