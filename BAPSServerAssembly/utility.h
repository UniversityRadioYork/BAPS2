#pragma once

namespace BAPSServerAssembly
{
	/** Convert .net strings to LPWSTR (wchar_t array) slow -- use as last resort **/
	LPWSTR stringToLPWSTR(System::String ^data);
	/** Convert LPWSTR to .net strings -- also slow **/
	System::String^ LPCWSTRToString(LPCWSTR data);

	System::String^ md5sum(System::String^ raw);
	System::String^ getRandomString();
	void UnhandledExceptionHandler( System::Object^ sender, System::UnhandledExceptionEventArgs^ args );

	public ref class Utility
	{
	public:
		static void start();
		static void stop();
	};
};