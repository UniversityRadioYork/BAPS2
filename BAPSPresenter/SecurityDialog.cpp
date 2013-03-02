#include "StdAfx.h"
#include "SecurityDialog.h"
#include "UtilityMacros.h"
#undef MessageBox
using namespace BAPSPresenter;


void SecurityDialog::receiveUserCount(System::Object^ _count)
{

	grantButton->Enabled = false;
	revokeButton->Enabled = false;
	availablePermissionList->Enabled = false;
	permissionList->Enabled = false;
	newPasswordText->Enabled = false;
	newPasswordText->Text = "12345";
	confirmNewPasswordText->Enabled = false;
	confirmNewPasswordText->Text = "12345";
	setPasswordButton->Enabled = false;
	deleteUserButton->Enabled = false;
	selectedUserLabel->Text = "<Select User>";
	permissionList->Items->Clear();
	availablePermissionList->Items->Clear();

	userList->Enabled = false;
	userList->Items->Clear();
	userCount = safe_cast<int>(_count);
	if (userCount == 0)
	{
		status = SD_DORMANT;
		userList->Enabled=true;
	}
}
void SecurityDialog::receiveUserInfo(System::String^ username, System::Object^ _permissions)
{
	int permissions = safe_cast<int>(_permissions);
	userList->Items->Add(gcnew UserInfo(username, permissions));
	userCount--;
	if (userCount == 0)
	{
		status = SD_DORMANT;
		userList->Enabled=true;
	}
}
void SecurityDialog::receivePermissionCount(System::Object^ _count)
{
	permissionCount = safe_cast<int>(_count);
	permissionInfo = gcnew array<PermissionInfo^>(permissionCount);
}
void SecurityDialog::receivePermissionInfo(System::Object^ _permissionCode, System::String^ description)
{
	int permissionCode = safe_cast<int>(_permissionCode);
	permissionInfo[permissionInfo->Length-permissionCount] = gcnew PermissionInfo(permissionCode, description);
	permissionCount--;

	if (permissionCount == 0)
	{
		status = SD_GETUSERS;
		Command cmd = BAPSNET_CONFIG | BAPSNET_GETUSERS;
		msgQueue->Enqueue(gcnew ActionMessage(cmd));
	}
}
void SecurityDialog::receiveUserResult(System::Object^ _resultCode, System::String^ description)
{
	SecurityStatus tempStatus = SD_DORMANT;
	int resultCode = safe_cast<int>(_resultCode);
	switch (status)
	{
	case SD_AWAITING_INIT:
	case SD_GETUSERS:
		System::Windows::Forms::MessageBox::Show(System::String::Concat("Cannot open Security Manager, reason: ", description), "Error:", System::Windows::Forms::MessageBoxButtons::OK);
		this->Close();
		break;
	case SD_DORMANT:
		System::Windows::Forms::MessageBox::Show("A recoverable error has occurred, this dialog will be closed. (Result rcvd but no cmd issued)", "Error:", System::Windows::Forms::MessageBoxButtons::OK);
		this->Close();
		break;
	case SD_ADDUSER:
		if (resultCode == 0)
		{
			newUsernameText->Text="";
			passwordText->Text="";
			confirmPasswordText->Text="";
			addUserButton->Enabled=true;
			tempStatus = SD_GETUSERS;
			status = SD_GETUSERS;
			Command cmd = BAPSNET_CONFIG | BAPSNET_GETUSERS;
			msgQueue->Enqueue(gcnew ActionMessage(cmd));
		}
		else
		{
			System::Windows::Forms::MessageBox::Show(System::String::Concat("Cannot add user, reason: ", description), "Error:", System::Windows::Forms::MessageBoxButtons::OK);
		}
		break;
	case SD_SETPASSWORD:
		if (resultCode == 0)
		{
			newPasswordText->Text="12345";
			confirmNewPasswordText->Text="12345";
			setPasswordButton->Enabled=true;
		}
		else
		{
			System::Windows::Forms::MessageBox::Show(System::String::Concat("Cannot set password, reason: ", description), "Error:", System::Windows::Forms::MessageBoxButtons::OK);
		}
		break;
	case SD_REMOVEUSER:
		if (resultCode == 0)
		{
			tempStatus = SD_GETUSERS;
			status = SD_GETUSERS;
			Command cmd = BAPSNET_CONFIG | BAPSNET_GETUSERS;
			msgQueue->Enqueue(gcnew ActionMessage(cmd));
		}
		else
		{
			System::Windows::Forms::MessageBox::Show(System::String::Concat("Cannot delete user, reason: ", description), "Error:", System::Windows::Forms::MessageBoxButtons::OK);
		}
		break;
	case SD_REVOKEPERMISSION:
		if (resultCode == 0)
		{
			tempStatus = SD_GETUSERS;
			status = SD_GETUSERS;
			Command cmd = BAPSNET_CONFIG | BAPSNET_GETUSERS;
			msgQueue->Enqueue(gcnew ActionMessage(cmd));
		}
		else
		{
			System::Windows::Forms::MessageBox::Show(System::String::Concat("Cannot revoke permission, reason: ", description), "Error:", System::Windows::Forms::MessageBoxButtons::OK);
		}
		break;
	case SD_GRANTPERMISSION:
		if (resultCode == 0)
		{
			tempStatus = SD_GETUSERS;
			status = SD_GETUSERS;
			Command cmd = BAPSNET_CONFIG | BAPSNET_GETUSERS;
			msgQueue->Enqueue(gcnew ActionMessage(cmd));
		}
		else
		{
			System::Windows::Forms::MessageBox::Show(System::String::Concat("Cannot grant permission, reason: ", description), "Error:", System::Windows::Forms::MessageBoxButtons::OK);
		}
		break;
	}
	status = tempStatus;
}
System::Void SecurityDialog::refreshButton_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	if (status == SD_DORMANT)
	{
		addUserButton->Enabled=false;
		status = SD_GETUSERS;
		Command cmd = BAPSNET_CONFIG | BAPSNET_GETUSERS;
		msgQueue->Enqueue(gcnew ActionMessage(cmd));
	}
	else
	{
		System::Windows::Forms::MessageBox::Show("A command is still being processed please wait and try again", "Notice:", System::Windows::Forms::MessageBoxButtons::OK);
	}
}
System::Void SecurityDialog::deleteUserButton_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	if (status == SD_DORMANT)
	{
		System::Windows::Forms::DialogResult dr;
		dr = System::Windows::Forms::MessageBox::Show("Are you sure you wish to delete the selcted user?", "Notice:", System::Windows::Forms::MessageBoxButtons::YesNo);
		if (dr == System::Windows::Forms::DialogResult::Yes)
		{
			status = SD_REMOVEUSER;
			Command cmd = BAPSNET_CONFIG | BAPSNET_REMOVEUSER;
			msgQueue->Enqueue(gcnew ActionMessageString(cmd, selectedUserLabel->Text));
		}
	}
	else
	{
		System::Windows::Forms::MessageBox::Show("A command is still being processed please wait and try again", "Notice:", System::Windows::Forms::MessageBoxButtons::OK);
	}
}
System::Void SecurityDialog::newUserText_Leave(System::Object ^  sender, System::EventArgs ^  e)
{
	bool valid = (newUsernameText->Text->Length>0 &&
				  System::String::Compare(passwordText->Text, confirmPasswordText->Text) == 0);
	addUserButton->Enabled = valid;
	if (!valid)
	{
		newUsernameLabel->ForeColor = System::Drawing::Color::Red;
		confirmPasswordLabel->ForeColor = System::Drawing::Color::Red;
	}
	else
	{
		newUsernameLabel->ForeColor = System::Drawing::SystemColors::ControlText;
		confirmPasswordLabel->ForeColor = System::Drawing::SystemColors::ControlText;
	}
}
System::Void SecurityDialog::changePassword_TextChanged(System::Object ^  sender, System::EventArgs ^  e)
{
	bool valid = (System::String::Compare(newPasswordText->Text, confirmNewPasswordText->Text) == 0);
	setPasswordButton->Enabled = valid;
	if (!valid)
	{
		confirmNewPasswordLabel->ForeColor = System::Drawing::Color::Red;
	}
	else
	{
		confirmNewPasswordLabel->ForeColor = System::Drawing::SystemColors::ControlText;
	}
}
System::Void SecurityDialog::addUserButton_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	if (status == SD_DORMANT)
	{
		addUserButton->Enabled=false;
		status = SD_ADDUSER;
		Command cmd = BAPSNET_CONFIG | BAPSNET_ADDUSER;
		msgQueue->Enqueue(gcnew ActionMessageStringString(cmd, newUsernameText->Text, passwordText->Text));
	}
	else
	{
		System::Windows::Forms::MessageBox::Show("A command is still being processed please wait and try again", "Notice:", System::Windows::Forms::MessageBoxButtons::OK);
	}
}
System::Void SecurityDialog::setPasswordButton_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	if (status == SD_DORMANT)
	{
		setPasswordButton->Enabled=false;
		status = SD_SETPASSWORD;
		Command cmd = BAPSNET_CONFIG | BAPSNET_SETPASSWORD;
		msgQueue->Enqueue(gcnew ActionMessageStringString(cmd, selectedUserLabel->Text, newPasswordText->Text));
	}
	else
	{
		System::Windows::Forms::MessageBox::Show("A command is still being processed please wait and try again", "Notice:", System::Windows::Forms::MessageBoxButtons::OK);
	}
}
System::Void SecurityDialog::userList_SelectedIndexChanged(System::Object ^  sender, System::EventArgs ^  e)
{
	grantButton->Enabled = false;
	revokeButton->Enabled = false;
	availablePermissionList->Enabled = false;
	permissionList->Enabled = false;
	newPasswordText->Enabled = false;
	newPasswordText->Text = "12345";
	confirmNewPasswordText->Enabled = false;
	confirmNewPasswordText->Text = "12345";
	setPasswordButton->Enabled = false;
	deleteUserButton->Enabled = false;

	UserInfo^ userInfo;
	if (userList->SelectedIndex != -1)
	{
		userInfo = static_cast<UserInfo^>(userList->Items[userList->SelectedIndex]);
	}
	else
	{
		userInfo = gcnew UserInfo("<None>", 0);
	}
	selectedUserLabel->Text = userInfo->username;
	int permissions = userInfo->permissions;
	permissionList->Items->Clear();
	availablePermissionList->Items->Clear();
	int i;
	for (i = 0 ; i < permissionInfo->Length ; i++)
	{
		if (ISFLAGSET(permissions, permissionInfo[i]->permissionCode))
		{
			permissionList->Items->Add(permissionInfo[i]);
		}
		else
		{
			availablePermissionList->Items->Add(permissionInfo[i]);
		}
	}
	availablePermissionList->Enabled = true;
	permissionList->Enabled = true;
	newPasswordText->Enabled = true;
	confirmNewPasswordText->Enabled = true;
	deleteUserButton->Enabled = true;
}

