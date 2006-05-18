#pragma once

ref struct ConfigIntChoice
{
	ConfigIntChoice(System::String^ _description, int _choice)
		: description(_description), choice(_choice)
	{}
	System::String^ description;
	int choice;
};

ref class ConfigIntChoices
{
public:
	ConfigIntChoices()
	{
		defaultIndex = 0;
		choiceTable = gcnew System::Collections::ArrayList();
	}
	void add(System::String^ description, int choice, bool isDefault)
	{
		choiceTable->Add(gcnew ConfigIntChoice(description, choice));
		if (isDefault)
		{
			defaultIndex = (choiceTable->Count -1);
		}
	}
	int getDefaultIndex()
	{
		return defaultIndex;
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
	bool indexExists(int index)
	{
		return (choiceTable->Count > index) && (index >= 0);
	}
	int getChoiceCount()
	{
		return choiceTable->Count;
	}
	System::String^ getChoiceDescription(int _choiceIndex)
	{
		if (indexExists(_choiceIndex))
		{
			return static_cast<ConfigIntChoice^>(choiceTable->default[_choiceIndex])->description;
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