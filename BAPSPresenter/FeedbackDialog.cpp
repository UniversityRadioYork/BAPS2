#include "StdAfx.h"
#include "FeedbackDialog.h"

using namespace BAPSPresenter;

System::Void FeedbackDialog::sendButton_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	if (feedbackText->Text->Length == 0)
	{
		System::Windows::Forms::MessageBox::Show("Please enter a message.", "Notice:", System::Windows::Forms::MessageBoxButtons::OK);
	}
	else
	{
		sendButton->Enabled = false;
		cancelButton->Enabled = false;
		Command cmd = BAPSNET_SYSTEM | BAPSNET_FEEDBACK;
		msgQueue->Enqueue(gcnew ActionMessageString(cmd, feedbackText->Text));
	}
}
System::Void FeedbackDialog::cancelButton_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	this->Close();
}