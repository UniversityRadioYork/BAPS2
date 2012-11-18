#include "stdafx.h"
#include "Globals.h"
#include "stdlib.h"

System::String^ md5sum(System::String^ raw)
{
	/** Generate an md5 sum of the raw argument **/
	System::Security::Cryptography::MD5^ md5serv = System::Security::Cryptography::MD5CryptoServiceProvider::Create();
	System::Text::StringBuilder^ stringbuff = gcnew System::Text::StringBuilder();
	array<System::Byte>^ buffer = System::Text::Encoding::ASCII->GetBytes(raw);
	array<System::Byte>^ hash = md5serv->ComputeHash(buffer);
	
	for(int i = 0 ; i < hash->Length ; i++)
	{
		stringbuff->Append(hash[i].ToString("x2"));
	}
	return stringbuff->ToString();
}

System::String ^TimeToString(int hours, int minutes, int seconds, int centiseconds)
{
	/** WORK NEEDED: fix me **/
	System::String ^htemp,^mtemp,^stemp;
	htemp = hours.ToString();
	
	if (minutes < 10)
	{
		mtemp = System::String::Concat("0", minutes.ToString());
	}
	else mtemp = minutes.ToString();

	if (seconds < 10)
	{
		stemp = System::String::Concat("0", seconds.ToString());
	}
	else stemp = seconds.ToString();

	return System::String::Concat(htemp,":", mtemp, ":", stemp);
}

System::String ^MillisecondsToTimeString(int msecs)
{
	/** WORK NEEDED: lots **/
	div_t temp;

	int secs = msecs / 1000;

	temp = div(secs, 3600);
	int hours = temp.quot;

	temp = div(secs, 60);
	int mins = temp.quot - (hours * 60);

	secs = secs - ((mins * 60) + (hours * 3600));

	return TimeToString(hours,mins,secs, msecs % 1000 / 10);

}