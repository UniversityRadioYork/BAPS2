#pragma once

#include "LogManager.h"
#include "ServerSocket.h"
#include "GlobalAudioObject.h"
#include "ClientManager.h"
#include "UserManager.h"
#include "LibraryTrack.h"
#include "UtilityMacros.h"

namespace BAPSServerAssembly
{
	/**
	 *  A ClientInstance defines a connection to a client application
	 *  Each client has some shared data accessible in ClientManager
	 **/

	using namespace Npgsql;

	#define STS_ENTRY 0
	#define STS_CONNECTED 1
	#define STS_EXIT 2

	#define BEGIN_MESSAGE_BLOCK()	ClientManager::getMessageLock();
	#define END_MESSAGE_BLOCK()		ClientManager::releaseMessageLock();

	#define BEGIN_ACTION_BLOCKED0(x)  void ClientInstance::x()\
										{\
											BEGIN_MESSAGE_BLOCK();\
											try\
											{
	#define BEGIN_ACTION_BLOCKED1(x,y1)  void ClientInstance::x(y1)\
										{\
											BEGIN_MESSAGE_BLOCK();\
											try\
											{
	#define BEGIN_ACTION_BLOCKED2(x,y1,y2)  void ClientInstance::x(y1,y2)\
										{\
											BEGIN_MESSAGE_BLOCK();\
											try\
											{
	#define BEGIN_ACTION_BLOCKED3(x,y1,y2,y3)  void ClientInstance::x(y1,y2,y3)\
										{\
											BEGIN_MESSAGE_BLOCK();\
											try\
											{

	#define END_ACTION_UNBLOCK()			}\
											finally\
											{\
												END_MESSAGE_BLOCK();\
											}\
										}

	ref class ClientInstance
	{
	public:
		Command lastcmd;
		/** Initialize **/
		ClientInstance();
		/** Destructor takes care of thread destruction **/
		~ClientInstance();
		/** Accessor for the Socket connection - prevents external change **/
		inline ServerSocket^ getConnection()
		{
			return connection;
		}
		/** Accessor for autoupdating (takes care of client being dead) **/
		inline bool shouldAutoUpdate()
		{
			return autoUpdate && !dead;
		}
		/** Accessor for the dead flag **/
		inline bool isDead()
		{
			return dead;
		}
		/** If something goes wrong to do with a client a ClientInstance handles the exception **/
		void handleException(System::Exception^ e)
		{
			LogManager::write(System::String::Concat("Exception Caught, Client terminating\n", e->Message, "Stack Trace:\n",e->StackTrace), LOG_WARNING, LOG_COMMS); 
			/** We just die horribly and nastily for now **/
			autoUpdate = false;
			dead = true;
		}

		/** Abstraction on the send lock **/
		inline void getSendLock()
		{
			sendMutex->WaitOne();
		}
		/** Abstraction on the send lock **/
		inline void releaseSendLock()
		{
			sendMutex->ReleaseMutex();
		}

		/** Gets the username of the logged in user **/
		System::String^ getUsername()
		{
			return userInfo->getUsername();
		}
		/** Find out if this client is chatting **/
		bool isChatting()
		{
			return receiveChat;
		}

		/** The ONLY public variable, This is updated by ClientManaged as it maintains the linked list **/
		ClientInstance^ nextClient;
	private:
		/** Decodes Command values to actions **/
		void decodeCommand(Command cmdReceived);
		/** Main program loop, each ClientInstance waits for Commands in this loop **/
		void clientControlLoop();

		/** PLAYBACK actions **/
		void loadFile(System::Byte channel, u32int index);
		void play(System::Byte channel);
		void stop(System::Byte channel);
		void pause(System::Byte channel);
		void setCue(System::Byte channel, u32int index);
		void setIntro(System::Byte channel, u32int index);
		void moveToPosition(System::Byte channel, u32int value);
		void setVolume(System::Byte channel, float value);

		/** PLAYLIST actions **/
		void addNote(System::Byte channel, System::String^ note) {};
		void addFile(System::Byte channel, u32int directoryIndex, System::String^ filename);
		void addSearchItem(System::Byte channel, u32int value);
		void deleteItem(System::Byte channel, u32int index);
		void moveItemTo(System::Byte channel, u32int oldIndex, u32int newIndex);
		void getPlaylist(System::Byte channel);
		void resetPlaylist(System::Byte channel);
		void copyItem(System::Byte channel, u32int fromIndex, u32int toChannel);

		/** SYSTEM actions **/
		void refreshDir(System::Byte directoryNumber);
		void synchronize();
		void synchronizeChatters();

		/** DATABASE actions **/
		bool searchMusicLib(System::String^ artist, System::String^ title, int trackid, int page);
		LibraryTrack^ getLibraryTrack(int index);
		void setupDatabaseConnection();
		bool executeQuery(System::String^ sql);
		void getShows(System::String^ username, bool newShowsOnly);
		void getListings(int showid);
		void assignListing(int channel, int listingid);

		/** CONFIG actions **/
		void sendOption(int optionid);
		void sendAllOptions();
		void sendAllOptionChoices(u32int optionid);
		/** 
		 *  Sending config settings is static such that updates can be sent from
		 *  other parts of the server
		**/
	public:
		static void sendOptionConfigSettings(int optionid, bool shouldBroadcast, ClientInstance^ c);
		
	private:
		void sendAllConfigSettings();
		void sendConfigOption(System::String^ optionName);
		void setConfigValue(u32int optionid, int index, u32int type);
		void sendAllUsers();
		void sendAllPermissionCodes();
		void sendUser(System::String^ username);
		void addUser(System::String^ username, System::String^ password);
		void removeUser(System::String^ username);
		void setPassword(System::String^ username, System::String^ password);
		void grantPermission(System::String^ username, UserPermission permission);
		void revokePermission(System::String^ username, UserPermission permission);
		void getIPRestrictions();
		void alterIPRestriction(Command cmd, System::String^ ipaddress, u32int mask);

		/** Private per client variables **/

		NpgsqlConnection^  bapsDB;
		System::Data::DataSet ^  bapsDataset;

		NpgsqlConnection^ recordlibDB;
		System::Data::DataSet ^ recordlibDataset;

		/** The handle for the ControlLoop thread **/
		System::Threading::Thread^ clientControlThread;
		/** The Socket connection for this client **/
		ServerSocket^ connection;
		/** Flag to say whether this client wants automatic updates **/
		bool autoUpdate;
		/** Flag to say whether this client wants to receive messages (chat) **/
		bool receiveChat;
		/** Flag to say if the client is dead **/
		bool dead;
		/** Mutex to ensure that onyl one thread is sending data at once **/
		System::Threading::Mutex^ sendMutex;
		/** Current user security info **/
		UserManager^ userInfo;
		/** Flags to indicate how record library results should be ordered **/
		int libraryOrderBy;
		int libraryAscDes;

	};
};