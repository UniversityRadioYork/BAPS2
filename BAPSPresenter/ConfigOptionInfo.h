#pragma once
#include "ConfigOptions.h"

public ref class ConfigOptionInfo
{
public:
	ConfigOptionInfo(
		int _optionid,
		System::String^ _description,
		int _type)
		: optionid(_optionid), 
		description(_description),
		type((ConfigType)_type),
		indexed(false),
		tbControl(nullptr),
		lblControl(nullptr),
		dt(nullptr),
		complete(false),
		choicesToFill(0),
		receivedResult(false),
		result(false)
	{
		if (type == CONFIG_TYPE_CHOICE)
		{
			valid = false;
		}
		else
		{
			valid = true;
		}
	}
	ConfigOptionInfo(
		int _optionid,
		System::String^ _description,
		int _type,
		int _groupid)
		: optionid(_optionid), 
		description(_description), 
		type((ConfigType)_type), 
		indexed(true), 
		groupid(_groupid),
		tbControl(nullptr),
		lblControl(nullptr),
		dt(nullptr),
		complete(false),
		choicesToFill(0),
		receivedResult(false),
		result(false)
	{
		if (type == CONFIG_TYPE_CHOICE)
		{
			valid = false;
		}
		else
		{
			valid = true;
		}
	}
	inline bool isIndexed()
	{
		return indexed;
	}
	inline int getGroupid()
	{
		return groupid;
	}
	inline int getOptionid()
	{
		return optionid;
	}
	inline System::String^ getDescription()
	{
		return description;
	}
	inline ConfigType getType()
	{
		return type;
	}
		
	inline void setTextBoxControl(System::Windows::Forms::TextBox^ tb)
	{
		if (indexed)
		{
			throw gcnew System::Exception("An indexed option should not be assigned a textbox");
		}
		tbControl = tb;
	}
	inline void setLabelControl(System::Windows::Forms::Label^ lbl)
	{
		if (indexed)
		{
			throw gcnew System::Exception("An indexed option should not be assigned a label");
		}
		lblControl = lbl;
	}
	inline void setDataTable(System::Data::DataTable^ _dt)
	{
		if (!indexed)
		{
			throw gcnew System::Exception("A non indexed option should not be assigned a datatable");
		}
		dt = _dt;
	}
	inline void setComboBoxControl(System::Windows::Forms::ComboBox^ _cbControl)
	{
		if (type != CONFIG_TYPE_CHOICE)
		{
			throw gcnew System::Exception("A non choice option should not be assigned a combobox");
		}
		cbControl = _cbControl;
	}
	inline void setValue(int _value)
	{
		if (type == CONFIG_TYPE_CHOICE)
		{
			cbControl->SelectedIndex = _value;
			cbControl->Enabled = true;
		}
		else
		{
			tbControl->Text = _value.ToString();
			tbControl->Enabled = true;
		}
		complete = true;
	}
	inline void setValue(System::String^ _value)
	{
		tbControl->Text = _value;
		tbControl->Enabled = true;
		complete = true;
	}
	inline void setValue(int index, int _value)
	{
		getRow(index)[description] = _value;
		complete = true;
	}
	inline void setValue(int index, System::String^ _value)
	{
		getRow(index)[description] = _value;
		complete = true;
	}
	inline int getIndexCount()
	{
		return dt->Rows->Count;
	}
	inline int getValueInt()
	{
		if (type == CONFIG_TYPE_CHOICE)
		{
			return cbControl->SelectedIndex;
		}
		else
		{
			return System::Convert::ToInt32(tbControl->Text);
		}
	}
	inline int getValueInt(int index)
	{
		return safe_cast<int>(getRow(index)[description]);
	}
	inline System::String^ getValueStr()
	{
		return tbControl->Text;
	}
	inline System::String^ getValueStr(int index)
	{
		return static_cast<System::String^>(getRow(index)[description]);
	}
	System::Data::DataRow^ getRow(int index)
	{
		if (dt->Rows->Count > index)
		{
			return dt->Rows[index];
		}
		else if (dt->Rows->Count == index)
		{
			System::Data::DataRow^ dr = dt->NewRow();
			dr["index"] = index;
			dt->Rows->Add(dr);
			return dr;
		}
		else
		{
			throw gcnew System::Exception("indexed options must receive their data in order starting at index 0");
		}
	}
	System::Windows::Forms::TextBox^ getTextBoxControl()
	{
		return tbControl;
	}

	System::Windows::Forms::Label^ getLabelControl()
	{
		return lblControl;
	}
	System::Windows::Forms::ComboBox^ getComboBoxControl()
	{
		return cbControl;
	}
	void addChoice(int choiceid, System::String^ choice)
	{
		cbControl->Items->Add(choice);
		choicesToFill--;
		valid = (choicesToFill == 0);
		if (valid)
		{
			cbControl->Enabled = true;
		}
	}
	void setChoiceCount(int count)
	{
		choicesToFill = count;
	}
	bool isValid()
	{
		return valid;
	}
	bool isComplete()
	{
		return complete;
	}
	void setResult(bool _result)
	{
		receivedResult = true;
		result = _result;
	}
	void clearResult()
	{
		receivedResult = false;
	}
	bool hasReceivedResult()
	{
		return (indexed && getIndexCount() == 0) || receivedResult;
	}
	bool getResult()
	{
		return (indexed && getIndexCount() == 0) || (receivedResult && result);
	}
private:
	bool valid;
	bool complete;
	bool receivedResult;
	/** WORK NEEDED: this will be an enum type (success, option not exist, not allowed to set... etc)**/
	bool result;
	int choicesToFill;
	int optionid;
	System::String^ description;
	ConfigType type;
	bool indexed;
	int groupid;
	System::Windows::Forms::ComboBox^ cbControl;
	System::Windows::Forms::TextBox^ tbControl;
	System::Windows::Forms::Label^ lblControl;
	System::Data::DataTable^ dt;
};