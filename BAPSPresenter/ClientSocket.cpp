#include "stdafx.h"
#include "ClientSocket.h"


using namespace BAPSPresenter;

ClientSocket::ClientSocket (System::String^ host, int port)
{
	clientSocket = gcnew System::Net::Sockets::Socket(System::Net::Sockets::AddressFamily::InterNetwork,
													System::Net::Sockets::SocketType::Stream,
													System::Net::Sockets::ProtocolType::Tcp );
	clientSocket->Connect(gcnew System::Net::IPEndPoint(System::Net::IPAddress::Parse(host), port));
	/** All sockets are non blocking due to lack of preemption on windows **/
	clientSocket->Blocking = false;
	/** Sockets will close without delay **/
	clientSocket->SetSocketOption(System::Net::Sockets::SocketOptionLevel::Tcp,
								  System::Net::Sockets::SocketOptionName::NoDelay,
								  1);
	/** Sockets shall linger for 0 milliseconds **/
	clientSocket->SetSocketOption(System::Net::Sockets::SocketOptionLevel::Socket,
										System::Net::Sockets::SocketOptionName::Linger,
										gcnew System::Net::Sockets::LingerOption(false, 0));
	rxBytes = gcnew array<System::Byte>(MAX_RECEIVE_BUFFER);
}

ClientSocket::~ClientSocket()
{
	/** Clear up socket resources **/
	if (isValid())
	{
		clientSocket->Shutdown(System::Net::Sockets::SocketShutdown::Both);
		clientSocket->Close();
		clientSocket = nullptr;
	}
}

void ClientSocket::send(System::String^ s)
{
	/** Strings are a combination of integer length and then ascii data **/
	send(static_cast<u32int>(System::Text::Encoding::ASCII->GetByteCount(s)));
	send(System::Text::Encoding::ASCII->GetBytes(s));
}
System::String^ ClientSocket::receiveS()
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
void ClientSocket::send(Command cmd)
{
	/** Commands and 16bit ints (2 bytes) **/
	cmd = System::Net::IPAddress::HostToNetworkOrder(*((short*)&cmd));
	send(System::BitConverter::GetBytes(static_cast<unsigned short int>(cmd)));
}
Command ClientSocket::receiveC()
{
	/** Commands are 2 bytes long **/
	return System::Net::IPAddress::HostToNetworkOrder(System::BitConverter::ToInt16(receive(2), 0));
}
void ClientSocket::send(const float f)
{
	/** Floats are assumed to be 4 bytes long **/
	u32int temp = System::BitConverter::ToUInt32(System::BitConverter::GetBytes(f), 0);
	temp = System::Net::IPAddress::HostToNetworkOrder(*((int*)&temp));
	send(System::BitConverter::GetBytes(temp));
}
float ClientSocket::receiveF()
{
	/** As above **/
	array<System::Byte>^ temp = receive(4);
	u32int temp2 = System::Net::IPAddress::HostToNetworkOrder(System::BitConverter::ToInt32(temp, 0));
	temp = System::BitConverter::GetBytes(temp2);
	return System::BitConverter::ToSingle(temp, 0);
}
void ClientSocket::send(u32int i)
{
	/** u32int is exactly as it says unsigned 32 bit int **/
	send(System::BitConverter::GetBytes(System::Net::IPAddress::HostToNetworkOrder(*((int*)&i))));
}
u32int ClientSocket::receiveI()
{
	/** As above **/
	return System::Net::IPAddress::HostToNetworkOrder(System::BitConverter::ToInt32(receive(4), 0));
}
void ClientSocket::send(array<System::Byte>^ bytes)
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
			index += clientSocket->Send(bytes, index, bytes->Length-index, System::Net::Sockets::SocketFlags::None);
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
array<System::Byte>^ ClientSocket::receive(int count)
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
			int amountReceived = clientSocket->Receive(rxBytes, index, count-index, System::Net::Sockets::SocketFlags::None);
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
