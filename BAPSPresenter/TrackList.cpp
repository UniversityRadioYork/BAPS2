#include "StdAfx.h"
#include "TrackList.h"
#include "ClientHelpers.h"

using namespace BAPSPresenter;

void TrackList::OnPaint(System::Windows::Forms::PaintEventArgs^ e)
{
	//opLock->WaitOne();
    // The base class contains a bitmap, offScreen, for constructing
    // the control and is rendered when all items are populated.
    // This technique prevents flicker.
	System::Drawing::Graphics^ gOffScreen = System::Drawing::Graphics::FromImage(offScreen);
	gOffScreen->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
	System::Drawing::Rectangle rect = this->ClientRectangle;
	rect.Width-=2;
	//rect.Height = ((items->Count<scroll->IndexAtTop+DrawCount)?items->Count:scroll->IndexAtTop+DrawCount);
	rect.Height = ((items->Count<scroll->Value+DrawCount)?items->Count:scroll->Value+DrawCount);
	gOffScreen->FillRectangle(System::Drawing::SystemBrushes::Window, rect);
	rect.Y = rect.Height;
	rect.Height = this->ClientRectangle.Height-rect.Height;
	if (rect.Height > 0)
	{
		gOffScreen->FillRectangle(System::Drawing::SystemBrushes::Window, rect);
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
	/*System::Reflection::Assembly^ assem = System::Reflection::Assembly::GetExecutingAssembly();
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
	textItemSel->MakeTransparent();*/

    // Draw the fonts in the list.
	//for(int n = scroll->IndexAtTop; n < ((items->Count<scroll->IndexAtTop+DrawCount)?items->Count:scroll->IndexAtTop+DrawCount); n++)
	for(int n = scroll->Value; n < ((items->Count<scroll->Value+DrawCount)?items->Count:scroll->Value+DrawCount); n++)
	{

		System::Drawing::Rectangle rect;
		rect = System::Drawing::Rectangle(0,
										  itemTop,
										  // If the scroll bar is visible, subtract the scrollbar width
										  // otherwise subtract 2 for the width of the rectangle
										  this->ClientSize.Width - (scroll->Visible ? scroll->Width : 1)-1, ItemHeight);
		System::Drawing::Brush^ brush;
		System::Drawing::Brush^ textbrush;
		if (n == loadedIndex)
		{
			brush = System::Drawing::SystemBrushes::Highlight;
			textbrush = System::Drawing::SystemBrushes::HighlightText;
			gOffScreen->FillRectangle(brush,rect);
		}
		/*else if (n%2 == 0)
		{
			brush = System::Drawing::Brushes::Snow;
		}*/
		else
		{
			//brush = System::Drawing::SystemBrushes::Window;
			textbrush = System::Drawing::SystemBrushes::ControlText;
		}

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
			gOffScreen->FillEllipse(System::Drawing::Brushes::SteelBlue, 4, itemTop+4, 8, 8);
			//gOffScreen->DrawString("Usr", this->Font, System::Drawing::Brushes::Red, 1, itemTop);
			//gOffScreen->DrawImage(fileItem, 0,itemTop);
			break;
		case BAPSNET_LIBRARYITEM:
			gOffScreen->FillEllipse(System::Drawing::Brushes::LimeGreen, 4, itemTop+4, 8, 8);
			//gOffScreen->DrawString("Lib", this->Font, System::Drawing::Brushes::Green, 1, itemTop);
			//gOffScreen->DrawImage(libraryItem, 0,itemTop);
			break;
		case BAPSNET_TEXTITEM:
			//gOffScreen->FillEllipse(System::Drawing::Brushes::Blue, 4, itemTop+4, 8, 8);
			if (items[indexToShow]->isSelectedTextItem)
			{
				gOffScreen->FillRectangle(System::Drawing::Brushes::Lavender,rect);
				//gOffScreen->DrawImage(textItemSel, 0,itemTop);
			}
			/*else
			{
				gOffScreen->DrawImage(textItem, 0,itemTop);
			}*/
			gOffScreen->DrawString("T", this->Font, System::Drawing::Brushes::Blue, 4.0f, (float)itemTop+1.0f);
			break;
		}

        // Draw the item
		gOffScreen->DrawString(items[indexToShow]->ToString(), this->Font, textbrush, System::Drawing::Rectangle(18, itemTop, this->ClientRectangle.Width-20,this->ItemHeight), gcnew System::Drawing::StringFormat(System::Drawing::StringFormatFlags::NoWrap));
		rect.Height -= 1;
		rect.Width -= 1;
		// if drawing the loaded index or the index we are hovering over
		if (n == loadedIndex || hoverIndex == n)
		{
			gOffScreen->DrawRectangle(System::Drawing::Pens::Black, rect);
		}

        itemTop += this->ItemHeight;
    }
	rect = this->ClientRectangle;
	rect.Height-=3;
	
	rect.Width-= (scroll->Visible)?2:3;
	if (scroll->Visible)
	{
		rect.Width -= scroll->Width;
	}
	// if we are adding to this control
	//if (addTo||this->Focused)
	if (addTo)
	{
		gOffScreen->DrawRectangle(System::Drawing::SystemPens::Highlight, rect);
		rect.X++;
		rect.Y++;
		rect.Height-=2;
		rect.Width-=2;
		gOffScreen->DrawRectangle(System::Drawing::SystemPens::Highlight, rect);
	} else gOffScreen->DrawRectangle(System::Drawing::SystemPens::WindowFrame, rect);

    e->Graphics->DrawImage(offScreen, 1, 1);

    delete gOffScreen;
	//opLock->ReleaseMutex();
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
	//opLock->WaitOne();
	System::Drawing::Point pt = System::Drawing::Point(e->X,e->Y);
	//Retrieve the item at the specified location within the ListBox.
	int index = indexFromY(e->Y);

	// Starts a drag-and-drop operation.
	if(index >= 0) 
	{
		TrackListDragDrop^ tldd = gcnew TrackListDragDrop(index, channel);
		savedFromIndex = index;
		System::Windows::Forms::DragDropEffects result;
		result = this->DoDragDrop(tldd, System::Windows::Forms::DragDropEffects::Move|System::Windows::Forms::DragDropEffects::Copy);
		if (result == System::Windows::Forms::DragDropEffects::Move)
		{
			if (!tldd->moved && index != selectedIndex && channel == tldd->toChannel)
			{
				RequestChange(this, gcnew RequestChangeEventArgs(channel, CHANGE_SELECTEDINDEX, index));
				this->Invalidate();
			}
		}
		hoverIndex = -1;
		fromIndex = -1;
		savedFromIndex = -1;
		this->Invalidate();
	}
	//opLock->ReleaseMutex();
}
void TrackList::OnMouseWheel(System::Windows::Forms::MouseEventArgs^ e)
{
	__super::OnMouseWheel(e);
	//opLock->WaitOne();
	//int newTop = scroll->IndexAtTop - (e->Delta/120);
	int newTop = scroll->Value - (e->Delta/120);
	if (newTop < 0)
	{
		newTop = 0;
	}
	/*if (newTop > scroll->TotalItems-scroll->ViewableItems)
	{
		newTop = scroll->TotalItems-scroll->ViewableItems;
	}*/
	if (newTop > scroll->Maximum - 9)
		newTop = scroll->Maximum - 9;
	//scroll->IndexAtTop = newTop;
	scroll->Value = newTop;
	this->Invalidate();
	//opLock->ReleaseMutex();
}