System::Void SecurityDialog::permissionList_SelectedIndexChanged(System::Object ^  sender, System::EventArgs ^  e)
{
	revokeButton->Enabled = (permissionList->SelectedIndex != -1);
}
System::Void SecurityDialog::availablePermissionList_SelectedIndexChanged(System::Object ^  sender, System::EventArgs ^  e)
{
	grantButton->Enabled = (availablePermissionList->SelectedIndex != -1);
}
System::Void SecurityDialog::revokeButton_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	if (status == SD_DORMANT)
	{
		status = SD_REVOKEPERMISSION;
		int permission = static_cast<PermissionInfo^>(permissionList->Items[permissionList->SelectedIndex])->permissionCode;
		Command cmd = BAPSNET_CONFIG | BAPSNET_REVOKEPERMISSION;
		msgQueue->Enqueue(gcnew ActionMessageStringU32int(cmd, selectedUserLabel->Text, permission));
	}
	else
	{
		System::Windows::Forms::MessageBox::Show("A command is still being processed please wait and try again", "Notice:", System::Windows::Forms::MessageBoxButtons::OK);
	}
}
System::Void SecurityDialog::grantButton_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	if (status == SD_DORMANT)
	{
		status = SD_GRANTPERMISSION;
		int permission = static_cast<PermissionInfo^>(availablePermissionList->Items[availablePermissionList->SelectedIndex])->permissionCode;
		Command cmd = BAPSNET_CONFIG | BAPSNET_GRANTPERMISSION;
		msgQueue->Enqueue(gcnew ActionMessageStringU32int(cmd, selectedUserLabel->Text, permission));
	}
	else
	{
		System::Windows::Forms::MessageBox::Show("A command is still being processed please wait and try again", "Notice:", System::Windows::Forms::MessageBoxButtons::OK);
	}
}

