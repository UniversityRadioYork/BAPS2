#include "StdAfx.h"
#include "ConfigDialog.h"

#undef MessageBox
using namespace BAPSPresenter;

#include "Messages.h"

/** Config System control flow...
	construct form --> SEND: get all options
	receive option --> if choice type, SEND: get all choices for the option
	continue receiving options until... last option received
	create UI
	IF all the options are not yet complete (IE there are choice types...)
		receive choice
		continue receiving choices until the form data is complete
	SEND: request all settings
	receive setting --> enable control as setting is received
		WORK NEEDED: disable datagrid cells until data is set in them correctly
	continue receiving settings until all received
	enable save button
**/
/** work on security for settings, ie saving to one without write perm is not severe **/
/** test logic sequence slowly! + different option sets! **/
/** Only save settings that have had a value received **/
/** WORK NEEDED: crash on text in an integer field! **/
ref struct IndexControlsLookup
{
	System::Windows::Forms::DataGrid^ dg;
	System::Data::DataTable^ dt;
	IndexControlsLookup(System::Windows::Forms::DataGrid^ _dg,
						System::Data::DataTable^ _dt)
						: dg(_dg),
						  dt(_dt)
	{}
};

void ConfigDialog::setNumberOfOptions(int _numberOfOptions)
{
	/** Store the number of options and set flag to ackoledge the fact **/
	numberOfOptions = _numberOfOptions;
	optionCountSet = true;
	/** Inform user they can't edit any config **/
	if (numberOfOptions == 0)
	{
		System::Windows::Forms::MessageBox::Show("There are no options which you are able to configure", "Error:", System::Windows::Forms::MessageBoxButtons::OK);
		this->Close();
	}
}

void ConfigDialog::addOption(ConfigOptionInfo^ option)
{
	/** Decrement the number of options remaining so that we know when we can draw the form **/
	numberOfOptions--;
	/** Add the option to the hashtable **/
	options->Add(option->getOptionid(), option);
	/** If it is a choice type we must get the choices for it before requesting the settings **/
	if (option->getType() == CONFIG_TYPE_CHOICE)
	{
		Command cmd = BAPSNET_CONFIG | BAPSNET_GETOPTIONCHOICES;
		msgQueue->Enqueue(gcnew ActionMessageU32int(cmd, option->getOptionid()));
	}
}