void TrackList::OnDragEnter(System::Windows::Forms::DragEventArgs ^  e)
{
	__super::OnDragEnter(e);
	if(e->Data->GetDataPresent(TrackListDragDrop::typeid)) {
		TrackListDragDrop^ tldd =static_cast<TrackListDragDrop^>(e->Data->GetData(TrackListDragDrop::typeid));
		e->Effect = System::Windows::Forms::DragDropEffects::Move;
	} else if(e->Data->GetDataPresent(FolderTempStruct::typeid)) {
		e->Effect = System::Windows::Forms::DragDropEffects::Copy;
	} else if(e->Data->GetDataPresent(DataFormats::FileDrop)) {
		e->Effect = System::Windows::Forms::DragDropEffects::All;
	} else
		e->Effect = System::Windows::Forms::DragDropEffects::None;
}

void TrackList::OnDragDrop(System::Windows::Forms::DragEventArgs ^  e)
{
	__super::OnDragDrop(e);
	int index = indexFromY(this->PointToClient(System::Drawing::Point(e->X, e->Y)).Y);
	if(e->Data->GetDataPresent(TrackListDragDrop::typeid))
	{
		TrackListDragDrop^ tldd =static_cast<TrackListDragDrop^>(e->Data->GetData(TrackListDragDrop::typeid));
		if (channel == tldd->fromChannel && !addTo)
		{
			if (index != -1 && index != tldd->fromIndex)
			{
				RequestChange(this, gcnew RequestChangeEventArgs(channel, CHANGE_MOVEINDEX, tldd->fromIndex, index));
			}
		}
		else
		{
			RequestChange(this, gcnew RequestChangeEventArgs(tldd->fromChannel, CHANGE_COPY, tldd->fromIndex, tldd->toChannel));
			if ((e->KeyState & 8) == 0)
			{
				RequestChange(this, gcnew RequestChangeEventArgs(tldd->fromChannel, CHANGE_DELETEINDEX, tldd->fromIndex));
			}
		}
	}
	else if (e->Data->GetDataPresent(FolderTempStruct::typeid))
	{
		FolderTempStruct^ fts =static_cast<FolderTempStruct^>(e->Data->GetData(FolderTempStruct::typeid));
		RequestChange(this, gcnew RequestChangeEventArgs(channel, CHANGE_ADD, fts->fromFolder, fts->fromIndex));
	}
	
	else if(e->Data->GetDataPresent(DataFormats::FileDrop)) {

		array<String^>^ Files = (array<String^>^) e->Data->GetData(DataFormats::FileDrop, false);
		for (int i = 0; i < Files->Length; i++) {
			System::String^ F = Files[i]->ToString();
			
		}
	}
	addTo = false;
	this->Invalidate();
}

