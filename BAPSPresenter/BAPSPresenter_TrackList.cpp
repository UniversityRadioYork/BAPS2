#include "StdAfx.h"
#include "BAPSPresenterMain.h"
#include "Messages.h"

using namespace BAPSPresenter;


System::Void BAPSPresenterMain::TrackList_RequestChange(System::Object^  o, BAPSPresenter::RequestChangeEventArgs^  e)
{
	switch (e->ct)
	{
	case CHANGE_SELECTEDINDEX:
		{
			if ((trackList[e->channel]->items[e->index]->type == BAPSNET_TEXTITEM) || (channelPlay[e->channel]->Enabled))
			{
				Command cmd = BAPSNET_PLAYBACK | BAPSNET_LOAD;
				/** Channel number is in the sender's tag **/
				cmd |= (e->channel & 0x3f);
				/** Get the selected index as above **/
				u32int intArg  = e->index;
				msgQueue->Enqueue(gcnew ActionMessageU32int(cmd, intArg));
				
				loadImpossibleTimer[e->channel]->Enabled = false;
				//loadedText[e->channel]->Highlighted = false;
				loadedText[e->channel]->BackColor = System::Drawing::SystemColors::Window;
			}
			else
			{
				safe_cast<ChannelTimeoutStruct^>(loadImpossibleTimer[e->channel]->Tag)->timeout = 10;
				loadImpossibleTimer[e->channel]->Enabled = true;
			}
		}
		break;
	case CHANGE_MOVEINDEX:
		{
			Command cmd = BAPSNET_PLAYLIST | (e->channel & 0x3f) | BAPSNET_MOVEITEMTO;
			msgQueue->Enqueue(gcnew ActionMessageU32intU32int(cmd, e->index, e->index2));
		}
		break;
	case CHANGE_DELETEINDEX:
		{
			Command cmd = BAPSNET_PLAYLIST | (e->channel & 0x3f)| BAPSNET_DELETEITEM;
			msgQueue->Enqueue(gcnew ActionMessageU32int(cmd, e->index));
		}
		break;
	case CHANGE_ADD:
		{
			Command cmd = BAPSNET_PLAYLIST | BAPSNET_ADDITEM | (e->channel & 0x3f);
			msgQueue->Enqueue(gcnew ActionMessageU32intU32intString(cmd, (u32int)BAPSNET_FILEITEM, e->index, directoryList[e->index]->Items[e->index2]->ToString()));
		}
		break;
	case CHANGE_COPY:
		{
			Command cmd = BAPSNET_PLAYLIST | BAPSNET_COPYITEM | (e->channel & 0x3f);
			msgQueue->Enqueue(gcnew ActionMessageU32intU32int(cmd, e->index, e->index2));
		}
		break;

	}
}

System::Void BAPSPresenterMain::loadImpossibleFlicker(System::Object ^  sender, System::EventArgs ^  e)
{
	System::Windows::Forms::Timer^ timer = safe_cast<System::Windows::Forms::Timer^>(sender);
	ChannelTimeoutStruct^ cts = safe_cast<ChannelTimeoutStruct^>(timer->Tag);
	cts->timeout--;
	if (cts->timeout == 0)
	{
		timer->Enabled = false;
		//loadedText[cts->channel]->Highlighted = false;
		loadedText[cts->channel]->BackColor = System::Drawing::SystemColors::Window;
	}
	else
	{
		if (loadedText[cts->channel]->BackColor == System::Drawing::SystemColors::Window)
			loadedText[cts->channel]->BackColor = System::Drawing::Color::LightSteelBlue;
		else
			loadedText[cts->channel]->BackColor = System::Drawing::SystemColors::Window;
	}
}