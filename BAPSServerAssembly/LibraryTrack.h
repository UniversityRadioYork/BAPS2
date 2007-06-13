#pragma once
#include "utility.h"
#include "LogManager.h"
#include "Track.h"

namespace BAPSServerAssembly
{
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
		LibraryTrack()
			: Track(BAPSNET_LIBRARYITEM, true)
		{
			/** Mark the LibraryEntry uninitialised **/
			initialised = 0xFFFF;
			/** make sure the fileLocation is blank **/
			fileLocation =nullptr;
		}
		
		LibraryTrack(System::Xml::XmlReader^ xr)
			: Track(BAPSNET_LIBRARYITEM, true)
		{
			xr->ReadStartElement("entry");
			xr->ReadStartElement("entrynumber");
			xr->ReadContentAsInt();
			xr->ReadEndElement();
			xr->ReadStartElement("title");
			title = xr->ReadContentAsString();
			xr->ReadEndElement();
			xr->ReadStartElement("artist");
			artist = xr->ReadContentAsString();
			xr->ReadEndElement();
			xr->ReadStartElement("recordid");
			recordID = xr->ReadContentAsInt();
			xr->ReadEndElement();
			xr->ReadStartElement("trackid");
			trackID = xr->ReadContentAsInt();
			xr->ReadEndElement();
			xr->ReadStartElement("location");
			if (xr->IsEmptyElement)
			{
				fileLocation = nullptr;
			}
			else
			{
				fileLocation = xr->ReadContentAsString();
			}
			xr->ReadEndElement();
			xr->ReadStartElement("introposition");
			introPosition = xr->ReadContentAsInt();
			xr->ReadEndElement();
			xr->ReadStartElement("cueposition");
			cuePosition = xr->ReadContentAsInt();
			xr->ReadEndElement();
			xr->ReadEndElement();
			initialised = 0;
		}
		virtual Entry^ Clone() override
		{
			LibraryTrack^ lt = gcnew LibraryTrack();
			lt->setArtist(artist);
			lt->setTitle(title);
			lt->RecordID = recordID;
			lt->TrackID = trackID;
			lt->IntroPosition = this->IntroPosition;
			lt->CuePosition = this->CuePosition;
			lt->setLocation(this->fileLocation);
			return lt;
		}
		virtual void dumpAsXML(System::Xml::XmlWriter^ xw) override
		{
			xw->WriteStartElement("entry");
			xw->WriteAttributeString("type", "librarytrack");
			xw->WriteStartElement("entrynumber");
			xw->WriteValue(getEntryNumber());
			xw->WriteEndElement();
			xw->WriteStartElement("title");
			xw->WriteString(title);
			xw->WriteEndElement();
			xw->WriteStartElement("artist");
			xw->WriteString(artist);
			xw->WriteEndElement();
			xw->WriteStartElement("recordid");
			xw->WriteValue(recordID);
			xw->WriteEndElement();
			xw->WriteStartElement("trackid");
			xw->WriteValue(trackID);
			xw->WriteEndElement();
			xw->WriteStartElement("location");
			if (fileLocation != nullptr)
			{
				xw->WriteString(fileLocation);
			}
			else
			{
				xw->WriteString("");
			}
			xw->WriteEndElement();
			xw->WriteStartElement("introposition");
			xw->WriteValue(introPosition);
			xw->WriteEndElement();
			xw->WriteStartElement("cueposition");
			xw->WriteValue(cuePosition);
			xw->WriteEndElement();
			xw->WriteEndElement();
		}
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
};