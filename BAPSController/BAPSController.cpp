// This is the main DLL file.

#include "stdafx.h"

#include "BAPSController.h"

using namespace BAPSControllerAssembly;

BAPSController::~BAPSController()
{
	if (hDll != 0)
	{
	    FreeLibrary(hDll);
	}
}
BAPSController::BAPSController()
{
    hDll = LoadLibrary(L"USBm.dll");

	if (hDll == 0)
	{
		this->hasUSBDevices = false;
		return;
	}
	else {
		this->hasUSBDevices = true;
	}

	USBm_FindDevices =      (USBm_FindDevices_type)GetProcAddress(hDll, "USBm_FindDevices");
	USBm_NumberOfDevices =  (USBm_NumberOfDevices_type)GetProcAddress(hDll, "USBm_NumberOfDevices");
	USBm_DeviceValid =      (USBm_DeviceValid_type)GetProcAddress(hDll, "USBm_DeviceValid");
	USBm_DeviceVID =        (USBm_DeviceVID_type)GetProcAddress(hDll, "USBm_DeviceVID");
	USBm_DevicePID =        (USBm_DevicePID_type)GetProcAddress(hDll, "USBm_DevicePID");
	USBm_DeviceDID =        (USBm_DeviceDID_type)GetProcAddress(hDll, "USBm_DeviceDID");
	USBm_DeviceMfr =        (USBm_DeviceMfr_type)GetProcAddress(hDll, "USBm_DeviceMfr");
	USBm_DeviceProd =       (USBm_DeviceProd_type)GetProcAddress(hDll, "USBm_DeviceProd");
	USBm_DeviceSer =        (USBm_DeviceSer_type)GetProcAddress(hDll, "USBm_DeviceSer");
	USBm_InitPorts =        (USBm_InitPorts_type)GetProcAddress(hDll, "USBm_InitPorts");
	USBm_CloseDevice =      (USBm_CloseDevice_type)GetProcAddress(hDll, "USBm_CloseDevice");
	USBm_WriteA =           (USBm_WriteA_type)GetProcAddress(hDll, "USBm_WriteA");
	USBm_WriteB =           (USBm_WriteB_type)GetProcAddress(hDll, "USBm_WriteB");
	USBm_WriteABit =        (USBm_WriteABit_type)GetProcAddress(hDll, "USBm_WriteABit");
	USBm_WriteBBit =        (USBm_WriteBBit_type)GetProcAddress(hDll, "USBm_WriteBBit");
	USBm_ReadA =            (USBm_ReadA_type)GetProcAddress(hDll, "USBm_ReadA");
	USBm_ReadB =            (USBm_ReadB_type)GetProcAddress(hDll, "USBm_ReadB");
	USBm_SetBit =           (USBm_SetBit_type)GetProcAddress(hDll, "USBm_SetBit");
	USBm_ResetBit =         (USBm_ResetBit_type)GetProcAddress(hDll, "USBm_ResetBit");
	USBm_DirectionA =       (USBm_DirectionA_type)GetProcAddress(hDll, "USBm_DirectionA");
	USBm_DirectionB =       (USBm_DirectionB_type)GetProcAddress(hDll, "USBm_DirectionB");
	USBm_StrobeWrite =      (USBm_StrobeWrite_type)GetProcAddress(hDll, "USBm_StrobeWrite");
	USBm_StrobeRead =       (USBm_StrobeRead_type)GetProcAddress(hDll, "USBm_StrobeRead");
	USBm_StrobeWrite2 =     (USBm_StrobeWrite2_type)GetProcAddress(hDll, "USBm_StrobeWrite2");
	USBm_StrobeRead2 =      (USBm_StrobeRead2_type)GetProcAddress(hDll, "USBm_StrobeRead2");
	USBm_StrobeWrites =     (USBm_StrobeWrites_type)GetProcAddress(hDll, "USBm_StrobeWrites");
	USBm_StrobeReads =      (USBm_StrobeReads_type)GetProcAddress(hDll, "USBm_StrobeReads");
	USBm_InitLCD =          (USBm_InitLCD_type)GetProcAddress(hDll, "USBm_InitLCD");
	USBm_LCDCmd =           (USBm_LCDCmd_type)GetProcAddress(hDll, "USBm_LCDCmd");
	USBm_LCDData =          (USBm_LCDData_type)GetProcAddress(hDll, "USBm_LCDData");
	USBm_InitSPI =          (USBm_InitSPI_type)GetProcAddress(hDll, "USBm_InitSPI");
	USBm_SPIMaster =        (USBm_SPIMaster_type)GetProcAddress(hDll, "USBm_SPIMaster");
	USBm_SPISlaveWrite =    (USBm_SPISlaveWrite_type)GetProcAddress(hDll, "USBm_SPISlaveWrite");
	USBm_SPISlaveRead =     (USBm_SPISlaveRead_type)GetProcAddress(hDll, "USBm_SPISlaveRead");
	USBm_Stepper =          (USBm_Stepper_type)GetProcAddress(hDll, "USBm_Stepper");
	USBm_Reset1Wire =       (USBm_Reset1Wire_type)GetProcAddress(hDll, "USBm_Reset1Wire");
	USBm_Write1Wire =       (USBm_Write1Wire_type)GetProcAddress(hDll, "USBm_Write1Wire");
	USBm_Read1Wire =        (USBm_Read1Wire_type)GetProcAddress(hDll, "USBm_Read1Wire");
	USBm_RecentError =      (USBm_RecentError_type)GetProcAddress(hDll, "USBm_RecentError");
	USBm_ClearRecentError = (USBm_ClearRecentError_type)GetProcAddress(hDll, "USBm_ClearRecentError");
	USBm_DebugString =      (USBm_DebugString_type)GetProcAddress(hDll, "USBm_DebugString");
	USBm_Copyright =        (USBm_Copyright_type)GetProcAddress(hDll, "USBm_Copyright");
	USBm_About =            (USBm_About_type)GetProcAddress(hDll, "USBm_About");
	USBm_Version =          (USBm_Version_type)GetProcAddress(hDll, "USBm_Version");


	// Discover the USBmicro devices
	USBm_FindDevices();
	// How many devices are attached
	deviceCount = USBm_NumberOfDevices();

	serialNumbers = gcnew array<System::String^>(deviceCount);
	lastByteA = gcnew array<unsigned char>(deviceCount);
	lastByteB = gcnew array<unsigned char>(deviceCount);
	for (int i = 0 ; i < deviceCount ; i++)
	{
		char serialNumber[300];
		// Device serial number
		USBm_DeviceSer(i, serialNumber);
		serialNumbers[i] = gcnew System::String(serialNumber);
		lastByteA[i] = 0;
		lastByteB[i] = 0;
		USBm_InitPorts(i);
		USBm_DirectionA(i, 0x00, 0xFF);
		USBm_WriteA(i, 0xFF);
		USBm_DirectionB(i, 0x00, 0xFF);
		USBm_WriteB(i, 0xFF);
	}
	pollThread = nullptr;
}

