// BAPSAudioOutputDevices.cpp


#include "stdafx.h"
#include "BAPSAudioOutputDevices.h"


CBAPSAudioOutputDevices::CBAPSAudioOutputDevices()
{

	// Initialise member variables
	m_iDeviceCount = 0;
	ZeroMemory(&m_arpDevice, sizeof(m_arpDevice));
	m_bEnumerateSuccess = FALSE;

}


CBAPSAudioOutputDevices::~CBAPSAudioOutputDevices()
{

	// Let CleanUp sort it out
	CleanUp();

}


BOOL CBAPSAudioOutputDevices::Initialise()
{

	ICreateDevEnum* pCreateDeviceEnumerator;
	IEnumMoniker* pDeviceEnumerator;
	IMoniker* pDeviceMoniker;
	ULONG cFetched;

	// Create the system device enumerator
	if (FAILED(CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (void**)&pCreateDeviceEnumerator)))
	{
		CleanUp();
		return FALSE;
	}

	if (FAILED(pCreateDeviceEnumerator->CreateClassEnumerator(CLSID_AudioRendererCategory, &pDeviceEnumerator, 0)))
	{
		pCreateDeviceEnumerator->Release();
		CleanUp();
		return FALSE;
	}

	pCreateDeviceEnumerator->Release();
	pDeviceEnumerator->Reset();

	while (m_iDeviceCount < BAPS_MAX_DEVICES && S_OK == pDeviceEnumerator->Next(1, &pDeviceMoniker, &cFetched))
	{

		// Create a new device object
		if (NULL == (m_arpDevice[m_iDeviceCount] = new CBAPSAudioOutputDevice()))
		{
			pDeviceEnumerator->Release();
			CleanUp();
			return FALSE;
		}

		// Initialise it with the device info
		if (!m_arpDevice[m_iDeviceCount]->Initialise(pDeviceMoniker))
		{
			pDeviceMoniker->Release();
			pDeviceEnumerator->Release();
			CleanUp();
			return FALSE;
		}

		// Release the moniker
		pDeviceMoniker->Release();

		// Increment the device count
		m_iDeviceCount++;

	}

	// Release the enumerator
	pDeviceEnumerator->Release();

	return TRUE;

}


int CBAPSAudioOutputDevices::GetCount()
{

	// Return the number of devices
	return m_iDeviceCount;

}


CBAPSAudioOutputDevice* CBAPSAudioOutputDevices::GetDevice(int iIndex)
{

	// Check that the index is valid
	if (iIndex >= m_iDeviceCount || iIndex < 0)
	{
		return NULL;
	}

	// Return the specified device
	return m_arpDevice[iIndex];

}

CBAPSAudioOutputDevice* CBAPSAudioOutputDevices::GetDevice(LPCWSTR szID)
{

	// If NULL was passed in, we look for the empty string instead
	LPCWSTR szRequestedID = (NULL == szID) ? L"" : szID;
	LPCWSTR szCheckID = NULL;

	// Do a linear search through the devices
	for (int iDevice = 0; iDevice < BAPS_MAX_DEVICES; iDevice++)
	{
		// Make sure the device exists
		if (NULL != m_arpDevice[iDevice])
		{
			// Get the device's ID
			szCheckID = m_arpDevice[iDevice]->GetID();
			
			// Compare the IDs
			if (0 == wcscmp(szRequestedID, szCheckID))
			{
				// We've found it
				return m_arpDevice[iDevice];
			}
		}
	}

	// Not found, return NULL
	return NULL;

}


void CBAPSAudioOutputDevices::CleanUp()
{

	// Delete all the devices
	for (int iDevice = 0; iDevice < BAPS_MAX_DEVICES; iDevice++)
	{
		if (NULL != m_arpDevice[iDevice])
		{
			delete m_arpDevice[iDevice];
			m_arpDevice[iDevice] = NULL;
		}
	}

	m_iDeviceCount = 0;
	m_bEnumerateSuccess = FALSE;

}
