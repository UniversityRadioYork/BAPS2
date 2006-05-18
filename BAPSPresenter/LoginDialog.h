#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#include "ConfigManager.h"
#include "BAPSButton.h"

/**
	The LoginDialog is the entry point of the Client Application and deals with
	obtaining server connection details and login details from the client
**/

namespace BAPSPresenter {

	/// <summary>
	/// Summary for LoginDialog
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class LoginDialog : public System::Windows::Forms::Form
	{
	public:
		LoginDialog(void)
		{
			InitializeComponent();
			/** flag to determine if the connection details have been changed
				since the last login/connection attempt
			**/
			connectionChanged = false;
			/** A counter to determine how many times we have attempted connection
				Currently used just to indicate that the first attempt needs
				to connect to the server even if the server details are not altered
			**/
			loginAttempt = 0;
			/** Get the default server and port from the config system **/
			serverText->Text = ConfigManager::getConfigValueString("ServerAddress", "127.0.0.1");
			portText->Text = ConfigManager::getConfigValueString("ServerPort", "1350");
			/** Get the default username and password from the config system **/
			usernameText->Text = ConfigManager::getConfigValueString("DefaultUsername", "");
			passwordText->Text = ConfigManager::getConfigValueString("DefaultPassword", "");
			this->BackColor = System::Drawing::Color::AliceBlue;
		}
		/** If this is the first time we have attempted to connect or if
			the user has altered the server details, the connection must be
			recreated.
		**/
		bool needsToConnect()
		{
			return (loginAttempt==1) || connectionChanged;
		}
		/** Accessor for server text **/
		System::String^ getServer()
		{
			return serverText->Text;
		}
		/** Accessor for port number **/
		int getPort()
		{
			return System::Convert::ToInt32(portText->Text);
		}
		/** Accessor for username **/
		System::String^ getUsername()
		{
			return usernameText->Text;
		}
		/** Accessor for password **/
		System::String^ getPassword()
		{
			return passwordText->Text;
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~LoginDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		/** Flag for when the connection details get changed **/
		bool connectionChanged;




	private: System::Windows::Forms::Label^  passwordLabel;
	private: System::Windows::Forms::TextBox^  passwordText;
	private: System::Windows::Forms::TextBox^  usernameText;
	private: System::Windows::Forms::Label^  usernameLabel;
	private: BAPSPresenter::BAPSButton^  loginButton;
	private: BAPSPresenter::BAPSButton^  cancelButton;
	private: System::Windows::Forms::GroupBox^  serverDetails;

	private: System::Windows::Forms::Label^  portLabel;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  portText;
	private: System::Windows::Forms::TextBox^  serverText;
	private: System::Windows::Forms::HelpProvider^  helpProvider1;
	private: BAPSPresenter::BAPSButton^  expandButton;


			 /** Counter for login attempts **/
		int loginAttempt;

		System::Void loginButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void cancelButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void LoginDialog_Load(System::Object ^  sender, System::EventArgs ^  e);
		System::Void connectionText_TextChanged(System::Object ^  sender, System::EventArgs ^  e);
		System::Void Textbox_Enter(System::Object^  sender, System::EventArgs^  e);
		System::Void expandButton_Click(System::Object^  sender, System::EventArgs^  e);

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(LoginDialog::typeid));
			this->passwordLabel = (gcnew System::Windows::Forms::Label());
			this->passwordText = (gcnew System::Windows::Forms::TextBox());
			this->usernameText = (gcnew System::Windows::Forms::TextBox());
			this->usernameLabel = (gcnew System::Windows::Forms::Label());
			this->serverDetails = (gcnew System::Windows::Forms::GroupBox());
			this->portLabel = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->portText = (gcnew System::Windows::Forms::TextBox());
			this->serverText = (gcnew System::Windows::Forms::TextBox());
			this->helpProvider1 = (gcnew System::Windows::Forms::HelpProvider());
			this->expandButton = (gcnew BAPSPresenter::BAPSButton());
			this->cancelButton = (gcnew BAPSPresenter::BAPSButton());
			this->loginButton = (gcnew BAPSPresenter::BAPSButton());
			this->serverDetails->SuspendLayout();
			this->SuspendLayout();
			// 
			// passwordLabel
			// 
			this->passwordLabel->BackColor = System::Drawing::Color::Transparent;
			this->passwordLabel->Location = System::Drawing::Point(9, 45);
			this->passwordLabel->Name = L"passwordLabel";
			this->passwordLabel->Size = System::Drawing::Size(64, 16);
			this->passwordLabel->TabIndex = 16;
			this->passwordLabel->Text = L"Password:";
			// 
			// passwordText
			// 
			this->passwordText->BackColor = System::Drawing::Color::SeaShell;
			this->passwordText->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->passwordText->Location = System::Drawing::Point(73, 45);
			this->passwordText->Name = L"passwordText";
			this->passwordText->PasswordChar = '*';
			this->passwordText->Size = System::Drawing::Size(112, 20);
			this->passwordText->TabIndex = 1;
			this->passwordText->Enter += gcnew System::EventHandler(this, &LoginDialog::connectionText_TextChanged);
			// 
			// usernameText
			// 
			this->usernameText->BackColor = System::Drawing::Color::SeaShell;
			this->usernameText->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->usernameText->Location = System::Drawing::Point(73, 21);
			this->usernameText->Name = L"usernameText";
			this->usernameText->Size = System::Drawing::Size(112, 20);
			this->usernameText->TabIndex = 0;
			this->usernameText->Enter += gcnew System::EventHandler(this, &LoginDialog::Textbox_Enter);
			// 
			// usernameLabel
			// 
			this->usernameLabel->BackColor = System::Drawing::Color::Transparent;
			this->usernameLabel->Location = System::Drawing::Point(9, 21);
			this->usernameLabel->Name = L"usernameLabel";
			this->usernameLabel->Size = System::Drawing::Size(64, 16);
			this->usernameLabel->TabIndex = 17;
			this->usernameLabel->Text = L"Username:";
			// 
			// serverDetails
			// 
			this->serverDetails->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"serverDetails.BackgroundImage")));
			this->serverDetails->Controls->Add(this->portLabel);
			this->serverDetails->Controls->Add(this->label1);
			this->serverDetails->Controls->Add(this->portText);
			this->serverDetails->Controls->Add(this->serverText);
			this->serverDetails->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->serverDetails->Location = System::Drawing::Point(10, 3);
			this->serverDetails->Name = L"serverDetails";
			this->serverDetails->Size = System::Drawing::Size(177, 70);
			this->serverDetails->TabIndex = 5;
			this->serverDetails->TabStop = false;
			this->serverDetails->Text = L"Server Details";
			this->serverDetails->Visible = false;
			// 
			// portLabel
			// 
			this->portLabel->BackColor = System::Drawing::Color::Transparent;
			this->portLabel->Location = System::Drawing::Point(11, 43);
			this->portLabel->Name = L"portLabel";
			this->portLabel->Size = System::Drawing::Size(76, 16);
			this->portLabel->TabIndex = 13;
			this->portLabel->Text = L"Port:";
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Location = System::Drawing::Point(11, 19);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(80, 16);
			this->label1->TabIndex = 12;
			this->label1->Text = L"Server Name:";
			// 
			// portText
			// 
			this->portText->BackColor = System::Drawing::Color::SeaShell;
			this->portText->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->portText->Location = System::Drawing::Point(91, 43);
			this->portText->Name = L"portText";
			this->portText->Size = System::Drawing::Size(80, 20);
			this->portText->TabIndex = 7;
			this->portText->Text = L"1350";
			this->portText->Enter += gcnew System::EventHandler(this, &LoginDialog::Textbox_Enter);
			this->portText->TextChanged += gcnew System::EventHandler(this, &LoginDialog::connectionText_TextChanged);
			// 
			// serverText
			// 
			this->serverText->BackColor = System::Drawing::Color::SeaShell;
			this->serverText->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->serverText->Location = System::Drawing::Point(91, 19);
			this->serverText->Name = L"serverText";
			this->serverText->Size = System::Drawing::Size(80, 20);
			this->serverText->TabIndex = 6;
			this->serverText->Text = L"127.0.0.1";
			this->serverText->Enter += gcnew System::EventHandler(this, &LoginDialog::Textbox_Enter);
			this->serverText->TextChanged += gcnew System::EventHandler(this, &LoginDialog::connectionText_TextChanged);
			// 
			// expandButton
			// 
			this->expandButton->BackColor = System::Drawing::Color::Transparent;
			this->expandButton->DialogResult = System::Windows::Forms::DialogResult::None;
			this->expandButton->HighlightColor = System::Drawing::Color::Red;
			this->expandButton->Highlighted = false;
			this->expandButton->Location = System::Drawing::Point(193, 3);
			this->expandButton->Name = L"expandButton";
			this->expandButton->Size = System::Drawing::Size(12, 12);
			this->expandButton->TabIndex = 4;
			this->expandButton->Text = L"+";
			this->expandButton->Click += gcnew System::EventHandler(this, &LoginDialog::expandButton_Click);
			// 
			// cancelButton
			// 
			this->cancelButton->BackColor = System::Drawing::Color::Transparent;
			this->cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->cancelButton->HighlightColor = System::Drawing::Color::Red;
			this->cancelButton->Highlighted = false;
			this->cancelButton->Location = System::Drawing::Point(118, 81);
			this->cancelButton->Name = L"cancelButton";
			this->cancelButton->Size = System::Drawing::Size(69, 19);
			this->cancelButton->TabIndex = 3;
			this->cancelButton->Text = L"Cancel";
			this->cancelButton->Click += gcnew System::EventHandler(this, &LoginDialog::cancelButton_Click);
			// 
			// loginButton
			// 
			this->loginButton->BackColor = System::Drawing::Color::Transparent;
			this->loginButton->DialogResult = System::Windows::Forms::DialogResult::None;
			this->loginButton->HighlightColor = System::Drawing::Color::Red;
			this->loginButton->Highlighted = false;
			this->loginButton->Location = System::Drawing::Point(10, 81);
			this->loginButton->Name = L"loginButton";
			this->loginButton->Size = System::Drawing::Size(69, 19);
			this->loginButton->TabIndex = 2;
			this->loginButton->Text = L"Login";
			this->loginButton->Click += gcnew System::EventHandler(this, &LoginDialog::loginButton_Click);
			// 
			// LoginDialog
			// 
			this->AcceptButton = this->loginButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->CancelButton = this->cancelButton;
			this->ClientSize = System::Drawing::Size(208, 107);
			this->ControlBox = false;
			this->Controls->Add(this->expandButton);
			this->Controls->Add(this->serverDetails);
			this->Controls->Add(this->cancelButton);
			this->Controls->Add(this->loginButton);
			this->Controls->Add(this->passwordLabel);
			this->Controls->Add(this->passwordText);
			this->Controls->Add(this->usernameText);
			this->Controls->Add(this->usernameLabel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"LoginDialog";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"BAPS Presenter: Please Login";
			this->Load += gcnew System::EventHandler(this, &LoginDialog::LoginDialog_Load);
			this->serverDetails->ResumeLayout(false);
			this->serverDetails->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


};
}
