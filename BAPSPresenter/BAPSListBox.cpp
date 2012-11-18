#include "StdAfx.h"
#include "BAPSListBox.h"
#include "ClientHelpers.h"
using namespace BAPSPresenter;

void BAPSListBox::OnPaint(System::Windows::Forms::PaintEventArgs^ e)
{
    // The base class contains a bitmap, offScreen, for constructing
    // the control and is rendered when all items are populated.
    // This technique prevents flicker.
	System::Drawing::Graphics^ gOffScreen = System::Drawing::Graphics::FromImage(offScreen);
	System::Drawing::Rectangle rect = this->ClientRectangle;
	if (rect.Width > 2) {rect.Width-=2;} //If added 270412 By lpw
	rect.Height = ((items->Count<scroll->IndexAtTop+DrawCount)?items->Count:scroll->IndexAtTop+DrawCount);
	gOffScreen->FillRectangle(System::Drawing::Brushes::LightGray, rect);
	if (rect.Height < 0) rect.Height = 0; //Line added 270412 By lpw
	rect.Y = rect.Height;
	rect.Height = this->ClientRectangle.Height-rect.Height;
	if (rect.Height > 0)
	{
		gOffScreen->FillRectangle(System::Drawing::Brushes::SeaShell, rect);
	}
    int itemTop = 0;

    // Draw the fonts in the list.
	for(int n = scroll->IndexAtTop; n < ((items->Count<scroll->IndexAtTop+DrawCount)?items->Count:scroll->IndexAtTop+DrawCount); n++)
	{

		System::Drawing::Brush^ brush;
		System::Drawing::Rectangle rect;
		if (n == selectedIndex && SelectedIndexEnabled)
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
		//Altered clientWidth specification 270412 By lpw
		int clientWidth = this->ClientSize.Width - (scroll->Visible ? scroll->Width : 2)-1;
		if (clientWidth < 0) clientWidth = 0;
		rect = System::Drawing::Rectangle(0,
										  itemTop,
										  // If the scroll bar is visible, subtract the scrollbar width
										  // otherwise subtract 2 for the width of the rectangle
										  clientWidth,
										  ItemHeight-1);
		gOffScreen->FillRectangle(brush,rect);

        // Draw the item
		gOffScreen->DrawString(items[n]->ToString(), this->Font, System::Drawing::Brushes::Black, (float)2, (float)itemTop);

        itemTop += this->ItemHeight;
    }
	// if we are adding to this control
	if (this->Focused)
	{
		System::Drawing::Rectangle rect = this->ClientRectangle;
		//If added 270412 By lpw
		if (rect.Height > 3) {
			rect.Height-=3;
		}
		
		if (rect.Width > 2) rect.Width-= (scroll->Visible)?2:3; //If added 270412 By lpw
		if (scroll->Visible)
		{
			rect.Width -= scroll->Width;
		}
		gOffScreen->DrawRectangle(System::Drawing::Pens::DarkOrange, rect);
		rect.X++;
		rect.Y++;
		if (rect.Height > 2) rect.Height-=2; //If added 270412 By lpw
		if (rect.Width > 2) rect.Width-=2; //If added 270412 By lpw
		gOffScreen->DrawRectangle(System::Drawing::Pens::DarkOrange, rect);
	}

    e->Graphics->DrawImage(offScreen, 1, 1);

    delete gOffScreen;
}
void BAPSListBox::OnMouseWheel(System::Windows::Forms::MouseEventArgs^ e)
{
	__super::OnMouseWheel(e);
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
}
void BAPSListBox::OnKeyDown(System::Windows::Forms::KeyEventArgs^ e)
{
	e->Handled = HandleKey(e->KeyCode);
	if (!e->Handled)
	{
		__super::OnKeyDown(e);
	}
}

bool BAPSListBox::ProcessDialogKey(System::Windows::Forms::Keys keyData)
{
	bool retVal = HandleKey(keyData);
	if (!retVal)
	{
		__super::ProcessDialogKey(keyData);
	}
	return retVal;
}

bool BAPSListBox::HandleKey(System::Windows::Forms::Keys keyData)
{
	bool retVal = false;
	switch(keyData)
	{
	case Keys::Down:
		if(SelectedIndex < (items->Count-1))
		{
			SelectedIndex = SelectedIndex+1;
		}
		retVal = true;
		break;
	case Keys::Up:
		if(SelectedIndex > 0)
		{
			SelectedIndex =  SelectedIndex-1;
		}
		retVal = true;
		break;
	case Keys::PageDown:
		SelectedIndex = Math::Min(items->Count-1, SelectedIndex + DrawCount);
		retVal = true;
		break;
	case Keys::PageUp:
		SelectedIndex = Math::Max(0, SelectedIndex - DrawCount);
		retVal = true;
		break;
	case Keys::Home:
		SelectedIndex = 0;
		retVal = true;
		break;
	case Keys::End:
		SelectedIndex = items->Count - 1;
		retVal = true;
		break;
	}
	return retVal;
}

void BAPSListBox::OnMouseDown(System::Windows::Forms::MouseEventArgs^ e)
{
	__super::OnMouseDown(e);
	SelectedIndex = indexFromY(e->Y);
}