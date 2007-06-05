#include "StdAfx.h"
#include "LoadShowDialog.h"
#include "Messages.h"
#include "ConfigCache.h"

using namespace BAPSPresenter;

/** Each radio button in the matrix needs to know what it refers to **/
ref struct MatrixLookup
{
	int listingid;
	int channel;
};
/** The List box used for selecting which show to load needs both the id and
	textual description
**/
ref struct Name2Id
{
	Name2Id(int _id, System::String ^ _name)
		: id(_id), name(_name)
	{}
	System::String^ name;
	int id;
	/** Provided to ensure the correct text is displayed in the listbox **/
	virtual System::String^ ToString() override
	{
		return name;
	}
};

System::Void LoadShowDialog::check_Changed(System::Object ^  sender, System::EventArgs ^  e)
{
	/** If we select the other user radio button we activate the text field as well **/
	otherUser->Enabled = (sender == otherUserRadio);
	/** Store the selection **/
	showListType = safe_cast<int>(static_cast<System::Windows::Forms::RadioButton ^>(sender)->Tag);
}
System::Void LoadShowDialog::listBox_SelectedIndexChanged(System::Object ^  sender, System::EventArgs ^  e)
{
	/** When we select an option in the list box we allow the go button to be used **/
	goButton->Enabled = true;
}
System::Void LoadShowDialog::goButton_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	/** The go button controls what is displayed on the form, turning controls on
		and off, it uses the state information to work out what to do next
	**/
	/** If something goes wrong there is a small red text box at the top to explain
		to the user
	**/
	errorLabel->Text = "";
	switch (stage)
	{
	case 0:
		{
			/** User has chosen which user shows should be retrieved for **/
			if (showListType == 2 && otherUser->Text->Length == 0)
			{
				/** If the 'other' radio button has been selected for user
					there must be a username present aswell.
				**/
				errorLabel->Text = "You must enter a username.";
			}
			else
			{
				/** Always wise when altering lots **/
				this->SuspendLayout();

				/** Disable aspects of stage 0 ui **/
				todaysShowsRadio->Visible = false;
				systemUserRadio->Visible = false;
				otherUserRadio->Visible = false;
				otherUser->Visible = false;
				newShowsOnly->Visible = false;
				/** Set the show count to -1 so it is different from 0 meaning
					non shows found.
				**/
				showResultCount = -1;

				/** Enable the stage 2 ui **/
				listBox->Visible = true;
				listBox->Enabled = false;
				goButton->Enabled = false;
				/** Wipe the listbox in case we are doing this after going 'back' **/
				listBox->clearList();
				/** Set the description to the new text **/
				dialogTitle->Text = "Select a show:";
				/** Done fiddling **/
				this->ResumeLayout(false);
				this->PerformLayout();
				/** We are now ready for the show results **/
				stage = 1;
				/** Request the show results **/
				Command cmd = BAPSNET_DATABASE | BAPSNET_GETSHOWS;
				if (newShowsOnly->Checked)
				{
					/** WORK NEEDED: undocumented flag... means only search for
						shows starting from now onwards
					**/
					cmd |= 0x4;
				}
				cmd |= showListType;
				if (showListType != 2)
				{
                    msgQueue->Enqueue(gcnew ActionMessage(cmd));
				}
				else
				{
					/** Append the username if it is the 'other' user selection **/
                    msgQueue->Enqueue(gcnew ActionMessageString(cmd, otherUser->Text));
				}
			}
		}
		break;
	case 1:
		{
			/** The Go button can only be clicked if we have received all the
				shows OR we have been told there are none. In the latter case the
				listBox remains disabled.
			**/
			if (listBox->Enabled)
			{
				/** Find out what the selection is **/
				Name2Id^ selectedId = static_cast<Name2Id^>(listBox->getItem(listBox->SelectedIndex));
				/** The Channel Count will be already in the cache as it is a non restricted config option
				**/
				Command cmd = BAPSNET_DATABASE | BAPSNET_GETLISTINGS;
				msgQueue->Enqueue(gcnew ActionMessageU32int(cmd, selectedId->id));
				/** Disable the stage 1 ui **/
				listBox->clearList();
				listBox->Enabled = false;
				listBox->Visible = false;
				goButton->Enabled = false;
				/** Set the new title **/
				dialogTitle->Text = "Select channels:";
				/** Move to stage 2 **/
				stage = 2;
			}
			else
			{
				/** This is a back button now **/
				/** Clear the stage 1 ui **/
				listBox->clearList();
				listBox->Visible = false;
				/** enable the stage 1 ui **/
				todaysShowsRadio->Visible = true;
				systemUserRadio->Visible = true;
				otherUserRadio->Visible = true;
				otherUser->Visible = true;
				newShowsOnly->Visible = true;
				/** Reset the Go button text and the title  **/
				goButton->Text = "Go";
				dialogTitle->Text = "Get list of shows for:";
				/** Go back to stage 0 **/
				stage = 0;
			}
		}
		break;
	case 2:
		{
			/** Get the values from the listings **/
			System::Collections::ArrayList^ listingPanels = gcnew System::Collections::ArrayList(listings->Values);
			int i;
			for (i = 0 ; i < listingPanels->Count ; i++)
			{
				/** Search through each panel for a selected option **/
				System::Windows::Forms::Panel^ panel = static_cast<System::Windows::Forms::Panel^>(listingPanels[i]);
				int j;
				for (j = 0 ; j < totalChannels ; j++)
				{
					System::Windows::Forms::RadioButton^ radioButton;
					radioButton = static_cast<System::Windows::Forms::RadioButton^>(panel->Controls[j]);
					if (radioButton->Checked)
					{
						/** If we find a selected option get the value out of its tag **/
						MatrixLookup^ matrixLookup = static_cast<MatrixLookup^>(radioButton->Tag);

						System::Windows::Forms::CheckBox^ cb = static_cast<System::Windows::Forms::CheckBox^>(panel->Controls[totalChannels+1]);
						if (cb->Checked)
						{
							Command cmd = BAPSNET_PLAYLIST | BAPSNET_RESETPLAYLIST | matrixLookup->channel;
							msgQueue->Enqueue(gcnew ActionMessage(cmd));
						}
						/** update the server **/
						Command cmd = BAPSNET_DATABASE | BAPSNET_ASSIGNLISTING | matrixLookup->channel;
						msgQueue->Enqueue(gcnew ActionMessageU32int(cmd, matrixLookup->listingid));
					}
				}
			}
			/** Done **/
			this->Close();
		}
		break;
	}
}

