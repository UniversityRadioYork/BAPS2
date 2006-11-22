#pragma once
#include "BAPSButton.h"
#include "BAPSListBox.h"
#include "BAPSLabel.h"
#include "BAPSPresenterMain.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/**
	This class allows the user to select a show to load into baps from the
	database backend
**/

namespace BAPSPresenter {

	/** We need a pre-declaration of the Main form so that we can define a handle to it here **/
	ref class BAPSPresenterMain;
	/// <summary>
	/// Summary for LoadShowDialog
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class LoadShowDialog : public System::Windows::Forms::Form
	{
	public:
		LoadShowDialog(BAPSPresenterMain^ _bapsPresenterMain,System::Collections::Queue^ _msgQueue)
			: bapsPresenterMain(_bapsPresenterMain), msgQueue(_msgQueue)
		{
			InitializeComponent();
			/** We keep a record of which user the shows are being selected from **/
			/** Default is other user **/
			showListType = 2;
			/** Each of the radio buttons needs an id so that they can be told apart
				at runtime
			**/
			this->currentUserRadio->Tag = safe_cast<System::Object^>(0);
			this->systemUserRadio->Tag = 1;
			this->otherUserRadio->Tag = 2;
			/** stage 0 is selecting a user **/
			stage = 0;
			/** This is used to help create the selection matrix for assigning
				listings to channels
			**/
			listings = gcnew System::Collections::Hashtable();

		}
		/** Public functions to receive data passed in from the client **/
		void setShowResultCount(System::Object^ count);
		void addShow(System::Object^ id, System::String^ description);
		void setListingResultCount(System::Object^ count);
		void addListing(System::Object^ id, System::Object^ channel, System::String^ description);
		void notifyError(System::Object^ _errorCode, System::String^ message);
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~LoadShowDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		/** Placeholder for the number of channels supported in the server **/
		int totalChannels;
		/** This controls the stage at which the LoadShow dialog is in **/
		int stage;
		/** This is the number of the radio button that was checked **/
		int showListType;
		/** Total shows expected to be received -- used to disable the ui until
			all data is received **/
		int showResultCount;
		/** Two counters for listing results as the matrix is complicated to generate **/
		int listingResultCount;
		int listingResultCountLeft;
		/** A handle on the global message Queue **/
		System::Collections::Queue^ msgQueue;
		/** A handle to the main window **/
		BAPSPresenterMain^ bapsPresenterMain;

	private: BAPSPresenter::BAPSButton^  goButton;
	private: BAPSPresenter::BAPSButton^  cancelButton;

	private: BAPSPresenter::BAPSListBox^  listBox;
	private: BAPSPresenter::BAPSLabel^  dialogTitle;

			 /** This hash table helps in generating the matrix **/
		System::Collections::Hashtable^ listings;

		System::Void check_Changed(System::Object ^  sender, System::EventArgs ^  e);
		System::Void goButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void listBox_SelectedIndexChanged(System::Object ^  sender, System::EventArgs ^  e);
		System::Void cancelButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void matrix_Changed(System::Object ^  sender, System::EventArgs ^  e);
		System::Void LoadShowDialog_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

		 System::Void otherUser_Enter(System::Object^  sender, System::EventArgs^  e);

	private: System::Windows::Forms::Label^  errorLabel;

	private: System::Windows::Forms::CheckBox^  newShowsOnly;
	private: System::Windows::Forms::TextBox^  otherUser;
	private: System::Windows::Forms::RadioButton^  currentUserRadio;


	private: System::Windows::Forms::RadioButton^  otherUserRadio;
	private: System::Windows::Forms::RadioButton^  systemUserRadio;


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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(LoadShowDialog::typeid));
			this->errorLabel = (gcnew System::Windows::Forms::Label());
			this->newShowsOnly = (gcnew System::Windows::Forms::CheckBox());
			this->otherUser = (gcnew System::Windows::Forms::TextBox());
			this->currentUserRadio = (gcnew System::Windows::Forms::RadioButton());
			this->otherUserRadio = (gcnew System::Windows::Forms::RadioButton());
			this->systemUserRadio = (gcnew System::Windows::Forms::RadioButton());
			this->dialogTitle = (gcnew BAPSPresenter::BAPSLabel());
			this->listBox = (gcnew BAPSPresenter::BAPSListBox());
			this->cancelButton = (gcnew BAPSPresenter::BAPSButton());
			this->goButton = (gcnew BAPSPresenter::BAPSButton());
			this->SuspendLayout();
			// 
			// errorLabel
			// 
			this->errorLabel->BackColor = System::Drawing::Color::Transparent;
			this->errorLabel->ForeColor = System::Drawing::Color::Red;
			this->errorLabel->Location = System::Drawing::Point(10, 2);
			this->errorLabel->Name = L"errorLabel";
			this->errorLabel->Size = System::Drawing::Size(302, 16);
			this->errorLabel->TabIndex = 100;
			// 
			// newShowsOnly
			// 
			this->newShowsOnly->BackColor = System::Drawing::Color::Transparent;
			this->newShowsOnly->Checked = true;
			this->newShowsOnly->CheckState = System::Windows::Forms::CheckState::Checked;
			this->newShowsOnly->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->newShowsOnly->Location = System::Drawing::Point(191, 56);
			this->newShowsOnly->Name = L"newShowsOnly";
			this->newShowsOnly->Size = System::Drawing::Size(112, 24);
			this->newShowsOnly->TabIndex = 4;
			this->newShowsOnly->Text = L"New shows only";
			this->newShowsOnly->UseVisualStyleBackColor = false;
			// 
			// otherUser
			// 
			this->otherUser->BackColor = System::Drawing::Color::SeaShell;
			this->otherUser->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->otherUser->ForeColor = System::Drawing::SystemColors::WindowText;
			this->otherUser->Location = System::Drawing::Point(150, 102);
			this->otherUser->Name = L"otherUser";
			this->otherUser->Size = System::Drawing::Size(131, 20);
			this->otherUser->TabIndex = 3;
			this->otherUser->Text = L"<E-mail / BAPS showid>";
			this->otherUser->Enter += gcnew System::EventHandler(this, &LoadShowDialog::otherUser_Enter);
			// 
			// currentUserRadio
			// 
			this->currentUserRadio->BackColor = System::Drawing::Color::Transparent;
			this->currentUserRadio->FlatAppearance->CheckedBackColor = System::Drawing::Color::SeaShell;
			this->currentUserRadio->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->currentUserRadio->Location = System::Drawing::Point(51, 56);
			this->currentUserRadio->Name = L"currentUserRadio";
			this->currentUserRadio->Size = System::Drawing::Size(104, 16);
			this->currentUserRadio->TabIndex = 0;
			this->currentUserRadio->Text = L"Current User";
			this->currentUserRadio->UseVisualStyleBackColor = false;
			this->currentUserRadio->CheckedChanged += gcnew System::EventHandler(this, &LoadShowDialog::check_Changed);
			// 
			// otherUserRadio
			// 
			this->otherUserRadio->BackColor = System::Drawing::Color::Transparent;
			this->otherUserRadio->Checked = true;
			this->otherUserRadio->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->otherUserRadio->Location = System::Drawing::Point(51, 104);
			this->otherUserRadio->Name = L"otherUserRadio";
			this->otherUserRadio->Size = System::Drawing::Size(80, 16);
			this->otherUserRadio->TabIndex = 2;
			this->otherUserRadio->TabStop = true;
			this->otherUserRadio->Text = L"Other user:";
			this->otherUserRadio->UseVisualStyleBackColor = false;
			this->otherUserRadio->CheckedChanged += gcnew System::EventHandler(this, &LoadShowDialog::check_Changed);
			// 
			// systemUserRadio
			// 
			this->systemUserRadio->BackColor = System::Drawing::Color::Transparent;
			this->systemUserRadio->FlatAppearance->BorderSize = 3;
			this->systemUserRadio->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->systemUserRadio->Location = System::Drawing::Point(51, 80);
			this->systemUserRadio->Name = L"systemUserRadio";
			this->systemUserRadio->Size = System::Drawing::Size(104, 16);
			this->systemUserRadio->TabIndex = 1;
			this->systemUserRadio->Text = L"Audio Wall";
			this->systemUserRadio->UseVisualStyleBackColor = false;
			this->systemUserRadio->CheckedChanged += gcnew System::EventHandler(this, &LoadShowDialog::check_Changed);
			// 
			// dialogTitle
			// 
			this->dialogTitle->BackColor = System::Drawing::Color::Transparent;
			this->dialogTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->dialogTitle->InfoText = L"";
			this->dialogTitle->Location = System::Drawing::Point(10, 19);
			this->dialogTitle->Name = L"dialogTitle";
			this->dialogTitle->Size = System::Drawing::Size(302, 23);
			this->dialogTitle->TabIndex = 100;
			this->dialogTitle->TabStop = false;
			this->dialogTitle->Text = L"Get list of shows for:";
			// 
			// listBox
			// 
			this->listBox->Location = System::Drawing::Point(10, 43);
			this->listBox->Name = L"listBox";
			this->listBox->SelectedIndexEnabled = true;
			this->listBox->Size = System::Drawing::Size(302, 85);
			this->listBox->TabIndex = 2;
			this->listBox->Text = L"bapsListBox1";
			this->listBox->Visible = false;
			this->listBox->SelectedIndexChanged += gcnew System::EventHandler(this, &LoadShowDialog::listBox_SelectedIndexChanged);
			// 
			// cancelButton
			// 
			this->cancelButton->BackColor = System::Drawing::Color::Transparent;
			this->cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->cancelButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->cancelButton->HighlightColor = System::Drawing::Color::Red;
			this->cancelButton->Highlighted = false;
			this->cancelButton->Location = System::Drawing::Point(192, 137);
			this->cancelButton->Name = L"cancelButton";
			this->cancelButton->Size = System::Drawing::Size(120, 27);
			this->cancelButton->TabIndex = 6;
			this->cancelButton->Text = L"Cancel";
			this->cancelButton->Click += gcnew System::EventHandler(this, &LoadShowDialog::cancelButton_Click);
			// 
			// goButton
			// 
			this->goButton->BackColor = System::Drawing::Color::Transparent;
			this->goButton->DialogResult = System::Windows::Forms::DialogResult::None;
			this->goButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->goButton->HighlightColor = System::Drawing::Color::Red;
			this->goButton->Highlighted = false;
			this->goButton->Location = System::Drawing::Point(10, 137);
			this->goButton->Name = L"goButton";
			this->goButton->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->goButton->Size = System::Drawing::Size(120, 27);
			this->goButton->TabIndex = 5;
			this->goButton->Text = L"Go";
			this->goButton->Click += gcnew System::EventHandler(this, &LoadShowDialog::goButton_Click);
			// 
			// LoadShowDialog
			// 
			this->AcceptButton = this->goButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->CancelButton = this->cancelButton;
			this->ClientSize = System::Drawing::Size(324, 176);
			this->ControlBox = false;
			this->Controls->Add(this->dialogTitle);
			this->Controls->Add(this->listBox);
			this->Controls->Add(this->cancelButton);
			this->Controls->Add(this->goButton);
			this->Controls->Add(this->errorLabel);
			this->Controls->Add(this->newShowsOnly);
			this->Controls->Add(this->otherUser);
			this->Controls->Add(this->currentUserRadio);
			this->Controls->Add(this->otherUserRadio);
			this->Controls->Add(this->systemUserRadio);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->KeyPreview = true;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"LoadShowDialog";
			this->Text = L"Load Show";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &LoadShowDialog::LoadShowDialog_KeyDown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


};
}
