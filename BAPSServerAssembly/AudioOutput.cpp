#include "stdafx.h"
#include "AudioOutput.h"
#include "ClientManager.h"
#include "Track.h"
#include "LibraryTrack.h"
#include "TextEntry.h"
#include "ClientInstance.h"
#include "AsyncActionManager.h"

using namespace BAPSServerAssembly;

/**
 *  This file contains the BAPS library interface abstraction
**/

AudioOutput::AudioOutput(CBAPSAudioOutput *m_AudioOutput)
{
	audioOutput = m_AudioOutput;
	bool errorFound = false;
	/** Channel start not ready indicating no file loaded **/
	channelStatus = CHANNEL_INVALID;
	/** We maintain a static count of the channels allocated in channelCount **/
	channelNumber = channelCount;
	channelCount++;
	/** Read the device name from the registry **/
	System::String^ AudioDeviceID = CONFIG_GETSTRn(CONFIG_DEVICE,channelNumber);
	/** 
		BAPS needs an LPWSTR, we send it a managed LPWSTR as it is used only
	    for a lookup this is safe, ie it is not stored in unmanaged code.
	**/
	LPWSTR szDevice = stringToLPWSTR(AudioDeviceID);
	/** Fetch the correct output device **/
	CBAPSAudioOutputDevice* pSelectedDevice = audioOutput->GetAudioOutputDevices()->GetDevice(szDevice);

	/** Fetch a handle for the output channel **/
	pChannel = audioOutput->GetAudioOutputChannels()->GetChannel(channelNumber);

	/** Tell the channel what device to use **/
	if (pChannel == 0 || pSelectedDevice == 0 || (pChannel->SetDevice(pSelectedDevice) == FALSE))
	{
		errorFound = true;
	}
	/** Make sure the channel is safe by setting the loaded track to a null track **/
	notLoadedTrack = gcnew Track("c:\\NOT LOADED");
	notLoadedTrack->setEntryNumber(-1);
	loadedTrack = notLoadedTrack;
	if (!errorFound)
	{
		channelStatus = CHANNEL_NOT_LOADED;
	}
}

AudioOutput::~AudioOutput()
{
	/** Make GC hints clear **/
	pChannel = 0;
	channelStatus = CHANNEL_NOT_LOADED;
	delete notLoadedTrack;
	notLoadedTrack = nullptr;
}

bool AudioOutput::play(bool updateLog)
{
	/** Play succeeds iff channel is loaded and the channel accepts the play command **/
	bool returnValue = false;
	if (isLoaded() && isPlayable() && !isPlaying())
	{
		pChannel->Pause();
		pChannel->SetPosition(loadedTrack->CuePosition);
		if (pChannel->Play() == TRUE)
		{
			if (updateLog ||
				CONFIG_GETINT(CONFIG_STOREPLAYBACKEVENTS) == CONFIG_PLAYBACKEVENT_STORE_ALL)
			{
				AsyncActionManager::logPlayEvent(channelNumber,loadedTrack);
			}
			setPlaying();
			returnValue = true;
			Command cmd = BAPSNET_PLAYBACK | BAPSNET_PLAY | (channelNumber & 0x3f);
			ClientManager::broadcast(cmd);
		}
	}
	if (!returnValue && !isPlaying())
	{
		Command cmd = BAPSNET_SYSTEM | BAPSNET_SENDLOGMESSAGE;
		System::String^ message = System::String::Concat("Channel: ", channelNumber.ToString(), ", Play failed: No file loaded\n");
		ClientManager::broadcast( cmd, message);
	}
	return returnValue;
}

bool AudioOutput::pause()
{
	/** Pause succeeds iff the channel is loaded and the appropriate command succeeds **/
	bool returnValue = false;
	if (isLoaded() && isPlayable())
	{
		if (isPaused())
		{
			setPlaying();
			returnValue = (pChannel->Play() == TRUE);
			Command cmd = BAPSNET_PLAYBACK | BAPSNET_PLAY | (channelNumber & 0x3f);
			ClientManager::broadcast(cmd);
		}
		else
		{
			setPaused();
			returnValue = (pChannel->Pause() == TRUE);
			Command cmd = BAPSNET_PLAYBACK | BAPSNET_PAUSE | (channelNumber & 0x3f);
			ClientManager::broadcast(cmd);
		}
	}
	if (!returnValue)
	{
		Command cmd = BAPSNET_SYSTEM | BAPSNET_SENDLOGMESSAGE;
		System::String^ message = System::String::Concat("Channel: ", channelNumber.ToString(), ", Pause failed: No file loaded\n");
		ClientManager::broadcast( cmd, message);
	}
	return returnValue;
}

