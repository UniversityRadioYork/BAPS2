#include "stdafx.h"
#include "BAPSPresenterMain.h"
#include "LoginDialog.h"
#include "ConfigCache.h"
#include "UtilityMacros.h"
#include "Messages.h"
#include "ConfigManager.h"

#undef MessageBox

using namespace BAPSPresenter;

BAPSPresenterMain::BAPSPresenterMain(void)
{
	/** Initialise the config manager **/
	ConfigManager::initConfigManager();
	/** Specify the application has not crashed **/
	crashed = false;
	/** Create the login form instance **/
	LoginDialog^ login = gcnew LoginDialog();
	/** This flag defines success of the login procedure
		(along with the implicit knowledge that the server is ready)
	**/
	bool authenticated = false;
	/** If a server error occurs we set this flag so that the connection is
		attempted again
	**/
	bool wasServerError = false;
	/** Each session with a server has a security string used to encrypt secrets **/
	System::String^ randomSecurityString;
	/** Keep looping until we authenticate, throw an exception or exit forcefully **/
	while (!authenticated)
	{
		/** If we cancel login we can assume we wish to abort as there is nothing
			else to do
		**/
		if (login->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
		{
			/** Quit! **/
			System::Diagnostics::Process::GetCurrentProcess()->Kill();
		}
		/** If either the server or port have been changed since last attempt
			we need to reconnect.
		**/
		if (login->needsToConnect() || wasServerError)
		{
			try 
			{
				/** Destroy old connection (if present) **/
				if (clientSocket != nullptr)
				{
					delete clientSocket;
				}
			}
			catch ( System::Exception^ )
			{
				/** Do nothing **/
			}
			try
			{
				/** Attempt to make a connection to the specified server **/
				clientSocket = gcnew ClientSocket(login->getServer(), login->getPort());
			}
			catch (System::Exception^ e)
			{
				/** If an error occurs just give the exception message and start again **/
				System::String^ errorMessage = System::String::Concat("System Error:\n", e->Message, "\nStack Trace:\n", e->StackTrace);
				System::Windows::Forms::MessageBox::Show(errorMessage, "Server error:", System::Windows::Forms::MessageBoxButtons::OK);
				logError(errorMessage);
				wasServerError = true;
				continue;
			}
			/** Receive the greeting string, this is the only communication
				that does not follow the 'command' 'command-length' 'argument1'...
				structure
			**/
			System::String^ greeting = clientSocket->receiveS();
			/** Let the server know we are a binary client **/
			clientSocket->send((Command)(BAPSNET_SYSTEM | BAPSNET_SETBINARYMODE));
			/** Specify the length of the command **/
			clientSocket->send((u32int)0);
			/** Receive what should be the SEED command **/
			Command seedCmd = clientSocket->receiveC();
			/** Receive the length of the seed command **/
			clientSocket->receiveI();
			/** Verify the server is sending what we expect **/
			if ((seedCmd & (BAPSNET_GROUPMASK | BAPSNET_SYSTEM_OPMASK)) != (BAPSNET_SYSTEM | BAPSNET_SEED))
			{
				System::Windows::Forms::MessageBox::Show("Server login procedure is not compatible with this client.", "Server error:", System::Windows::Forms::MessageBoxButtons::OK);
				/** Notify a server error so a reconnect is attempted **/
				wasServerError = true;
				continue;
			}
			else
			{
				/** Receive the SEED **/
				randomSecurityString = clientSocket->receiveS();
			}
			/** Clear any server error **/
			wasServerError = false;
		}
		/** Encrypt the password **/
		System::String^ securedPassword = md5sum(System::String::Concat(randomSecurityString, md5sum(login->getPassword())));
		/** Send LOGIN command **/
		clientSocket->send((Command)(BAPSNET_SYSTEM | BAPSNET_LOGIN|0));
		/** Send correct command length **/
		clientSocket->send((u32int)(login->getUsername()->Length+securedPassword->Length));
		/** Send username **/
		clientSocket->send(login->getUsername());
		/** Send encrypted password **/
		clientSocket->send(securedPassword);
		/** Receive what should be the login result **/
		Command authResult = clientSocket->receiveC();
		/** Verify it is what we expected **/
		if ((authResult & (BAPSNET_GROUPMASK | BAPSNET_SYSTEM_OPMASK)) != (BAPSNET_SYSTEM | BAPSNET_LOGINRESULT))
		{
			System::Windows::Forms::MessageBox::Show("Server login procedure is not compatible with this client.", "Server error:", System::Windows::Forms::MessageBoxButtons::OK);
			/** This is a server error as the server is incompatible with this client **/
			wasServerError = true;
			continue;
		}
		else
		{
			/** Receive the result command length **/
			clientSocket->receiveI();
			/** Receive the description of the result code **/
			System::String^ description = clientSocket->receiveS();
			/** Check the value for '0' meaning success **/
			authenticated = ((authResult & BAPSNET_SYSTEM_VALUEMASK) == 0);
			if (!authenticated)
			{
				/** Tell the client of any failure **/
				System::Windows::Forms::MessageBox::Show(description, "Login error:", System::Windows::Forms::MessageBoxButtons::OK);
			}
		}
	}
	username = login->getUsername();
	/** Do the form initialization **/
	InitializeComponent();
	
	/** Tag codes for the controls so they can be identified at runtime **/
	System::Object  ^number0 = safe_cast<System::Object^>(0);
	System::Object  ^number1 = 1;
	System::Object  ^number2 = 2;

	/** Array initialisation so that controls can be found by channel
		number at runtime
	**/
	trackLengthText	   = gcnew array<BAPSLabel^>(3);
	trackLengthText[0] = Channel0Length;
	trackLengthText[1] = Channel1Length;
	trackLengthText[2] = Channel2Length;
	Channel0Length->Tag = gcnew CountDownState(0);
	Channel1Length->Tag = gcnew CountDownState(1);
	Channel2Length->Tag = gcnew CountDownState(2);

	timeLeftText	   = gcnew array<BAPSLabel^>(3);
	timeLeftText[0]    = Channel0TimeLeft;
	timeLeftText[1]    = Channel1TimeLeft;
	timeLeftText[2]    = Channel2TimeLeft;
	timeGoneText	   = gcnew array<BAPSLabel^>(3);
	timeGoneText[0]    = Channel0TimeGone;
	timeGoneText[1]    = Channel1TimeGone;
	timeGoneText[2]    = Channel2TimeGone;
	/*volumeBar		   = gcnew array<System::Windows::Forms::TrackBar^>(3);
	volumeBar[0]       = Channel0VolumeBar;
	Channel0VolumeBar->Tag = number0;
	volumeBar[1]       = Channel1VolumeBar;
	Channel1VolumeBar->Tag = number1;
	volumeBar[2]       = Channel2VolumeBar;
	Channel2VolumeBar->Tag = number2;*/

	channelPlay			= gcnew array<Windows::Forms::Button^>(3);
	channelPlay[0]		= Channel0Play;
	channelPlay[0]->Tag	= gcnew ChannelOperationLookup(0, BAPSNET_PLAY);
	channelPlay[1]		= Channel1Play;
	channelPlay[1]->Tag	= gcnew ChannelOperationLookup(1, BAPSNET_PLAY);
	channelPlay[2]		= Channel2Play;
	channelPlay[2]->Tag	= gcnew ChannelOperationLookup(2, BAPSNET_PLAY);

	channelPause		= gcnew array<Windows::Forms::Button^>(3);
	channelPause[0]		= Channel0Pause;
	channelPause[0]->Tag	= gcnew ChannelOperationLookup(0, BAPSNET_PAUSE);
	channelPause[1]		= Channel1Pause;
	channelPause[1]->Tag	= gcnew ChannelOperationLookup(1, BAPSNET_PAUSE);
	channelPause[2]		= Channel2Pause;
	channelPause[2]->Tag	= gcnew ChannelOperationLookup(2, BAPSNET_PAUSE);

	channelStop			= gcnew array<Windows::Forms::Button^>(3);
	channelStop[0]		= Channel0Stop;
	channelStop[0]->Tag	= gcnew ChannelOperationLookup(0, BAPSNET_STOP);
	channelStop[1]		= Channel1Stop;
	channelStop[1]->Tag	= gcnew ChannelOperationLookup(1, BAPSNET_STOP);
	channelStop[2]		= Channel2Stop;
	channelStop[2]->Tag	= gcnew ChannelOperationLookup(2, BAPSNET_STOP);

	trackList		   = gcnew array<BAPSPresenter::TrackList^>(3);
	trackList[0]	   = trackList0;
	trackList[1]	   = trackList1;
	trackList[2]	   = trackList2;

	directoryList	   = gcnew array<System::Windows::Forms::ListBox^>(3);
	directoryList[0]   = Directory0;
	directoryList[1]   = Directory1;
	directoryList[2]   = Directory2;
	directoryList[0]->Tag   = number0;
	directoryList[1]->Tag   = number1;
	directoryList[2]->Tag   = number2;

	directoryRefresh	= gcnew array<System::Windows::Forms::Button^>(3);
	directoryRefresh[0] = Directory0Refresh;
	directoryRefresh[1] = Directory1Refresh;
	directoryRefresh[2] = Directory2Refresh;
	directoryRefresh[0]->Tag = number0;
	directoryRefresh[1]->Tag = number1;
	directoryRefresh[2]->Tag = number2;

	loadedText		   = gcnew array<System::Windows::Forms::Label^>(3);
	loadedText[0]	   = Channel0LoadedText;
	loadedText[1]	   = Channel1LoadedText;
	loadedText[2]	   = Channel2LoadedText;
	
	trackTime			= gcnew array<TrackTime^>(3);
	trackTime[0]		= trackTime0;
	trackTime[1]		= trackTime1;
	trackTime[2]		= trackTime2;

	trackTime[0]->Dock = System::Windows::Forms::DockStyle::None;
	trackTime[1]->Dock = System::Windows::Forms::DockStyle::None;
	trackTime[2]->Dock = System::Windows::Forms::DockStyle::None;
	this->Controls->Add(trackTime[0]);
	this->Controls->Add(trackTime[1]);
	this->Controls->Add(trackTime[2]);
	trackTime[0]->PositionChanged += gcnew System::EventHandler(this, &BAPSPresenterMain::positionChanged);
	trackTime[1]->PositionChanged += gcnew System::EventHandler(this, &BAPSPresenterMain::positionChanged);
	trackTime[2]->PositionChanged += gcnew System::EventHandler(this, &BAPSPresenterMain::positionChanged);
	trackTime[0]->CuePositionChanged += gcnew System::EventHandler(this, &BAPSPresenterMain::cuePositionChanged);
	trackTime[1]->CuePositionChanged += gcnew System::EventHandler(this, &BAPSPresenterMain::cuePositionChanged);
	trackTime[2]->CuePositionChanged += gcnew System::EventHandler(this, &BAPSPresenterMain::cuePositionChanged);
	trackTime[0]->IntroPositionChanged += gcnew System::EventHandler(this, &BAPSPresenterMain::introPositionChanged);
	trackTime[1]->IntroPositionChanged += gcnew System::EventHandler(this, &BAPSPresenterMain::introPositionChanged);
	trackTime[2]->IntroPositionChanged += gcnew System::EventHandler(this, &BAPSPresenterMain::introPositionChanged);
	
	loadImpossibleTimer = gcnew array<System::Windows::Forms::Timer^>(3);
	loadImpossibleTimer[0] = gcnew System::Windows::Forms::Timer();
	loadImpossibleTimer[0]->Interval=70;
	loadImpossibleTimer[0]->Tag = gcnew ChannelTimeoutStruct(0, 10);
	loadImpossibleTimer[0]->Tick += gcnew System::EventHandler(this, &BAPSPresenterMain::loadImpossibleFlicker);
	loadImpossibleTimer[1] = gcnew System::Windows::Forms::Timer();
	loadImpossibleTimer[1]->Interval=70;
	loadImpossibleTimer[1]->Tag = gcnew ChannelTimeoutStruct(1, 10);
	loadImpossibleTimer[1]->Tick += gcnew System::EventHandler(this, &BAPSPresenterMain::loadImpossibleFlicker);
	loadImpossibleTimer[2] = gcnew System::Windows::Forms::Timer();
	loadImpossibleTimer[2]->Interval=70;
	loadImpossibleTimer[2]->Tag = gcnew ChannelTimeoutStruct(2, 10);
	loadImpossibleTimer[2]->Tick += gcnew System::EventHandler(this, &BAPSPresenterMain::loadImpossibleFlicker);
	nearEndTimer = gcnew array<System::Windows::Forms::Timer^>(3);
	nearEndTimer[0] = gcnew System::Windows::Forms::Timer();
	nearEndTimer[0]->Interval=100;
	nearEndTimer[0]->Tag = safe_cast<System::Object^>(0);
	nearEndTimer[0]->Tick += gcnew System::EventHandler(this, &BAPSPresenterMain::nearEndFlash);
	nearEndTimer[1] = gcnew System::Windows::Forms::Timer();
	nearEndTimer[1]->Interval=100;
	nearEndTimer[1]->Tag = 1;
	nearEndTimer[1]->Tick += gcnew System::EventHandler(this, &BAPSPresenterMain::nearEndFlash);
	nearEndTimer[2] = gcnew System::Windows::Forms::Timer();
	nearEndTimer[2]->Interval=100;
	nearEndTimer[2]->Tag = 2;
	nearEndTimer[2]->Tick += gcnew System::EventHandler(this, &BAPSPresenterMain::nearEndFlash);
	
	countdownTimer = gcnew System::Windows::Forms::Timer();
	countdownTimer->Interval = 200;
	countdownTimer->Tick += gcnew System::EventHandler(this, &BAPSPresenterMain::countdownTick);
	countdownTimer->Start();

	/** We are not dead yet **/
	dead = false;
	/** Set the form handles to null **/
	recordLibrarySearch = nullptr;
	configDialog = nullptr;
	loadShowDialog = nullptr;
	securityDialog = nullptr;
	about = nullptr;
	textDialog = gcnew TextDialog(this,"Write on me");

	/** Initialize the config cache **/
	ConfigCache::initConfigCache();
	/** Create a message queue for sending commands to the server **/
	msgQueue = gcnew System::Collections::Queue();
	/** It needs to be synchronized so that enqueue and dequeue are atomic **/
	msgQueue = System::Collections::Queue::Synchronized(msgQueue);
	/** Add the autoupdate message onto the queue (chat(2) and general(1)) **/
	Command cmd = BAPSNET_SYSTEM | BAPSNET_AUTOUPDATE | 2 | 1;
	msgQueue->Enqueue(gcnew ActionMessage(cmd));
	int i;
	for (i = 0 ; i < 3 ; i++)
	{
		/** Add the refresh folder onto the queue **/
		cmd = BAPSNET_SYSTEM | BAPSNET_LISTFILES | i;
		msgQueue->Enqueue(gcnew ActionMessage(cmd));
	}

	/** Show or hide the volume controls depending on the config setting **/
	/*bool showVolume = (System::String::Compare(ConfigManager::getConfigValueString("ShowVolume", "No"),"Yes") == 0);
	showVolumeControls(showVolume);*/

	/** Enable or disable the timers depending on the config setting **/
	bool enableTimers = (System::String::Compare(ConfigManager::getConfigValueString("EnableTimers", "No"),"Yes") == 0);
	enableTimerControls(enableTimers);

	/** Start the receive thread so we are ready for the autoupdate messages **/ 
	receiverThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &BAPSPresenterMain::receiverFunc));
	receiverThread->Start();
	/** Start the sender thread last so that everything is ready for the autoupdate
		message to be sent and acted upon by the server
	**/
	senderThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &BAPSPresenterMain::senderFunc));
	senderThread->Start();


}

