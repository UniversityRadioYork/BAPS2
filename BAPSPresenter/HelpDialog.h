#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace BAPSPresenter {

	/// <summary>
	/// Summary for HelpDialog
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class HelpDialog : public System::Windows::Forms::Form
	{
	public:
		HelpDialog(void)
		{
			InitializeComponent();
			writeText();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~HelpDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		/** Write the help text into the boxes **/
		void writeText();



	protected: 









	private: System::Windows::Forms::Label^  loadingText;

	private: System::Windows::Forms::Label^  textText;
	private: System::Windows::Forms::TabPage^  textPage;
	private: System::Windows::Forms::Label^  textLabel;
	private: System::Windows::Forms::Label^  loadingLabel;
	private: System::Windows::Forms::TabPage^  loadShowPage;
	private: System::Windows::Forms::Label^  modifyLabel;



	private: System::Windows::Forms::Label^  modifyText;
	private: System::Windows::Forms::TabPage^  modifyPlaylistPage;

	private: System::Windows::Forms::Label^  ppsText;
	private: System::Windows::Forms::Label^  controlLabel;

	private: System::Windows::Forms::Label^  faqLabel;

	private: System::Windows::Forms::Label^  faqText;
	private: System::Windows::Forms::TabPage^  faqPage;

	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  searchPage;
	private: System::Windows::Forms::Label^  searchText;
	private: System::Windows::Forms::Label^  searchLabel;
	private: System::Windows::Forms::TabPage^  controlsPage;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;










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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(HelpDialog::typeid));
			this->loadingText = (gcnew System::Windows::Forms::Label());
			this->textText = (gcnew System::Windows::Forms::Label());
			this->textPage = (gcnew System::Windows::Forms::TabPage());
			this->textLabel = (gcnew System::Windows::Forms::Label());
			this->loadingLabel = (gcnew System::Windows::Forms::Label());
			this->loadShowPage = (gcnew System::Windows::Forms::TabPage());
			this->modifyLabel = (gcnew System::Windows::Forms::Label());
			this->modifyText = (gcnew System::Windows::Forms::Label());
			this->modifyPlaylistPage = (gcnew System::Windows::Forms::TabPage());
			this->ppsText = (gcnew System::Windows::Forms::Label());
			this->controlLabel = (gcnew System::Windows::Forms::Label());
			this->faqLabel = (gcnew System::Windows::Forms::Label());
			this->faqText = (gcnew System::Windows::Forms::Label());
			this->faqPage = (gcnew System::Windows::Forms::TabPage());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->searchPage = (gcnew System::Windows::Forms::TabPage());
			this->searchText = (gcnew System::Windows::Forms::Label());
			this->searchLabel = (gcnew System::Windows::Forms::Label());
			this->controlsPage = (gcnew System::Windows::Forms::TabPage());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->textPage->SuspendLayout();
			this->loadShowPage->SuspendLayout();
			this->modifyPlaylistPage->SuspendLayout();
			this->faqPage->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->searchPage->SuspendLayout();
			this->controlsPage->SuspendLayout();
			this->SuspendLayout();
			// 
			// loadingText
			// 
			this->loadingText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->loadingText->Location = System::Drawing::Point(8, 48);
			this->loadingText->Name = L"loadingText";
			this->loadingText->Size = System::Drawing::Size(608, 344);
			this->loadingText->TabIndex = 9;
			// 
			// textText
			// 
			this->textText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textText->Location = System::Drawing::Point(8, 48);
			this->textText->Name = L"textText";
			this->textText->Size = System::Drawing::Size(608, 344);
			this->textText->TabIndex = 7;
			// 
			// textPage
			// 
			this->textPage->Controls->Add(this->textText);
			this->textPage->Controls->Add(this->textLabel);
			this->textPage->Location = System::Drawing::Point(4, 22);
			this->textPage->Name = L"textPage";
			this->textPage->Size = System::Drawing::Size(662, 475);
			this->textPage->TabIndex = 5;
			this->textPage->Text = L"Text in playlists";
			this->textPage->UseVisualStyleBackColor = true;
			// 
			// textLabel
			// 
			this->textLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->textLabel->Location = System::Drawing::Point(8, 8);
			this->textLabel->Name = L"textLabel";
			this->textLabel->Size = System::Drawing::Size(224, 32);
			this->textLabel->TabIndex = 6;
			this->textLabel->Text = L"Text in playlists";
			this->textLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// loadingLabel
			// 
			this->loadingLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->loadingLabel->Location = System::Drawing::Point(8, 8);
			this->loadingLabel->Name = L"loadingLabel";
			this->loadingLabel->Size = System::Drawing::Size(224, 32);
			this->loadingLabel->TabIndex = 8;
			this->loadingLabel->Text = L"Loading A Show";
			this->loadingLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// loadShowPage
			// 
			this->loadShowPage->Controls->Add(this->loadingText);
			this->loadShowPage->Controls->Add(this->loadingLabel);
			this->loadShowPage->Location = System::Drawing::Point(4, 22);
			this->loadShowPage->Name = L"loadShowPage";
			this->loadShowPage->Size = System::Drawing::Size(662, 475);
			this->loadShowPage->TabIndex = 1;
			this->loadShowPage->Text = L"Loading a Show";
			this->loadShowPage->UseVisualStyleBackColor = true;
			// 
			// modifyLabel
			// 
			this->modifyLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->modifyLabel->Location = System::Drawing::Point(8, 8);
			this->modifyLabel->Name = L"modifyLabel";
			this->modifyLabel->Size = System::Drawing::Size(280, 32);
			this->modifyLabel->TabIndex = 2;
			this->modifyLabel->Text = L"Modify a track list";
			this->modifyLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// modifyText
			// 
			this->modifyText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->modifyText->Location = System::Drawing::Point(8, 48);
			this->modifyText->Name = L"modifyText";
			this->modifyText->Size = System::Drawing::Size(608, 422);
			this->modifyText->TabIndex = 3;
			// 
			// modifyPlaylistPage
			// 
			this->modifyPlaylistPage->Controls->Add(this->richTextBox1);
			this->modifyPlaylistPage->Controls->Add(this->modifyText);
			this->modifyPlaylistPage->Controls->Add(this->modifyLabel);
			this->modifyPlaylistPage->Location = System::Drawing::Point(4, 22);
			this->modifyPlaylistPage->Name = L"modifyPlaylistPage";
			this->modifyPlaylistPage->Size = System::Drawing::Size(662, 475);
			this->modifyPlaylistPage->TabIndex = 2;
			this->modifyPlaylistPage->Text = L"Modify a track list";
			this->modifyPlaylistPage->UseVisualStyleBackColor = true;
			// 
			// ppsText
			// 
			this->ppsText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->ppsText->Location = System::Drawing::Point(8, 48);
			this->ppsText->Name = L"ppsText";
			this->ppsText->Size = System::Drawing::Size(608, 422);
			this->ppsText->TabIndex = 1;
			// 
			// controlLabel
			// 
			this->controlLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->controlLabel->Location = System::Drawing::Point(8, 8);
			this->controlLabel->Name = L"controlLabel";
			this->controlLabel->Size = System::Drawing::Size(280, 32);
			this->controlLabel->TabIndex = 0;
			this->controlLabel->Text = L"Controlling Playback";
			this->controlLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// faqLabel
			// 
			this->faqLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->faqLabel->Location = System::Drawing::Point(8, 8);
			this->faqLabel->Name = L"faqLabel";
			this->faqLabel->Size = System::Drawing::Size(80, 32);
			this->faqLabel->TabIndex = 1;
			this->faqLabel->Text = L"FAQ";
			this->faqLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// faqText
			// 
			this->faqText->Font = (gcnew System::Drawing::Font(L"Lucida Console", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->faqText->Location = System::Drawing::Point(8, 48);
			this->faqText->Name = L"faqText";
			this->faqText->Size = System::Drawing::Size(608, 424);
			this->faqText->TabIndex = 0;
			// 
			// faqPage
			// 
			this->faqPage->BackColor = System::Drawing::SystemColors::Control;
			this->faqPage->Controls->Add(this->faqLabel);
			this->faqPage->Controls->Add(this->faqText);
			this->faqPage->Location = System::Drawing::Point(4, 22);
			this->faqPage->Name = L"faqPage";
			this->faqPage->Size = System::Drawing::Size(662, 475);
			this->faqPage->TabIndex = 0;
			this->faqPage->Text = L"FAQ";
			this->faqPage->UseVisualStyleBackColor = true;
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->faqPage);
			this->tabControl1->Controls->Add(this->searchPage);
			this->tabControl1->Controls->Add(this->controlsPage);
			this->tabControl1->Controls->Add(this->modifyPlaylistPage);
			this->tabControl1->Controls->Add(this->textPage);
			this->tabControl1->Controls->Add(this->loadShowPage);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(670, 501);
			this->tabControl1->TabIndex = 1;
			// 
			// searchPage
			// 
			this->searchPage->Controls->Add(this->searchText);
			this->searchPage->Controls->Add(this->searchLabel);
			this->searchPage->Location = System::Drawing::Point(4, 22);
			this->searchPage->Name = L"searchPage";
			this->searchPage->Size = System::Drawing::Size(662, 475);
			this->searchPage->TabIndex = 4;
			this->searchPage->Text = L"Search Record Library";
			this->searchPage->UseVisualStyleBackColor = true;
			// 
			// searchText
			// 
			this->searchText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->searchText->Location = System::Drawing::Point(8, 48);
			this->searchText->Name = L"searchText";
			this->searchText->Size = System::Drawing::Size(608, 344);
			this->searchText->TabIndex = 5;
			// 
			// searchLabel
			// 
			this->searchLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->searchLabel->Location = System::Drawing::Point(8, 8);
			this->searchLabel->Name = L"searchLabel";
			this->searchLabel->Size = System::Drawing::Size(320, 32);
			this->searchLabel->TabIndex = 4;
			this->searchLabel->Text = L"Search Record Library";
			this->searchLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// controlsPage
			// 
			this->controlsPage->Controls->Add(this->ppsText);
			this->controlsPage->Controls->Add(this->controlLabel);
			this->controlsPage->Location = System::Drawing::Point(4, 22);
			this->controlsPage->Name = L"controlsPage";
			this->controlsPage->Size = System::Drawing::Size(662, 475);
			this->controlsPage->TabIndex = 3;
			this->controlsPage->Text = L"Controlling Playback";
			this->controlsPage->UseVisualStyleBackColor = true;
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(352, 30);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(234, 229);
			this->richTextBox1->TabIndex = 4;
			this->richTextBox1->Text = L"";
			// 
			// HelpDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(670, 501);
			this->Controls->Add(this->tabControl1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"HelpDialog";
			this->Text = L"Help System";
			this->textPage->ResumeLayout(false);
			this->loadShowPage->ResumeLayout(false);
			this->modifyPlaylistPage->ResumeLayout(false);
			this->faqPage->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->searchPage->ResumeLayout(false);
			this->controlsPage->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
