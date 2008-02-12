#pragma once

#include "ConfigChoices.h"

namespace BAPSServerAssembly
{
	ref struct ConfigIntChoice : ConfigChoice
	{
		ConfigIntChoice(System::String^ _description, int _choice)
			: ConfigChoice(_description), choice(_choice)
		{}
		int choice;
	};

	ref class ConfigIntChoices : ConfigChoices
	{
	public:
		ConfigIntChoices() : ConfigChoices()
		{
		}
		void add(System::String^ description, int choice, bool isDefault)
		{
			choiceTable->Add(gcnew ConfigIntChoice(description, choice));
			if (isDefault)
			{
				defaultIndex = (choiceTable->Count -1);
			}
		}
		int getDefaultChoice()
		{
			if (choiceTable->Count > 0)
			{
				return static_cast<ConfigIntChoice^>(choiceTable->default[defaultIndex])->choice;
			}
			else
			{
				return 0;
			}
		}
		int getChoice(int index)
		{
			if (indexExists(index))
			{
				return static_cast<ConfigIntChoice^>(choiceTable->default[index])->choice;
			}
			else
			{
				//WORK NEEDED: exception here
				return 0;
			}
		}
		void add(System::String^ description, int choice)
		{
			add(description, choice, false);
		}

		bool contains(int _choice)
		{
			return (indexOf(_choice) != -1);
		}
		int indexOf(int _choice)
		{
			int i = 0;
			for ( i = 0 ; i < choiceTable->Count ; i++ )
			{
				if (static_cast<ConfigIntChoice^>(choiceTable->default[i])->choice == _choice)
				{
					return i;
				}
			}
			return -1;
		}
	};
};