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
			serverText->Text = ConfigManager::getConfigValueString("ServerAddress", "localhost");
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




	private: System::Windows::Forms::Label^  portLabel;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  portText;

	private: System::Windows::Forms::HelpProvider^  helpProvider1;
	private: System::Windows::Forms::Button^  loginButton;
	private: System::Windows::Forms::Button^  cancelButton;
	private: System::Windows::Forms::ComboBox^  serverText;




			 /** Counter for login attempts **/
		int loginAttempt;

		System::Void loginButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void cancelButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void LoginDialog_Load(System::Object ^  sender, System::EventArgs ^  e);
		System::Void connectionText_TextChanged(System::Object ^  sender, System::EventArgs ^  e);
		System::Void Textbox_Enter(System::Object^  sender, System::EventArgs^  e);
		//System::Void expandButton_Click(System::Object^  sender, System::EventArgs^  e);

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
			this->portLabel = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->portText = (gcnew System::Windows::Forms::TextBox());
			this->helpProvider1 = (gcnew System::Windows::Forms::HelpProvider());
			this->loginButton = (gcnew System::Windows::Forms::Button());
			this->cancelButton = (gcnew System::Windows::Forms::Button());
			this->serverText = (gcnew System::Windows::Forms::ComboBox());
			this->SuspendLayout();
			// 
			// passwordLabel
			// 
			this->passwordLabel->BackColor = System::Drawing::Color::Transparent;
			this->passwordLabel->Location = System::Drawing::Point(12, 40);
			this->passwordLabel->Name = L"passwordLabel";
			this->passwordLabel->Size = System::Drawing::Size(64, 16);
			this->passwordLabel->TabIndex = 16;
			this->passwordLabel->Text = L"Password:";
			// 
			// passwordText
			// 
			this->passwordText->BackColor = System::Drawing::SystemColors::Window;
			this->passwordText->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->passwordText->Location = System::Drawing::Point(82, 38);
			this->passwordText->Name = L"passwordText";
			this->passwordText->PasswordChar = '*';
			this->passwordText->Size = System::Drawing::Size(125, 21);
			this->passwordText->TabIndex = 1;
			this->passwordText->UseSystemPasswordChar = true;
			this->passwordText->Enter += gcnew System::EventHandler(this, &LoginDialog::connectionText_TextChanged);
			// 
			// usernameText
			// 
			this->usernameText->BackColor = System::Drawing::SystemColors::Window;
			this->usernameText->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->usernameText->Location = System::Drawing::Point(82, 12);
			this->usernameText->Name = L"usernameText";
			this->usernameText->Size = System::Drawing::Size(125, 21);
			this->usernameText->TabIndex = 0;
			this->usernameText->Enter += gcnew System::EventHandler(this, &LoginDialog::Textbox_Enter);
			// 
			// usernameLabel
			// 
			this->usernameLabel->BackColor = System::Drawing::Color::Transparent;
			this->usernameLabel->Location = System::Drawing::Point(12, 14);
			this->usernameLabel->Name = L"usernameLabel";
			this->usernameLabel->Size = System::Drawing::Size(64, 16);
			this->usernameLabel->TabIndex = 17;
			this->usernameLabel->Text = L"Username:";
			// 
			// portLabel
			// 
			this->portLabel->BackColor = System::Drawing::Color::Transparent;
			this->portLabel->Location = System::Drawing::Point(12, 92);
			this->portLabel->Name = L"portLabel";
			this->portLabel->Size = System::Drawing::Size(64, 18);
			this->portLabel->TabIndex = 13;
			this->portLabel->Text = L"Port:";
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Location = System::Drawing::Point(12, 66);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(64, 18);
			this->label1->TabIndex = 12;
			this->label1->Text = L"Server:";
			// 
			// portText
			// 
			this->portText->BackColor = System::Drawing::SystemColors::Window;
			this->portText->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->portText->Location = System::Drawing::Point(82, 90);
			this->portText->Name = L"portText";
			this->portText->Size = System::Drawing::Size(125, 21);
			this->portText->TabIndex = 7;
			this->portText->Text = L"1350";
			this->portText->TextChanged += gcnew System::EventHandler(this, &LoginDialog::connectionText_TextChanged);
			this->portText->Enter += gcnew System::EventHandler(this, &LoginDialog::Textbox_Enter);
			// 
			// loginButton
			// 
			this->loginButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->loginButton->Location = System::Drawing::Point(51, 117);
			this->loginButton->Name = L"loginButton";
			this->loginButton->Size = System::Drawing::Size(75, 23);
			this->loginButton->TabIndex = 18;
			this->loginButton->Text = L"Login";
			this->loginButton->UseVisualStyleBackColor = true;
			this->loginButton->Click += gcnew System::EventHandler(this, &LoginDialog::loginButton_Click);
			// 
			// cancelButton
			// 
			this->cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->cancelButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cancelButton->Location = System::Drawing::Point(132, 117);
			this->cancelButton->Name = L"cancelButton";
			this->cancelButton->Size = System::Drawing::Size(75, 23);
			this->cancelButton->TabIndex = 19;
			this->cancelButton->Text = L"Cancel";
			this->cancelButton->UseVisualStyleBackColor = true;
			this->cancelButton->Click += gcnew System::EventHandler(this, &LoginDialog::cancelButton_Click);
			// 
			// serverText
			// 
			this->serverText->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->serverText->FormattingEnabled = true;
			this->serverText->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"localhost", L"studio1", L"studio2", L"production"});
			this->serverText->Location = System::Drawing::Point(82, 63);
			this->serverText->Name = L"serverText";
			this->serverText->Size = System::Drawing::Size(125, 21);
			this->serverText->TabIndex = 20;
			// 
			// LoginDialog
			// 
			this->AcceptButton = this->loginButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->CancelButton = this->cancelButton;
			this->ClientSize = System::Drawing::Size(219, 152);
			this->ControlBox = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Controls->Add(this->serverText);
			this->Controls->Add(this->cancelButton);
			this->Controls->Add(this->loginButton);
			this->Controls->Add(this->portText);
			this->Controls->Add(this->portLabel);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->passwordLabel);
			this->Controls->Add(this->passwordText);
			this->Controls->Add(this->usernameText);
			this->Controls->Add(this->usernameLabel);
			this->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"LoginDialog";
			this->Text = L"BAPS Presenter: Please Login";
			this->Load += gcnew System::EventHandler(this, &LoginDialog::LoginDialog_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


};
}
