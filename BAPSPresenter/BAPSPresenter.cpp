// BAPSPresenter.cpp : main project file.

#include "stdafx.h"
#include "BAPSPresenterMain.h"
using namespace BAPSPresenter;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	/** The client class creates threads and needs to have its destructor called
		on exit to clean up, this is why the odd arrangement below is required
	**/
	BAPSPresenterMain^ main;

	// Create the main window and run it
	Application::Run(main = gcnew BAPSPresenterMain());

	bool crashed = main->hasCrashed();
	delete main;
	System::Windows::Forms::Application::Exit();
	if (crashed)
	{
		System::Diagnostics::Process::Start(System::Windows::Forms::Application::ExecutablePath);
	}

	return 0;
}
