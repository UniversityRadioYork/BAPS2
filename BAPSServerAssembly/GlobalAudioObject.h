#pragma once

#include "AudioOutput.h"
#include "ConfigManager.h"

namespace BAPSServerAssembly
{
	/**
	 *  GlobalAudioObject manages the output channels and related playlist information
	 *  This is essentially global data
	**/
	ref struct sChannel
	{
		AudioOutput^ audioOutput;
		Playlist ^currentPlaylist;
	};
		
	ref class GlobalAudioObject
	{
	public:
		GlobalAudioObject();
		~GlobalAudioObject();
		/** Inline these so they get compiled out, they guard against accidental modification **/
		inline AudioOutput^ getOutput(int channel)
		{
			if (channel < CHANNEL_COUNT)
			{
				/** Get the Output from the channel struct **/
				return activeChannels[channel]->audioOutput;
			}
			else
			{
				/** We should never hit this case as caller should guard against OOB channel **/
				return nullptr;
			}
		}
		inline Playlist^ getPlaylist(int channel)
		{
			if (channel < CHANNEL_COUNT)
			{
				/** Get the Playlist from the channel struct **/
				return activeChannels[channel]->currentPlaylist;
			}
			else
			{
				/** We should never hit this case as caller should guard against OOB channel **/
				return nullptr;
			}
		}
		void notifyDelegate(int _channel)
		{
			_channel++;
		}

		/** Managed equivalent to the callback above **/
		static void notifyCallback(int channel);

		/** Dump the system state **/
		void dumpAsXML(System::Xml::XmlWriter^ xw);
		/** Restore system state from XML **/
		void restoreFromXML(System::Xml::XmlReader^ xr);
		/** Load system state from specified xml file **/
		void loadStateFromFile(System::String^ filename);
		/** Load system state from specified xml text **/
		void loadStateFromText(System::String^ xml);
		/** No public variables **/
	private:
		/** Contains the array of channel pairs (output/playlist) **/
		static array<sChannel^>^ activeChannels;
		/** The global handle to the BAPS library audio
		 *  (This should never be accessible outside this class
		**/
		CBAPSAudioOutput *m_AudioOutput;
	};

	/** Inner unmanaged class to expose functionality to BAPSlib **/
	class UnmanagedCallBacks
	{
	public:
		static void notifyCallback(int channel)
		{
			GlobalAudioObject::notifyCallback(channel);
		}
	};
};