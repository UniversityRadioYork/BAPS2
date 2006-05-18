#pragma once

#include "decodeStructs.h"

/**
 * This is the abstract base class for all playlist entries
 * An entry may or may not be playable
 * It will always be able to describe itself using the ToString call
**/

ref class Entry abstract
{
public:
	/** On construction a type is defined as well as if the Entry will be playable **/
	Entry(int _type, bool _playable)
		:type(_type), playable(_playable){};
	/** Force ToString to be overloaded **/
	virtual System::String^ ToString() override abstract;
	virtual ~Entry() {};
	inline int getPosition()
	{
		return position;
	}
	inline void setPosition(int _position)
	{
		position = _position;
	}
	inline bool isPlayable()
	{
		return playable;
	}
	inline int getType()
	{
		return type;
	}
private:
	/** Is the Entry playable **/
	bool playable;
	/** Where the entry is in its current playlist **/
	int position;
	/** What the Entries exact type is **/
	int type;
};