void LoadShowDialog::notifyError(System::Object^ _errorCode, System::String^ message)
{
	/** If something goes from this should explain it **/
	errorLabel->Text = message;
}
void LoadShowDialog::setShowResultCount(System::Object^ count)
{
	/** On receiving a new result count we empty the listbox ( it should already be empty ) **/
	listBox->clearList();
	/** Make sure the box is disabled **/
	listBox->Enabled = false;
	/** Set the count **/
	showResultCount = safe_cast<int>(count);
	if (showResultCount == 0)
	{
		/** If it is 0 then there are no shows and we enable a back button, 
			to choose another user etc
		**/
		listBox->addItem("No shows available");
		goButton->Text = "Back";
		goButton->Enabled = true;
	}
}
void LoadShowDialog::addShow(System::Object^ id, System::String^ description)
{
	listBox->addItem(gcnew Name2Id(safe_cast<int>(id), description));
	if (listBox->itemCount() == showResultCount)
	{
		/** When the listbox is full enable it **/
		listBox->Enabled = true;
	}
}
void LoadShowDialog::setListingResultCount(System::Object^ count)
{
	listingResultCount = safe_cast<int>(count);
	/** A countdown to help the matrix generate itself **/
	listingResultCountLeft = listingResultCount;
	if (listingResultCount == 0)
	{
		errorLabel->Text = "No listings available";
	}
}
void LoadShowDialog::addListing(System::Object^ _listingid, System::Object^ _channel, System::String^ description)
{
	/** Generate the matrix as we go **/
	/** Un-manage the arguments **/
	int listingid = safe_cast<int>(_listingid);
	int channel = safe_cast<int>(_channel);
	/** The channel count must be valid now due to strong ordering of command-response**/
	totalChannels = ConfigCache::getValueInt("Number of Channels");

	/** Each listing gets its own panel so that it can have a selection of
		radio buttons acting independantly of the others on the form
	**/
	System::Windows::Forms::Panel ^  panel;
	/** Placeholder for a radio button **/
	System::Windows::Forms::RadioButton ^  radioButton;
	/** Create the panel **/
 	panel = gcnew System::Windows::Forms::Panel();

	/** Careful with the ordering here, suspend the panel then the form **/
	panel->SuspendLayout();
	this->SuspendLayout();

	/** As we receive more listings we go further down the form... **/
	panel->Location = System::Drawing::Point(0, 64+((listingResultCount-listingResultCountLeft)*24));
	/** One less result **/
	listingResultCountLeft--;
	/** Set up standard control info **/
	panel->Name = System::String::Concat("panel", listingid.ToString());
	panel->Size = System::Drawing::Size(this->Width, 16);
	/** Try to get tabs correct **/
	panel->TabIndex = 0+listingResultCount-listingResultCountLeft;
	panel->BackColor = System::Drawing::Color::Transparent;
	int i;
	/** Flag to see if the listing has managed to get its default channel or not
		if it doesnt it gets assigned to the none channel
	**/
	bool hasBeenChecked = false;
	/** Loop for channels+1 to include the none channel **/
	for (i = 0 ; i < totalChannels+1 ; i++)
	{
		if (listingResultCountLeft == 0)
		{
			/** When we get to the last listing we add the channel labels **/
			System::Windows::Forms::Label^ label = gcnew System::Windows::Forms::Label();
			label->Location = System::Drawing::Point(132+(i*24), 48);
			label->Name = System::String::Concat("ChannelLabel", i.ToString());
			label->Size = System::Drawing::Size(16, 16);
			label->TabStop = false;
			label->BackColor = System::Drawing::Color::Transparent;
			if (i < totalChannels)
			{
				/** just a channel number for the read channels **/
				label->Text = (i+1).ToString();
			}
			else
			{
				label->Size = System::Drawing::Size(16, 16);
				/** The last one is none e.g. not assigned **/
				label->Text = "-";
			}
			/** add it onto the form **/
			this->Controls->Add(label);
		}
		/**	Make the button and the tag for this listing/channel combination **/ 
		radioButton = gcnew System::Windows::Forms::RadioButton();
		MatrixLookup^ matrixLookup = gcnew MatrixLookup();
		matrixLookup->channel = i;
		matrixLookup->listingid = listingid;
		radioButton->Tag = matrixLookup;
		/** Set the standard control info **/
		radioButton->Location = System::Drawing::Point(132+(i*24), 0);
		radioButton->Name = System::String::Concat(listingid.ToString(), "radioButton", i.ToString());
		radioButton->Size = System::Drawing::Size(16, 16);
		radioButton->TabIndex = i;
		/** No label gets cluttered up **/
		radioButton->Text = "";
		/** When changing the selection we do some sanity checks like no 2 listings on the same channel **/
		radioButton->CheckedChanged += gcnew System::EventHandler(this, &LoadShowDialog::matrix_Changed);
		radioButton->BackColor = System::Drawing::Color::Transparent;
		radioButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		/** If this listing is supposed to be on this channel || it hasnt found anywhere yet and it is the 'none' option **/
		if (i == channel || (i == totalChannels && !hasBeenChecked))
		{
			/** Check this radio button, if two listing have been selected by the user to be on the
				same channel the latter will get precedence as the checked changed handler will be
				validating all the check operations
			**/
			radioButton->Checked = true;
			/** Dont check again **/
			hasBeenChecked = true;
		}
		else
		{
			/** Just to make sure **/
			radioButton->Checked = false;
		}
		/** Add the button onto the PANEL **/
		panel->Controls->Add(radioButton);
	}
	if (listingResultCountLeft == 0)
	{
		/** When we get to the last listing we add the channel labels **/
		System::Windows::Forms::Label^ label = gcnew System::Windows::Forms::Label();
		label->Location = System::Drawing::Point(125+((totalChannels+1)*24), 48);
		label->Size = System::Drawing::Size(100, 16);
		label->TabStop = false;
		label->BackColor = System::Drawing::Color::Transparent;
		label->Text = "Clear on load";
		this->Controls->Add(label);
	}
	System::Windows::Forms::CheckBox^ checkbox = gcnew System::Windows::Forms::CheckBox();
	checkbox->BackColor = System::Drawing::Color::Transparent;
	checkbox->Location = System::Drawing::Point(155+((totalChannels+1)*24), 0);
	checkbox->Text = "";
	checkbox->Size = System::Drawing::Size(16, 16);
	checkbox->Checked = true;
	panel->Controls->Add(checkbox);

	/** Add the listing description **/
	System::Windows::Forms::Label^ label = gcnew System::Windows::Forms::Label();
	label->Location = System::Drawing::Point(16, 0);
	label->Name = System::String::Concat("DescriptionLabel", listingid.ToString());
	label->Size = System::Drawing::Size(100, 16);
	label->TabStop = false;
	label->Text = description;
	/** Put it in the panel also **/
	panel->Controls->Add(label);
	/** Add the panel to the matrix so the check changed event handler can find out what is checked where **/
	listings->Add(listingid, panel);
	/** Add the panel onto the form **/
	this->Controls->Add(panel);
	/** When at the end enable the go button **/
	if (listingResultCountLeft == 0)
	{
		goButton->Enabled = true;
	}
	/** Resume layout in this order (panel, form ) **/
	panel->ResumeLayout(false);
	this->ResumeLayout(false);
	this->PerformLayout();
}
System::Void LoadShowDialog::cancelButton_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	/** If we cancel we cancel, any data will be discarded that was destined for this class **/
	this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
	this->Close();
}
System::Void LoadShowDialog::matrix_Changed(System::Object ^  sender, System::EventArgs ^  e)
{
	/** Grab the tag info for the sender control **/
	MatrixLookup^ matrixLookup = static_cast<MatrixLookup^>(static_cast<System::Windows::Forms::RadioButton^>(sender)->Tag);
	/** ignore when we 'check' the unassigned channel and also the events referring to the user 
		'unchecking' boxes
	**/
	if (matrixLookup->channel != totalChannels && static_cast<System::Windows::Forms::RadioButton^>(sender)->Checked)
	{
		/** Must flip any other listing to none if it is selecting this channel **/
		/** Grab all the listing panels **/
		System::Collections::ArrayList^ keys = gcnew System::Collections::ArrayList(listings->Keys);
		int i;
		for (i = 0 ; i < keys->Count ; i++)
		{
			/** Ignore the panel that we are on (hashtable keys are listingids)**/
			if (safe_cast<int>(keys[i]) != matrixLookup->listingid)
			{
				System::Windows::Forms::Panel^ panel;
				/** Get the panel **/
				panel = static_cast<System::Windows::Forms::Panel^>(listings[keys[i]]);
				/** WORK NEEDED: We ASSUME the controls will remain in the same order as we added them 
					to the panel... Therefore item 0 is for channel 0 etc etc
				**/
				if (static_cast<System::Windows::Forms::RadioButton^>(panel->Controls[matrixLookup->channel])->Checked)
				{
					/** Set the checked item to be 'none' **/
					static_cast<System::Windows::Forms::RadioButton^>(panel->Controls[totalChannels])->Checked =true;
				}
			}
		}
	}
}


System::Void LoadShowDialog::otherUser_Enter(System::Object^  sender, System::EventArgs^  e)
{
	if (otherUser->Tag == nullptr)
	{
		otherUser->Text = "";
		otherUser->Tag = safe_cast<System::Object^>(0);
	}
}

System::Void LoadShowDialog::LoadShowDialog_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	MethodInvokerObjKeyEventArgs^ mi = gcnew MethodInvokerObjKeyEventArgs(bapsPresenterMain, &BAPSPresenterMain::BAPSPresenterMain_KeyDown);
	array<System::Object^>^ dd = gcnew array<System::Object^>(2) {bapsPresenterMain, e};
	this->Invoke(mi, dd);
}