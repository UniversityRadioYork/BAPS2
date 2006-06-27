#pragma once
#include "ClientManager.h"
#include "LogManager.h"
#include "ConfigManager.h"
#include "Exceptions.h"

ref class BAPSController
{
public:
	static void initBAPSController()
	{
		if (CONFIG_GETINT(CONFIG_BAPSCONTROLLERENABLED) == CONFIG_YES_VALUE)
		{
			try
			{
				serialPort = gcnew System::IO::Ports::SerialPort("COM1", 2400, System::IO::Ports::Parity::None,8,System::IO::Ports::StopBits::One);
				serialPort->Open();
				serialPort->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(&BAPSController::handleData);
			}
			catch (System::Exception^ e)
			{
				throw gcnew BAPSTerminateException(System::String::Concat("Failed to start BAPS Controller:\n", e->Message, "Stack Trace:\n",e->StackTrace));
			}
		}
	}
	static void closeBAPSController()
	{
		if (serialPort != nullptr && serialPort->IsOpen)
		{
			serialPort->Close();
			serialPort = nullptr;
		}
	}
	static void handleData(System::Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e)
	{
		ClientManager::getMessageLock();
		try
		{
			int mode = CONFIG_GETINT(CONFIG_BAPSPADDLEMODE);
			int buttonCount = CONFIG_GETINT(CONFIG_BAPSCONTROLLERBUTTONCOUNT);
			int channelCount = ConfigManager::getChannelCount();
			int i;
			bool handled = false;
			for (i = 0 ; serialPort!=nullptr && serialPort->IsOpen && i < serialPort->BytesToRead ; i++)
			{
				System::Byte data = serialPort->ReadByte();
				handled=false;
				if (mode == CONFIG_CONTROLLER_PLAYBACK)
				{
					if (buttonCount>0 && data == CONFIG_GETINTn(CONFIG_BAPSCONTROLLERBUTTONCODE, 0))
					{
						ClientManager::getAudio()->getOutput(0)->play();
						handled=true;
					}
					else if (buttonCount>1 && data == CONFIG_GETINTn(CONFIG_BAPSCONTROLLERBUTTONCODE, 1))
					{
						if (ClientManager::getAudio()->getOutput(0)->isPlaying())
						{
							ClientManager::getAudio()->getOutput(0)->stop();
						}
						else
						{
							loadNextTrack(0);
						}
						handled=true;
					}
					else if (channelCount > 1 && buttonCount>2 && data == CONFIG_GETINTn(CONFIG_BAPSCONTROLLERBUTTONCODE, 2))
					{
						ClientManager::getAudio()->getOutput(1)->play();
						handled=true;
					}
					else if (channelCount > 1 && buttonCount>3 && data == CONFIG_GETINTn(CONFIG_BAPSCONTROLLERBUTTONCODE, 3))
					{
						if (ClientManager::getAudio()->getOutput(1)->isPlaying())
						{
							ClientManager::getAudio()->getOutput(1)->stop();
						}
						else
						{
							loadNextTrack(1);
						}
						handled=true;
					}
					else if (channelCount > 2 && buttonCount>4 && data == CONFIG_GETINTn(CONFIG_BAPSCONTROLLERBUTTONCODE, 4))
					{
						ClientManager::getAudio()->getOutput(2)->play();
						handled=true;
					}
					else if (channelCount > 2 && buttonCount>5 && data == CONFIG_GETINTn(CONFIG_BAPSCONTROLLERBUTTONCODE, 5))
					{
						if (ClientManager::getAudio()->getOutput(2)->isPlaying())
						{
							ClientManager::getAudio()->getOutput(2)->stop();
						}
						else
						{
							loadNextTrack(2);
						}
						handled=true;
					}
				}
				else if (mode == CONFIG_CONTROLLER_TEXTSCREEN)
				{
					if (buttonCount>0 && data == CONFIG_GETINTn(CONFIG_BAPSCONTROLLERBUTTONCODE, 0))
					{
						ClientManager::getAudio()->getOutput(0)->play();
						handled=true;
					}
					else if (buttonCount>1 && data == CONFIG_GETINTn(CONFIG_BAPSCONTROLLERBUTTONCODE, 1))
					{
						if (ClientManager::getAudio()->getOutput(0)->isPlaying())
						{
							ClientManager::getAudio()->getOutput(0)->stop();
						}
						else
						{
							loadNextTrack(0);
						}
						handled=true;
					}
					else if (buttonCount>2 && data == CONFIG_GETINTn(CONFIG_BAPSCONTROLLERBUTTONCODE, 2))
					{
						Command cmd = BAPSNET_SYSTEM | BAPSNET_TEXTSIZE | 1;
						ClientManager::broadcast(cmd);
						handled=true;
					}
					else if (buttonCount>3 && data == CONFIG_GETINTn(CONFIG_BAPSCONTROLLERBUTTONCODE, 3))
					{
						Command cmd = BAPSNET_SYSTEM | BAPSNET_TEXTSIZE | 0;
						ClientManager::broadcast(cmd);
						handled=true;
					}
					else if (buttonCount>4 && data == CONFIG_GETINTn(CONFIG_BAPSCONTROLLERBUTTONCODE, 4))
					{
						Command cmd = BAPSNET_SYSTEM | BAPSNET_SCROLLTEXT | 1;
						ClientManager::broadcast(cmd);
						handled=true;
					}
					else if (buttonCount>5 && data == CONFIG_GETINTn(CONFIG_BAPSCONTROLLERBUTTONCODE, 5))
					{
						Command cmd = BAPSNET_SYSTEM | BAPSNET_SCROLLTEXT | 0;
						ClientManager::broadcast(cmd);
						handled=true;
					}
				}
				if (buttonCount>6 && data == CONFIG_GETINTn(CONFIG_BAPSCONTROLLERBUTTONCODE, 6))
				{
					ClientManager::getAudio()->getOutput(0)->play();
						handled=true;
				}
				else if (buttonCount>7 && data == CONFIG_GETINTn(CONFIG_BAPSCONTROLLERBUTTONCODE, 7))
				{
					ClientManager::getAudio()->getOutput(1)->play();
						handled=true;
				}
				else if (buttonCount>8 && data == CONFIG_GETINTn(CONFIG_BAPSCONTROLLERBUTTONCODE, 8))
				{
					ClientManager::getAudio()->getOutput(2)->play();
						handled=true;
				}
				if (!handled)
				{
					LogManager::write(System::String::Concat("Received unrecognised BAPS Controller Code: ", data.ToString()), LOG_INFO, LOG_COMMS);
				}
			}
		}
		finally
		{
			ClientManager::releaseMessageLock();
		}
	}
private:
	static void loadNextTrack(int channel)
	{
		ClientManager::getAudio()->getOutput(channel)->stop();
		int nextTrack = ClientManager::getAudio()->getPlaylist(channel)->getNextPlayable(ClientManager::getAudio()->getOutput(channel)->getLoadedTrack()->getPosition()+1);
		if (nextTrack == -1)
		{
			nextTrack = ClientManager::getAudio()->getPlaylist(channel)->getNextPlayable(0);
		}
		if (nextTrack != -1)
		{
			ClientManager::getAudio()->getOutput(channel)->loadTrack(safe_cast<Track^>(ClientManager::getAudio()->getPlaylist(channel)->getEntry(nextTrack)));
		}
	}
	static System::IO::Ports::SerialPort^ serialPort;
};