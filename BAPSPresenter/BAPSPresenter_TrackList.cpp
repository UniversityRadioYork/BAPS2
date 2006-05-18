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
			Command cmd = BAPSNET_PLAYBACK | BAPSNET_LOAD;
			/** Channel number is in the sender's tag **/
			cmd |= (e->channel & 0x3f);
			/** Get the selected index as above **/
			u32int intArg  = e->index;
			msgQueue->Enqueue(gcnew ActionMessageU32int(cmd, intArg));
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
			msgQueue->Enqueue(gcnew ActionMessageU32intU32intString(cmd, (u32int)BAPSNET_FILEITEM, e->index, directoryList[e->index]->getItem(e->index2)->ToString()));
		}
		break;
	}
}