#pragma once

#include "decodeStructs.h"
#include "Globals.h"
#include "RecordLibrarySearch.h"
#include "ConfigDialog.h"
#include "LoadShowDialog.h"
#include "SecurityDialog.h"
#include "ClientHelpers.h"
#include "FeedbackDialog.h"
#include "About.h"
#include "AudioWall.h"
#include "TextDialog.h"
#include "TrackTime.h"
#include "TrackList.h"
#include "BAPSButton.h"
#include "BAPSLabel.h"
#include "BAPSListBox.h"
#include "TimeLine.h"

#define DISABLE_INDEX_CHANGE() 	channelList[channel]->Enabled=false;\
								channelList[channel]->remove_SelectedIndexChanged( gcnew System::EventHandler(this, &BAPSPresenterMain::LoadNewIndex_Event));

#define ENABLE_INDEX_CHANGE()	channelList[channel]->add_SelectedIndexChanged( gcnew System::EventHandler(this, &BAPSPresenterMain::LoadNewIndex_Event));\
								channelList[channel]->Enabled=true;

namespace BAPSPresenter {

	ref class RecordLibrarySearch;
	ref class ConfigDialog;
	ref class SecurityDialog;
	ref class About;
	ref class FeedbackDialog;
	ref class LoadShowDialog;

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for BAPSPresenterMain
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class BAPSPresenterMain : public System::Windows::Forms::Form
	{
	public:
		/** Constructor controls connection and login, this may quit the
			application
		**/
		BAPSPresenterMain(void);
		/** Accessor for the crashed variable **/
		bool hasCrashed()
		{
			return crashed;
		}
		/** ### NO PUBLIC VARIABLES ### **/
	protected:
		/// <summary>
		/// Tidy up nicely, close the server connection, kill all threads
		/// </summary>
		~BAPSPresenterMain();

	private:
		/** ### PRIVATE FUNCTIONS ### **/

		/**
			PLAYBACK functions
		**/
		void showChannelOperation(System::Object^ _channel, System::Object^ _operation);
		void showPosition(System::Object^ _channel, System::Object^ _value);
		void showVolume(System::Object^ _channel, System::Object^ _value);
		void showLoadedItem(System::Object^ _channel, System::Object^ _index, System::Object^ _itemType, System::String^ description);
		void showDuration(System::Object^ _channel, System::Object^ _value);
		void showText(System::Object^ _channel, System::Object^ _index, System::String^ description, System::String^ text);
		void showCuePosition(System::Object^ _channel, System::Object^ _cuePosition);
		void showIntroPosition(System::Object^ _channel, System::Object^ _introPosition);

		/**
			PLAYLIST functions
		**/
		void addItem(System::Object^ _channel, System::Object^ _index, System::Object^ _type, System::String^ entry);
		void moveItemTo(System::Object^ _channel, System::Object^ _oldIndex, System::Object^ _newIndex);
		void deleteItem(System::Object^ _channel, System::Object^ _index);
		void cleanPlaylist(System::Object^ _channel);

		/**
			DATABASE functions
		**/
		void addLibraryResult(u32int index, System::String^ result);
		void setLibraryResultCount(int count);
		void notifyLibraryError(int errorcode, System::String^ description);
		
		void addShowResult(u32int showid, System::String^ description);
		void setShowResultCount(int count);
		void addListingResult(u32int listingid, u32int channel, System::String^ description);
		void setListingResultCount(int count);
		void notifyLoadShowError(int errorCode, System::String^ message);

		/**
			CONFIG functions
		**/
		void processOption(Command cmdReceived, int optionid, System::String^ description, int type);
		void processOptionCount(int count);
		void processChoice(int optionid, int choiceIndex, System::String^ choiceDescription);
		void processChoiceCount(int optionid, int count);
		void processConfigSetting(Command cmdReceived, int optionid, int type);
		void processConfigResult(Command cmdReceived, int optionid, int result);
		void processConfigError(int errorCode, System::String^ description);
		void processUserInfo(System::String^ username, int permissions);
		void processUserCount(int userCount);
		void processPermissionInfo(int permissionCode, System::String^ description);
		void processPermissionCount(int permissionCount);
		void processUserResult(int resultCode, System::String^ description);
		void processIPRestrictionCount(Command cmd, int count);
		void processIPRestriction(Command cmd, System::String^ ipaddress, int mask);

		/**
			SYSTEM functions
		**/
		void addFileToDirectoryList(System::Object^ _directoryIndex, System::Object^ _fileIndex, System::String^ entry);
		void clearFiles(System::Object^ _directoryIndex);
		void displayVersion(System::String^ version, System::String^ date, System::String^ time, System::String^ author);
		void processFeedbackResult(int resultCode);
		void addToChatList(System::String^ username);
		void removeFromChatList(System::String^ username);
		void processChatMessage(System::String^ from, System::String^ to, System::String^ message);

		/** Show or hide the volume controls **/
		void showVolumeControls(bool shouldShow);
		/** Enable or diable the timer controls **/
		void enableTimerControls(bool shouldEnable);
		/** Notify AudioWall to Update **/
		void refreshAudioWall();
		/** Loop to wait for a command and then process it correctly **/
		void receiverFunc();
		/** Helper function to do command decoding **/
		void decodeCommand(Command cmdReceived);
		/** Loop to watch for an outgoing message on the queue and send it **/
		void senderFunc();
		/** Function to async send the notify of a Comms Error **/
		void sendNotifyCommsError(System::String^ description);
		/** Function to notify of a Comms Error **/
		void notifyCommsError(System::String^ description);
		/** Function to open write and close a log file -- FOR EMERGENCIES ONLY **/
		void logError(System::String^ errorMessage);

		/** functions to receive events from the custom TrackTime class */
		void positionChanged(System::Object^ sender, System::EventArgs^ e);
		void cuePositionChanged(System::Object^ sender, System::EventArgs^ e);
		void introPositionChanged(System::Object^ sender, System::EventArgs^ e);
		/** functions to receive context menu events **/
		void ChannelListClear_Click(System::Object^ sender, System::EventArgs^ e);
		/** ### END PRIVATE FUNCTIONS ### **/
		/** ### PRIVATE VARIABLES ### **/

		/** A handle for the connection to the server **/
		ClientSocket^ clientSocket;

		/** The current user **/
		System::String^ username;

		/** This flag is used to cleanly exit the send/receive loops
			in the case of the receive loop, the flag will not take effect
			until data is received, so an abort message is still required
		**/
		bool dead;
		/** Flag to say if the client crashed **/
		bool crashed;
		/** The sender thread **/
		System::Threading::Thread ^senderThread;
		/** The receiver thread **/
		System::Threading::Thread ^receiverThread;
		/** Whether or not the timers are enabled **/
		bool timersEnabled;

		/** The outgoing message queue (Should only have ActionMessage objects)**/
		System::Collections::Queue^ msgQueue;

		/** Sub-form handles **/
		RecordLibrarySearch^ recordLibrarySearch;
		ConfigDialog^ configDialog;
		LoadShowDialog^ loadShowDialog;
		SecurityDialog^ securityDialog;
		About^ about;
		FeedbackDialog^ feedbackDialog;
		TextDialog^ textDialog;
		AudioWall^ audioWall;
		
		/** Arrays with channel number indices for easy updating **/
		array<BAPSPresenter::BAPSListBox^>^	directoryList;
		array<BAPSLabel^>^		loadedText;
		array<BAPSLabel^>^		trackLengthText;
		array<BAPSLabel^>^		timeLeftText;
		array<BAPSLabel^>^		timeGoneText;
		array<System::Windows::Forms::TrackBar^>^	volumeBar;
		array<BAPSButton^>^		channelPlay;
		array<BAPSButton^>^		channelPause;
		array<BAPSButton^>^		channelStop;
		array<BAPSPresenter::TrackTime^>^ trackTime;
		array<System::Windows::Forms::Timer^>^ loadImpossibleTimer;
		array<System::Windows::Forms::Timer^>^ nearEndTimer;
		System::Windows::Forms::Timer^ countdownTimer;
private: System::Windows::Forms::ContextMenuStrip^  trackListContextMenuStrip;

private: System::Windows::Forms::ToolStripMenuItem^  resetChannelStripMenuItem;

private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
private: System::Windows::Forms::ToolStripMenuItem^  deleteItemToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  automaticAdvanceToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  playOnLoadToolStripMenuItem;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;



private: System::Windows::Forms::ToolStripMenuItem^  repeatAllToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  repeatNoneToolStripMenuItem;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
private: BAPSPresenter::BAPSLabel^  Channel0Label;
private: BAPSPresenter::BAPSLabel^  Channel1Label;
private: BAPSPresenter::BAPSLabel^  Channel2Label;
private: System::Windows::Forms::ToolStripMenuItem^  repeatOneToolStripMenuItem;
private: System::Windows::Forms::TextBox^  MainTextDisplay;
private: System::Windows::Forms::TextBox^  chatText;
private: System::Windows::Forms::TextBox^  newChatMessage;
private: BAPSPresenter::BAPSLabel^  newMessageLabel;
private: System::Windows::Forms::ComboBox^  chatTo;

private: BAPSPresenter::BAPSButton^  sendMessage;
private: BAPSPresenter::BAPSButton^  chatOnOff;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator4;
private: System::Windows::Forms::ToolStripMenuItem^  showAudioWallToolStripMenuItem;
private: BAPSPresenter::TimeLine^  timeLine;





		 array<BAPSPresenter::TrackList^>^ trackList;

		/** ### END PRIVATE VARIABLES ### **/
		/** ### DESIGNER PRIVATE EVENT HANDLERS ### **/
public:
		System::Void BAPSPresenterMain_KeyDown(System::Object ^  sender, System::Windows::Forms::KeyEventArgs ^  e);
private:
		System::Void TrackBar_Scroll(System::Object ^  sender, System::EventArgs ^  e);
		System::Void VolumeBar_Scroll(System::Object ^  sender, System::EventArgs ^  e);
	
		System::Void RefreshDirectory_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void newChatMessage_TextChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void helpButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void SearchRecordLib_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void loadShow_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void sendMessage_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void feedbackButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void Directory_MouseDown(System::Object ^  sender, System::Windows::Forms::MouseEventArgs ^  e);
		System::Void chatOnOff_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void ChannelOperation_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void TrackList_RequestChange(System::Object^  o, BAPSPresenter::RequestChangeEventArgs^  e);
		System::Void trackListContextMenuStrip_Opening(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e);
		System::Void trackListContextMenuStrip_ItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e);
		System::Void loadImpossibleFlicker(System::Object ^  sender, System::EventArgs ^  e);
		System::Void nearEndFlash(System::Object ^  sender, System::EventArgs ^  e);
		System::Void ChannelLength_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
		System::Void countdownTick(System::Object ^  sender, System::EventArgs ^  e);
		System::Void timeLine_StartTimeChanged(System::Object^  sender, BAPSPresenter::TimeLineEventArgs^  e);
		/** ### END DESIGNER PRIVATE EVENT HANDLERS ### **/
		/** ### DESIGNER PRIVATE VARIABLES ### **/

