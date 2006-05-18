#pragma once

#include "PlayoutObject.h"
#include "ConfigManager.h"


/**
 *  GlobalAudioObject manages the output channels and related playlist information
 *  This is essentially global data
**/
ref struct sChannel
{
	PlayoutObject^ playoutObject;
	Playlist ^currentPlaylist;
};
	
ref class GlobalAudioObject
{
public:
	GlobalAudioObject();
	~GlobalAudioObject();
	/** Inline these so they get compiled out, they guard against accidental modification **/
	inline PlayoutObject^ getOutput(int channel)
	{
		if (channel < CHANNEL_COUNT)
		{
			/** Get the Output from the channel struct **/
			return activeChannels[channel]->playoutObject;
		}
		else
		{
			/** We should never hit this case as caller should guard against OOB channel **/
			return nullptr;
		}
	}
	inline Playlist^ getPlaylist(int channel)
	{
		if (channel < CHANNEL_COUNT)
		{
			/** Get the Playlist from the channel struct **/
			return activeChannels[channel]->currentPlaylist;
		}
		else
		{
			/** We should never hit this case as caller should guard against OOB channel **/
			return nullptr;
		}
	}
	void notifyDelegate(int _channel)
	{
		_channel++;
	}

	/** Managed equivalent to the callback above **/
	static void notifyCallback(int channel);

	/** No public variables **/
private:
	/** Contains the array of channel pairs (output/playlist) **/
	static array<sChannel^>^ activeChannels;
	/** The global handle to the BAPS library audio
	 *  (This should never be accessible outside this class
	**/
	CBAPSAudioOutput *m_AudioOutput;
};

	/** Inner unmanaged class to expose functionality to BAPSlib **/
	class UnmanagedCallBacks
	{
	public:
		static void notifyCallback(int channel)
		{
			GlobalAudioObject::notifyCallback(channel);
		}
	};