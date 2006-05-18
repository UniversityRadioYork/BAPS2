#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::ServiceProcess;
using namespace System::ComponentModel;
using namespace System::Diagnostics;

namespace BAPSWatchdogService {

	/// <summary>
	/// Summary for BAPSWatchdogServiceWinService
	/// </summary>
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	public ref class BAPSWatchdogServiceWinService : public System::ServiceProcess::ServiceBase
	{
	public:
		BAPSWatchdogServiceWinService()
		{
			timeout = 0;
			InitializeComponent();
#ifdef _DEBUG
			this->ServiceName = "BAPS (DEBUG) Watchdog Service";
			this->bapsServerService->ServiceName = L"BAPS (DEBUG) Server Service";
#else
			this->ServiceName = "BAPS Watchdog Service";
			this->bapsServerService->ServiceName = L"BAPS Server Service";
#endif
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~BAPSWatchdogServiceWinService()
		{
			if (components)
			{
				delete components;
			}
		}

		/// <summary>
		/// Set things in motion so your service can do its work.
		/// </summary>
		virtual void OnStart(array<String^>^ args) override
		{
			// TODO: Add code here to start your service.
			timer2->Start();
		}

		/// <summary>
		/// Stop this service.
		/// </summary>
		virtual void OnStop() override
		{
			// TODO: Add code here to perform any tear-down necessary to stop your service.
			timer2->Stop();
		}
	private: System::ServiceProcess::ServiceController^  bapsServerService;
	private: System::Timers::Timer^  timer2;


	private: System::ComponentModel::IContainer^  components;
	protected: 

	private:
		int timeout;
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->bapsServerService = (gcnew System::ServiceProcess::ServiceController());
			this->timer2 = (gcnew System::Timers::Timer());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->timer2))->BeginInit();
			// 
			// bapsServerService
			// 
			this->bapsServerService->ServiceName = L"BAPS Server Service";
			// 
			// timer2
			// 
			this->timer2->Enabled = true;
			this->timer2->Interval = 300;
			this->timer2->Elapsed += gcnew System::Timers::ElapsedEventHandler(this, &BAPSWatchdogServiceWinService::timer2_Elapsed);
			// 
			// BAPSWatchdogServiceWinService
			// 
			this->CanPauseAndContinue = true;
			this->ServiceName = L"BAPS Watchdog Service";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->timer2))->EndInit();

		}
#pragma endregion

	private: System::Void timer2_Elapsed(System::Object^  sender, System::Timers::ElapsedEventArgs^  e)
			{
				bapsServerService->Refresh();
				try
				{
					if (bapsServerService->Status == System::ServiceProcess::ServiceControllerStatus::Paused)
					{
						timeout = 0;
						bapsServerService->Continue();
					}
					else if (bapsServerService->Status == System::ServiceProcess::ServiceControllerStatus::Stopped)
					{
						timeout = 0;
						bapsServerService->Start();
					}
					else if (bapsServerService->Status != System::ServiceProcess::ServiceControllerStatus::Running)
					{
						timeout++;
						if (timeout > 360) /**roughly 2 mins **/
						{
							throw gcnew System::Exception("2 minute timeout expired. Service is not in a runnable state");
						}
					}
				}
				catch (System::Exception^ e)
				{
					System::Diagnostics::EventLog^ emergLog = gcnew System::Diagnostics::EventLog("Application", ".", "BAPS Watchdog Service");
					emergLog->WriteEntry(System::String::Concat("Failed to start BAPS Server Service. Current status: ", bapsServerService->Status, "\nException: ",e->Message), EventLogEntryType::Error, 0);
					emergLog->Close();
				}
			}
	};
}