void TrackList::OnDragOver(System::Windows::Forms::DragEventArgs ^  e)
{
	__super::OnDragOver(e);
	if(e->Data->GetDataPresent(TrackListDragDrop::typeid))
	{
		if ((e->KeyState & 8) == 0)
		{
			e->Effect = System::Windows::Forms::DragDropEffects::Move;
		}
		else
		{
			e->Effect = System::Windows::Forms::DragDropEffects::Copy;
		}
		TrackListDragDrop^ tldd =static_cast<TrackListDragDrop^>(e->Data->GetData(TrackListDragDrop::typeid));
		tldd->toChannel = channel;
		if (channel == tldd->fromChannel && (e->KeyState & 8) == 0)
		{
			fromIndex = savedFromIndex;
			int yValue = this->PointToClient(System::Drawing::Point(e->X, e->Y)).Y;
			int hi = indexFromY(yValue);
			if (hi != fromIndex)
			{
				tldd->moved = true;
			}
			//if (yValue < 8 && scroll->IndexAtTop != 0)
			if (yValue < 8 && scroll->Value != 0)
			{
				System::Threading::Thread::Sleep(40);
				//scroll->IndexAtTop = scroll->IndexAtTop - 1;
				scroll->Value -= 1;
				this->Invalidate();
			}
			//else if (yValue > this->ClientRectangle.Height-8 && scroll->IndexAtTop != scroll->TotalItems-scroll->ViewableItems)
			// THIS MIGHT BE WRONG!
			else if (yValue > this->ClientRectangle.Height-8 && scroll->Value != 0)
			{
				System::Threading::Thread::Sleep(40);
				//scroll->IndexAtTop = scroll->IndexAtTop + 1;
				scroll->Value += 1;
				this->Invalidate();
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
			addTo = false;
		}
		else
		{
			hoverIndex = -1;
			fromIndex = -1;
			/** item has been moved between channels **/
			if (!addTo)
			{
				addTo = true;
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
	//opLock->WaitOne();
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
	//opLock->ReleaseMutex();

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