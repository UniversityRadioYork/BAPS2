#pragma once

#include "decodeStructs.h"
#include "Globals.h"
#include "RecordLibrarySearch.h"
#include "ConfigDialog.h"
#include "LoadShowDialog.h"
#include "SecurityDialog.h"
#include "ClientHelpers.h"
#include "About.h"
#include "AudioWall.h"
#include "TextDialog.h"
#include "TrackTime.h"
#include "TrackList.h"
#include "BAPSButton.h"
#include "BAPSLabel.h"
#include "BAPSListBox.h"
#include "TimeLine.h"
#include "ConfigManager.h"

#define DISABLE_INDEX_CHANGE() 	channelList[channel]->Enabled=false;\
								channelList[channel]->remove_SelectedIndexChanged( gcnew System::EventHandler(this, &BAPSPresenterMain::LoadNewIndex_Event));

#define ENABLE_INDEX_CHANGE()	channelList[channel]->add_SelectedIndexChanged( gcnew System::EventHandler(this, &BAPSPresenterMain::LoadNewIndex_Event));\
								channelList[channel]->Enabled=true;

namespace BAPSPresenter {

	ref class RecordLibrarySearch;
	ref class ConfigDialog;
	ref class SecurityDialog;
	ref class About;
	ref class LoadShowDialog;

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
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
		/*void showVolume(System::Object^ _channel, System::Object^ _value);*/
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
		void addLibraryResult(u32int index, int dirtyStatus, System::String^ result);
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
		void clearFiles(System::Object^ _directoryIndex, System::String^ niceDirectoryName);
		void displayVersion(System::String^ version, System::String^ date, System::String^ time, System::String^ author);
		//void processFeedbackResult(int resultCode);
		//void addToChatList(System::String^ username);
		//void removeFromChatList(System::String^ username);
		//void processChatMessage(System::String^ from, System::String^ to, System::String^ message);

		/** Show or hide the volume controls **/
		/*void showVolumeControls(bool shouldShow);*/
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
		TextDialog^ textDialog;
		AudioWall^ audioWall;
		
		/** Arrays with channel number indices for easy updating **/
		array<System::Windows::Forms::ListBox^>^	directoryList;
		array<System::Windows::Forms::Button^>^		directoryRefresh;
		array<System::Windows::Forms::Label^>^		loadedText;
		array<BAPSLabel^>^		trackLengthText;
		array<BAPSLabel^>^		timeLeftText;
		array<BAPSLabel^>^		timeGoneText;
		/*array<System::Windows::Forms::TrackBar^>^	volumeBar;*/
		array<System::Windows::Forms::Button^>^		channelPlay;
		array<System::Windows::Forms::Button^>^		channelPause;
		array<System::Windows::Forms::Button^>^		channelStop;
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



private: System::Windows::Forms::ToolStripMenuItem^  repeatOneToolStripMenuItem;
private: System::Windows::Forms::TextBox^  MainTextDisplay;







private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator4;
private: System::Windows::Forms::ToolStripMenuItem^  showAudioWallToolStripMenuItem;
private: BAPSPresenter::TimeLine^  timeLine;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::Label^  label4;
private: System::Windows::Forms::ListBox^  Directory0;
private: System::Windows::Forms::ListBox^  Directory1;
private: System::Windows::Forms::ListBox^  Directory2;
private: System::Windows::Forms::Button^  loadShowButton;
private: System::Windows::Forms::Button^  bapsButton1;
private: System::Windows::Forms::Button^  Directory0Refresh;
private: System::Windows::Forms::Button^  Directory1Refresh;
private: System::Windows::Forms::Button^  Directory2Refresh;
private: System::Windows::Forms::Button^  button1;
private: System::Windows::Forms::Button^  button2;
private: System::Windows::Forms::Button^  button3;
private: System::Windows::Forms::Button^  Channel0Play;
private: System::Windows::Forms::Button^  Channel0Pause;
private: System::Windows::Forms::Button^  Channel0Stop;
private: System::Windows::Forms::Button^  Channel1Play;
private: System::Windows::Forms::Button^  Channel1Pause;
private: System::Windows::Forms::Button^  Channel1Stop;
private: System::Windows::Forms::Button^  Channel2Play;
private: System::Windows::Forms::Button^  Channel2Pause;
private: System::Windows::Forms::Button^  Channel2Stop;
private: System::Windows::Forms::Label^  Channel0LoadedText;
private: System::Windows::Forms::Label^  Channel1LoadedText;
private: System::Windows::Forms::Label^  Channel2LoadedText;





