#pragma once

// Discovery routine
typedef int (__stdcall *USBm_FindDevices_type) ();

// Info about devices
typedef int (__stdcall *USBm_NumberOfDevices_type)   (void);
typedef int (__stdcall *USBm_DeviceValid_type)   (unsigned char);
typedef int (__stdcall *USBm_DeviceVID_type)   (unsigned char device);
typedef int (__stdcall *USBm_DevicePID_type)   (unsigned char device);
typedef int (__stdcall *USBm_DeviceDID_type)   (unsigned char device);
typedef int (__stdcall *USBm_DeviceMfr_type)   (unsigned char, char *);
typedef int (__stdcall *USBm_DeviceProd_type)   (unsigned char, char *);
typedef int (__stdcall *USBm_DeviceSer_type)   (unsigned char, char *);

// General U4xx functions
typedef int (__stdcall *USBm_InitPorts_type)  (unsigned char);
typedef int (__stdcall *USBm_CloseDevice_type)  (unsigned char);
typedef int (__stdcall *USBm_WriteA_type)  (unsigned char, unsigned char);
typedef int (__stdcall *USBm_WriteB_type)  (unsigned char, unsigned char);
typedef int (__stdcall *USBm_WriteABit_type)  (unsigned char, unsigned char, unsigned char);
typedef int (__stdcall *USBm_WriteBBit_type)  (unsigned char, unsigned char, unsigned char);
typedef int (__stdcall *USBm_ReadA_type)  (unsigned char, unsigned char *);
typedef int (__stdcall *USBm_ReadB_type)  (unsigned char, unsigned char *);
typedef int (__stdcall *USBm_SetBit_type)  (unsigned char, unsigned char);
typedef int (__stdcall *USBm_ResetBit_type)  (unsigned char, unsigned char);
typedef int (__stdcall *USBm_DirectionA_type)  (unsigned char, unsigned char, unsigned char);
typedef int (__stdcall *USBm_DirectionB_type)  (unsigned char, unsigned char, unsigned char);
typedef int (__stdcall *USBm_StrobeWrite_type)  (unsigned char, unsigned char, unsigned char, unsigned char);
typedef int (__stdcall *USBm_StrobeRead_type)  (unsigned char, unsigned char *, unsigned char, unsigned char);
typedef int (__stdcall *USBm_StrobeWrite2_type)  (unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
typedef int (__stdcall *USBm_StrobeRead2_type)  (unsigned char, unsigned char *, unsigned char, unsigned char, unsigned char);
typedef int (__stdcall *USBm_StrobeWrites_type)  (unsigned char, unsigned char *, unsigned char *);
typedef int (__stdcall *USBm_StrobeReads_type)  (unsigned char, unsigned char *, unsigned char *);
typedef int (__stdcall *USBm_InitLCD_type)  (unsigned char, unsigned char, unsigned char);
typedef int (__stdcall *USBm_LCDCmd_type)  (unsigned char, unsigned char);
typedef int (__stdcall *USBm_LCDData_type)  (unsigned char, unsigned char);
typedef int (__stdcall *USBm_InitSPI_type)  (unsigned char, unsigned char);
typedef int (__stdcall *USBm_SPIMaster_type)  (unsigned char, unsigned char *, unsigned char *);
typedef int (__stdcall *USBm_SPISlaveWrite_type)  (unsigned char, unsigned char, unsigned char *);
typedef int (__stdcall *USBm_SPISlaveRead_type)  (unsigned char, unsigned char *, unsigned char *);
typedef int (__stdcall *USBm_Stepper_type)  (unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
typedef int (__stdcall *USBm_Reset1Wire_type)  (unsigned char, unsigned char *);
typedef int (__stdcall *USBm_Write1Wire_type)  (unsigned char, unsigned char);
typedef int (__stdcall *USBm_Read1Wire_type)  (unsigned char, unsigned char *);

// DLL string info access
typedef int (__stdcall *USBm_RecentError_type)  (char *);
typedef int (__stdcall *USBm_ClearRecentError_type)  (void);
typedef int (__stdcall *USBm_DebugString_type)  (char *);
typedef int (__stdcall *USBm_Copyright_type)  (char *);
typedef int (__stdcall *USBm_About_type)  (char *);
typedef int (__stdcall *USBm_Version_type)  (char *);
