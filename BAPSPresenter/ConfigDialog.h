#pragma once

#include "Messages.h"
#include "decodeStructs.h"
#include "ConfigOptionInfo.h"
#include "ConfigOptions.h"
#include "DataGridComboBoxColumn.h"
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
	/// Summary for ConfigDialog
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class ConfigDialog : public System::Windows::Forms::Form
	{
	public:
		ConfigDialog(BAPSPresenterMain^ _bapsPresenterMain, System::Collections::Queue^ _msgQueue)
			: bapsPresenterMain(_bapsPresenterMain),
			  msgQueue(_msgQueue),
			  numberOfOptions(0),
			  optionCountSet(false)
		{
			InitializeComponent();
			/** optionid to optioninfo lookup **/
			options = gcnew System::Collections::Hashtable();
			/** Used to store datagrid controls (for indexed options) options
				are columns in the datagrid that share the same index control
			**/
			indexControls = gcnew System::Collections::Hashtable();
			/** Request all the options to be sent ( doing this at construction guarantees
				that the form handle is ready and valid for the data sent from the server
				to be sent to
			**/
			saveButton->Enabled = false;
			/** A mutex to stop the form closing while it is being updated **/
			closeMutex = gcnew System::Threading::Mutex();
		}
		/** When the form has received all the options it was told it will receive,
			it can start to generate the UI, this is used by the main client so that
			it can 'Invoke' the UI generation as it is supposed to
		**/
		bool isReadyToShow()
		{
			return (optionCountSet && (numberOfOptions == 0));
		}
		/** Standard calling method for these as they update only data not the UI **/
		void setNumberOfOptions(int _numberOfOptions);
		void addOption(ConfigOptionInfo^ option);
		/** Must be 'Invoked' updates the UI **/
		void updateUI();
		/** These must be 'Invoked' too as they update combo boxes **/
		void addChoice(System::Object^ optionid, System::Object^ choiceid, System::String^ description);
		void setChoiceCount(System::Object^ optionid, System::Object^ count);
		void receiveSettingsIfReady();
		void enableSaveButtonIfReady();
		/** These update text boxes or combo boxes as appropriate and must be 'Invoked' **/
		void setValue(System::Object^ id, System::String^ str);
		void setValue(System::Object^ id, System::Object^ value);
		void setValue(System::Object^ id,System::Object^ index, System::String^ str);
		void setValue(System::Object^ id,System::Object^ index, System::Object^ value);
		void setResult(System::Object^ optionid, System::Object^ result);
		/** A mutex to ensure the config dialog cannot close while an update is occuring **/
		System::Threading::Mutex^ closeMutex;
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ConfigDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		/** Storage for the number of options to be received **/
		int numberOfOptions;
		bool optionCountSet;
		/** A handle to the main window **/
		BAPSPresenterMain^ bapsPresenterMain;


		System::Collections::Hashtable^ options;
		System::Collections::Hashtable^ indexControls;

			 System::Collections::Queue^ msgQueue;

		System::Void saveButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void restartButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void ConfigDialog_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
		System::Void cancelButton_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void ConfigDialog_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Windows::Forms::StatusStrip^  status;
	protected: 
	private: System::Windows::Forms::ToolStripStatusLabel^  statusLabel;
	private: System::Windows::Forms::Button^  cancelButton;
	private: System::Windows::Forms::Button^  saveButton;
	private: System::Windows::Forms::Button^  restartButton;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ConfigDialog::typeid));
			this->status = (gcnew System::Windows::Forms::StatusStrip());
			this->statusLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->cancelButton = (gcnew System::Windows::Forms::Button());
			this->saveButton = (gcnew System::Windows::Forms::Button());
			this->restartButton = (gcnew System::Windows::Forms::Button());
			this->status->SuspendLayout();
			this->SuspendLayout();
			// 
			// status
			// 
			this->status->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->statusLabel});
			this->status->Location = System::Drawing::Point(0, 354);
			this->status->Name = L"status";
			this->status->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			this->status->Size = System::Drawing::Size(649, 22);
			this->status->TabIndex = 905;
			this->status->Text = L"statusStrip1";
			// 
			// statusLabel
			// 
			this->statusLabel->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->statusLabel->Name = L"statusLabel";
			this->statusLabel->Size = System::Drawing::Size(634, 17);
			this->statusLabel->Spring = true;
			this->statusLabel->Text = L"status";
			this->statusLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// cancelButton
			// 
			this->cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->cancelButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cancelButton->Location = System::Drawing::Point(336, 320);
			this->cancelButton->Name = L"cancelButton";
			this->cancelButton->Size = System::Drawing::Size(88, 24);
			this->cancelButton->TabIndex = 904;
			this->cancelButton->Text = L"Cancel";
			this->cancelButton->Click += gcnew System::EventHandler(this, &ConfigDialog::cancelButton_Click);
			// 
			// saveButton
			// 
			this->saveButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->saveButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->saveButton->Location = System::Drawing::Point(232, 320);
			this->saveButton->Name = L"saveButton";
			this->saveButton->Size = System::Drawing::Size(88, 24);
			this->saveButton->TabIndex = 903;
			this->saveButton->Text = L"Save Settings";
			this->saveButton->Click += gcnew System::EventHandler(this, &ConfigDialog::saveButton_Click);
			// 
			// restartButton
			// 
			this->restartButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->restartButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->restartButton->Location = System::Drawing::Point(150, 320);
			this->restartButton->Name = L"restartButton";
			this->restartButton->Size = System::Drawing::Size(88, 24);
			this->restartButton->TabIndex = 903;
			this->restartButton->Text = L"Restart Server";
			this->restartButton->Click += gcnew System::EventHandler(this, &ConfigDialog::restartButton_Click);
			// 
			// ConfigDialog
			// 
			this->AcceptButton = this->saveButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->cancelButton;
			this->ClientSize = System::Drawing::Size(649, 376);
			this->ControlBox = false;
			this->Controls->Add(this->status);
			this->Controls->Add(this->cancelButton);
			this->Controls->Add(this->saveButton);
			this->Controls->Add(this->restartButton);
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->KeyPreview = true;
			this->Name = L"ConfigDialog";
			this->Text = L"Configuration Settings";
			this->Load += gcnew System::EventHandler(this, &ConfigDialog::ConfigDialog_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ConfigDialog::ConfigDialog_KeyDown);
			this->status->ResumeLayout(false);
			this->status->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

};
}
