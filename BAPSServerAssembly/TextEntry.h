#pragma once
#include "Entry.h"

namespace BAPSServerAssembly
{
	/**
	 *  This class describes a text entry
	**/

	ref class TextEntry : public Entry
	{
	public:
		/** Text entries must be fully declared at construction **/
		TextEntry(System::String^ _description, System::String^ _text)
			:Entry(BAPSNET_TEXTITEM, false), description(_description), text(_text)
		{
		}
		/** Load text item from XML **/
		TextEntry(System::Xml::XmlReader^ xr)
			:Entry(BAPSNET_TEXTITEM, false)
		{
			xr->ReadStartElement("entry");
			xr->ReadStartElement("entrynumber");
			xr->ReadContentAsInt();
			xr->ReadEndElement();
			xr->ReadStartElement("description");
			description = xr->ReadContentAsString();
			xr->ReadEndElement();
			xr->ReadStartElement("textdata");
			text = xr->ReadContentAsString();
			xr->ReadEndElement();
			xr->ReadEndElement();
		}
		~TextEntry(){};
		virtual Entry^ Clone() override
		{
			return gcnew TextEntry(description, text);
		}
		virtual void dumpAsXML(System::Xml::XmlWriter^ xw) override
		{
			xw->WriteStartElement("entry");
			xw->WriteAttributeString("type", "text");
			xw->WriteStartElement("entrynumber");
			xw->WriteValue(getEntryNumber());
			xw->WriteEndElement();
			xw->WriteStartElement("description");
			xw->WriteString(description);
			xw->WriteEndElement();
			xw->WriteStartElement("textdata");
			xw->WriteString(text);
			xw->WriteEndElement();
			xw->WriteEndElement();
		}
		/** The description is the title and artist strings **/
		virtual System::String^ ToString() override
		{
			return description;
		}
		System::String^ getText()
		{
			return text;
		}
		System::String^ getDescription()
		{
			return description;
		}

	private:
		/** The item's description **/
		System::String^ description;
		/** The item's text **/
		System::String^ text;
	};
};