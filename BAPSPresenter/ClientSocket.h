#pragma once

#include "decodeStructs.h"

#define MAX_RECEIVE_BUFFER 512

/**
	This class defines all the low level network connection functions and functions
	for how to send and receive the 4 fundamental data types used in BAPSNet
**/
namespace BAPSPresenter
{
	ref class ClientSocket
	{
	public:
		/** Create and connect a socket **/
		ClientSocket(System::String^ host, int port);
		/** Destroy the socket so that it doesn't block threads from exiting **/
		~ClientSocket();

		/** Strings are sent as an integer representing length and the ascii data **/
		void send(System::String^ s);
		System::String^ receiveS();

		/** Commands are 16bit **/
		void send(const Command cmd);
		Command receiveC();

		/** Floats are 32bit **/
		void send(const float f);
		float receiveF();

		/** u32ints are 32bit **/
		void send(const u32int i);
		u32int receiveI();

		/** Check if the socket is valid/connected **/
		inline bool isValid()
		{
			return (clientSocket!=nullptr && clientSocket->Connected);
		}

	private:
		/** Generic send function to reduce code duplication, simply sends all data in 'bytes' **/
 		inline void send(array<System::Byte>^ bytes);
		/** Generic receive function (limit MAX_RECEIVE_BUFFER), returned data is at start of byte array **/
		inline array<System::Byte>^ receive(int count);

		/** The low level socket connection **/
		System::Net::Sockets::Socket^ clientSocket;
		/** The receive buffer **/
		array<System::Byte>^ rxBytes;
	};
};