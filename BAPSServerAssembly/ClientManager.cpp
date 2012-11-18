#include "stdafx.h"
#include "ClientManager.h"
#include "ClientInstance.h"

using namespace BAPSServerAssembly;

/**
 *  This file defines all send routines for the Server
 *  This allows for easy updating of any locking required and simplifies the
 *  remote client update process.
**/

/** MACRO definitions to make broadcast functions easier to read and maintain:
 *    We assume the linked list of clients is always valid at any point in time
 *    The last client in the list is 0
 *    Lock the send function so we have mutual exclusion on the socket (for writes)
 *    Pass any exceptions to the clientInstance object this can choose to kill itself
 *      or deal with the error and accept the consequences
**/
#define TRAVERSE_AND_LOCK() 	clientMutex->WaitOne();\
								ClientInstance^ myClient = firstClient;\
								while (myClient != nullptr)\
								{\
									if (myClient->shouldAutoUpdate())\
									{\
										myClient->getSendLock();\
										try\
										{
											
#define UNLOCK_TRAVERSE_END()			}\
										catch (System::Exception^ e)\
										{\
											myClient->handleException(e);\
										}\
										myClient->releaseSendLock();\
									}\
									myClient = myClient->nextClient;\
								}\
								clientMutex->ReleaseMutex();

void ClientManager::springClean()
{
	clientMutex->WaitOne();
	/** Three cases arise when trying to tidy up the linked list:
	 *  1) The first client is dead
	 *  2) Any other client is dead
	 *  3) Should not happen - Last client is dead! Therefore Server is dead
	**/
	/** WORK NEEDED: handle the case where the last client is dead! **/
	ClientInstance ^myClient, ^previousClient;
	bool modifyingFirstClient = true;

	while (modifyingFirstClient)
	{
		myClient = firstClient;
		if (myClient->isDead())
		{
			firstClient = myClient->nextClient;
			if (myClient->isChatting())
			{
				removeFromChat(myClient->getUsername());
			}
			delete myClient;
		}
		else
		{
			modifyingFirstClient = false;
			myClient = myClient->nextClient;
		}
	}
	previousClient = firstClient;
	while (myClient != nullptr)
	{
		if (myClient->isDead())
		{
			previousClient->nextClient = myClient->nextClient;
			if (myClient->isChatting())
			{
				removeFromChat(myClient->getUsername());
			}
			delete myClient;
			myClient = previousClient->nextClient;
		}
		else
		{
			previousClient = myClient;
			myClient = myClient->nextClient;
		}
	}
	clientMutex->ReleaseMutex();
}
void ClientManager::initClientManager()
{
	/** WORK NEEDED: exception handling in startup and shutdown of client manager **/
	isDead = false;

	server = gcnew ServerSocket( CONFIG_GETINT(CONFIG_PORT));
	messageMutex = gcnew System::Threading::Mutex();
	clientMutex = gcnew System::Threading::Mutex();
	asyncMutex = gcnew System::Threading::Mutex();
	
	audio = gcnew GlobalAudioObject();
	firstClient = gcnew ClientInstance();
	/** In 300ms run updateClients every 300ms **/
	System::Threading::TimerCallback^ tc = gcnew System::Threading::TimerCallback(&ClientManager::updateClients);
	updateTimer = gcnew System::Threading::Timer(tc,
											   nullptr,
											   300,
											   300);
}
void ClientManager::closeClientManager()
{
	/** Set the timer to never execute its delegate **/
	if (updateTimer != nullptr)
	{
		updateTimer->Change(System::Threading::Timeout::Infinite,System::Threading::Timeout::Infinite);
		updateTimer->~Timer();
		updateTimer = nullptr;
	}
	/** Ensure that there is no lingering update thread active **/
	if (asyncMutex != nullptr)
	{
		asyncMutex->WaitOne();
		/** CAUTION: This relies on x86 memory model, true must be set before release**/
		isDead = true;
		asyncMutex->ReleaseMutex();
	}
	/** Kill off all the clients we are going down hard! **/
	ClientInstance ^nextClient = nullptr;
	while (firstClient != nullptr)
	{
		nextClient = firstClient->nextClient;
		/** deconstructor does the killing **/
		delete firstClient;
		firstClient = nextClient;
	}
	/** server is being 'accepted' from and must not become invalid until clients are dead **/
	if (server != nullptr)
	{
		delete server;
		server = nullptr;
	}
	/** Client Manager is also responsible for the outputs **/
	if (audio != nullptr)
	{
		delete audio;
		audio = nullptr;
	}
	messageMutex = nullptr;
	clientMutex = nullptr;
	asyncMutex = nullptr;
}

void ClientManager::updateClients(Object^ state)
{
	static bool alreadyRunning = false;
	if (alreadyRunning)
	{
		return;
	}
	/** WORK NEEDED: guarantee this to never stall **/
	/** Take the Mutex (this should always succeed) to stop the ClientManager from being closed **/
	asyncMutex->WaitOne();
	try
	{
		alreadyRunning = true;
		if (!isDead)
		{
			/** Setup the command to be send elapsed time **/
			u32int cmd = BAPSNET_PLAYBACK | BAPSNET_POSITION;

			/** Loop through all the channels **/
			for (int channel = 0; channel < CHANNEL_COUNT ; channel++)
			{
				/** Check the channel is currently active **/
				if (getAudio()->getOutput(channel)->isLoaded())
				{
					/** Send elapsed time to all clients, ClientManager deals with clients who have
					*  requested no updates **/
					broadcast(cmd | (channel & 0x3f),
						getAudio()->getOutput(channel)->getFilePosition());
				}
			}
			/** Check for dead clients and destroy them **/
			springClean();
		}
	}
	finally
	{
		alreadyRunning = false;
		asyncMutex->ReleaseMutex();
	}
}

void ClientManager::sendMessage(System::String^ from, System::String^ to, System::String^ message)
{
	getClientLock();
	try
	{
		ClientInstance^ ci = getFirstClient();

		System::String^ currentUser;
		Command cmd = BAPSNET_SYSTEM | BAPSNET_SENDMESSAGE;

		while (ci != nullptr)
		{
			currentUser = ci->getUsername();
			if (ci->isChatting() &&
				(System::String::Compare(currentUser,from) == 0 ||
				System::String::Compare(currentUser,to) == 0 ||
				System::String::Compare("ALL",to) == 0))
			{
				send(ci,cmd, from, to, message);
			}
			ci = ci->nextClient;
		}
	}
	finally
	{
		releaseClientLock();
	}
}

void ClientManager::addToChat(System::String^ username)
{
	getClientLock();
	try
	{
		int alreadyChattingCount = 0;
		/** Add a user **/
		Command cmd = BAPSNET_SYSTEM | BAPSNET_CLIENTCHANGE | 1;
		ClientInstance^ ci = getFirstClient();
		while (ci != nullptr)
		{
			if (ci->isChatting() &&
				System::String::Compare(ci->getUsername(),username) ==0)
			{
				alreadyChattingCount++;
			}
			ci = ci->nextClient;
		}
		ci = getFirstClient();
		while (alreadyChattingCount == 1 && ci != nullptr)
		{
			if (ci->isChatting() &&
				System::String::Compare(ci->getUsername(),username) ==0)
			{
				send(ci,cmd, username);
			}
			ci = ci->nextClient;
		}

		ci = getFirstClient();

		while (alreadyChattingCount == 0 && ci != nullptr)
		{
			if (ci->isChatting())
			{
				send(ci,cmd, username);
			}
			ci = ci->nextClient;
		}
	}
	finally
	{
		releaseClientLock();
	}
}

void ClientManager::removeFromChat(System::String^ username)
{
	/** Assumes the client being removed has had its chatting flag reset **/
	getClientLock();
	try
	{
		ClientInstance^ ci = getFirstClient();
		int stillChatting = 0;
		/** Remove a user **/
		Command cmd = BAPSNET_SYSTEM | BAPSNET_CLIENTCHANGE | 0;

		while (ci != nullptr)
		{
			if (ci->isChatting() &&
				System::String::Compare(ci->getUsername(),username) ==0)
			{
				stillChatting++;
			}
			ci = ci->nextClient;
		}
		ci = getFirstClient();
		while (stillChatting == 1 && ci != nullptr)
		{
			if (ci->isChatting() &&
				System::String::Compare(ci->getUsername(),username) ==0)
			{
				send(ci,cmd, username);
			}
			ci = ci->nextClient;
		}

		ci = getFirstClient();

		while (stillChatting == 0 && ci != nullptr)
		{
			if (ci->isChatting())
			{
				send(ci,cmd, username);
			}
			ci = ci->nextClient;
		}
	}
	finally
	{
		releaseClientLock();
	}
}


/** Helper functions for broadcasts to all clients and sends to single clients
 *  WORK NEEDED: investigate using templates to reduce the number of functions needed
 *               send<type1, type2, type3>(a, b, c)
**/
void ClientManager::broadcast(Command cmd)
{
	TRAVERSE_AND_LOCK()
		myClient->getConnection()->send(cmd);
		myClient->getConnection()->send((u32int)0);
	UNLOCK_TRAVERSE_END()
}
void ClientManager::send(ClientInstance^ c, Command cmd)
{
	c->getSendLock();
	c->getConnection()->send(cmd);
	c->getConnection()->send((u32int)0);
	c->releaseSendLock();
}
void ClientManager::broadcast(Command cmd, u32int u)
{
	TRAVERSE_AND_LOCK()
		myClient->getConnection()->send(cmd);
		myClient->getConnection()->send((u32int)4);
		myClient->getConnection()->send(u);
	UNLOCK_TRAVERSE_END()
}
void ClientManager::send(ClientInstance^ c, Command cmd, u32int u)
{
	c->getSendLock();
	c->getConnection()->send(cmd);
	c->getConnection()->send((u32int)4);
	c->getConnection()->send(u);
	c->releaseSendLock();
}
void ClientManager::broadcast(Command cmd, System::String^ s)
{
	TRAVERSE_AND_LOCK()
		myClient->getConnection()->send(cmd);
		myClient->getConnection()->send((u32int)(4+s->Length));
		myClient->getConnection()->send(s);
	UNLOCK_TRAVERSE_END()
}
void ClientManager::send(ClientInstance^ c, Command cmd, System::String^ s)
{
	c->getSendLock();
	c->getConnection()->send(cmd);
	c->getConnection()->send((u32int)(4+s->Length));
	c->getConnection()->send(s);
	c->releaseSendLock();
}
void ClientManager::send(ClientInstance^ c, Command cmd, System::String^ s1, u32int i2)
{
	c->getSendLock();
	c->getConnection()->send(cmd);
	c->getConnection()->send((u32int)(8+s1->Length));
	c->getConnection()->send(s1);
	c->getConnection()->send(i2);
	c->releaseSendLock();
}
void ClientManager::broadcast(Command cmd, float f)
{
	TRAVERSE_AND_LOCK()
		myClient->getConnection()->send(cmd);
		myClient->getConnection()->send((u32int)4);
		myClient->getConnection()->send(f);
	UNLOCK_TRAVERSE_END()
}
void ClientManager::send(ClientInstance^ c, Command cmd, float f)
{
	c->getSendLock();
	c->getConnection()->send(cmd);
	c->getConnection()->send((u32int)4);
	c->getConnection()->send(f);
	c->releaseSendLock();
}
void ClientManager::broadcast(Command cmd, u32int u, System::String^ s)
{
	TRAVERSE_AND_LOCK()
		myClient->getConnection()->send(cmd);
		myClient->getConnection()->send((u32int)(8+s->Length));
		myClient->getConnection()->send(u);
		myClient->getConnection()->send(s);
	UNLOCK_TRAVERSE_END()
}
void ClientManager::send(ClientInstance^ c, Command cmd, u32int u, System::String^ s)
{
	c->getSendLock();
	c->getConnection()->send(cmd);
	c->getConnection()->send((u32int)(8+s->Length));
	c->getConnection()->send(u);
	c->getConnection()->send(s);
	c->releaseSendLock();
}
void ClientManager::broadcast(Command cmd, u32int u1, u32int u2)
{
	TRAVERSE_AND_LOCK()
		myClient->getConnection()->send(cmd);
		myClient->getConnection()->send((u32int)8);
		myClient->getConnection()->send(u1);
		myClient->getConnection()->send(u2);
	UNLOCK_TRAVERSE_END()
}
void ClientManager::send(ClientInstance^ c, Command cmd, u32int u1, u32int u2)
{
	c->getSendLock();
	c->getConnection()->send(cmd);
	c->getConnection()->send((u32int)8);
	c->getConnection()->send(u1);
	c->getConnection()->send(u2);
	c->releaseSendLock();
}

void ClientManager::send(ClientInstance^ c, Command cmd, u32int u1, System::String^ s, u32int u2)
{
	c->getSendLock();
	c->getConnection()->send(cmd);
	c->getConnection()->send((u32int)(12+s->Length));
	c->getConnection()->send(u1);
	c->getConnection()->send(s);
	c->getConnection()->send(u2);
	c->releaseSendLock();
}

void ClientManager::broadcast(Command cmd, u32int u1, u32int u2, System::String^ s)
{
	TRAVERSE_AND_LOCK()
		myClient->getConnection()->send(cmd);
		myClient->getConnection()->send((u32int)12+s->Length);
		myClient->getConnection()->send(u1);
		myClient->getConnection()->send(u2);
		myClient->getConnection()->send(s);
	UNLOCK_TRAVERSE_END()
}
void ClientManager::broadcast(Command cmd, u32int u1, u32int u2, u32int u3)
{
	TRAVERSE_AND_LOCK()
		myClient->getConnection()->send(cmd);
		myClient->getConnection()->send((u32int)12);
		myClient->getConnection()->send(u1);
		myClient->getConnection()->send(u2);
		myClient->getConnection()->send(u3);
	UNLOCK_TRAVERSE_END()
}
void ClientManager::broadcast(Command cmd, u32int u1, u32int u2, System::String^ s3, u32int u4)
{
	TRAVERSE_AND_LOCK()
	myClient->getConnection()->send(cmd);
	myClient->getConnection()->send((u32int)16+s3->Length);
	myClient->getConnection()->send(u1);
	myClient->getConnection()->send(u2);
	myClient->getConnection()->send(s3);
	myClient->getConnection()->send(u4);
	UNLOCK_TRAVERSE_END()
}

void ClientManager::broadcast(Command cmd, u32int u1, u32int u2, System::String^ s3, System::String^ s4)
{
	TRAVERSE_AND_LOCK()
	myClient->getConnection()->send(cmd);
	myClient->getConnection()->send((u32int)16+s3->Length+s4->Length);
	myClient->getConnection()->send(u1);
	myClient->getConnection()->send(u2);
	myClient->getConnection()->send(s3);
	myClient->getConnection()->send(s4);
	UNLOCK_TRAVERSE_END()
}

void ClientManager::broadcast(Command cmd, u32int u1, u32int u2, System::String^ s3, System::String^ s4, System::String^ s5)
{
	TRAVERSE_AND_LOCK()
	myClient->getConnection()->send(cmd);
	myClient->getConnection()->send((u32int)20+s3->Length+s4->Length+s5->Length);
	myClient->getConnection()->send(u1);
	myClient->getConnection()->send(u2);
	myClient->getConnection()->send(s3);
	myClient->getConnection()->send(s4);
	myClient->getConnection()->send(s5);
	UNLOCK_TRAVERSE_END()
}

void ClientManager::send(ClientInstance^ c, Command cmd, u32int u1, u32int u2, System::String^ s3, System::String^ s4)
{
	c->getSendLock();
	c->getConnection()->send(cmd);
	c->getConnection()->send((u32int)16+s3->Length+s4->Length);
	c->getConnection()->send(u1);
	c->getConnection()->send(u2);
	c->getConnection()->send(s3);
	c->getConnection()->send(s4);
	c->releaseSendLock();
}
void ClientManager::send(ClientInstance^ c, Command cmd, u32int u1, u32int u2, System::String^ s3, u32int u4)
{
	c->getSendLock();
	c->getConnection()->send(cmd);
	c->getConnection()->send((u32int)(16+s3->Length));
	c->getConnection()->send(u1);
	c->getConnection()->send(u2);
	c->getConnection()->send(s3);
	c->getConnection()->send(u4);
	c->releaseSendLock();
}
void ClientManager::send(ClientInstance^ c, Command cmd, u32int u1, u32int u2, System::String^ s)
{
	c->getSendLock();
	c->getConnection()->send(cmd);
	c->getConnection()->send((u32int)(12+s->Length));
	c->getConnection()->send(u1);
	c->getConnection()->send(u2);
	c->getConnection()->send(s);
	c->releaseSendLock();
}

void ClientManager::send(ClientInstance^ c, Command cmd, u32int u1, u32int u2, u32int u3)
{
	c->getSendLock();
	c->getConnection()->send(cmd);
	c->getConnection()->send((u32int)(12));
	c->getConnection()->send(u1);
	c->getConnection()->send(u2);
	c->getConnection()->send(u3);
	c->releaseSendLock();
}
void ClientManager::send(ClientInstance^ c, Command cmd, System::String^ s1, System::String^ s2, System::String^ s3, System::String^ s4 )
{
	c->getSendLock();
	c->getConnection()->send(cmd);
	c->getConnection()->send((u32int)(16+s1->Length+s2->Length+s3->Length+s4->Length));
	c->getConnection()->send(s1);
	c->getConnection()->send(s2);
	c->getConnection()->send(s3);
	c->getConnection()->send(s4);
	c->releaseSendLock();
}
void ClientManager::send(ClientInstance^ c, Command cmd, System::String^ s1, System::String^ s2, System::String^ s3 )
{
	c->getSendLock();
	c->getConnection()->send(cmd);
	c->getConnection()->send((u32int)(12+s1->Length+s2->Length+s3->Length));
	c->getConnection()->send(s1);
	c->getConnection()->send(s2);
	c->getConnection()->send(s3);
	c->releaseSendLock();
}