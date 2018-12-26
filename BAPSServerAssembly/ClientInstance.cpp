#include "stdafx.h"
#include "LogManager.h"
#include "ClientInstance.h"
#include "UserManager.h"
#include "EmailWrapper.h"

using namespace BAPSServerAssembly;

/**
 *  This file contains the shared helper functions and public functions for ClientInstance
 **/

ClientInstance::ClientInstance()
{
	/** Setup the Mutex to avoid multiple threads sending at the same time.
	 *  This is not implicitly locked in ServerSocket so that groups of sends
	 *  can be enforced
	 **/
	sendMutex = gcnew System::Threading::Mutex();
	/** Use default ServerSocket constructor. This allows for it being the destination of an accept() **/
	connection = gcnew ServerSocket();

	/** Client is not dead, is not wanting automatic updates and is at the end of the list of clients **/
	dead =false;
	autoUpdate = false;
	receiveChat = false;
	nextClient = nullptr;
	/** Blank user information **/
	userInfo = gcnew UserManager();

	recordlibDB = nullptr;
	libraryOrderBy = BAPSNET_ORDER_BYARTIST;
	libraryAscDes = BAPSNET_ORDER_ASCENDING;
	/** Create the controlLoop thread so that the current thread can go on doing what it wants to do **/
	clientControlThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this,&ClientInstance::clientControlLoop));
	try
	{
		clientControlThread->Start();
	}
	catch (System::Exception^ e)
	{
		/** Security or Out of Space exception has been thrown (probably)**/
		dead = true;
		LogManager::write(System::String::Concat("Unable to start client thread:\n", e->Message, "Stack Trace:\n",e->StackTrace),
						  LOG_ERROR,
						  LOG_OBJECTS);
	}
}

ClientInstance::~ClientInstance()
{
	/** Client is definitely dead **/
	dead = true;
	/** Mark all of the database variables as null - for easier GC **/
	if (recordlibDB != nullptr)
	{
		recordlibDB->Close();
	}
	recordlibDataset = nullptr;
	if (bapsDB != nullptr)
	{
		bapsDB->Close();
	}
	bapsDataset = nullptr;

	/** Destroy the control thread (hopefully this will cleanly exit before this **/
	if (clientControlThread != nullptr)
	{
		clientControlThread->Abort();
		clientControlThread->Join();
		clientControlThread = nullptr;
	}

	/** Destroy the user information **/
	if (userInfo != nullptr)
	{
		delete userInfo;
		userInfo = nullptr;
	}
	/** remove the connection **/
	delete connection;
	connection = nullptr;
}

