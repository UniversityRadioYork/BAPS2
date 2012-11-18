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
#include "TextDialog.h"
#include "TrackTime.h"
#include "TrackList.h"
#include "BAPSButton.h"
#include "BAPSLabel.h"

#define DISABLE_INDEX_CHANGE() 	channelList[channel]->Enabled=false;\
								channelList[channel]->remove_SelectedIndexChanged( gcnew System::EventHandler(this, &BAPSPresenterMain::LoadNewIndex_Event));

#define ENABLE_INDEX_CHANGE()	channelList[channel]->add_SelectedIndexChanged( gcnew System::EventHandler(this, &BAPSPresenterMain::LoadNewIndex_Event));\
								channelList[channel]->Enabled=true;

namespace BAPSPresenter {

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
		void showText(System::Object^ _channel);
		void showCuePosition(System::Object^ _channel, System::Object^ _cuePosition);

		/**
			PLAYLIST functions
		**/
		void addItem(System::Object^ _channel, System::Object^ _index, System::String^ entry);
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

		/** Show or hide the volume controls **/
		void showVolumeControls(bool shouldShow);
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
		/** Information about the status of each channel **/
		array<ChannelStatus^>^ channelStatus;

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

		/** The outgoing message queue (Should only have ActionMessage objects)**/
		System::Collections::Queue^ msgQueue;

		/** Sub-form handles **/
		RecordLibrarySearch^ recordLibrarySearch;
		ConfigDialog^ configDialog;
		LoadShowDialog^ loadShowDialog;
		SecurityDialog^ securityDialog;
		About^ about;
		FeedbackDialog^ feedbackDialog;
		array<TextDialog^>^ textDialog;
		
		/** Arrays with channel number indices for easy updating **/
		array<System::Windows::Forms::ListBox^>^	directoryList;
		array<BAPSLabel^>^		loadedText;
		array<System::Windows::Forms::Label^>^		trackLengthText;
		array<System::Windows::Forms::Label^>^		timeLeftText;
		array<System::Windows::Forms::Label^>^		timeGoneText;
		array<System::Windows::Forms::TrackBar^>^	volumeBar;
		array<BAPSButton^>^		channelPlay;
		array<BAPSButton^>^		channelPause;
		array<BAPSButton^>^		channelStop;
		array<BAPSPresenter::TrackTime^>^ trackTime;
private: BAPSPresenter::BAPSLabel^  Channel0TimeGone;
private: BAPSPresenter::BAPSLabel^  Channel0TimeLeft;
private: BAPSPresenter::BAPSLabel^  Channel0Length;

		 array<BAPSPresenter::TrackList^>^ trackList;

		/** ### END PRIVATE VARIABLES ### **/
		/** ### DESIGNER PRIVATE EVENT HANDLERS ### **/

		System::Void TrackBar_Scroll(System::Object ^  sender, System::EventArgs ^  e);
		System::Void VolumeBar_Scroll(System::Object ^  sender, System::EventArgs ^  e);
		System::Void BAPSPresenterMain_KeyDown(System::Object ^  sender, System::Windows::Forms::KeyEventArgs ^  e);
	
		System::Void RefreshDirectory_Click(System::Object ^  sender, System::EventArgs ^  e);

		System::Void helpButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void SearchRecordLib_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void loadShow_Click(System::Object ^  sender, System::EventArgs ^  e);

		System::Void feedbackButton_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void Directory_MouseDown(System::Object ^  sender, System::Windows::Forms::MouseEventArgs ^  e);

		System::Void ChannelOperation_Click(System::Object ^  sender, System::EventArgs ^  e);
		System::Void TrackList_RequestChange(System::Object^  o, BAPSPresenter::RequestChangeEventArgs^  e);
		/** ### END DESIGNER PRIVATE EVENT HANDLERS ### **/
		/** ### DESIGNER PRIVATE VARIABLES ### **/

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


	private: System::Windows::Forms::Label^  Channel2TrackLengthLabel;
	private: System::Windows::Forms::Label^  Channel2TimeLeftLabel;
	private: System::Windows::Forms::Label^  Channel2TimeGoneLabel;
	private: System::Windows::Forms::Label^  Channel1TrackLengthLabel;
	private: System::Windows::Forms::Label^  Channel1TimeLeftLabel;
	private: System::Windows::Forms::Label^  Channel1TimeGoneLabel;
	private: System::Windows::Forms::Label^  Channel0TrackLengthLabel;
	private: System::Windows::Forms::Label^  Channel0TimeLeftLabel;
	private: System::Windows::Forms::Label^  Channel0TimeGoneLabel;
	private: System::Windows::Forms::Label^  Channel2VolLabel;
	private: System::Windows::Forms::Label^  Channel1VolLabel;
	private: System::Windows::Forms::Label^  Channel0VolLabel;
	private: System::Windows::Forms::Label^  Channel2Label;
	private: System::Windows::Forms::Label^  Channel1Label;
	private: System::Windows::Forms::Label^  Channel0Label;

	private: System::Windows::Forms::ListBox^  Directory2;
	private: System::Windows::Forms::ListBox^  Directory1;
	private: System::Windows::Forms::ListBox^  Directory0;


	private: System::Windows::Forms::TrackBar^  Channel2VolumeBar;
	private: System::Windows::Forms::TrackBar^  Channel1VolumeBar;
	private: System::Windows::Forms::TrackBar^  Channel0VolumeBar;





	private: System::Windows::Forms::Label^  Channel1TimeLeft;
	private: System::Windows::Forms::Label^  Channel1Length;
	private: System::Windows::Forms::Label^  Channel1TimeGone;
	private: System::Windows::Forms::Label^  Channel2TimeGone;
	private: System::Windows::Forms::Label^  Channel2Length;
	private: System::Windows::Forms::Label^  Channel2TimeLeft;


