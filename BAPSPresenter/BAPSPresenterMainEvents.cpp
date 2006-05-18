#include "StdAfx.h"
#include "BAPSPresenterMain.h"
#include "Messages.h"
#include "HelpDialog.h"
#include "AudioWall.h"
#include "LocalConfigDialog.h"
#include "ConfigCache.h"

#undef MessageBox

using namespace BAPSPresenter;

System::Void BAPSPresenterMain::TrackBar_Scroll(System::Object ^  sender, System::EventArgs ^  e)
{
	/** Update the server with the new value the user has selected **/
	Command cmd = BAPSNET_PLAYBACK | BAPSNET_POSITION;
	/** The tag contains the channel number as a managed int **/
	cmd |= (safe_cast<int>(dynamic_cast<System::Windows::Forms::TrackBar^>(sender)->Tag) & 0x3f);
	/** The scrollbar value is the new setting **/
	u32int intArg = dynamic_cast<System::Windows::Forms::TrackBar^>(sender)->Value * 100;
	msgQueue->Enqueue(gcnew ActionMessageU32int(cmd, intArg));
}

System::Void BAPSPresenterMain::VolumeBar_Scroll(System::Object ^  sender, System::EventArgs ^  e)
{
	/** Update the server with the new value the user has selected **/
	Command cmd = BAPSNET_PLAYBACK | BAPSNET_VOLUME;
	/** The tag contains the channel number as a managed int **/
	cmd |= (safe_cast<int>(dynamic_cast<System::Windows::Forms::TrackBar^>(sender)->Tag) & 0x3f);
	/** WORK NEEDED: why oh why do we need floats **/
	float fltArg  = (float)((float)(dynamic_cast<System::Windows::Forms::TrackBar^>(sender)->Value) / 100.0);
	msgQueue->Enqueue(gcnew ActionMessageFloat(cmd, fltArg));
}

