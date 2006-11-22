#include "stdafx.h"
#include "ClientInstance.h"
#include "AsyncActionManager.h"
#include "TextEntry.h"

/**
 *  This file contains the implementations of all the PLAYBACK functionality
**/

BEGIN_ACTION_BLOCKED1(play, unsigned char channel)
{
	if (channel < CHANNEL_COUNT)
	{
		/** Ignoring true return value as it is implicit
		 *  Play will return false if there is no valid file loaded
		**/
		if (!ClientManager::getAudio()->getOutput(channel)->play())
		{
			// WORK NEEDED: tell non autoupdate clients what just happened
		}
	}
	else
	{
		LogManager::write(System::String::Concat("Invalid channel: ", channel.ToString(), ", in play command"), LOG_WARNING, LOG_PLAYBACK);
	}
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED1(stop, unsigned char channel)
{
	if (channel < CHANNEL_COUNT)
	{
		/** Ignoring true return value as it is implicit
		 *  Stop will return false if there is no valid file loaded
		**/
		if (!ClientManager::getAudio()->getOutput(channel)->stop())
		{
			// WORK NEEDED: tell non autoupdate clients what just happened
		}
	}
	else
	{
		LogManager::write(System::String::Concat("Invalid channel: ", channel.ToString(), ", in stop command"), LOG_WARNING, LOG_PLAYBACK);
	}
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED1(pause, unsigned char channel)
{
	if (channel < CHANNEL_COUNT)
	{
		/** Ignoring true return value as it is implicit
		 *  Pause will return false if there is no valid file loaded
		**/
		if (!ClientManager::getAudio()->getOutput(channel)->pause())
		{
			// WORK NEEDED: tell non autoupdate clients what just happened
		}
	}
	else
	{
		LogManager::write(System::String::Concat("Invalid channel: ", channel.ToString(), ", in pause command"), LOG_WARNING, LOG_PLAYBACK);
	}
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED2(setVolume, System::Byte channel, float value)
{
	if (channel < CHANNEL_COUNT)
	{
		ClientManager::getAudio()->getOutput(channel)->setChannelVolume(value);
	}
	else
	{
		LogManager::write(System::String::Concat("Invalid channel: ", channel.ToString(), ", in setVolume command"), LOG_WARNING, LOG_PLAYBACK);
	}
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED2(moveToPosition, System::Byte channel, u32int value)
{
	if (channel < CHANNEL_COUNT)
	{
		/** Always succeeds even if there is no file loaded or it is an invalid position **/
		ClientManager::getAudio()->getOutput(channel)->setFilePosition(value);
	}
	else
	{
		LogManager::write(System::String::Concat("Invalid channel: ", channel.ToString(), ", in moveToPosition command"), LOG_WARNING, LOG_PLAYBACK);
	}
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED2(setCue, System::Byte channel, u32int value)
{
	/** This is stored in the playout class and is currently only explicitly known at the server **/
	if (channel < CHANNEL_COUNT)
	{
		/** Always succeeds **/
		ClientManager::broadcast(BAPSNET_PLAYBACK | BAPSNET_CUEPOSITION | (channel & 0x3f),
								value);
		ClientManager::getAudio()->getOutput(channel)->getLoadedTrack()->CuePosition = value;
	}
	else
	{
		LogManager::write(System::String::Concat("Invalid channel: ", channel.ToString(), ", in setCue command"), LOG_WARNING, LOG_PLAYBACK);
	}
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED2(setIntro, System::Byte channel, u32int value)
{
	/** This is stored in the playout class and is currently only explicitly known at the server **/
	if (channel < CHANNEL_COUNT)
	{
		/** Always succeeds **/
		ClientManager::broadcast(BAPSNET_PLAYBACK | BAPSNET_INTROPOSITION | (channel & 0x3f),
								value);
		Track^ loadedTrack = ClientManager::getAudio()->getOutput(channel)->getLoadedTrack();
		loadedTrack->IntroPosition = value;
		/** Update the entry if it is a library item **/
		if (loadedTrack->getType() == BAPSNET_LIBRARYITEM)
		{
			AsyncActionManager::addIntroPosition(safe_cast<LibraryTrack^>(loadedTrack)->TrackID, value);
		}
	}
	else
	{
		LogManager::write(System::String::Concat("Invalid channel: ", channel.ToString(), ", in setIntro command"), LOG_WARNING, LOG_PLAYBACK);
	}
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED2(loadFile, System::Byte channel, u32int index)
{
	if (channel <CHANNEL_COUNT)
	{
		Entry^ thisEntry = ClientManager::getAudio()->getPlaylist(channel)->getEntry(index);
		if (thisEntry != nullptr)
		{
			if (thisEntry->getType() == BAPSNET_TEXTITEM)
			{
				TextEntry^ te = safe_cast<TextEntry^>(thisEntry);
				/** Fill the client in with details of the loaded track **/
				Command cmd = BAPSNET_PLAYBACK | BAPSNET_LOAD | (channel & 0x3f);
				ClientManager::broadcast( cmd,
										  (u32int)te->getPosition(),
										  (u32int)te->getType(),
										  te->getDescription(),
										  te->getText());
				ClientManager::getAudio()->getPlaylist(channel)->setLoadedTextEntry(index);
			}
			else if (!ClientManager::getAudio()->getOutput(channel)->isPlaying())
			{
				if (ClientManager::getAudio()->getOutput(channel)->loadTrack(safe_cast<Track^>(thisEntry)))
				{
					// WORK NEEDED: tell non autoupdate clients what just happened
				}
				else
				{
					// WORK NEEDED: tell non autoupdate clients what just happened
				}
			}
		}
	}
	else
	{
		LogManager::write(System::String::Concat("Invalid channel: ", channel.ToString(), ", in loadFile command"), LOG_WARNING, LOG_PLAYBACK);
	}
}
END_ACTION_UNBLOCK();