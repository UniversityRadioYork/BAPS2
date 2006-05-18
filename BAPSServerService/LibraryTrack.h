#pragma once

#include "utility.h"
#include "LogManager.h"
#include "Track.h"

/**
 *  This class describes a Music Library Track entry
**/
ref class LibraryTrack : public Track
{
public:
	/** 
	 *  Library Tracks are permitted to be lazily filled in as the information
	 *  is retrieved serially from the database
	**/
	LibraryTrack():Track(BAPSNET_LIBRARYITEM, true)
	{
		/** Mark the LibraryEntry uninitialised **/
		initialised = 0xFFFF;
		/** make sure the fileLocation is blank **/
		fileLocation =nullptr;
	};
	virtual System::String^ ToString() override
	{
		/** Check if the track is initialised and error if it is not **/
		if (initialised == 0x0)
		{
			return System::String::Concat(title, " - ", artist);
		}
		else
		{
			LogManager::write("Un-initialised Library Track, ToString cannot be executed", LOG_ERROR, LOG_OBJECTS);
			return "PROGRAM ERROR: ToString on un-initialized library track";
		}
	}
	virtual System::String^ getFileLocation() override
	{
		/** Check that the track is initialised and error if not **/
		if (initialised == 0x0)
		{
			if (fileLocation != nullptr)
			{
				return fileLocation;
			}
			else
			{
				System::String^ musicLocation = CONFIG_GETSTR(CONFIG_LIBRARYLOCATION);
				return System::String::Concat(musicLocation, "\\", recordID, "\\", trackID, ".mp3");
			}
		}
		else
		{
			LogManager::write("Un-initialised Library Track, getFileLocation cannot be executed", LOG_ERROR, LOG_OBJECTS);
			return "PROGRAM ERROR: getFileLocation on un-initialized library track";
		}
	}
	/** 
	 *  Accessors to maintain the state of the class
	 *  When all the fields are filled in initialised will be 0x0
	**/
	property int RecordID
	{
		void set(int _recordID)
		{
			initialised &= 0x0FFF;
			recordID = _recordID;
		}
		int get()
		{
			return recordID;
		}
	}
	property int TrackID
	{
		void set(int _trackID)
		{
			initialised &= 0xF0FF;
			trackID = _trackID;
		}
		int get()
		{
			return trackID;
		}
	}
	void setTitle(System::String^ _title)
	{
		initialised &= 0xFF0F;
		title = _title;
	}
	void setArtist(System::String^ _artist)
	{
		initialised &= 0xFFF0;
		artist = _artist;
	}
	void setLocation(System::String^ _location)
	{
		fileLocation = _location;
	}

private:
	/** Status value: 0x0 when initialised **/
	int initialised;
	/** Various track information **/
	int recordID;
	int trackID;
	/** The track's title **/
	System::String^ title;
	/** The track's artist **/
	System::String^ artist;
};