System::Void BAPSPresenterMain::BAPSPresenterMain_KeyDown(System::Object ^  sender, System::Windows::Forms::KeyEventArgs ^  e)
{
	/** Placeholder for the command we generate **/
	Command cmd;
	switch (e->KeyCode)
	{
	/** Keys F1-F4 are for channel 0 **/
	case Keys::F1 : /** F1 play **/
		cmd = BAPSNET_PLAYBACK | BAPSNET_PLAY | 0;
		msgQueue->Enqueue(gcnew ActionMessage(cmd));
		e->Handled = true;
		break;
	case Keys::F2 : /** F2 Pause **/
		cmd = BAPSNET_PLAYBACK | BAPSNET_PAUSE | 0;
		msgQueue->Enqueue(gcnew ActionMessage(cmd));
		e->Handled = true;
		break;
	case Keys::F3 : /** F3 Stop **/
		cmd = BAPSNET_PLAYBACK | BAPSNET_STOP | 0;
		msgQueue->Enqueue(gcnew ActionMessage(cmd));
		e->Handled = true;
		break;
	case Keys::F4:
		if (e->Alt)
		{
			e->Handled = true;
		}
		break;

	/** Keys F5-F8 are for channel 1 **/
	case Keys::F5 : /** F5 Play **/
		cmd = BAPSNET_PLAYBACK | BAPSNET_PLAY | 1;
		msgQueue->Enqueue(gcnew ActionMessage(cmd));
		e->Handled = true;
		break;
	case Keys::F6 : /** F6 Pause **/
		cmd = BAPSNET_PLAYBACK | BAPSNET_PAUSE | 1;
		msgQueue->Enqueue(gcnew ActionMessage(cmd));
		e->Handled = true;
		break;
	case Keys::F7 : /** F7 Stop **/
		cmd = BAPSNET_PLAYBACK | BAPSNET_STOP | 1;
		msgQueue->Enqueue(gcnew ActionMessage(cmd));
		e->Handled = true;
		break;

	/** Keys F9-F12 are for channel 2 **/
	case Keys::F9 : /** F9 Play **/
		cmd = BAPSNET_PLAYBACK | BAPSNET_PLAY | 2;
		msgQueue->Enqueue(gcnew ActionMessage(cmd));
		e->Handled = true;
		break;
	case Keys::F10 : /** F10 Pause **/
		cmd = BAPSNET_PLAYBACK | BAPSNET_PAUSE | 2;
		msgQueue->Enqueue(gcnew ActionMessage(cmd));
		e->Handled = true;
		break;
	case Keys::F11 : /** F11 Stop **/
		cmd = BAPSNET_PLAYBACK | BAPSNET_STOP | 2;
		msgQueue->Enqueue(gcnew ActionMessage(cmd));
		e->Handled = true;
		break;
	/** Other keyboard Commands **/
	case 'Q' : /** Ctrl+Alt+Q Shutdown **/
		if (e->Control && e->Alt)
		{
			System::Windows::Forms::DialogResult result = System::Windows::Forms::MessageBox::Show("Do you wish to disconnect?", "Shutdown?", System::Windows::Forms::MessageBoxButtons::YesNo);
			if (result == System::Windows::Forms::DialogResult::Yes)
			{
				this->Close();
			}
			e->Handled = true;		
		}
		break;
	case 'W' : /** Ctrl+Alt+W Alter Window **/
	case 'w' : /** Ctrl+Alt+W Alter Window **/
		if (e->Control && e->Alt)
		{
			if (this->WindowState == System::Windows::Forms::FormWindowState::Normal)
			{
				System::Drawing::Rectangle bounds = System::Windows::Forms::Screen::GetWorkingArea(this);
				bounds.X =0;
				bounds.Y = 0;
				this->MaximizedBounds = bounds;
				this->MaximumSize = bounds.Size;
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
				this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			}
			else
			{
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
				this->WindowState = System::Windows::Forms::FormWindowState::Normal;
			}
		}
		break;
	case 'O':
		if (e->Control)
		{
			if (e->Shift)
			{
				LocalConfigDialog^ ccd = gcnew LocalConfigDialog();
				ccd->ShowDialog();
				/** Show or hide the volume controls depending on the config setting **/
				bool showVolume = (System::String::Compare(ConfigManager::getConfigValueString("ShowVolume", "No"),"Yes") == 0);
				showVolumeControls(showVolume);
			}
			else
			{
				configDialog = gcnew ConfigDialog(msgQueue);
				Command cmd = BAPSNET_CONFIG | BAPSNET_GETOPTIONS;
				msgQueue->Enqueue(gcnew ActionMessage(cmd));
				configDialog->ShowDialog();
				delete configDialog;
				configDialog = nullptr;
			}
			e->Handled = true;
		}
		break;
	case 'S':
		if (e->Control)
		{
			securityDialog = gcnew SecurityDialog(msgQueue);
			Command cmd = BAPSNET_CONFIG | BAPSNET_GETPERMISSIONS;
			msgQueue->Enqueue(gcnew ActionMessage(cmd));
			securityDialog->ShowDialog();
			delete securityDialog;
			securityDialog = nullptr;
			e->Handled = true;
		}
		break;
	case 'N':
		if (e->Control)
		{
			bool wasOpen = true;
			if (!textDialog->Visible)
			{
				wasOpen = false;
				textDialog->Show();
				MethodInvokerStr^ mi = gcnew MethodInvokerStr(textDialog, &TextDialog::updateText);
				array<System::Object^>^ dd = gcnew array<System::Object^>(1) {MainTextDisplay->Text};
				textDialog->Invoke(mi, dd);
			}
			if (e->Shift)
			{
				MethodInvoker^ mi = gcnew MethodInvoker(textDialog, &TextDialog::toggleMaximize);
				textDialog->Invoke(mi);
			}
			else if (wasOpen)
			{
				textDialog->Hide();
			}
			e->Handled = true;
		}
		break;
	case 'A':
		if (e->Control)
		{
			about = gcnew About();
			msgQueue->Enqueue(gcnew ActionMessage(BAPSNET_SYSTEM|BAPSNET_VERSION));
			about->ShowDialog();
			about = nullptr;
			e->Handled = true;
		}
		break;
	default:
		/** Ignore all other keys **/
		break;
	}
}

System::Void BAPSPresenterMain::RefreshDirectory_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	Command cmd = BAPSNET_SYSTEM | BAPSNET_LISTFILES;
	/** The senders tag refers to the folder that needs to be refreshed **/
	cmd |= (safe_cast<int>(dynamic_cast<BAPSButton^>(sender)->Tag) & 0x3f);
	msgQueue->Enqueue(gcnew ActionMessage(cmd));
}

System::Void BAPSPresenterMain::SearchRecordLib_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	/** We have a handle stored in the class so that data can be passed to the object **/
	recordLibrarySearch = gcnew RecordLibrarySearch(msgQueue);
	recordLibrarySearch->ShowDialog();
	/** Always get rid of it again **/
	delete recordLibrarySearch;
	recordLibrarySearch = nullptr;
}

System::Void BAPSPresenterMain::loadShow_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	/** Handle stored for same reason as record library **/
	loadShowDialog = gcnew LoadShowDialog(msgQueue);
	loadShowDialog->ShowDialog();
	loadShowDialog = nullptr;
}

