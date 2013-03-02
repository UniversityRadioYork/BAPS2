#include "StdAfx.h"
#include "AudioWall.h"
#include "BAPSPresenterMain.h"

using namespace BAPSPresenter;

System::Void AudioWall::AudioWall_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	switch (e->KeyCode)
	{
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
	default:
		{
			MethodInvokerObjKeyEventArgs^ mi = gcnew MethodInvokerObjKeyEventArgs(bapsPresenterMain, &BAPSPresenterMain::BAPSPresenterMain_KeyDown);
			array<System::Object^>^ dd = gcnew array<System::Object^>(2) {bapsPresenterMain, e};
			this->Invoke(mi, dd);
		}
	}
}