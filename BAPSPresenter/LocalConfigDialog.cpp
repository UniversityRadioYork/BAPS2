#include "StdAfx.h"
#include "LocalConfigDialog.h"

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