void SecurityDialog::receiveIPDenyCount(System::Object^ _count)
{
	denyCount = safe_cast<int>(_count);
	deniedIPList->Enabled=false;
	deniedIPList->Items->Clear();
	if (denyCount == 0)
	{
		if (status == SD_GETIPRESTRICTIONS)
		{
			status = SD_GETIPRESTRICTIONS2;
		}
		else
		{
			status = SD_DORMANT;
		}
		deniedIPList->Enabled=true;
	}
}
void SecurityDialog::receiveIPAllowCount(System::Object^ _count)
{
	allowCount = safe_cast<int>(_count);
	allowedIPList->Enabled=false;
	allowedIPList->Items->Clear();
	if (allowCount == 0)
	{
		if (status == SD_GETIPRESTRICTIONS)
		{
			status = SD_GETIPRESTRICTIONS2;
		}
		else
		{
			status = SD_DORMANT;
		}
		allowedIPList->Enabled=true;
	}
}
void SecurityDialog::receiveIPDeny(System::String^ ipaddress, System::Object^ _mask)
{
	int mask = safe_cast<int>(_mask);
	deniedIPList->Items->Add(gcnew IPRestriction(ipaddress, mask));
	denyCount--;
	if (denyCount == 0)
	{
		if (status == SD_GETIPRESTRICTIONS)
		{
			status = SD_GETIPRESTRICTIONS2;
		}
		else
		{
			status = SD_DORMANT;
		}
		deniedIPList->Enabled=true;
	}
}
void SecurityDialog::receiveIPAllow(System::String^ ipaddress, System::Object^ _mask)
{
	int mask = safe_cast<int>(_mask);
	allowedIPList->Items->Add(gcnew IPRestriction(ipaddress, mask));
	allowCount--;
	if (allowCount == 0)
	{
		if (status == SD_GETIPRESTRICTIONS)
		{
			status = SD_GETIPRESTRICTIONS2;
		}
		else
		{
			status = SD_DORMANT;
		}
		allowedIPList->Enabled=true;
	}
}
System::Void SecurityDialog::securityPageControl_SelectedIndexChanged(System::Object ^  sender, System::EventArgs ^  e)
{
	if (securityPageControl->SelectedTab == userManagerPage)
	{
		if (status == SD_DORMANT)
		{
			status = SD_GETUSERS;
			Command cmd = BAPSNET_CONFIG | BAPSNET_GETUSERS;
			msgQueue->Enqueue(gcnew ActionMessage(cmd));
		}
		else
		{
			System::Windows::Forms::MessageBox::Show("A command is still being processed please wait and use the refresh button to update the form.", "Notice:", System::Windows::Forms::MessageBoxButtons::OK);
		}
	}
	else if (securityPageControl->SelectedTab == connectionManagerPage)
	{
		if (status == SD_DORMANT)
		{
			status = SD_GETIPRESTRICTIONS;
			Command cmd = BAPSNET_CONFIG | BAPSNET_GETIPRESTRICTIONS;
			msgQueue->Enqueue(gcnew ActionMessage(cmd));
		}
		else
		{
			System::Windows::Forms::MessageBox::Show("A command is still being processed please wait and use the refresh button to update the form.", "Notice:", System::Windows::Forms::MessageBoxButtons::OK);
		}
	}
}
void SecurityDialog::receiveConfigError(System::Object^ _resultCode, System::String^ description)
{
	int resultCode = safe_cast<int>(_resultCode);
	if (resultCode != 0)
	{
		System::Windows::Forms::MessageBox::Show(System::String::Concat("Unable to alter IP list, reason: ", description), "Error:", System::Windows::Forms::MessageBoxButtons::OK);
	}
	status = SD_GETIPRESTRICTIONS;
	Command cmd = BAPSNET_CONFIG | BAPSNET_GETIPRESTRICTIONS;
	msgQueue->Enqueue(gcnew ActionMessage(cmd));
}
System::Void SecurityDialog::alterRestrictionButton_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	if (status == SD_DORMANT)
	{
		try
		{
			int cmdMask = safe_cast<int>(static_cast<System::Windows::Forms::Button^>(sender)->Tag);
			status = SD_ALTERIPRESTRICTION;
			Command cmd = BAPSNET_CONFIG | BAPSNET_ALTERIPRESTRICTION | cmdMask;
			msgQueue->Enqueue(gcnew ActionMessageStringU32int(cmd, ipAddressText->Text, (u32int)System::Convert::ToInt32(maskText->Text)));
		}
		catch (System::FormatException^ )
		{
			System::Windows::Forms::MessageBox::Show("The mask value must be an integer.", "Error:", System::Windows::Forms::MessageBoxButtons::OK);
			status = SD_DORMANT;
		}
	}
	else
	{
		System::Windows::Forms::MessageBox::Show("A command is still being processed please wait and use the refresh button to update the form.", "Notice:", System::Windows::Forms::MessageBoxButtons::OK);
	}
}

System::Void SecurityDialog::SecurityDialog_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	bool ignore = false;
	switch (e->KeyCode)
	{
	case 'S' : /** Ctrl+s opens this window, we don't want another **/
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