System::Void BAPSPresenterMain::feedbackButton_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	/** Handle stored for same reason as record library **/
	feedbackDialog = gcnew FeedbackDialog(msgQueue);
	feedbackDialog->ShowDialog();
	feedbackDialog = nullptr;
}
System::Void BAPSPresenterMain::helpButton_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	System::Windows::Forms::Help::ShowHelp(this,"BAPSPresenterHelp.chm");
	//HelpDialog^ hd = gcnew HelpDialog();
	//hd->Show();
}


void BAPSPresenterMain::positionChanged(System::Object^ sender, System::EventArgs^ e)
{
	TrackTime^ tt = static_cast<TrackTime^>(sender);
	/** Update the server with the new value the user has selected **/
	Command cmd = BAPSNET_PLAYBACK | BAPSNET_POSITION | tt->Channel;
	/** The scrollbar value is the new setting **/
	msgQueue->Enqueue(gcnew ActionMessageU32int(cmd, tt->Position));
}
void BAPSPresenterMain::cuePositionChanged(System::Object^ sender, System::EventArgs^ e)
{
	TrackTime^ tt = static_cast<TrackTime^>(sender);
	/** Update the server with the new value the user has selected **/
	Command cmd = BAPSNET_PLAYBACK | BAPSNET_CUEPOSITION | tt->Channel;
	/** The scrollbar value is the new setting **/
	msgQueue->Enqueue(gcnew ActionMessageU32int(cmd, tt->CuePosition));
}
void BAPSPresenterMain::introPositionChanged(System::Object^ sender, System::EventArgs^ e)
{
	TrackTime^ tt = static_cast<TrackTime^>(sender);
	/** Update the server with the new value the user has selected **/
	Command cmd = BAPSNET_PLAYBACK | BAPSNET_INTROPOSITION | tt->Channel;
	/** The scrollbar value is the new setting **/
	msgQueue->Enqueue(gcnew ActionMessageU32int(cmd, tt->IntroPosition));
}
System::Void BAPSPresenterMain::ChannelOperation_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	System::Windows::Forms::Label ^ lbl = static_cast<System::Windows::Forms::Label^>(sender);
	ChannelOperationLookup^ col = static_cast<ChannelOperationLookup^>(lbl->Tag);
	Command cmd = BAPSNET_PLAYBACK | col->co | (col->channel & 0x3f);
	msgQueue->Enqueue(gcnew ActionMessage(cmd));
}

void BAPSPresenterMain::ChannelListClear_Click(System::Object^ sender, System::EventArgs^ e)
{
	System::Windows::Forms::MenuItem^ mi = static_cast<System::Windows::Forms::MenuItem^>(sender);
	
	System::Windows::Forms::ContextMenu^ cm = static_cast<System::Windows::Forms::ContextMenu^>(mi->Parent);
	TrackList^ tl = static_cast<TrackList^>(cm->SourceControl);
	Command cmd = BAPSNET_PLAYLIST | BAPSNET_RESETPLAYLIST | tl->Channel;
	msgQueue->Enqueue(gcnew ActionMessage(cmd));
}

