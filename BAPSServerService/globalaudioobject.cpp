#include <stdafx.h>
#include "GlobalAudioObject.h"
#include "ConfigManager.h"
#include "Exceptions.h"
#include "ClientManager.h"
#include "AsyncActionManager.h"

/**
 *  This file contains all the objects holding information about a channel
 *  GlobalAudioObject is responsible for the output device initialisation
**/

GlobalAudioObject::GlobalAudioObject()
{
	/** Create the only visible object from BAPS library
	 *  Make sure this doesn't happen twice!!
	 *  This is the only unmanaged object which we create
	**/
	
	m_AudioOutput = new CBAPSAudioOutput();

	NotifyCallback cb = UnmanagedCallBacks::notifyCallback;
	/** BAPS library doesn't initialise on construction... **/
	if (m_AudioOutput->Initialise( CHANNEL_COUNT,cb ) == FALSE)
	{
		/**
			Ok so this is bad. The only thing we can do is suggest
			that the channel count is too high.
			We DO NOT want to terminate /but/ we need to keep our state valid.
			WORK NEEDED: find out from library what went wrong
		**/
		LogManager::write("Failed to initialize audio at startup -- Starting with 1 channel",
						  LOG_ERROR, LOG_OBJECTS);
		if ( m_AudioOutput->Initialise( 1,cb ) == FALSE )
		{
			/** We are dead, If it is impossible to initialize one channel then we have to exit **/
			throw gcnew BAPSTerminateException("GlobalAudioObject.cpp - Failed to initialize any channels - Contact an engineer");
		}
		else
		{
			ConfigManager::setChannelCount(1);
		}
	}

	/** Make the desired number of channels	**/
	activeChannels = gcnew array<sChannel^>(CHANNEL_COUNT);
	int i = 0;
	/** Each channel needs a playlist and an output **/
	for (i = 0 ; i < CHANNEL_COUNT ; i++)
	{
		activeChannels[i] = gcnew sChannel();
		/** Create the new output **/
		activeChannels[i]->playoutObject = gcnew PlayoutObject(m_AudioOutput);
		
		/** Make an empty playlist **/
		activeChannels[i]->currentPlaylist = gcnew Playlist(i);
	}
}


GlobalAudioObject::~GlobalAudioObject()
{
	int i = 0;
	/** Stop and clean up all channels **/
	for (i = 0 ; i < CHANNEL_COUNT ; i++)
	{
        activeChannels[i]->playoutObject->stop();
		delete activeChannels[i]->playoutObject;
		delete activeChannels[i]->currentPlaylist;
	}
	/** GC helpful hints **/
	delete [] activeChannels;
	activeChannels = nullptr;

	/** VERY IMPORTANT: unmanaged object should always be deleted **/
	delete m_AudioOutput;
	m_AudioOutput = 0;
}

void GlobalAudioObject::notifyCallback(int channel)
{
	if (channel >= CHANNEL_COUNT)
	{
		LogManager::write(System::String::Concat("Received notification from unknown channel: ", channel.ToString()), LOG_ERROR, LOG_SYSTEM);
		return;
	}
	ClientManager::getMessageLock();
	PlayoutObject^ playoutObject = activeChannels[channel]->playoutObject;
	Playlist ^currentPlaylist = activeChannels[channel]->currentPlaylist;
	playoutObject->stop();
	
	AsyncActionManager::incPlayCount(playoutObject->getLoadedTrack());
	int advanceTo = currentPlaylist->getNextPlayable(playoutObject->getLoadedTrack()->getPosition()+1);
	int autoRepeat = CONFIG_GETINTn(CONFIG_REPEAT, channel);
	if (autoRepeat == 1)
	{
		playoutObject->play();
	}
	else if (autoRepeat == 2)
	{
		if (advanceTo == -1)
		{
			advanceTo = currentPlaylist->getNextPlayable(0);
		}
		if (advanceTo != -1)
		{
			playoutObject->loadTrack(safe_cast<Track^>(currentPlaylist->getEntry(advanceTo)));
		}
		if (CONFIG_GETINTn(CONFIG_AUTOPLAY, channel) == 0)
		{
			playoutObject->play();
		}
	}
	else if ((advanceTo != -1) &&
		     (CONFIG_GETINTn(CONFIG_AUTOADVANCE, channel) != 0))
	{
		playoutObject->loadTrack(safe_cast<Track^>(currentPlaylist->getEntry(advanceTo)));
	}

	ClientManager::releaseMessageLock();
}