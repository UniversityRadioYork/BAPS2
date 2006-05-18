#pragma once

/** Convert .net strings to LPWSTR (wchar_t array) slow -- use as last resort **/
LPWSTR stringToLPWSTR(System::String ^data);
/** Convert LPWSTR to .net strings -- also slow **/
System::String^ LPCWSTRToString(LPCWSTR data);

System::String^ md5sum(System::String^ raw);
System::String^ getRandomString();