#include "StdAfx.h"
#include "RecordLibrarySearch.h"
#include "Messages.h"

using namespace BAPSPresenter;

System::Void RecordLibrarySearch::AddToChannel_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	/** Ignore the add if nothing was selected **/
	if (ResultsBox->SelectedIndex != -1)
	{
		/** update the server **/
		Command cmd = BAPSNET_PLAYLIST | BAPSNET_ADDITEM;
		cmd |= (safe_cast<int>(dynamic_cast<BAPSButton^>(sender)->Tag) & 0x3f);
		msgQueue->Enqueue(gcnew ActionMessageU32intU32int(cmd, (u32int)BAPSNET_LIBRARYITEM, ResultsBox->SelectedIndex));
	}
}

System::Void RecordLibrarySearch::closeButton_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->Close();
}

System::Void RecordLibrarySearch::SearchButton_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	/** Starting a new search means getting rid of the old one **/
	ResultsBox->clearList();
	ResultsBox->Enabled = true;
	connectionStatus->Text = "Connected";
	/** Set the artist to a wildcard **/
	System::String^ _artist = "%";
	/** If a tag is set it contains useful info **/
	if (Artist->Tag != nullptr)
	{
		_artist = Artist->Text;
	}
	/** Set the title to a wildcard **/
	System::String^ _title = "%";
	/** If a tag is set it contains useful info **/
	if (Title->Tag != nullptr)
	{
		_title = Title->Text;
	}
	/** If neither box has anything in it is rejected otherwise the entire DB is returned **/
	/** WORK NEEDED: server or client side rejection of % % for artist and title **/
	if (Artist->Tag == nullptr && Title->Tag == nullptr && !dateAddedRadioButton->Checked && !dateReleasedRadioButton->Checked)
	{
		resultsInfo->Text = "Empty Artist/Title";
		ResultsBox->addItem("Empty Artist/Title");
		ResultsBox->Enabled = false;
	}
	else
	{
		/** Say that it is searching **/
		resultsInfo->Text = "Searching... ";
		/** disable the ui so the server doesnt do too much  **/
		SearchButton->Enabled=false;
		AddToChannel0->Enabled = false;
		AddToChannel1->Enabled = false;
		AddToChannel2->Enabled = false;
		ResultsBox->Enabled = false;
		numberOfResults = 0;
		/** Submit the request **/
		u32int orderby = BAPSNET_ORDER_BYARTIST;
		if (artistRadioButton->Checked)
		{
			orderby = BAPSNET_ORDER_BYARTIST;
		}
		else if (titleRadioButton->Checked)
		{
			orderby = BAPSNET_ORDER_BYTITLE;
		}
		else if (dateAddedRadioButton->Checked)
		{
			orderby = BAPSNET_ORDER_BYDATEADDED;
		}
		else if (dateReleasedRadioButton->Checked)
		{
			orderby = BAPSNET_ORDER_BYDATERELEASED;
		}
		u32int ascdes = BAPSNET_ORDER_ASCENDING;
		if (reverseOrderCheckBox->Checked)
		{
			ascdes = BAPSNET_ORDER_DESCENDING;
		}
		Command cmd = BAPSNET_DATABASE | BAPSNET_LIBRARYORDERING;
		msgQueue->Enqueue(gcnew ActionMessageU32intU32int(cmd, orderby, ascdes));

		cmd = BAPSNET_DATABASE | BAPSNET_LIBRARYSEARCH;
		msgQueue->Enqueue(gcnew ActionMessageStringStringU32int(cmd, _artist, _title, pageNum));
	}
}