	private: BAPSPresenter::TrackTime^  trackTime0;
	private: BAPSPresenter::TrackTime^  trackTime1;
	private: BAPSPresenter::TrackTime^  trackTime2;
	private: BAPSPresenter::TrackList^  trackList0;
	private: BAPSPresenter::TrackList^  trackList1;
	private: BAPSPresenter::TrackList^  trackList2;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(BAPSPresenterMain::typeid));
			this->Channel2TrackLengthLabel = (gcnew System::Windows::Forms::Label());
			this->Channel2TimeLeftLabel = (gcnew System::Windows::Forms::Label());
			this->Channel2TimeGoneLabel = (gcnew System::Windows::Forms::Label());
			this->Channel1TrackLengthLabel = (gcnew System::Windows::Forms::Label());
			this->Channel1TimeLeftLabel = (gcnew System::Windows::Forms::Label());
			this->Channel1TimeGoneLabel = (gcnew System::Windows::Forms::Label());
			this->Channel0TrackLengthLabel = (gcnew System::Windows::Forms::Label());
			this->Channel0TimeLeftLabel = (gcnew System::Windows::Forms::Label());
			this->Channel0TimeGoneLabel = (gcnew System::Windows::Forms::Label());
			this->Channel2VolLabel = (gcnew System::Windows::Forms::Label());
			this->Channel1VolLabel = (gcnew System::Windows::Forms::Label());
			this->Channel0VolLabel = (gcnew System::Windows::Forms::Label());
			this->Channel2Label = (gcnew System::Windows::Forms::Label());
			this->Channel1Label = (gcnew System::Windows::Forms::Label());
			this->Channel0Label = (gcnew System::Windows::Forms::Label());
			this->Directory2 = (gcnew System::Windows::Forms::ListBox());
			this->Directory1 = (gcnew System::Windows::Forms::ListBox());
			this->Directory0 = (gcnew System::Windows::Forms::ListBox());
			this->Channel2VolumeBar = (gcnew System::Windows::Forms::TrackBar());
			this->Channel1VolumeBar = (gcnew System::Windows::Forms::TrackBar());
			this->Channel0VolumeBar = (gcnew System::Windows::Forms::TrackBar());
			this->Channel1TimeLeft = (gcnew System::Windows::Forms::Label());
			this->Channel1Length = (gcnew System::Windows::Forms::Label());
			this->Channel1TimeGone = (gcnew System::Windows::Forms::Label());
			this->Channel2TimeGone = (gcnew System::Windows::Forms::Label());
			this->Channel2Length = (gcnew System::Windows::Forms::Label());
			this->Channel2TimeLeft = (gcnew System::Windows::Forms::Label());
			this->Channel0LoadedText = (gcnew BAPSPresenter::BAPSLabel());
			this->Directory2Refresh = (gcnew BAPSPresenter::BAPSButton());
			this->Directory1Refresh = (gcnew BAPSPresenter::BAPSButton());
			this->Directory0Refresh = (gcnew BAPSPresenter::BAPSButton());
			this->feedbackButton = (gcnew BAPSPresenter::BAPSButton());
			this->helpButton = (gcnew BAPSPresenter::BAPSButton());
			this->bapsButton1 = (gcnew BAPSPresenter::BAPSButton());
			this->loadShowButton = (gcnew BAPSPresenter::BAPSButton());
			this->Channel2Play = (gcnew BAPSPresenter::BAPSButton());
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
			this->Channel1LoadedText = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel2LoadedText = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel0TimeGone = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel0TimeLeft = (gcnew BAPSPresenter::BAPSLabel());
			this->Channel0Length = (gcnew BAPSPresenter::BAPSLabel());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Channel2VolumeBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Channel1VolumeBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Channel0VolumeBar))->BeginInit();
			this->SuspendLayout();
			// 
			// Channel2TrackLengthLabel
			// 
			this->Channel2TrackLengthLabel->BackColor = System::Drawing::Color::Transparent;
			this->Channel2TrackLengthLabel->Location = System::Drawing::Point(800, 592);
			this->Channel2TrackLengthLabel->Name = L"Channel2TrackLengthLabel";
			this->Channel2TrackLengthLabel->Size = System::Drawing::Size(80, 16);
			this->Channel2TrackLengthLabel->TabIndex = 226;
			this->Channel2TrackLengthLabel->Text = L"Total:";
			this->Channel2TrackLengthLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Channel2TimeLeftLabel
			// 
			this->Channel2TimeLeftLabel->BackColor = System::Drawing::Color::Transparent;
			this->Channel2TimeLeftLabel->Location = System::Drawing::Point(712, 592);
			this->Channel2TimeLeftLabel->Name = L"Channel2TimeLeftLabel";
			this->Channel2TimeLeftLabel->Size = System::Drawing::Size(80, 16);
			this->Channel2TimeLeftLabel->TabIndex = 225;
			this->Channel2TimeLeftLabel->Text = L"Remaining:";
			this->Channel2TimeLeftLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Channel2TimeGoneLabel
			// 
			this->Channel2TimeGoneLabel->BackColor = System::Drawing::Color::Transparent;
			this->Channel2TimeGoneLabel->Location = System::Drawing::Point(624, 592);
			this->Channel2TimeGoneLabel->Name = L"Channel2TimeGoneLabel";
			this->Channel2TimeGoneLabel->Size = System::Drawing::Size(80, 16);
			this->Channel2TimeGoneLabel->TabIndex = 224;
			this->Channel2TimeGoneLabel->Text = L"Elapsed:";
			this->Channel2TimeGoneLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Channel1TrackLengthLabel
			// 
			this->Channel1TrackLengthLabel->BackColor = System::Drawing::Color::Transparent;
			this->Channel1TrackLengthLabel->Location = System::Drawing::Point(504, 592);
			this->Channel1TrackLengthLabel->Name = L"Channel1TrackLengthLabel";
			this->Channel1TrackLengthLabel->Size = System::Drawing::Size(80, 16);
			this->Channel1TrackLengthLabel->TabIndex = 223;
			this->Channel1TrackLengthLabel->Text = L"Total:";
			this->Channel1TrackLengthLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Channel1TimeLeftLabel
			// 
			this->Channel1TimeLeftLabel->BackColor = System::Drawing::Color::Transparent;
			this->Channel1TimeLeftLabel->Location = System::Drawing::Point(416, 592);
			this->Channel1TimeLeftLabel->Name = L"Channel1TimeLeftLabel";
			this->Channel1TimeLeftLabel->Size = System::Drawing::Size(80, 16);
			this->Channel1TimeLeftLabel->TabIndex = 222;
			this->Channel1TimeLeftLabel->Text = L"Remaining:";
			this->Channel1TimeLeftLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Channel1TimeGoneLabel
			// 
			this->Channel1TimeGoneLabel->BackColor = System::Drawing::Color::Transparent;
			this->Channel1TimeGoneLabel->Location = System::Drawing::Point(328, 592);
			this->Channel1TimeGoneLabel->Name = L"Channel1TimeGoneLabel";
			this->Channel1TimeGoneLabel->Size = System::Drawing::Size(80, 16);
			this->Channel1TimeGoneLabel->TabIndex = 221;
			this->Channel1TimeGoneLabel->Text = L"Elapsed:";
			this->Channel1TimeGoneLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Channel0TrackLengthLabel
			// 
			this->Channel0TrackLengthLabel->BackColor = System::Drawing::Color::Transparent;
			this->Channel0TrackLengthLabel->Location = System::Drawing::Point(208, 592);
			this->Channel0TrackLengthLabel->Name = L"Channel0TrackLengthLabel";
			this->Channel0TrackLengthLabel->Size = System::Drawing::Size(80, 16);
			this->Channel0TrackLengthLabel->TabIndex = 220;
			this->Channel0TrackLengthLabel->Text = L"Total:";
			this->Channel0TrackLengthLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Channel0TimeLeftLabel
			// 
			this->Channel0TimeLeftLabel->BackColor = System::Drawing::Color::Transparent;
			this->Channel0TimeLeftLabel->Location = System::Drawing::Point(120, 592);
			this->Channel0TimeLeftLabel->Name = L"Channel0TimeLeftLabel";
			this->Channel0TimeLeftLabel->Size = System::Drawing::Size(80, 16);
			this->Channel0TimeLeftLabel->TabIndex = 219;
			this->Channel0TimeLeftLabel->Text = L"Remaining:";
			this->Channel0TimeLeftLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Channel0TimeGoneLabel
			// 
			this->Channel0TimeGoneLabel->BackColor = System::Drawing::Color::Transparent;
			this->Channel0TimeGoneLabel->Location = System::Drawing::Point(32, 592);
			this->Channel0TimeGoneLabel->Name = L"Channel0TimeGoneLabel";
			this->Channel0TimeGoneLabel->Size = System::Drawing::Size(80, 16);
			this->Channel0TimeGoneLabel->TabIndex = 218;
			this->Channel0TimeGoneLabel->Text = L"Elapsed:";
			this->Channel0TimeGoneLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Channel2VolLabel
			// 
			this->Channel2VolLabel->AutoSize = true;
			this->Channel2VolLabel->BackColor = System::Drawing::Color::Transparent;
			this->Channel2VolLabel->Location = System::Drawing::Point(856, 136);
			this->Channel2VolLabel->Name = L"Channel2VolLabel";
			this->Channel2VolLabel->Size = System::Drawing::Size(22, 13);
			this->Channel2VolLabel->TabIndex = 217;
			this->Channel2VolLabel->Text = L"Vol";
			// 
			// Channel1VolLabel
			// 
			this->Channel1VolLabel->AutoSize = true;
			this->Channel1VolLabel->BackColor = System::Drawing::Color::Transparent;
			this->Channel1VolLabel->Location = System::Drawing::Point(560, 136);
			this->Channel1VolLabel->Name = L"Channel1VolLabel";
			this->Channel1VolLabel->Size = System::Drawing::Size(22, 13);
			this->Channel1VolLabel->TabIndex = 216;
			this->Channel1VolLabel->Text = L"Vol";
			// 
			// Channel0VolLabel
			// 
			this->Channel0VolLabel->AutoSize = true;
			this->Channel0VolLabel->BackColor = System::Drawing::Color::Transparent;
			this->Channel0VolLabel->Location = System::Drawing::Point(264, 136);
			this->Channel0VolLabel->Name = L"Channel0VolLabel";
			this->Channel0VolLabel->Size = System::Drawing::Size(22, 13);
			this->Channel0VolLabel->TabIndex = 215;
			this->Channel0VolLabel->Text = L"Vol";
			// 
			// Channel2Label
			// 
			this->Channel2Label->BackColor = System::Drawing::Color::Transparent;
			this->Channel2Label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel2Label->Location = System::Drawing::Point(632, 120);
			this->Channel2Label->Name = L"Channel2Label";
			this->Channel2Label->Size = System::Drawing::Size(216, 26);
			this->Channel2Label->TabIndex = 214;
			this->Channel2Label->Text = L"Channel C";
			this->Channel2Label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Channel1Label
			// 
			this->Channel1Label->BackColor = System::Drawing::Color::Transparent;
			this->Channel1Label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel1Label->Location = System::Drawing::Point(336, 120);
			this->Channel1Label->Name = L"Channel1Label";
			this->Channel1Label->Size = System::Drawing::Size(216, 26);
			this->Channel1Label->TabIndex = 213;
			this->Channel1Label->Text = L"Channel B";
			this->Channel1Label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Channel0Label
			// 
			this->Channel0Label->BackColor = System::Drawing::Color::Transparent;
			this->Channel0Label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel0Label->Location = System::Drawing::Point(40, 120);
			this->Channel0Label->Name = L"Channel0Label";
			this->Channel0Label->Size = System::Drawing::Size(216, 26);
			this->Channel0Label->TabIndex = 212;
			this->Channel0Label->Text = L"Channel A";
			this->Channel0Label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Directory2
			// 
			this->Directory2->BackColor = System::Drawing::Color::Snow;
			this->Directory2->Location = System::Drawing::Point(568, 22);
			this->Directory2->Name = L"Directory2";
			this->Directory2->SelectionMode = System::Windows::Forms::SelectionMode::None;
			this->Directory2->Size = System::Drawing::Size(200, 82);
			this->Directory2->TabIndex = 204;
			this->Directory2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &BAPSPresenterMain::Directory_MouseDown);
			// 
			// Directory1
			// 
			this->Directory1->BackColor = System::Drawing::Color::Snow;
			this->Directory1->Location = System::Drawing::Point(360, 22);
			this->Directory1->Name = L"Directory1";
			this->Directory1->SelectionMode = System::Windows::Forms::SelectionMode::None;
			this->Directory1->Size = System::Drawing::Size(200, 82);
			this->Directory1->TabIndex = 203;
			this->Directory1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &BAPSPresenterMain::Directory_MouseDown);
			// 
			// Directory0
			// 
			this->Directory0->BackColor = System::Drawing::Color::Snow;
			this->Directory0->Location = System::Drawing::Point(152, 22);
			this->Directory0->Name = L"Directory0";
			this->Directory0->SelectionMode = System::Windows::Forms::SelectionMode::None;
			this->Directory0->Size = System::Drawing::Size(200, 82);
			this->Directory0->TabIndex = 202;
			this->Directory0->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &BAPSPresenterMain::Directory_MouseDown);
			// 
			// Channel2VolumeBar
			// 
			this->Channel2VolumeBar->LargeChange = 10;
			this->Channel2VolumeBar->Location = System::Drawing::Point(848, 152);
			this->Channel2VolumeBar->Maximum = 100;
			this->Channel2VolumeBar->Name = L"Channel2VolumeBar";
			this->Channel2VolumeBar->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->Channel2VolumeBar->Size = System::Drawing::Size(42, 280);
			this->Channel2VolumeBar->TabIndex = 211;
			this->Channel2VolumeBar->TickFrequency = 10;
			this->Channel2VolumeBar->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->Channel2VolumeBar->Value = 100;
			this->Channel2VolumeBar->Scroll += gcnew System::EventHandler(this, &BAPSPresenterMain::VolumeBar_Scroll);
			// 
			// Channel1VolumeBar
			// 
			this->Channel1VolumeBar->LargeChange = 10;
			this->Channel1VolumeBar->Location = System::Drawing::Point(552, 152);
			this->Channel1VolumeBar->Maximum = 100;
			this->Channel1VolumeBar->Name = L"Channel1VolumeBar";
			this->Channel1VolumeBar->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->Channel1VolumeBar->Size = System::Drawing::Size(42, 280);
			this->Channel1VolumeBar->TabIndex = 209;
			this->Channel1VolumeBar->TickFrequency = 10;
			this->Channel1VolumeBar->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->Channel1VolumeBar->Value = 100;
			this->Channel1VolumeBar->Scroll += gcnew System::EventHandler(this, &BAPSPresenterMain::VolumeBar_Scroll);
			// 
			// Channel0VolumeBar
			// 
			this->Channel0VolumeBar->LargeChange = 10;
			this->Channel0VolumeBar->Location = System::Drawing::Point(256, 152);
			this->Channel0VolumeBar->Maximum = 100;
			this->Channel0VolumeBar->Name = L"Channel0VolumeBar";
			this->Channel0VolumeBar->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->Channel0VolumeBar->Size = System::Drawing::Size(42, 280);
			this->Channel0VolumeBar->TabIndex = 207;
			this->Channel0VolumeBar->TickFrequency = 10;
			this->Channel0VolumeBar->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->Channel0VolumeBar->Value = 100;
			this->Channel0VolumeBar->Scroll += gcnew System::EventHandler(this, &BAPSPresenterMain::VolumeBar_Scroll);
			// 
			// Channel1TimeLeft
			// 
			this->Channel1TimeLeft->BackColor = System::Drawing::Color::Black;
			this->Channel1TimeLeft->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->Channel1TimeLeft->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel1TimeLeft->ForeColor = System::Drawing::Color::White;
			this->Channel1TimeLeft->Location = System::Drawing::Point(416, 560);
			this->Channel1TimeLeft->Name = L"Channel1TimeLeft";
			this->Channel1TimeLeft->Size = System::Drawing::Size(80, 32);
			this->Channel1TimeLeft->TabIndex = 238;
			this->Channel1TimeLeft->Text = L"00:00:00";
			this->Channel1TimeLeft->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Channel1Length
			// 
			this->Channel1Length->BackColor = System::Drawing::Color::Black;
			this->Channel1Length->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->Channel1Length->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel1Length->ForeColor = System::Drawing::Color::White;
			this->Channel1Length->Location = System::Drawing::Point(504, 560);
			this->Channel1Length->Name = L"Channel1Length";
			this->Channel1Length->Size = System::Drawing::Size(80, 32);
			this->Channel1Length->TabIndex = 235;
			this->Channel1Length->Text = L"00:00:00";
			this->Channel1Length->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Channel1TimeGone
			// 
			this->Channel1TimeGone->BackColor = System::Drawing::Color::Black;
			this->Channel1TimeGone->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->Channel1TimeGone->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel1TimeGone->ForeColor = System::Drawing::Color::White;
			this->Channel1TimeGone->Location = System::Drawing::Point(328, 560);
			this->Channel1TimeGone->Name = L"Channel1TimeGone";
			this->Channel1TimeGone->Size = System::Drawing::Size(80, 32);
			this->Channel1TimeGone->TabIndex = 232;
			this->Channel1TimeGone->Text = L"00:00:00";
			this->Channel1TimeGone->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Channel2TimeGone
			// 
			this->Channel2TimeGone->BackColor = System::Drawing::Color::Black;
			this->Channel2TimeGone->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->Channel2TimeGone->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel2TimeGone->ForeColor = System::Drawing::Color::White;
			this->Channel2TimeGone->Location = System::Drawing::Point(624, 560);
			this->Channel2TimeGone->Name = L"Channel2TimeGone";
			this->Channel2TimeGone->Size = System::Drawing::Size(80, 32);
			this->Channel2TimeGone->TabIndex = 231;
			this->Channel2TimeGone->Text = L"00:00:00";
			this->Channel2TimeGone->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Channel2Length
			// 
			this->Channel2Length->BackColor = System::Drawing::Color::Black;
			this->Channel2Length->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->Channel2Length->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel2Length->ForeColor = System::Drawing::Color::White;
			this->Channel2Length->Location = System::Drawing::Point(800, 560);
			this->Channel2Length->Name = L"Channel2Length";
			this->Channel2Length->Size = System::Drawing::Size(80, 32);
			this->Channel2Length->TabIndex = 234;
			this->Channel2Length->Text = L"00:00:00";
			this->Channel2Length->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Channel2TimeLeft
			// 
			this->Channel2TimeLeft->BackColor = System::Drawing::Color::Black;
			this->Channel2TimeLeft->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->Channel2TimeLeft->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel2TimeLeft->ForeColor = System::Drawing::Color::White;
			this->Channel2TimeLeft->Location = System::Drawing::Point(712, 560);
			this->Channel2TimeLeft->Name = L"Channel2TimeLeft";
			this->Channel2TimeLeft->Size = System::Drawing::Size(80, 32);
			this->Channel2TimeLeft->TabIndex = 233;
			this->Channel2TimeLeft->Text = L"00:00:00";
			this->Channel2TimeLeft->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Channel0LoadedText
			// 
			this->Channel0LoadedText->BackColor = System::Drawing::Color::Transparent;
			this->Channel0LoadedText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel0LoadedText->ForeColor = System::Drawing::Color::MidnightBlue;
			this->Channel0LoadedText->Location = System::Drawing::Point(32, 459);
			this->Channel0LoadedText->Name = L"Channel0LoadedText";
			this->Channel0LoadedText->Size = System::Drawing::Size(256, 20);
			this->Channel0LoadedText->TabIndex = 264;
			this->Channel0LoadedText->Text = L"--NONE LOADED--";
			// 
			// Directory2Refresh
			// 
			this->Directory2Refresh->BackColor = System::Drawing::Color::Transparent;
			this->Directory2Refresh->HighlightColor = System::Drawing::Color::Red;
			this->Directory2Refresh->Highlighted = false;
			this->Directory2Refresh->Location = System::Drawing::Point(568, 7);
			this->Directory2Refresh->Name = L"Directory2Refresh";
			this->Directory2Refresh->Size = System::Drawing::Size(200, 8);
			this->Directory2Refresh->TabIndex = 263;
			// 
			// Directory1Refresh
			// 
			this->Directory1Refresh->BackColor = System::Drawing::Color::Transparent;
			this->Directory1Refresh->HighlightColor = System::Drawing::Color::Red;
			this->Directory1Refresh->Highlighted = false;
			this->Directory1Refresh->Location = System::Drawing::Point(360, 7);
			this->Directory1Refresh->Name = L"Directory1Refresh";
			this->Directory1Refresh->Size = System::Drawing::Size(200, 8);
			this->Directory1Refresh->TabIndex = 263;
			// 
			// Directory0Refresh
			// 
			this->Directory0Refresh->BackColor = System::Drawing::Color::Transparent;
			this->Directory0Refresh->HighlightColor = System::Drawing::Color::Red;
			this->Directory0Refresh->Highlighted = false;
			this->Directory0Refresh->Location = System::Drawing::Point(152, 7);
			this->Directory0Refresh->Name = L"Directory0Refresh";
			this->Directory0Refresh->Size = System::Drawing::Size(200, 8);
			this->Directory0Refresh->TabIndex = 263;
			// 
			// feedbackButton
			// 
			this->feedbackButton->BackColor = System::Drawing::Color::Transparent;
			this->feedbackButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->feedbackButton->HighlightColor = System::Drawing::Color::Red;
			this->feedbackButton->Highlighted = false;
			this->feedbackButton->Location = System::Drawing::Point(848, 8);
			this->feedbackButton->Name = L"feedbackButton";
			this->feedbackButton->Size = System::Drawing::Size(57, 18);
			this->feedbackButton->TabIndex = 262;
			this->feedbackButton->Text = L"Support";
			this->feedbackButton->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::feedbackButton_Click);
			// 
			// helpButton
			// 
			this->helpButton->BackColor = System::Drawing::Color::Transparent;
			this->helpButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->helpButton->HighlightColor = System::Drawing::Color::Red;
			this->helpButton->Highlighted = false;
			this->helpButton->Location = System::Drawing::Point(796, 8);
			this->helpButton->Name = L"helpButton";
			this->helpButton->Size = System::Drawing::Size(42, 18);
			this->helpButton->TabIndex = 261;
			this->helpButton->Text = L"Help";
			this->helpButton->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::helpButton_Click);
			// 
			// bapsButton1
			// 
			this->bapsButton1->BackColor = System::Drawing::Color::Transparent;
			this->bapsButton1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->bapsButton1->HighlightColor = System::Drawing::Color::Red;
			this->bapsButton1->Highlighted = false;
			this->bapsButton1->Location = System::Drawing::Point(796, 32);
			this->bapsButton1->Name = L"bapsButton1";
			this->bapsButton1->Size = System::Drawing::Size(109, 70);
			this->bapsButton1->TabIndex = 260;
			this->bapsButton1->Text = L"Search Record Library";
			this->bapsButton1->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::SearchRecordLib_Click);
			// 
			// loadShowButton
			// 
			this->loadShowButton->BackColor = System::Drawing::Color::Transparent;
			this->loadShowButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->loadShowButton->HighlightColor = System::Drawing::Color::Red;
			this->loadShowButton->Highlighted = false;
			this->loadShowButton->Location = System::Drawing::Point(12, 32);
			this->loadShowButton->Name = L"loadShowButton";
			this->loadShowButton->Size = System::Drawing::Size(109, 70);
			this->loadShowButton->TabIndex = 259;
			this->loadShowButton->Text = L"Load Show";
			this->loadShowButton->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::loadShow_Click);
			// 
			// Channel2Play
			// 
			this->Channel2Play->BackColor = System::Drawing::Color::Transparent;
			this->Channel2Play->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel2Play->HighlightColor = System::Drawing::Color::DarkGreen;
			this->Channel2Play->Highlighted = false;
			this->Channel2Play->Location = System::Drawing::Point(624, 435);
			this->Channel2Play->Name = L"Channel2Play";
			this->Channel2Play->Size = System::Drawing::Size(72, 19);
			this->Channel2Play->TabIndex = 258;
			this->Channel2Play->Text = L"F9 - Play";
			this->Channel2Play->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel1Play
			// 
			this->Channel1Play->BackColor = System::Drawing::Color::Transparent;
			this->Channel1Play->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel1Play->HighlightColor = System::Drawing::Color::DarkGreen;
			this->Channel1Play->Highlighted = false;
			this->Channel1Play->Location = System::Drawing::Point(328, 435);
			this->Channel1Play->Name = L"Channel1Play";
			this->Channel1Play->Size = System::Drawing::Size(72, 19);
			this->Channel1Play->TabIndex = 258;
			this->Channel1Play->Text = L"F4 - Play";
			this->Channel1Play->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel2Stop
			// 
			this->Channel2Stop->BackColor = System::Drawing::Color::Transparent;
			this->Channel2Stop->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel2Stop->HighlightColor = System::Drawing::Color::Firebrick;
			this->Channel2Stop->Highlighted = false;
			this->Channel2Stop->Location = System::Drawing::Point(808, 435);
			this->Channel2Stop->Name = L"Channel2Stop";
			this->Channel2Stop->Size = System::Drawing::Size(72, 19);
			this->Channel2Stop->TabIndex = 258;
			this->Channel2Stop->Text = L"F11 - Stop";
			this->Channel2Stop->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel1Stop
			// 
			this->Channel1Stop->BackColor = System::Drawing::Color::Transparent;
			this->Channel1Stop->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel1Stop->HighlightColor = System::Drawing::Color::Firebrick;
			this->Channel1Stop->Highlighted = false;
			this->Channel1Stop->Location = System::Drawing::Point(512, 435);
			this->Channel1Stop->Name = L"Channel1Stop";
			this->Channel1Stop->Size = System::Drawing::Size(72, 19);
			this->Channel1Stop->TabIndex = 258;
			this->Channel1Stop->Text = L"F7 - Stop";
			this->Channel1Stop->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel2Pause
			// 
			this->Channel2Pause->BackColor = System::Drawing::Color::Transparent;
			this->Channel2Pause->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel2Pause->HighlightColor = System::Drawing::Color::DarkOrange;
			this->Channel2Pause->Highlighted = false;
			this->Channel2Pause->Location = System::Drawing::Point(716, 435);
			this->Channel2Pause->Name = L"Channel2Pause";
			this->Channel2Pause->Size = System::Drawing::Size(72, 19);
			this->Channel2Pause->TabIndex = 258;
			this->Channel2Pause->Text = L"F10 - Pause";
			this->Channel2Pause->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel1Pause
			// 
			this->Channel1Pause->BackColor = System::Drawing::Color::Transparent;
			this->Channel1Pause->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel1Pause->HighlightColor = System::Drawing::Color::DarkOrange;
			this->Channel1Pause->Highlighted = false;
			this->Channel1Pause->Location = System::Drawing::Point(420, 435);
			this->Channel1Pause->Name = L"Channel1Pause";
			this->Channel1Pause->Size = System::Drawing::Size(72, 19);
			this->Channel1Pause->TabIndex = 258;
			this->Channel1Pause->Text = L"F6 - Pause";
			this->Channel1Pause->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel0Pause
			// 
			this->Channel0Pause->BackColor = System::Drawing::Color::Transparent;
			this->Channel0Pause->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel0Pause->HighlightColor = System::Drawing::Color::DarkOrange;
			this->Channel0Pause->Highlighted = false;
			this->Channel0Pause->Location = System::Drawing::Point(124, 435);
			this->Channel0Pause->Name = L"Channel0Pause";
			this->Channel0Pause->Size = System::Drawing::Size(72, 19);
			this->Channel0Pause->TabIndex = 258;
			this->Channel0Pause->Text = L"F2 - Pause";
			this->Channel0Pause->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel0Stop
			// 
			this->Channel0Stop->BackColor = System::Drawing::Color::Transparent;
			this->Channel0Stop->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel0Stop->HighlightColor = System::Drawing::Color::Firebrick;
			this->Channel0Stop->Highlighted = false;
			this->Channel0Stop->Location = System::Drawing::Point(216, 435);
			this->Channel0Stop->Name = L"Channel0Stop";
			this->Channel0Stop->Size = System::Drawing::Size(72, 19);
			this->Channel0Stop->TabIndex = 258;
			this->Channel0Stop->Text = L"F3 - Stop";
			this->Channel0Stop->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// Channel0Play
			// 
			this->Channel0Play->BackColor = System::Drawing::Color::Transparent;
			this->Channel0Play->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel0Play->HighlightColor = System::Drawing::Color::DarkGreen;
			this->Channel0Play->Highlighted = false;
			this->Channel0Play->Location = System::Drawing::Point(32, 435);
			this->Channel0Play->Name = L"Channel0Play";
			this->Channel0Play->Size = System::Drawing::Size(72, 19);
			this->Channel0Play->TabIndex = 258;
			this->Channel0Play->Text = L"F1 - Play";
			this->Channel0Play->Click += gcnew System::EventHandler(this, &BAPSPresenterMain::ChannelOperation_Click);
			// 
			// trackList2
			// 
			this->trackList2->AllowDrop = true;
			this->trackList2->Channel = 2;
			this->trackList2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->trackList2->Location = System::Drawing::Point(624, 152);
			this->trackList2->Name = L"trackList2";
			this->trackList2->Size = System::Drawing::Size(256, 274);
			this->trackList2->TabIndex = 257;
			this->trackList2->Text = L"trackList2";
			this->trackList2->RequestChange += gcnew BAPSPresenter::RequestChangeEventHandler(this, &BAPSPresenterMain::TrackList_RequestChange);
			// 
			// trackList1
			// 
			this->trackList1->AllowDrop = true;
			this->trackList1->Channel = 1;
			this->trackList1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->trackList1->Location = System::Drawing::Point(328, 152);
			this->trackList1->Name = L"trackList1";
			this->trackList1->Size = System::Drawing::Size(256, 274);
			this->trackList1->TabIndex = 257;
			this->trackList1->Text = L"trackList1";
			this->trackList1->RequestChange += gcnew BAPSPresenter::RequestChangeEventHandler(this, &BAPSPresenterMain::TrackList_RequestChange);
			// 
			// trackList0
			// 
			this->trackList0->AllowDrop = true;
			this->trackList0->Channel = 0;
			this->trackList0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->trackList0->Location = System::Drawing::Point(32, 152);
			this->trackList0->Name = L"trackList0";
			this->trackList0->Size = System::Drawing::Size(256, 274);
			this->trackList0->TabIndex = 257;
			this->trackList0->Text = L"trackList0";
			this->trackList0->RequestChange += gcnew BAPSPresenter::RequestChangeEventHandler(this, &BAPSPresenterMain::TrackList_RequestChange);
			// 
			// trackTime2
			// 
			this->trackTime2->BackColor = System::Drawing::Color::Transparent;
			this->trackTime2->BackColor1 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(250)), 
				static_cast<System::Int32>(static_cast<System::Byte>(250)));
			this->trackTime2->BackColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(250)), static_cast<System::Int32>(static_cast<System::Byte>(235)), 
				static_cast<System::Int32>(static_cast<System::Byte>(215)));
			this->trackTime2->Channel = 2;
			this->trackTime2->CuePosition = 0;
			this->trackTime2->Duration = 0;
			this->trackTime2->IntroPosition = 0;
			this->trackTime2->Location = System::Drawing::Point(624, 484);
			this->trackTime2->Name = L"trackTime2";
			this->trackTime2->Position = 0;
			this->trackTime2->SilencePosition = 0;
			this->trackTime2->Size = System::Drawing::Size(256, 72);
			this->trackTime2->TabIndex = 256;
			this->trackTime2->Text = L"trackTime2";
			// 
			// trackTime1
			// 
			this->trackTime1->BackColor = System::Drawing::Color::Transparent;
			this->trackTime1->BackColor1 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(250)), 
				static_cast<System::Int32>(static_cast<System::Byte>(250)));
			this->trackTime1->BackColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(250)), static_cast<System::Int32>(static_cast<System::Byte>(235)), 
				static_cast<System::Int32>(static_cast<System::Byte>(215)));
			this->trackTime1->Channel = 1;
			this->trackTime1->CuePosition = 0;
			this->trackTime1->Duration = 0;
			this->trackTime1->IntroPosition = 0;
			this->trackTime1->Location = System::Drawing::Point(328, 484);
			this->trackTime1->Name = L"trackTime1";
			this->trackTime1->Position = 0;
			this->trackTime1->SilencePosition = 0;
			this->trackTime1->Size = System::Drawing::Size(256, 72);
			this->trackTime1->TabIndex = 256;
			this->trackTime1->Text = L"trackTime1";
			// 
			// trackTime0
			// 
			this->trackTime0->BackColor = System::Drawing::Color::Transparent;
			this->trackTime0->BackColor1 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(250)), 
				static_cast<System::Int32>(static_cast<System::Byte>(250)));
			this->trackTime0->BackColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(250)), static_cast<System::Int32>(static_cast<System::Byte>(235)), 
				static_cast<System::Int32>(static_cast<System::Byte>(215)));
			this->trackTime0->Channel = 0;
			this->trackTime0->CuePosition = 0;
			this->trackTime0->Duration = 0;
			this->trackTime0->IntroPosition = 0;
			this->trackTime0->Location = System::Drawing::Point(32, 484);
			this->trackTime0->Name = L"trackTime0";
			this->trackTime0->Position = 0;
			this->trackTime0->SilencePosition = 0;
			this->trackTime0->Size = System::Drawing::Size(256, 72);
			this->trackTime0->TabIndex = 256;
			this->trackTime0->Text = L"trackTime0";
			// 
			// Channel1LoadedText
			// 
			this->Channel1LoadedText->BackColor = System::Drawing::Color::Transparent;
			this->Channel1LoadedText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel1LoadedText->ForeColor = System::Drawing::Color::MidnightBlue;
			this->Channel1LoadedText->Location = System::Drawing::Point(328, 458);
			this->Channel1LoadedText->Name = L"Channel1LoadedText";
			this->Channel1LoadedText->Size = System::Drawing::Size(256, 20);
			this->Channel1LoadedText->TabIndex = 264;
			this->Channel1LoadedText->Text = L"--NONE LOADED--";
			// 
			// Channel2LoadedText
			// 
			this->Channel2LoadedText->BackColor = System::Drawing::Color::Transparent;
			this->Channel2LoadedText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel2LoadedText->ForeColor = System::Drawing::Color::MidnightBlue;
			this->Channel2LoadedText->Location = System::Drawing::Point(624, 458);
			this->Channel2LoadedText->Name = L"Channel2LoadedText";
			this->Channel2LoadedText->Size = System::Drawing::Size(256, 20);
			this->Channel2LoadedText->TabIndex = 264;
			this->Channel2LoadedText->Text = L"--NONE LOADED--";
			// 
			// Channel0TimeGone
			// 
			this->Channel0TimeGone->BackColor = System::Drawing::Color::Transparent;
			this->Channel0TimeGone->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel0TimeGone->Location = System::Drawing::Point(32, 560);
			this->Channel0TimeGone->Name = L"Channel0TimeGone";
			this->Channel0TimeGone->Size = System::Drawing::Size(72, 32);
			this->Channel0TimeGone->TabIndex = 265;
			this->Channel0TimeGone->Text = L"00:00:0";
			// 
			// Channel0TimeLeft
			// 
			this->Channel0TimeLeft->BackColor = System::Drawing::Color::Transparent;
			this->Channel0TimeLeft->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel0TimeLeft->Location = System::Drawing::Point(124, 560);
			this->Channel0TimeLeft->Name = L"Channel0TimeLeft";
			this->Channel0TimeLeft->Size = System::Drawing::Size(72, 32);
			this->Channel0TimeLeft->TabIndex = 265;
			this->Channel0TimeLeft->Text = L"00:00:0";
			// 
			// Channel0Length
			// 
			this->Channel0Length->BackColor = System::Drawing::Color::Transparent;
			this->Channel0Length->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Channel0Length->Location = System::Drawing::Point(216, 560);
			this->Channel0Length->Name = L"Channel0Length";
			this->Channel0Length->Size = System::Drawing::Size(72, 32);
			this->Channel0Length->TabIndex = 265;
			this->Channel0Length->Text = L"00:00:0";
			// 
			// BAPSPresenterMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(202)), static_cast<System::Int32>(static_cast<System::Byte>(202)), 
				static_cast<System::Int32>(static_cast<System::Byte>(202)));
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(917, 619);
			this->ControlBox = false;
			this->Controls->Add(this->Channel0Length);
			this->Controls->Add(this->Channel0TimeLeft);
			this->Controls->Add(this->Channel0TimeGone);
			this->Controls->Add(this->Channel2LoadedText);
			this->Controls->Add(this->Channel1LoadedText);
			this->Controls->Add(this->Channel0LoadedText);
			this->Controls->Add(this->Directory2Refresh);
			this->Controls->Add(this->Directory1Refresh);
			this->Controls->Add(this->Directory0Refresh);
			this->Controls->Add(this->feedbackButton);
			this->Controls->Add(this->helpButton);
			this->Controls->Add(this->bapsButton1);
			this->Controls->Add(this->loadShowButton);
			this->Controls->Add(this->Channel2Play);
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
			this->Controls->Add(this->Channel2TrackLengthLabel);
			this->Controls->Add(this->Channel2TimeLeftLabel);
			this->Controls->Add(this->Channel2TimeGoneLabel);
			this->Controls->Add(this->Channel1TrackLengthLabel);
			this->Controls->Add(this->Channel1TimeLeftLabel);
			this->Controls->Add(this->Channel1TimeGoneLabel);
			this->Controls->Add(this->Channel0TrackLengthLabel);
			this->Controls->Add(this->Channel0TimeLeftLabel);
			this->Controls->Add(this->Channel0TimeGoneLabel);
			this->Controls->Add(this->Channel2VolLabel);
			this->Controls->Add(this->Channel1VolLabel);
			this->Controls->Add(this->Channel0VolLabel);
			this->Controls->Add(this->Channel2Label);
			this->Controls->Add(this->Channel1Label);
			this->Controls->Add(this->Channel0Label);
			this->Controls->Add(this->Directory2);
			this->Controls->Add(this->Directory1);
			this->Controls->Add(this->Directory0);
			this->Controls->Add(this->Channel2VolumeBar);
			this->Controls->Add(this->Channel1VolumeBar);
			this->Controls->Add(this->Channel0VolumeBar);
			this->Controls->Add(this->Channel1TimeLeft);
			this->Controls->Add(this->Channel1Length);
			this->Controls->Add(this->Channel1TimeGone);
			this->Controls->Add(this->Channel2TimeGone);
			this->Controls->Add(this->Channel2Length);
			this->Controls->Add(this->Channel2TimeLeft);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->KeyPreview = true;
			this->Name = L"BAPSPresenterMain";
			this->Text = L"BAPS Presenter";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &BAPSPresenterMain::BAPSPresenterMain_KeyDown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Channel2VolumeBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Channel1VolumeBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Channel0VolumeBar))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

};
}

