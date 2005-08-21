// BAPSAudioOutputChannels.h


#ifndef INCLUDED_BAPSAUDIOOUTPUTCHANNELS_H
#define INCLUDED_BAPSAUDIOOUTPUTCHANNELS_H


#include "BAPSCommon.h"
#include "BAPSAudioOutputChannel.h"


#define BAPS_MAX_CHANNELS 16


class BAPS_API CBAPSAudioOutputChannels
{

	friend class CBAPSAudioOutput;


public:

	// Returns the number of channels
	int BAPS_CALL GetCount();

	// Returns the specified channel
	CBAPSAudioOutputChannel* BAPS_CALL GetChannel(int iIndex);


protected:

	//Constructor
	CBAPSAudioOutputChannels();

	//Destructor
	~CBAPSAudioOutputChannels();

	// Sets the notification window and creates the specified number of channels
	BOOL Initialise(int iNumberOfChannels);

	// Deletes objects and frees memory
	void CleanUp();


protected:

	// The number of channels
	int m_iChannelCount;

	// An array of channel pointers
	CBAPSAudioOutputChannel* m_arpChannel[BAPS_MAX_CHANNELS];


};


#endif //INCLUDED_BAPSAUDIOOUTPUTCHANNELS_H
