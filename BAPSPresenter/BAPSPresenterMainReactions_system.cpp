#include "stdafx.h"
#include "BAPSPresenterMain.h"

using namespace BAPSPresenter;

void BAPSPresenterMain::addFileToDirectoryList(System::Object^ _directoryIndex, System::Object^ _fileIndex, System::String^ entry)
{
	int directoryIndex = safe_cast<int>(_directoryIndex);
	int fileIndex = safe_cast<int>(_fileIndex);
	if (directoryIndex < 3)
	{
		/** Add the new entry to the bottom of the listbox **/
		directoryList[directoryIndex]->Items->Add(entry);
	}
}

void BAPSPresenterMain::clearFiles(System::Object^ _directoryIndex)
{
	int directoryIndex = safe_cast<int>(_directoryIndex);
	if (directoryIndex < 3)
	{
		/** Empty the list box ready for new entries (required due to implicit indexing) **/
		directoryList[directoryIndex]->Items->Clear();
	}
}

void BAPSPresenterMain::displayVersion(System::String^ version, System::String^ date, System::String^ time, System::String^ author)
{
	if (about != nullptr)
	{
		MethodInvokerStrStrStrStr^ mi = gcnew MethodInvokerStrStrStrStr(about, &About::serverVersion);
		array<System::Object^>^ dd = gcnew array<System::Object^>(4) {version, date, time, author};
		about->Invoke(mi,dd);
	}
}
/*void BAPSPresenterMain::processFeedbackResult(int resultCode)
{
	if (feedbackDialog != nullptr)
	{
		MethodInvokerObj^ mi = gcnew MethodInvokerObj(feedbackDialog, &FeedbackDialog::receiveResult);
		array<System::Object^>^ dd = gcnew array<System::Object^>(1) {resultCode};
		feedbackDialog->Invoke(mi,dd);
	}
}*/

/*void BAPSPresenterMain::addToChatList(System::String^ username)
{
	if (!chatTo->Items->Contains(username))
	{
		chatTo->Items->Add(username);
		if (chatTo->Items->Count == 1)
		{
			chatTo->Items->Add("ALL");
			sendMessage->Enabled = true;
			chatTo->SelectedIndex = 0;
		}
	}
}
void BAPSPresenterMain::removeFromChatList(System::String^ username)
{
	if (chatTo->Items->Contains(username))
	{
		bool selectSomething = false;
		if (System::String::Compare(chatTo->SelectedItem->ToString(),username) == 0)
		{
			selectSomething = true;
		}
		chatTo->Items->Remove(username);
		if (chatTo->Items->Count > 1)
		{
			if ( selectSomething)
			{
				chatTo->SelectedIndex = 0;
			}
		}
		else
		{
			chatTo->Items->Remove("ALL");
			sendMessage->Enabled = false;
		}
	}
}
void BAPSPresenterMain::processChatMessage(System::String^ from, System::String^ to, System::String^ message)
{
	System::String^ prepend ="";
	if (chatText->Text->Length > 3000)
	{
		chatText->Text = chatText->Text->Remove(0,1500);
		prepend = "(cut)";
	}
	chatText->Text = System::String::Concat(prepend,chatText->Text, "\r\n", from, "->", to, ": ", message);
	chatText->SelectionStart = chatText->Text->Length;
	chatText->SelectionLength = 0;
	chatText->ScrollToCaret();
	if (!chatText->Visible)
	{
		chatOnOff->Highlighted = true;
	}
}*/