// Tinker.cpp : main project file.

#include "stdafx.h"
#include "fred.h"
#include "BAPSParallelController.h"

using namespace System;


void handleData(System::Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e)
{
	int i;
	for (i = 0 ; i < fred::serialPort->BytesToRead ; i++)
	{
		System::Byte data = fred::serialPort->ReadByte();
		Console::WriteLine(System::String::Concat("Serial Data received: ", data.ToString()));
	}
	Console::WriteLine("");
}

int main(array<System::String ^> ^args)
{
	
	try
	{
		fred::serialPort = gcnew System::IO::Ports::SerialPort("COM1", 2400, System::IO::Ports::Parity::None,8,System::IO::Ports::StopBits::One);
		fred::serialPort->Open();
		fred::serialPort->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(&handleData);
	}
	catch (System::IO::IOException^ e)
	{
	}
	System::Threading::Thread::Sleep(60000);
	fred::serialPort->Close();
    

	return 0;
}


