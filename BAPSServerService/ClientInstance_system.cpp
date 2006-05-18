#include "stdafx.h"
#include "ClientInstance.h"
#include "Exceptions.h"
#include "TextEntry.h"

/**
 *  This file contains the implementations of all the SYSTEM functionality
**/

BEGIN_ACTION_BLOCKED0(synchronize)
{
	/** Message block prevents synchronously updated states from being updated at the same time
	 *  That is anything other than file position. This means we have guaranteed state inside a
	 *  MESSAGE_BLOCK
	**/

	Command cmd;
	/** Loop round the channels and update the client with the details **/
	for (int channel = 0; channel < CHANNEL_COUNT ; channel++)
	{
		/** This loop sends all the playlist entries **/
		cmd = BAPSNET_PLAYLIST | BAPSNET_ITEM | BAPSNET_PLAYLIST_MODEMASK | (channel & 0x3f);
		/** Get a playlist reference to make the code easier **/
		Playlist^ playlist = ClientManager::getAudio()->getPlaylist(channel);
		/** Iterate through the list sending each item as it goes **/
		for (int i = 0; i< playlist->getLength(); i++)
		{
			ClientManager::send(this,
								cmd,
								(u32int)i,
								(u32int)playlist->getEntry(i)->getType(),
								playlist->getEntry(i)->ToString());
		}
		/** Common option for this section is just the channel number **/
		cmd = (channel & 0x3f);
		if (ClientManager::getAudio()->getPlaylist(channel)->getLoadedTextEntry() != nullptr)
		{
			TextEntry^ te = ClientManager::getAudio()->getPlaylist(channel)->getLoadedTextEntry();
			/** Fill the client in with details of the loaded track **/
			ClientManager::send(this, 
								cmd | BAPSNET_PLAYBACK | BAPSNET_LOAD,
								(u32int)te->getPosition(),
								(u32int)te->getType(),
								te->getDescription(),
								te->getText());
		}
		/** Determine if there is a track loaded in the Output
		 *  WORK NEEDED: Make the ChannelStatus 'better' ie isChannelLoaded()
		**/
		if (ClientManager::getAudio()->getOutput(channel)->isLoaded())
		{
			/** Send the index of the playlist that the loaded track corresponds to **/
			ClientManager::send(this,
							    cmd | BAPSNET_PLAYBACK | BAPSNET_LOAD,
			                    (u32int)ClientManager::getAudio()->getOutput(channel)->getLoadedTrack()->getPosition(),
				                (u32int)ClientManager::getAudio()->getOutput(channel)->getLoadedTrack()->getType(),
					            ClientManager::getAudio()->getOutput(channel)->getLoadedTrack()->ToString(),
								ClientManager::getAudio()->getOutput(channel)->getFileDuration());

			ClientManager::send(this, cmd | BAPSNET_PLAYBACK | BAPSNET_CUEPOSITION,
								(u32int)ClientManager::getAudio()->getOutput(channel)->getLoadedTrack()->CuePosition);
			ClientManager::send(this, cmd | BAPSNET_PLAYBACK | BAPSNET_INTROPOSITION,
								(u32int)ClientManager::getAudio()->getOutput(channel)->getLoadedTrack()->IntroPosition);

			if (ClientManager::getAudio()->getOutput(channel)->isPlaying())
			{
				ClientManager::send(this, cmd | BAPSNET_PLAYBACK | BAPSNET_PLAY);
			}
			else if (ClientManager::getAudio()->getOutput(channel)->isPaused())
			{
				ClientManager::send(this, cmd | BAPSNET_PLAYBACK | BAPSNET_PAUSE);
			}
			else
			{
				ClientManager::send(this, cmd | BAPSNET_PLAYBACK | BAPSNET_STOP);
			}
		}
		else
		{
			ClientManager::send(this, cmd | BAPSNET_PLAYBACK | BAPSNET_STOP);
		}
		/** Finally send the volume setting for this channel **/
		ClientManager::send(this,
							cmd | BAPSNET_PLAYBACK | BAPSNET_VOLUME,
							ClientManager::getAudio()->getOutput(channel)->getChannelVolume());
	}
	/** Channel specific data has now been sent **/
	/** Now send all of the read/read-write config options **/

	/** Only list options which are editable by anyone **/
	int count = 0;
	int i;
	for ( i = 0 ; i < CONFIG_LASTOPTION ; i++ )
	{
		if (CONFIG_ACCESS_RIGHTS(i) != CA_SU_ONLY)
		{
			count++;
		}
	}

	/** Send the number of options about to be sent **/
	cmd = (Command)(BAPSNET_CONFIG | BAPSNET_OPTION | count);
	ClientManager::send(this, cmd, (u32int)count);

	/** Loop through the options sending each one **/
	for ( i = 0 ; i < CONFIG_LASTOPTION ; i++ )
	{
		if (CONFIG_ACCESS_RIGHTS(i) != CA_SU_ONLY)
		{
			sendOption(i);
		}
	}
	/** Loop through the options sending option choices if applicable for each one **/
	for ( i = 0 ; i < CONFIG_LASTOPTION ; i++ )
	{
		if (CONFIG_ACCESS_RIGHTS(i) != CA_SU_ONLY && CONFIG_TYPE(i) == CONFIG_TYPE_CHOICE)
		{
			sendAllOptionChoices(i);
		}
	}

	count = 0;
	for ( i = 0 ; i < CONFIG_LASTOPTION ; i++ )
	{
		/** For non indexed options this will be just +1 **/
		/** For indexed options this is +[value of controlling option] **/
		if (CONFIG_ACCESS_RIGHTS(i) != CA_SU_ONLY)
		{
			count += CONFIG_COUNTINDICES(i);
		}
	}
	/** Send setting count to client **/
	cmd = (Command)(BAPSNET_CONFIG | BAPSNET_CONFIGSETTING);
	ClientManager::send(this, cmd, (u32int)count);
	/** Loop through all the options and indices sending each setting **/
	for ( i = 0 ; i < CONFIG_LASTOPTION ; i++ )
	{
		if (CONFIG_ACCESS_RIGHTS(i) != CA_SU_ONLY)
		{
			sendOptionConfigSettings(i, false, this);
		}
	}

	/** Turn autoupdate on for this channel now so that as soon as the BLOCK is removed whatever
	 *  is waiting will be able to send to this client. This is necessary to guarantee sync
	**/
	autoUpdate = true;
}
END_ACTION_UNBLOCK();

