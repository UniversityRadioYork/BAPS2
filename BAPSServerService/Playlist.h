#pragma once

#include "Entry.h"
#include "TextEntry.h"

#define FIELD_SEPARATOR '#'

ref class Playlist
{
public:
	/** Pass in the channel associated with this list**/
	Playlist(int _channel);
	/** Just clear up the array **/
	~Playlist();
	/** Add a entry to the end of the list **/
	void addEntry(Entry^ entry);
	/** Remove an entry from the specified index **/
	bool removeEntry(int entryNumber);
	/** How long the list currently is **/
	int  getLength();
	/** Bubble the selected index up one position **/
	bool moveItemTo(int oldIndex, int newIndex);
	/** Get the entry from the specified index **/
	Entry^ getEntry(int entryNumber);
	/** Get the loaded text entry **/
	TextEntry^ getLoadedTextEntry()
	{
		return loadedTextEntry;
	}
	/** Set the loaded text entry **/
	void setLoadedTextEntry(int entryNumber)
	{
		/** Ensure a valid entry is being deleted **/
		if (entryNumber > nextEntry-1)
		{
			return;
		}
		loadedTextEntry = safe_cast<TextEntry^>(entries[entryNumber]);
	}
	/** Get the next playable entry given a starting index **/
	int getNextPlayable(int currentIndex);
	/** Delete all entries in this playlist **/
	void clean()
	{
		clean(0);
	}
	void clean(int newLength);
private:
	/** The position to insert at next **/
	int nextEntry;
	/** The size of the current array **/
	int maxEntries;
	/** The current array of tracks **/
	array<Entry^>^ entries;
	/** The channel number associated with this playlist **/
	int channel;
	/** The index of the loaded text item **/
	TextEntry^ loadedTextEntry;
};