BAPSPresenterMain::~BAPSPresenterMain()
{
	if (msgQueue != nullptr)
	{
		/** When we die it is only fair to tell the server **/
		Command cmd = BAPSNET_SYSTEM | BAPSNET_END;
		msgQueue->Enqueue(gcnew ActionMessageString(cmd, "Normal Termination"));
		/** Wait 500ms for the command to be sent **/
		int timeout = 500;
		while (msgQueue->Count >0 && timeout>0)
		{
			System::Threading::Thread::Sleep(1);
			timeout--;
		}
	}
	/** Notify the send/receive threads they should die **/
	dead = true;
	/** Empty the config cache **/
	ConfigCache::closeConfigCache();
	/** Force the receive thread to abort FIRST so that we cant receive
		any messages that need automatic responses **/
	if (receiverThread != nullptr)
	{
		receiverThread->Abort();
		receiverThread->Join();
	}
	/** Force the sender thread to die (should be dead already) **/
	if (senderThread != nullptr)
	{
		senderThread->Abort();
		senderThread->Join();
	}
	/** Close the connection properly **/
	if (clientSocket != nullptr)
	{
		delete clientSocket;
		clientSocket = nullptr;
	}
	if (components)
	{
		delete components;
	}
}
void BAPSPresenterMain::notifyCommsError(System::String^ description)
{
	/** On Communications errors this is called to notify the user **/
	/** Only current option is to die **/
	dead = true;
	System::Windows::Forms::MessageBox::Show(System::String::Concat(description, "\nClick OK to restart the Presenter Interface.\nPlease notify support that an error occurred."), "System error:", System::Windows::Forms::MessageBoxButtons::OK);
	logError(description);
	crashed = true;
	this->Close();
}
void BAPSPresenterMain::sendNotifyCommsError(System::String^ description)
{
	if (!crashed)
	{
		MethodInvokerStr^ mi = gcnew MethodInvokerStr(this, &BAPSPresenterMain::notifyCommsError);
		array<System::Object^>^ dd = gcnew array<System::Object^>(1) {description};
		this->BeginInvoke(mi,dd);
	}
}
void BAPSPresenterMain::receiverFunc()
{
	/** Simple loop, just keep decoding **/
#ifndef _DEBUG
	try 
	{
#endif
		while (!dead)
		{	
			decodeCommand(clientSocket->receiveC());
		}
#ifndef _DEBUG
	}
	catch (System::Exception^ e) 
	{
		if (!dead)
		{
			/** If we receive an exception we assume it to be a bad thing **/
			sendNotifyCommsError(System::String::Concat("Receiver Loop Failed, server may have died:\n", e->Message, "\nStack Trace:\n", e->StackTrace));
		}
	}
#endif
}

