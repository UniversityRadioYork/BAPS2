#include "stdafx.h"
#include "ServerSocket.h"

using namespace BAPSServerAssembly;

/**
 *  This file contains the network interface code as optimised as possible
**/

ServerSocket::ServerSocket ( int port )
{
	/** Create the connection **/
	serverSocket = gcnew System::Net::Sockets::Socket(System::Net::Sockets::AddressFamily::InterNetwork,
													System::Net::Sockets::SocketType::Stream,
													System::Net::Sockets::ProtocolType::Tcp );
	/** Bind to all interfaces on the correct port **/
	serverSocket->Bind(gcnew System::Net::IPEndPoint(System::Net::IPAddress::Parse("0.0.0.0"), port));
	/** All sockets are non blocking due to lack of preemption on windows **/
	serverSocket->Blocking = false;
	/** Sockets will close without delay **/
	serverSocket->SetSocketOption(System::Net::Sockets::SocketOptionLevel::Tcp,
								  System::Net::Sockets::SocketOptionName::NoDelay,
								  1);
	/** Sockets shall linger for 0 milliseconds **/
	serverSocket->SetSocketOption(System::Net::Sockets::SocketOptionLevel::Socket,
										System::Net::Sockets::SocketOptionName::Linger,
										gcnew System::Net::Sockets::LingerOption(false, 0));
	/** Allow 10 queued connections maximum:
	 *  WORK NEEDED: config for this, bounds checks
	**/
	serverSocket->Listen(CONFIG_GETINT(CONFIG_MAXQUEUECONNS));
}

ServerSocket::ServerSocket()
{
	/** We need a buffer for the receive calls, so we use one function-wide buffer **/
	rxBytes = gcnew array<System::Byte>(MAX_RECEIVE_BUFFER);
}

ServerSocket::~ServerSocket()
{
	/** Clear up socket resources **/
	if (isValid())
	{
		serverSocket->Shutdown(System::Net::Sockets::SocketShutdown::Both);
		serverSocket->Close();
		serverSocket = nullptr;
	}
}