System::Void RecordLibrarySearch::Text_Enter(System::Object ^  sender, System::EventArgs ^  e)
{
	/** If the textbox has no tag then we reset its value to nothing as it contains our help text **/
	if (dynamic_cast<System::Windows::Forms::TextBox^>(sender)->Tag == nullptr)
	{
		dynamic_cast<System::Windows::Forms::TextBox^>(sender)->Text = "";
	}
	/** Add a tag to say this box contains text**/
	dynamic_cast<System::Windows::Forms::TextBox^>(sender)->Tag = safe_cast<System::Object^>(0);
}
System::Void RecordLibrarySearch::Artist_Leave(System::Object ^  sender, System::EventArgs ^  e)
{
	/** If the textbox is empty upon leaving **/
	if (System::String::Compare(dynamic_cast<System::Windows::Forms::TextBox^>(sender)->Text, "") == 0)
	{
		/** Set the text back to the info **/
		dynamic_cast<System::Windows::Forms::TextBox^>(sender)->Text = "<Enter the Artist to search for>";
		/** remove the tag so that we know it is really empty **/
		dynamic_cast<System::Windows::Forms::TextBox^>(sender)->Tag = nullptr;
	}
}
System::Void RecordLibrarySearch::Title_Leave(System::Object ^  sender, System::EventArgs ^  e)
{
	/** If the textbox is empty upon leaving **/
	if (System::String::Compare(dynamic_cast<System::Windows::Forms::TextBox^>(sender)->Text, "") == 0)
	{
		/** Set the text back to the info **/
		dynamic_cast<System::Windows::Forms::TextBox^>(sender)->Text = "<Enter the Title to search for>";
		/** remove the tag so that we know it is really empty **/
		dynamic_cast<System::Windows::Forms::TextBox^>(sender)->Tag = nullptr;
	}
}
void RecordLibrarySearch::setResultCount(System::Object^ _count)
{
	/** Create an array big enough to hold the results **/
	int count = safe_cast<int>(_count);
	if (count == 0)
	{
		SearchButton->Enabled = true;
		resultsInfo->Text = "No Results";
	}
	else
	{
		/** Set the progress bar maximum so as to track the progress accurately **/
		progressBar->Maximum = count;
		numberOfResults = count;
	}

}
void RecordLibrarySearch::add(System::Object^ _index, System::String^ description)
{
	int index = safe_cast<int>(_index);
	/** Move the progress bar on **/
	progressBar->Value = index;
	/** Place the string into the array **/
	ResultsBox->addItem(description);
	/** The index is 0 based so the last item is numberofresults-1 **/
	if (numberOfResults == index+1)
	{
		switch (numberOfResults)
		{
		case 1:
			/** Get the grammar correct **/
			resultsInfo->Text = "1 result";
			break;
		default:
			/** Report how many results were found **/
			resultsInfo->Text = System::String::Concat(numberOfResults.ToString(), " results");
			break;
		}
		/** Reset the progress bar **/
		progressBar->Value = 0;
		progressBar->Maximum = 0;
		/** Enable all the buttons again **/
		SearchButton->Enabled = true;
		pageNum++;
		SearchButton->Text = "Search Again";
	SearchButton->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0));
		AddToChannel0->Enabled = true;
		AddToChannel1->Enabled = true;
		AddToChannel2->Enabled = true;
		ResultsBox->Enabled = true;
	}
}
void RecordLibrarySearch::handleError(System::Object^ _errorcode, System::String^ description)
{
	/** Report the error message to the client **/
	int errorcode = safe_cast<int>(_errorcode);
	connectionStatus->Text = description;
	if (errorcode == 4)
	{
		SearchButton->Enabled = true;
		resultsInfo->Text = "Try Again";
	}
	else
	{
		resultsInfo->Text = "Server Error";
	}
}

System::Void RecordLibrarySearch::RecordLibrarySearch_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	MethodInvokerObjKeyEventArgs^ mi = gcnew MethodInvokerObjKeyEventArgs(bapsPresenterMain, &BAPSPresenterMain::BAPSPresenterMain_KeyDown);
	array<System::Object^>^ dd = gcnew array<System::Object^>(2) {bapsPresenterMain, e};
	this->Invoke(mi, dd);
}
System::Void RecordLibrarySearch::Some_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	pageNum = 0;

	SearchButton->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0));
	SearchButton->Text = "Search";
}

System::Void RecordLibrarySearch::RadioButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	Some_TextChanged(sender, e);

	if (sender == dateAddedRadioButton || sender == dateReleasedRadioButton)
	{
		reverseOrderCheckBox->Checked = true;
	}
	else
	{
		reverseOrderCheckBox->Checked = false;
	}
}