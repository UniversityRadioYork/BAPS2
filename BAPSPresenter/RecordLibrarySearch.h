#pragma once
#include "BAPSButton.h"
#include "BAPSListBox.h"
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
	/// Summary for RecordLibrarySearch
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class RecordLibrarySearch : public System::Windows::Forms::Form
	{
	public:
		RecordLibrarySearch(BAPSPresenterMain^ _bapsPresenterMain, System::Collections::Queue^ _queue)
			: bapsPresenterMain(_bapsPresenterMain), msgQueue(_queue)
		{
			InitializeComponent();

			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(RecordLibrarySearch::typeid));
			//this->connectionStatus->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			//this->resultsInfo->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			//this->statusStrip->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			
			/** Tag objects for the 3 buttons to find out at runtime what they are **/
			System::Object  ^number0 = safe_cast<System::Object^>(0);
			System::Object  ^number1 = 1;
			System::Object  ^number2 = 2;
			/** Set the tags correctly **/
			AddToChannel0->Tag = number0;
			AddToChannel1->Tag = number1;
			AddToChannel2->Tag = number2;
			/** Disable all the buttons **/
			AddToChannel0->Enabled = false;
			AddToChannel1->Enabled = false;
			AddToChannel2->Enabled = false;
			/** Disable the listbox **/
			ResultsBox->Enabled = false;
			/** We don't want to be tabbing onto the labels! **/
			ArtistBoxLabel->TabStop = false;
			TitleBoxLabel->TabStop = false;
			/** Set result count to be 0 **/
			numberOfResults = 0;
			/** Set to first result page **/
			pageNum = 0;
		}
		void setResultCount(System::Object^ _count);
		void add(System::Object^ _index, System::Object^ _dirtyStatus, System::String^ string);
		void handleError(System::Object^ _errorcode, System::String^ description);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~RecordLibrarySearch()
		{
			/** The fastest method turned out to be when we load the results
				into a temporary array and then add them to the listbox
			**/
			ResultsBox->Items->Clear();
			if (components)
			{
				delete components;
			}
		}
	private:
		/** The page of results to view **/
		int pageNum;
		/** Placeholder for result count **/
		int numberOfResults;
		/** A handle to the main window **/
		BAPSPresenterMain^ bapsPresenterMain;
	private: System::Windows::Forms::RadioButton^  dateReleasedRadioButton;
	private: System::Windows::Forms::CheckBox^  noncleanCheckbox;
	private: System::Windows::Forms::Button^  closeButton;
	private: System::Windows::Forms::Button^  SearchButton;
	private: System::Windows::Forms::ListBox^  ResultsBox;



			 /** handle to the global message queue **/
		System::Collections::Queue^ msgQueue;

		System::Void RadioButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void AddToChannel_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void SearchButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void Text_Enter(System::Object ^  sender, System::EventArgs ^  e);
		System::Void Artist_Leave(System::Object ^  sender, System::EventArgs ^  e);
		System::Void Title_Leave(System::Object ^  sender, System::EventArgs ^  e);
		System::Void closeButton_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void RecordLibrarySearch_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
		System::Void Some_TextChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Windows::Forms::Button^  AddToChannel0;
	private: System::Windows::Forms::Button^  AddToChannel1;
	private: System::Windows::Forms::Button^  AddToChannel2;





	private: System::Windows::Forms::RadioButton^ titleRadioButton;
	private: System::Windows::Forms::RadioButton^ artistRadioButton;
	private: System::Windows::Forms::RadioButton^ dateAddedRadioButton;
	private: System::Windows::Forms::CheckBox^ reverseOrderCheckBox;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ToolStripStatusLabel^  connectionStatus;
	private: System::Windows::Forms::StatusStrip^  statusStrip;
	private: System::Windows::Forms::ToolStripProgressBar^  progressBar;
	private: System::Windows::Forms::ToolStripStatusLabel^  resultsInfo;
	private: System::Windows::Forms::Label^  TitleBoxLabel;
	private: System::Windows::Forms::Label^  ArtistBoxLabel;
	private: System::Windows::Forms::TextBox^  Title;
	private: System::Windows::Forms::TextBox^  Artist;


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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(RecordLibrarySearch::typeid));
			this->connectionStatus = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->statusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->progressBar = (gcnew System::Windows::Forms::ToolStripProgressBar());
			this->resultsInfo = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->TitleBoxLabel = (gcnew System::Windows::Forms::Label());
			this->ArtistBoxLabel = (gcnew System::Windows::Forms::Label());
			this->Title = (gcnew System::Windows::Forms::TextBox());
			this->Artist = (gcnew System::Windows::Forms::TextBox());
			this->artistRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->titleRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->dateAddedRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->reverseOrderCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->dateReleasedRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->noncleanCheckbox = (gcnew System::Windows::Forms::CheckBox());
			this->closeButton = (gcnew System::Windows::Forms::Button());
			this->SearchButton = (gcnew System::Windows::Forms::Button());
			this->AddToChannel0 = (gcnew System::Windows::Forms::Button());
			this->AddToChannel1 = (gcnew System::Windows::Forms::Button());
			this->AddToChannel2 = (gcnew System::Windows::Forms::Button());
			this->ResultsBox = (gcnew System::Windows::Forms::ListBox());
			this->statusStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// connectionStatus
			// 
			this->connectionStatus->Name = L"connectionStatus";
			this->connectionStatus->Size = System::Drawing::Size(145, 17);
			this->connectionStatus->Spring = true;
			this->connectionStatus->Text = L"Connection: stable";
			// 
			// statusStrip
			// 
			this->statusStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->connectionStatus, 
				this->progressBar, this->resultsInfo});
			this->statusStrip->Location = System::Drawing::Point(0, 492);
			this->statusStrip->Name = L"statusStrip";
			this->statusStrip->Size = System::Drawing::Size(508, 22);
			this->statusStrip->SizingGrip = false;
			this->statusStrip->TabIndex = 11;
			this->statusStrip->Text = L"statusStrip1";
			// 
			// progressBar
			// 
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(200, 16);
			// 
			// resultsInfo
			// 
			this->resultsInfo->Name = L"resultsInfo";
			this->resultsInfo->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->resultsInfo->Size = System::Drawing::Size(145, 17);
			this->resultsInfo->Spring = true;
			this->resultsInfo->Text = L"No Results";
			// 
			// TitleBoxLabel
			// 
			this->TitleBoxLabel->BackColor = System::Drawing::Color::Transparent;
			this->TitleBoxLabel->Location = System::Drawing::Point(22, 13);
			this->TitleBoxLabel->Name = L"TitleBoxLabel";
			this->TitleBoxLabel->Size = System::Drawing::Size(40, 20);
			this->TitleBoxLabel->TabIndex = 18;
			this->TitleBoxLabel->Text = L"Title:";
			this->TitleBoxLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// ArtistBoxLabel
			// 
			this->ArtistBoxLabel->BackColor = System::Drawing::Color::Transparent;
			this->ArtistBoxLabel->Location = System::Drawing::Point(20, 41);
			this->ArtistBoxLabel->Name = L"ArtistBoxLabel";
			this->ArtistBoxLabel->Size = System::Drawing::Size(40, 20);
			this->ArtistBoxLabel->TabIndex = 17;
			this->ArtistBoxLabel->Text = L"Artist:";
			this->ArtistBoxLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// Title
			// 
			this->Title->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->Title->BackColor = System::Drawing::SystemColors::Window;
			this->Title->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->Title->Location = System::Drawing::Point(68, 12);
			this->Title->Name = L"Title";
			this->Title->Size = System::Drawing::Size(347, 21);
			this->Title->TabIndex = 0;
			this->Title->Text = L"<Enter the Title to search for>";
			this->Title->TextChanged += gcnew System::EventHandler(this, &RecordLibrarySearch::Some_TextChanged);
			this->Title->Leave += gcnew System::EventHandler(this, &RecordLibrarySearch::Title_Leave);
			this->Title->Enter += gcnew System::EventHandler(this, &RecordLibrarySearch::Text_Enter);
			// 
			// Artist
			// 
			this->Artist->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->Artist->BackColor = System::Drawing::SystemColors::Window;
			this->Artist->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->Artist->Location = System::Drawing::Point(68, 40);
			this->Artist->Name = L"Artist";
			this->Artist->Size = System::Drawing::Size(347, 21);
			this->Artist->TabIndex = 1;
			this->Artist->Text = L"<Enter the Artist to search for>";
			this->Artist->TextChanged += gcnew System::EventHandler(this, &RecordLibrarySearch::Some_TextChanged);
			this->Artist->Leave += gcnew System::EventHandler(this, &RecordLibrarySearch::Artist_Leave);
			this->Artist->Enter += gcnew System::EventHandler(this, &RecordLibrarySearch::Text_Enter);
			// 
			// artistRadioButton
			// 
			this->artistRadioButton->AutoSize = true;
			this->artistRadioButton->BackColor = System::Drawing::Color::Transparent;
			this->artistRadioButton->Location = System::Drawing::Point(117, 66);
			this->artistRadioButton->Name = L"artistRadioButton";
			this->artistRadioButton->Size = System::Drawing::Size(51, 17);
			this->artistRadioButton->TabIndex = 6;
			this->artistRadioButton->Text = L"Artist";
			this->artistRadioButton->UseVisualStyleBackColor = false;
			this->artistRadioButton->CheckedChanged += gcnew System::EventHandler(this, &RecordLibrarySearch::RadioButton_CheckedChanged);
			// 
			// titleRadioButton
			// 
			this->titleRadioButton->AutoSize = true;
			this->titleRadioButton->BackColor = System::Drawing::Color::Transparent;
			this->titleRadioButton->Checked = true;
			this->titleRadioButton->Location = System::Drawing::Point(68, 66);
			this->titleRadioButton->Name = L"titleRadioButton";
			this->titleRadioButton->Size = System::Drawing::Size(45, 17);
			this->titleRadioButton->TabIndex = 5;
			this->titleRadioButton->TabStop = true;
			this->titleRadioButton->Text = L"Title";
			this->titleRadioButton->UseVisualStyleBackColor = false;
			this->titleRadioButton->CheckedChanged += gcnew System::EventHandler(this, &RecordLibrarySearch::RadioButton_CheckedChanged);
			// 
			// dateAddedRadioButton
			// 
			this->dateAddedRadioButton->AutoSize = true;
			this->dateAddedRadioButton->BackColor = System::Drawing::Color::Transparent;
			this->dateAddedRadioButton->Location = System::Drawing::Point(168, 66);
			this->dateAddedRadioButton->Name = L"dateAddedRadioButton";
			this->dateAddedRadioButton->Size = System::Drawing::Size(82, 17);
			this->dateAddedRadioButton->TabIndex = 7;
			this->dateAddedRadioButton->Text = L"Date Added";
			this->dateAddedRadioButton->UseVisualStyleBackColor = false;
			this->dateAddedRadioButton->CheckedChanged += gcnew System::EventHandler(this, &RecordLibrarySearch::RadioButton_CheckedChanged);
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Location = System::Drawing::Point(15, 66);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(62, 17);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Order By:";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// reverseOrderCheckBox
			// 
			this->reverseOrderCheckBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->reverseOrderCheckBox->AutoSize = true;
			this->reverseOrderCheckBox->BackColor = System::Drawing::Color::Transparent;
			this->reverseOrderCheckBox->Location = System::Drawing::Point(283, 89);
			this->reverseOrderCheckBox->Name = L"reverseOrderCheckBox";
			this->reverseOrderCheckBox->Size = System::Drawing::Size(97, 17);
			this->reverseOrderCheckBox->TabIndex = 9;
			this->reverseOrderCheckBox->Text = L"Reverse Order";
			this->reverseOrderCheckBox->UseVisualStyleBackColor = false;
			this->reverseOrderCheckBox->CheckedChanged += gcnew System::EventHandler(this, &RecordLibrarySearch::Some_TextChanged);
			// 
			// dateReleasedRadioButton
			// 
			this->dateReleasedRadioButton->AutoSize = true;
			this->dateReleasedRadioButton->BackColor = System::Drawing::Color::Transparent;
			this->dateReleasedRadioButton->Location = System::Drawing::Point(254, 66);
			this->dateReleasedRadioButton->Name = L"dateReleasedRadioButton";
			this->dateReleasedRadioButton->Size = System::Drawing::Size(95, 17);
			this->dateReleasedRadioButton->TabIndex = 8;
			this->dateReleasedRadioButton->Text = L"Date Released";
			this->dateReleasedRadioButton->UseVisualStyleBackColor = false;
			this->dateReleasedRadioButton->CheckedChanged += gcnew System::EventHandler(this, &RecordLibrarySearch::RadioButton_CheckedChanged);
			// 
			// noncleanCheckbox
			// 
			this->noncleanCheckbox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->noncleanCheckbox->AutoSize = true;
			this->noncleanCheckbox->BackColor = System::Drawing::Color::Transparent;
			this->noncleanCheckbox->Location = System::Drawing::Point(383, 89);
			this->noncleanCheckbox->Name = L"noncleanCheckbox";
			this->noncleanCheckbox->Size = System::Drawing::Size(110, 17);
			this->noncleanCheckbox->TabIndex = 10;
			this->noncleanCheckbox->Text = L"Non-Clean Tracks";
			this->noncleanCheckbox->UseVisualStyleBackColor = false;
			this->noncleanCheckbox->CheckedChanged += gcnew System::EventHandler(this, &RecordLibrarySearch::Some_TextChanged);
			// 
			// closeButton
			// 
			this->closeButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->closeButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->closeButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->closeButton->Location = System::Drawing::Point(421, 40);
			this->closeButton->Name = L"closeButton";
			this->closeButton->Size = System::Drawing::Size(75, 23);
			this->closeButton->TabIndex = 3;
			this->closeButton->Text = L"Close";
			this->closeButton->Click += gcnew System::EventHandler(this, &RecordLibrarySearch::closeButton_Click);
			// 
			// SearchButton
			// 
			this->SearchButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->SearchButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->SearchButton->Location = System::Drawing::Point(421, 12);
			this->SearchButton->Name = L"SearchButton";
			this->SearchButton->Size = System::Drawing::Size(75, 23);
			this->SearchButton->TabIndex = 2;
			this->SearchButton->Text = L"Search";
			this->SearchButton->Click += gcnew System::EventHandler(this, &RecordLibrarySearch::SearchButton_Click);
			// 
			// AddToChannel0
			// 
			this->AddToChannel0->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->AddToChannel0->BackColor = System::Drawing::Color::Transparent;
			this->AddToChannel0->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->AddToChannel0->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->AddToChannel0->Location = System::Drawing::Point(12, 447);
			this->AddToChannel0->Name = L"AddToChannel0";
			this->AddToChannel0->Size = System::Drawing::Size(156, 36);
			this->AddToChannel0->TabIndex = 12;
			this->AddToChannel0->Text = L"Add to Channel 1";
			this->AddToChannel0->UseVisualStyleBackColor = false;
			this->AddToChannel0->Click += gcnew System::EventHandler(this, &RecordLibrarySearch::AddToChannel_Click);
			// 
			// AddToChannel1
			// 
			this->AddToChannel1->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->AddToChannel1->BackColor = System::Drawing::Color::Transparent;
			this->AddToChannel1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->AddToChannel1->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->AddToChannel1->Location = System::Drawing::Point(177, 447);
			this->AddToChannel1->Name = L"AddToChannel1";
			this->AddToChannel1->Size = System::Drawing::Size(156, 36);
			this->AddToChannel1->TabIndex = 13;
			this->AddToChannel1->Text = L"Add to Channel 2";
			this->AddToChannel1->UseVisualStyleBackColor = false;
			this->AddToChannel1->Click += gcnew System::EventHandler(this, &RecordLibrarySearch::AddToChannel_Click);
			// 
			// AddToChannel2
			// 
			this->AddToChannel2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->AddToChannel2->BackColor = System::Drawing::Color::Transparent;
			this->AddToChannel2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->AddToChannel2->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->AddToChannel2->Location = System::Drawing::Point(340, 447);
			this->AddToChannel2->Name = L"AddToChannel2";
			this->AddToChannel2->Size = System::Drawing::Size(156, 36);
			this->AddToChannel2->TabIndex = 14;
			this->AddToChannel2->Text = L"Add to Channel 3";
			this->AddToChannel2->UseVisualStyleBackColor = false;
			this->AddToChannel2->Click += gcnew System::EventHandler(this, &RecordLibrarySearch::AddToChannel_Click);
			// 
			// ResultsBox
			// 
			this->ResultsBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->ResultsBox->Location = System::Drawing::Point(12, 112);
			this->ResultsBox->Name = L"ResultsBox";
			this->ResultsBox->Size = System::Drawing::Size(484, 329);
			this->ResultsBox->TabIndex = 11;
			// 
			// RecordLibrarySearch
			// 
			this->AcceptButton = this->SearchButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->closeButton;
			this->ClientSize = System::Drawing::Size(508, 514);
			this->ControlBox = false;
			this->Controls->Add(this->ResultsBox);
			this->Controls->Add(this->SearchButton);
			this->Controls->Add(this->closeButton);
			this->Controls->Add(this->titleRadioButton);
			this->Controls->Add(this->AddToChannel2);
			this->Controls->Add(this->AddToChannel1);
			this->Controls->Add(this->AddToChannel0);
			this->Controls->Add(this->statusStrip);
			this->Controls->Add(this->TitleBoxLabel);
			this->Controls->Add(this->ArtistBoxLabel);
			this->Controls->Add(this->Title);
			this->Controls->Add(this->Artist);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->noncleanCheckbox);
			this->Controls->Add(this->reverseOrderCheckBox);
			this->Controls->Add(this->dateReleasedRadioButton);
			this->Controls->Add(this->dateAddedRadioButton);
			this->Controls->Add(this->artistRadioButton);
			this->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->KeyPreview = true;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(516, 309);
			this->Name = L"RecordLibrarySearch";
			this->ShowInTaskbar = false;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Record Library Search";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &RecordLibrarySearch::RecordLibrarySearch_KeyDown);
			this->statusStrip->ResumeLayout(false);
			this->statusStrip->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


};
}