bool BAPSController::run(SignalCallback^ _callback)
{
	if (hDll == 0)
	{
		return false;
	}
	callback = _callback;
	pollThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &BAPSController::runHelper));
	pollThread->Start();
	return true;
}
void BAPSController::runHelper()
{
	quit = false;
	int refreshCount = 0;
	unsigned char byteA, byteB;
	while (!quit)
	{
		for (int i = 0 ; i < deviceCount ; i++)
		{
			USBm_ReadA(i, &byteA);
			USBm_ReadB(i, &byteB);
			if (byteA != lastByteA[i])
			{
				/* Find all the bits that have just been cleared (signals a button push) */
				char buttonDown = (byteA^lastByteA[i])&lastByteA[i];
				char buttonRelease = (byteA^lastByteA[i])&byteA;
				for (int j = 0 ; j < 8 ; j++)
				{
					if ((buttonDown >> j)&0x1)
					{
						/** callback here **/
						callback(serialNumbers[i], j);
					}
				}
				lastByteA[i] = byteA;
			}
			if (byteB != lastByteB[i])
			{
				/* Find all the bits that have just been cleared (signals a button push) */
				char buttonDown = (byteB^lastByteB[i])&lastByteB[i];
				char buttonRelease = (byteB^lastByteB[i])&byteB;
				for (int j = 0 ; j < 8 ; j++)
				{
					if ((buttonDown >> j)&0x1)
					{
						/** callback here **/
						callback(serialNumbers[i], 8+j);
					}
				}
				lastByteB[i] = byteB;
			}
		}
		refreshCount++;
		if (refreshCount == 1000)
		{
			refreshCount = 0;

			for (int i = 0 ; i < deviceCount ; i++)
			{
				USBm_CloseDevice(i);
			}
			// Re-Discover the USBmicro devices
			USBm_FindDevices();
			// How many devices are attached
			int newDeviceCount = USBm_NumberOfDevices();

			array<System::String^>^ newSerialNumbers = gcnew array<System::String^>(newDeviceCount);
			array<unsigned char>^ newLastByteA = gcnew array<unsigned char>(newDeviceCount);
			array<unsigned char>^ newLastByteB = gcnew array<unsigned char>(newDeviceCount);

			for (int i = 0 ; i < newDeviceCount ; i++)
			{
				char serialNumber[300];
				// Device serial number
				USBm_DeviceSer(i, serialNumber);
				newSerialNumbers[i] = gcnew System::String(serialNumber);
				/* Match the offsets from the previous config (order of devices may have changed) */
				for (int j = 0 ; j < deviceCount ; j++)
				{
					if (serialNumbers[j]->Equals(newSerialNumbers[i]))
					{
						newLastByteA[i] = lastByteA[i];
						newLastByteB[i] = lastByteB[i];
					}
				}
				/* Re-initialise everything */
				USBm_InitPorts(i);
				USBm_DirectionA(i, 0x00, 0xFF);
				USBm_WriteA(i, 0xFF);
				USBm_DirectionB(i, 0x00, 0xFF);
				USBm_WriteB(i, 0xFF);
			}
		
			/* Swap in the new names and offsets */
			serialNumbers = newSerialNumbers;
			deviceCount = newDeviceCount;
			lastByteA = newLastByteA;
			lastByteB = newLastByteB;
		}
		SleepEx(10, FALSE);
	}
}

array<System::String^>^ BAPSController::getSerialNumbers()
{
	if (hasUSBDevices == true) {
		return safe_cast<array<System::String^>^>(serialNumbers->Clone());
	} else {
		array<System::String^>^ empty = gcnew array<System::String^>(0);
		return empty;
	}
}

bool BAPSController::hasUSB()
{
	return hasUSBDevices;
}