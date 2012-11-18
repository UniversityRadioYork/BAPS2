// Tinker.cpp : main project file.

#include "stdafx.h"

using namespace System;
using namespace BAPSControllerAssembly;

void notify(System::String^ s, int number)
{
	Console::WriteLine("Down: "+s+" "+number.ToString());
}

int main(array<System::String ^> ^args)
{
	
	BAPSControllerAssembly::BAPSController^ bc = gcnew BAPSControllerAssembly::BAPSController();
	array<System::String^>^ serialNumbers = bc->getSerialNumbers();

	bc->run(gcnew BAPSControllerAssembly::SignalCallback(notify));
	for (int i = 0 ; i < 100 ; i++)
	{
		System::Threading::Thread::Sleep(3000);
	}
	return 0;
}


