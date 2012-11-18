#include "StdAfx.h"
#include "LocalConfigDialog.h"
#include "BAPSPresenterMain.h"

using namespace BAPSPresenter;

System::Void LocalConfigDialog::saveButton_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	if (serverText->Text->Equals("studio1")) ConfigManager::setConfigValue("ServerAddress", "10.0.0.50");
	else if (serverText->Text->Equals("studio2")) ConfigManager::setConfigValue("ServerAddress", "10.0.0.40");
	else if (serverText->Text->Equals("production")) ConfigManager::setConfigValue("ServerAddress", "10.0.0.14");
	else if (serverText->Text->Equals("localhost")) ConfigManager::setConfigValue("ServerAddress", "127.0.0.1");
	else ConfigManager::setConfigValue("ServerAddress", serverText->Text);
	ConfigManager::setConfigValue("ServerPort", portText->Text);
	ConfigManager::setConfigValue("DefaultUsername", usernameText->Text);
	ConfigManager::setConfigValue("DefaultPassword", passwordText->Text);
	ConfigManager::setConfigValue("ShowVolume", static_cast<System::String^>(showVolumeList->SelectedItem) );
	ConfigManager::setConfigValue("EnableTimers", static_cast<System::String^>(enableTimersList->SelectedItem) );
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