#include "stdafx.h"
#include "Playlist.h"
#include "ClientManager.h"
#include "LibraryTrack.h"

using namespace BAPSServerAssembly;

/**
 *  This file contains the Playlist class which stores tracks in a specific sequence ready
 *  To be played
**/
#define MINIMUM_LENGTH 10

Playlist::Playlist(int _channel)
: channel(_channel)
{
	/** We specify that a list should at least be 10 items long **/
	maxEntries = MINIMUM_LENGTH;
	/** Seemingly odd notation, this is an array of Track* **/
	entries = gcnew array<Entry^>(maxEntries);
	/** There is no text loaded to start **/
	loadedTextEntry = nullptr;
}

Playlist::~Playlist()
{
	/** Tidy up, just because its good practice **/
	delete [] entries;
}

void Playlist::addEntry(Entry^ entry)
{
	/** The array is kind of an 'autogrow' array
	 *  It doubles in size when it runs out of room
	**/
	if (nextEntry == maxEntries)
	{	
		/** Double the array size **/
		maxEntries *=2;
		/** Do not statically create the array as it is to be passed out **/
		array<Entry^>^ tempEntries;
		/** Grab the new array **/
		tempEntries = gcnew array<Entry^>(maxEntries);
		/** Copy the old array into the new one **/
		for (int i = 0 ; i < nextEntry ; i++)
		{
            tempEntries[i] = entries[i];
		}
		/** Delete the old because its good practice **/
		delete [] entries;
		/** Swap the arrays over **/
		entries = tempEntries;
	}
	/** Put the new item at the next position in the array **/
	entries[nextEntry] = entry;
	/** Tell the new item what position it is in **/
	entries[nextEntry]->setEntryNumber(nextEntry);
	/** Move to next entry point **/
	nextEntry++;
	/** Tell all clients what has happened **/
	Command cmd = BAPSNET_PLAYLIST | BAPSNET_ITEM | BAPSNET_PLAYLIST_MODEMASK | channel;
	ClientManager::broadcast( cmd, entry->getEntryNumber(), entry->getType(), entry->ToString());
}

bool Playlist::removeEntry(int entryNumber)
{
	/** Ensure a valid entry is being deleted **/
	if (entryNumber > nextEntry-1)
	{
		return false;
	}
	if (loadedTextEntry != nullptr && loadedTextEntry->getEntryNumber() == entryNumber)
	{
		loadedTextEntry = nullptr;
	}
	Entry^ removedEntry = entries[entryNumber];
	if (removedEntry == ClientManager::getAudio()->getOutput(channel)->getLoadedTrack() &&
		ClientManager::getAudio()->getOutput(channel)->isPlaying())
	{
		return false;
	}
	/** Notify there is one less item **/
	nextEntry--;
	/** Bubble the deleted item out of the list maintaining ordering **/
	while (entryNumber < nextEntry)
	{
		/** Move the entry up the list **/
		entries[entryNumber] = entries[entryNumber+1];
		/** Tell it where it moved to **/
		entries[entryNumber]->setEntryNumber(entryNumber);
		entryNumber++;
	}
	/** If the list is more than 3/4 empty, half the list size **/
	if ((maxEntries - nextEntry) > ((maxEntries * 3) /4))
	{
		/** Notify the list it is half the size **/
		maxEntries = (maxEntries/2 > MINIMUM_LENGTH)?maxEntries/2:MINIMUM_LENGTH; 

		/** Do not statically allocate the array **/
		array<Entry^>^ tempEntries;
		tempEntries = gcnew array<Entry^>(maxEntries);
		/** Copy the relevant number of items accross **/
		for (int i = 0 ; i < nextEntry ; i++)
		{
            tempEntries[i] = entries[i];
		}
		/** Delete the old array **/
		delete [] entries;
		/** Swap in the new array **/
		entries = tempEntries;
	}
	/** Notify on success this way clients cannot become out of sync
		*  by assuming things succeed
	**/
	Command cmd = BAPSNET_PLAYLIST | BAPSNET_DELETEITEM | channel;
	ClientManager::broadcast( cmd, (u32int)removedEntry->getEntryNumber());
	/** If the current loaded track is deleted,
	    let the client know there is no loaded track	**/
	if (removedEntry==ClientManager::getAudio()->getOutput(channel)->getLoadedTrack())
	{
		ClientManager::getAudio()->getOutput(channel)->resetChannel(false);
	}

	/** Success **/
	return true;
}

int Playlist::getLength()
{
	/** The next entry marker is always at the next position to insert at
	 *  As this is a zero based array it is therefore the number of items
	 *  in the list
	**/
	return nextEntry;
}

int Playlist::getNextPlayable(int currentIndex)
{
	/** Find the next playable entry or return -1 if there are no more
	 *  playable entries
	**/
	if (currentIndex >= nextEntry)
	{
		return -1;
	}
	int i;
	for (i = currentIndex ; i < nextEntry ; i++)
	{
		if (entries[i]->isPlayable())
		{
			return i;
		}
	}
	return -1;
}