void ClientInstance::clientControlLoop()
{
	/** We allow all Socket Exceptions to bubble back to this point so that the thread can abort **/
	try 
	{  
		/** Get the next connection request **/
		System::Net::IPAddress^ address = ClientManager::getServer()->accept(connection);


		/** Start a new client to deal with future connection requests **/
		/** Must hold the client lock before adding a new client **/
		ClientManager::getClientLock();
		nextClient = gcnew ClientInstance();
		ClientManager::releaseClientLock();

		System::String^ greeting = "~~~~~ Welcome to BAPS2 ~~~~~~\n\r~ press enter to begin ~\n\r~ press enter to begin ~\n\r~ press enter to begin ~\n\r~ ~~~~~~=~~~~~~ ~";
		/** 
		 *  Greet the new client regardless of whether it is is binary or not,
		 *  The greeting is carefully constructed such that the length is equal
		 *  to the ascii character '~' so that non binary clients get nice greetings
		**/
		connection->send(greeting);

		/** 
		 *  Now we expect the client to tell us exactly what kind of connection
		 *  it is. The Command to describe a binary connection is well out of the
		 *  range of valid ascii characters
		**/
 		Command connType = connection->receiveC();

		/** Everything not binary is... telnet/text based **/
		if (connType != (Command)(BAPSNET_SYSTEM | BAPSNET_SETBINARYMODE))
		{
			/** Unsupported for now **/
			LogManager::write("Text mode client connected -- Killing", LOG_INFO, LOG_COMMS);
			connection->send("Due to can't-be-bothered-itus the text mode connection system is not currently implemented\n");
			dead=true;
		}
		else
		{
			/** Get the length of the set binary mode command **/
			connection->receiveI();
			/** Send this as the seed for the encrypted password auth **/
			connection->send((Command)(BAPSNET_SYSTEM | BAPSNET_SEED));
			/** Send the length of the command **/
			connection->send((u32int)userInfo->getSeed()->Length+4);
			/** Send the seed **/
			connection->send(userInfo->getSeed());

			LoginResult authenticated = LR_USERNOTEXIST;
			/**
			*  Keep trying to authenticate the client, use exception mechanism
			*  for the case when the client quits
			**/
			while (authenticated != LR_SUCCESS)
			{
				Command cmdReceived = connection->receiveC();
				if ((cmdReceived & (BAPSNET_SYSTEM | BAPSNET_LOGIN)) != (BAPSNET_SYSTEM | BAPSNET_LOGIN))
				{
					dead = true;
					authenticated = LR_SUCCESS;
					continue;
				}
				/** Get the length of the login command **/
				connection->receiveI();
				/** Client will send username and encrypted password - return result value**/
				authenticated = userInfo->login(connection->receiveS(), connection->receiveS(), address);

				/** Inform the client of the result - with description **/
				connection->send((Command)(BAPSNET_SYSTEM | BAPSNET_LOGINRESULT | authenticated));
				/** Send the length of the description (const cast to remove const'ness and allow for get_length to work **/
				connection->send((u32int)const_cast<System::String^>(UserManager::loginResultText[authenticated])->Length);
				/** Send the description **/
				connection->send(UserManager::loginResultText[authenticated]);
			}
		}

		/** The work loop -- keep decoding Commands forever... **/
		while (!dead)
		{	
			decodeCommand(connection->receiveC());
		}
	}
	catch (System::Net::Sockets::SocketException^ e) 
	{
		/** Client application may have abruptly disappeared **/
		LogManager::write(System::String::Concat("clientControlLoop, Socket exception caught:\n", e->Message, "\n\nStack Trace:\n",e->StackTrace), LOG_ERROR, LOG_COMMS);
	}
	catch (System::ObjectDisposedException^ e) 
	{
		/** Client application may have closed gracefully but not warned us, or
		 *  our connection has been closed by the ClientManager
		 **/
		LogManager::write(System::String::Concat("clientControlLoop, Object Disposed exception caught:\n", e->Message, "\n\nStack Trace:\n",e->StackTrace), LOG_ERROR, LOG_COMMS);
	}
	catch (System::InvalidOperationException^ e) 
	{
		/** Bad programming and poor exception handling might get us here **/
		LogManager::write(System::String::Concat("clientControlLoop, Invalid operation exception caught:\n", e->Message, "\n\nStack Trace:\n",e->StackTrace), LOG_ERROR, LOG_COMMS);
	}
	catch (System::Threading::AbandonedMutexException^ ame)
	{
		/** Serious program flaw... mutex's should always be correctly owned. Even if we escape via an
			exception from a protected block of code the system should be in a valid state **/
		LogManager::write(System::String::Concat("clientControlLoop, AbandonedMutexException received serious program flaw detected:\n", ame->Message, "Stack Trace:\n",ame->StackTrace), LOG_ERROR, LOG_OBJECTS);
	}
	try
	{
		ClientManager::releaseMessageLock();
		LogManager::write(System::String::Concat("We have had to drop the message mutex: ",lastcmd.ToString()), LOG_WARNING, LOG_OBJECTS);

	}
	catch (System::ApplicationException^)
	{
		/** Nothing as we should not have held the lock in the first place.. this is normally what happens **/
	}

	dead = true;
}

