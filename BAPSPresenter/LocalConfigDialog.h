#pragma once
#include "ConfigManager.h"
#include "BAPSButton.h"
#include "BAPSPresenterMain.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace BAPSPresenter {

	/** We need a pre-declaration of the Main form so that we can define a handle to it here **/
	ref class BAPSPresenterMain;
	/// <summary>
	/// Summary for LocalConfigDialog
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class LocalConfigDialog : public System::Windows::Forms::Form
	{
	public:
		LocalConfigDialog(BAPSPresenterMain^ _bapsPresenterMain)
			: bapsPresenterMain(_bapsPresenterMain)
		{
			InitializeComponent();
			serverText->Text = ConfigManager::getConfigValueString("ServerAddress", "127.0.0.1");
			portText->Text = ConfigManager::getConfigValueString("ServerPort", "1350");
			usernameText->Text = ConfigManager::getConfigValueString("DefaultUsername", "");
			passwordText->Text = ConfigManager::getConfigValueString("DefaultPassword", "");
			showVolumeList->SelectedItem = ConfigManager::getConfigValueString("ShowVolume", "No");
			enableTimersList->SelectedItem = ConfigManager::getConfigValueString("EnableTimers", "No");
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~LocalConfigDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  enableTimersLabel;
	protected: 
	private: System::Windows::Forms::ListBox^  enableTimersList;
	private: System::Windows::Forms::Button^  saveButton;
	private: System::Windows::Forms::Button^  cancelButton;
	private: System::Windows::Forms::ComboBox^  serverText;
	private:
		/** A handle to the main window **/
		BAPSPresenterMain^ bapsPresenterMain;

		System::Void saveButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void cancelButton_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void LocalConfigDialog_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Windows::Forms::ListBox^  showVolumeList;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  portText;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;


	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  usernameText;

	private: System::Windows::Forms::TextBox^  passwordText;


	private: System::Windows::Forms::Label^  label5;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(LocalConfigDialog::typeid));
			this->showVolumeList = (gcnew System::Windows::Forms::ListBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->portText = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->usernameText = (gcnew System::Windows::Forms::TextBox());
			this->passwordText = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->enableTimersLabel = (gcnew System::Windows::Forms::Label());
			this->enableTimersList = (gcnew System::Windows::Forms::ListBox());
			this->saveButton = (gcnew System::Windows::Forms::Button());
			this->cancelButton = (gcnew System::Windows::Forms::Button());
			this->serverText = (gcnew System::Windows::Forms::ComboBox());
			this->SuspendLayout();
			// 
			// showVolumeList
			// 
			this->showVolumeList->BackColor = System::Drawing::SystemColors::Window;
			this->showVolumeList->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->showVolumeList->Enabled = false;
			this->showVolumeList->FormattingEnabled = true;
			this->showVolumeList->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Yes", L"No"});
			this->showVolumeList->Location = System::Drawing::Point(114, 120);
			this->showVolumeList->Name = L"showVolumeList";
			this->showVolumeList->Size = System::Drawing::Size(125, 28);
			this->showVolumeList->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label1->Location = System::Drawing::Point(6, 12);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(88, 20);
			this->label1->TabIndex = 11;
			this->label1->Text = L"Server Address:";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// portText
			// 
			this->portText->BackColor = System::Drawing::SystemColors::Window;
			this->portText->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->portText->Location = System::Drawing::Point(114, 39);
			this->portText->Name = L"portText";
			this->portText->Size = System::Drawing::Size(125, 21);
			this->portText->TabIndex = 1;
			this->portText->Text = L"<not set>";
			// 
			// label2
			// 
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Location = System::Drawing::Point(6, 39);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(88, 20);
			this->label2->TabIndex = 10;
			this->label2->Text = L"Server Port:";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label3
			// 
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Location = System::Drawing::Point(6, 116);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(88, 20);
			this->label3->TabIndex = 9;
			this->label3->Text = L"Show Volume:";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label4
			// 
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Location = System::Drawing::Point(6, 93);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(102, 20);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Default Password:";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// usernameText
			// 
			this->usernameText->BackColor = System::Drawing::SystemColors::Window;
			this->usernameText->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->usernameText->Location = System::Drawing::Point(114, 66);
			this->usernameText->Name = L"usernameText";
			this->usernameText->Size = System::Drawing::Size(125, 21);
			this->usernameText->TabIndex = 2;
			this->usernameText->Text = L"<not set>";
			// 
			// passwordText
			// 
			this->passwordText->BackColor = System::Drawing::SystemColors::Window;
			this->passwordText->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->passwordText->Location = System::Drawing::Point(114, 93);
			this->passwordText->Name = L"passwordText";
			this->passwordText->Size = System::Drawing::Size(125, 21);
			this->passwordText->TabIndex = 3;
			this->passwordText->Text = L"<not set>";
			// 
			// label5
			// 
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label5->Location = System::Drawing::Point(6, 66);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(102, 20);
			this->label5->TabIndex = 11;
			this->label5->Text = L"Default Username:";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// enableTimersLabel
			// 
			this->enableTimersLabel->BackColor = System::Drawing::Color::Transparent;
			this->enableTimersLabel->Location = System::Drawing::Point(6, 150);
			this->enableTimersLabel->Name = L"enableTimersLabel";
			this->enableTimersLabel->Size = System::Drawing::Size(88, 20);
			this->enableTimersLabel->TabIndex = 9;
			this->enableTimersLabel->Text = L"Enable Timers:";
			this->enableTimersLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// enableTimersList
			// 
			this->enableTimersList->BackColor = System::Drawing::SystemColors::Window;
			this->enableTimersList->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->enableTimersList->FormattingEnabled = true;
			this->enableTimersList->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Yes", L"No"});
			this->enableTimersList->Location = System::Drawing::Point(114, 154);
			this->enableTimersList->Name = L"enableTimersList";
			this->enableTimersList->Size = System::Drawing::Size(125, 28);
			this->enableTimersList->TabIndex = 4;
			// 
			// saveButton
			// 
			this->saveButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->saveButton->Location = System::Drawing::Point(79, 188);
			this->saveButton->Name = L"saveButton";
			this->saveButton->Size = System::Drawing::Size(75, 23);
			this->saveButton->TabIndex = 12;
			this->saveButton->Text = L"Save";
			this->saveButton->UseVisualStyleBackColor = true;
			this->saveButton->Click += gcnew System::EventHandler(this, &LocalConfigDialog::saveButton_Click);
			// 
			// cancelButton
			// 
			this->cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->cancelButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cancelButton->Location = System::Drawing::Point(164, 188);
			this->cancelButton->Name = L"cancelButton";
			this->cancelButton->Size = System::Drawing::Size(75, 23);
			this->cancelButton->TabIndex = 13;
			this->cancelButton->Text = L"Cancel";
			this->cancelButton->UseVisualStyleBackColor = true;
			this->cancelButton->Click += gcnew System::EventHandler(this, &LocalConfigDialog::cancelButton_Click);
			// 
			// serverText
			// 
			this->serverText->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->serverText->FormattingEnabled = true;
			this->serverText->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"localhost", L"studio1", L"studio2", L"production"});
			this->serverText->Location = System::Drawing::Point(114, 12);
			this->serverText->Name = L"serverText";
			this->serverText->Size = System::Drawing::Size(125, 21);
			this->serverText->TabIndex = 21;
			this->serverText->Text = L"<not set>";
			// 
			// LocalConfigDialog
			// 
			this->AcceptButton = this->saveButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->cancelButton;
			this->ClientSize = System::Drawing::Size(246, 218);
			this->ControlBox = false;
			this->Controls->Add(this->serverText);
			this->Controls->Add(this->cancelButton);
			this->Controls->Add(this->saveButton);
			this->Controls->Add(this->enableTimersList);
			this->Controls->Add(this->showVolumeList);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->passwordText);
			this->Controls->Add(this->portText);
			this->Controls->Add(this->usernameText);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->enableTimersLabel);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label3);
			this->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->KeyPreview = true;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"LocalConfigDialog";
			this->Text = L"Settings";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &LocalConfigDialog::LocalConfigDialog_KeyDown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

};
}
