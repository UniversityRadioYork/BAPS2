#pragma once

namespace BAPSServerAssembly
{
	ref struct ConfigStringChoice
	{
		ConfigStringChoice(System::String^ _description, System::String^ _choice)
			: description(_description), choice(_choice)
		{}
		System::String^ description;
		System::String^ choice;
	};

	ref class ConfigStringChoices
	{
	public:
		ConfigStringChoices()
		{
			defaultIndex = 0;
			choiceTable = gcnew System::Collections::ArrayList();
		}
		void add(System::String^ description, System::String^ choice, bool isDefault)
		{
			choiceTable->Add(gcnew ConfigStringChoice(description, choice));
			if (isDefault)
			{
				defaultIndex = (choiceTable->Count -1);
			}
		}
		int getDefaultIndex()
		{
			return defaultIndex;
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
		bool indexExists(int index)
		{
			return (choiceTable->Count > index);
		}
		int getChoiceCount()
		{
			return choiceTable->Count;
		}
		System::String^ getChoiceDescription(int _choiceIndex)
		{
			if (indexExists(_choiceIndex))
			{
				return static_cast<ConfigStringChoice^>(choiceTable->default[_choiceIndex])->description;
			}
			else
			{
				// WORK NEEDED: throw an exception
				return "";
			}
		}
	private:
		System::Collections::ArrayList^ choiceTable;
		int defaultIndex;
	};
};