void ServerSocket::send(const System::String^ s)
{
	/** Strings are a combination of integer length and then ascii data **/
	send(static_cast<u32int>(System::Text::Encoding::ASCII->GetByteCount(const_cast<System::String^>(s))));
	send(System::Text::Encoding::ASCII->GetBytes(const_cast<System::String^>(s)));
}
System::String^ ServerSocket::receiveS()
{
	/** As before we find out how long the string is first and then grab the ascii data **/
	int stringLength = receiveI();
	System::String^ theString= "";

	while (stringLength > 0)
	{
		int toReceive = stringLength;
		if (stringLength > MAX_RECEIVE_BUFFER)
		{
			toReceive = MAX_RECEIVE_BUFFER;
		}
		theString = System::String::Concat(theString, System::Text::Encoding::ASCII->GetString(receive(toReceive), 0, toReceive));
		stringLength -= toReceive;
	}
	return theString;
}
void ServerSocket::send(Command cmd)
{
	/** We send commands as u32ints for now until clients support otherwise:
	 *  WORK NEEDED: wait for client support for shorter command sends
	**/
	cmd = System::Net::IPAddress::HostToNetworkOrder(*((short*)&cmd));
	send(System::BitConverter::GetBytes(static_cast<unsigned short int>(cmd)));
}
Command ServerSocket::receiveC()
{
	/** As above receive 4 bytes and chop to sizeof(cmd) (2) **/
	return System::Net::IPAddress::HostToNetworkOrder(System::BitConverter::ToInt16(receive(2), 0));
}
void ServerSocket::send(const float f)
{
	/** Floats are assumed to be 4 bytes long **/
	u32int temp = System::BitConverter::ToUInt32(System::BitConverter::GetBytes(f), 0);
	temp = System::Net::IPAddress::HostToNetworkOrder(*((int*)&temp));
	send(System::BitConverter::GetBytes(temp));
}
float ServerSocket::receiveF()
{
	/** As above **/
	array<System::Byte>^ temp = receive(4);
	u32int temp2 = System::Net::IPAddress::HostToNetworkOrder(System::BitConverter::ToInt32(temp, 0));
	temp = System::BitConverter::GetBytes(temp2);
	return System::BitConverter::ToSingle(temp, 0);
}
void ServerSocket::send(u32int i)
{
	/** u32int is exactly as it says unsigned 32 bit int **/
	send(System::BitConverter::GetBytes(System::Net::IPAddress::HostToNetworkOrder(*((int*)&i))));
}
u32int ServerSocket::receiveI()
{
	/** As above **/
	return System::Net::IPAddress::HostToNetworkOrder(System::BitConverter::ToInt32(receive(4), 0));
}
void ServerSocket::send(array<System::Byte>^ bytes)
{
	int index = 0;
	/** If sending no data then return immediately, else wait until it is all sent **/
	while (index != bytes->Length)
	{
		/**
		 *  Manage exceptions and maintain a count of the bytes sent and therefore the position
		 *  in the byte array
		**/
		try
		{
			index += serverSocket->Send(bytes, index, bytes->Length-index, System::Net::Sockets::SocketFlags::None);
		}
		catch (System::Net::Sockets::SocketException^ e)
		{
			if (static_cast<System::Net::Sockets::SocketError>(e->ErrorCode) != System::Net::Sockets::SocketError::WouldBlock)
			{
				/** Connection error must have occurred, rethrow exception **/
				throw e;
			}
			/** We are flooding the connection this is bad
			 *  WORK NEEDED: possible implementation of lossy sends for non vital data
			**/
			System::Threading::Thread::Sleep(1);
		}
	}
}
array<System::Byte>^ ServerSocket::receive(int count)
{
	/** We cannot receive more than MAX_RECEIVE_BUFFER so error **/
	if (count > MAX_RECEIVE_BUFFER)
	{
		/** Use the exception mechanism to abort this connection **/
		throw gcnew System::Exception(System::String::Concat("Attempt to receive: ", count.ToString(), " bytes. Overflow error\n"));
	}
	int index = 0;
	/** Keep going until all the data is received **/
	while (index != count)
	{
		/** Maintain count of the number of bytes received and set offsets accordingly **/
		try
		{
			int amountReceived = serverSocket->Receive(rxBytes, index, count-index, System::Net::Sockets::SocketFlags::None);
			if (amountReceived == 0)
			{
				throw gcnew System::Net::Sockets::SocketException();
			}
			index += amountReceived;
		}
		catch (System::Net::Sockets::SocketException^ e)
		{
			if (static_cast<System::Net::Sockets::SocketError>(e->ErrorCode) != System::Net::Sockets::SocketError::WouldBlock)
			{
				/** Re-throw exception if it is not just notifying the socket would have blocked
				 *  if it were in blocking mode
				**/
				throw e;
			}
			/** We are too fast or there is no data waiting **/
			System::Threading::Thread::Sleep(1);
		}
	}
	/** We assume the caller will be sensible enough to use only the amount of bytes it asked for **/
	return rxBytes;
}

System::Net::IPAddress^ ServerSocket::accept ( ServerSocket^ sock )
{
	/** As everything is non blocking we must make sure we succeed before returning **/
	bool success = false;
	while (!success)
	{
		/** If the accept does not throw an exception it has succeeded **/
		try
		{
			sock->serverSocket = serverSocket->Accept();
			success=true;
		}
		catch (System::Net::Sockets::SocketException^ e)
		{
			/** Only ignore the notification of would block **/
			if (static_cast<System::Net::Sockets::SocketError>(e->ErrorCode) != System::Net::Sockets::SocketError::WouldBlock)
			{
				/** Re-throw to allow the caller to deal with the issue **/
				throw e;
			}
			/** Perhaps a little too small but it is a very lightweight loop **/
			System::Threading::Thread::Sleep(1);
		}
	}
	/** The new socket is to be non blocking (this is not inherited under windows **/
	sock->serverSocket->Blocking = false;
	/** Will exit immediately (no delay) **/
	sock->serverSocket->SetSocketOption(System::Net::Sockets::SocketOptionLevel::Tcp,
										System::Net::Sockets::SocketOptionName::NoDelay,
										1);
	/** Will linger for 0 milliseconds (effectively never) **/
	sock->serverSocket->SetSocketOption(System::Net::Sockets::SocketOptionLevel::Socket,
										System::Net::Sockets::SocketOptionName::Linger,
										gcnew System::Net::Sockets::LingerOption(false, 0));
	return static_cast<System::Net::IPEndPoint ^>(sock->serverSocket->RemoteEndPoint)->Address;
}