void BAPSPresenterMain::decodeCommand(Command cmdReceived)
{
	/** Receive the command length **/
	clientSocket->receiveI();
	/** Due to lack of bitfield support in .net we do this the old fashioned
		way with masks and &'s or |'s
	**/
	switch (cmdReceived & BAPSNET_GROUPMASK)
	{
	case BAPSNET_PLAYBACK:
		switch (cmdReceived & BAPSNET_PLAYBACK_OPMASK)
		{
		case BAPSNET_PLAY:
		case BAPSNET_PAUSE:
		case BAPSNET_STOP:
			{
				MethodInvokerObjObj^ mi = gcnew MethodInvokerObjObj(this, &BAPSPresenterMain::showChannelOperation);
				array<System::Object^>^ dd = gcnew array<System::Object^>(2) {cmdReceived & BAPSNET_PLAYBACK_CHANNELMASK, cmdReceived & BAPSNET_PLAYBACK_OPMASK};
				this->Invoke(mi, dd);
			}
			break;
		case BAPSNET_POSITION:
			{
				int position = clientSocket->receiveI();
				MethodInvokerObjObj^ mi = gcnew MethodInvokerObjObj(this, &BAPSPresenterMain::showPosition);
				array<System::Object^>^ dd = gcnew array<System::Object^>(2) {cmdReceived & BAPSNET_PLAYBACK_CHANNELMASK, position};
				this->Invoke(mi, dd);
			}
			break;
		case BAPSNET_VOLUME:
			{
				float value = clientSocket->receiveF();
				//MethodInvokerObjObj^ mi = gcnew MethodInvokerObjObj(this, &BAPSPresenterMain::showVolume);
				//array<System::Object^>^ dd = gcnew array<System::Object^>(2) {cmdReceived & BAPSNET_PLAYBACK_CHANNELMASK, value};
				//this->Invoke(mi, dd);
			}
			break;
		case BAPSNET_LOAD:
			{
				int channel = cmdReceived & BAPSNET_PLAYLIST_CHANNELMASK;
				int index = clientSocket->receiveI();
				int type = clientSocket->receiveI();
				System::String^ description = clientSocket->receiveS();
				array<System::Object^>^ dd;
				switch (type)
				{
				case BAPSNET_FILEITEM:
				case BAPSNET_LIBRARYITEM:
					{
						int duration = clientSocket->receiveI();
						MethodInvokerObjObj^ mi2 = gcnew MethodInvokerObjObj(this, &BAPSPresenterMain::showDuration);
						dd = gcnew array<System::Object^>(2) {cmdReceived & BAPSNET_PLAYBACK_CHANNELMASK, duration};
						this->Invoke(mi2, dd);
						mi2 = gcnew MethodInvokerObjObj(this, &BAPSPresenterMain::showPosition);
						dd = gcnew array<System::Object^>(2) {cmdReceived & BAPSNET_PLAYBACK_CHANNELMASK, safe_cast<System::Object^>(0)};
						this->Invoke(mi2, dd);
					}
				case BAPSNET_VOIDITEM:
					{
						MethodInvokerObjObjObjStr^ mi = gcnew MethodInvokerObjObjObjStr(this, &BAPSPresenterMain::showLoadedItem);
						array<System::Object^>^ dd = gcnew array<System::Object^>(4) {cmdReceived & BAPSNET_PLAYLIST_CHANNELMASK, index, type, description};
						this->Invoke(mi, dd);
					}
					break;
				case BAPSNET_TEXTITEM:
					{
						System::String^ text = clientSocket->receiveS();
						MethodInvokerObjObjStrStr^ mi = gcnew MethodInvokerObjObjStrStr(this, &BAPSPresenterMain::showText);
						array<System::Object^>^ dd = gcnew array<System::Object^>(4) {channel, index, description, text};
						this->Invoke(mi, dd);
					}
					break;
				default:
					MethodInvokerObjObj^ mi = gcnew MethodInvokerObjObj(this, &BAPSPresenterMain::showDuration);
					dd = gcnew array<System::Object^>(2) {cmdReceived & BAPSNET_PLAYBACK_CHANNELMASK, safe_cast<System::Object^>(0)};
					this->Invoke(mi, dd);
					mi = gcnew MethodInvokerObjObj(this, &BAPSPresenterMain::showPosition);
					dd = gcnew array<System::Object^>(2) {cmdReceived & BAPSNET_PLAYBACK_CHANNELMASK, safe_cast<System::Object^>(0)};
					this->Invoke(mi, dd);
				}
			}
			break;
		case BAPSNET_CUEPOSITION:
			{
				int cuePosition = clientSocket->receiveI();
				MethodInvokerObjObj^ mi = gcnew MethodInvokerObjObj(this, &BAPSPresenterMain::showCuePosition);
				array<System::Object^>^ dd = gcnew array<System::Object^>(2) {cmdReceived & BAPSNET_PLAYBACK_CHANNELMASK, cuePosition};
				this->Invoke(mi, dd);
			}
			break;
		case BAPSNET_INTROPOSITION:
			{
				int introPosition = clientSocket->receiveI();
				MethodInvokerObjObj^ mi = gcnew MethodInvokerObjObj(this, &BAPSPresenterMain::showIntroPosition);
				array<System::Object^>^ dd = gcnew array<System::Object^>(2) {cmdReceived & BAPSNET_PLAYBACK_CHANNELMASK, introPosition};
				this->Invoke(mi, dd);
			}
			break;
		default:
			{
				/** ERROR **/
				sendNotifyCommsError("Received unknown command, possibly a malformed PLAYBACK.\n");
			}
			break;
		}
		break;
	case BAPSNET_PLAYLIST:
		switch (cmdReceived & BAPSNET_PLAYLIST_OPMASK)
		{
		case BAPSNET_ITEM:
			if (ISFLAGSET(cmdReceived,BAPSNET_PLAYLIST_MODEMASK))
			{
				int index = clientSocket->receiveI();
				int type = clientSocket->receiveI();
				System::String^ description = clientSocket->receiveS();
				MethodInvokerObjObjObjStr^ mi = gcnew MethodInvokerObjObjObjStr(this, &BAPSPresenterMain::addItem);
				array<System::Object^>^ dd = gcnew array<System::Object^>(4){cmdReceived & BAPSNET_PLAYLIST_CHANNELMASK, index, type, description};
				this->Invoke(mi, dd);
			}
			else
			{
				u32int count = clientSocket->receiveI();
			}
			break;
		case BAPSNET_MOVEITEMTO:
			{
				int indexFrom = clientSocket->receiveI();
				int indexTo = clientSocket->receiveI();
				MethodInvokerObjObjObj^ mi = gcnew MethodInvokerObjObjObj(this, &BAPSPresenterMain::moveItemTo);
				array<System::Object^>^ dd = gcnew array<System::Object^>(3) {cmdReceived & BAPSNET_PLAYLIST_CHANNELMASK, indexFrom, indexTo};
				this->Invoke(mi, dd);
			}
			break;
		case BAPSNET_DELETEITEM:
			{
				int index = clientSocket->receiveI();
				MethodInvokerObjObj^ mi = gcnew MethodInvokerObjObj(this, &BAPSPresenterMain::deleteItem);
				array<System::Object^>^ dd = gcnew array<System::Object^>(2) {cmdReceived & BAPSNET_PLAYLIST_CHANNELMASK, index};
				this->Invoke(mi, dd);
			}
			break;
		case BAPSNET_RESETPLAYLIST:
			{
				MethodInvokerObj^ mi = gcnew MethodInvokerObj(this, &BAPSPresenterMain::cleanPlaylist);
				array<System::Object^>^ dd = gcnew array<System::Object^>(1) {cmdReceived & BAPSNET_PLAYLIST_CHANNELMASK};
				this->Invoke(mi, dd);
			}
			break;
		default:
			{
				/** ERROR **/
				sendNotifyCommsError("Received unknown command, possibly a malformed PLAYLIST.\n");
			}
			break;
		}
		break;
	case BAPSNET_DATABASE:
		switch (cmdReceived & BAPSNET_DATABASE_OPMASK)
		{
		case BAPSNET_LIBRARYRESULT:
			{
				if (ISFLAGSET(cmdReceived,BAPSNET_DATABASE_MODEMASK))
				{
					int dirtyStatus = cmdReceived&BAPSNET_DATABASE_VALUEMASK;
					int resultid = clientSocket->receiveI();
					System::String^ description = clientSocket->receiveS();
					addLibraryResult(resultid, dirtyStatus, description);
				}
				else
				{
					int count = clientSocket->receiveI();
					setLibraryResultCount(count);
				}
			}
			break;
		case BAPSNET_LIBRARYERROR:
			{
				System::String^ description = clientSocket->receiveS();
				notifyLibraryError(cmdReceived & BAPSNET_DATABASE_VALUEMASK, description);
			}
			break;
		case BAPSNET_SHOW:
			if (ISFLAGSET(cmdReceived,BAPSNET_DATABASE_MODEMASK))
			{
				int showid = clientSocket->receiveI();
				System::String^ description = clientSocket->receiveS();
				addShowResult(showid,description);
			}
			else
			{
				int count = clientSocket->receiveI();
				setShowResultCount(count);
			}
			break;
		case BAPSNET_LISTING:
			if (ISFLAGSET(cmdReceived,BAPSNET_DATABASE_MODEMASK))
			{
				int listingid = clientSocket->receiveI();
				int channel = clientSocket->receiveI();
				System::String^ description = clientSocket->receiveS();
				addListingResult(listingid,channel,description);
			}
			else
			{
				int count = clientSocket->receiveI();
				setListingResultCount(count);
			}
			break;
		case BAPSNET_BAPSDBERROR:
			/** There is an error code in the command **/
			notifyLoadShowError(cmdReceived & BAPSNET_DATABASE_VALUEMASK,clientSocket->receiveS());
			break;
		default:
			{
				/** ERROR **/
				sendNotifyCommsError("Received unknown command, possibly a malformed DATABASE.\n");
			}
			break;
		}
		break;
	case BAPSNET_CONFIG:
		switch (cmdReceived & BAPSNET_CONFIG_OPMASK)
		{
		case BAPSNET_OPTION:
			{
				if (ISFLAGSET(cmdReceived,BAPSNET_CONFIG_MODEMASK))
				{
					int optionid = clientSocket->receiveI();
					System::String^ description = clientSocket->receiveS();
					int type = clientSocket->receiveI();
					processOption(cmdReceived, optionid, description, type);
				}
				else
				{
					int count = clientSocket->receiveI();
					processOptionCount(count);
				}
			}
			break;
		case BAPSNET_OPTIONCHOICE:
			{
				if (ISFLAGSET(cmdReceived,BAPSNET_CONFIG_MODEMASK))
				{
					int optionid = clientSocket->receiveI();
					int choiceIndex = clientSocket->receiveI();
					System::String^ choiceDescription = clientSocket->receiveS();
					processChoice(optionid, choiceIndex, choiceDescription);
				}
				else
				{
					int optionid = clientSocket->receiveI();
					int count = clientSocket->receiveI();
					processChoiceCount(optionid, count);
				}
			}
			break;
		case BAPSNET_CONFIGSETTING:
			{
				if (ISFLAGSET(cmdReceived,BAPSNET_CONFIG_MODEMASK))
				{
					int optionid = clientSocket->receiveI();
					int type = clientSocket->receiveI();
					processConfigSetting(cmdReceived, optionid, type);
				}
				else
				{
					int count = clientSocket->receiveI();
				}
			}
			break;
		case BAPSNET_CONFIGRESULT:
			{
				int optionid = clientSocket->receiveI();
				int result = clientSocket->receiveI();
				processConfigResult(cmdReceived, optionid, result);
			}
			break;
		case BAPSNET_CONFIGERROR:
			{
				System::String^ description = clientSocket->receiveS();
				processConfigError(cmdReceived & BAPSNET_CONFIG_VALUEMASK, description);
			}
			break;
		case BAPSNET_USER:
			{
				if (ISFLAGSET(cmdReceived,BAPSNET_CONFIG_MODEMASK))
				{
					System::String^ username = clientSocket->receiveS();
					int permissions = clientSocket->receiveI();
					processUserInfo(username, permissions);
				}
				else
				{
					int count = clientSocket->receiveI();
					processUserCount(count);
				}
			}
			break;
		case BAPSNET_PERMISSION:
			{
				if (ISFLAGSET(cmdReceived,BAPSNET_CONFIG_MODEMASK))
				{
					int permissionCode = clientSocket->receiveI();
					System::String^ description = clientSocket->receiveS();
					processPermissionInfo(permissionCode, description);
				}
				else
				{
					int count = clientSocket->receiveI();
					processPermissionCount(count);
				}
			}
			break;
		case BAPSNET_USERRESULT:
			{
				int resultCode = cmdReceived & BAPSNET_CONFIG_VALUEMASK;
				System::String^ description = clientSocket->receiveS();
				processUserResult(resultCode, description);
			}
			break;
		case BAPSNET_IPRESTRICTION:
			{
				if (ISFLAGSET(cmdReceived,BAPSNET_CONFIG_MODEMASK))
				{
					System::String^ ipaddress = clientSocket->receiveS();
					int mask = clientSocket->receiveI();
					processIPRestriction(cmdReceived, ipaddress, mask);
				}
				else
				{
					int count = clientSocket->receiveI();
					processIPRestrictionCount(cmdReceived, count);
				}
			}
			break;
		default:
			{
				/** ERROR **/
				sendNotifyCommsError("Received unknown command, possibly a malformed CONFIG.\n");
			}
			break;
		}
		break;
	case BAPSNET_SYSTEM:
		switch (cmdReceived & BAPSNET_SYSTEM_OPMASK)
		{
		case BAPSNET_SENDLOGMESSAGE:
			clientSocket->receiveS();
			break;
		case BAPSNET_FILENAME:
			if (ISFLAGSET(cmdReceived, BAPSNET_SYSTEM_MODEMASK))
			{
				int index = clientSocket->receiveI();
				System::String^ description = clientSocket->receiveS();
				MethodInvokerObjObjStr^ mi = gcnew MethodInvokerObjObjStr(this, &BAPSPresenterMain::addFileToDirectoryList);
				array<System::Object^>^ dd = gcnew array<System::Object^>(3) {cmdReceived & BAPSNET_SYSTEM_VALUEMASK, index, description};
				this->Invoke(mi, dd);
			}
			else
			{
				int count = clientSocket->receiveI();
				System::String^ niceDirectoryName = clientSocket->receiveS();
				MethodInvokerObjStr^ mi = gcnew MethodInvokerObjStr(this, &BAPSPresenterMain::clearFiles);
				array<System::Object^>^ dd = gcnew array<System::Object^>(2) {cmdReceived & BAPSNET_SYSTEM_VALUEMASK, niceDirectoryName};
				this->Invoke(mi, dd);
			}
			break;
		case BAPSNET_VERSION:
			{
				System::String^ version = clientSocket->receiveS();
				System::String^ date = clientSocket->receiveS();
				System::String^ time = clientSocket->receiveS();
				System::String^ author = clientSocket->receiveS();
				displayVersion(version, date, time, author);
			}
			break;
		case BAPSNET_FEEDBACK:
			{
				int result = clientSocket->receiveI();
				//processFeedbackResult(result);
			}
			break;
		case BAPSNET_SENDMESSAGE:
			{
				System::String^ from = clientSocket->receiveS();
				System::String^ to = clientSocket->receiveS();
				System::String^ message = clientSocket->receiveS();
				//MethodInvokerStrStrStr^ mi = gcnew MethodInvokerStrStrStr(this, &BAPSPresenterMain::processChatMessage);
				//array<System::Object^>^ dd = gcnew array<System::Object^>(3) {from,to,message};
				//this->Invoke(mi, dd);
			}
			break;
		case BAPSNET_CLIENTCHANGE:
			{
				System::String^ username = clientSocket->receiveS();
				/*if ((cmdReceived & BAPSNET_SYSTEM_VALUEMASK) == 1)
				{
					MethodInvokerStr^ mi = gcnew MethodInvokerStr(this, &BAPSPresenterMain::addToChatList);
					array<System::Object^>^ dd = gcnew array<System::Object^>(1) {username};
					this->Invoke(mi, dd);
				}
				else
				{
					MethodInvokerStr^ mi = gcnew MethodInvokerStr(this, &BAPSPresenterMain::removeFromChatList);
					array<System::Object^>^ dd = gcnew array<System::Object^>(1) {username};
					this->Invoke(mi, dd);
				}*/
			}
			break;
		case BAPSNET_SCROLLTEXT:
			{
				MethodInvokerObj^ mi = gcnew MethodInvokerObj(textDialog, &TextDialog::scroll);
				array<System::Object^>^ dd = gcnew array<System::Object^>(1) {cmdReceived & BAPSNET_SYSTEM_VALUEMASK};
				this->Invoke(mi, dd);
			}
			break;
		case BAPSNET_TEXTSIZE:
			{
				MethodInvokerObj^ mi = gcnew MethodInvokerObj(textDialog, &TextDialog::textSize);
				array<System::Object^>^ dd = gcnew array<System::Object^>(1) {cmdReceived & BAPSNET_SYSTEM_VALUEMASK};
				this->Invoke(mi, dd);
			}
			break;
		default:
			{
				/** ERROR **/
				sendNotifyCommsError("Received unknown command, possibly a malformed SYSTEM.\n");
			}
			break;
		}
		break;
	default:
		{
			/** ERROR **/
			sendNotifyCommsError("Received unknown command.\n");
		}
		break;
	}

}

