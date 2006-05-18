#pragma once

#include "Entry.h"


/**
 *  This class describes a text entry
**/

ref class TextEntry : public Entry
{
public:
	/** Fixed files must be fully declared at construction **/
	TextEntry(System::String^ _description, System::String^ _text)
		:Entry(BAPSNET_TEXTITEM, false), description(_description), text(_text)
	{
	}
	~TextEntry(){};
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