void ClientInstance::decodeCommand(Command cmdReceived)
{
	lastcmd = cmdReceived;
	connection->receiveI();
	/** Managed c++ doesn't support bitfields... so I made them the old fashioned way **/
	/** Mask the uninteresting bits and switch on the rest **/
	switch (cmdReceived & BAPSNET_GROUPMASK)
	{
	case BAPSNET_PLAYBACK:
		switch (cmdReceived & BAPSNET_PLAYBACK_OPMASK)
		{
		case BAPSNET_PLAY:
			play(cmdReceived & BAPSNET_PLAYBACK_CHANNELMASK);
			break;
		case BAPSNET_STOP:
			stop(cmdReceived & BAPSNET_PLAYBACK_CHANNELMASK);
			break;
		case BAPSNET_PAUSE:
			pause(cmdReceived & BAPSNET_PLAYBACK_CHANNELMASK);
			break;
		case BAPSNET_POSITION:
			if (ISFLAGSET(cmdReceived,BAPSNET_PLAYBACK_MODEMASK))
			{
				// WORK NEEDED: getPosition
			}
			else
			{
				moveToPosition(cmdReceived & BAPSNET_PLAYBACK_CHANNELMASK, connection->receiveI());
			}
			break;
		case BAPSNET_VOLUME:
			if (ISFLAGSET(cmdReceived,BAPSNET_PLAYBACK_MODEMASK))
			{
				// WORK NEEDED: getVolume
			}
			else
			{
				setVolume(cmdReceived & BAPSNET_PLAYBACK_CHANNELMASK, connection->receiveF());
			}
			break;
		case BAPSNET_LOAD:
			if (ISFLAGSET(cmdReceived,BAPSNET_PLAYBACK_MODEMASK))
			{
				// WORK NEEDED: getLoadedItem
			}
			else
			{
				loadFile(cmdReceived & BAPSNET_PLAYBACK_CHANNELMASK, connection->receiveI());
			}
			break;
		case BAPSNET_CUEPOSITION:
			if (ISFLAGSET(cmdReceived,BAPSNET_PLAYBACK_MODEMASK))
			{
				// WORK NEEDED: getCuePosition
			}
			else
			{
				setCue(cmdReceived & BAPSNET_PLAYBACK_CHANNELMASK, connection->receiveI());
			}
			break;
		case BAPSNET_INTROPOSITION:
			if (ISFLAGSET(cmdReceived,BAPSNET_PLAYBACK_MODEMASK))
			{
				// WORK NEEDED: getCuePosition
			}
			else
			{
				setIntro(cmdReceived & BAPSNET_PLAYBACK_CHANNELMASK, connection->receiveI());
			}
			break;
		default:
			LogManager::write(System::String::Concat("Received unknown Command, Possibly a deformed PLAYBACK: ", cmdReceived.ToString()), LOG_ERROR, LOG_COMMS);
			dead = true;
			break;
		}
		break;
	case BAPSNET_PLAYLIST:
		/* mattbw 2014-01-10: Separate this into its own function. */
		decodePlaylistCommand(cmdReceived);
		break;
	case BAPSNET_BTEXT:
		switch (cmdReceived & BAPSNET_TEXT_OPMASK)
		{
		case BAPSNET_AUTOTXTON:
			/** WORK NEEDED: Work on text message interface **/
			break;
		case BAPSNET_AUTOTXTOFF:
			/** WORK NEEDED: Work on text message interface **/
			break;
		case BAPSNET_SENDTXTLIST:
			/** WORK NEEDED: Work on text message interface **/
			break;
		case BAPSNET_READ:
			/** WORK NEEDED: Work on text message interface **/
			break;
		case BAPSNET_UNREAD:
			/** WORK NEEDED: Work on text message interface **/
			break;
		default:
			LogManager::write(System::String::Concat("Received unknown Command, Possibly a deformed BTEXT: ", cmdReceived.ToString()), LOG_ERROR, LOG_COMMS);
			dead = true;
			break;
		}
		break;
	case BAPSNET_DATABASE:
		switch (cmdReceived & BAPSNET_DATABASE_OPMASK)
		{
		case BAPSNET_LIBRARYSEARCH:
			{
				bool mayBeDirty = ISFLAGSET(cmdReceived & BAPSNET_DATABASE_VALUEMASK, BAPSNET_LIBRARY_MAYBEDIRTY);
				System::String^ artist = connection->receiveS();
				System::String^ title = connection->receiveS();
				int pageNum = connection->receiveI();
				searchMusicLib(artist, title, mayBeDirty, -1, pageNum);
			}
			break;
		case BAPSNET_LIBRARYORDERING:
			{
				libraryOrderBy = connection->receiveI();
				libraryAscDes = connection->receiveI();
			}
			break;
		case BAPSNET_GETSHOWS:
			{
				// WORK NEEDED: make all these constants
				bool newShowsOnly = ((cmdReceived & 0x4) == 0x4);
				switch (cmdReceived & 0x3)
				{
				case 0:
					getShows("TODAYS_SHOWS", newShowsOnly);
					break;
				case 1:
					getShows("system", newShowsOnly);
					break;
				case 2:
					getShows(connection->receiveS(), newShowsOnly);
					break;
				default:
					getShows("system", newShowsOnly);
					break;
				}
			}
			break;
		case BAPSNET_GETLISTINGS:
			getListings(connection->receiveI());
			break;
		case BAPSNET_ASSIGNLISTING:
			assignListing(cmdReceived & BAPSNET_DATABASE_VALUEMASK, connection->receiveI());
			break;
		default:
			LogManager::write(System::String::Concat("Received unknown Command, Possibly a deformed DATABASE: ", cmdReceived.ToString()), LOG_ERROR, LOG_COMMS);
			dead = true;
			break;
		}
		break;
	case BAPSNET_CONFIG:
		switch (cmdReceived & BAPSNET_CONFIG_OPMASK)
		{
		case BAPSNET_GETOPTIONS:
			sendAllOptions();
			break;
		case BAPSNET_GETOPTIONCHOICES:
			sendAllOptionChoices(connection->receiveI());
			break;
		case BAPSNET_GETCONFIGSETTINGS:
			sendAllConfigSettings();
			break;
		case BAPSNET_GETCONFIGSETTING:
			sendOptionConfigSettings(connection->receiveI(), false, this);
			break;
		case BAPSNET_GETOPTION:
			sendConfigOption(connection->receiveS());
			break;
		case BAPSNET_SETCONFIGVALUE:
			/** WORK NEEDED: comment all of these and recomment ones which receive outside of this function **/
			if ((cmdReceived & BAPSNET_CONFIG_USEVALUEMASK) == BAPSNET_CONFIG_USEVALUEMASK)
			{
                setConfigValue(connection->receiveI(), (cmdReceived&BAPSNET_CONFIG_VALUEMASK), connection->receiveI());
			}
			else
			{
                setConfigValue(connection->receiveI(), -1, connection->receiveI());
			}
			break;
		case BAPSNET_GETUSERS:
			sendAllUsers();
			break;
		case BAPSNET_GETPERMISSIONS:
			sendAllPermissionCodes();
			break;
		case BAPSNET_GETUSER:
			sendUser(connection->receiveS());
			break;
		case BAPSNET_ADDUSER:
			addUser(connection->receiveS(), connection->receiveS());
			break;
		case BAPSNET_REMOVEUSER:
			removeUser(connection->receiveS());
			break;
		case BAPSNET_SETPASSWORD:
			setPassword(connection->receiveS(), connection->receiveS());
			break;
		case BAPSNET_GRANTPERMISSION:
			grantPermission(connection->receiveS(), static_cast<UserPermission>(connection->receiveI()));
			break;
		case BAPSNET_REVOKEPERMISSION:
			revokePermission(connection->receiveS(), static_cast<UserPermission>(connection->receiveI()));
			break;
		case BAPSNET_GETIPRESTRICTIONS:
			getIPRestrictions();
			break;
		case BAPSNET_ALTERIPRESTRICTION:
			alterIPRestriction(cmdReceived, connection->receiveS(), connection->receiveI());
			break;
		default:
			LogManager::write(System::String::Concat("Received unknown Command, Possibly a deformed CONFIG: ", cmdReceived.ToString()), LOG_ERROR, LOG_COMMS);
			dead = true;
			break;
		}
		break;
	case BAPSNET_SYSTEM:
		switch (cmdReceived & BAPSNET_SYSTEM_OPMASK)
		{
		case BAPSNET_LISTFILES:
			refreshDir(cmdReceived & BAPSNET_PLAYLIST_CHANNELMASK);
			break;
		case BAPSNET_SENDMESSAGE:
			ClientManager::sendMessage(connection->receiveS(),connection->receiveS(),connection->receiveS());
			break;
		case BAPSNET_AUTOUPDATE:
			{
				bool intendAutoUpdate = ((cmdReceived & BAPSNET_SYSTEM_VALUEMASK & 1) == 1);
				/** If client reasserts a wish to be autoupdated we assume the client
					*  is totally cleaned out. WORK NEEDED: Have a 'clean data' Command
					**/
				if (intendAutoUpdate)
				{
					synchronize();
				}
				if (!receiveChat && ((cmdReceived & BAPSNET_SYSTEM_VALUEMASK & 2) == 2))
				{
					// Notify everyone that this user has arrived
					ClientManager::addToChat(getUsername());
					// send the list of chatters to this user
					synchronizeChatters();

				}
				break;
			}
		case BAPSNET_END:
			{
				/** RIP **/
				System::String^ reason = connection->receiveS();
				LogManager::write(System::String::Concat(getUsername(), " exited. Reason given: ", reason), LOG_INFO, LOG_COMMS);
				dead = true;
			}
			break;
		case BAPSNET_VERSION:
			{
				System::String^ author = "Matthew Fortune\n\nAudio Library: Dan Lambert\n\nMaintained By:\nMatthew Stratford (2018)\n";
				System::String^ version = System::Reflection::Assembly::GetExecutingAssembly()->GetName()->Version->ToString();
				Command cmd = BAPSNET_SYSTEM | BAPSNET_VERSION;
				ClientManager::send(this, cmd, version, __DATE__, __TIME__, author);
			}
			break;
		case BAPSNET_FEEDBACK:
			{
				System::String^ feedback = connection->receiveS();
				bool sent = EmailWrapper::sendEmail(feedback);
				int result = (sent)?0:1;
				Command cmd = BAPSNET_SYSTEM | BAPSNET_FEEDBACK;
				ClientManager::send(this, cmd, (u32int)result);
			}
			break;
		case BAPSNET_QUIT:
		{
			/** Used to restart the server from the config menu **/
			LogManager::write("Recieved BAPSNET_QUIT, restarting.", LOG_INFO, LOG_SYSTEM);
			Command cmd = BAPSNET_SYSTEM | BAPSNET_QUIT;
			/* Send 0 to signify this is an expected quit. */
			ClientManager::broadcast(cmd, (u32int) 0);
			dead = true;
			throw gcnew BAPSTerminateException("Server restarting. Triggered from BAPSNet.");
			break;
		}
		default:
			LogManager::write(System::String::Concat("Received unknown Command, Possibly a deformed SYSTEM: ", cmdReceived.ToString()), LOG_ERROR, LOG_COMMS);
			dead = true;
			break;
		}
		break;
	default:
		LogManager::write(System::String::Concat("Received unknown Command: ", cmdReceived.ToString()), LOG_ERROR, LOG_COMMS);
		dead = true;
		break;
	}
}

