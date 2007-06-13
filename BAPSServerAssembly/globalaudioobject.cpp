#include <stdafx.h>
#include "GlobalAudioObject.h"
#include "ConfigManager.h"
#include "Exceptions.h"
#include "ClientManager.h"
#include "AsyncActionManager.h"

using namespace BAPSServerAssembly;

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
		activeChannels[i]->audioOutput = gcnew AudioOutput(m_AudioOutput);
		
		/** Make an empty playlist **/
		activeChannels[i]->currentPlaylist = gcnew Playlist(i);
	}
	/** Restore the state from the most recent statefile **/
	System::String^ path = System::Reflection::Assembly::GetExecutingAssembly()->Location;
	path = System::String::Concat(System::IO::Path::GetDirectoryName(path),"\\serverstate.xml");
	if (System::IO::File::Exists(path))
	{
		loadStateFromFile(path);
	}
}


GlobalAudioObject::~GlobalAudioObject()
{
	int i = 0;
	/** Stop and clean up all channels **/
	for (i = 0 ; i < CHANNEL_COUNT ; i++)
	{
        activeChannels[i]->audioOutput->stop();
		delete activeChannels[i]->audioOutput;
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
	AudioOutput^ AudioOutput = activeChannels[channel]->audioOutput;
	Playlist ^currentPlaylist = activeChannels[channel]->currentPlaylist;
	AudioOutput->stop();
	
	AsyncActionManager::incPlayCount(AudioOutput->getLoadedTrack());
	int advanceTo = currentPlaylist->getNextPlayable(AudioOutput->getLoadedTrack()->getEntryNumber()+1);
	int autoRepeat = CONFIG_GETINTn(CONFIG_REPEAT, channel);
	if (autoRepeat == 1)
	{
		AudioOutput->play();
	}
	else if (autoRepeat == 2)
	{
		if (advanceTo == -1)
		{
			advanceTo = currentPlaylist->getNextPlayable(0);
		}
		if (advanceTo != -1)
		{
			AudioOutput->loadTrack(safe_cast<Track^>(currentPlaylist->getEntry(advanceTo)));
		}
		if (CONFIG_GETINTn(CONFIG_AUTOPLAY, channel) == 0)
		{
			AudioOutput->play();
		}
	}
	else if ((advanceTo != -1) &&
		     (CONFIG_GETINTn(CONFIG_AUTOADVANCE, channel) != 0))
	{
		AudioOutput->loadTrack(safe_cast<Track^>(currentPlaylist->getEntry(advanceTo)));
	}

	ClientManager::releaseMessageLock();
}

void GlobalAudioObject::dumpAsXML(System::Xml::XmlWriter^ xw)
{
	int i;
	for (i = 0 ; i < CHANNEL_COUNT ; i++)
	{
		xw->WriteStartElement("channel");
		xw->WriteStartElement("channelnumber");
		xw->WriteValue(i);
		xw->WriteEndElement();
		/** Write out the playlist **/
		activeChannels[i]->currentPlaylist->dumpAsXML(xw);
		/** Write out the player state **/
		activeChannels[i]->audioOutput->dumpAsXML(xw);
		xw->WriteEndElement();
	}
}

void GlobalAudioObject::restoreFromXML(System::Xml::XmlReader^ xr)
{
	/** Prevent clients from making requests while restoring state **/
	ClientManager::getMessageLock();
	int i;
	for (i = 0 ; xr->IsStartElement("channel") ; i++)
	{
		xr->ReadStartElement("channel");
		xr->ReadStartElement("channelnumber");
		int j = xr->ReadContentAsInt();
		xr->ReadEndElement();
		/** Write out the playlist **/
		activeChannels[j]->currentPlaylist->restoreFromXML(xr);
		/** Write out the player state **/
		activeChannels[j]->audioOutput->restoreFromXML(xr);
		xr->ReadEndElement();
	}
	ClientManager::releaseMessageLock();
}

void GlobalAudioObject::loadStateFromFile(System::String ^filename)
{
	System::Xml::XmlReader^ xr = System::Xml::XmlReader::Create(filename);
	xr->Read();
	xr->ReadStartElement("bapsserverstate");
	ClientManager::getAudio()->restoreFromXML(xr);
	xr->ReadEndElement();
	xr->Close();
}

void GlobalAudioObject::loadStateFromText(System::String ^xml)
{
	System::IO::StringReader^ sr = gcnew System::IO::StringReader(xml);
	System::Xml::XmlReader^ xr = System::Xml::XmlReader::Create(sr);
	xr->Read();
	xr->ReadStartElement("bapsserverstate");
	ClientManager::getAudio()->restoreFromXML(xr);
	xr->ReadEndElement();
	xr->Close();
}