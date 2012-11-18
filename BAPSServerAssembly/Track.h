#pragma once
#include "Entry.h"

namespace BAPSServerAssembly
{
	/**
	 *  This class describes a fixed file entry
	**/

	ref class Track : public Entry
	{
	public:
		/** Fixed files must be fully declared at construction **/
		Track(System::String^ _filelocation)
			:Entry(BAPSNET_FILEITEM, true)
		{
			fileLocation = _filelocation;
			introPosition = 0;
			cuePosition = 0;
		}
		/** Load track data from XML **/
		Track(System::Xml::XmlReader^ xr)
			:Entry(BAPSNET_FILEITEM, true)
		{
			xr->ReadStartElement("entry");
			xr->ReadStartElement("entrynumber");
			xr->ReadContentAsInt();
			xr->ReadEndElement();
			xr->ReadStartElement("filename");
			fileLocation = xr->ReadContentAsString();
			xr->ReadEndElement();
			xr->ReadStartElement("introposition");
			introPosition = xr->ReadContentAsInt();
			xr->ReadEndElement();
			xr->ReadStartElement("cueposition");
			cuePosition = xr->ReadContentAsInt();
			xr->ReadEndElement();
			xr->ReadEndElement();
		}
		~Track(){};
		virtual Entry^ Clone() override
		{
			return gcnew Track(fileLocation);
		}
		
		virtual void dumpAsXML(System::Xml::XmlWriter^ xw) override
		{
			xw->WriteStartElement("entry");
			xw->WriteAttributeString("type", "track");
			xw->WriteStartElement("entrynumber");
			xw->WriteValue(getEntryNumber());
			xw->WriteEndElement();
			xw->WriteStartElement("filename");
			xw->WriteString(fileLocation);
			xw->WriteEndElement();
			xw->WriteStartElement("introposition");
			xw->WriteValue(introPosition);
			xw->WriteEndElement();
			xw->WriteStartElement("cueposition");
			xw->WriteValue(cuePosition);
			xw->WriteEndElement();
			xw->WriteEndElement();
		}
		/** The description is the filename (without path) **/
		virtual System::String^ ToString() override
		{
			int helperInt = fileLocation->LastIndexOf("\\");
			System::String^ filename;
			if (helperInt != -1 && helperInt != fileLocation->Length-1)
			{
				filename = fileLocation->Substring(helperInt+1);
			}
			else
			{
				filename = fileLocation;
			}
			helperInt = filename->LastIndexOf(".");
			if (helperInt > 0)
			{
				return filename->Substring(0,helperInt);
			}
			else
			{
				return filename;
			}
		}
		/** File location is simply the fixed location given at construction **/
		virtual System::String^ getFileLocation()
		{
			return fileLocation;
		}
		property int IntroPosition
		{
			int get()
			{
				return introPosition;
			}
			void set(int value)
			{
				introPosition = value;
			}
		}
		property int CuePosition
		{
			int get()
			{
				return cuePosition;
			}
			void set(int value)
			{
				cuePosition = value;
			}
		}
	protected:
		Track(int _type, bool _playable)
			:Entry(_type, _playable)
		{}
		/** The intro position **/
		int introPosition;
		/** The cue position **/
		int cuePosition;
		/** The track's fixed location **/
		System::String^ fileLocation;
	};
};