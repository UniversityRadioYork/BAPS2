#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Configuration::Install;


namespace BAPSServerService
{
	[RunInstaller(true)]	

	/// <summary> 
	/// Summary for ProjectInstaller
	/// </summary>
	public ref class ProjectInstaller : public System::Configuration::Install::Installer
	{
	public: 
		ProjectInstaller(void)
		{
			InitializeComponent();
#ifdef _DEBUG
			this->serviceInstaller1->ServiceName = "BAPS (DEBUG) Server Service";
			this->serviceInstaller1->DisplayName = "BAPS (DEBUG) Server Service";
#else
			this->serviceInstaller1->ServiceName = "BAPS Server Service";
			this->serviceInstaller1->DisplayName = "BAPS Server Service";
#endif
		}
	private: System::ServiceProcess::ServiceProcessInstaller^  serviceProcessInstaller1;
	public: 
	private: System::ServiceProcess::ServiceInstaller^  serviceInstaller1;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;
		
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>		
		void InitializeComponent(void)
		{
			this->serviceProcessInstaller1 = (gcnew System::ServiceProcess::ServiceProcessInstaller());
			this->serviceInstaller1 = (gcnew System::ServiceProcess::ServiceInstaller());
			// 
			// serviceProcessInstaller1
			// 
			this->serviceProcessInstaller1->Password = nullptr;
			this->serviceProcessInstaller1->Username = nullptr;
			// 
			// serviceInstaller1
			// 
			this->serviceInstaller1->Description = L"Broadcasting And Presenting Suite - Server";
			this->serviceInstaller1->DisplayName = L"BAPS Server Service";
			this->serviceInstaller1->ServiceName = L"BAPS Server Service";
			this->serviceInstaller1->StartType = System::ServiceProcess::ServiceStartMode::Automatic;
			// 
			// ProjectInstaller
			// 
			this->Installers->AddRange(gcnew cli::array< System::Configuration::Install::Installer^  >(2) {this->serviceProcessInstaller1, 
				this->serviceInstaller1});

		}
	};
}