	private: BAPSPresenter::BAPSListBox^  Directory0;
	private: BAPSPresenter::BAPSListBox^  Directory1;
	private: BAPSPresenter::BAPSListBox^  Directory2;

	private: BAPSPresenter::BAPSButton^  Channel0Play;
	private: BAPSPresenter::BAPSButton^  Channel1Play;
	private: BAPSPresenter::BAPSButton^  Channel2Play;
	private: BAPSPresenter::BAPSButton^  Channel0Stop;
	private: BAPSPresenter::BAPSButton^  Channel1Stop;
	private: BAPSPresenter::BAPSButton^  Channel2Stop;
	private: BAPSPresenter::BAPSButton^  Channel0Pause;
	private: BAPSPresenter::BAPSButton^  Channel1Pause;
	private: BAPSPresenter::BAPSButton^  Channel2Pause;

	private: BAPSPresenter::BAPSButton^  loadShowButton;
	private: BAPSPresenter::BAPSButton^  bapsButton1;
	private: BAPSPresenter::BAPSButton^  helpButton;
	private: BAPSPresenter::BAPSButton^  feedbackButton;
	private: BAPSPresenter::BAPSButton^  Directory0Refresh;
	private: BAPSPresenter::BAPSButton^  Directory1Refresh;
	private: BAPSPresenter::BAPSButton^  Directory2Refresh;
	private: BAPSPresenter::BAPSLabel^  Channel0LoadedText;
	private: BAPSPresenter::BAPSLabel^  Channel1LoadedText;
	private: BAPSPresenter::BAPSLabel^  Channel2LoadedText;

	private: BAPSPresenter::BAPSLabel^  Channel0TimeGone;
	private: BAPSPresenter::BAPSLabel^  Channel0TimeLeft;
	private: BAPSPresenter::BAPSLabel^  Channel0Length;
	private: BAPSPresenter::BAPSLabel^  Channel1TimeGone;
	private: BAPSPresenter::BAPSLabel^  Channel1TimeLeft;
	private: BAPSPresenter::BAPSLabel^  Channel1Length;
	private: BAPSPresenter::BAPSLabel^  Channel2TimeGone;
	private: BAPSPresenter::BAPSLabel^  Channel2TimeLeft;
	private: BAPSPresenter::BAPSLabel^  Channel2Length;

	private: System::Windows::Forms::Label^  Channel2VolLabel;
	private: System::Windows::Forms::Label^  Channel1VolLabel;
	private: System::Windows::Forms::Label^  Channel0VolLabel;




	private: System::Windows::Forms::TrackBar^  Channel2VolumeBar;
	private: System::Windows::Forms::TrackBar^  Channel1VolumeBar;
	private: System::Windows::Forms::TrackBar^  Channel0VolumeBar;