void ConfigDialog::updateUI()
{
	/** Handles for holding controls while filling them in **/
	System::Windows::Forms::TextBox ^  tb;
	System::Windows::Forms::Label ^  lbl;
	System::Windows::Forms::ComboBox ^  cb;
	/** A handle for the current option which is having its UI generated **/
	ConfigOptionInfo^ option;
	/** We don't care about the association of optionid to optioninfo just the info **/
	System::Collections::ArrayList^ ops = gcnew System::Collections::ArrayList(options->Values);
	/** For some odd reason the array comes out backwards, WORK NEEDED: this is assumed internal
		workings of .NET framework
	**/
	ops->Reverse();
	/** The current index into the option array **/
	int i = 0;
	/** Horizontal offset from the fixed start coordinarte **/
	int xOffset = 0;
	/** Vertical offset from the fixed start coordinarte **/
	int yOffset = 16;
	/** The vertical multiplier (essentially how many control have been generated into the
		current column.
	**/
	int yMultiplier = 0;
	/** Are we generating the second column **/
	bool secondColumn = false;
	/** Lets save some time and wait until the end to draw all this! **/
	this->SuspendLayout();
	/** Increment the index and the multiplier each iteration (so that the multiplier
		can reset at start of column 2
	**/
	for (i = 0 ; i < ops->Count ; i++, yMultiplier++)
	{
		/** When half the controls have been generated move onto the second column
			WORK NEEDED: a better method of splitting controls into 2 columns, half
			the options != half space on screen due to indexed options.
		**/
		if (!secondColumn && i-1 >= ops->Count/2)
		{
			/** Set the form height to the height of the first column **/
			this->Height = (28+yOffset+(24*(yMultiplier)) + status->Height + 32);
			/** Place the statusBar correctly after resize **/
			status->Top = yOffset+(24*(yMultiplier))+32;
			/** Move the save and cancel buttons to a sensible place **/
			saveButton->Top = yOffset+(24*(yMultiplier))+4;
			cancelButton->Top = yOffset+(24*(yMultiplier))+4;
			/** New horizontal offset to represent column 2 **/
			xOffset = 328;
			/** Back to the top row **/
			yMultiplier = 0;
			/** We are now on the second column **/
			secondColumn = true;
			/** Set the offset to the same value as originally **/
			yOffset = 16;
		}
		/** Get the current option **/
		option = static_cast<ConfigOptionInfo^>(ops[i]);
		/** Indexed options must be treated differently, they are placed into datagrids **/
		if (option->isIndexed())
		{
			/** This needs to be done using a datagrid so that we can have indexable
				settings for it.
			**/
			/** If this is the first option for this set of indexed options (options based on
				the same maximum index value then there will be no datagrid already so we 
				make one.
			**/
			/** Create a handle for the datagrid and datatable **/
			System::Windows::Forms::DataGrid^ dg;
			System::Data::DataTable^ dt;
			if (indexControls[option->getGroupid()] == nullptr)
			{
				dg = gcnew System::Windows::Forms::DataGrid();
				/** Create a table style for the datagrid **/
				System::Windows::Forms::DataGridTableStyle^ dgts;
				dgts = gcnew System::Windows::Forms::DataGridTableStyle();
				/** Taken from the forms designer... assumed to be needed **/
				(safe_cast<System::ComponentModel::ISupportInitialize ^  >(dg))->BeginInit();
				dg->DataMember = "";
				dg->HeaderForeColor = System::Drawing::SystemColors::ControlText;
				/** Use the horizontal and vertical attributes to place the control correctly **/
				dg->Location = System::Drawing::Point(16+xOffset, yOffset+(24*yMultiplier));
				/** The control refers to the group of options and is so named **/
				dg->Name = System::String::Concat("groupOption", option->getGroupid().ToString());
				/** Control is 64 px high **/
				int height = 64;
				dg->Size = System::Drawing::Size(296, height);
				/** WORK NEEDED: why do we subtract 20 first! **/
				yOffset += (height-20);
				/** WORK NEEDED: tabindex counter **/
				dg->TabIndex = 2;
				dg->TableStyles->Add(dgts);
				/** Hide the description bit at the top, it serves no purpose **/
				dg->CaptionVisible = false;
				/** link the grid and the gridstyle **/
				dgts->DataGrid = dg;
				dgts->HeaderForeColor = System::Drawing::SystemColors::ControlText;
				dgts->MappingName = "";
				/** Add it to the form controls **/
				this->Controls->Add(dg);
				(safe_cast<System::ComponentModel::ISupportInitialize ^  >(dg))->EndInit();
				/** Finished basic datagrid initialization **/

				/** Create a datatable to hold all the info for this set of options **/
				dt = gcnew System::Data::DataTable();
				/** Add an index column so that visually we can see which index we are editing **/
				dt->Columns->Add("index", System::Type::GetType("System.Int32"));
				dt->Columns["index"]->ReadOnly = true;
				/** Add a column style so that the column created above can be seen **/
				System::Windows::Forms::DataGridTextBoxColumn^ tbc;
				tbc = gcnew System::Windows::Forms::DataGridTextBoxColumn();
				tbc->HeaderText = "";
				/** map it onto the index field **/
				tbc->MappingName = "index";
				/** It is only a 1 or 2 digit number **/
				tbc->Width = 20;
				/** Add the style onto the grid **/
				dg->TableStyles[0]->GridColumnStyles->Add(tbc);
				/** Make a dataview for the datatable so that we cant delete or create new rows
					rows are deleted or created by altering the value of the option controlling
					the number of indices 
				**/
				System::Data::DataView^ dv = gcnew System::Data::DataView(dt);
				dv->AllowNew = false;
				dv->AllowDelete = false;
				dg->SetDataBinding(dv, "");
				/** Add the datagrid and table to the hashtable so that future options in
					the same group can reuse them
				**/
				indexControls->Add(option->getGroupid(), gcnew IndexControlsLookup(dg, dt));
			}
			else
			{
				/** Get the datatable and the grid out of the cache and effectively remove an item
					from the column by backing up the vertical offset by 24 (the same value as
					the multiplier's multiplicand)
				**/
				IndexControlsLookup^ icl = static_cast<IndexControlsLookup^>(indexControls[option->getGroupid()]);
				dt = icl->dt;
				dg = icl->dg;
				yOffset -= 24;
			}
			/** Each option type has to be treated differently as it is stored differently in the datatable **/
			switch (option->getType())
			{
			case CONFIG_TYPE_STR:
				{
					/** Strings are stored as... strings **/
					dt->Columns->Add(option->getDescription(), System::Type::GetType("System.String"));
					/** In... textboxes **/
					System::Windows::Forms::DataGridTextBoxColumn^ tbc;
					tbc = gcnew System::Windows::Forms::DataGridTextBoxColumn();
					/** The description is used as the field name. WORK NEEDED: this could cause
						bugs, consider using the optionid
					**/
					tbc->HeaderText = option->getDescription();
					tbc->MappingName = option->getDescription();
					tbc->Width = 200;
					dg->TableStyles[0]->GridColumnStyles->Add(tbc);
				}
				break;
			case CONFIG_TYPE_INT:
				{
					/** Integers are stored as... integers **/
					dt->Columns->Add(option->getDescription(), System::Type::GetType("System.Int32"));
					/** In text boxes... WORK NEEDED: perhaps add a textchanged event to validate it being a number **/
					System::Windows::Forms::DataGridTextBoxColumn^ tbc;
					tbc = gcnew System::Windows::Forms::DataGridTextBoxColumn();
					/** Same rules as above **/
					tbc->HeaderText = option->getDescription();
					tbc->MappingName = option->getDescription();
					tbc->Width = 200;
					dg->TableStyles[0]->GridColumnStyles->Add(tbc);
				}
				break;
			case CONFIG_TYPE_CHOICE:
				{
					/** Choice types are stored as integers as well because we refer to the choice index not the value **/
					dt->Columns->Add(option->getDescription(), System::Type::GetType("System.Int32"));
					DataGridComboBoxColumn^ cbc;
					cbc = gcnew DataGridComboBoxColumn();
					cbc->HeaderText = option->getDescription();
					cbc->MappingName = option->getDescription();
					cbc->Width = 200;
					dg->TableStyles[0]->GridColumnStyles->Add(cbc);
					/** In order for the combo box to receive its values it has to be exposed
						DO NOT MESS WITH IT.. AT ALL
					**/
					option->setComboBoxControl(cbc->getComboBox());
				}
				break;
			}
			/** The option needs to know where its data is stored, it assumes it will have a valid
				handle to a datatable if it is an indexed option
			**/
			option->setDataTable(dt);
		}
		else
		{
			/** NON INDEXED options **/
			/** The non indexed options have labels to describe them **/
			lbl = gcnew System::Windows::Forms::Label();
			/** Place the label according to the horizontal and vertical rules **/
			lbl->Location = System::Drawing::Point(16+xOffset, yOffset+(24*yMultiplier));
			lbl->Name = System::String::Concat("optionLabel", option->getOptionid().ToString());
			lbl->Size = System::Drawing::Size(192, 20);
			lbl->TabStop = false;
			/** The label contains the option description **/
			lbl->Text = option->getDescription();
			/** For completeness the option is told what its label handle is **/
			option->setLabelControl(lbl);
			/** Add the label to the form **/
			this->Controls->Add(lbl);

			switch (option->getType())
			{
			case CONFIG_TYPE_STR:
			case CONFIG_TYPE_INT:
				{
					/** String and integer options can be treated the same (For now)
						WORK NEEDED: validate entries to integer text boxes to ensure they are integers
					**/
					tb = gcnew System::Windows::Forms::TextBox();
					/** Place the textbox according to the horizontal and vertical rules **/
					tb->Location = System::Drawing::Point(216+xOffset, yOffset+(24*yMultiplier));
					tb->Name = System::String::Concat("optionBox", option->getOptionid().ToString());
					tb->Size = System::Drawing::Size(96, 20);
					/** WORK NEEDED: tab indices **/
					tb->TabIndex = option->getOptionid();
					/** Start with the control disabled and with set-me as its text to show it
						has not received a value from the server (useful ofr debugging only)
					**/
					tb->Text = "[set-me]";
					/** The control knows what option it refers to... unused for now maybe **/
					tb->Tag = option;
					/** Inform the option what control it is hosted in **/
					option->setTextBoxControl(tb);
					tb->Enabled = false;
					/** Show the control on the form **/
					this->Controls->Add(tb);
				}
				break;
			case CONFIG_TYPE_CHOICE:
				{
					cb = gcnew System::Windows::Forms::ComboBox();
					/** Place the textbox according to the horizontal and vertical rules **/
					cb->Location = System::Drawing::Point(216+xOffset, yOffset+(24*yMultiplier));
					cb->Name = System::String::Concat("optionBox", option->getOptionid().ToString());
					cb->Size = System::Drawing::Size(96, 20);
					/** WORK NEEDED: tab indices **/
					cb->TabIndex = option->getOptionid();
					/** The control knows what option it refers to... unused for now maybe **/
					cb->Tag = option;
					/** Make it uneditable **/
					cb->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					/** Inform the option what control it is hosted in **/
					option->setComboBoxControl(cb);
					/** Disable the control to start with (so it cannot be set until the server
						has sent its current value
					**/
					cb->Enabled = false;
					/** Show the control on the form **/
					this->Controls->Add(cb);
				}
				break;
			}
		}
	}
	/** Get the required height for column 2 (same equation as used after end of column 1) **/
	int minHeight = (28+yOffset+(24*(yMultiplier+1)) + status->Height+32);
	/** If the height of the form is less that what is needed resize as above **/
	if (this->Height < minHeight)
	{
		this->Height = minHeight;
		status->Top = yOffset+(24*(yMultiplier+1)+32);
		saveButton->Top = yOffset+(24*(yMultiplier))+4;
		cancelButton->Top = yOffset+(24*(yMultiplier))+4;
	}
	/** Show all the controls that have just been made **/
	this->ResumeLayout(false);
	this->PerformLayout();
	/** Attempt to receive all the settings (will not happen if there are outstanding choices
		for some of the CHOICE type options still to receive)
	**/
	receiveSettingsIfReady();
}

