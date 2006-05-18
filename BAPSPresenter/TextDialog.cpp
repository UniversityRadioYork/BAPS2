#include "StdAfx.h"
#include "TextDialog.h"

using namespace BAPSPresenter;

System::Void TextDialog::TextDialog_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	switch (e->KeyCode)
	{
	case Keys::F4:
	if (e->Alt)
	{
		e->Handled = true;
	}
	break;
	case 'N':
		if (e->Control)
		{
			if (e->Shift)
			{
				toggleMaximize();
			}
			else
			{
				this->Hide();
			}
			e->Handled = true;
		}
		break;
	}
}