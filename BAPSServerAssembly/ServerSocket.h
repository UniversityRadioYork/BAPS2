#pragma once

#include "decodeStructs.h"

/**
 *  This file contains the network interface code, optimised where possible
**/

#define MAX_RECEIVE_BUFFER 512

namespace BAPSServerAssembly
{
	ref class ServerSocket
	{
	public:
		/** Create a listening socket **/
		ServerSocket( int port );
		/** Create a placeholder socket to receive an incoming connection on **/
		ServerSocket();
		/** Destroy the socket so that it doesn't block threads from exiting **/
		~ServerSocket();

		/** Strings are sent as an integer representing length and the ascii data **/
		void send(const System::String^ s);
		System::String^ receiveS();

		/** Commands are 16bit **/
		void send(const Command cmd);
		Command receiveC();

		/** Floats are 32bit **/
		void send(const float f);
		float receiveF();

		/** u32ints are 32 bit **/
		void send(const u32int i);
		u32int receiveI();

		/** Place the next inbound connection from this sockets queue and associate sock with it **/
		System::Net::IPAddress^ accept ( ServerSocket^ sock);
		/** Check if the socket is valid/connected **/
		inline bool isValid()
		{
			return (serverSocket!=nullptr && serverSocket->Connected);
		}

	private:
		/** Generic send function to reduce code duplication, simply sends all data in 'bytes' **/
 		inline void send(array<System::Byte>^ bytes);
		/** Generic receive function (limit MAX_RECEIVE_BUFFER), returned data is at start of byte array **/
		inline array<System::Byte>^ receive(int count);

		/** The low level socket connection **/
		System::Net::Sockets::Socket^ serverSocket;
		/** The receive buffer **/
		array<System::Byte>^ rxBytes;
	};
}