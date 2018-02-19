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
			this->todaysShowsRadio->Tag = safe_cast<System::Object^>(0);
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





	private: System::Windows::Forms::Button^  goButton;
	private: System::Windows::Forms::Button^  cancelButton;
	private: System::Windows::Forms::ListBox^  listBox;


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
	private: System::Windows::Forms::RadioButton^  todaysShowsRadio;

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
			this->todaysShowsRadio = (gcnew System::Windows::Forms::RadioButton());
			this->otherUserRadio = (gcnew System::Windows::Forms::RadioButton());
			this->systemUserRadio = (gcnew System::Windows::Forms::RadioButton());
			this->goButton = (gcnew System::Windows::Forms::Button());
			this->cancelButton = (gcnew System::Windows::Forms::Button());
			this->listBox = (gcnew System::Windows::Forms::ListBox());
			this->SuspendLayout();
			this->errorLabel->BackColor = System::Drawing::Color::Transparent;
			this->errorLabel->ForeColor = System::Drawing::Color::Red;
			this->errorLabel->Location = System::Drawing::Point(12, 3);
			this->errorLabel->Name = L"errorLabel";
			this->errorLabel->Size = System::Drawing::Size(310, 16);
			this->errorLabel->TabIndex = 100;
			this->newShowsOnly->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->newShowsOnly->BackColor = System::Drawing::Color::Transparent;
			this->newShowsOnly->Checked = true;
			this->newShowsOnly->CheckState = System::Windows::Forms::CheckState::Checked;
			this->newShowsOnly->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->newShowsOnly->Location = System::Drawing::Point(220, 22);
			this->newShowsOnly->Name = L"newShowsOnly";
			this->newShowsOnly->Size = System::Drawing::Size(102, 24);
			this->newShowsOnly->TabIndex = 1;
			this->newShowsOnly->Text = L"New shows only";
			this->newShowsOnly->UseVisualStyleBackColor = false;
			this->otherUser->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->otherUser->BackColor = System::Drawing::SystemColors::Window;
			this->otherUser->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->otherUser->ForeColor = System::Drawing::SystemColors::WindowText;
			this->otherUser->Location = System::Drawing::Point(98, 84);
			this->otherUser->Name = L"otherUser";
			this->otherUser->Size = System::Drawing::Size(224, 21);
			this->otherUser->TabIndex = 4;
			this->otherUser->Text = L"<E-mail / BAPS showid>";
			this->otherUser->Enter += gcnew System::EventHandler(this, &LoadShowDialog::otherUser_Enter);
			this->todaysShowsRadio->BackColor = System::Drawing::Color::Transparent;
			this->todaysShowsRadio->FlatAppearance->CheckedBackColor = System::Drawing::Color::SeaShell;
			this->todaysShowsRadio->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->todaysShowsRadio->Location = System::Drawing::Point(13, 22);
			this->todaysShowsRadio->Name = L"todaysShowsRadio";
			this->todaysShowsRadio->Size = System::Drawing::Size(104, 24);
			this->todaysShowsRadio->TabIndex = 0;
			this->todaysShowsRadio->Text = L"Today\'s shows";
			this->todaysShowsRadio->UseVisualStyleBackColor = false;
			this->todaysShowsRadio->CheckedChanged += gcnew System::EventHandler(this, &LoadShowDialog::check_Changed);
			this->otherUserRadio->BackColor = System::Drawing::Color::Transparent;
			this->otherUserRadio->Checked = true;
			this->otherUserRadio->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->otherUserRadio->Location = System::Drawing::Point(13, 81);
			this->otherUserRadio->Name = L"otherUserRadio";
			this->otherUserRadio->Size = System::Drawing::Size(80, 23);
			this->otherUserRadio->TabIndex = 3;
			this->otherUserRadio->TabStop = true;
			this->otherUserRadio->Text = L"Other user:";
			this->otherUserRadio->UseVisualStyleBackColor = false;
			this->otherUserRadio->CheckedChanged += gcnew System::EventHandler(this, &LoadShowDialog::check_Changed);
			this->systemUserRadio->BackColor = System::Drawing::Color::Transparent;
			this->systemUserRadio->FlatAppearance->BorderSize = 3;
			this->systemUserRadio->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->systemUserRadio->Location = System::Drawing::Point(13, 52);
			this->systemUserRadio->Name = L"systemUserRadio";
			this->systemUserRadio->Size = System::Drawing::Size(168, 23);
			this->systemUserRadio->TabIndex = 2;
			this->systemUserRadio->Text = L"Recommended Audio";
			this->systemUserRadio->UseVisualStyleBackColor = false;
			this->systemUserRadio->CheckedChanged += gcnew System::EventHandler(this, &LoadShowDialog::check_Changed);
			this->goButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->goButton->Location = System::Drawing::Point(12, 130);
			this->goButton->Name = L"goButton";
			this->goButton->Size = System::Drawing::Size(75, 23);
			this->goButton->TabIndex = 5;
			this->goButton->Text = L"Go";
			this->goButton->UseVisualStyleBackColor = true;
			this->goButton->Click += gcnew System::EventHandler(this, &LoadShowDialog::goButton_Click);
			this->cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->cancelButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cancelButton->Location = System::Drawing::Point(247, 130);
			this->cancelButton->Name = L"cancelButton";
			this->cancelButton->Size = System::Drawing::Size(75, 23);
			this->cancelButton->TabIndex = 6;
			this->cancelButton->Text = L"Cancel";
			this->cancelButton->UseVisualStyleBackColor = true;
			this->cancelButton->Click += gcnew System::EventHandler(this, &LoadShowDialog::cancelButton_Click);
			this->listBox->FormattingEnabled = true;
			this->listBox->Location = System::Drawing::Point(12, 3);
			this->listBox->Name = L"listBox";
			this->listBox->Size = System::Drawing::Size(310, 121);
			this->listBox->TabIndex = 101;
			this->listBox->Visible = false;
			this->listBox->SelectedIndexChanged += gcnew System::EventHandler(this, &LoadShowDialog::listBox_SelectedIndexChanged);
			this->AcceptButton = this->goButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->cancelButton;
			this->ClientSize = System::Drawing::Size(334, 161);
			this->ControlBox = false;
			this->Controls->Add(this->listBox);
			this->Controls->Add(this->cancelButton);
			this->Controls->Add(this->goButton);
			this->Controls->Add(this->errorLabel);
			this->Controls->Add(this->newShowsOnly);
			this->Controls->Add(this->otherUser);
			this->Controls->Add(this->otherUserRadio);
			this->Controls->Add(this->systemUserRadio);
			this->Controls->Add(this->todaysShowsRadio);
			this->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
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
