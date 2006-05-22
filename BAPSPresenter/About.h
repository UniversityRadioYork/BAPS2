#pragma once
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
	/// Summary for About
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class About : public System::Windows::Forms::Form
	{
	public:
		About(BAPSPresenterMain^ _bapsPresenterMain)
			: bapsPresenterMain(_bapsPresenterMain)
		{
			InitializeComponent();
			pCompileDateText->Text = __DATE__;
			pCompileTimeText->Text = __TIME__;
			pVersionText->Text = System::Reflection::Assembly::GetExecutingAssembly()->GetName()->Version->ToString();
			pAuthorText->Text = L"Matthew Fortune\nUI based on work by:\nMark Fenton";

		}
		void serverVersion(System::String^ version, System::String^ date, System::String^ time, System::String^ author)
		{
			sCompileDateText->Text = date;
			sCompileTimeText->Text = time;
			sVersionText->Text = version;
			sAuthorText->Text = author;
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~About()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		/** A handle to the main window **/
		BAPSPresenterMain^ bapsPresenterMain;
	private: System::Windows::Forms::Label^  sVersionLabel;
	private: System::Windows::Forms::Label^  sCompileDateLabel;
	private: System::Windows::Forms::Label^  sCompileTimeLabel;
	private: System::Windows::Forms::Label^  sAuthorLabel;
	private: System::Windows::Forms::Label^  sVersionText;
	private: System::Windows::Forms::GroupBox^  presenterGroup;
	private: System::Windows::Forms::Label^  pVersionLabel;
	private: System::Windows::Forms::Label^  pCompileDateLabel;
	private: System::Windows::Forms::Label^  pCompileTimeLabel;
	private: System::Windows::Forms::Label^  pAuthorLabel;
	private: System::Windows::Forms::Label^  pVersionText;
	private: System::Windows::Forms::Label^  pCompileDateText;
	private: System::Windows::Forms::Label^  pCompileTimeText;
	private: System::Windows::Forms::Label^  pAuthorText;
	private: System::Windows::Forms::Label^  sCompileDateText;
	private: System::Windows::Forms::Label^  sCompileTimeText;
	private: System::Windows::Forms::Label^  sAuthorText;
	private: System::Windows::Forms::Label^  mailTitle;
	private: System::Windows::Forms::GroupBox^  serverGroup;

		System::Void About_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(About::typeid));
			this->sVersionLabel = (gcnew System::Windows::Forms::Label());
			this->sCompileDateLabel = (gcnew System::Windows::Forms::Label());
			this->sCompileTimeLabel = (gcnew System::Windows::Forms::Label());
			this->sAuthorLabel = (gcnew System::Windows::Forms::Label());
			this->sVersionText = (gcnew System::Windows::Forms::Label());
			this->presenterGroup = (gcnew System::Windows::Forms::GroupBox());
			this->pVersionLabel = (gcnew System::Windows::Forms::Label());
			this->pCompileDateLabel = (gcnew System::Windows::Forms::Label());
			this->pCompileTimeLabel = (gcnew System::Windows::Forms::Label());
			this->pAuthorLabel = (gcnew System::Windows::Forms::Label());
			this->pVersionText = (gcnew System::Windows::Forms::Label());
			this->pCompileDateText = (gcnew System::Windows::Forms::Label());
			this->pCompileTimeText = (gcnew System::Windows::Forms::Label());
			this->pAuthorText = (gcnew System::Windows::Forms::Label());
			this->sCompileDateText = (gcnew System::Windows::Forms::Label());
			this->sCompileTimeText = (gcnew System::Windows::Forms::Label());
			this->sAuthorText = (gcnew System::Windows::Forms::Label());
			this->mailTitle = (gcnew System::Windows::Forms::Label());
			this->serverGroup = (gcnew System::Windows::Forms::GroupBox());
			this->presenterGroup->SuspendLayout();
			this->serverGroup->SuspendLayout();
			this->SuspendLayout();
			// 
			// sVersionLabel
			// 
			this->sVersionLabel->Location = System::Drawing::Point(8, 16);
			this->sVersionLabel->Name = L"sVersionLabel";
			this->sVersionLabel->Size = System::Drawing::Size(56, 16);
			this->sVersionLabel->TabIndex = 6;
			this->sVersionLabel->Text = L"Version:";
			// 
			// sCompileDateLabel
			// 
			this->sCompileDateLabel->Location = System::Drawing::Point(8, 32);
			this->sCompileDateLabel->Name = L"sCompileDateLabel";
			this->sCompileDateLabel->Size = System::Drawing::Size(88, 16);
			this->sCompileDateLabel->TabIndex = 5;
			this->sCompileDateLabel->Text = L"Compile Date:";
			// 
			// sCompileTimeLabel
			// 
			this->sCompileTimeLabel->Location = System::Drawing::Point(8, 48);
			this->sCompileTimeLabel->Name = L"sCompileTimeLabel";
			this->sCompileTimeLabel->Size = System::Drawing::Size(80, 16);
			this->sCompileTimeLabel->TabIndex = 8;
			this->sCompileTimeLabel->Text = L"Compile Time:";
			// 
			// sAuthorLabel
			// 
			this->sAuthorLabel->Location = System::Drawing::Point(8, 64);
			this->sAuthorLabel->Name = L"sAuthorLabel";
			this->sAuthorLabel->Size = System::Drawing::Size(80, 16);
			this->sAuthorLabel->TabIndex = 7;
			this->sAuthorLabel->Text = L"Author:";
			// 
			// sVersionText
			// 
			this->sVersionText->Location = System::Drawing::Point(104, 16);
			this->sVersionText->Name = L"sVersionText";
			this->sVersionText->Size = System::Drawing::Size(160, 16);
			this->sVersionText->TabIndex = 2;
			// 
			// presenterGroup
			// 
			this->presenterGroup->BackColor = System::Drawing::Color::Transparent;
			this->presenterGroup->Controls->Add(this->pVersionLabel);
			this->presenterGroup->Controls->Add(this->pCompileDateLabel);
			this->presenterGroup->Controls->Add(this->pCompileTimeLabel);
			this->presenterGroup->Controls->Add(this->pAuthorLabel);
			this->presenterGroup->Controls->Add(this->pVersionText);
			this->presenterGroup->Controls->Add(this->pCompileDateText);
			this->presenterGroup->Controls->Add(this->pCompileTimeText);
			this->presenterGroup->Controls->Add(this->pAuthorText);
			this->presenterGroup->Location = System::Drawing::Point(4, 81);
			this->presenterGroup->Name = L"presenterGroup";
			this->presenterGroup->Size = System::Drawing::Size(272, 144);
			this->presenterGroup->TabIndex = 5;
			this->presenterGroup->TabStop = false;
			this->presenterGroup->Text = L"BAPS Presenter";
			// 
			// pVersionLabel
			// 
			this->pVersionLabel->Location = System::Drawing::Point(8, 16);
			this->pVersionLabel->Name = L"pVersionLabel";
			this->pVersionLabel->Size = System::Drawing::Size(56, 16);
			this->pVersionLabel->TabIndex = 0;
			this->pVersionLabel->Text = L"Version:";
			// 
			// pCompileDateLabel
			// 
			this->pCompileDateLabel->Location = System::Drawing::Point(8, 32);
			this->pCompileDateLabel->Name = L"pCompileDateLabel";
			this->pCompileDateLabel->Size = System::Drawing::Size(88, 16);
			this->pCompileDateLabel->TabIndex = 0;
			this->pCompileDateLabel->Text = L"Compile Date:";
			// 
			// pCompileTimeLabel
			// 
			this->pCompileTimeLabel->Location = System::Drawing::Point(8, 48);
			this->pCompileTimeLabel->Name = L"pCompileTimeLabel";
			this->pCompileTimeLabel->Size = System::Drawing::Size(80, 16);
			this->pCompileTimeLabel->TabIndex = 0;
			this->pCompileTimeLabel->Text = L"Compile Time:";
			// 
			// pAuthorLabel
			// 
			this->pAuthorLabel->Location = System::Drawing::Point(8, 64);
			this->pAuthorLabel->Name = L"pAuthorLabel";
			this->pAuthorLabel->Size = System::Drawing::Size(80, 16);
			this->pAuthorLabel->TabIndex = 0;
			this->pAuthorLabel->Text = L"Author:";
			// 
			// pVersionText
			// 
			this->pVersionText->Location = System::Drawing::Point(104, 16);
			this->pVersionText->Name = L"pVersionText";
			this->pVersionText->Size = System::Drawing::Size(160, 16);
			this->pVersionText->TabIndex = 0;
			// 
			// pCompileDateText
			// 
			this->pCompileDateText->Location = System::Drawing::Point(104, 32);
			this->pCompileDateText->Name = L"pCompileDateText";
			this->pCompileDateText->Size = System::Drawing::Size(160, 16);
			this->pCompileDateText->TabIndex = 0;
			// 
			// pCompileTimeText
			// 
			this->pCompileTimeText->Location = System::Drawing::Point(104, 48);
			this->pCompileTimeText->Name = L"pCompileTimeText";
			this->pCompileTimeText->Size = System::Drawing::Size(160, 16);
			this->pCompileTimeText->TabIndex = 0;
			// 
			// pAuthorText
			// 
			this->pAuthorText->Location = System::Drawing::Point(104, 64);
			this->pAuthorText->Name = L"pAuthorText";
			this->pAuthorText->Size = System::Drawing::Size(160, 72);
			this->pAuthorText->TabIndex = 0;
			// 
			// sCompileDateText
			// 
			this->sCompileDateText->Location = System::Drawing::Point(104, 32);
			this->sCompileDateText->Name = L"sCompileDateText";
			this->sCompileDateText->Size = System::Drawing::Size(160, 16);
			this->sCompileDateText->TabIndex = 1;
			// 
			// sCompileTimeText
			// 
			this->sCompileTimeText->Location = System::Drawing::Point(104, 48);
			this->sCompileTimeText->Name = L"sCompileTimeText";
			this->sCompileTimeText->Size = System::Drawing::Size(160, 16);
			this->sCompileTimeText->TabIndex = 4;
			// 
			// sAuthorText
			// 
			this->sAuthorText->Location = System::Drawing::Point(104, 64);
			this->sAuthorText->Name = L"sAuthorText";
			this->sAuthorText->Size = System::Drawing::Size(160, 72);
			this->sAuthorText->TabIndex = 3;
			// 
			// mailTitle
			// 
			this->mailTitle->BackColor = System::Drawing::Color::Transparent;
			this->mailTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->mailTitle->Location = System::Drawing::Point(12, 9);
			this->mailTitle->Name = L"mailTitle";
			this->mailTitle->Size = System::Drawing::Size(256, 56);
			this->mailTitle->TabIndex = 3;
			this->mailTitle->Text = L"Broadcast And Presenting System";
			this->mailTitle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// serverGroup
			// 
			this->serverGroup->BackColor = System::Drawing::Color::Transparent;
			this->serverGroup->Controls->Add(this->sVersionLabel);
			this->serverGroup->Controls->Add(this->sCompileDateLabel);
			this->serverGroup->Controls->Add(this->sCompileTimeLabel);
			this->serverGroup->Controls->Add(this->sAuthorLabel);
			this->serverGroup->Controls->Add(this->sVersionText);
			this->serverGroup->Controls->Add(this->sCompileDateText);
			this->serverGroup->Controls->Add(this->sCompileTimeText);
			this->serverGroup->Controls->Add(this->sAuthorText);
			this->serverGroup->Location = System::Drawing::Point(4, 233);
			this->serverGroup->Name = L"serverGroup";
			this->serverGroup->Size = System::Drawing::Size(272, 144);
			this->serverGroup->TabIndex = 4;
			this->serverGroup->TabStop = false;
			this->serverGroup->Text = L"BAPS Server";
			// 
			// About
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(284, 384);
			this->Controls->Add(this->presenterGroup);
			this->Controls->Add(this->mailTitle);
			this->Controls->Add(this->serverGroup);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->KeyPreview = true;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"About";
			this->Text = L"About BAPS Presenter";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &About::About_KeyDown);
			this->presenterGroup->ResumeLayout(false);
			this->serverGroup->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

};
}
