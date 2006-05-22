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
		}
		void setResultCount(System::Object^ _count);
		void add(System::Object^ _index, System::String^ string);
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
			ResultsBox->clearList();
			if (components)
			{
				delete components;
			}
		}
	private:
		/** Placeholder for result count **/
		int numberOfResults;
		/** A handle to the main window **/
		BAPSPresenterMain^ bapsPresenterMain;
	private: BAPSPresenter::BAPSButton^  SearchButton;
	private: BAPSPresenter::BAPSButton^  AddToChannel0;
	private: BAPSPresenter::BAPSButton^  AddToChannel1;
	private: BAPSPresenter::BAPSButton^  AddToChannel2;
	private: BAPSPresenter::BAPSListBox^  ResultsBox;
	private: BAPSPresenter::BAPSButton^  closeButton;

			 /** handle to the global message queue **/
		System::Collections::Queue^ msgQueue;

		System::Void AddToChannel_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void SearchButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void Text_Enter(System::Object ^  sender, System::EventArgs ^  e);
		System::Void Artist_Leave(System::Object ^  sender, System::EventArgs ^  e);
		System::Void Title_Leave(System::Object ^  sender, System::EventArgs ^  e);
		System::Void closeButton_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void RecordLibrarySearch_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	private: System::Windows::Forms::ToolStripStatusLabel^  connectionStatus;
	protected: 
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
			this->ResultsBox = (gcnew BAPSPresenter::BAPSListBox());
			this->AddToChannel2 = (gcnew BAPSPresenter::BAPSButton());
			this->AddToChannel1 = (gcnew BAPSPresenter::BAPSButton());
			this->AddToChannel0 = (gcnew BAPSPresenter::BAPSButton());
			this->SearchButton = (gcnew BAPSPresenter::BAPSButton());
			this->closeButton = (gcnew BAPSPresenter::BAPSButton());
			this->statusStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// connectionStatus
			// 
			this->connectionStatus->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"connectionStatus.BackgroundImage")));
			this->connectionStatus->Name = L"connectionStatus";
			this->connectionStatus->Size = System::Drawing::Size(124, 17);
			this->connectionStatus->Spring = true;
			this->connectionStatus->Text = L"Connection: stable";
			// 
			// statusStrip
			// 
			this->statusStrip->BackColor = System::Drawing::Color::AntiqueWhite;
			this->statusStrip->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"statusStrip.BackgroundImage")));
			this->statusStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->connectionStatus, 
				this->progressBar, this->resultsInfo});
			this->statusStrip->Location = System::Drawing::Point(0, 365);
			this->statusStrip->Name = L"statusStrip";
			this->statusStrip->Size = System::Drawing::Size(465, 22);
			this->statusStrip->SizingGrip = false;
			this->statusStrip->TabIndex = 11;
			this->statusStrip->Text = L"statusStrip1";
			// 
			// progressBar
			// 
			this->progressBar->ForeColor = System::Drawing::Color::Tan;
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(200, 16);
			// 
			// resultsInfo
			// 
			this->resultsInfo->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"resultsInfo.BackgroundImage")));
			this->resultsInfo->Name = L"resultsInfo";
			this->resultsInfo->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->resultsInfo->Size = System::Drawing::Size(124, 17);
			this->resultsInfo->Spring = true;
			this->resultsInfo->Text = L"No Results";
			// 
			// TitleBoxLabel
			// 
			this->TitleBoxLabel->BackColor = System::Drawing::Color::Transparent;
			this->TitleBoxLabel->Location = System::Drawing::Point(20, 44);
			this->TitleBoxLabel->Name = L"TitleBoxLabel";
			this->TitleBoxLabel->Size = System::Drawing::Size(40, 24);
			this->TitleBoxLabel->TabIndex = 18;
			this->TitleBoxLabel->Text = L"Title:";
			// 
			// ArtistBoxLabel
			// 
			this->ArtistBoxLabel->BackColor = System::Drawing::Color::Transparent;
			this->ArtistBoxLabel->Location = System::Drawing::Point(20, 12);
			this->ArtistBoxLabel->Name = L"ArtistBoxLabel";
			this->ArtistBoxLabel->Size = System::Drawing::Size(40, 24);
			this->ArtistBoxLabel->TabIndex = 17;
			this->ArtistBoxLabel->Text = L"Artist:";
			// 
			// Title
			// 
			this->Title->BackColor = System::Drawing::Color::SeaShell;
			this->Title->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->Title->Location = System::Drawing::Point(68, 44);
			this->Title->Name = L"Title";
			this->Title->Size = System::Drawing::Size(256, 20);
			this->Title->TabIndex = 1;
			this->Title->Text = L"<Enter the Title to search for>";
			this->Title->Enter += gcnew System::EventHandler(this, &RecordLibrarySearch::Text_Enter);
			this->Title->Leave += gcnew System::EventHandler(this, &RecordLibrarySearch::Title_Leave);
			// 
			// Artist
			// 
			this->Artist->BackColor = System::Drawing::Color::SeaShell;
			this->Artist->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->Artist->Location = System::Drawing::Point(68, 12);
			this->Artist->Name = L"Artist";
			this->Artist->Size = System::Drawing::Size(256, 20);
			this->Artist->TabIndex = 0;
			this->Artist->Text = L"<Enter the Artist to search for>";
			this->Artist->Enter += gcnew System::EventHandler(this, &RecordLibrarySearch::Text_Enter);
			this->Artist->Leave += gcnew System::EventHandler(this, &RecordLibrarySearch::Artist_Leave);
			// 
			// ResultsBox
			// 
			this->ResultsBox->Location = System::Drawing::Point(12, 73);
			this->ResultsBox->Name = L"ResultsBox";
			this->ResultsBox->SelectedIndexEnabled = true;
			this->ResultsBox->Size = System::Drawing::Size(439, 235);
			this->ResultsBox->TabIndex = 3;
			this->ResultsBox->Text = L"bapsListBox1";
			// 
			// AddToChannel2
			// 
			this->AddToChannel2->BackColor = System::Drawing::Color::Transparent;
			this->AddToChannel2->DialogResult = System::Windows::Forms::DialogResult::None;
			this->AddToChannel2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->AddToChannel2->HighlightColor = System::Drawing::Color::Red;
			this->AddToChannel2->Highlighted = false;
			this->AddToChannel2->Location = System::Drawing::Point(322, 320);
			this->AddToChannel2->Name = L"AddToChannel2";
			this->AddToChannel2->Size = System::Drawing::Size(130, 36);
			this->AddToChannel2->TabIndex = 6;
			this->AddToChannel2->Text = L"Add to List C";
			this->AddToChannel2->Click += gcnew System::EventHandler(this, &RecordLibrarySearch::AddToChannel_Click);
			// 
			// AddToChannel1
			// 
			this->AddToChannel1->BackColor = System::Drawing::Color::Transparent;
			this->AddToChannel1->DialogResult = System::Windows::Forms::DialogResult::None;
			this->AddToChannel1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->AddToChannel1->HighlightColor = System::Drawing::Color::Red;
			this->AddToChannel1->Highlighted = false;
			this->AddToChannel1->Location = System::Drawing::Point(167, 320);
			this->AddToChannel1->Name = L"AddToChannel1";
			this->AddToChannel1->Size = System::Drawing::Size(130, 36);
			this->AddToChannel1->TabIndex = 5;
			this->AddToChannel1->Text = L"Add to List B";
			this->AddToChannel1->Click += gcnew System::EventHandler(this, &RecordLibrarySearch::AddToChannel_Click);
			// 
			// AddToChannel0
			// 
			this->AddToChannel0->BackColor = System::Drawing::Color::Transparent;
			this->AddToChannel0->DialogResult = System::Windows::Forms::DialogResult::None;
			this->AddToChannel0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->AddToChannel0->HighlightColor = System::Drawing::Color::Red;
			this->AddToChannel0->Highlighted = false;
			this->AddToChannel0->Location = System::Drawing::Point(12, 320);
			this->AddToChannel0->Name = L"AddToChannel0";
			this->AddToChannel0->Size = System::Drawing::Size(130, 36);
			this->AddToChannel0->TabIndex = 4;
			this->AddToChannel0->Text = L"Add to List A";
			this->AddToChannel0->Click += gcnew System::EventHandler(this, &RecordLibrarySearch::AddToChannel_Click);
			// 
			// SearchButton
			// 
			this->SearchButton->BackColor = System::Drawing::Color::Transparent;
			this->SearchButton->DialogResult = System::Windows::Forms::DialogResult::None;
			this->SearchButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->SearchButton->HighlightColor = System::Drawing::Color::Red;
			this->SearchButton->Highlighted = false;
			this->SearchButton->Location = System::Drawing::Point(335, 23);
			this->SearchButton->Name = L"SearchButton";
			this->SearchButton->Size = System::Drawing::Size(116, 41);
			this->SearchButton->TabIndex = 2;
			this->SearchButton->Text = L"Search";
			this->SearchButton->Click += gcnew System::EventHandler(this, &RecordLibrarySearch::SearchButton_Click);
			// 
			// closeButton
			// 
			this->closeButton->BackColor = System::Drawing::Color::Transparent;
			this->closeButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->closeButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->closeButton->HighlightColor = System::Drawing::Color::Red;
			this->closeButton->Highlighted = false;
			this->closeButton->Location = System::Drawing::Point(416, 6);
			this->closeButton->Name = L"closeButton";
			this->closeButton->Size = System::Drawing::Size(43, 11);
			this->closeButton->TabIndex = 2;
			this->closeButton->Text = L"Close";
			this->closeButton->Click += gcnew System::EventHandler(this, &RecordLibrarySearch::closeButton_Click);
			// 
			// RecordLibrarySearch
			// 
			this->AcceptButton = this->SearchButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->CancelButton = this->closeButton;
			this->ClientSize = System::Drawing::Size(465, 387);
			this->ControlBox = false;
			this->Controls->Add(this->ResultsBox);
			this->Controls->Add(this->AddToChannel2);
			this->Controls->Add(this->AddToChannel1);
			this->Controls->Add(this->AddToChannel0);
			this->Controls->Add(this->closeButton);
			this->Controls->Add(this->SearchButton);
			this->Controls->Add(this->statusStrip);
			this->Controls->Add(this->TitleBoxLabel);
			this->Controls->Add(this->ArtistBoxLabel);
			this->Controls->Add(this->Title);
			this->Controls->Add(this->Artist);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->KeyPreview = true;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"RecordLibrarySearch";
			this->ShowInTaskbar = false;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
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
