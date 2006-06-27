#include "StdAfx.h"
#include "About.h"

using namespace BAPSPresenter;

System::Void About::About_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	bool ignore = false;
	switch (e->KeyCode)
	{
	case 'A' : /** Ctrl+a opens this window, we don't want another **/
		if (e->Control)
		{
			ignore = true;
		}
	}
	if (!ignore)
	{
		MethodInvokerObjKeyEventArgs^ mi = gcnew MethodInvokerObjKeyEventArgs(bapsPresenterMain, &BAPSPresenterMain::BAPSPresenterMain_KeyDown);
		array<System::Object^>^ dd = gcnew array<System::Object^>(2) {bapsPresenterMain, e};
		this->Invoke(mi, dd);
	}
}