void ClientInstance::refreshDir(unsigned char directoryNumber)
{
	System::String^ directoryName = "";
	try
	{
		directoryName = CONFIG_GETSTRn(CONFIG_DIRECTORYLOCATION, directoryNumber);
		array<System::String^>^ files = System::IO::Directory::GetFiles(directoryName);
		array<System::String^>^ audioFiles = gcnew array<System::String^>(files->Length);
		int i = 0;
		int audioCount = 0;
		for ( i = 0 ; i < files->Length ; i++)
		{
			if (files[i]->EndsWith(".wav") ||
				files[i]->EndsWith(".mp3") ||
				files[i]->EndsWith(".wma"))
			{
				audioFiles[audioCount] = files[i];
				audioCount++;
			}	
		}

		Command cmd = BAPSNET_SYSTEM | BAPSNET_FILENAME | (directoryNumber & BAPSNET_SYSTEM_VALUEMASK);
		ClientManager::send(this, cmd, (u32int)audioCount );

		cmd = BAPSNET_SYSTEM | BAPSNET_FILENAME | BAPSNET_SYSTEM_MODEMASK | (directoryNumber & BAPSNET_SYSTEM_VALUEMASK);

		for ( i = 0 ; i < audioCount ; i++)
		{
			System::IO::FileInfo ^finfo = gcnew System::IO::FileInfo(audioFiles[i]);
			ClientManager::send(this, cmd, (u32int)i, finfo->Name->ToString());
		}
	}
	catch (BAPSConfigException^ cfg)
	{
		LogManager::write(System::String::Concat("Directory config error:\n", cfg->Message, "Stack Trace:\n",cfg->StackTrace), LOG_ERROR, LOG_PLAYLIST);
		Command cmd = BAPSNET_SYSTEM | BAPSNET_SENDLOGMESSAGE;
		ClientManager::send(this, cmd, cfg->Message);
	}
	catch (System::UnauthorizedAccessException^ e)
	{
		LogManager::write(System::String::Concat("Error in RefreshDir:\n",e->Message, "Stack Trace:\n",e->StackTrace), LOG_ERROR, LOG_OTHER);
		Command cmd = BAPSNET_SYSTEM | BAPSNET_SENDLOGMESSAGE;
		ClientManager::send(this, cmd, System::String::Concat("Please check configuration: Directory ", directoryNumber.ToString(), " - '", directoryName, "', is not accessible\n"));
	}
	catch (System::ArgumentException^ e)
	{
		LogManager::write(System::String::Concat("Error in RefreshDir:\n",e->Message, "Stack Trace:\n",e->StackTrace), LOG_ERROR, LOG_OTHER);
		Command cmd = BAPSNET_SYSTEM | BAPSNET_SENDLOGMESSAGE;
		ClientManager::send(this, cmd, System::String::Concat("Please check configuration: Directory ", directoryNumber.ToString(), " - '", directoryName, "', is invalid\n"));
	}
	catch (System::IO::PathTooLongException^ e)
	{
		LogManager::write(System::String::Concat("Error in RefreshDir:\n",e->Message, "Stack Trace:\n",e->StackTrace), LOG_ERROR, LOG_OTHER);
		Command cmd = BAPSNET_SYSTEM | BAPSNET_SENDLOGMESSAGE;
		ClientManager::send(this, cmd, System::String::Concat("Please check configuration: Directory ", directoryNumber.ToString(), " - '...', is too long to be accessed (check server log)\n"));
	}
	catch (System::IO::DirectoryNotFoundException^ e)
	{
		LogManager::write(System::String::Concat("Error in RefreshDir:\n",e->Message, "Stack Trace:\n",e->StackTrace), LOG_ERROR, LOG_OTHER);
		Command cmd = BAPSNET_SYSTEM | BAPSNET_SENDLOGMESSAGE;
		ClientManager::send(this, cmd, System::String::Concat("Please check configuration: Directory ", directoryNumber.ToString(), " - '", directoryName, "', does not exist\n"));
	}
	catch (System::IO::IOException^ e)
	{
		LogManager::write(System::String::Concat("Error in RefreshDir:\n",e->Message, "Stack Trace:\n",e->StackTrace), LOG_ERROR, LOG_OTHER);
		Command cmd = BAPSNET_SYSTEM | BAPSNET_SENDLOGMESSAGE;
		ClientManager::send(this, cmd, System::String::Concat("Please check configuration: Directory ", directoryNumber.ToString(), " - '", directoryName, "', is not a directory\n"));
	}
}

void ClientInstance::synchronizeChatters()
{
	ClientManager::getClientLock();
	try
	{
		ClientInstance^ ci = ClientManager::getFirstClient();
		System::Collections::Hashtable^ users = gcnew System::Collections::Hashtable();
		/** Add the user **/
		Command cmd = BAPSNET_SYSTEM | BAPSNET_CLIENTCHANGE | 1;

		while (ci != nullptr)
		{
			System::String^ currentUsername = ci->getUsername();
			if (ci->isChatting() && users[currentUsername] == nullptr)
			{
				users[currentUsername] = safe_cast<System::Object^>(0);
				ClientManager::send(this,cmd, currentUsername);
			}
			ci = ci->nextClient;
		}
		receiveChat = true;
	}
	finally
	{
		ClientManager::releaseClientLock();
	}
}