#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#include "SecurityDialogStructs.h"
#include "Messages.h"
#include "BAPSPresenterMain.h"

namespace BAPSPresenter {

	/** We need a pre-declaration of the Main form so that we can define a handle to it here **/
	ref class BAPSPresenterMain;

	enum SecurityStatus
	{
		SD_AWAITING_INIT =0,
		SD_DORMANT,
		SD_ADDUSER,
		SD_GETUSERS,
		SD_REVOKEPERMISSION,
		SD_GRANTPERMISSION,
		SD_SETPASSWORD,
		SD_REMOVEUSER,
		SD_GETIPRESTRICTIONS,
		SD_GETIPRESTRICTIONS2,
		SD_ALTERIPRESTRICTION,
		LAST_VALUE
	};
	/// <summary>
	/// Summary for SecurityDialog
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class SecurityDialog : public System::Windows::Forms::Form
	{
	public:
		SecurityDialog(BAPSPresenterMain^ _bapsPresenterMain, System::Collections::Queue^ _msgQueue)
			: bapsPresenterMain(_bapsPresenterMain), msgQueue(_msgQueue)
		{
			InitializeComponent();
			userList->Enabled=false;
			permissionList->Enabled=false;
			revokeButton->Enabled=false;
			grantButton->Enabled=false;
			availablePermissionList->Enabled=false;
			newPasswordText->Enabled=false;
			confirmNewPasswordText->Enabled=false;
			setPasswordButton->Enabled=false;
			addUserButton->Enabled=false;
			deleteUserButton->Enabled=false;
			permissionCount = 0;
			userCount = 0;
			addToAllowButton->Tag		= safe_cast<System::Object^>(0);
			addToDenyButton->Tag		= BAPSNET_CONFIG_USEVALUEMASK;
			removeFromAllowButton->Tag	= BAPSNET_CONFIG_MODEMASK;
			removeFromDenyButton->Tag	= BAPSNET_CONFIG_USEVALUEMASK|BAPSNET_CONFIG_MODEMASK;
			status = SD_AWAITING_INIT;
		}
		void receiveUserCount(System::Object^ _count);
		void receiveUserInfo(System::String^ username, System::Object^ _permissions);
		void receivePermissionCount(System::Object^ _count);
		void receivePermissionInfo(System::Object^ _permissionCode, System::String^ description);
		void receiveUserResult(System::Object^ _resultCode, System::String^ description);
		void receiveIPDenyCount(System::Object^ _count);
		void receiveIPAllowCount(System::Object^ _count);
		void receiveIPDeny(System::String^ ipaddress, System::Object^ _mask);
		void receiveIPAllow(System::String^ ipaddress, System::Object^ _mask);
		void receiveConfigError(System::Object^ _resultCode, System::String^ description);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SecurityDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		System::Collections::Queue^ msgQueue;
		SecurityStatus status;
		int userCount;
		int permissionCount;
		int allowCount;
		int denyCount;
		array<PermissionInfo^>^ permissionInfo;
		/** A handle to the main window **/
		BAPSPresenterMain^ bapsPresenterMain;

		System::Void newUserText_Leave(System::Object ^  sender, System::EventArgs ^  e);
		System::Void addUserButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void userList_SelectedIndexChanged(System::Object ^  sender, System::EventArgs ^  e);
		System::Void permissionList_SelectedIndexChanged(System::Object ^  sender, System::EventArgs ^  e);
		System::Void availablePermissionList_SelectedIndexChanged(System::Object ^  sender, System::EventArgs ^  e);
		System::Void revokeButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void grantButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void changePassword_TextChanged(System::Object ^  sender, System::EventArgs ^  e);
		System::Void setPasswordButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void refreshButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void deleteUserButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void securityPageControl_SelectedIndexChanged(System::Object ^  sender, System::EventArgs ^  e);
		System::Void alterRestrictionButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void SecurityDialog_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Windows::Forms::Button^  addToAllowButton;
	protected: 
	private: System::Windows::Forms::TextBox^  ipAddressText;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ListBox^  deniedIPList;
	private: System::Windows::Forms::ListBox^  allowedIPList;
	private: System::Windows::Forms::ListBox^  permissionList;
	private: System::Windows::Forms::ListBox^  userList;
	private: System::Windows::Forms::Label^  selectedUserLabel;
	private: System::Windows::Forms::Label^  confirmNewPasswordLabel;
	private: System::Windows::Forms::Button^  grantButton;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  maskText;
	private: System::Windows::Forms::Button^  addToDenyButton;
	private: System::Windows::Forms::Button^  removeFromAllowButton;
	private: System::Windows::Forms::TabPage^  connectionManagerPage;
	private: System::Windows::Forms::Button^  removeFromDenyButton;
	private: System::Windows::Forms::TextBox^  confirmNewPasswordText;
	private: System::Windows::Forms::ListBox^  availablePermissionList;
	private: System::Windows::Forms::Label^  availablePermissionLabel;
	private: System::Windows::Forms::Button^  refreshButton;
	private: System::Windows::Forms::Button^  deleteUserButton;
	private: System::Windows::Forms::TabPage^  userManagerPage;
	private: System::Windows::Forms::Label^  selectedUserLabelLabel;
	private: System::Windows::Forms::GroupBox^  newUserBox;
	private: System::Windows::Forms::Button^  addUserButton;
	private: System::Windows::Forms::Label^  passwordLabel;
	private: System::Windows::Forms::Label^  newUsernameLabel;
	private: System::Windows::Forms::TextBox^  newUsernameText;
	private: System::Windows::Forms::TextBox^  passwordText;
	private: System::Windows::Forms::TextBox^  confirmPasswordText;
	private: System::Windows::Forms::Label^  confirmPasswordLabel;
	private: System::Windows::Forms::Button^  setPasswordButton;
	private: System::Windows::Forms::Label^  newPasswordLabel;
	private: System::Windows::Forms::TextBox^  newPasswordText;
	private: System::Windows::Forms::Label^  permissionLabel;
	private: System::Windows::Forms::Label^  selectUserLabel;
	private: System::Windows::Forms::Button^  revokeButton;
	private: System::Windows::Forms::TabControl^  securityPageControl;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(SecurityDialog::typeid));
			this->addToAllowButton = (gcnew System::Windows::Forms::Button());
			this->ipAddressText = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->deniedIPList = (gcnew System::Windows::Forms::ListBox());
			this->allowedIPList = (gcnew System::Windows::Forms::ListBox());
			this->permissionList = (gcnew System::Windows::Forms::ListBox());
			this->userList = (gcnew System::Windows::Forms::ListBox());
			this->selectedUserLabel = (gcnew System::Windows::Forms::Label());
			this->confirmNewPasswordLabel = (gcnew System::Windows::Forms::Label());
			this->grantButton = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->maskText = (gcnew System::Windows::Forms::TextBox());
			this->addToDenyButton = (gcnew System::Windows::Forms::Button());
			this->removeFromAllowButton = (gcnew System::Windows::Forms::Button());
			this->connectionManagerPage = (gcnew System::Windows::Forms::TabPage());
			this->removeFromDenyButton = (gcnew System::Windows::Forms::Button());
			this->confirmNewPasswordText = (gcnew System::Windows::Forms::TextBox());
			this->availablePermissionList = (gcnew System::Windows::Forms::ListBox());
			this->availablePermissionLabel = (gcnew System::Windows::Forms::Label());
			this->refreshButton = (gcnew System::Windows::Forms::Button());
			this->deleteUserButton = (gcnew System::Windows::Forms::Button());
			this->userManagerPage = (gcnew System::Windows::Forms::TabPage());
			this->selectedUserLabelLabel = (gcnew System::Windows::Forms::Label());
			this->newUserBox = (gcnew System::Windows::Forms::GroupBox());
			this->addUserButton = (gcnew System::Windows::Forms::Button());
			this->passwordLabel = (gcnew System::Windows::Forms::Label());
			this->newUsernameLabel = (gcnew System::Windows::Forms::Label());
			this->newUsernameText = (gcnew System::Windows::Forms::TextBox());
			this->passwordText = (gcnew System::Windows::Forms::TextBox());
			this->confirmPasswordText = (gcnew System::Windows::Forms::TextBox());
			this->confirmPasswordLabel = (gcnew System::Windows::Forms::Label());
			this->setPasswordButton = (gcnew System::Windows::Forms::Button());
			this->newPasswordLabel = (gcnew System::Windows::Forms::Label());
			this->newPasswordText = (gcnew System::Windows::Forms::TextBox());
			this->permissionLabel = (gcnew System::Windows::Forms::Label());
			this->selectUserLabel = (gcnew System::Windows::Forms::Label());
			this->revokeButton = (gcnew System::Windows::Forms::Button());
			this->securityPageControl = (gcnew System::Windows::Forms::TabControl());
			this->connectionManagerPage->SuspendLayout();
			this->userManagerPage->SuspendLayout();
			this->newUserBox->SuspendLayout();
			this->securityPageControl->SuspendLayout();
			this->SuspendLayout();
			// 
			// addToAllowButton
			// 
			this->addToAllowButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->addToAllowButton->Location = System::Drawing::Point(288, 294);
			this->addToAllowButton->Name = L"addToAllowButton";
			this->addToAllowButton->Size = System::Drawing::Size(80, 22);
			this->addToAllowButton->TabIndex = 4;
			this->addToAllowButton->Text = L"Add to Allow";
			this->addToAllowButton->Click += gcnew System::EventHandler(this, &SecurityDialog::alterRestrictionButton_Click);
			// 
			// ipAddressText
			// 
			this->ipAddressText->Location = System::Drawing::Point(16, 294);
			this->ipAddressText->Name = L"ipAddressText";
			this->ipAddressText->Size = System::Drawing::Size(170, 21);
			this->ipAddressText->TabIndex = 3;
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 8);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(192, 24);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Allowed Networks";
			// 
			// deniedIPList
			// 
			this->deniedIPList->Location = System::Drawing::Point(288, 32);
			this->deniedIPList->Name = L"deniedIPList";
			this->deniedIPList->Size = System::Drawing::Size(232, 251);
			this->deniedIPList->TabIndex = 1;
			// 
			// allowedIPList
			// 
			this->allowedIPList->Location = System::Drawing::Point(16, 32);
			this->allowedIPList->Name = L"allowedIPList";
			this->allowedIPList->Size = System::Drawing::Size(232, 251);
			this->allowedIPList->TabIndex = 0;
			// 
			// permissionList
			// 
			this->permissionList->Location = System::Drawing::Point(216, 64);
			this->permissionList->Name = L"permissionList";
			this->permissionList->Size = System::Drawing::Size(296, 56);
			this->permissionList->TabIndex = 18;
			this->permissionList->SelectedIndexChanged += gcnew System::EventHandler(this, &SecurityDialog::permissionList_SelectedIndexChanged);
			// 
			// userList
			// 
			this->userList->Location = System::Drawing::Point(16, 24);
			this->userList->Name = L"userList";
			this->userList->Size = System::Drawing::Size(176, 251);
			this->userList->TabIndex = 6;
			this->userList->SelectedIndexChanged += gcnew System::EventHandler(this, &SecurityDialog::userList_SelectedIndexChanged);
			// 
			// selectedUserLabel
			// 
			this->selectedUserLabel->Font = (gcnew System::Drawing::Font(L"Tahoma", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->selectedUserLabel->Location = System::Drawing::Point(280, 16);
			this->selectedUserLabel->Name = L"selectedUserLabel";
			this->selectedUserLabel->Size = System::Drawing::Size(176, 24);
			this->selectedUserLabel->TabIndex = 11;
			this->selectedUserLabel->Text = L"<select user>";
			// 
			// confirmNewPasswordLabel
			// 
			this->confirmNewPasswordLabel->Location = System::Drawing::Point(307, 237);
			this->confirmNewPasswordLabel->Name = L"confirmNewPasswordLabel";
			this->confirmNewPasswordLabel->Size = System::Drawing::Size(104, 16);
			this->confirmNewPasswordLabel->TabIndex = 16;
			this->confirmNewPasswordLabel->Text = L"Confirm Password";
			// 
			// grantButton
			// 
			this->grantButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->grantButton->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->grantButton->Location = System::Drawing::Point(448, 150);
			this->grantButton->Name = L"grantButton";
			this->grantButton->Size = System::Drawing::Size(64, 21);
			this->grantButton->TabIndex = 9;
			this->grantButton->Text = L"Grant";
			this->grantButton->Click += gcnew System::EventHandler(this, &SecurityDialog::grantButton_Click);
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(284, 8);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(192, 24);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Denied Networks";
			// 
			// maskText
			// 
			this->maskText->Location = System::Drawing::Point(192, 294);
			this->maskText->Name = L"maskText";
			this->maskText->Size = System::Drawing::Size(56, 21);
			this->maskText->TabIndex = 3;
			// 
			// addToDenyButton
			// 
			this->addToDenyButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->addToDenyButton->Location = System::Drawing::Point(288, 322);
			this->addToDenyButton->Name = L"addToDenyButton";
			this->addToDenyButton->Size = System::Drawing::Size(80, 22);
			this->addToDenyButton->TabIndex = 4;
			this->addToDenyButton->Text = L"Add to Deny";
			this->addToDenyButton->Click += gcnew System::EventHandler(this, &SecurityDialog::alterRestrictionButton_Click);
			// 
			// removeFromAllowButton
			// 
			this->removeFromAllowButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->removeFromAllowButton->Location = System::Drawing::Point(374, 294);
			this->removeFromAllowButton->Name = L"removeFromAllowButton";
			this->removeFromAllowButton->Size = System::Drawing::Size(112, 22);
			this->removeFromAllowButton->TabIndex = 4;
			this->removeFromAllowButton->Text = L"Remove from Allow";
			this->removeFromAllowButton->Click += gcnew System::EventHandler(this, &SecurityDialog::alterRestrictionButton_Click);
			// 
			// connectionManagerPage
			// 
			this->connectionManagerPage->Controls->Add(this->addToAllowButton);
			this->connectionManagerPage->Controls->Add(this->ipAddressText);
			this->connectionManagerPage->Controls->Add(this->label1);
			this->connectionManagerPage->Controls->Add(this->deniedIPList);
			this->connectionManagerPage->Controls->Add(this->allowedIPList);
			this->connectionManagerPage->Controls->Add(this->label2);
			this->connectionManagerPage->Controls->Add(this->maskText);
			this->connectionManagerPage->Controls->Add(this->addToDenyButton);
			this->connectionManagerPage->Controls->Add(this->removeFromAllowButton);
			this->connectionManagerPage->Controls->Add(this->removeFromDenyButton);
			this->connectionManagerPage->Location = System::Drawing::Point(4, 25);
			this->connectionManagerPage->Name = L"connectionManagerPage";
			this->connectionManagerPage->Size = System::Drawing::Size(531, 349);
			this->connectionManagerPage->TabIndex = 1;
			this->connectionManagerPage->Text = L"Connection Manager";
			// 
			// removeFromDenyButton
			// 
			this->removeFromDenyButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->removeFromDenyButton->Location = System::Drawing::Point(374, 322);
			this->removeFromDenyButton->Name = L"removeFromDenyButton";
			this->removeFromDenyButton->Size = System::Drawing::Size(112, 22);
			this->removeFromDenyButton->TabIndex = 4;
			this->removeFromDenyButton->Text = L"Remove from Deny";
			this->removeFromDenyButton->Click += gcnew System::EventHandler(this, &SecurityDialog::alterRestrictionButton_Click);
			// 
			// confirmNewPasswordText
			// 
			this->confirmNewPasswordText->Location = System::Drawing::Point(310, 256);
			this->confirmNewPasswordText->Name = L"confirmNewPasswordText";
			this->confirmNewPasswordText->PasswordChar = '*';
			this->confirmNewPasswordText->Size = System::Drawing::Size(88, 21);
			this->confirmNewPasswordText->TabIndex = 15;
			this->confirmNewPasswordText->Text = L"12345";
			this->confirmNewPasswordText->UseSystemPasswordChar = true;
			this->confirmNewPasswordText->TextChanged += gcnew System::EventHandler(this, &SecurityDialog::changePassword_TextChanged);
			// 
			// availablePermissionList
			// 
			this->availablePermissionList->Location = System::Drawing::Point(216, 177);
			this->availablePermissionList->Name = L"availablePermissionList";
			this->availablePermissionList->Size = System::Drawing::Size(296, 56);
			this->availablePermissionList->TabIndex = 18;
			this->availablePermissionList->SelectedIndexChanged += gcnew System::EventHandler(this, &SecurityDialog::availablePermissionList_SelectedIndexChanged);
			// 
			// availablePermissionLabel
			// 
			this->availablePermissionLabel->Location = System::Drawing::Point(213, 158);
			this->availablePermissionLabel->Name = L"availablePermissionLabel";
			this->availablePermissionLabel->Size = System::Drawing::Size(136, 16);
			this->availablePermissionLabel->TabIndex = 14;
			this->availablePermissionLabel->Text = L"Permissions (available):";
			// 
			// refreshButton
			// 
			this->refreshButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->refreshButton->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->refreshButton->Location = System::Drawing::Point(448, 8);
			this->refreshButton->Name = L"refreshButton";
			this->refreshButton->Size = System::Drawing::Size(66, 22);
			this->refreshButton->TabIndex = 21;
			this->refreshButton->Text = L"Refresh";
			this->refreshButton->Click += gcnew System::EventHandler(this, &SecurityDialog::refreshButton_Click);
			// 
			// deleteUserButton
			// 
			this->deleteUserButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->deleteUserButton->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->deleteUserButton->Location = System::Drawing::Point(448, 36);
			this->deleteUserButton->Name = L"deleteUserButton";
			this->deleteUserButton->Size = System::Drawing::Size(64, 22);
			this->deleteUserButton->TabIndex = 22;
			this->deleteUserButton->Text = L"Delete User";
			this->deleteUserButton->Click += gcnew System::EventHandler(this, &SecurityDialog::deleteUserButton_Click);
			// 
			// userManagerPage
			// 
			this->userManagerPage->Controls->Add(this->deleteUserButton);
			this->userManagerPage->Controls->Add(this->refreshButton);
			this->userManagerPage->Controls->Add(this->selectedUserLabelLabel);
			this->userManagerPage->Controls->Add(this->newUserBox);
			this->userManagerPage->Controls->Add(this->setPasswordButton);
			this->userManagerPage->Controls->Add(this->newPasswordLabel);
			this->userManagerPage->Controls->Add(this->newPasswordText);
			this->userManagerPage->Controls->Add(this->permissionLabel);
			this->userManagerPage->Controls->Add(this->selectUserLabel);
			this->userManagerPage->Controls->Add(this->revokeButton);
			this->userManagerPage->Controls->Add(this->grantButton);
			this->userManagerPage->Controls->Add(this->permissionList);
			this->userManagerPage->Controls->Add(this->userList);
			this->userManagerPage->Controls->Add(this->selectedUserLabel);
			this->userManagerPage->Controls->Add(this->confirmNewPasswordLabel);
			this->userManagerPage->Controls->Add(this->confirmNewPasswordText);
			this->userManagerPage->Controls->Add(this->availablePermissionList);
			this->userManagerPage->Controls->Add(this->availablePermissionLabel);
			this->userManagerPage->Location = System::Drawing::Point(4, 25);
			this->userManagerPage->Name = L"userManagerPage";
			this->userManagerPage->Size = System::Drawing::Size(531, 349);
			this->userManagerPage->TabIndex = 0;
			this->userManagerPage->Text = L"User Manager";
			// 
			// selectedUserLabelLabel
			// 
			this->selectedUserLabelLabel->Font = (gcnew System::Drawing::Font(L"Tahoma", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->selectedUserLabelLabel->Location = System::Drawing::Point(216, 16);
			this->selectedUserLabelLabel->Name = L"selectedUserLabelLabel";
			this->selectedUserLabelLabel->Size = System::Drawing::Size(64, 24);
			this->selectedUserLabelLabel->TabIndex = 20;
			this->selectedUserLabelLabel->Text = L"User:";
			// 
			// newUserBox
			// 
			this->newUserBox->Controls->Add(this->addUserButton);
			this->newUserBox->Controls->Add(this->passwordLabel);
			this->newUserBox->Controls->Add(this->newUsernameLabel);
			this->newUserBox->Controls->Add(this->newUsernameText);
			this->newUserBox->Controls->Add(this->passwordText);
			this->newUserBox->Controls->Add(this->confirmPasswordText);
			this->newUserBox->Controls->Add(this->confirmPasswordLabel);
			this->newUserBox->Location = System::Drawing::Point(8, 280);
			this->newUserBox->Name = L"newUserBox";
			this->newUserBox->Size = System::Drawing::Size(520, 64);
			this->newUserBox->TabIndex = 19;
			this->newUserBox->TabStop = false;
			this->newUserBox->Text = L"Add User";
			// 
			// addUserButton
			// 
			this->addUserButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->addUserButton->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->addUserButton->Location = System::Drawing::Point(416, 27);
			this->addUserButton->Name = L"addUserButton";
			this->addUserButton->Size = System::Drawing::Size(88, 26);
			this->addUserButton->TabIndex = 4;
			this->addUserButton->Text = L"Add User";
			this->addUserButton->Click += gcnew System::EventHandler(this, &SecurityDialog::addUserButton_Click);
			// 
			// passwordLabel
			// 
			this->passwordLabel->Location = System::Drawing::Point(176, 16);
			this->passwordLabel->Name = L"passwordLabel";
			this->passwordLabel->Size = System::Drawing::Size(88, 16);
			this->passwordLabel->TabIndex = 2;
			this->passwordLabel->Text = L"Password";
			// 
			// newUsernameLabel
			// 
			this->newUsernameLabel->ForeColor = System::Drawing::SystemColors::ControlText;
			this->newUsernameLabel->Location = System::Drawing::Point(40, 16);
			this->newUsernameLabel->Name = L"newUsernameLabel";
			this->newUsernameLabel->Size = System::Drawing::Size(112, 16);
			this->newUsernameLabel->TabIndex = 1;
			this->newUsernameLabel->Text = L"Username";
			// 
			// newUsernameText
			// 
			this->newUsernameText->Location = System::Drawing::Point(40, 32);
			this->newUsernameText->Name = L"newUsernameText";
			this->newUsernameText->Size = System::Drawing::Size(112, 21);
			this->newUsernameText->TabIndex = 0;
			this->newUsernameText->TextChanged += gcnew System::EventHandler(this, &SecurityDialog::newUserText_Leave);
			// 
			// passwordText
			// 
			this->passwordText->Location = System::Drawing::Point(176, 32);
			this->passwordText->Name = L"passwordText";
			this->passwordText->PasswordChar = '*';
			this->passwordText->Size = System::Drawing::Size(88, 21);
			this->passwordText->TabIndex = 0;
			this->passwordText->UseSystemPasswordChar = true;
			this->passwordText->TextChanged += gcnew System::EventHandler(this, &SecurityDialog::newUserText_Leave);
			// 
			// confirmPasswordText
			// 
			this->confirmPasswordText->Location = System::Drawing::Point(272, 32);
			this->confirmPasswordText->Name = L"confirmPasswordText";
			this->confirmPasswordText->PasswordChar = '*';
			this->confirmPasswordText->Size = System::Drawing::Size(88, 21);
			this->confirmPasswordText->TabIndex = 0;
			this->confirmPasswordText->UseSystemPasswordChar = true;
			this->confirmPasswordText->TextChanged += gcnew System::EventHandler(this, &SecurityDialog::newUserText_Leave);
			// 
			// confirmPasswordLabel
			// 
			this->confirmPasswordLabel->Location = System::Drawing::Point(272, 16);
			this->confirmPasswordLabel->Name = L"confirmPasswordLabel";
			this->confirmPasswordLabel->Size = System::Drawing::Size(104, 16);
			this->confirmPasswordLabel->TabIndex = 2;
			this->confirmPasswordLabel->Text = L"Confirm Password";
			// 
			// setPasswordButton
			// 
			this->setPasswordButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->setPasswordButton->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->setPasswordButton->Location = System::Drawing::Point(424, 256);
			this->setPasswordButton->Name = L"setPasswordButton";
			this->setPasswordButton->Size = System::Drawing::Size(88, 21);
			this->setPasswordButton->TabIndex = 17;
			this->setPasswordButton->Text = L"Set Password";
			this->setPasswordButton->Click += gcnew System::EventHandler(this, &SecurityDialog::setPasswordButton_Click);
			// 
			// newPasswordLabel
			// 
			this->newPasswordLabel->Location = System::Drawing::Point(213, 237);
			this->newPasswordLabel->Name = L"newPasswordLabel";
			this->newPasswordLabel->Size = System::Drawing::Size(88, 16);
			this->newPasswordLabel->TabIndex = 16;
			this->newPasswordLabel->Text = L"New Password";
			// 
			// newPasswordText
			// 
			this->newPasswordText->Location = System::Drawing::Point(216, 256);
			this->newPasswordText->Name = L"newPasswordText";
			this->newPasswordText->PasswordChar = '*';
			this->newPasswordText->Size = System::Drawing::Size(88, 21);
			this->newPasswordText->TabIndex = 15;
			this->newPasswordText->Text = L"12345";
			this->newPasswordText->UseSystemPasswordChar = true;
			this->newPasswordText->TextChanged += gcnew System::EventHandler(this, &SecurityDialog::changePassword_TextChanged);
			// 
			// permissionLabel
			// 
			this->permissionLabel->Location = System::Drawing::Point(213, 45);
			this->permissionLabel->Name = L"permissionLabel";
			this->permissionLabel->Size = System::Drawing::Size(136, 16);
			this->permissionLabel->TabIndex = 14;
			this->permissionLabel->Text = L"Permissions (granted):";
			// 
			// selectUserLabel
			// 
			this->selectUserLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->selectUserLabel->Location = System::Drawing::Point(16, 8);
			this->selectUserLabel->Name = L"selectUserLabel";
			this->selectUserLabel->Size = System::Drawing::Size(168, 16);
			this->selectUserLabel->TabIndex = 13;
			this->selectUserLabel->Text = L"Select User:";
			// 
			// revokeButton
			// 
			this->revokeButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->revokeButton->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->revokeButton->Location = System::Drawing::Point(448, 126);
			this->revokeButton->Name = L"revokeButton";
			this->revokeButton->Size = System::Drawing::Size(64, 21);
			this->revokeButton->TabIndex = 10;
			this->revokeButton->Text = L"Revoke";
			this->revokeButton->Click += gcnew System::EventHandler(this, &SecurityDialog::revokeButton_Click);
			// 
			// securityPageControl
			// 
			this->securityPageControl->Appearance = System::Windows::Forms::TabAppearance::FlatButtons;
			this->securityPageControl->Controls->Add(this->userManagerPage);
			this->securityPageControl->Controls->Add(this->connectionManagerPage);
			this->securityPageControl->Dock = System::Windows::Forms::DockStyle::Fill;
			this->securityPageControl->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->securityPageControl->Location = System::Drawing::Point(0, 0);
			this->securityPageControl->Name = L"securityPageControl";
			this->securityPageControl->SelectedIndex = 0;
			this->securityPageControl->Size = System::Drawing::Size(539, 378);
			this->securityPageControl->TabIndex = 1;
			this->securityPageControl->SelectedIndexChanged += gcnew System::EventHandler(this, &SecurityDialog::securityPageControl_SelectedIndexChanged);
			// 
			// SecurityDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(539, 378);
			this->Controls->Add(this->securityPageControl);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->KeyPreview = true;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"SecurityDialog";
			this->Text = L"Security Manager";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SecurityDialog::SecurityDialog_KeyDown);
			this->connectionManagerPage->ResumeLayout(false);
			this->connectionManagerPage->PerformLayout();
			this->userManagerPage->ResumeLayout(false);
			this->userManagerPage->PerformLayout();
			this->newUserBox->ResumeLayout(false);
			this->newUserBox->PerformLayout();
			this->securityPageControl->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
};
}
