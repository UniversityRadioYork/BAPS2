#pragma once
#include "ClientManager.h"
#include "LogManager.h"

ref class BAPSController
{
public:
	static void initBAPSController()
	{
		try
		{
			serialPort = gcnew System::IO::Ports::SerialPort("COM1", 9600, System::IO::Ports::Parity::None,8,System::IO::Ports::StopBits::One);
			serialPort->Open();
			serialPort->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(&BAPSController::handleData);
		}
		catch (System::IO::IOException^ e)
		{
			LogManager::write(System::String::Concat("Failed to start BAPS Controller:\n", e->Message, "Stack Trace:\n",e->StackTrace),LOG_ERROR, LOG_COMMS);
		}
	}
	static void closeBAPSController()
	{
		if (serialPort != nullptr && serialPort->IsOpen)
		{
			serialPort->Close();
			serialPort = nullptr;
		}
	}
	static void handleData(System::Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e)
	{
		int i;
		for (i = 0 ; serialPort!=nullptr && serialPort->IsOpen && i < serialPort->BytesToRead ; i++)
		{
			System::Byte data = serialPort->ReadByte();
			LogManager::write(System::String::Concat("Serial Data received: ", data.ToString()),LOG_INFO, LOG_COMMS);
		}
	}
private:
	static System::IO::Ports::SerialPort^ serialPort;
};