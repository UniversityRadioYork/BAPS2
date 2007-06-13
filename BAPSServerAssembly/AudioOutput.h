#pragma once

#include "Playlist.h"
#include "BAPS.h"
#include "utility.h"
#include "Track.h"

/**
 *  This file contains the BAPS library interface abstraction
**/

/** The various status possibilities **/
#define CHANNEL_NOT_LOADED 0
#define CHANNEL_STOPPED 1
#define CHANNEL_PLAYING 2
#define CHANNEL_PAUSED 3
#define CHANNEL_INVALID 4

#define CHANNEL_COUNT ConfigManager::getChannelCount()
namespace BAPSServerAssembly
{
	ref class AudioOutput
	{
		public:
			AudioOutput(CBAPSAudioOutput *m_AudioOutput);
			~AudioOutput();

			/** Play loaded track **/
			bool play(); 
			/** Pause loaded track **/
			bool pause(); 
			/** Stop loaded track **/
			bool stop();
			/** Load new entry **/
			bool loadTrack(Track^ entry);
			/** The currently loaded track is maintained **/
			inline Track^ getLoadedTrack()
			{
				return loadedTrack;
			}

			/** Make the channel look as though it were newly created **/
			void resetChannel(bool setDefaultConfig);

			/** Read only accessors **/
			inline unsigned int getFileDuration()
			{
				if (isLoaded() && isPlayable())
				{
					return pChannel->GetDuration();
				}
				else
				{
					return 0;
				}
			}
			inline bool isValid()
			{
				return channelStatus != CHANNEL_INVALID;
			}
			inline bool isLoaded()
			{
				return isValid() && channelStatus != CHANNEL_NOT_LOADED;
			}
			inline bool isPlayable()
			{
				return getLoadedTrack()->isPlayable();
			}

			inline bool isPaused()
			{
				return channelStatus == CHANNEL_PAUSED;
			}

			inline bool isPlaying()
			{
				return channelStatus == CHANNEL_PLAYING;
			}

			/** Read/Write accessors **/
			inline unsigned int getFilePosition()
			{
				if (isLoaded() && isPlayable())
				{
					return pChannel->GetPosition();
				}
				else
				{
					return 0;
				}
			}

			void setFilePosition(unsigned int position);

			inline float getChannelVolume()
			{
				if (isValid())
				{
					return pChannel->GetVolume();
				}
				else
				{
					return 0.0;
				}
			}

			void setChannelVolume(float volume);
			void dumpAsXML(System::Xml::XmlWriter^ xw);
			void restoreFromXML(System::Xml::XmlReader^ xr);
		private:
			/** Channel counter to guarantee the same channel is not reallocated **/
			static int channelCount = 0;
			/** Channel number of this channel **/
			int channelNumber;
			/** The track loaded on this channel **/
			Track^ loadedTrack;
			/** The dummy track for when the channel is empty **/
			Track^ notLoadedTrack;
			/** The device to play on **/
			CBAPSAudioOutputChannel *pChannel;
			/** A handle to the BAPS library **/
			CBAPSAudioOutput *audioOutput;
			/** Maintain state of channel so it is easy to query **/
			unsigned int channelStatus;

			/** Private write accessors **/
			inline void setPlaying()
			{
				if (isValid())
				{
					channelStatus = CHANNEL_PLAYING;
				}
			}
			inline void setPaused()
			{
				if (isValid())
				{
					channelStatus = CHANNEL_PAUSED;
				}
			}
			inline void setStopped()
			{
				if (isValid())
				{
					channelStatus = CHANNEL_STOPPED;
				}
			}
			inline void setNotLoaded()
			{
				if (isValid())
				{
					channelStatus = CHANNEL_NOT_LOADED;
					loadedTrack = notLoadedTrack;
				}
			}
	};
};