bool Playlist::moveItemTo(int oldIndex, int newIndex)
{
	/** Both indices must be valid point in the list **/
	/** oldIndex==newIndex falls through doing nothing **/
	if ((oldIndex >= 0 && oldIndex < nextEntry) &&
		(newIndex >= 0 && newIndex < nextEntry) )
	{
		Entry^ tempEntry = entries[oldIndex];
		if (oldIndex > newIndex)
		{
			/** Bubble the entries up from oldIndex+1 down to newIndex **/
			for (int i = oldIndex; i > newIndex ; i--) 
			{
				entries[i] = entries[i-1];
				entries[i]->setEntryNumber(i);
			}
			/** Put the Entry where it wanted to be **/
			entries[newIndex] = tempEntry;
			entries[newIndex]->setEntryNumber(newIndex);
		}
		else if (newIndex > oldIndex)
		{
			/** Bubble the entries down from the oldIndex up to newIndex **/
			for (int i = oldIndex; i < newIndex ; i++)
			{
				entries[i] = entries[i+1];
				entries[i]->setEntryNumber(i);
			}
			/** Put the Entry where it wanted to be **/
			entries[newIndex] = tempEntry;
			entries[newIndex]->setEntryNumber(newIndex);
		}
		/** Notify on success this way clients cannot become out of sync
			*  by assuming things succeed
		**/
		if (oldIndex != newIndex)
		{
			Command cmd = BAPSNET_PLAYLIST | BAPSNET_MOVEITEMTO | channel;
			ClientManager::broadcast( cmd, oldIndex, newIndex);
		}
		return true;
	}
	else
	{
		/** Could not move tracks **/
		return false;
	}
	
}

Entry^ Playlist::getEntry(int entryNumber)
{
	/** If it's a valid entry **/
	if (entryNumber >= 0 && entryNumber < nextEntry)
	{
		/** Return selected entry **/
		return entries[entryNumber];
	}
	else
	{
		/** Otherwise return zero
		 *  WORK NEEDED: consider exception mechanism
		**/
		return nullptr;
	}
}

void Playlist::clean(int newLength)
{
	nextEntry = 0;
	loadedTextEntry = nullptr;
	/** If the list is more than twice the default size **/
	if ( (newLength > 0) || (maxEntries > (2*MINIMUM_LENGTH)))
	{
		maxEntries = (newLength > 0)?newLength:MINIMUM_LENGTH;
		/** Delete the old array **/
		delete [] entries;
		/** Create the new array **/
		entries = gcnew array<Entry^>(maxEntries);
	}
	/** Tell all clients what has happened **/
	Command cmd = BAPSNET_PLAYLIST | BAPSNET_RESETPLAYLIST | channel;
	ClientManager::broadcast( cmd );
	if (ClientManager::getAudio()->getOutput(channel)->isPlaying())
	{
		Track^ t = ClientManager::getAudio()->getOutput(channel)->getLoadedTrack();
		addEntry(t);
		/** Fill the client in with details of the (still) loaded track **/
		cmd = BAPSNET_PLAYBACK | BAPSNET_LOAD | (channel & 0x3f);
		ClientManager::broadcast( cmd,
								(u32int)t->getEntryNumber(),
								(u32int)t->getType(),
								t->ToString(),
								ClientManager::getAudio()->getOutput(channel)->getFileDuration());
		Command cmd = BAPSNET_PLAYBACK | BAPSNET_POSITION | (channel & 0x3f);
		ClientManager::broadcast( cmd, (u32int)ClientManager::getAudio()->getOutput(channel)->getFilePosition());
		ClientManager::broadcast(BAPSNET_PLAYBACK | BAPSNET_CUEPOSITION | (channel & 0x3f),
								 (u32int)t->CuePosition);

		ClientManager::broadcast(BAPSNET_PLAYBACK | BAPSNET_INTROPOSITION | (channel & 0x3f),
							 (u32int)t->IntroPosition);
	}
	else
	{
		ClientManager::getAudio()->getOutput(channel)->resetChannel(true);
	}
}


void Playlist::dumpAsXML(System::Xml::XmlWriter^ xw)
{
	xw->WriteStartElement("playlist");
	int i;
	for (i = 0 ; i < nextEntry ; i++)
	{
		entries[i]->dumpAsXML(xw);
	}
	xw->WriteEndElement();
}

void Playlist::restoreFromXML(System::Xml::XmlReader^ xr)
{
	clean(0);
	xr->ReadStartElement("playlist");
	int i;
	for (i = 0 ; xr->IsStartElement() ; i++)
	{
		System::String^ type = xr->GetAttribute("type");
		if (type->Equals("text"))
		{
			addEntry(gcnew TextEntry(xr));
		}
		else if (type->Equals("librarytrack"))
		{
			addEntry(gcnew LibraryTrack(xr));
		}
		else if (type->Equals("track"))
		{
			addEntry(gcnew Track(xr));
		}
		else
		{
			/** ignore entry **/
			xr->ReadSubtree();
		}
	}
	xr->ReadEndElement();
}