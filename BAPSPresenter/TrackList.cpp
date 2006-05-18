#include "StdAfx.h"
#include "TrackList.h"
#include "ClientHelpers.h"

using namespace BAPSPresenter;



void TrackList::OnPaint(System::Windows::Forms::PaintEventArgs^ e)
{
	opLock->WaitOne();
    // The base class contains a bitmap, offScreen, for constructing
    // the control and is rendered when all items are populated.
    // This technique prevents flicker.
	System::Drawing::Graphics^ gOffScreen = System::Drawing::Graphics::FromImage(offScreen);
	System::Drawing::Rectangle rect = this->ClientRectangle;
	rect.Width-=2;
	rect.Height = ((items->Count<scroll->IndexAtTop+DrawCount)?items->Count:scroll->IndexAtTop+DrawCount);
	gOffScreen->FillRectangle(System::Drawing::Brushes::LightGray, rect);
	rect.Y = rect.Height;
	rect.Height = this->ClientRectangle.Height-rect.Height;
	if (rect.Height > 0)
	{
		gOffScreen->FillRectangle(System::Drawing::Brushes::SeaShell, rect);
	}
    int itemTop = 0;

	// The index to be shown as loaded
	int loadedIndex = selectedIndex;
	if (selectedIndex == fromIndex)
	{
		loadedIndex = hoverIndex;
	}
	else if (fromIndex < selectedIndex &&
			 hoverIndex >= selectedIndex)
	{
		loadedIndex = selectedIndex-1;
	}
	else if (fromIndex > selectedIndex &&
			 hoverIndex <= selectedIndex)
	{
		loadedIndex = selectedIndex+1;
	}

	// Get this type's assembly
	System::Reflection::Assembly^ assem = System::Reflection::Assembly::GetExecutingAssembly();
	// Get the stream that holds the resource
	// NOTE1: Make sure not to close this stream!
	// NOTE2: Also be very careful to match the case
	//        on the resource name itself
	System::IO::Stream^ stream = assem->GetManifestResourceStream("textItem.png");
	// Load the text item bitmap
	Bitmap^ textItem = gcnew Bitmap(stream);
	textItem->MakeTransparent();

	stream = assem->GetManifestResourceStream("libraryItem.png");
	// Load the text item bitmap
	Bitmap^ libraryItem = gcnew Bitmap(stream);
	libraryItem->MakeTransparent();

	stream = assem->GetManifestResourceStream("fileItem.png");
	// Load the text item bitmap
	Bitmap^ fileItem = gcnew Bitmap(stream);
	fileItem->MakeTransparent();

	stream = assem->GetManifestResourceStream("textItemSel.png");
	// Load the text item bitmap
	Bitmap^ textItemSel = gcnew Bitmap(stream);
	textItemSel->MakeTransparent();

    // Draw the fonts in the list.
	for(int n = scroll->IndexAtTop; n < ((items->Count<scroll->IndexAtTop+DrawCount)?items->Count:scroll->IndexAtTop+DrawCount); n++)
	{

		System::Drawing::Brush^ brush;
		System::Drawing::Rectangle rect;
		if (n == loadedIndex)
		{
			brush = System::Drawing::Brushes::PaleGoldenrod;
		}
		else if (n%2 == 0)
		{
			brush = System::Drawing::Brushes::Snow;
		}
		else
		{
			brush = System::Drawing::Brushes::AntiqueWhite;
		}
		rect = System::Drawing::Rectangle(0,
										  itemTop,
										  // If the scroll bar is visible, subtract the scrollbar width
										  // otherwise subtract 2 for the width of the rectangle
										  this->ClientSize.Width - (scroll->Visible ? scroll->Width : 1)-1,
										  ItemHeight-1);
		gOffScreen->FillRectangle(brush,rect);

		/** Which index do we display here **/
		int indexToShow = n;
		if (n == hoverIndex)
		{
			indexToShow = fromIndex;
		}
		else if (fromIndex <= n && hoverIndex >= n)
		{
			indexToShow = n+1;
		}
		else if (fromIndex >= n && hoverIndex < n)
		{
			indexToShow = n-1;
		}
		switch (items[indexToShow]->type)
		{
		case BAPSNET_FILEITEM:
			gOffScreen->DrawImage(fileItem, 0,itemTop);
			break;
		case BAPSNET_LIBRARYITEM:
			gOffScreen->DrawImage(libraryItem, 0,itemTop);
			break;
		case BAPSNET_TEXTITEM:
			if (items[indexToShow]->isSelectedTextItem)
			{
				gOffScreen->DrawImage(textItemSel, 0,itemTop);
			}
			else
			{
				gOffScreen->DrawImage(textItem, 0,itemTop);
			}
			break;
		}

        // Draw the item
		gOffScreen->DrawString(items[indexToShow]->ToString(), this->Font, System::Drawing::Brushes::Black, System::Drawing::Rectangle(18, itemTop, this->ClientRectangle.Width-20,this->ItemHeight), gcnew System::Drawing::StringFormat(System::Drawing::StringFormatFlags::NoWrap));
		rect.Height -= 1;
		rect.Width -= 1;
		// if drawing the loaded index or the index we are hovering over
		if (n == loadedIndex || hoverIndex == n)
		{
			gOffScreen->DrawRectangle(System::Drawing::Pens::Black, rect);
		}

        itemTop += this->ItemHeight;
    }
	// if we are adding to this control
	if (addTo||this->Focused)
	{
		System::Drawing::Rectangle rect = this->ClientRectangle;
		rect.Height-=3;
		
		rect.Width-= (scroll->Visible)?2:3;
		if (scroll->Visible)
		{
			rect.Width -= scroll->Width;
		}
		gOffScreen->DrawRectangle(System::Drawing::Pens::DarkOrange, rect);
		rect.X++;
		rect.Y++;
		rect.Height-=2;
		rect.Width-=2;
		gOffScreen->DrawRectangle(System::Drawing::Pens::DarkOrange, rect);
	}

    e->Graphics->DrawImage(offScreen, 1, 1);

    delete gOffScreen;
	opLock->ReleaseMutex();
}

