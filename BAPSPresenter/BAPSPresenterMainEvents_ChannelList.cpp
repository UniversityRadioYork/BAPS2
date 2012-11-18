#include "StdAfx.h"
#include "BAPSPresenterMain.h"
#include "Messages.h"

using namespace BAPSPresenter;

System::Void BAPSPresenterMain::ChannelList_MouseDown(System::Object ^  sender, System::Windows::Forms::MouseEventArgs ^  e)
{
	if (e->Button != System::Windows::Forms::MouseButtons::Left)
	{
		return;
	}
	System::Windows::Forms::ListBox^ lb =( dynamic_cast<System::Windows::Forms::ListBox^>(sender));
	PlaylistInfo^ info = static_cast<PlaylistInfo^>(lb->Tag);
	info->opLock->WaitOne();
	int channel = info->channel;
	System::Drawing::Point pt = System::Drawing::Point(e->X,e->Y);
	//Retrieve the item at the specified location within the ListBox.
	int index = lb->IndexFromPoint(pt);

	// Starts a drag-and-drop operation.
	if(index >= 0) 
	{
		PlayListTempStruct^ plts = gcnew PlayListTempStruct(index, channel);
		info->fromIndex = index;
		System::Windows::Forms::DragDropEffects result;
		result = lb->DoDragDrop(plts, System::Windows::Forms::DragDropEffects::Move);
		if (result == System::Windows::Forms::DragDropEffects::Move)
		{
			if (!plts->moved)
			{
				if (index != info->selectedIndex)
				{
					Command cmd = BAPSNET_PLAYBACK | BAPSNET_LOAD;
					/** Channel number is in the sender's tag **/
					cmd |= (channel & 0x3f);
					/** Get the selected index as above **/
					u32int intArg  = index;
					msgQueue->Enqueue(gcnew ActionMessageU32int(cmd, intArg));
				}
			}
		}
		info->hoverIndex = -1;
		info->fromIndex = -1;
		lb->Invalidate();
	}
	info->opLock->ReleaseMutex();
}

System::Void BAPSPresenterMain::ChannelList_DragEnter(System::Object ^  sender, System::Windows::Forms::DragEventArgs ^  e)
{
	if(e->Data->GetDataPresent(PlayListTempStruct::typeid))
	{
		System::Windows::Forms::ListBox^ lb =( dynamic_cast<System::Windows::Forms::ListBox^>(sender));
		PlaylistInfo^ info = static_cast<PlaylistInfo^>(lb->Tag);
		PlayListTempStruct^ plts =static_cast<PlayListTempStruct^>(e->Data->GetData(PlayListTempStruct::typeid));
		if (plts->fromChannel == info->channel)
		{
			e->Effect = System::Windows::Forms::DragDropEffects::Move;
		}
	}
	else if(e->Data->GetDataPresent(FolderTempStruct::typeid))
	{
		e->Effect = System::Windows::Forms::DragDropEffects::Copy;
	}
}

System::Void BAPSPresenterMain::ChannelList_DragDrop(System::Object ^  sender, System::Windows::Forms::DragEventArgs ^  e)
{
	System::Windows::Forms::ListBox^ lb =( dynamic_cast<System::Windows::Forms::ListBox^>(sender));
	PlaylistInfo^ info = static_cast<PlaylistInfo^>(lb->Tag);
	int channel = info->channel;
	System::Drawing::Point pt = System::Drawing::Point(e->X, e->Y);
	int index = lb->IndexFromPoint(lb->PointToClient(pt));
	if(e->Data->GetDataPresent(PlayListTempStruct::typeid))
	{
		PlayListTempStruct^ plts =static_cast<PlayListTempStruct^>(e->Data->GetData(PlayListTempStruct::typeid));
		if (channel == plts->fromChannel)
		{
			if (index != -1 && index != plts->fromIndex)
			{
				Command cmd = BAPSNET_PLAYLIST | (channel & 0x3f) | BAPSNET_MOVEITEMTO;
				msgQueue->Enqueue(gcnew ActionMessageU32intU32int(cmd, plts->fromIndex, index));
			}
		}
		else
		{
			e->Effect = System::Windows::Forms::DragDropEffects::None;
		}
	}
	else if (e->Data->GetDataPresent(FolderTempStruct::typeid))
	{
		FolderTempStruct^ fts =static_cast<FolderTempStruct^>(e->Data->GetData(FolderTempStruct::typeid));
		/** Update the server to add the FILEITEM **/
		Command cmd = BAPSNET_PLAYLIST | BAPSNET_ADDITEM | (channel & 0x3f);
		msgQueue->Enqueue(gcnew ActionMessageU32intU32intString(cmd, (u32int)BAPSNET_FILEITEM, fts->fromFolder, directoryList[fts->fromFolder]->Items[fts->fromIndex]->ToString()));
		info->addTo = false;
		lb->Invalidate();
	}
}

