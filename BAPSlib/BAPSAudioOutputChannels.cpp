// BAPSAudioOutputChannels.cpp


#include "stdafx.h"
#include "BAPSAudioOutputChannels.h"


CBAPSAudioOutputChannels::CBAPSAudioOutputChannels()
{

	// Initialise member variables
	m_iChannelCount = 0;
	ZeroMemory(&m_arpChannel, sizeof(m_arpChannel));

}


CBAPSAudioOutputChannels::~CBAPSAudioOutputChannels()
{

	// Let CleanUp take care of it
	CleanUp();

}


BOOL CBAPSAudioOutputChannels::Initialise(int iNumberOfChannels, NotifyCallback _callback)
{
	callback = _callback;
	// Check that the number of channels is valid
	if (iNumberOfChannels > BAPS_MAX_CHANNELS || iNumberOfChannels <= 0)
	{
		CleanUp();
		return FALSE;
	}

	// Create the channels
	for (int iChannel = 0; iChannel < iNumberOfChannels; iChannel++)
	{

		if (NULL == (m_arpChannel[iChannel] = new CBAPSAudioOutputChannel()))
		{
			CleanUp();
			return FALSE;
		}

		if (!m_arpChannel[iChannel]->Initialise(iChannel, _callback))
		{
			CleanUp();
			return FALSE;
		}

	}

	m_iChannelCount = iNumberOfChannels;

	// Success!
	return TRUE;

}


int CBAPSAudioOutputChannels::GetCount()
{

	// Return the channel count
	return m_iChannelCount;

}


CBAPSAudioOutputChannel* CBAPSAudioOutputChannels::GetChannel(int iIndex)
{

	// Check that the index is valid
	if (iIndex >= m_iChannelCount || iIndex < 0)
	{
		return NULL;
	}

	// Return the specified channel
	return m_arpChannel[iIndex];

}


void CBAPSAudioOutputChannels::CleanUp()
{

	// Delete the channel objects
	for (int iChannel = 0; iChannel < BAPS_MAX_CHANNELS; iChannel++)
	{
		if (NULL != m_arpChannel[iChannel])
		{
			delete m_arpChannel[iChannel];
			m_arpChannel[iChannel] = NULL;
		}
	}

	m_iChannelCount = 0;

}