bool AudioOutput::stop()
{
	/** Stop succeeds if the channel is loaded and can be stopped **/
	bool returnValue = false;
	if (isLoaded() && isPlayable())
	{
		if (pChannel->Stop() == TRUE)
		{
			setStopped();
			pChannel->SetPosition(loadedTrack->CuePosition);
			returnValue = true;
			Command cmd = BAPSNET_PLAYBACK | BAPSNET_STOP | (channelNumber & 0x3f);
			ClientManager::broadcast(cmd);
			AsyncActionManager::logStopEvent(this->channelNumber, loadedTrack);
		}
	}
	if (!returnValue)
	{
		Command cmd = BAPSNET_SYSTEM | BAPSNET_SENDLOGMESSAGE;
		System::String^ message = System::String::Concat("Channel: ", channelNumber.ToString(), ", Stop failed: No file loaded\n");
		ClientManager::broadcast( cmd, message);
	}
	return returnValue;
}

bool AudioOutput::loadTrack(Track^ entry)
{
	if (isPlaying())
	{
		return false;
	}
	/** Passing managed data to unmanaged library
	 *  WORK NEEDED: investigate danger
	**/
	/** For large files the LOADING message is helpful to let the client know work is happening **/
	Command cmd = BAPSNET_PLAYBACK | BAPSNET_LOAD | (channelNumber & 0x3f);
	ClientManager::broadcast( cmd,
							  (u32int)-1,
							  (u32int)BAPSNET_VOIDITEM,
							  "--LOADING--");

	if(isLoaded() && isPlayable())
	{
		stop();
	}

	pin_ptr<const wchar_t> szFilename = PtrToStringChars(entry->getFileLocation());

	if (isValid() && pChannel->LoadFile(szFilename) == TRUE)
	{
		/** Inform the channel what it is playing **/
		loadedTrack = entry;
		/** Assert that something is loaded and currently stopped **/
		setStopped();
		/** Move to the cue position **/
		pChannel->SetPosition(loadedTrack->CuePosition);

		/** Fill the client in with details of the loaded track **/
		cmd = BAPSNET_PLAYBACK | BAPSNET_LOAD | (channelNumber & 0x3f);
		ClientManager::broadcast( cmd,
								(u32int)loadedTrack->getEntryNumber(),
								(u32int)loadedTrack->getType(),
								loadedTrack->ToString(),
								getFileDuration());
		Command cmd = BAPSNET_PLAYBACK | BAPSNET_POSITION | (channelNumber & 0x3f);
		ClientManager::broadcast( cmd, (u32int)loadedTrack->CuePosition);
		ClientManager::broadcast(BAPSNET_PLAYBACK | BAPSNET_CUEPOSITION | (channelNumber & 0x3f),
								 (u32int)loadedTrack->CuePosition);

		ClientManager::broadcast(BAPSNET_PLAYBACK | BAPSNET_INTROPOSITION | (channelNumber & 0x3f),
							 (u32int)loadedTrack->IntroPosition);


		if (CONFIG_GETINTn(CONFIG_AUTOPLAY, channelNumber) != 0)
		{
			play(false);
		}
		return true;
	}
	else
	{
		setNotLoaded();
		notLoadedTrack->setEntryNumber(entry->getEntryNumber());
		/** Make the client aware that loading failed **/
		cmd = BAPSNET_PLAYBACK | BAPSNET_LOAD | (channelNumber & 0x3f);
		ClientManager::broadcast( cmd,
								  (u32int)entry->getEntryNumber(),
								  (u32int)BAPSNET_VOIDITEM,
								  "--LOAD FAILED--");
		ClientManager::broadcast(BAPSNET_PLAYBACK | BAPSNET_CUEPOSITION | (channelNumber & 0x3f),
								 (u32int)0);
		ClientManager::broadcast(BAPSNET_PLAYBACK | BAPSNET_INTROPOSITION | (channelNumber & 0x3f),
								 (u32int)0);
		return false;
	}

	return false;
}

void AudioOutput::setChannelVolume(float volume)
{
	if (isValid())
	{
		pChannel->SetVolume(volume);
		Command cmd = BAPSNET_PLAYBACK | BAPSNET_VOLUME | (channelNumber & 0x3f);
		ClientManager::broadcast( cmd, volume);
	}
	/** WORK NEEDED: else case **/
}
void AudioOutput::setFilePosition(unsigned int position)
{
	if (isLoaded() && isPlayable())
	{
		pChannel->SetPosition(position);
		Command cmd = BAPSNET_PLAYBACK | BAPSNET_POSITION | (channelNumber & 0x3f);
		ClientManager::broadcast( cmd, position);
	}
	/** WORK NEEDED: else case **/
}

