// BAPSAudioOutput.h


#ifndef INCLUDED_BAPSAUDIOOUTPUT_H
#define INCLUDED_BAPSAUDIOOUTPUT_H


#include "BAPSCommon.h"
#include "BAPSAudioOutputChannels.h"
#include "BAPSAudioOutputDevices.h"


class BAPS_API CBAPSAudioOutput
{


public:

	// Constructor
	CBAPSAudioOutput();

	// Destructor
	~CBAPSAudioOutput();


public:

	// Initialises BAPS audio output ready for use
	BOOL BAPS_CALL Initialise(int iNumberOfChannels = 1);

	// Returns the collection of audio output channels
	CBAPSAudioOutputChannels* BAPS_CALL GetAudioOutputChannels();

	// Returns the collection of audio output devices
	CBAPSAudioOutputDevices* BAPS_CALL GetAudioOutputDevices();


protected:

	// Deletes objects, frees memory, etc.
	void CleanUp();

	// The collection of channels
	CBAPSAudioOutputChannels* m_pChannels;

	// The collection of devices
	CBAPSAudioOutputDevices* m_pDevices;

};


#endif //INCLUDED_BAPSAUDIOOUTPUT_H