/* mattbw 2014-01-10: This was originally part of decodeCommand. */
void ClientInstance::decodePlaylistCommand(Command cmdReceived)
{
	System::Byte channel = cmdReceived & BAPSNET_PLAYLIST_CHANNELMASK;

	switch (cmdReceived & BAPSNET_PLAYLIST_OPMASK)
	{
	case BAPSNET_ADDITEM:
		switch (connection->receiveI())
		{
		case BAPSNET_VOIDITEM:
			// nothing
			break;
		case BAPSNET_FILEITEM:
			addFile(channel, connection->receiveI(), connection->receiveS());
			break;
		case BAPSNET_LIBRARYITEM:
			addSearchItem(channel, connection->receiveI());
			break;
		/* mattbw 2013-11-18: Allow for direct library item addition.
		 *
		 * This was added in order to allow new BAPS clients to supply their own
		 * library searching functions without having to go through BAPS, as is
		 * the case with BAPSNET_LIBRARYITEM.
		 */
		case BAPSNET_DIRECTLIBRARYITEM:
			addDirectLibraryItem(
				channel,                 // Channel ID
				connection->receiveI(),  // Record ID
				connection->receiveI(),  // Track ID
				connection->receiveS(),  // Title
				connection->receiveS()   // Artist
			);
			break;
		/* end 2013-11-18 */
		case BAPSNET_TEXTITEM:
			/* mattbw 2014-01-10: Implement this. */
			addTextItem(
				channel,                 // Channel ID
				connection->receiveS(),  // Summary
				connection->receiveS()   // Details
			);
			break;
		default:
			LogManager::write("Received unknown item type.", LOG_ERROR, LOG_COMMS);
			// WORK NEEDED: hmm
			break;
		}
		break;
	case BAPSNET_DELETEITEM:
		deleteItem(channel, connection->receiveI());
		break;
	case BAPSNET_MOVEITEMTO:
		moveItemTo(channel, connection->receiveI(), connection->receiveI());
		break;
	case BAPSNET_ITEM:
		if (ISFLAGSET(cmdReceived,BAPSNET_PLAYBACK_MODEMASK))
		{
			// WORK NEEDED: getItem
		}
		break;
	case BAPSNET_GETPLAYLIST:
		getPlaylist(channel);
		break;
	case BAPSNET_RESETPLAYLIST:
		resetPlaylist(channel);
		break;
	case BAPSNET_COPYITEM:
		copyItem(channel, connection->receiveI(), connection->receiveI());
		break;
	default:
		LogManager::write(System::String::Concat("Received unknown Command, Possibly a deformed PLAYLIST: ", cmdReceived.ToString()), LOG_ERROR, LOG_COMMS);
		dead = true;
		break;
	}
}

