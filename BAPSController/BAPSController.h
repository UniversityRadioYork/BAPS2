// BAPSController.h

#pragma once
#include "USBMicro.h"
#include <windows.h>

using namespace System;


namespace BAPSControllerAssembly
{
	public delegate void SignalCallback(System::String^, int);

	public ref class BAPSController
	{

	public:
		BAPSController();
		~BAPSController();
		bool run(SignalCallback^ callback);
		void stop()
		{
			quit = true;
			if (pollThread != nullptr)
			{
				pollThread->Abort();
				pollThread->Join();
			}
		}
		array<System::String^>^ getSerialNumbers();
	private:
		void runHelper();
		HINSTANCE hDll;

		USBm_FindDevices_type       USBm_FindDevices;
		USBm_NumberOfDevices_type   USBm_NumberOfDevices;
		USBm_DeviceValid_type       USBm_DeviceValid;
		USBm_DeviceVID_type         USBm_DeviceVID;
		USBm_DevicePID_type         USBm_DevicePID;
		USBm_DeviceDID_type         USBm_DeviceDID;
		USBm_DeviceMfr_type         USBm_DeviceMfr;
		USBm_DeviceProd_type        USBm_DeviceProd;
		USBm_DeviceSer_type         USBm_DeviceSer;
		USBm_InitPorts_type         USBm_InitPorts;
		USBm_CloseDevice_type       USBm_CloseDevice;
		USBm_WriteA_type            USBm_WriteA;
		USBm_WriteB_type            USBm_WriteB;
		USBm_WriteABit_type         USBm_WriteABit;
		USBm_WriteBBit_type         USBm_WriteBBit;
		USBm_ReadA_type             USBm_ReadA;
		USBm_ReadB_type             USBm_ReadB;
		USBm_SetBit_type            USBm_SetBit;
		USBm_ResetBit_type          USBm_ResetBit;
		USBm_DirectionA_type        USBm_DirectionA;
		USBm_DirectionB_type        USBm_DirectionB;
		USBm_StrobeWrite_type       USBm_StrobeWrite;
		USBm_StrobeRead_type        USBm_StrobeRead;
		USBm_StrobeWrite2_type      USBm_StrobeWrite2;
		USBm_StrobeRead2_type       USBm_StrobeRead2;
		USBm_StrobeWrites_type      USBm_StrobeWrites;
		USBm_StrobeReads_type       USBm_StrobeReads;
		USBm_InitLCD_type           USBm_InitLCD;
		USBm_LCDCmd_type            USBm_LCDCmd;
		USBm_LCDData_type           USBm_LCDData;
		USBm_InitSPI_type           USBm_InitSPI;
		USBm_SPIMaster_type         USBm_SPIMaster;
		USBm_SPISlaveWrite_type     USBm_SPISlaveWrite;
		USBm_SPISlaveRead_type      USBm_SPISlaveRead;
		USBm_Stepper_type           USBm_Stepper;
		USBm_Reset1Wire_type        USBm_Reset1Wire;
		USBm_Write1Wire_type        USBm_Write1Wire;
		USBm_Read1Wire_type         USBm_Read1Wire;
		USBm_RecentError_type       USBm_RecentError;
		USBm_ClearRecentError_type  USBm_ClearRecentError;
		USBm_DebugString_type       USBm_DebugString;
		USBm_Copyright_type         USBm_Copyright;
		USBm_About_type             USBm_About;
		USBm_Version_type           USBm_Version;

		int deviceCount;
		array<System::String^>^ serialNumbers;
		array<unsigned char>^ lastByteA;
		array<unsigned char>^ lastByteB;
		bool quit;
		System::Threading::Thread^ pollThread;
		SignalCallback^ callback;
	};
}