System::Void BAPSPresenterMain::ChannelList_DrawItem(System::Object ^  sender, System::Windows::Forms::DrawItemEventArgs ^  e)
{

	System::Windows::Forms::ListBox^ lb =( dynamic_cast<System::Windows::Forms::ListBox^>(sender));
	if (e->Index == -1 || e->Index >= lb->Items->Count)
	{
		return;
	}
	PlaylistInfo^ info= static_cast<PlaylistInfo^>(lb->Tag);
	System::Drawing::Brush^ brush = System::Drawing::Brushes::White;

	int loadedIndex = info->selectedIndex;
	if (info->selectedIndex == info->fromIndex)
	{
		loadedIndex = info->hoverIndex;
	}
	else if (info->fromIndex < info->selectedIndex &&
			 info->hoverIndex >= info->selectedIndex)
	{
		loadedIndex = info->selectedIndex-1;
	}
	else if (info->fromIndex > info->selectedIndex &&
			 info->hoverIndex <= info->selectedIndex)
	{
		loadedIndex = info->selectedIndex+1;
	}
	// Create a new Brush and initialize to a Black colored brush by default.
	if (e->Index == loadedIndex)
	{
		brush = System::Drawing::Brushes::PaleGoldenrod;
	}
	else if (e->Index%2 == 0)
	{
		brush = System::Drawing::Brushes::Snow;
	}
	else
	{
		brush = System::Drawing::Brushes::AntiqueWhite;
	}
	
	e->Graphics->FillRectangle(brush, e->Bounds);
	if (e->Index == loadedIndex)
	{
		e->Graphics->DrawRectangle(System::Drawing::Pens::Black, System::Drawing::Rectangle(e->Bounds.X, e->Bounds.Y, e->Bounds.Width-1, e->Bounds.Height-1));
	}

	/** Which text do we display here **/
	int indexToShow = e->Index;
	if (e->Index == info->hoverIndex)
	{
		indexToShow = info->fromIndex;
	}
	else if (info->fromIndex <= e->Index && info->hoverIndex >= e->Index)
	{
		indexToShow = e->Index+1;
	}
	else if (info->fromIndex >= e->Index && info->hoverIndex < e->Index)
	{
		indexToShow = e->Index-1;
	}
	brush = System::Drawing::Brushes::Black;
	// Draw the current item text based on the current Font and the custom brush settings.
	e->Graphics->DrawString(lb->Items[indexToShow]->ToString(),
							e->Font,
							brush,
							e->Bounds,
							System::Drawing::StringFormat::GenericDefault);

	if (info->hoverIndex == e->Index)
	{
		e->Graphics->DrawRectangle(System::Drawing::Pens::Black, System::Drawing::Rectangle(e->Bounds.X, e->Bounds.Y, e->Bounds.Width-1, e->Bounds.Height-1));
	}
	else if (info->addTo && e->Index==(lb->Items->Count-1))
	{
		e->Graphics->DrawLine(System::Drawing::Pens::Black, System::Drawing::Point(e->Bounds.X+5, e->Bounds.Y+e->Bounds.Height-2), System::Drawing::Point(e->Bounds.X+e->Bounds.Width-5, e->Bounds.Y+e->Bounds.Height-2));
	}
}

System::Void BAPSPresenterMain::ChannelList_DragOver(System::Object ^  sender, System::Windows::Forms::DragEventArgs ^  e)
{
	System::Windows::Forms::ListBox^ lb =( dynamic_cast<System::Windows::Forms::ListBox^>(sender));
	if(e->Data->GetDataPresent(PlayListTempStruct::typeid))
	{
		int channel = static_cast<PlaylistInfo^>(lb->Tag)->channel;
		PlayListTempStruct^ plts =static_cast<PlayListTempStruct^>(e->Data->GetData(PlayListTempStruct::typeid));
		if (channel == plts->fromChannel)
		{
			System::Windows::Forms::ListBox^ lb =dynamic_cast<System::Windows::Forms::ListBox^>(sender);
			PlaylistInfo^ info= static_cast<PlaylistInfo^>(lb->Tag);
			System::Drawing::Point pt = System::Drawing::Point(e->X, e->Y);
			int hi = lb->IndexFromPoint(lb->PointToClient(pt));
			if (hi != info->fromIndex)
			{
				plts->moved = true;
			}
			if (hi == -1)
			{
				hi = info->fromIndex;
			}
			if (hi != info->hoverIndex)
			{
				info->hoverIndex = hi;
				lb->Invalidate();
			}
		}
	}
	else if (e->Data->GetDataPresent(FolderTempStruct::typeid))
	{
		bool addTo = static_cast<PlaylistInfo^>(lb->Tag)->addTo;
		if (!addTo)
		{
			static_cast<PlaylistInfo^>(lb->Tag)->addTo = true;
			lb->Invalidate();
		}
	}
}
System::Void BAPSPresenterMain::ChannelList_DragLeave(System::Object ^  sender, System::EventArgs ^  e)
{
	System::Windows::Forms::ListBox^ lb =( dynamic_cast<System::Windows::Forms::ListBox^>(sender));
	PlaylistInfo^ info = static_cast<PlaylistInfo^>(lb->Tag);
	info->addTo = false;
	info->hoverIndex = info->fromIndex;
	lb->Invalidate();
}
System::Void BAPSPresenterMain::ChannelList_KeyDown(System::Object ^  sender, System::Windows::Forms::KeyEventArgs ^  e)
{
	System::Windows::Forms::ListBox^ lb =( dynamic_cast<System::Windows::Forms::ListBox^>(sender));
	PlaylistInfo^ info = static_cast<PlaylistInfo^>(lb->Tag);
	switch (e->KeyCode)
	{
	case Keys::Delete:
		if (info->selectedIndex != -1)
		{
			Command cmd = BAPSNET_PLAYLIST | (info->channel & 0x3f)| BAPSNET_DELETEITEM;
			msgQueue->Enqueue(gcnew ActionMessageU32int(cmd, info->selectedIndex));
		}
		e->Handled = true;
		break;
	}
}