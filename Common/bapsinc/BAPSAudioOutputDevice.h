// BAPSAudioOutputDevice.h


#ifndef INCLUDED_BAPSAUDIOOUTPUTDEVICE_H
#define INCLUDED_BAPSAUDIOOUTPUTDEVICE_H


#include "BAPSCommon.h"


class BAPS_API CBAPSAudioOutputDevice
{

	friend class CBAPSAudioOutputDevices;
	friend class CBAPSAudioOutputChannel;
	

public:

	// Returns the description of the device
	// WARNING: Returns a pointer to our string - don't change or free it!
	LPCWSTR BAPS_CALL GetDescription();

	// Returns the device's module name
	// WARNING: Returns a pointer to our string - don't change or free it!
	LPCWSTR BAPS_CALL GetModule();

	// Returns the device's unique ID
	// WARNING: As above
	LPCWSTR BAPS_CALL GetID();


protected:

	// Constructor
	CBAPSAudioOutputDevice();

	// Destructor
	~CBAPSAudioOutputDevice();

	// Sets the device info
	BOOL Initialise(IMoniker* pDeviceMoniker);

	// Returns the string GUID of the device
	// WARNING: Returns a pointer to our string - don't change or free it!
	LPCWSTR GetGUID();

	// Takes a pointer to a string pointer and if the string pointer is NULL,
	// it assigns an empty string to it
	void NullToEmptyString(LPWSTR* pszString);

	// Frees memory and stuff
	void CleanUp();


protected:

	// The description
	LPWSTR m_szDescription;

	// The module
	LPWSTR m_szModule;

	// The GUID
	LPWSTR m_szGUID;


};


#endif //INCLUDED_BAPSAUDIOOUTPUTDEVICE_H