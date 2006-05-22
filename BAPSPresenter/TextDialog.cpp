#include "StdAfx.h"
#include "TextDialog.h"
#include "BAPSPresenterMain.h"

#undef MessageBox
using namespace BAPSPresenter;

System::Void TextDialog::TextDialog_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	MethodInvokerObjKeyEventArgs^ mi = gcnew MethodInvokerObjKeyEventArgs(bapsPresenterMain, &BAPSPresenterMain::BAPSPresenterMain_KeyDown);
	array<System::Object^>^ dd = gcnew array<System::Object^>(2) {bapsPresenterMain, e};
	this->Invoke(mi, dd);
}
void TextDialog::scroll(System::Object^ _updown)
{
	int updown = safe_cast<int>(_updown);

	System::Drawing::Point pnt;
	if (updown == 0)
	{
		/** Down **/
		pnt = System::Drawing::Point(0,textText->ClientSize.Height-1);
	}
	else
	{
		/** Up **/
		pnt = System::Drawing::Point(0,0);
	}
	int charIndex = textText->GetCharIndexFromPosition(pnt);
	textText->SelectionStart = charIndex;
	textText->SelectionLength = 0;
	textText->ScrollToCaret();
}
void TextDialog::textSize(System::Object^ _updown)
{
	int updown = safe_cast<int>(_updown);

	System::Drawing::Point pnt;
	if (updown == 0)
	{
		/** Smaller **/
		if (textText->Font->Size > 12)
		{
			textText->Font = gcnew System::Drawing::Font(textText->Font->FontFamily, textText->Font->Size-1);
		}
	}
	else
	{
		/** Bigger **/
		if (textText->Font->Size < 40)
		{
			textText->Font = gcnew System::Drawing::Font(textText->Font->FontFamily, textText->Font->Size+1);
		}
	}
}