		 array<BAPSPresenter::TrackList^>^ trackList;

		/** ### END PRIVATE VARIABLES ### **/
		/** ### DESIGNER PRIVATE EVENT HANDLERS ### **/
public:
		System::Void BAPSPresenterMain_KeyDown(System::Object ^  sender, System::Windows::Forms::KeyEventArgs ^  e);
private:
		System::Void TrackBar_Scroll(System::Object ^  sender, System::EventArgs ^  e);
		/*System::Void VolumeBar_Scroll(System::Object ^  sender, System::EventArgs ^  e);*/
	
		System::Void RefreshDirectory_Click(System::Object ^  sender, System::EventArgs ^  e);
		//System::Void newChatMessage_TextChanged(System::Object^  sender, System::EventArgs^  e);
		//System::Void helpButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void SearchRecordLib_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void loadShow_Click(System::Object ^  sender, System::EventArgs ^  e);
		//System::Void sendMessage_Click(System::Object^  sender, System::EventArgs^  e);
		//System::Void feedbackButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void Directory_MouseDown(System::Object ^  sender, System::Windows::Forms::MouseEventArgs ^  e);
		//System::Void chatOnOff_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void ChannelOperation_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void TrackList_RequestChange(System::Object^  o, BAPSPresenter::RequestChangeEventArgs^  e);
		System::Void trackListContextMenuStrip_Opening(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e);
		System::Void trackListContextMenuStrip_ItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e);
		System::Void loadImpossibleFlicker(System::Object ^  sender, System::EventArgs ^  e);
		System::Void nearEndFlash(System::Object ^  sender, System::EventArgs ^  e);
		 System::Void ChannelLength_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
		System::Void countdownTick(System::Object ^  sender, System::EventArgs ^  e);
		System::Void timeLine_StartTimeChanged(System::Object^  sender, BAPSPresenter::TimeLineEventArgs^  e);

















	private: BAPSPresenter::BAPSLabel^  Channel0TimeGone;
	private: BAPSPresenter::BAPSLabel^  Channel0TimeLeft;
	private: BAPSPresenter::BAPSLabel^  Channel0Length;
	private: BAPSPresenter::BAPSLabel^  Channel1TimeGone;
	private: BAPSPresenter::BAPSLabel^  Channel1TimeLeft;
	private: BAPSPresenter::BAPSLabel^  Channel1Length;
	private: BAPSPresenter::BAPSLabel^  Channel2TimeGone;
	private: BAPSPresenter::BAPSLabel^  Channel2TimeLeft;
	private: BAPSPresenter::BAPSLabel^  Channel2Length;












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
			this->Directory0 = (gcnew System::Windows::Forms::ListBox());
			this->Directory1 = (gcnew System::Windows::Forms::ListBox());
			this->Directory2 = (gcnew System::Windows::Forms::ListBox());
			this->loadShowButton = (gcnew System::Windows::Forms::Button());
			this->bapsButton1 = (gcnew System::Windows::Forms::Button());
			this->Directory0Refresh = (gcnew System::Windows::Forms::Button());
			this->Directory1Refresh = (gcnew System::Windows::Forms::Button());
			this->Directory2Refresh = (gcnew System::Windows::Forms::Button());
			this->Channel0Play = (gcnew System::Windows::Forms::Button());
			this->Channel0Pause = (gcnew System::Windows::Forms::Button());
			this->Channel0Stop = (gcnew System::Windows::Forms::Button());
			this->Channel1Play = (gcnew System::Windows::Forms::Button());
			this->Channel1Pause = (gcnew System::Windows::Forms::Button());
			this->Channel1Stop = (gcnew System::Windows::Forms::Button());
			this->Channel2Play = (gcnew System::Windows::Forms::Button());
			this->Channel2Pause = (gcnew System::Windows::Forms::Button());
			this->Channel2Stop = (gcnew System::Windows::Forms::Button());
			this->Channel0LoadedText = (gcnew System::Windows::Forms::Label());
			this->Channel1LoadedText = (gcnew System::Windows::Forms::Label());
			this->Channel2LoadedText = (gcnew System::Windows::Forms::Label());
			this->timeLine = (gcnew BAPSPresenter::TimeLine());
			this->Channel2Length = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel1TimeLeft = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel1Length = (gcnew BAPSPresenter::BAPSLabel());
			this->trackList0 = (gcnew BAPSPresenter::TrackList());
			this->Channel0Length = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel2TimeLeft = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel0TimeLeft = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel1TimeGone = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel2TimeGone = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel0TimeGone = (gcnew BAPSPresenter::BAPSLabel());
			this->trackList2 = (gcnew BAPSPresenter::TrackList());
			this->trackList1 = (gcnew BAPSPresenter::TrackList());
			this->trackTime1 = (gcnew BAPSPresenter::TrackTime());
			this->trackTime2 = (gcnew BAPSPresenter::TrackTime());
			this->trackTime0 = (gcnew BAPSPresenter::TrackTime());
			this->trackListContextMenuStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// trackListContextMenuStrip
			// 
			this->trackListContextMenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(12) {this->resetChannelStripMenuItem, 
				this->toolStripSeparator2, this->deleteItemToolStripMenuItem, this->toolStripSeparator3, this->automaticAdvanceToolStripMenuItem, 
				this->playOnLoadToolStripMenuItem, this->toolStripSeparator1, this->repeatAllToolStripMenuItem, this->repeatOneToolStripMenuItem, 
				this->repeatNoneToolStripMenuItem, this->toolStripSeparator4, this->showAudioWallToolStripMenuItem});
			this->trackListContextMenuStrip->Name = L"trackListContextMenuStrip";
			this->trackListContextMenuStrip->ShowCheckMargin = true;
			this->trackListContextMenuStrip->ShowImageMargin = false;
			this->trackListContextMenuStrip->Size = System::Drawing::Size(178, 204);
			this->trackListContextMenuStrip->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &BAPSPresenterMain::trackListContextMenuStrip_ItemClicked);
			this->trackListContextMenuStrip->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &BAPSPresenterMain::trackListContextMenuStrip_Opening);
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
			this->MainTextDisplay->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->MainTextDisplay->Font = (gcnew System::Drawing::Font(L"Tahoma", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->MainTextDisplay->Location = System::Drawing::Point(8, 647);
			this->MainTextDisplay->Multiline = true;
			this->MainTextDisplay->Name = L"MainTextDisplay";
			this->MainTextDisplay->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->MainTextDisplay->Size = System::Drawing::Size(1024, 82);
			this->MainTextDisplay->TabIndex = 29;
			this->MainTextDisplay->Text = L"<You can type notes here>";
			// 
			// Directory0
			// 
			this->Directory0->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->Directory0->Location = System::Drawing::Point(12, 116);
			this->Directory0->Name = L"Directory0";
			this->Directory0->Size = System::Drawing::Size(234, 132);
			this->Directory0->TabIndex = 215;
			this->Directory0->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &BAPSPresenterMain::Directory_MouseDown);
			// 
			// Directory1
			// 
			this->Directory1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->Directory1->Location = System::Drawing::Point(12, 276);
			this->Directory1->Name = L"Directory1";
			this->Directory1->Size = System::Drawing::Size(234, 132);
			this->Directory1->TabIndex = 216;
			this->Directory1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &BAPSPresenterMain::Directory_MouseDown);
			// 
			// Directory2
			// 
			this->Directory2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->Directory2->Location = System::Drawing::Point(12, 436);
			this->Directory2->Name = L"Directory2";
			this->Directory2->Size = System::Drawing::Size(234, 132);
			this->Directory2->TabIndex = 217;
			this->Directory2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &BAPSPresenterMain::Directory_MouseDown);
			// 
			// loadShowButton
			// 
			this->loadShowButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->loadShowButton->Font = (gcnew System::Drawing::Font(L"Tahoma", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->loadShowButton->Location = System::Drawing::Point(12, 12);
			this->loadShowButton->Name = L"loadShowButton";
			this->loadShowButton->Size = System::Drawing::Size(114, 64);
			this->loadShowButton->TabIndex = 218;
			this->loadShowButton->Text = L"Load Show";
			this->loadShowButton->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::loadShow_Click);
			// 
			// bapsButton1
			// 
			this->bapsButton1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bapsButton1->Font = (gcnew System::Drawing::Font(L"Tahoma", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->bapsButton1->Location = System::Drawing::Point(132, 12);
			this->bapsButton1->Name = L"bapsButton1";
			this->bapsButton1->Size = System::Drawing::Size(114, 64);
			this->bapsButton1->TabIndex = 219;
			this->bapsButton1->Text = L"Search Library";
			this->bapsButton1->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::SearchRecordLib_Click);
			// 
			// Directory0Refresh
			// 
			this->Directory0Refresh->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Directory0Refresh->Location = System::Drawing::Point(12, 94);
			this->Directory0Refresh->Name = L"Directory0Refresh";
			this->Directory0Refresh->Size = System::Drawing::Size(234, 23);
			this->Directory0Refresh->TabIndex = 220;
			this->Directory0Refresh->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::RefreshDirectory_Click);
			// 
			// Directory1Refresh
			// 
			this->Directory1Refresh->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Directory1Refresh->Location = System::Drawing::Point(12, 254);
			this->Directory1Refresh->Name = L"Directory1Refresh";
			this->Directory1Refresh->Size = System::Drawing::Size(234, 23);
			this->Directory1Refresh->TabIndex = 221;
			this->Directory1Refresh->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::RefreshDirectory_Click);
			// 
			// Directory2Refresh
			// 
			this->Directory2Refresh->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Directory2Refresh->Location = System::Drawing::Point(12, 414);
			this->Directory2Refresh->Name = L"Directory2Refresh";
			this->Directory2Refresh->Size = System::Drawing::Size(234, 23);
			this->Directory2Refresh->TabIndex = 222;
			this->Directory2Refresh->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::RefreshDirectory_Click);
			// 
			// Channel0Play
			// 
			this->Channel0Play->BackColor = System::Drawing::SystemColors::Control;
			this->Channel0Play->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Channel0Play->Location = System::Drawing::Point(252, 415);
			this->Channel0Play->Name = L"Channel0Play";
			this->Channel0Play->Size = System::Drawing::Size(75, 23);
			this->Channel0Play->TabIndex = 223;
			this->Channel0Play->Text = L"F1 - Play";
			this->Channel0Play->UseVisualStyleBackColor = false;
			this->Channel0Play->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel0Pause
			// 
			this->Channel0Pause->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Channel0Pause->Location = System::Drawing::Point(343, 415);
			this->Channel0Pause->Name = L"Channel0Pause";
			this->Channel0Pause->Size = System::Drawing::Size(75, 23);
			this->Channel0Pause->TabIndex = 223;
			this->Channel0Pause->Text = L"F2 - Pause";
			this->Channel0Pause->UseVisualStyleBackColor = true;
			this->Channel0Pause->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel0Stop
			// 
			this->Channel0Stop->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Channel0Stop->Location = System::Drawing::Point(433, 415);
			this->Channel0Stop->Name = L"Channel0Stop";
			this->Channel0Stop->Size = System::Drawing::Size(75, 23);
			this->Channel0Stop->TabIndex = 223;
			this->Channel0Stop->Text = L"F3 - Stop";
			this->Channel0Stop->UseVisualStyleBackColor = true;
			this->Channel0Stop->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel1Play
			// 
			this->Channel1Play->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Channel1Play->Location = System::Drawing::Point(514, 415);
			this->Channel1Play->Name = L"Channel1Play";
			this->Channel1Play->Size = System::Drawing::Size(75, 23);
			this->Channel1Play->TabIndex = 223;
			this->Channel1Play->Text = L"F1 - Play";
			this->Channel1Play->UseVisualStyleBackColor = true;
			this->Channel1Play->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel1Pause
			// 
			this->Channel1Pause->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Channel1Pause->Location = System::Drawing::Point(604, 415);
			this->Channel1Pause->Name = L"Channel1Pause";
			this->Channel1Pause->Size = System::Drawing::Size(75, 23);
			this->Channel1Pause->TabIndex = 223;
			this->Channel1Pause->Text = L"F2 - Pause";
			this->Channel1Pause->UseVisualStyleBackColor = true;
			this->Channel1Pause->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel1Stop
			// 
			this->Channel1Stop->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Channel1Stop->Location = System::Drawing::Point(695, 415);
			this->Channel1Stop->Name = L"Channel1Stop";
			this->Channel1Stop->Size = System::Drawing::Size(75, 23);
			this->Channel1Stop->TabIndex = 223;
			this->Channel1Stop->Text = L"F3 - Stop";
			this->Channel1Stop->UseVisualStyleBackColor = true;
			this->Channel1Stop->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel2Play
			// 
			this->Channel2Play->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Channel2Play->Location = System::Drawing::Point(776, 415);
			this->Channel2Play->Name = L"Channel2Play";
			this->Channel2Play->Size = System::Drawing::Size(75, 23);
			this->Channel2Play->TabIndex = 223;
			this->Channel2Play->Text = L"F1 - Play";
			this->Channel2Play->UseVisualStyleBackColor = true;
			this->Channel2Play->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel2Pause
			// 
			this->Channel2Pause->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Channel2Pause->Location = System::Drawing::Point(866, 415);
			this->Channel2Pause->Name = L"Channel2Pause";
			this->Channel2Pause->Size = System::Drawing::Size(75, 23);
			this->Channel2Pause->TabIndex = 223;
			this->Channel2Pause->Text = L"F2 - Pause";
			this->Channel2Pause->UseVisualStyleBackColor = true;
			this->Channel2Pause->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel2Stop
			// 
			this->Channel2Stop->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Channel2Stop->Location = System::Drawing::Point(957, 415);
			this->Channel2Stop->Name = L"Channel2Stop";
			this->Channel2Stop->Size = System::Drawing::Size(75, 23);
			this->Channel2Stop->TabIndex = 223;
			this->Channel2Stop->Text = L"F3 - Stop";
			this->Channel2Stop->UseVisualStyleBackColor = true;
			this->Channel2Stop->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel0LoadedText
			// 
			this->Channel0LoadedText->AutoEllipsis = true;
			this->Channel0LoadedText->BackColor = System::Drawing::SystemColors::Window;
			this->Channel0LoadedText->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->Channel0LoadedText->ForeColor = System::Drawing::Color::MidnightBlue;
			this->Channel0LoadedText->Location = System::Drawing::Point(252, 441);
			this->Channel0LoadedText->Name = L"Channel0LoadedText";
			this->Channel0LoadedText->Size = System::Drawing::Size(256, 30);
			this->Channel0LoadedText->TabIndex = 224;
			this->Channel0LoadedText->Text = L"--NONE--";
			this->Channel0LoadedText->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Channel1LoadedText
			// 
			this->Channel1LoadedText->AutoEllipsis = true;
			this->Channel1LoadedText->BackColor = System::Drawing::SystemColors::Window;
			this->Channel1LoadedText->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->Channel1LoadedText->ForeColor = System::Drawing::Color::MidnightBlue;
			this->Channel1LoadedText->Location = System::Drawing::Point(514, 441);
			this->Channel1LoadedText->Name = L"Channel1LoadedText";
			this->Channel1LoadedText->Size = System::Drawing::Size(256, 30);
			this->Channel1LoadedText->TabIndex = 224;
			this->Channel1LoadedText->Text = L"--NONE--";
			this->Channel1LoadedText->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Channel2LoadedText
			// 
			this->Channel2LoadedText->AutoEllipsis = true;
			this->Channel2LoadedText->BackColor = System::Drawing::SystemColors::Window;
			this->Channel2LoadedText->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->Channel2LoadedText->ForeColor = System::Drawing::Color::MidnightBlue;
			this->Channel2LoadedText->Location = System::Drawing::Point(776, 441);
			this->Channel2LoadedText->Name = L"Channel2LoadedText";
			this->Channel2LoadedText->Size = System::Drawing::Size(256, 30);
			this->Channel2LoadedText->TabIndex = 224;
			this->Channel2LoadedText->Text = L"--NONE--";
			this->Channel2LoadedText->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// timeLine
			// 
			this->timeLine->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->timeLine->Location = System::Drawing::Point(12, 589);
			this->timeLine->Name = L"timeLine";
			this->timeLine->Size = System::Drawing::Size(1020, 52);
			this->timeLine->TabIndex = 214;
			this->timeLine->TabStop = false;
			this->timeLine->Text = L"timeLine1";
			this->timeLine->StartTimeChanged += gcnew BAPSPresenter::TimeLineEventHandler(this, &BAPSPresenterMain::timeLine_StartTimeChanged);
			// 
			// Channel2Length
			// 
			this->Channel2Length->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel2Length->HighlightColor = System::Drawing::Color::Red;
			this->Channel2Length->Highlighted = false;
			this->Channel2Length->InfoText = L"End At: 59:50";
			this->Channel2Length->Location = System::Drawing::Point(950, 551);
			this->Channel2Length->Name = L"Channel2Length";
			this->Channel2Length->Size = System::Drawing::Size(82, 32);
			this->Channel2Length->TabIndex = 117;
			this->Channel2Length->TabStop = false;
			this->Channel2Length->Tag = L"";
			this->Channel2Length->Text = L"--:--";
			this->Channel2Length->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &BAPSPresenterMain::ChannelLength_MouseDown);
			// 
			// Channel1TimeLeft
			// 
			this->Channel1TimeLeft->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel1TimeLeft->HighlightColor = System::Drawing::Color::HotPink;
			this->Channel1TimeLeft->Highlighted = false;
			this->Channel1TimeLeft->InfoText = L"Remaining:";
			this->Channel1TimeLeft->Location = System::Drawing::Point(599, 551);
			this->Channel1TimeLeft->Name = L"Channel1TimeLeft";
			this->Channel1TimeLeft->Size = System::Drawing::Size(82, 32);
			this->Channel1TimeLeft->TabIndex = 113;
			this->Channel1TimeLeft->TabStop = false;
			this->Channel1TimeLeft->Text = L"0:00:00";
			// 
			// Channel1Length
			// 
			this->Channel1Length->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel1Length->HighlightColor = System::Drawing::Color::Red;
			this->Channel1Length->Highlighted = false;
			this->Channel1Length->InfoText = L"End At: 59:50";
			this->Channel1Length->Location = System::Drawing::Point(687, 551);
			this->Channel1Length->Name = L"Channel1Length";
			this->Channel1Length->Size = System::Drawing::Size(82, 32);
			this->Channel1Length->TabIndex = 114;
			this->Channel1Length->TabStop = false;
			this->Channel1Length->Tag = L"";
			this->Channel1Length->Text = L"--:--";
			this->Channel1Length->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &BAPSPresenterMain::ChannelLength_MouseDown);
			// 
			// trackList0
			// 
			this->trackList0->AllowDrop = true;
			this->trackList0->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->trackList0->Channel = 0;
			this->trackList0->ContextMenuStrip = this->trackListContextMenuStrip;
			this->trackList0->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->trackList0->LastIndexClicked = -1;
			this->trackList0->LoadedIndex = -1;
			this->trackList0->Location = System::Drawing::Point(252, 12);
			this->trackList0->Name = L"trackList0";
			this->trackList0->Size = System::Drawing::Size(256, 397);
			this->trackList0->TabIndex = 10;
			this->trackList0->Text = L"trackList0";
			this->trackList0->RequestChange += gcnew BAPSPresenter::RequestChangeEventHandler(this, &BAPSPresenterMain::TrackList_RequestChange);
			// 
			// Channel0Length
			// 
			this->Channel0Length->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel0Length->HighlightColor = System::Drawing::Color::Red;
			this->Channel0Length->Highlighted = false;
			this->Channel0Length->InfoText = L"End At: 59:50";
			this->Channel0Length->Location = System::Drawing::Point(426, 551);
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
			this->Channel2TimeLeft->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel2TimeLeft->HighlightColor = System::Drawing::Color::HotPink;
			this->Channel2TimeLeft->Highlighted = false;
			this->Channel2TimeLeft->InfoText = L"Remaining:";
			this->Channel2TimeLeft->Location = System::Drawing::Point(863, 551);
			this->Channel2TimeLeft->Name = L"Channel2TimeLeft";
			this->Channel2TimeLeft->Size = System::Drawing::Size(82, 32);
			this->Channel2TimeLeft->TabIndex = 116;
			this->Channel2TimeLeft->TabStop = false;
			this->Channel2TimeLeft->Text = L"0:00:00";
			// 
			// Channel0TimeLeft
			// 
			this->Channel0TimeLeft->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel0TimeLeft->HighlightColor = System::Drawing::Color::HotPink;
			this->Channel0TimeLeft->Highlighted = false;
			this->Channel0TimeLeft->InfoText = L"Remaining:";
			this->Channel0TimeLeft->Location = System::Drawing::Point(339, 551);
			this->Channel0TimeLeft->Name = L"Channel0TimeLeft";
			this->Channel0TimeLeft->Size = System::Drawing::Size(82, 32);
			this->Channel0TimeLeft->TabIndex = 110;
			this->Channel0TimeLeft->TabStop = false;
			this->Channel0TimeLeft->Text = L"0:00:00";
			// 
			// Channel1TimeGone
			// 
			this->Channel1TimeGone->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel1TimeGone->HighlightColor = System::Drawing::Color::Red;
			this->Channel1TimeGone->Highlighted = false;
			this->Channel1TimeGone->InfoText = L"Elapsed:";
			this->Channel1TimeGone->Location = System::Drawing::Point(514, 551);
			this->Channel1TimeGone->Name = L"Channel1TimeGone";
			this->Channel1TimeGone->Size = System::Drawing::Size(82, 32);
			this->Channel1TimeGone->TabIndex = 112;
			this->Channel1TimeGone->TabStop = false;
			this->Channel1TimeGone->Text = L"0:00:00";
			// 
			// Channel2TimeGone
			// 
			this->Channel2TimeGone->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel2TimeGone->HighlightColor = System::Drawing::Color::Red;
			this->Channel2TimeGone->Highlighted = false;
			this->Channel2TimeGone->InfoText = L"Elapsed:";
			this->Channel2TimeGone->Location = System::Drawing::Point(776, 551);
			this->Channel2TimeGone->Name = L"Channel2TimeGone";
			this->Channel2TimeGone->Size = System::Drawing::Size(82, 32);
			this->Channel2TimeGone->TabIndex = 115;
			this->Channel2TimeGone->TabStop = false;
			this->Channel2TimeGone->Text = L"0:00:00";
			// 
			// Channel0TimeGone
			// 
			this->Channel0TimeGone->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel0TimeGone->HighlightColor = System::Drawing::Color::Red;
			this->Channel0TimeGone->Highlighted = false;
			this->Channel0TimeGone->InfoText = L"Elapsed:";
			this->Channel0TimeGone->Location = System::Drawing::Point(252, 551);
			this->Channel0TimeGone->Name = L"Channel0TimeGone";
			this->Channel0TimeGone->Size = System::Drawing::Size(82, 32);
			this->Channel0TimeGone->TabIndex = 109;
			this->Channel0TimeGone->TabStop = false;
			this->Channel0TimeGone->Text = L"0:00:00";
			// 
			// trackList2
			// 
			this->trackList2->AllowDrop = true;
			this->trackList2->Channel = 2;
			this->trackList2->ContextMenuStrip = this->trackListContextMenuStrip;
			this->trackList2->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->trackList2->LastIndexClicked = -1;
			this->trackList2->LoadedIndex = -1;
			this->trackList2->Location = System::Drawing::Point(776, 12);
			this->trackList2->Name = L"trackList2";
			this->trackList2->Size = System::Drawing::Size(256, 397);
			this->trackList2->TabIndex = 14;
			this->trackList2->Text = L"trackList2";
			this->trackList2->RequestChange += gcnew BAPSPresenter::RequestChangeEventHandler(this, &BAPSPresenterMain::TrackList_RequestChange);
			// 
			// trackList1
			// 
			this->trackList1->AllowDrop = true;
			this->trackList1->Channel = 1;
			this->trackList1->ContextMenuStrip = this->trackListContextMenuStrip;
			this->trackList1->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->trackList1->LastIndexClicked = -1;
			this->trackList1->LoadedIndex = -1;
			this->trackList1->Location = System::Drawing::Point(514, 12);
			this->trackList1->Name = L"trackList1";
			this->trackList1->Size = System::Drawing::Size(256, 397);
			this->trackList1->TabIndex = 12;
			this->trackList1->Text = L"trackList1";
			this->trackList1->RequestChange += gcnew BAPSPresenter::RequestChangeEventHandler(this, &BAPSPresenterMain::TrackList_RequestChange);
			// 
			// trackTime1
			// 
			this->trackTime1->Channel = 1;
			this->trackTime1->CuePosition = 0;
			this->trackTime1->Duration = 0;
			this->trackTime1->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->trackTime1->IntroPosition = 0;
			this->trackTime1->Location = System::Drawing::Point(514, 474);
			this->trackTime1->Name = L"trackTime1";
			this->trackTime1->Position = 0;
			this->trackTime1->SilencePosition = 0;
			this->trackTime1->Size = System::Drawing::Size(256, 72);
			this->trackTime1->TabIndex = 26;
			this->trackTime1->Text = L"trackTime1";
			// 
			// trackTime2
			// 
			this->trackTime2->Channel = 2;
			this->trackTime2->CuePosition = 0;
			this->trackTime2->Duration = 0;
			this->trackTime2->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->trackTime2->IntroPosition = 0;
			this->trackTime2->Location = System::Drawing::Point(776, 474);
			this->trackTime2->Name = L"trackTime2";
			this->trackTime2->Position = 0;
			this->trackTime2->SilencePosition = 0;
			this->trackTime2->Size = System::Drawing::Size(256, 72);
			this->trackTime2->TabIndex = 27;
			this->trackTime2->Text = L"trackTime2";
			// 
			// trackTime0
			// 
			this->trackTime0->Channel = 0;
			this->trackTime0->CuePosition = 0;
			this->trackTime0->Duration = 0;
			this->trackTime0->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->trackTime0->IntroPosition = 0;
			this->trackTime0->Location = System::Drawing::Point(252, 474);
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
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(1044, 737);
			this->ControlBox = false;
			this->Controls->Add(this->Channel2LoadedText);
			this->Controls->Add(this->Channel0LoadedText);
			this->Controls->Add(this->Channel1LoadedText);
			this->Controls->Add(this->Channel2Stop);
			this->Controls->Add(this->Channel1Stop);
			this->Controls->Add(this->Channel0Stop);
			this->Controls->Add(this->Channel2Pause);
			this->Controls->Add(this->Channel1Pause);
			this->Controls->Add(this->Channel0Pause);
			this->Controls->Add(this->Channel2Play);
			this->Controls->Add(this->Channel1Play);
			this->Controls->Add(this->loadShowButton);
			this->Controls->Add(this->Channel0Play);
			this->Controls->Add(this->Directory0Refresh);
			this->Controls->Add(this->bapsButton1);
			this->Controls->Add(this->Directory2Refresh);
			this->Controls->Add(this->Directory1Refresh);
			this->Controls->Add(this->timeLine);
			this->Controls->Add(this->MainTextDisplay);
			this->Controls->Add(this->Directory2);
			this->Controls->Add(this->Channel2Length);
			this->Controls->Add(this->Channel1TimeLeft);
			this->Controls->Add(this->Directory1);
			this->Controls->Add(this->Channel1Length);
			this->Controls->Add(this->Directory0);
			this->Controls->Add(this->trackList0);
			this->Controls->Add(this->Channel0Length);
			this->Controls->Add(this->Channel2TimeLeft);
			this->Controls->Add(this->Channel0TimeLeft);
			this->Controls->Add(this->Channel1TimeGone);
			this->Controls->Add(this->Channel2TimeGone);
			this->Controls->Add(this->Channel0TimeGone);
			this->Controls->Add(this->trackList2);
			this->Controls->Add(this->trackList1);
			this->Controls->Add(this->trackTime1);
			this->Controls->Add(this->trackTime2);
			this->Controls->Add(this->trackTime0);
			this->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->KeyPreview = true;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"BAPSPresenterMain";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"BAPS Presenter";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &BAPSPresenterMain::BAPSPresenterMain_KeyDown);
			this->trackListContextMenuStrip->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void trackList0_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
			 
			 
		 }
};
}

