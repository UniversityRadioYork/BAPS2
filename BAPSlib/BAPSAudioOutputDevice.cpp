// BAPSAudioOutputDevice.cpp


#include "stdafx.h"
#include "BAPSAudioOutputDevice.h"


CBAPSAudioOutputDevice::CBAPSAudioOutputDevice()
{

	// Initialise member variables
	m_szDescription = NULL;
	m_szModule = NULL;
	m_szGUID = NULL;

}


CBAPSAudioOutputDevice::~CBAPSAudioOutputDevice()
{

	// Let CleanUp sort it out
	CleanUp();

}


BOOL CBAPSAudioOutputDevice::Initialise(IMoniker* pDeviceMoniker)
{

	IPropertyBag* pPropertyBag;
	VARIANT varDescription;

	// Get the moniker's display name (we can create a filter from this)
	if (FAILED(pDeviceMoniker->GetDisplayName(NULL, NULL, &m_szGUID)))
	{
		return FALSE;
	}

	// Get the moniker's property bag
	if (FAILED(pDeviceMoniker->BindToStorage(NULL, NULL, IID_IPropertyBag, (void**)&pPropertyBag)))
	{
		CleanUp();
		return FALSE;
	}

	VariantInit(&varDescription);
	varDescription.vt = VT_BSTR;

	// Get the device's friendly name
	if (FAILED(pPropertyBag->Read(L"FriendlyName", &varDescription, 0)))
	{
		pPropertyBag->Release();
		CleanUp();
		return FALSE;
	}

	// Copy the string
	if (NULL == (m_szDescription = (LPWSTR)malloc(sizeof(WCHAR) * (wcslen(varDescription.bstrVal) + 1))))
	{
		CleanUp();
		return FALSE;
	}

	wcscpy(m_szDescription, varDescription.bstrVal);
	
	// Free the variant and release the property bag interface
	VariantClear(&varDescription);
	pPropertyBag->Release();

	// This implementation doesn't support modules
	NullToEmptyString(&m_szModule);

	return TRUE;

}


LPCWSTR CBAPSAudioOutputDevice::GetDescription()
{

	// Return the description string
	return m_szDescription;

}


LPCWSTR CBAPSAudioOutputDevice::GetModule()
{

	// Return the module string
	return m_szModule;

}

LPCWSTR CBAPSAudioOutputDevice::GetID()
{

	// The ID is the same as the GUID
	return GetGUID();

}


LPCWSTR CBAPSAudioOutputDevice::GetGUID()
{

	// Return the GUID string
	return m_szGUID;

}


void CBAPSAudioOutputDevice::NullToEmptyString(LPWSTR* pszString)
{

	// Check if it's NULL
	if (NULL == *pszString)
	{
		// Allocate it a single character with malloc (so CleanUp will work)
		*pszString = (LPWSTR)malloc(sizeof(WCHAR));

		// Set it to zero
		**pszString = 0;

	}

}


void CBAPSAudioOutputDevice::CleanUp()
{

	// Free the description memory
	if (NULL != m_szDescription)
	{
		free(m_szDescription);
		m_szDescription = NULL;
	}

	// Free the module memory
	if (NULL != m_szModule)
	{
		free(m_szModule);
		m_szModule = NULL;
	}

	// Free the GUID memory
	if (NULL != m_szGUID)
	{
		CoTaskMemFree(m_szGUID);
		m_szGUID = NULL;
	}

}