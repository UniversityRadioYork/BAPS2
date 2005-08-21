// BAPSAudioOutput.cpp


#include "stdafx.h"
#include "BAPSAudioOutput.h"


CBAPSAudioOutput::CBAPSAudioOutput()
{

	// Initialise COM
	CoInitialize(NULL);

	// Initialise member variables
	m_pChannels = NULL;
	m_pDevices = NULL;

}


CBAPSAudioOutput::~CBAPSAudioOutput()
{

	// Uninitialise COM
	CoUninitialize();

	// Let CleanUp handle it
	CleanUp();

}


BOOL CBAPSAudioOutput::Initialise(int iNumberOfChannels)
{

	// Create the output channels object
	if (NULL == (m_pChannels = new CBAPSAudioOutputChannels()))
	{
		CleanUp();
		return FALSE;
	}

	// Initialise the output channels object
	if (!m_pChannels->Initialise(iNumberOfChannels))
	{
		CleanUp();
		return FALSE;
	}

	// Create the output devices object
	if (NULL == (m_pDevices = new CBAPSAudioOutputDevices()))
	{
		CleanUp();
		return FALSE;
	}

	// Initialise the output devices object
	if (!m_pDevices->Initialise())
	{
		CleanUp();
		return FALSE;
	}

	return TRUE;

}


CBAPSAudioOutputChannels* CBAPSAudioOutput::GetAudioOutputChannels()
{

	// Return a pointer to the output channels object
	return m_pChannels;

}


CBAPSAudioOutputDevices* CBAPSAudioOutput::GetAudioOutputDevices()
{

	// Return a pointer to the output devices object
	return m_pDevices;

}


void CBAPSAudioOutput::CleanUp()
{

	// Delete the output channels object
	if (NULL != m_pChannels)
	{
		delete m_pChannels;
		m_pChannels = NULL;
	}

	// Delete the output devices object
	if (NULL != m_pDevices)
	{
		delete m_pDevices;
		m_pDevices = NULL;
	}

}