System::Void ConfigDialog::saveButton_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	saveButton->Enabled = false;
	System::Collections::ArrayList^ ops = gcnew System::Collections::ArrayList(options->Values);
	Command cmd;
	int i = 0;
	ConfigOptionInfo^ coi;
	for ( i = 0 ; i < options->Count ; i++ )
	{
		coi = static_cast<ConfigOptionInfo^>(ops[i]);
		if (coi->isIndexed())
		{
			int j = 0;
			for (j = 0 ; j < coi->getIndexCount() ; j++)
			{
				cmd = BAPSNET_CONFIG | BAPSNET_SETCONFIGVALUE | BAPSNET_CONFIG_USEVALUEMASK | j;
				switch (coi->getType())
				{
				case CONFIG_TYPE_STR:
					{
						msgQueue->Enqueue(gcnew ActionMessageU32intU32intString(cmd, coi->getOptionid(), coi->getType(), coi->getValueStr(j)));
					}
					break;
				case CONFIG_TYPE_INT:
				case CONFIG_TYPE_CHOICE:
					{
						msgQueue->Enqueue(gcnew ActionMessageU32intU32intU32int(cmd, coi->getOptionid(), coi->getType(), coi->getValueInt(j)));
					}
					break;
				default:
					break;
				}
			}
		}
		else
		{
			cmd = BAPSNET_CONFIG | BAPSNET_SETCONFIGVALUE;
			switch (coi->getType())
			{
			case CONFIG_TYPE_STR:
				{
					msgQueue->Enqueue(gcnew ActionMessageU32intU32intString(cmd, coi->getOptionid(), coi->getType(), coi->getValueStr()));
				}
				break;
			case CONFIG_TYPE_INT:
			case CONFIG_TYPE_CHOICE:
				{
					msgQueue->Enqueue(gcnew ActionMessageU32intU32intU32int(cmd, coi->getOptionid(), coi->getType(), coi->getValueInt()));
				}
				break;
			default:
				break;
			}
		}
	}
}

