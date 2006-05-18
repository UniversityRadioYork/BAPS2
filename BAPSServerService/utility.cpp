#include "stdafx.h"
#include "LogManager.h"
#include "utility.h"
#include "Exceptions.h"


LPWSTR stringToLPWSTR(System::String ^data)
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

System::String^ LPCWSTRToString(LPCWSTR data)
{
	System::String^ str = "";
	int i = 0;
	for (i= 0 ; data[i] != 0; i++)
	{
		str = System::String::Concat(str, System::Convert::ToString(data[i]));
	}
	return str;
}

System::String^ md5sum(System::String^ raw)
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
System::String^ getRandomString()
{
	array<System::Byte>^ random = gcnew array<System::Byte>(50);

	System::Security::Cryptography::RNGCryptoServiceProvider^ rng = gcnew System::Security::Cryptography::RNGCryptoServiceProvider();
	rng->GetNonZeroBytes(random);
	return md5sum(System::Text::Encoding::ASCII->GetString(random));
}

