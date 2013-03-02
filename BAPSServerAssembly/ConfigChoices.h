#pragma once

namespace BAPSServerAssembly
{
	ref struct ConfigChoice
	{
		ConfigChoice(System::String^ _description)
			: description(_description)
		{}
		System::String^ description;
	};

	ref class ConfigChoices
	{
	public:
		ConfigChoices()
		{
			defaultIndex = 0;
			choiceTable = gcnew System::Collections::ArrayList();
		}
		int getDefaultIndex()
		{
			return defaultIndex;
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
				return static_cast<ConfigChoice^>(choiceTable->default[_choiceIndex])->description;
			}
			else
			{
				// WORK NEEDED: throw an exception
				return "";
			}
		}
	protected:
		System::Collections::ArrayList^ choiceTable;
		int defaultIndex;
	};
};