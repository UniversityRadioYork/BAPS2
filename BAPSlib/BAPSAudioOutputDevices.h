// BAPSAudioOutputDevices.h


#ifndef INCLUDED_BAPSAUDIOOUTPUTDEVICES_H
#define INCLUDED_BAPSAUDIOOUTPUTDEVICES_H


#include "BAPSCommon.h"
#include "BAPSAudioOutputDevice.h"


#define BAPS_MAX_DEVICES 32


class BAPS_API CBAPSAudioOutputDevices
{

	friend class CBAPSAudioOutput;


public:

	// Returns the number of devices
	int BAPS_CALL GetCount();

	// Returns the device at the specified index
	CBAPSAudioOutputDevice* BAPS_CALL GetDevice(int iIndex);

	// Returns the device with the specified identifier
	// Can pass NULL for the default audio device
	CBAPSAudioOutputDevice* BAPS_CALL GetDevice(LPCWSTR szID);

	// Constructor
	CBAPSAudioOutputDevices();

	// Destructor
	~CBAPSAudioOutputDevices();

	// Enumerates the available devices ready for use
	BOOL Initialise();

protected:

	// The callback function for Direct Sound device enumeration
	static BOOL CALLBACK DSDeviceEnumCallback(LPGUID lpGUID, LPCTSTR szDescription, LPCTSTR szModule, LPVOID lpContext);

	// The callback handler
	BOOL DSDeviceEnumCallback(LPGUID lpGUID, LPCTSTR szDescription, LPCTSTR szModule);

	// Free memory and stuff
	void CleanUp();


protected:

	// The number of devices
	int m_iDeviceCount;

	// An array of device object pointers
	CBAPSAudioOutputDevice* m_arpDevice[BAPS_MAX_DEVICES];

	// Whether the enumeration succeeded
	BOOL m_bEnumerateSuccess;

};


#endif //INCLUDED_BAPSAUDIOOUTPUTDEVICES_H