System::Void BAPSPresenterMain::trackListContextMenuStrip_Opening(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
{
	TrackList^ tl = safe_cast<TrackList^>(trackListContextMenuStrip->SourceControl);
	int testValue = ConfigCache::getValueInt("Automatically advance", tl->Channel);
	bool shouldCheck = (testValue == ConfigCache::findChoiceIndexFor("Automatically advance", "Yes"));
	automaticAdvanceToolStripMenuItem->Checked = shouldCheck;
	testValue = ConfigCache::getValueInt("Play on load", tl->Channel);
	shouldCheck = (testValue == ConfigCache::findChoiceIndexFor("Play on load", "Yes"));
	playOnLoadToolStripMenuItem->Checked = shouldCheck;
	testValue = ConfigCache::getValueInt("Repeat", tl->Channel);
	shouldCheck = (testValue == ConfigCache::findChoiceIndexFor("Repeat", "No repeat"));
	repeatNoneToolStripMenuItem->Checked = shouldCheck;
	shouldCheck = (testValue == ConfigCache::findChoiceIndexFor("Repeat", "Repeat one"));
	repeatOneToolStripMenuItem->Checked = shouldCheck;
	shouldCheck = (testValue == ConfigCache::findChoiceIndexFor("Repeat", "Repeat all"));
	repeatAllToolStripMenuItem->Checked = shouldCheck;
	deleteItemToolStripMenuItem->Enabled = (tl->LastIndexClicked != -1);
}

System::Void BAPSPresenterMain::trackListContextMenuStrip_ItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e)
{
	TrackList^ tl = safe_cast<TrackList^>(trackListContextMenuStrip->SourceControl);
	Command cmd = BAPSNET_CONFIG | BAPSNET_SETCONFIGVALUE | BAPSNET_CONFIG_USEVALUEMASK | tl->Channel;
	if (e->ClickedItem == automaticAdvanceToolStripMenuItem)
	{
		OptionCacheInfo^ oci = ConfigCache::getOption("Automatically advance");
		System::String^ newSetting = "Yes";
		if (automaticAdvanceToolStripMenuItem->Checked)
		{
			newSetting = "No";
		}
		msgQueue->Enqueue(gcnew ActionMessageU32intU32intU32int(cmd, oci->optionid, oci->type, safe_cast<int>(oci->choiceList[newSetting])));
	}
	else if (e->ClickedItem == playOnLoadToolStripMenuItem)
	{
		OptionCacheInfo^ oci = ConfigCache::getOption("Play on load");
		System::String^ newSetting = "Yes";
		if (playOnLoadToolStripMenuItem->Checked)
		{
			newSetting = "No";
		}
		msgQueue->Enqueue(gcnew ActionMessageU32intU32intU32int(cmd, oci->optionid, oci->type, safe_cast<int>(oci->choiceList[newSetting])));
	}
	else if (e->ClickedItem == repeatNoneToolStripMenuItem && !repeatNoneToolStripMenuItem->Checked)
	{
		OptionCacheInfo^ oci = ConfigCache::getOption("Repeat");
		msgQueue->Enqueue(gcnew ActionMessageU32intU32intU32int(cmd, oci->optionid, oci->type, safe_cast<int>(oci->choiceList["No repeat"])));
	}
	else if (e->ClickedItem == repeatOneToolStripMenuItem && !repeatOneToolStripMenuItem->Checked)
	{
		OptionCacheInfo^ oci = ConfigCache::getOption("Repeat");
		msgQueue->Enqueue(gcnew ActionMessageU32intU32intU32int(cmd, oci->optionid, oci->type, safe_cast<int>(oci->choiceList["Repeat one"])));
	}
	else if (e->ClickedItem == repeatAllToolStripMenuItem && !repeatAllToolStripMenuItem->Checked)
	{
		OptionCacheInfo^ oci = ConfigCache::getOption("Repeat");
		msgQueue->Enqueue(gcnew ActionMessageU32intU32intU32int(cmd, oci->optionid, oci->type, safe_cast<int>(oci->choiceList["Repeat all"])));
	}
	else if (e->ClickedItem == deleteItemToolStripMenuItem)
	{
		cmd = BAPSNET_PLAYLIST | BAPSNET_DELETEITEM | tl->Channel;
		msgQueue->Enqueue(gcnew ActionMessageU32int(cmd, tl->LastIndexClicked));
	}
	else if (e->ClickedItem == resetChannelStripMenuItem)
	{
		cmd = BAPSNET_PLAYLIST | BAPSNET_RESETPLAYLIST | tl->Channel;
		msgQueue->Enqueue(gcnew ActionMessage(cmd));
	}
	else if (e->ClickedItem == showAudioWallToolStripMenuItem)
	{
		if (audioWall==nullptr || !audioWall->Visible)
		{
			audioWall = gcnew AudioWall(msgQueue, tl);
			audioWall->Show();
		}
		else
		{
			audioWall->setChannel(tl);
			refreshAudioWall();
		}
	}
}
System::Void BAPSPresenterMain::chatOnOff_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (MainTextDisplay->Visible)
	{
		chatOnOff->Highlighted = false;
		chatOnOff->Text = "Chat OFF";
		MainTextDisplay->Visible = false;
		newMessageLabel->Visible = true;
		newChatMessage->Visible = true;
		chatText->Visible = true;
		chatTo->Visible = true;
		sendMessage->Visible = true;
	}
	else
	{
		chatOnOff->Text = "Chat ON";
		MainTextDisplay->Visible = true;
		newMessageLabel->Visible = false;
		newChatMessage->Visible = false;
		chatText->Visible = false;
		chatTo->Visible = false;
		sendMessage->Visible = false;
	}
}
System::Void BAPSPresenterMain::sendMessage_Click(System::Object^  sender, System::EventArgs^  e)
{
	Command cmd = BAPSNET_SYSTEM | BAPSNET_SENDMESSAGE;
	msgQueue->Enqueue(gcnew ActionMessageStringStringString(cmd,username, chatTo->SelectedItem->ToString(), newChatMessage->Text));
	newChatMessage->Text = "";
}

System::Void BAPSPresenterMain::newChatMessage_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (newChatMessage->Text->Length > 0)
	{
		this->AcceptButton = sendMessage;
	}
	else
	{
		this->AcceptButton = nullptr;
	}
}