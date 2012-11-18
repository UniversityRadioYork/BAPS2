#include "stdafx.h"
#include "ClientInstance.h"
#include "Exceptions.h"
#include "Track.h"

using namespace BAPSServerAssembly;

/**
 *  This file contains the implementations of all the PLAYLIST functionality
**/

BEGIN_ACTION_BLOCKED3(addFile, System::Byte channel, u32int directoryIndex, System::String^ filename)
{
	if (channel < CHANNEL_COUNT)
	{
		try
		{
			/** WORK NEEDED: make this per client config perhaps **/
			System::String^ directory = CONFIG_GETSTRn(CONFIG_DIRECTORYLOCATION, directoryIndex);
			if (filename->IndexOf("..") == -1)
			{
				/** When adding tracks we receive the track number back **/
				Entry^ tempEntry = gcnew Track(System::String::Concat(directory, "\\", filename));

				ClientManager::getAudio()->getPlaylist(channel)->addEntry(tempEntry);
			}
			else
			{
				LogManager::write(System::String::Concat("Attempted directory traversal in addfile command: ", filename), LOG_WARNING, LOG_PLAYLIST);
			}
		}
		catch (BAPSConfigException^ cfg)
		{
			LogManager::write(System::String::Concat("Directory config error:\n", cfg->Message, "Stack Trace:\n",cfg->StackTrace), LOG_ERROR, LOG_PLAYLIST);
			Command cmd = BAPSNET_SYSTEM | BAPSNET_SENDLOGMESSAGE;
			ClientManager::broadcast( cmd, cfg->Message);
		}
	}
	else
	{
		LogManager::write(System::String::Concat("Invalid channel: ", channel.ToString(), ", in addfile command"), LOG_WARNING, LOG_PLAYLIST);
	}
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED2(addSearchItem, System::Byte channel, u32int index)
{
	if (channel < CHANNEL_COUNT)
	{
		/** Fetch the track from the musicResults.
		 *  WORK NEEDED: need a notification that client has finished with dataset so it
		 *				 can be cleared.
		**/
		Entry^ tempEntry = getLibraryTrack(index);
		if (tempEntry != nullptr)
		{
			ClientManager::getAudio()->getPlaylist(channel)->addEntry(tempEntry);
		}
		else
		{
			Command cmd = BAPSNET_SYSTEM | BAPSNET_SENDLOGMESSAGE;
			System::String^ message = System::String::Concat("Channel: ", channel.ToString(), ", addSearchItem failed: The specified index to the resultset was not valid.\n");
			ClientManager::broadcast( cmd, message);
		}
	}
	else
	{
		LogManager::write(System::String::Concat("Invalid channel: ", channel.ToString(), ", in addSearchItem command"), LOG_WARNING, LOG_PLAYLIST);
	}
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED2(deleteItem, System::Byte channel, u32int index)
{
	Command cmd;
	if (channel < CHANNEL_COUNT)
	{
		/** Take track out of playlist
		 *  WORK NEEDED: Do not delete the playing track
		**/
		if (ClientManager::getAudio()->getPlaylist(channel)->removeEntry(index))
		{
			/** notify non autoupdate clients **/
		}
		else
		{
			cmd = BAPSNET_SYSTEM | BAPSNET_SENDLOGMESSAGE;
			System::String^ message = System::String::Concat("Channel: ", channel.ToString(), ", deleteItem failed: The specified playlist index does not exist / or is in use.\n");
			ClientManager::broadcast( cmd, message);
		}
	}
	else
	{
		LogManager::write(System::String::Concat("Invalid channel: ", channel.ToString(), ", in deleteitem command"), LOG_WARNING, LOG_PLAYLIST);
	}
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED3(moveItemTo, System::Byte channel, u32int oldIndex, u32int newIndex)
{
	if (channel < CHANNEL_COUNT)
	{
		/** moveItemTo will fail only if either index does not exist **/
		if (ClientManager::getAudio()->getPlaylist(channel)->moveItemTo(oldIndex, newIndex))
		{
			/** notify non autoupdate clients **/
		}
		else
		{
			Command cmd = BAPSNET_SYSTEM | BAPSNET_SENDLOGMESSAGE;
			System::String^ message = System::String::Concat("Channel: ", channel.ToString(), ", moveItemTo failed: A specified index was not valid\n");
			ClientManager::broadcast( cmd, message);
		}
	}
	else
	{
		LogManager::write(System::String::Concat("Invalid channel: ", channel.ToString(), ", in swapItem command"), LOG_WARNING, LOG_PLAYLIST);
	}
}
END_ACTION_UNBLOCK();
BEGIN_ACTION_BLOCKED1(getPlaylist, System::Byte channel)
{
	if (channel < CHANNEL_COUNT)
	{
		/** This loop sends all the playlist entries **/
		Command cmd = BAPSNET_PLAYLIST | BAPSNET_ITEM | (channel & 0x3f);
		/** Get a playlist reference to make the code easier **/
		Playlist^ playlist = ClientManager::getAudio()->getPlaylist(channel);
		ClientManager::send(this,
							cmd,
							(u32int)playlist->getLength());
		/** The rest of these are data values **/
		cmd |= BAPSNET_PLAYLIST_MODEMASK;
		/** Iterate through the list sending each item as it goes **/
		for (int i = 0; i< playlist->getLength(); i++)
		{
			ClientManager::send(this,
								cmd,
								(u32int)playlist->getEntry(i)->getEntryNumber(),
								(u32int)playlist->getEntry(i)->getType(),
								playlist->getEntry(i)->ToString());
		}
	}
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED1(resetPlaylist, System::Byte channel)
{
	if (channel < CHANNEL_COUNT)
	{
		ClientManager::getAudio()->getPlaylist(channel)->clean();
	}
	else
	{
		LogManager::write(System::String::Concat("Invalid channel: ", channel.ToString(), ", in addfile command"), LOG_WARNING, LOG_PLAYLIST);
	}
}
END_ACTION_UNBLOCK();

BEGIN_ACTION_BLOCKED3(copyItem, System::Byte channel, u32int fromIndex, u32int toChannel)
{
	if (channel < CHANNEL_COUNT && (int)toChannel < CHANNEL_COUNT)
	{
		Entry^ e = ClientManager::getAudio()->getPlaylist(channel)->getEntry(fromIndex);
		if (e != nullptr)
		{
			ClientManager::getAudio()->getPlaylist(toChannel)->addEntry(e->Clone());
		}
		else
		{
			LogManager::write(System::String::Concat("Invalid index specified in copy item: ",fromIndex), LOG_WARNING, LOG_PLAYLIST);
		}
	}
	else
	{
		LogManager::write(System::String::Concat("Invalid channel: ", channel.ToString(), " or ", toChannel.ToString(), " in copyitem command"), LOG_WARNING, LOG_PLAYLIST);
	}
}
END_ACTION_UNBLOCK();