#include "StdAfx.h"
#include "LocalConfigDialog.h"
#include "BAPSPresenterMain.h"

using namespace BAPSPresenter;

System::Void LocalConfigDialog::saveButton_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	ConfigManager::setConfigValue("ServerAddress", serverText->Text);
	ConfigManager::setConfigValue("ServerPort", portText->Text);
	ConfigManager::setConfigValue("DefaultUsername", usernameText->Text);
	ConfigManager::setConfigValue("DefaultPassword", passwordText->Text);
	ConfigManager::setConfigValue("ShowVolume", static_cast<System::String^>(showVolumeList->SelectedItem) );
	this->Close();
}


System::Void LocalConfigDialog::cancelButton_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->Close();
}

System::Void LocalConfigDialog::LocalConfigDialog_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	bool ignore = false;
	switch (e->KeyCode)
	{
	case 'O' : /** Ctrl+o opens this window, we don't want another **/
		if (e->Control & e->Shift)
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