void BAPSPresenterMain::senderFunc()
{
	/** Placeholder for the current message being processed **/
	ActionMessage^ currentMessage;
#ifndef _DEBUG
	try 
	{    
#endif
		/** Drop out if something goes horribly wrong elsewhere **/
		while (!dead)
		{
			/** Grab a message if there is one **/
			if (msgQueue->Count > 0)
			{
                currentMessage = static_cast<ActionMessage^>(msgQueue->Dequeue());
				/** Each message knows how to send itself **/
				currentMessage->sendMsg(clientSocket);
				/** Don't sleep if we have just processed a message, it is
					likely there will be another
				**/
			}
			else
			{
				System::Threading::Thread::Sleep(1);
			}
		}
#ifndef _DEBUG
	}
	catch (System::Exception^ e) 
	{
		if (!dead)
		{
			/** If we receive an exception we assume it to be a bad thing **/
			sendNotifyCommsError(System::String::Concat("Sender Loop Failed, server may have died:\n", e->Message, "\nStack Trace:\n", e->StackTrace));
		}
	}
#endif
}
void BAPSPresenterMain::logError(System::String^ errorMessage)
{
	System::IO::StreamWriter^ stream = nullptr;
	try
	{
		stream = gcnew System::IO::StreamWriter("bapserror.log", true);
		stream->Write(errorMessage);
	}
	catch (System::Exception^)
	{
		System::Windows::Forms::MessageBox::Show(System::String::Concat("Unable to write log file, Please write down the following information:\n", errorMessage), "Log file error", System::Windows::Forms::MessageBoxButtons::OK);
	}
	finally
	{
		if (stream != nullptr)
		{
			stream->Close();
		}
	}
}