void TrackList::OnMouseDown(System::Windows::Forms::MouseEventArgs^ e)
{
	__super::OnMouseDown(e);
	this->Focus();
	LastIndexClicked = indexFromY(e->Y);
	if (e->Button != System::Windows::Forms::MouseButtons::Left)
	{
		return;
	}
	opLock->WaitOne();
	System::Drawing::Point pt = System::Drawing::Point(e->X,e->Y);
	//Retrieve the item at the specified location within the ListBox.
	int index = indexFromY(e->Y);

	// Starts a drag-and-drop operation.
	if(index >= 0) 
	{
		TrackListDragDrop^ tldd = gcnew TrackListDragDrop(index, channel);
		fromIndex = index;
		System::Windows::Forms::DragDropEffects result;
		result = this->DoDragDrop(tldd, System::Windows::Forms::DragDropEffects::Move);
		if (result == System::Windows::Forms::DragDropEffects::Move)
		{
			if (!tldd->moved && index != selectedIndex && !pendingLoadRequest)
			{
				if (items[index]->type != BAPSNET_TEXTITEM)
				{
					pendingLoadRequest = true;
				}
				RequestChange(this, gcnew RequestChangeEventArgs(channel, CHANGE_SELECTEDINDEX, index));
				this->Invalidate();
			}
		}
		hoverIndex = -1;
		fromIndex = -1;
	}
	opLock->ReleaseMutex();
}
void TrackList::OnMouseWheel(System::Windows::Forms::MouseEventArgs^ e)
{
	__super::OnMouseWheel(e);
	opLock->WaitOne();
	int newTop = scroll->IndexAtTop - (e->Delta/120);
	if (newTop < 0)
	{
		newTop = 0;
	}
	if (newTop > scroll->TotalItems-scroll->ViewableItems)
	{
		newTop = scroll->TotalItems-scroll->ViewableItems;
	}
	scroll->IndexAtTop = newTop;
	this->Invalidate();
	opLock->ReleaseMutex();
}

void TrackList::OnDragEnter(System::Windows::Forms::DragEventArgs ^  e)
{
	__super::OnDragEnter(e);
	if(e->Data->GetDataPresent(TrackListDragDrop::typeid))
	{
		TrackListDragDrop^ tldd =static_cast<TrackListDragDrop^>(e->Data->GetData(TrackListDragDrop::typeid));
		if (tldd->fromChannel == channel)
		{
			e->Effect = System::Windows::Forms::DragDropEffects::Move;
		}
	}
	else if(e->Data->GetDataPresent(FolderTempStruct::typeid))
	{
		e->Effect = System::Windows::Forms::DragDropEffects::Copy;
	}
}

