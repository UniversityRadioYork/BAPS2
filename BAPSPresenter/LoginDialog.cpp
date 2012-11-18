#include "StdAfx.h"
#include "LoginDialog.h"

using namespace BAPSPresenter;
#undef MessageBox

System::Void LoginDialog::loginButton_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	/** Blank usernames are not permitted **/
	if (usernameText->Text->Length == 0)
	{
		System::Windows::Forms::MessageBox::Show("You must enter a username", "Incomplete login:", System::Windows::Forms::MessageBoxButtons::OK);
	}
	else
	{
	if (serverText->Text->Equals("studio1")) serverText->Text = "10.0.0.50";
	else if (serverText->Text->Equals("studio2")) serverText->Text = "10.0.0.40";
	else if (serverText->Text->Equals("production")) serverText->Text = "10.0.0.14";
	else if (serverText->Text->Equals("localhost")) serverText->Text = "127.0.0.1";

		/** Increment the attempt counter so the first attempt is the only
			one that causes a connection to the server to be made, (unless
			the server details are altered
		**/
		loginAttempt++;
		/** Set OK as the result as cancel will terminate the client **/
		DialogResult = System::Windows::Forms::DialogResult::OK;
		Close();
	}
}

System::Void LoginDialog::cancelButton_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	/** This will in effect end the application **/
	DialogResult = System::Windows::Forms::DialogResult::Cancel;
	Close();
}

System::Void LoginDialog::connectionText_TextChanged(System::Object ^  sender, System::EventArgs ^  e)
{
	/** If the server or port change then the connection must be dropped the the current server **/
	connectionChanged = true;
	/** Validate the port number **/
	try 
	{
		int port = getPort();
		if (port < 1 || port > 65535)
		{
			throw gcnew System::Exception("Port out of range");
		}
	}
	catch (System::Exception^)
	{
		System::Windows::Forms::MessageBox::Show("You must enter a number (1-65535).", "Port error:", System::Windows::Forms::MessageBoxButtons::OK);
		portText->Text = "1350";
	}
}
System::Void LoginDialog::LoginDialog_Load(System::Object ^  sender, System::EventArgs ^  e)
{
	/** On showing the form we reset the flag so that we dont reconnect next attempt **/
	connectionChanged = false;
	serverText->Focus();
}

System::Void LoginDialog::Textbox_Enter(System::Object^  sender, System::EventArgs^  e)
{
	System::Windows::Forms::TextBox^ tb = safe_cast<System::Windows::Forms::TextBox^>(sender);
	tb->SelectAll();
}

