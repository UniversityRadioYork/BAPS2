#pragma once

#undef MessageBox
#include "Messages.h"
#include "BAPSButton.h"
#include "BAPSLabel.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace BAPSPresenter {

	/// <summary>
	/// Summary for FeedbackDialog
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class FeedbackDialog : public System::Windows::Forms::Form
	{
	public:
		FeedbackDialog(System::Collections::Queue^ _msgQueue)
			: msgQueue(_msgQueue)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		void receiveResult(System::Object^ _resultCode)
		{
			int resultCode = safe_cast<int>(_resultCode);
			if (resultCode == 0)
			{
				System::Windows::Forms::MessageBox::Show("Feedback sent successfully", "Notice:", System::Windows::Forms::MessageBoxButtons::OK);
			}
			else
			{
				System::Windows::Forms::MessageBox::Show("Failed to send feedback:\nPlease e-mail support with your feeback.", "Notice:", System::Windows::Forms::MessageBoxButtons::OK);
			}
			this->Close();
		} 
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FeedbackDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: BAPSPresenter::BAPSLabel^  bapsLabel1;
	private: BAPSPresenter::BAPSButton^  sendButton;
	private: BAPSPresenter::BAPSButton^  cancelButton;
	protected: 
	private:
		System::Collections::Queue^ msgQueue;
		System::Void sendButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void cancelButton_Click(System::Object ^  sender, System::EventArgs ^  e);



	private: System::Windows::Forms::TextBox^  feedbackText;


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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FeedbackDialog::typeid));
			this->feedbackText = (gcnew System::Windows::Forms::TextBox());
			this->bapsLabel1 = (gcnew BAPSPresenter::BAPSLabel());
			this->sendButton = (gcnew BAPSPresenter::BAPSButton());
			this->cancelButton = (gcnew BAPSPresenter::BAPSButton());
			this->SuspendLayout();
			// 
			// feedbackText
			// 
			this->feedbackText->BackColor = System::Drawing::Color::SeaShell;
			this->feedbackText->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->feedbackText->Location = System::Drawing::Point(12, 49);
			this->feedbackText->Multiline = true;
			this->feedbackText->Name = L"feedbackText";
			this->feedbackText->Size = System::Drawing::Size(512, 184);
			this->feedbackText->TabIndex = 3;
			// 
			// bapsLabel1
			// 
			this->bapsLabel1->BackColor = System::Drawing::Color::Transparent;
			this->bapsLabel1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->bapsLabel1->InfoText = L"";
			this->bapsLabel1->Location = System::Drawing::Point(11, 11);
			this->bapsLabel1->Name = L"bapsLabel1";
			this->bapsLabel1->Size = System::Drawing::Size(328, 28);
			this->bapsLabel1->TabIndex = 7;
			this->bapsLabel1->TabStop = false;
			this->bapsLabel1->Text = L"Feedback/Opinions/Problems:";
			// 
			// sendButton
			// 
			this->sendButton->BackColor = System::Drawing::Color::Transparent;
			this->sendButton->DialogResult = System::Windows::Forms::DialogResult::None;
			this->sendButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->sendButton->HighlightColor = System::Drawing::Color::Red;
			this->sendButton->Highlighted = false;
			this->sendButton->Location = System::Drawing::Point(320, 241);
			this->sendButton->Name = L"sendButton";
			this->sendButton->Size = System::Drawing::Size(102, 26);
			this->sendButton->TabIndex = 8;
			this->sendButton->Text = L"Send";
			this->sendButton->Click += gcnew System::EventHandler(this, &FeedbackDialog::sendButton_Click);
			// 
			// cancelButton
			// 
			this->cancelButton->BackColor = System::Drawing::Color::Transparent;
			this->cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->cancelButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->cancelButton->HighlightColor = System::Drawing::Color::Red;
			this->cancelButton->Highlighted = false;
			this->cancelButton->Location = System::Drawing::Point(428, 241);
			this->cancelButton->Name = L"cancelButton";
			this->cancelButton->Size = System::Drawing::Size(102, 26);
			this->cancelButton->TabIndex = 8;
			this->cancelButton->Text = L"Cancel";
			this->cancelButton->Click += gcnew System::EventHandler(this, &FeedbackDialog::cancelButton_Click);
			// 
			// FeedbackDialog
			// 
			this->AcceptButton = this->sendButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->CancelButton = this->cancelButton;
			this->ClientSize = System::Drawing::Size(542, 279);
			this->ControlBox = false;
			this->Controls->Add(this->cancelButton);
			this->Controls->Add(this->sendButton);
			this->Controls->Add(this->bapsLabel1);
			this->Controls->Add(this->feedbackText);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"FeedbackDialog";
			this->Text = L"Feedback";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}
