#pragma once

#include "Entry.h"


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
	~Track(){};
	/** The description is the title and artist strings **/
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
	/** File location is simple the fixed location given at construction **/
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