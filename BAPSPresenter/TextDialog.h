#pragma once

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
	/// Summary for TextDialog
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class TextDialog : public System::Windows::Forms::Form
	{
	public:
		TextDialog(BAPSPresenterMain^ _bapsPresenterMain, System::String^ text)
			: bapsPresenterMain(_bapsPresenterMain)
		{
			InitializeComponent();
			this->Text = "News Stories / Long Links";
			textText->Text = text;
		}
		void toggleMaximize()
		{
			if (this->WindowState == System::Windows::Forms::FormWindowState::Normal)
			{
				System::Drawing::Rectangle bounds = System::Windows::Forms::Screen::GetWorkingArea(this);
				bounds.X =0;
				bounds.Y = 0;
				this->MaximizedBounds = bounds;
				this->MaximumSize = bounds.Size;
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
				this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			}
			else
			{
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
				this->WindowState = System::Windows::Forms::FormWindowState::Normal;
			}
		}
		void updateText(System::String^ text)
		{
			textText->Text = text;
		}
		void scroll(System::Object^ _updown);
		void textSize(System::Object^ _updown);


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~TextDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		/** A handle to the main window **/
		BAPSPresenterMain^ bapsPresenterMain;
		System::Windows::Forms::TextBox^  textText;
		System::Void TextDialog_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(TextDialog::typeid));
			this->textText = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// textText
			// 
			this->textText->BackColor = System::Drawing::Color::SeaShell;
			this->textText->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textText->Location = System::Drawing::Point(0, 0);
			this->textText->Multiline = true;
			this->textText->Name = L"textText";
			this->textText->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textText->Size = System::Drawing::Size(759, 542);
			this->textText->TabIndex = 2;
			// 
			// TextDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(759, 542);
			this->ControlBox = false;
			this->Controls->Add(this->textText);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->KeyPreview = true;
			this->Name = L"TextDialog";
			this->Text = L"Text Display";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &TextDialog::TextDialog_KeyDown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	};
}
