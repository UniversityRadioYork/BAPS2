#include "stdafx.h"
#include "utility.h"
#include "Exceptions.h"
#include "ClientManager.h"
#include "GlobalAudioObject.h"
#include "LogManager.h"
#include "ConfigManager.h"
#include "BAPSController.h"
#include "UserManager.h"
#include "Exceptions.h"
#include "AsyncActionManager.h"

using namespace BAPSServerAssembly;

LPWSTR BAPSServerAssembly::stringToLPWSTR(System::String ^data)
{
	/** Simply copy the data one character at a time into a new wchar_t array and return it **/
	wchar_t *szBuf;
	LPWSTR thestring;
	szBuf = new wchar_t[data->Length + 1]; 
	array<wchar_t>^ gcszBuf = data->ToCharArray();
	for (int i = 0; i < data->Length; i++)
	{
		szBuf[i] = gcszBuf[i];
	}
	szBuf[data->Length] = '\0';		
	thestring = szBuf;
	return thestring;
}

System::String^ BAPSServerAssembly::LPCWSTRToString(LPCWSTR data)
{
	System::String^ str = "";
	int i = 0;
	for (i= 0 ; data[i] != 0; i++)
	{
		str = System::String::Concat(str, System::Convert::ToString(data[i]));
	}
	return str;
}

System::String^ BAPSServerAssembly::md5sum(System::String^ raw)
{
	System::Security::Cryptography::MD5^ md5serv = System::Security::Cryptography::MD5CryptoServiceProvider::Create();
	System::Text::StringBuilder^ stringbuff = gcnew System::Text::StringBuilder();
	array<System::Byte>^ buffer = System::Text::Encoding::ASCII->GetBytes(raw);
	array<System::Byte>^ hash = md5serv->ComputeHash(buffer);
	
	for (int i = 0 ; i < hash->Length ; i++)
	{
		stringbuff->Append(hash[i].ToString("x2"));
	}
	return stringbuff->ToString();
}


System::String^ BAPSServerAssembly::getRandomString()
{
	array<System::Byte>^ random = gcnew array<System::Byte>(50);

	System::Security::Cryptography::RNGCryptoServiceProvider^ rng = gcnew System::Security::Cryptography::RNGCryptoServiceProvider();
	rng->GetNonZeroBytes(random);
	return md5sum(System::Text::Encoding::ASCII->GetString(random));
}

void BAPSServerAssembly::UnhandledExceptionHandler( System::Object^ sender, System::UnhandledExceptionEventArgs^ args )
{
	System::Exception^ e = dynamic_cast<System::Exception^>(args->ExceptionObject);
	LogManager::emergency(System::String::Concat("Unhandled exception:\n", e->Message,"\nStack trace:\n",e->StackTrace));
}

void BAPSServerAssembly::Utility::start()
{
	System::Diagnostics::Process::GetCurrentProcess()->PriorityClass = System::Diagnostics::ProcessPriorityClass::High;
	System::AppDomain::CurrentDomain->UnhandledException += gcnew System::UnhandledExceptionEventHandler( BAPSServerAssembly::UnhandledExceptionHandler );
	try
	{
		ConfigManager::initConfigManager();
		LogManager::initLogManager();
		UserManager::initUserManager();
		AsyncActionManager::initAsyncActionManager();
		ClientManager::initClientManager();
		BAPSController::initBAPSController();
		AsyncActionManager::start();
	}
	catch (BAPSTerminateException^ bte)
	{
		LogManager::emergency(System::String::Concat("Initialization error:\n", bte->Message, "Stack Trace:\n",bte->StackTrace));
		stop();
		exit(1);
	}
	catch (System::Exception^ e)
	{
		LogManager::emergency(System::String::Concat("Received unexpected exception, terminating immediately:\n", e->Message, "Stack Trace:\n",e->StackTrace));
		stop();
		exit(2);
	}
}

void BAPSServerAssembly::Utility::stop()
{
	BAPSController::closeBAPSController();
	ClientManager::closeClientManager();
	AsyncActionManager::closeAsyncActionManager();
	UserManager::closeUserManager();
	LogManager::closeLogManager();
	ConfigManager::closeConfigManager();
}