	private: BAPSPresenter::TrackTime^  trackTime0;
	private: BAPSPresenter::TrackTime^  trackTime1;
	private: BAPSPresenter::TrackTime^  trackTime2;
	private: BAPSPresenter::TrackList^  trackList0;
	private: BAPSPresenter::TrackList^  trackList1;
	private: BAPSPresenter::TrackList^  trackList2;


private: System::ComponentModel::IContainer^  components;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(BAPSPresenterMain::typeid));
			this->Channel2VolLabel = (gcnew System::Windows::Forms::Label());
			this->Channel1VolLabel = (gcnew System::Windows::Forms::Label());
			this->Channel0VolLabel = (gcnew System::Windows::Forms::Label());
			this->Channel2VolumeBar = (gcnew System::Windows::Forms::TrackBar());
			this->Channel1VolumeBar = (gcnew System::Windows::Forms::TrackBar());
			this->Channel0VolumeBar = (gcnew System::Windows::Forms::TrackBar());
			this->trackListContextMenuStrip = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->resetChannelStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->deleteItemToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->automaticAdvanceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->playOnLoadToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->repeatAllToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->repeatOneToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->repeatNoneToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->showAudioWallToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MainTextDisplay = (gcnew System::Windows::Forms::TextBox());
			this->chatText = (gcnew System::Windows::Forms::TextBox());
			this->newChatMessage = (gcnew System::Windows::Forms::TextBox());
			this->chatTo = (gcnew System::Windows::Forms::ComboBox());
			this->timeLine = (gcnew BAPSPresenter::TimeLine());
			this->chatOnOff = (gcnew BAPSPresenter::BAPSButton());
			this->sendMessage = (gcnew BAPSPresenter::BAPSButton());
			this->newMessageLabel = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel2Label = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel1Label = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel0Label = (gcnew BAPSPresenter::BAPSLabel());
			this->Directory2 = (gcnew BAPSPresenter::BAPSListBox());
			this->Directory1 = (gcnew BAPSPresenter::BAPSListBox());
			this->Directory0 = (gcnew BAPSPresenter::BAPSListBox());
			this->Channel2Length = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel1Length = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel0Length = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel2TimeLeft = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel1TimeLeft = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel0TimeLeft = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel2TimeGone = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel1TimeGone = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel0TimeGone = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel2LoadedText = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel1LoadedText = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel0LoadedText = (gcnew BAPSPresenter::BAPSLabel());
			this->Directory2Refresh = (gcnew BAPSPresenter::BAPSButton());
			this->Directory1Refresh = (gcnew BAPSPresenter::BAPSButton());
			this->feedbackButton = (gcnew BAPSPresenter::BAPSButton());
			this->Directory0Refresh = (gcnew BAPSPresenter::BAPSButton());
			this->helpButton = (gcnew BAPSPresenter::BAPSButton());
			this->bapsButton1 = (gcnew BAPSPresenter::BAPSButton());
			this->Channel2Play = (gcnew BAPSPresenter::BAPSButton());
			this->loadShowButton = (gcnew BAPSPresenter::BAPSButton());
			this->Channel1Play = (gcnew BAPSPresenter::BAPSButton());
			this->Channel2Stop = (gcnew BAPSPresenter::BAPSButton());
			this->Channel1Stop = (gcnew BAPSPresenter::BAPSButton());
			this->Channel2Pause = (gcnew BAPSPresenter::BAPSButton());
			this->Channel1Pause = (gcnew BAPSPresenter::BAPSButton());
			this->Channel0Pause = (gcnew BAPSPresenter::BAPSButton());
			this->Channel0Stop = (gcnew BAPSPresenter::BAPSButton());
			this->Channel0Play = (gcnew BAPSPresenter::BAPSButton());
			this->trackList2 = (gcnew BAPSPresenter::TrackList());
			this->trackList1 = (gcnew BAPSPresenter::TrackList());
			this->trackList0 = (gcnew BAPSPresenter::TrackList());
			this->trackTime2 = (gcnew BAPSPresenter::TrackTime());
			this->trackTime1 = (gcnew BAPSPresenter::TrackTime());
			this->trackTime0 = (gcnew BAPSPresenter::TrackTime());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Channel2VolumeBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Channel1VolumeBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Channel0VolumeBar))->BeginInit();
			this->trackListContextMenuStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// Channel2VolLabel
			// 
			this->Channel2VolLabel->AutoSize = true;
			this->Channel2VolLabel->BackColor = System::Drawing::Color::Transparent;
			this->Channel2VolLabel->Location = System::Drawing::Point(934, 113);
			this->Channel2VolLabel->Name = L"Channel2VolLabel";
			this->Channel2VolLabel->Size = System::Drawing::Size(22, 13);
			this->Channel2VolLabel->TabIndex = 105;
			this->Channel2VolLabel->Text = L"Vol";
			// 
			// Channel1VolLabel
			// 
			this->Channel1VolLabel->AutoSize = true;
			this->Channel1VolLabel->BackColor = System::Drawing::Color::Transparent;
			this->Channel1VolLabel->Location = System::Drawing::Point(638, 113);
			this->Channel1VolLabel->Name = L"Channel1VolLabel";
			this->Channel1VolLabel->Size = System::Drawing::Size(22, 13);
			this->Channel1VolLabel->TabIndex = 104;
			this->Channel1VolLabel->Text = L"Vol";
			// 
			// Channel0VolLabel
			// 
			this->Channel0VolLabel->AutoSize = true;
			this->Channel0VolLabel->BackColor = System::Drawing::Color::Transparent;
			this->Channel0VolLabel->Location = System::Drawing::Point(342, 112);
			this->Channel0VolLabel->Name = L"Channel0VolLabel";
			this->Channel0VolLabel->Size = System::Drawing::Size(22, 13);
			this->Channel0VolLabel->TabIndex = 103;
			this->Channel0VolLabel->Text = L"Vol";
			// 
			// Channel2VolumeBar
			// 
			this->Channel2VolumeBar->LargeChange = 10;
			this->Channel2VolumeBar->Location = System::Drawing::Point(899, 118);
			this->Channel2VolumeBar->Maximum = 100;
			this->Channel2VolumeBar->Name = L"Channel2VolumeBar";
			this->Channel2VolumeBar->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->Channel2VolumeBar->Size = System::Drawing::Size(45, 286);
			this->Channel2VolumeBar->TabIndex = 211;
			this->Channel2VolumeBar->TickFrequency = 10;
			this->Channel2VolumeBar->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->Channel2VolumeBar->Value = 15;
			this->Channel2VolumeBar->Scroll += gcnew System::EventHandler(this, &BAPSPresenterMain::VolumeBar_Scroll);
			// 
			// Channel1VolumeBar
			// 
			this->Channel1VolumeBar->LargeChange = 10;
			this->Channel1VolumeBar->Location = System::Drawing::Point(603, 118);
			this->Channel1VolumeBar->Maximum = 100;
			this->Channel1VolumeBar->Name = L"Channel1VolumeBar";
			this->Channel1VolumeBar->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->Channel1VolumeBar->Size = System::Drawing::Size(45, 286);
			this->Channel1VolumeBar->TabIndex = 13;
			this->Channel1VolumeBar->TickFrequency = 10;
			this->Channel1VolumeBar->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->Channel1VolumeBar->Value = 100;
			this->Channel1VolumeBar->Scroll += gcnew System::EventHandler(this, &BAPSPresenterMain::VolumeBar_Scroll);
			// 
			// Channel0VolumeBar
			// 
			this->Channel0VolumeBar->LargeChange = 10;
			this->Channel0VolumeBar->Location = System::Drawing::Point(307, 118);
			this->Channel0VolumeBar->Maximum = 100;
			this->Channel0VolumeBar->Name = L"Channel0VolumeBar";
			this->Channel0VolumeBar->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->Channel0VolumeBar->Size = System::Drawing::Size(45, 286);
			this->Channel0VolumeBar->TabIndex = 11;
			this->Channel0VolumeBar->TickFrequency = 10;
			this->Channel0VolumeBar->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->Channel0VolumeBar->Value = 100;
			this->Channel0VolumeBar->Scroll += gcnew System::EventHandler(this, &BAPSPresenterMain::VolumeBar_Scroll);
			// 
			// trackListContextMenuStrip
			// 
			this->trackListContextMenuStrip->BackColor = System::Drawing::Color::SeaShell;
			this->trackListContextMenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(12) {this->resetChannelStripMenuItem, 
				this->toolStripSeparator2, this->deleteItemToolStripMenuItem, this->toolStripSeparator3, this->automaticAdvanceToolStripMenuItem, 
				this->playOnLoadToolStripMenuItem, this->toolStripSeparator1, this->repeatAllToolStripMenuItem, this->repeatOneToolStripMenuItem, 
				this->repeatNoneToolStripMenuItem, this->toolStripSeparator4, this->showAudioWallToolStripMenuItem});
			this->trackListContextMenuStrip->Name = L"trackListContextMenuStrip";
			this->trackListContextMenuStrip->ShowCheckMargin = true;
			this->trackListContextMenuStrip->ShowImageMargin = false;
			this->trackListContextMenuStrip->Size = System::Drawing::Size(178, 204);
			this->trackListContextMenuStrip->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &BAPSPresenterMain::trackListContextMenuStrip_Opening);
			this->trackListContextMenuStrip->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &BAPSPresenterMain::trackListContextMenuStrip_ItemClicked);
			// 
			// resetChannelStripMenuItem
			// 
			this->resetChannelStripMenuItem->Name = L"resetChannelStripMenuItem";
			this->resetChannelStripMenuItem->Size = System::Drawing::Size(177, 22);
			this->resetChannelStripMenuItem->Text = L"&Reset Channel";
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(174, 6);
			// 
			// deleteItemToolStripMenuItem
			// 
			this->deleteItemToolStripMenuItem->Name = L"deleteItemToolStripMenuItem";
			this->deleteItemToolStripMenuItem->Size = System::Drawing::Size(177, 22);
			this->deleteItemToolStripMenuItem->Text = L"&Delete Item";
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			this->toolStripSeparator3->Size = System::Drawing::Size(174, 6);
			// 
			// automaticAdvanceToolStripMenuItem
			// 
			this->automaticAdvanceToolStripMenuItem->Name = L"automaticAdvanceToolStripMenuItem";
			this->automaticAdvanceToolStripMenuItem->Size = System::Drawing::Size(177, 22);
			this->automaticAdvanceToolStripMenuItem->Text = L"&Automatic advance";
			// 
			// playOnLoadToolStripMenuItem
			// 
			this->playOnLoadToolStripMenuItem->Name = L"playOnLoadToolStripMenuItem";
			this->playOnLoadToolStripMenuItem->Size = System::Drawing::Size(177, 22);
			this->playOnLoadToolStripMenuItem->Text = L"&Play on load";
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(174, 6);
			// 
			// repeatAllToolStripMenuItem
			// 
			this->repeatAllToolStripMenuItem->Name = L"repeatAllToolStripMenuItem";
			this->repeatAllToolStripMenuItem->Size = System::Drawing::Size(177, 22);
			this->repeatAllToolStripMenuItem->Text = L"Repeat a&ll";
			// 
			// repeatOneToolStripMenuItem
			// 
			this->repeatOneToolStripMenuItem->Name = L"repeatOneToolStripMenuItem";
			this->repeatOneToolStripMenuItem->Size = System::Drawing::Size(177, 22);
			this->repeatOneToolStripMenuItem->Text = L"Repeat &one";
			// 
			// repeatNoneToolStripMenuItem
			// 
			this->repeatNoneToolStripMenuItem->Name = L"repeatNoneToolStripMenuItem";
			this->repeatNoneToolStripMenuItem->Size = System::Drawing::Size(177, 22);
			this->repeatNoneToolStripMenuItem->Text = L"Repeat &none";
			// 
			// toolStripSeparator4
			// 
			this->toolStripSeparator4->Name = L"toolStripSeparator4";
			this->toolStripSeparator4->Size = System::Drawing::Size(174, 6);
			// 
			// showAudioWallToolStripMenuItem
			// 
			this->showAudioWallToolStripMenuItem->Name = L"showAudioWallToolStripMenuItem";
			this->showAudioWallToolStripMenuItem->Size = System::Drawing::Size(177, 22);
			this->showAudioWallToolStripMenuItem->Text = L"&Show AudioWall";
			// 
			// MainTextDisplay
			// 
			this->MainTextDisplay->AcceptsReturn = true;
			this->MainTextDisplay->BackColor = System::Drawing::Color::SeaShell;
			this->MainTextDisplay->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->MainTextDisplay->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->MainTextDisplay->Location = System::Drawing::Point(8, 639);
			this->MainTextDisplay->Multiline = true;
			this->MainTextDisplay->Name = L"MainTextDisplay";
			this->MainTextDisplay->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->MainTextDisplay->Size = System::Drawing::Size(1005, 83);
			this->MainTextDisplay->TabIndex = 29;
			this->MainTextDisplay->Text = L"<You can type notes here>";
			// 
			// chatText
			// 
			this->chatText->AcceptsReturn = true;
			this->chatText->BackColor = System::Drawing::Color::SeaShell;
			this->chatText->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->chatText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->chatText->Location = System::Drawing::Point(7, 664);
			this->chatText->Multiline = true;
			this->chatText->Name = L"chatText";
			this->chatText->ReadOnly = true;
			this->chatText->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->chatText->Size = System::Drawing::Size(1005, 62);
			this->chatText->TabIndex = 213;
			this->chatText->TabStop = false;
			this->chatText->Text = L"<CHAT>";
			this->chatText->Visible = false;
			// 
			// newChatMessage
			// 
			this->newChatMessage->BackColor = System::Drawing::Color::SeaShell;
			this->newChatMessage->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->newChatMessage->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->newChatMessage->Location = System::Drawing::Point(83, 635);
			this->newChatMessage->Name = L"newChatMessage";
			this->newChatMessage->Size = System::Drawing::Size(756, 26);
			this->newChatMessage->TabIndex = 29;
			this->newChatMessage->Visible = false;
			this->newChatMessage->TextChanged += gcnew System::EventHandler(this, &BAPSPresenterMain::newChatMessage_TextChanged);
			// 
			// chatTo
			// 
			this->chatTo->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Suggest;
			this->chatTo->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::ListItems;
			this->chatTo->BackColor = System::Drawing::Color::SeaShell;
			this->chatTo->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->chatTo->FormattingEnabled = true;
			this->chatTo->Location = System::Drawing::Point(845, 639);
			this->chatTo->Name = L"chatTo";
			this->chatTo->Size = System::Drawing::Size(96, 21);
			this->chatTo->Sorted = true;
			this->chatTo->TabIndex = 30;
			this->chatTo->Visible = false;
			// 
			// timeLine
			// 
			this->timeLine->BackColor = System::Drawing::Color::Transparent;
			this->timeLine->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->timeLine->Location = System::Drawing::Point(83, 579);
			this->timeLine->Name = L"timeLine";
			this->timeLine->Size = System::Drawing::Size(848, 52);
			this->timeLine->TabIndex = 214;
			this->timeLine->TabStop = false;
			this->timeLine->Text = L"timeLine1";
			this->timeLine->StartTimeChanged += gcnew BAPSPresenter::TimeLineEventHandler(this, &BAPSPresenterMain::timeLine_StartTimeChanged);
			// 
			// chatOnOff
			// 
			this->chatOnOff->BackColor = System::Drawing::Color::Transparent;
			this->chatOnOff->DialogResult = System::Windows::Forms::DialogResult::None;
			this->chatOnOff->HighlightColor = System::Drawing::Color::Red;
			this->chatOnOff->Highlighted = false;
			this->chatOnOff->Location = System::Drawing::Point(7, 600);
			this->chatOnOff->Name = L"chatOnOff";
			this->chatOnOff->Size = System::Drawing::Size(66, 26);
			this->chatOnOff->TabIndex = 28;
			this->chatOnOff->Text = L"Chat ON";
			this->chatOnOff->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::chatOnOff_Click);
			// 
			// sendMessage
			// 
			this->sendMessage->BackColor = System::Drawing::Color::Transparent;
			this->sendMessage->DialogResult = System::Windows::Forms::DialogResult::None;
			this->sendMessage->Enabled = false;
			this->sendMessage->HighlightColor = System::Drawing::Color::Red;
			this->sendMessage->Highlighted = false;
			this->sendMessage->Location = System::Drawing::Point(947, 636);
			this->sendMessage->Name = L"sendMessage";
			this->sendMessage->Size = System::Drawing::Size(66, 26);
			this->sendMessage->TabIndex = 31;
			this->sendMessage->Text = L"Send";
			this->sendMessage->Visible = false;
			this->sendMessage->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::sendMessage_Click);
			// 
			// newMessageLabel
			// 
			this->newMessageLabel->BackColor = System::Drawing::Color::Transparent;
			this->newMessageLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->newMessageLabel->ForeColor = System::Drawing::Color::MidnightBlue;
			this->newMessageLabel->HighlightColor = System::Drawing::Color::Red;
			this->newMessageLabel->Highlighted = false;
			this->newMessageLabel->InfoText = L"";
			this->newMessageLabel->Location = System::Drawing::Point(7, 635);
			this->newMessageLabel->Name = L"newMessageLabel";
			this->newMessageLabel->Size = System::Drawing::Size(70, 26);
			this->newMessageLabel->TabIndex = 106;
			this->newMessageLabel->TabStop = false;
			this->newMessageLabel->Text = L"Message:";
			this->newMessageLabel->Visible = false;
			// 
			// Channel2Label
			// 
			this->Channel2Label->BackColor = System::Drawing::Color::Transparent;
			this->Channel2Label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel2Label->HighlightColor = System::Drawing::Color::Red;
			this->Channel2Label->Highlighted = false;
			this->Channel2Label->InfoText = L"";
			this->Channel2Label->Location = System::Drawing::Point(675, 98);
			this->Channel2Label->Name = L"Channel2Label";
			this->Channel2Label->Size = System::Drawing::Size(256, 16);
			this->Channel2Label->TabIndex = 212;
			this->Channel2Label->TabStop = false;
			this->Channel2Label->Text = L"Channel 3";
			// 
			// Channel1Label
			// 
			this->Channel1Label->BackColor = System::Drawing::Color::Transparent;
			this->Channel1Label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel1Label->HighlightColor = System::Drawing::Color::Red;
			this->Channel1Label->Highlighted = false;
			this->Channel1Label->InfoText = L"";
			this->Channel1Label->Location = System::Drawing::Point(377, 98);
			this->Channel1Label->Name = L"Channel1Label";
			this->Channel1Label->Size = System::Drawing::Size(256, 16);
			this->Channel1Label->TabIndex = 212;
			this->Channel1Label->TabStop = false;
			this->Channel1Label->Text = L"Channel 2";
			// 
			// Channel0Label
			// 
			this->Channel0Label->BackColor = System::Drawing::Color::Transparent;
			this->Channel0Label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel0Label->HighlightColor = System::Drawing::Color::Red;
			this->Channel0Label->Highlighted = false;
			this->Channel0Label->InfoText = L"";
			this->Channel0Label->Location = System::Drawing::Point(83, 98);
			this->Channel0Label->Name = L"Channel0Label";
			this->Channel0Label->Size = System::Drawing::Size(256, 16);
			this->Channel0Label->TabIndex = 212;
			this->Channel0Label->TabStop = false;
			this->Channel0Label->Text = L"Channel 1";
			// 
			// Directory2
			// 
			this->Directory2->Location = System::Drawing::Point(619, 22);
			this->Directory2->Name = L"Directory0";
			this->Directory2->SelectedIndexEnabled = false;
			this->Directory2->Size = System::Drawing::Size(200, 69);
			this->Directory2->TabIndex = 6;
			this->Directory2->Text = L"bapsListBox1";
			this->Directory2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &BAPSPresenterMain::Directory_MouseDown);
			// 
			// Directory1
			// 
			this->Directory1->Location = System::Drawing::Point(411, 22);
			this->Directory1->Name = L"Directory0";
			this->Directory1->SelectedIndexEnabled = false;
			this->Directory1->Size = System::Drawing::Size(200, 69);
			this->Directory1->TabIndex = 5;
			this->Directory1->Text = L"bapsListBox1";
			this->Directory1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &BAPSPresenterMain::Directory_MouseDown);
			// 
			// Directory0
			// 
			this->Directory0->Location = System::Drawing::Point(205, 22);
			this->Directory0->Name = L"Directory0";
			this->Directory0->SelectedIndexEnabled = false;
			this->Directory0->Size = System::Drawing::Size(200, 69);
			this->Directory0->TabIndex = 4;
			this->Directory0->Text = L"bapsListBox1";
			this->Directory0->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &BAPSPresenterMain::Directory_MouseDown);
			// 
			// Channel2Length
			// 
			this->Channel2Length->BackColor = System::Drawing::Color::Transparent;
			this->Channel2Length->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel2Length->HighlightColor = System::Drawing::Color::Red;
			this->Channel2Length->Highlighted = false;
			this->Channel2Length->InfoText = L"End At: 59:50";
			this->Channel2Length->Location = System::Drawing::Point(849, 536);
			this->Channel2Length->Name = L"Channel2Length";
			this->Channel2Length->Size = System::Drawing::Size(82, 32);
			this->Channel2Length->TabIndex = 117;
			this->Channel2Length->TabStop = false;
			this->Channel2Length->Tag = L"";
			this->Channel2Length->Text = L"--:--";
			this->Channel2Length->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &BAPSPresenterMain::ChannelLength_MouseDown);
			// 
			// Channel1Length
			// 
			this->Channel1Length->BackColor = System::Drawing::Color::Transparent;
			this->Channel1Length->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel1Length->HighlightColor = System::Drawing::Color::Red;
			this->Channel1Length->Highlighted = false;
			this->Channel1Length->InfoText = L"End At: 59:50";
			this->Channel1Length->Location = System::Drawing::Point(553, 536);
			this->Channel1Length->Name = L"Channel1Length";
			this->Channel1Length->Size = System::Drawing::Size(82, 32);
			this->Channel1Length->TabIndex = 114;
			this->Channel1Length->TabStop = false;
			this->Channel1Length->Tag = L"";
			this->Channel1Length->Text = L"--:--";
			this->Channel1Length->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &BAPSPresenterMain::ChannelLength_MouseDown);
			// 
			// Channel0Length
			// 
			this->Channel0Length->BackColor = System::Drawing::Color::Transparent;
			this->Channel0Length->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel0Length->HighlightColor = System::Drawing::Color::Red;
			this->Channel0Length->Highlighted = false;
			this->Channel0Length->InfoText = L"End At: 59:50";
			this->Channel0Length->Location = System::Drawing::Point(257, 536);
			this->Channel0Length->Name = L"Channel0Length";
			this->Channel0Length->Size = System::Drawing::Size(82, 32);
			this->Channel0Length->TabIndex = 111;
			this->Channel0Length->TabStop = false;
			this->Channel0Length->Tag = L"";
			this->Channel0Length->Text = L"--:--";
			this->Channel0Length->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &BAPSPresenterMain::ChannelLength_MouseDown);
			// 
			// Channel2TimeLeft
			// 
			this->Channel2TimeLeft->BackColor = System::Drawing::Color::Transparent;
			this->Channel2TimeLeft->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel2TimeLeft->HighlightColor = System::Drawing::Color::HotPink;
			this->Channel2TimeLeft->Highlighted = false;
			this->Channel2TimeLeft->InfoText = L"Remaining:";
			this->Channel2TimeLeft->Location = System::Drawing::Point(762, 536);
			this->Channel2TimeLeft->Name = L"Channel2TimeLeft";
			this->Channel2TimeLeft->Size = System::Drawing::Size(82, 32);
			this->Channel2TimeLeft->TabIndex = 116;
			this->Channel2TimeLeft->TabStop = false;
			this->Channel2TimeLeft->Text = L"0:00:00";
			// 
			// Channel1TimeLeft
			// 
			this->Channel1TimeLeft->BackColor = System::Drawing::Color::Transparent;
			this->Channel1TimeLeft->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel1TimeLeft->HighlightColor = System::Drawing::Color::HotPink;
			this->Channel1TimeLeft->Highlighted = false;
			this->Channel1TimeLeft->InfoText = L"Remaining:";
			this->Channel1TimeLeft->Location = System::Drawing::Point(466, 536);
			this->Channel1TimeLeft->Name = L"Channel1TimeLeft";
			this->Channel1TimeLeft->Size = System::Drawing::Size(82, 32);
			this->Channel1TimeLeft->TabIndex = 113;
			this->Channel1TimeLeft->TabStop = false;
			this->Channel1TimeLeft->Text = L"0:00:00";
			// 
			// Channel0TimeLeft
			// 
			this->Channel0TimeLeft->BackColor = System::Drawing::Color::Transparent;
			this->Channel0TimeLeft->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel0TimeLeft->HighlightColor = System::Drawing::Color::HotPink;
			this->Channel0TimeLeft->Highlighted = false;
			this->Channel0TimeLeft->InfoText = L"Remaining:";
			this->Channel0TimeLeft->Location = System::Drawing::Point(170, 536);
			this->Channel0TimeLeft->Name = L"Channel0TimeLeft";
			this->Channel0TimeLeft->Size = System::Drawing::Size(82, 32);
			this->Channel0TimeLeft->TabIndex = 110;
			this->Channel0TimeLeft->TabStop = false;
			this->Channel0TimeLeft->Text = L"0:00:00";
			// 
			// Channel2TimeGone
			// 
			this->Channel2TimeGone->BackColor = System::Drawing::Color::Transparent;
			this->Channel2TimeGone->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel2TimeGone->HighlightColor = System::Drawing::Color::Red;
			this->Channel2TimeGone->Highlighted = false;
			this->Channel2TimeGone->InfoText = L"Elapsed:";
			this->Channel2TimeGone->Location = System::Drawing::Point(675, 536);
			this->Channel2TimeGone->Name = L"Channel2TimeGone";
			this->Channel2TimeGone->Size = System::Drawing::Size(82, 32);
			this->Channel2TimeGone->TabIndex = 115;
			this->Channel2TimeGone->TabStop = false;
			this->Channel2TimeGone->Text = L"0:00:00";
			// 
			// Channel1TimeGone
			// 
			this->Channel1TimeGone->BackColor = System::Drawing::Color::Transparent;
			this->Channel1TimeGone->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel1TimeGone->HighlightColor = System::Drawing::Color::Red;
			this->Channel1TimeGone->Highlighted = false;
			this->Channel1TimeGone->InfoText = L"Elapsed:";
			this->Channel1TimeGone->Location = System::Drawing::Point(379, 536);
			this->Channel1TimeGone->Name = L"Channel1TimeGone";
			this->Channel1TimeGone->Size = System::Drawing::Size(82, 32);
			this->Channel1TimeGone->TabIndex = 112;
			this->Channel1TimeGone->TabStop = false;
			this->Channel1TimeGone->Text = L"0:00:00";
			// 
			// Channel0TimeGone
			// 
			this->Channel0TimeGone->BackColor = System::Drawing::Color::Transparent;
			this->Channel0TimeGone->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel0TimeGone->HighlightColor = System::Drawing::Color::Red;
			this->Channel0TimeGone->Highlighted = false;
			this->Channel0TimeGone->InfoText = L"Elapsed:";
			this->Channel0TimeGone->Location = System::Drawing::Point(83, 536);
			this->Channel0TimeGone->Name = L"Channel0TimeGone";
			this->Channel0TimeGone->Size = System::Drawing::Size(82, 32);
			this->Channel0TimeGone->TabIndex = 109;
			this->Channel0TimeGone->TabStop = false;
			this->Channel0TimeGone->Text = L"0:00:00";
			// 
			// Channel2LoadedText
			// 
			this->Channel2LoadedText->BackColor = System::Drawing::Color::Transparent;
			this->Channel2LoadedText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel2LoadedText->ForeColor = System::Drawing::Color::MidnightBlue;
			this->Channel2LoadedText->HighlightColor = System::Drawing::Color::MediumTurquoise;
			this->Channel2LoadedText->Highlighted = false;
			this->Channel2LoadedText->InfoText = L"";
			this->Channel2LoadedText->Location = System::Drawing::Point(675, 425);
			this->Channel2LoadedText->Name = L"Channel2LoadedText";
			this->Channel2LoadedText->Size = System::Drawing::Size(256, 30);
			this->Channel2LoadedText->TabIndex = 108;
			this->Channel2LoadedText->TabStop = false;
			this->Channel2LoadedText->Text = L"--NONE--";
			// 
			// Channel1LoadedText
			// 
			this->Channel1LoadedText->BackColor = System::Drawing::Color::Transparent;
			this->Channel1LoadedText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel1LoadedText->ForeColor = System::Drawing::Color::MidnightBlue;
			this->Channel1LoadedText->HighlightColor = System::Drawing::Color::MediumTurquoise;
			this->Channel1LoadedText->Highlighted = false;
			this->Channel1LoadedText->InfoText = L"";
			this->Channel1LoadedText->Location = System::Drawing::Point(379, 425);
			this->Channel1LoadedText->Name = L"Channel1LoadedText";
			this->Channel1LoadedText->Size = System::Drawing::Size(256, 30);
			this->Channel1LoadedText->TabIndex = 107;
			this->Channel1LoadedText->TabStop = false;
			this->Channel1LoadedText->Text = L"--NONE--";
			// 
			// Channel0LoadedText
			// 
			this->Channel0LoadedText->BackColor = System::Drawing::Color::Transparent;
			this->Channel0LoadedText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel0LoadedText->ForeColor = System::Drawing::Color::MidnightBlue;
			this->Channel0LoadedText->HighlightColor = System::Drawing::Color::MediumTurquoise;
			this->Channel0LoadedText->Highlighted = false;
			this->Channel0LoadedText->InfoText = L"";
			this->Channel0LoadedText->Location = System::Drawing::Point(83, 426);
			this->Channel0LoadedText->Name = L"Channel0LoadedText";
			this->Channel0LoadedText->Size = System::Drawing::Size(256, 30);
			this->Channel0LoadedText->TabIndex = 106;
			this->Channel0LoadedText->TabStop = false;
			this->Channel0LoadedText->Text = L"--NONE--";
			// 
			// Directory2Refresh
			// 
			this->Directory2Refresh->BackColor = System::Drawing::Color::Transparent;
			this->Directory2Refresh->DialogResult = System::Windows::Forms::DialogResult::None;
			this->Directory2Refresh->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Directory2Refresh->HighlightColor = System::Drawing::Color::Red;
			this->Directory2Refresh->Highlighted = false;
			this->Directory2Refresh->Location = System::Drawing::Point(619, 5);
			this->Directory2Refresh->Name = L"Directory2Refresh";
			this->Directory2Refresh->Size = System::Drawing::Size(200, 12);
			this->Directory2Refresh->TabIndex = 3;
			this->Directory2Refresh->Text = L"Adverts - Adverts - Adverts";
			this->Directory2Refresh->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::RefreshDirectory_Click);
			// 
			// Directory1Refresh
			// 
			this->Directory1Refresh->BackColor = System::Drawing::Color::Transparent;
			this->Directory1Refresh->DialogResult = System::Windows::Forms::DialogResult::None;
			this->Directory1Refresh->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Directory1Refresh->HighlightColor = System::Drawing::Color::Red;
			this->Directory1Refresh->Highlighted = false;
			this->Directory1Refresh->Location = System::Drawing::Point(411, 5);
			this->Directory1Refresh->Name = L"Directory1Refresh";
			this->Directory1Refresh->Size = System::Drawing::Size(200, 12);
			this->Directory1Refresh->TabIndex = 2;
			this->Directory1Refresh->Text = L"Beds - Beds - Beds";
			this->Directory1Refresh->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::RefreshDirectory_Click);
			// 
			// feedbackButton
			// 
			this->feedbackButton->BackColor = System::Drawing::Color::Transparent;
			this->feedbackButton->DialogResult = System::Windows::Forms::DialogResult::None;
			this->feedbackButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->feedbackButton->HighlightColor = System::Drawing::Color::Red;
			this->feedbackButton->Highlighted = false;
			this->feedbackButton->Location = System::Drawing::Point(899, 5);
			this->feedbackButton->Name = L"feedbackButton";
			this->feedbackButton->Size = System::Drawing::Size(57, 18);
			this->feedbackButton->TabIndex = 8;
			this->feedbackButton->Text = L"Feedback";
			this->feedbackButton->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::feedbackButton_Click);
			// 
			// Directory0Refresh
			// 
			this->Directory0Refresh->BackColor = System::Drawing::Color::Transparent;
			this->Directory0Refresh->DialogResult = System::Windows::Forms::DialogResult::None;
			this->Directory0Refresh->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Directory0Refresh->HighlightColor = System::Drawing::Color::Red;
			this->Directory0Refresh->Highlighted = false;
			this->Directory0Refresh->Location = System::Drawing::Point(205, 5);
			this->Directory0Refresh->Name = L"Directory0Refresh";
			this->Directory0Refresh->Size = System::Drawing::Size(200, 12);
			this->Directory0Refresh->TabIndex = 1;
			this->Directory0Refresh->Text = L"Jingles - Jingles - Jingles";
			this->Directory0Refresh->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::RefreshDirectory_Click);
			// 
			// helpButton
			// 
			this->helpButton->BackColor = System::Drawing::Color::Transparent;
			this->helpButton->DialogResult = System::Windows::Forms::DialogResult::None;
			this->helpButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->helpButton->HighlightColor = System::Drawing::Color::Red;
			this->helpButton->Highlighted = false;
			this->helpButton->Location = System::Drawing::Point(847, 5);
			this->helpButton->Name = L"helpButton";
			this->helpButton->Size = System::Drawing::Size(42, 18);
			this->helpButton->TabIndex = 7;
			this->helpButton->Text = L"Help";
			this->helpButton->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::helpButton_Click);
			// 
			// bapsButton1
			// 
			this->bapsButton1->BackColor = System::Drawing::Color::Transparent;
			this->bapsButton1->DialogResult = System::Windows::Forms::DialogResult::None;
			this->bapsButton1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->bapsButton1->HighlightColor = System::Drawing::Color::Red;
			this->bapsButton1->Highlighted = false;
			this->bapsButton1->Location = System::Drawing::Point(847, 27);
			this->bapsButton1->Name = L"bapsButton1";
			this->bapsButton1->Size = System::Drawing::Size(109, 64);
			this->bapsButton1->TabIndex = 9;
			this->bapsButton1->Text = L"Search Record Library";
			this->bapsButton1->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::SearchRecordLib_Click);
			// 
			// Channel2Play
			// 
			this->Channel2Play->BackColor = System::Drawing::Color::Transparent;
			this->Channel2Play->DialogResult = System::Windows::Forms::DialogResult::None;
			this->Channel2Play->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel2Play->HighlightColor = System::Drawing::Color::DarkGreen;
			this->Channel2Play->Highlighted = false;
			this->Channel2Play->Location = System::Drawing::Point(675, 402);
			this->Channel2Play->Name = L"Channel2Play";
			this->Channel2Play->Size = System::Drawing::Size(72, 19);
			this->Channel2Play->TabIndex = 22;
			this->Channel2Play->Text = L"F9 - Play";
			this->Channel2Play->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// loadShowButton
			// 
			this->loadShowButton->BackColor = System::Drawing::Color::Transparent;
			this->loadShowButton->DialogResult = System::Windows::Forms::DialogResult::None;
			this->loadShowButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->loadShowButton->HighlightColor = System::Drawing::Color::Red;
			this->loadShowButton->Highlighted = false;
			this->loadShowButton->Location = System::Drawing::Point(63, 22);
			this->loadShowButton->Name = L"loadShowButton";
			this->loadShowButton->Size = System::Drawing::Size(109, 69);
			this->loadShowButton->TabIndex = 0;
			this->loadShowButton->Text = L"Load Show";
			this->loadShowButton->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::loadShow_Click);
			// 
			// Channel1Play
			// 
			this->Channel1Play->BackColor = System::Drawing::Color::Transparent;
			this->Channel1Play->DialogResult = System::Windows::Forms::DialogResult::None;
			this->Channel1Play->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel1Play->HighlightColor = System::Drawing::Color::DarkGreen;
			this->Channel1Play->Highlighted = false;
			this->Channel1Play->Location = System::Drawing::Point(379, 402);
			this->Channel1Play->Name = L"Channel1Play";
			this->Channel1Play->Size = System::Drawing::Size(72, 19);
			this->Channel1Play->TabIndex = 19;
			this->Channel1Play->Text = L"F5 - Play";
			this->Channel1Play->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel2Stop
			// 
			this->Channel2Stop->BackColor = System::Drawing::Color::Transparent;
			this->Channel2Stop->DialogResult = System::Windows::Forms::DialogResult::None;
			this->Channel2Stop->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel2Stop->HighlightColor = System::Drawing::Color::Firebrick;
			this->Channel2Stop->Highlighted = false;
			this->Channel2Stop->Location = System::Drawing::Point(859, 402);
			this->Channel2Stop->Name = L"Channel2Stop";
			this->Channel2Stop->Size = System::Drawing::Size(72, 19);
			this->Channel2Stop->TabIndex = 24;
			this->Channel2Stop->Text = L"F11 - Stop";
			this->Channel2Stop->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel1Stop
			// 
			this->Channel1Stop->BackColor = System::Drawing::Color::Transparent;
			this->Channel1Stop->DialogResult = System::Windows::Forms::DialogResult::None;
			this->Channel1Stop->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel1Stop->HighlightColor = System::Drawing::Color::Firebrick;
			this->Channel1Stop->Highlighted = false;
			this->Channel1Stop->Location = System::Drawing::Point(563, 402);
			this->Channel1Stop->Name = L"Channel1Stop";
			this->Channel1Stop->Size = System::Drawing::Size(72, 19);
			this->Channel1Stop->TabIndex = 21;
			this->Channel1Stop->Text = L"F7 - Stop";
			this->Channel1Stop->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel2Pause
			// 
			this->Channel2Pause->BackColor = System::Drawing::Color::Transparent;
			this->Channel2Pause->DialogResult = System::Windows::Forms::DialogResult::None;
			this->Channel2Pause->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel2Pause->HighlightColor = System::Drawing::Color::DarkOrange;
			this->Channel2Pause->Highlighted = false;
			this->Channel2Pause->Location = System::Drawing::Point(767, 402);
			this->Channel2Pause->Name = L"Channel2Pause";
			this->Channel2Pause->Size = System::Drawing::Size(72, 19);
			this->Channel2Pause->TabIndex = 23;
			this->Channel2Pause->Text = L"F10 - Pause";
			this->Channel2Pause->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel1Pause
			// 
			this->Channel1Pause->BackColor = System::Drawing::Color::Transparent;
			this->Channel1Pause->DialogResult = System::Windows::Forms::DialogResult::None;
			this->Channel1Pause->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel1Pause->HighlightColor = System::Drawing::Color::DarkOrange;
			this->Channel1Pause->Highlighted = false;
			this->Channel1Pause->Location = System::Drawing::Point(471, 402);
			this->Channel1Pause->Name = L"Channel1Pause";
			this->Channel1Pause->Size = System::Drawing::Size(72, 19);
			this->Channel1Pause->TabIndex = 20;
			this->Channel1Pause->Text = L"F6 - Pause";
			this->Channel1Pause->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel0Pause
			// 
			this->Channel0Pause->BackColor = System::Drawing::Color::Transparent;
			this->Channel0Pause->DialogResult = System::Windows::Forms::DialogResult::None;
			this->Channel0Pause->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel0Pause->HighlightColor = System::Drawing::Color::DarkOrange;
			this->Channel0Pause->Highlighted = false;
			this->Channel0Pause->Location = System::Drawing::Point(175, 402);
			this->Channel0Pause->Name = L"Channel0Pause";
			this->Channel0Pause->Size = System::Drawing::Size(72, 19);
			this->Channel0Pause->TabIndex = 17;
			this->Channel0Pause->Text = L"F2 - Pause";
			this->Channel0Pause->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel0Stop
			// 
			this->Channel0Stop->BackColor = System::Drawing::Color::Transparent;
			this->Channel0Stop->DialogResult = System::Windows::Forms::DialogResult::None;
			this->Channel0Stop->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel0Stop->HighlightColor = System::Drawing::Color::Firebrick;
			this->Channel0Stop->Highlighted = false;
			this->Channel0Stop->Location = System::Drawing::Point(267, 402);
			this->Channel0Stop->Name = L"Channel0Stop";
			this->Channel0Stop->Size = System::Drawing::Size(72, 19);
			this->Channel0Stop->TabIndex = 18;
			this->Channel0Stop->Text = L"F3 - Stop";
			this->Channel0Stop->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel0Play
			// 
			this->Channel0Play->BackColor = System::Drawing::Color::Transparent;
			this->Channel0Play->DialogResult = System::Windows::Forms::DialogResult::None;
			this->Channel0Play->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel0Play->HighlightColor = System::Drawing::Color::DarkGreen;
			this->Channel0Play->Highlighted = false;
			this->Channel0Play->Location = System::Drawing::Point(83, 402);
			this->Channel0Play->Name = L"Channel0Play";
			this->Channel0Play->Size = System::Drawing::Size(72, 19);
			this->Channel0Play->TabIndex = 16;
			this->Channel0Play->Text = L"F1 - Play";
			this->Channel0Play->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// trackList2
			// 
			this->trackList2->AllowDrop = true;
			this->trackList2->Channel = 2;
			this->trackList2->ContextMenuStrip = this->trackListContextMenuStrip;
			this->trackList2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->trackList2->Location = System::Drawing::Point(675, 118);
			this->trackList2->Name = L"trackList2";
			this->trackList2->Size = System::Drawing::Size(256, 280);
			this->trackList2->TabIndex = 14;
			this->trackList2->Text = L"trackList2";
			this->trackList2->RequestChange += gcnew BAPSPresenter::RequestChangeEventHandler(this, &BAPSPresenterMain::TrackList_RequestChange);
			// 
			// trackList1
			// 
			this->trackList1->AllowDrop = true;
			this->trackList1->Channel = 1;
			this->trackList1->ContextMenuStrip = this->trackListContextMenuStrip;
			this->trackList1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->trackList1->Location = System::Drawing::Point(377, 118);
			this->trackList1->Name = L"trackList1";
			this->trackList1->Size = System::Drawing::Size(256, 280);
			this->trackList1->TabIndex = 12;
			this->trackList1->Text = L"trackList1";
			this->trackList1->RequestChange += gcnew BAPSPresenter::RequestChangeEventHandler(this, &BAPSPresenterMain::TrackList_RequestChange);
			// 
			// trackList0
			// 
			this->trackList0->AllowDrop = true;
			this->trackList0->BackColor = System::Drawing::Color::SeaShell;
			this->trackList0->Channel = 0;
			this->trackList0->ContextMenuStrip = this->trackListContextMenuStrip;
			this->trackList0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->trackList0->Location = System::Drawing::Point(83, 118);
			this->trackList0->Name = L"trackList0";
			this->trackList0->Size = System::Drawing::Size(256, 280);
			this->trackList0->TabIndex = 10;
			this->trackList0->Text = L"trackList0";
			this->trackList0->RequestChange += gcnew BAPSPresenter::RequestChangeEventHandler(this, &BAPSPresenterMain::TrackList_RequestChange);
			// 
			// trackTime2
			// 
			this->trackTime2->BackColor = System::Drawing::Color::Transparent;
			this->trackTime2->Channel = 2;
			this->trackTime2->CuePosition = 0;
			this->trackTime2->Duration = 0;
			this->trackTime2->IntroPosition = 0;
			this->trackTime2->Location = System::Drawing::Point(675, 459);
			this->trackTime2->Name = L"trackTime2";
			this->trackTime2->Position = 0;
			this->trackTime2->SilencePosition = 0;
			this->trackTime2->Size = System::Drawing::Size(256, 72);
			this->trackTime2->TabIndex = 27;
			this->trackTime2->Text = L"trackTime2";
			// 
			// trackTime1
			// 
			this->trackTime1->BackColor = System::Drawing::Color::Transparent;
			this->trackTime1->Channel = 1;
			this->trackTime1->CuePosition = 0;
			this->trackTime1->Duration = 0;
			this->trackTime1->IntroPosition = 0;
			this->trackTime1->Location = System::Drawing::Point(379, 459);
			this->trackTime1->Name = L"trackTime1";
			this->trackTime1->Position = 0;
			this->trackTime1->SilencePosition = 0;
			this->trackTime1->Size = System::Drawing::Size(256, 72);
			this->trackTime1->TabIndex = 26;
			this->trackTime1->Text = L"trackTime1";
			// 
			// trackTime0
			// 
			this->trackTime0->BackColor = System::Drawing::Color::Transparent;
			this->trackTime0->Channel = 0;
			this->trackTime0->CuePosition = 0;
			this->trackTime0->Duration = 0;
			this->trackTime0->IntroPosition = 0;
			this->trackTime0->Location = System::Drawing::Point(83, 459);
			this->trackTime0->Name = L"trackTime0";
			this->trackTime0->Position = 0;
			this->trackTime0->SilencePosition = 0;
			this->trackTime0->Size = System::Drawing::Size(256, 72);
			this->trackTime0->TabIndex = 25;
			this->trackTime0->Text = L"trackTime0";
			// 
			// BAPSPresenterMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(202)), static_cast<System::Int32>(static_cast<System::Byte>(202)), 
				static_cast<System::Int32>(static_cast<System::Byte>(202)));
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(1024, 733);
			this->ControlBox = false;
			this->Controls->Add(this->chatOnOff);
			this->Controls->Add(this->timeLine);
			this->Controls->Add(this->sendMessage);
			this->Controls->Add(this->chatTo);
			this->Controls->Add(this->newMessageLabel);
			this->Controls->Add(this->newChatMessage);
			this->Controls->Add(this->chatText);
			this->Controls->Add(this->MainTextDisplay);
			this->Controls->Add(this->Channel2Label);
			this->Controls->Add(this->Channel1Label);
			this->Controls->Add(this->Channel0Label);
			this->Controls->Add(this->Directory2);
			this->Controls->Add(this->Directory1);
			this->Controls->Add(this->Directory0);
			this->Controls->Add(this->Channel2Length);
			this->Controls->Add(this->Channel1Length);
			this->Controls->Add(this->Channel0Length);
			this->Controls->Add(this->Channel2TimeLeft);
			this->Controls->Add(this->Channel1TimeLeft);
			this->Controls->Add(this->Channel0TimeLeft);
			this->Controls->Add(this->Channel2TimeGone);
			this->Controls->Add(this->Channel1TimeGone);
			this->Controls->Add(this->Channel0TimeGone);
			this->Controls->Add(this->Channel2LoadedText);
			this->Controls->Add(this->Channel1LoadedText);
			this->Controls->Add(this->Channel0LoadedText);
			this->Controls->Add(this->Directory2Refresh);
			this->Controls->Add(this->Directory1Refresh);
			this->Controls->Add(this->feedbackButton);
			this->Controls->Add(this->Directory0Refresh);
			this->Controls->Add(this->helpButton);
			this->Controls->Add(this->bapsButton1);
			this->Controls->Add(this->Channel2Play);
			this->Controls->Add(this->loadShowButton);
			this->Controls->Add(this->Channel1Play);
			this->Controls->Add(this->Channel2Stop);
			this->Controls->Add(this->Channel1Stop);
			this->Controls->Add(this->Channel2Pause);
			this->Controls->Add(this->Channel1Pause);
			this->Controls->Add(this->Channel0Pause);
			this->Controls->Add(this->Channel0Stop);
			this->Controls->Add(this->Channel0Play);
			this->Controls->Add(this->trackList2);
			this->Controls->Add(this->trackList1);
			this->Controls->Add(this->trackList0);
			this->Controls->Add(this->trackTime2);
			this->Controls->Add(this->trackTime1);
			this->Controls->Add(this->trackTime0);
			this->Controls->Add(this->Channel2VolLabel);
			this->Controls->Add(this->Channel1VolLabel);
			this->Controls->Add(this->Channel0VolLabel);
			this->Controls->Add(this->Channel2VolumeBar);
			this->Controls->Add(this->Channel1VolumeBar);
			this->Controls->Add(this->Channel0VolumeBar);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->KeyPreview = true;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"BAPSPresenterMain";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->Text = L"BAPS Presenter";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &BAPSPresenterMain::BAPSPresenterMain_KeyDown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Channel2VolumeBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Channel1VolumeBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Channel0VolumeBar))->EndInit();
			this->trackListContextMenuStrip->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
};
}

