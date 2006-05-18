// BAPSWatchdogService.cpp : main Windows Service project file.

#include "stdafx.h"
#include <string.h>
#include "BAPSWatchdogServiceWinService.h"

using namespace BAPSWatchdogService;
using namespace System::Text;
using namespace System::Security::Policy;
using namespace System::Reflection;

//To install/uninstall the service, type: "BAPSWatchdogService.exe -Install [-u]"
int _tmain(int argc, _TCHAR* argv[])
{
	if (argc >= 2)
	{
		if (argv[1][0] == _T('/'))
		{
			argv[1][0] = _T('-');
		}

		if (_tcsicmp(argv[1], _T("-Install")) == 0)
		{
			array<String^>^ myargs = System::Environment::GetCommandLineArgs();
			array<String^>^ args = gcnew array<String^>(myargs->Length - 1);

			// Set args[0] with the full path to the assembly,
			Assembly^ assem = Assembly::GetExecutingAssembly();
			args[0] = assem->Location;

			Array::Copy(myargs, 2, args, 1, args->Length - 1);
			AppDomain^ dom = AppDomain::CreateDomain(L"execDom");
			Type^ type = System::Object::typeid;
			String^ path = type->Assembly->Location;
			StringBuilder^ sb = gcnew StringBuilder(path->Substring(0, path->LastIndexOf(L"\\")));
			sb->Append(L"\\InstallUtil.exe");
			Evidence^ evidence = gcnew Evidence();
			dom->ExecuteAssembly(sb->ToString(), evidence, args);

			try
			{
				System::ServiceProcess::ServiceController^ thisservice;
				thisservice = (gcnew System::ServiceProcess::ServiceController());
#ifdef _DEBUG
				thisservice->ServiceName = "BAPS (DEBUG) Watchdog Service";
#else
				thisservice->ServiceName = "BAPS Watchdog Service";
#endif
				thisservice->Start();
			}
			catch (System::Exception^ )
			{
				/** Oh well couldn't start it **/
				Console::WriteLine("Failed to start service.\nBAPS Server Service might not be installed or is not runnable.\nPush enter to continue.");
				Console::ReadLine();
			}
		}
		else if (_tcsicmp(argv[1], _T("-Uninstall")) == 0)
		{
			//Install this Windows Service using InstallUtil.exe
			array<String^>^ myargs = System::Environment::GetCommandLineArgs();
			array<String^>^ args = gcnew array<String^>(myargs->Length);

			// Set args[0] with the full path to the assembly,
			System::Reflection::Assembly^ assem = System::Reflection::Assembly::GetExecutingAssembly();
			args[0] = "-u";
			args[1] = assem->Location;

			System::Array::Copy(myargs, 2, args, 2,myargs->Length - 2);
			System::AppDomain^ dom = System::AppDomain::CreateDomain(L"execDom");
			System::Type^ type = System::Object::typeid;
			System::String^ path = type->Assembly->Location;
			System::Text::StringBuilder^ sb = gcnew System::Text::StringBuilder(path->Substring(0, path->LastIndexOf(L"\\")));
			sb->Append(L"\\InstallUtil.exe");
			System::Security::Policy::Evidence^ evidence = gcnew System::Security::Policy::Evidence();
			dom->ExecuteAssembly(sb->ToString(), evidence, args);
		}
	}
	else
	{
		ServiceBase::Run(gcnew BAPSWatchdogServiceWinService());
	}
}