void AudioOutput::resetChannel(bool setDefaultConfig)
{
	stop();
	setNotLoaded();
	/** WORK NEEDED: this code allows channels to reattach to their chosen devices
					 if for some reason they have been kicked off
	**/
	/** Read the device name from the registry **/
	System::String^ AudioDeviceID = CONFIG_GETSTRn(CONFIG_DEVICE,channelNumber);
	/** 
		BAPS needs an LPWSTR, we send it a managed LPWSTR as it is used only
	    for a lookup this is safe, ie it is not stored in unmanaged code.
	**/
	LPWSTR szDevice = stringToLPWSTR(AudioDeviceID);
	/** Fetch the correct output device **/
	CBAPSAudioOutputDevice* pSelectedDevice = audioOutput->GetAudioOutputDevices()->GetDevice(szDevice);

	/** Tell the channel what device to use **/
	if (pChannel->SetDevice(pSelectedDevice) == FALSE)
	{
		/** WORK NEEDED: hmm difficult one to resolve **/
	}

	Command cmd = BAPSNET_PLAYBACK | BAPSNET_LOAD | (channelNumber & 0x3f);
	ClientManager::broadcast( cmd,
							(u32int)-1,
							(u32int)BAPSNET_VOIDITEM,
							"--NONE--");
	ClientManager::broadcast(BAPSNET_PLAYBACK | BAPSNET_CUEPOSITION | (channelNumber & 0x3f),
							 (u32int)0);
	ClientManager::broadcast(BAPSNET_PLAYBACK | BAPSNET_INTROPOSITION | (channelNumber & 0x3f),
							 (u32int)0);
	ClientManager::broadcast(BAPSNET_PLAYBACK | BAPSNET_VOLUME | (channelNumber & 0x3f),
							 getChannelVolume());

	if (setDefaultConfig)
	{
		CONFIG_SETn(CONFIG_AUTOADVANCE,channelNumber,CONFIG_YES_VALUE);
		CONFIG_SETn(CONFIG_AUTOPLAY,channelNumber,CONFIG_NO_VALUE);
		CONFIG_SETn(CONFIG_REPEAT,channelNumber,CONFIG_REPEAT_NONE_VALUE);
		ClientInstance::sendOptionConfigSettings(CONFIG_AUTOADVANCE, true,nullptr);
		ClientInstance::sendOptionConfigSettings(CONFIG_AUTOPLAY, true,nullptr);
		ClientInstance::sendOptionConfigSettings(CONFIG_REPEAT, true,nullptr);
	}
}


void AudioOutput::dumpAsXML(System::Xml::XmlWriter^ xw)
{
	xw->WriteStartElement("loaded");
	xw->WriteStartElement("entrynumber");
	xw->WriteValue(loadedTrack->getEntryNumber());
	xw->WriteEndElement();
	xw->WriteStartElement("position");
	xw->WriteValue(pChannel->GetPosition());
	xw->WriteEndElement();
	xw->WriteEndElement();
	xw->WriteStartElement("volume");
	xw->WriteValue(pChannel->GetVolume());
	xw->WriteEndElement();
	xw->WriteStartElement("state");
	if (isPlaying())
	{
		xw->WriteString("playing");
	}
	else if (isPaused())
	{
		xw->WriteString("paused");
	}
	else
	{
		xw->WriteString("stopped");
	}
	xw->WriteEndElement();
}

void AudioOutput::restoreFromXML(System::Xml::XmlReader^ xr)
{
	xr->ReadStartElement("loaded");
	xr->ReadStartElement("entrynumber");
	int indexToLoad = xr->ReadContentAsInt();
	Entry^ e = ClientManager::getAudio()->getPlaylist(channelNumber)->getEntry(indexToLoad);
	if (e != nullptr && e->isPlayable())
	{
		loadTrack(safe_cast<Track^>(e));
	}
	xr->ReadEndElement();
	xr->ReadStartElement("position");
	int newPosition = xr->ReadContentAsInt();
	if (!isPlaying())
	{
		setFilePosition(newPosition);
	}
	xr->ReadEndElement();
	xr->ReadEndElement();
	xr->ReadStartElement("volume");
	setChannelVolume(xr->ReadContentAsFloat());
	xr->ReadEndElement();
	xr->ReadStartElement("state");
	System::String^ state = xr->ReadContentAsString();
	if (state->Equals("playing") && !isPlaying())
	{
		/** double pause to start from position that is loaded **/
		pause();
		pause();
	}
	else if (state->Equals("paused") && !isPlaying())
	{
		pause();
	}
	xr->ReadEndElement();
}