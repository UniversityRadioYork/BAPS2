#pragma once

#include "ClientManager.h"
#include "GlobalAudioObject.h"
#include "LogManager.h"
#include "ConfigManager.h"
#include "BAPSController.h"
#include "UserManager.h"
#include "Exceptions.h"
#include "AsyncActionManager.h"

using namespace System;
using namespace System::Collections;
using namespace System::ServiceProcess;
using namespace System::ComponentModel;


namespace BAPSServerService
{
	/// <summary> 
	/// Summary for BAPSServerServiceWinService
	/// </summary>
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	public ref class BAPSServerServiceWinService : public System::ServiceProcess::ServiceBase 
	{
	public:
		BAPSServerServiceWinService()
		{
			InitializeComponent();   
#ifdef _DEBUG
			this->ServiceName = "BAPS (DEBUG) Server Service";
#else
			this->ServiceName = "BAPS Server Service";
#endif
		}
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~BAPSServerServiceWinService()
		{
			if (components)
			{
				delete components;
			}
		}
		static void UnhandledExceptionHandler( Object^ /*sender*/, UnhandledExceptionEventArgs^ args )
		{
			Exception^ e = dynamic_cast<Exception^>(args->ExceptionObject);
			LogManager::emergency(System::String::Concat("Unhandled exception:\n", e->Message,"\nStack trace:\n",e->StackTrace));
		}
	protected:


		/// <summary>
		/// Set things in motion so your service can do its work.
		/// </summary>
		virtual void OnStart(array<String^>^ args) override
		{
			try
			{
				ConfigManager::initConfigManager();
				LogManager::initLogManager();
				UserManager::initUserManager();
				AsyncActionManager::initAsyncActionManager();
				ClientManager::initClientManager();
				BAPSController::initBAPSController();
			}
			catch (BAPSTerminateException^ bte)
			{
				LogManager::emergency(System::String::Concat("Initialization error:\n", bte->Message, "Stack Trace:\n",bte->StackTrace));
				OnStop();
				exit(1);
			}
			catch (System::Exception^ e)
			{
				LogManager::emergency(System::String::Concat("Received unexpected exception, terminating immediately:\n", e->Message, "Stack Trace:\n",e->StackTrace));
				OnStop();
				exit(2);
			}

		}
		
		/// <summary>
		/// Stop this service.
		/// </summary>
		virtual void OnStop() override
		{     
			BAPSController::closeBAPSController();
			ClientManager::closeClientManager();
			AsyncActionManager::closeAsyncActionManager();
			UserManager::closeUserManager();
			LogManager::closeLogManager();
			ConfigManager::closeConfigManager();
			GC::Collect();
		}

		virtual void OnShutdown() override
		{
			OnStop();
		}
    		
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
			// 
			// BAPSServerServiceWinService
			// 
			this->CanPauseAndContinue = true;
			this->CanShutdown = true;
			this->ServiceName = L"BAPS Server Service";

		}		
	};
#pragma endregion
}