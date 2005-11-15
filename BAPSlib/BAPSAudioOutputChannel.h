// BAPSAudioOutputChannel.h


#ifndef INCLUDED_BAPSAUDIOOUTPUTCHANNEL_H
#define INCLUDED_BAPSAUDIOOUTPUTCHANNEL_H


#include "BAPSCommon.h"
#include "BAPSAudioOutputDevice.h"

// Function pointer for notifying a channel has stopped
typedef void (*NotifyCallback)(int);

// Still need to implement current graph state / play state
// and send events when they change

// Might be worth doing loading etc on a different thread
// to keep the client application responsive


class BAPS_API CBAPSAudioOutputChannel
{

	friend class CBAPSAudioOutputChannels;


public:

	// Sets the audio output device for this channel
	BOOL BAPS_CALL SetDevice(CBAPSAudioOutputDevice* pDevice);

	// Gets the audio output device
	CBAPSAudioOutputDevice* BAPS_CALL GetDevice();

	// Loads a new file into the channel
	BOOL BAPS_CALL LoadFile(LPCWSTR szFileName);

	// Starts/resumes playback of the current file
	BOOL BAPS_CALL Play();

	// Suspends playback of the current file
	BOOL BAPS_CALL Pause();

	// Suspends playback of the current file and resets the position to the start
	BOOL BAPS_CALL Stop();

	// Returns the duration of the current file
	int BAPS_CALL GetDuration();

	// Gets and sets the playback position within the current file
	int BAPS_CALL GetPosition();
	void BAPS_CALL SetPosition(int iPosition);

	// Gets and sets this channel's output volume
	// Range: 0.0 (silence) - 1.0 (maximum)
	float BAPS_CALL GetVolume();
	void BAPS_CALL SetVolume(float fVolume);

	// Gets and sets the channel's panning
	// Range -1.0 (fully left) - 1.0 (fully right)
	float BAPS_CALL GetPan();
	void BAPS_CALL SetPan(float fPan);


protected:

	// Constructor
	CBAPSAudioOutputChannel();

	// Destructor
	~CBAPSAudioOutputChannel();

	// Sets the windows handle to which the object should send its messages
	// and tells it its index in the collection
	BOOL Initialise(int iIndex, NotifyCallback _callback);

	// Releases interfaces, deletes objects, etc.
	void CleanUp();

	// Event monitoring thread procedures
	static DWORD WINAPI EventMonitorThreadProc(void* pParameter);
	DWORD EventMonitorThreadProc();

	__inline int ReferenceTimeToMilliseconds(LONGLONG* pllTime);
	__inline LONGLONG MillisecondsToReferenceTime(int nMilliseconds);


protected:

	// BAPS audio output device
	CBAPSAudioOutputDevice* m_pOutputDevice;

	// Graph builder
	IGraphBuilder* m_pGraphBuilder;

	// Media control
	IMediaControl* m_pMediaControl;

	// Media event
	IMediaEvent* m_pMediaEvent;

	// Media seeking
	IMediaSeeking* m_pMediaSeeking;

	// Basic Audio
	IBasicAudio* m_pBasicAudio;

	// Renderer filter
	IBaseFilter* m_pRendererFilter;

	// Source filter
	IBaseFilter* m_pSourceFilter;

	// Index of this object in the channels collection
	int m_iIndex;

	// Handle of the DirectShow event monitoring thread
	HANDLE m_hEventMonitorThread;

	// Event that's signalled when event monitoring should stop
	HANDLE m_hStopEventMonitorEvent;

	// The current state of the graph
	FILTER_STATE m_FilterState;

	// The callback
	NotifyCallback callback;

};


#endif //INCLUDED_BAPSAUDIOOUTPUTCHANNEL_H