void ConfigDialog::setResult(System::Object^ optionid, System::Object^ result)
{
	// WORK NEEDED: fix this
	ConfigResult res = (ConfigResult)(safe_cast<int>(result));
	static_cast<ConfigOptionInfo^>(options[optionid])->setResult( res == CONFIG_RESULT_SUCCESS);
	if (res != CONFIG_RESULT_SUCCESS)
	{
		statusLabel->Text = System::String::Concat("Failed to set: ", static_cast<ConfigOptionInfo^>(options[optionid])->getDescription(), ". Error: ", ConfigResultText::text[res]);
	}
	System::Collections::ArrayList^ ops = gcnew System::Collections::ArrayList(options->Values);
	int i = 0;
	bool allReceived = true;
	bool allSucceeded = true;
	for ( i = 0 ; i < options->Count && allReceived && allSucceeded ; i++ )
	{
		if (!static_cast<ConfigOptionInfo^>(ops[i])->hasReceivedResult())
		{
			allReceived = false;
		}
		else if (!static_cast<ConfigOptionInfo^>(ops[i])->getResult())
		{
			allSucceeded = false;
		}
	}
	if ( allReceived&&allSucceeded)
	{
		this->Close();
	}
	else if (allReceived)
	{
		saveButton->Enabled = true;
	}
}
void ConfigDialog::setValue(System::Object^ id, System::String^ str)
{
	static_cast<ConfigOptionInfo^>(options[id])->setValue(str);
	enableSaveButtonIfReady();
}
void ConfigDialog::setValue(System::Object^ id, System::Object^ value)
{
	static_cast<ConfigOptionInfo^>(options[id])->setValue(safe_cast<int>(value));
	enableSaveButtonIfReady();
}
void ConfigDialog::setValue(System::Object^ id,System::Object^ index, System::String^ str)
{
	static_cast<ConfigOptionInfo^>(options[id])->setValue(safe_cast<int>(index), str);
	enableSaveButtonIfReady();
}
void ConfigDialog::setValue(System::Object^ id,System::Object^ index, System::Object^ value)
{
	static_cast<ConfigOptionInfo^>(options[id])->setValue(safe_cast<int>(index),safe_cast<int>(value));
	enableSaveButtonIfReady();
}
void ConfigDialog::addChoice(System::Object^ optionid, System::Object^ choiceid, System::String^ description)
{
	static_cast<ConfigOptionInfo^>(options[optionid])->addChoice(safe_cast<int>(choiceid), description);
	receiveSettingsIfReady();
}
void ConfigDialog::setChoiceCount(System::Object^ optionid, System::Object^ count)
{
	static_cast<ConfigOptionInfo^>(options[optionid])->setChoiceCount(safe_cast<int>(count));
}
void ConfigDialog::receiveSettingsIfReady()
{
	if (!(optionCountSet && (numberOfOptions == 0)))
	{
		return;
	}
	System::Collections::ArrayList^ ops = gcnew System::Collections::ArrayList(options->Values);
	int i = 0;
	for ( i = 0 ; i < options->Count ; i++ )
	{
		if (!static_cast<ConfigOptionInfo^>(ops[i])->isValid())
		{
			return;
		}
	}
	Command cmd = BAPSNET_CONFIG | BAPSNET_GETCONFIGSETTINGS;
	msgQueue->Enqueue(gcnew ActionMessage(cmd));
	optionCountSet = false;
}

void ConfigDialog::enableSaveButtonIfReady()
{
	System::Collections::ArrayList^ ops = gcnew System::Collections::ArrayList(options->Values);
	int i = 0;
	for ( i = 0 ; i < options->Count ; i++ )
	{
		if (!static_cast<ConfigOptionInfo^>(ops[i])->isComplete())
		{
			return;
		}
	}
	saveButton->Enabled = true;
}