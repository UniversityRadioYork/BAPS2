#pragma once
#include "ClientManager.h"
#include "LogManager.h"
#include "ConfigManager.h"
#include "Exceptions.h"

using namespace BAPSControllerAssembly;

namespace BAPSServerAssembly
{
	ref class BAPSController
	{
	public:
		static void initBAPSController()
		{
			if (CONFIG_GETINT(CONFIG_BAPSCONTROLLERENABLED) == CONFIG_YES_VALUE)
			{
				try
				{
					serialPort = gcnew System::IO::Ports::SerialPort(CONFIG_GETSTR(CONFIG_BAPSCONTROLLERPORT), 2400, System::IO::Ports::Parity::None,8,System::IO::Ports::StopBits::One);
					serialPort->Open();
					serialPort->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(&BAPSController::handleData);
				}
				catch (System::Exception^ e)
				{
					CONFIG_SET(CONFIG_BAPSCONTROLLERENABLED, CONFIG_NO_VALUE);
					LogManager::write(System::String::Concat("Failed to start BAPS Serial Controller:\n", e->Message, "Stack Trace:\n", e->StackTrace), LOG_INFO, LOG_COMMS);
				}
			}

			// Defined, but does nothing if no usb device is defined
			bapsController2 = gcnew BAPSControllerAssembly::BAPSController();
			if (CONFIG_GETINT(CONFIG_BAPSCONTROLLER2ENABLED) == CONFIG_YES_VALUE)
			{
				bapsController2->run(gcnew BAPSControllerAssembly::SignalCallback(handleSignal));
			}
		}
		static void closeBAPSController()
		{
			if (serialPort != nullptr && serialPort->IsOpen)
			{
				serialPort->Close();
				serialPort = nullptr;
			}
			if (bapsController2 != nullptr)
			{
				bapsController2->stop();
				bapsController2 = nullptr;
			}
		}
		static array<System::String^>^ getBAPSController2Serials()
		{
			return bapsController2->getSerialNumbers();
		}
		static void handleSignal(System::String^ device, int signal)
		{
			ClientManager::getMessageLock();
			for (int i = 0 ; i < CONFIG_GETINT(CONFIG_BAPSCONTROLLER2DEVICECOUNT) ; i++)
			{
				if (device->Equals(CONFIG_GETSTRn(CONFIG_BAPSCONTROLLER2SERIAL, i)))
				{
					signal += CONFIG_GETINTn(CONFIG_BAPSCONTROLLER2OFFSET, i);
					break;
				}
			}
			try
			{
				int mode = CONFIG_GETINT(CONFIG_BAPSPADDLEMODE);
				int buttonCount = CONFIG_GETINT(CONFIG_BAPSCONTROLLER2BUTTONCOUNT);
				int channelCount = ConfigManager::getChannelCount();
				bool handled = false;

				if (mode == CONFIG_CONTROLLER_PLAYBACK)
				{
					if (buttonCount>0 && signal == CONFIG_GETINTn(CONFIG_BAPSCONTROLLER2BUTTONCODE, 0))
					{
						ClientManager::getAudio()->getOutput(0)->play(true);
						handled=true;
					}
					else if (buttonCount>1 && signal == CONFIG_GETINTn(CONFIG_BAPSCONTROLLER2BUTTONCODE, 1))
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
					else if (channelCount > 1 && buttonCount>2 && signal == CONFIG_GETINTn(CONFIG_BAPSCONTROLLER2BUTTONCODE, 2))
					{
						ClientManager::getAudio()->getOutput(1)->play(true);
						handled=true;
					}
					else if (channelCount > 1 && buttonCount>3 && signal == CONFIG_GETINTn(CONFIG_BAPSCONTROLLER2BUTTONCODE, 3))
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
					else if (channelCount > 2 && buttonCount>4 && signal == CONFIG_GETINTn(CONFIG_BAPSCONTROLLER2BUTTONCODE, 4))
					{
						ClientManager::getAudio()->getOutput(2)->play(true);
						handled=true;
					}
					else if (channelCount > 2 && buttonCount>5 && signal == CONFIG_GETINTn(CONFIG_BAPSCONTROLLER2BUTTONCODE, 5))
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
					if (buttonCount>0 && signal == CONFIG_GETINTn(CONFIG_BAPSCONTROLLER2BUTTONCODE, 0))
					{
						ClientManager::getAudio()->getOutput(0)->play(true);
						handled=true;
					}
					else if (buttonCount>1 && signal == CONFIG_GETINTn(CONFIG_BAPSCONTROLLER2BUTTONCODE, 1))
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
					else if (buttonCount>2 && signal == CONFIG_GETINTn(CONFIG_BAPSCONTROLLER2BUTTONCODE, 2))
					{
						Command cmd = BAPSNET_SYSTEM | BAPSNET_TEXTSIZE | 1;
						ClientManager::broadcast(cmd);
						handled=true;
					}
					else if (buttonCount>3 && signal == CONFIG_GETINTn(CONFIG_BAPSCONTROLLER2BUTTONCODE, 3))
					{
						Command cmd = BAPSNET_SYSTEM | BAPSNET_TEXTSIZE | 0;
						ClientManager::broadcast(cmd);
						handled=true;
					}
					else if (buttonCount>4 && signal == CONFIG_GETINTn(CONFIG_BAPSCONTROLLER2BUTTONCODE, 4))
					{
						Command cmd = BAPSNET_SYSTEM | BAPSNET_SCROLLTEXT | 1;
						ClientManager::broadcast(cmd);
						handled=true;
					}
					else if (buttonCount>5 && signal == CONFIG_GETINTn(CONFIG_BAPSCONTROLLER2BUTTONCODE, 5))
					{
						Command cmd = BAPSNET_SYSTEM | BAPSNET_SCROLLTEXT | 0;
						ClientManager::broadcast(cmd);
						handled=true;
					}
				}
				if (buttonCount>6 && signal == CONFIG_GETINTn(CONFIG_BAPSCONTROLLER2BUTTONCODE, 6))
				{
					ClientManager::getAudio()->getOutput(0)->play(true);
					handled=true;
				}
				else if (buttonCount>7 && signal == CONFIG_GETINTn(CONFIG_BAPSCONTROLLER2BUTTONCODE, 7))
				{
					ClientManager::getAudio()->getOutput(1)->play(true);
					handled=true;
				}
				else if (buttonCount>8 && signal == CONFIG_GETINTn(CONFIG_BAPSCONTROLLER2BUTTONCODE, 8))
				{
					ClientManager::getAudio()->getOutput(2)->play(true);
					handled=true;
				}
				if (!handled)
				{
					LogManager::write(System::String::Concat("Received unrecognised BAPS 2 Controller Code: ", signal.ToString()), LOG_INFO, LOG_COMMS);
				}
			}
			finally
			{
				ClientManager::releaseMessageLock();
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
					if (data == 255)
					{
						// Keepalive, used for the controller to know that BAPS is alive and talking over serial.
						array<System::Byte>^ response = gcnew array<System::Byte>(1);
						response[0] = 255;
						serialPort->Write(response, 0, 1);
						handled=true;
					}
					// 254 is used to send a response back to the controller, containing channel information. Useful if the controller has a UI.
					else if (data == 254)
					{
						//Yes, this is rather manual, but I didn't like the look of trying to do JSON in C++
						for (int i = 0; i < 3; i++) {
							serialPort->Write(System::String::Concat("<CHANNEL:", i.ToString(), ","));
							serialPort->Write(System::String::Concat("TITLE:", ClientManager::getAudio()->getOutput(i)->getLoadedTrack()->ToString(), ","));
							serialPort->Write(System::String::Concat("LENGTH:", ClientManager::getAudio()->getOutput(i)->getFileDuration(), ","));
							serialPort->Write(System::String::Concat("POS:", ClientManager::getAudio()->getOutput(i)->getFilePosition(), ","));
							serialPort->Write("STATE:");
							if (ClientManager::getAudio()->getOutput(0)->isPlaying()) {
								serialPort->Write("PLAY");
							}
							else if (ClientManager::getAudio()->getOutput(0)->isPaused()) {
								serialPort->Write("PAUSE");
							}
							else {
								serialPort->Write("STOP");
							}
							serialPort->Write(">\r\n");
						}
						handled = true;
					}
					else if (mode == CONFIG_CONTROLLER_PLAYBACK)
					{
						if (buttonCount>0 && data == CONFIG_GETINTn(CONFIG_BAPSCONTROLLERBUTTONCODE, 0))
						{
							ClientManager::getAudio()->getOutput(0)->play(true);
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
							ClientManager::getAudio()->getOutput(1)->play(true);
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
							ClientManager::getAudio()->getOutput(2)->play(true);
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
							ClientManager::getAudio()->getOutput(0)->play(true);
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
						ClientManager::getAudio()->getOutput(0)->play(true);
						handled=true;
					}
					else if (buttonCount>7 && data == CONFIG_GETINTn(CONFIG_BAPSCONTROLLERBUTTONCODE, 7))
					{
						ClientManager::getAudio()->getOutput(1)->play(true);
						handled=true;
					}
					else if (buttonCount>8 && data == CONFIG_GETINTn(CONFIG_BAPSCONTROLLERBUTTONCODE, 8))
					{
						ClientManager::getAudio()->getOutput(2)->play(true);
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
			int nextTrack = ClientManager::getAudio()->getPlaylist(channel)->getNextPlayable(ClientManager::getAudio()->getOutput(channel)->getLoadedTrack()->getEntryNumber()+1);
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
		static BAPSControllerAssembly::BAPSController^ bapsController2;
	};
};