void TrackList::OnDragDrop(System::Windows::Forms::DragEventArgs ^  e)
{
	__super::OnDragDrop(e);
	int index = indexFromY(this->PointToClient(System::Drawing::Point(e->X, e->Y)).Y);
	if(e->Data->GetDataPresent(TrackListDragDrop::typeid))
	{
		TrackListDragDrop^ tldd =static_cast<TrackListDragDrop^>(e->Data->GetData(TrackListDragDrop::typeid));
		if (channel == tldd->fromChannel)
		{
			if (index != -1 && index != tldd->fromIndex)
			{
				RequestChange(this, gcnew RequestChangeEventArgs(channel, CHANGE_MOVEINDEX, tldd->fromIndex, index));
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
		RequestChange(this, gcnew RequestChangeEventArgs(channel, CHANGE_ADD, fts->fromFolder, fts->fromIndex));
		addTo = false;
		this->Invalidate();
	}
}

void TrackList::OnDragOver(System::Windows::Forms::DragEventArgs ^  e)
{
	__super::OnDragOver(e);
	if(e->Data->GetDataPresent(TrackListDragDrop::typeid))
	{
		TrackListDragDrop^ tldd =static_cast<TrackListDragDrop^>(e->Data->GetData(TrackListDragDrop::typeid));
		if (channel == tldd->fromChannel)
		{
			int hi = indexFromY(this->PointToClient(System::Drawing::Point(e->X, e->Y)).Y);
			if (hi != fromIndex)
			{
				tldd->moved = true;
			}
			if (hi == -1)
			{
				hi = fromIndex;
			}
			if (hi != hoverIndex)
			{
				hoverIndex = hi;
				this->Invalidate();
			}
		}
	}
	else if (e->Data->GetDataPresent(FolderTempStruct::typeid))
	{
		if (!addTo)
		{
			addTo = true;
			this->Invalidate();
		}
	}
}

void TrackList::OnDragLeave(System::EventArgs ^  e)
{
	__super::OnDragLeave(e);
	addTo = false;
	hoverIndex = fromIndex;
	this->Invalidate();
}

void TrackList::OnKeyDown(System::Windows::Forms::KeyEventArgs^ e)
{
	__super::OnKeyDown(e);
	e->Handled = HandleKey(e->KeyCode);
}

bool TrackList::ProcessDialogKey(System::Windows::Forms::Keys keyData)
{
	bool retVal = HandleKey(keyData);
	if (!retVal)
	{
		__super::ProcessDialogKey(keyData);
	}
	return retVal;
}

bool TrackList::HandleKey(System::Windows::Forms::Keys keyData)
{
	bool retVal = false;
	opLock->WaitOne();
	int newSelectedIndex = -1;
	switch(keyData)
	{
	case Keys::Down:
		newSelectedIndex = findAudioItem(LoadedIndex+1, false);
		retVal = true;
		break;
	case Keys::Up:
		newSelectedIndex = findAudioItem(LoadedIndex-1, true);
		retVal = true;
		break;
	case Keys::PageDown:
		newSelectedIndex = findAudioItem(LoadedIndex+DrawCount, false);
		if (newSelectedIndex == -1)
		{
			newSelectedIndex = findAudioItem(items->Count-1, true);
		}
		retVal = true;
		break;
	case Keys::PageUp:
		newSelectedIndex = findAudioItem(LoadedIndex-DrawCount, true);
		if (newSelectedIndex == -1)
		{
			newSelectedIndex = findAudioItem(0, false);
		}
		retVal = true;
		break;
	case Keys::Home:
		newSelectedIndex = findAudioItem(0, false);
		retVal = true;
		break;
	case Keys::End:
		newSelectedIndex = findAudioItem(items->Count-1, true);
		retVal = true;
		break;
	}
	if (newSelectedIndex!=-1 && newSelectedIndex !=LoadedIndex && !pendingLoadRequest)
	{
		pendingLoadRequest = true;
		RequestChange(this, gcnew RequestChangeEventArgs(channel, CHANGE_SELECTEDINDEX, newSelectedIndex));
	}
	if (keyData == Keys::Delete)
	{
		if (LoadedIndex != -1)
		{
			RequestChange(this, gcnew RequestChangeEventArgs(channel, CHANGE_DELETEINDEX, LoadedIndex));
		}
		retVal = true;
	}
	opLock->ReleaseMutex();

	return retVal;
}

int TrackList::findAudioItem(int startIndex, bool goingUp)
{
	int addMe = 1;
	if (goingUp)
	{
		addMe = -1;
	}
	for ( ; ((goingUp)?-1:startIndex) < ((goingUp)?startIndex:items->Count) ; startIndex+=addMe)
	{
		if (items[startIndex]->type != BAPSNET_TEXTITEM)
		{
			return startIndex;
		}
	}
	return -1;
}