/*void BAPSPresenterMain::showVolumeControls(bool shouldShow)
{
	Channel0VolumeBar->Visible = shouldShow;
	Channel1VolumeBar->Visible = shouldShow;
	Channel2VolumeBar->Visible = shouldShow;
	Channel0VolLabel->Visible = shouldShow;
	Channel1VolLabel->Visible = shouldShow;
	Channel2VolLabel->Visible = shouldShow;
	if (shouldShow)
	{
		trackList[0]->Width = 224;
		trackList[1]->Width = 224;
		trackList[2]->Width = 224;
	}
	else
	{
		trackList[0]->Width = 256;
		trackList[1]->Width = 256;
		trackList[2]->Width = 256;
	}
}*/
void BAPSPresenterMain::enableTimerControls(bool shouldEnable)
{
	this->timersEnabled = shouldEnable;
	this->Channel0Length->Visible = shouldEnable;
	this->Channel1Length->Visible = shouldEnable;
	this->Channel2Length->Visible = shouldEnable;
	this->Channel0Length->Enabled = shouldEnable;
	this->Channel1Length->Enabled = shouldEnable;
	this->Channel2Length->Enabled = shouldEnable;
	this->timeLine->DragEnabled = shouldEnable;
	CountDownState^ cds = safe_cast<CountDownState^>(trackLengthText[0]->Tag);
    cds->running = false;
	cds = safe_cast<CountDownState^>(trackLengthText[1]->Tag);
    cds->running = false;
	cds = safe_cast<CountDownState^>(trackLengthText[2]->Tag);
    cds->running = false;
}

void BAPSPresenterMain::refreshAudioWall()
{
	if (audioWall != nullptr && audioWall->Visible)
	{
		MethodInvoker^ mi = gcnew MethodInvoker(audioWall, &AudioWall::refreshWall);
		audioWall->Invoke(mi);
	}
}