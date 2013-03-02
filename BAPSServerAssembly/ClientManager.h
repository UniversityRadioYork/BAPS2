#pragma once

#include "GlobalAudioObject.h"
#include "decodeStructs.h"
#include "ServerSocket.h"

namespace BAPSServerAssembly
{
	/** Forward declaration due to each class referencing each other **/
	ref class ClientInstance;

	/**
	 *  ClientManager is the central class of the Server. It holds all the information for the clients
	 *  as well as holding all the clients. This is because all clients share information and all
	 *  clients need to be aware of all other clients (or at least have access to an object that does)
	**/

	ref class ClientManager
	{
	public:
		/** Initialise all objects **/
		static void initClientManager();
		/** This class must be closed to clean up threads **/ 
		static void closeClientManager();
		/** Notify everyone who is chatting that there is a new person **/
		static void addToChat(System::String^ username);
		/** Notify everyone who is chatting that someone left **/
		static void removeFromChat(System::String^ username);
		/** Send a message to the appropriate people **/
		static void sendMessage(System::String^ from, System::String^ to, System::String^ message);

		/** Accessor for the server Socket so that it can be 'accept'ed from **/
		static ServerSocket ^ getServer()
		{
			return server;
		}
		/** Retrieve a handle to the audio outputs **/
		static GlobalAudioObject ^ getAudio()
		{
			return audio;
		}
		/** This lock is here to provide mutual exclusion over updates to clients
		 *  A client should hold this lock whilst synchronizing state
		 *  All state changing operations must hold this lock before making the operation
		 *  and up until after they have sent the update to all clients 
		**/
		static void getMessageLock()
		{
			messageMutex->WaitOne();
		}
		static void releaseMessageLock()
		{
			messageMutex->ReleaseMutex();
		}
		/** Accessors for the client lock **/
		static void getClientLock()
		{
			clientMutex->WaitOne();
		}
		static void releaseClientLock()
		{
			clientMutex->ReleaseMutex();
		}
		static ClientInstance^ getFirstClient()
		{
			return firstClient;
		}
		/** springClean is used to update the client linked list to remove dead clients	**/
		static void springClean();

		/** All the various communications functions **/
		static void broadcast(Command cmd);
		static void broadcast(Command cmd, u32int u);
		static void broadcast(Command cmd, System::String^ s);
		static void broadcast(Command cmd, float f);
		static void broadcast(Command cmd, u32int u, System::String^ s);
		static void broadcast(Command cmd, u32int u1, u32int u2);
		static void broadcast(Command cmd, u32int u1, u32int u2, u32int u3);
		static void broadcast(Command cmd, u32int u1, u32int u2, System::String^ s);
		static void broadcast(Command cmd, u32int u1, u32int u2, System::String^ s3, u32int u4);
		static void broadcast(Command cmd, u32int u1, u32int u2, System::String^ s3, System::String^ s4);
		static void broadcast(Command cmd, u32int u1, u32int u2, System::String^ s3, System::String^ s4, System::String^ s5);
		static void send(ClientInstance^ c, Command cmd);
		static void send(ClientInstance^ c, Command cmd, u32int u);
		static void send(ClientInstance^ c, Command cmd, System::String^ s);
		static void send(ClientInstance^ c, Command cmd, System::String^ s1, u32int i2);
		static void send(ClientInstance^ c, Command cmd, float f);
		static void send(ClientInstance^ c, Command cmd, u32int u, System::String^ s);
		static void send(ClientInstance^ c, Command cmd, u32int u1, u32int u2);
		static void send(ClientInstance^ c, Command cmd, u32int u1, System::String^ s, u32int u2);
		static void send(ClientInstance^ c, Command cmd, u32int u1, u32int u2, System::String^ s);
		static void send(ClientInstance^ c, Command cmd, u32int u1, u32int u2, u32int u3);
		static void send(ClientInstance^ c, Command cmd, u32int u1, u32int u2, System::String^ s3, u32int u4);
		static void send(ClientInstance^ c, Command cmd, System::String^ s1, System::String^ s2, System::String^ s3 );
		static void send(ClientInstance^ c, Command cmd, System::String^ s1, System::String^ s2, System::String^ s3, System::String^ s4 );
		static void send(ClientInstance^ c, Command cmd, u32int u1, u32int u2, System::String^ s3, System::String^ s4);

	private:
		/** A placeholder for the first client in the list, Don't ever lose this
		 *  or clients will be GC'd
		**/
		static ClientInstance ^ firstClient;
		/** The server Socket object **/
		static ServerSocket ^ server;
		/** The main handle to the audio output library **/
		static GlobalAudioObject^ audio;
		/** The message Synchronization mutex **/
		static System::Threading::Mutex^ messageMutex;
		/** The Client list mutex **/
		static System::Threading::Mutex^ clientMutex;
		/** Controls the automatic update of clients **/
		static System::Threading::Timer^ updateTimer;
		/** The asynchronous update mutex -- used to ensure an update is not taking place when exiting **/
		static System::Threading::Mutex^ asyncMutex;
		/** Used to update clients asynchronously **/
		static void updateClients(Object^ state);
		/** When the ClientManager is being deleted there is a possibility of one last update to Clients
			This flag guards against this
		**/
		static bool isDead;
	};
};