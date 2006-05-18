#include "stdafx.h"
#include "BAPSPresenterMain.h"

using namespace BAPSPresenter;

void BAPSPresenterMain::addItem(System::Object^ _channel, System::Object^ _index, System::Object^ _type, System::String^ description)
{
	int channel = safe_cast<int>(_channel);
	int index = safe_cast<int>(_index);
	int type = safe_cast<int>(_type);
	if (channel < 3)
	{
		/** Add an item to the end of the list ( only method currently supported by server ) **/
		trackList[channel]->addTrack(type, description);
		refreshAudioWall();
	}
}

void BAPSPresenterMain::moveItemTo(System::Object^ _channel, System::Object^ _oldIndex, System::Object^ _newIndex)
{	
	int channel = safe_cast<int>(_channel);
	int oldIndex = safe_cast<int>(_oldIndex);
	int newIndex = safe_cast<int>(_newIndex);
	if (channel < 3)
	{
		trackList[channel]->moveTrack(oldIndex, newIndex);
		refreshAudioWall();
	}

}

void BAPSPresenterMain::deleteItem(System::Object^ _channel, System::Object^ _index)
{
	int channel = safe_cast<int>(_channel);
	int index = safe_cast<int>(_index);
	if (channel < 3)
	{
		trackList[channel]->removeTrack(index);
		refreshAudioWall();
	}
}

void BAPSPresenterMain::cleanPlaylist(System::Object^ _channel)
{	
	int channel = safe_cast<int>(_channel);
	if (channel < 3)
	{
		/** Empty the track list **/
		trackList[channel]->clearTrackList();
		refreshAudioWall();
	}
}