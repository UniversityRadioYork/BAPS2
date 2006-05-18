#pragma once
#include "BAPSButton.h"
#include "TrackList.h"
#include "Messages.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace BAPSPresenter {

	/// <summary>
	/// Summary for AudioWall
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	private ref class AudioWall : public System::Windows::Forms::Form
	{
	public:
		AudioWall(System::Collections::Queue^ _msgQueue, TrackList^ _tl)
			: msgQueue(_msgQueue),tl(_tl)
		{
			InitializeComponent();
			buttons = gcnew array<BAPSButton^>(20);
			BAPSPresenter::BAPSButton^ bapsButton;
			int i = 0;
			for (i = 0 ; i < 5 ; i++)
			{
				int j = 0;
				for (j = 0 ; j < 4 ; j++)
				{
					bapsButton = gcnew BAPSPresenter::BAPSButton();
					bapsButton->BackColor = System::Drawing::Color::Transparent;
					bapsButton->DialogResult = System::Windows::Forms::DialogResult::None;
					bapsButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
						static_cast<System::Byte>(0)));
					bapsButton->HighlightColor = System::Drawing::Color::Red;
					bapsButton->Highlighted = false;
					bapsButton->Location = System::Drawing::Point(((i+1)*12)+(i*190), ((j+1)*12)+(j*170));
					bapsButton->Name = System::String::Concat("bapsButton", ((5*j)+i).ToString());
					bapsButton->Size = System::Drawing::Size(190, 170);
					bapsButton->TabIndex = 0;
					bapsButton->Text = System::String::Concat("bapsButton", ((5*j)+i).ToString());
					bapsButton->Tag = 1;
					bapsButton->Enabled = false;
					bapsButton->TabIndex = (5*j)+i;
					bapsButton->Click += gcnew System::EventHandler(this, &AudioWall::audioWallClick);
					buttons[(5*j)+i] = bapsButton;
					this ->Controls->Add(bapsButton);
				}
			}
			refreshWall();
		}
		void setChannel(TrackList^ _tl)
		{
			tl = _tl;
		}
		void refreshWall()
		{
			this->Text = System::String::Concat("Audio Wall for Channel ", tl->Channel.ToString());
			int i = 0;
			int walli = 0;
			for (i=0;i<tl->TrackCount&&walli<20;i++)
			{
				EntryInfo^ ei = tl->getTrack(i);
				if (ei->type != BAPSNET_TEXTITEM)
				{
					buttons[walli]->Text = ei->description;
					buttons[walli]->Tag = i;
					buttons[walli]->Enabled = true;
					if (i == tl->LoadedIndex)
					{
						buttons[walli]->Highlighted = true;
					}
					else
					{
						buttons[walli]->Highlighted = false;
					}
					walli++;
				}
			}
			for (;walli < 20 ; walli++)
			{
				buttons[walli]->Text = "[NONE]";
				buttons[walli]->Tag = -1;
				buttons[walli]->Enabled = false;
				buttons[walli]->Highlighted = false;
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~AudioWall()
		{
			if (components)
			{
				delete components;
			}
		}
		virtual void OnResize(System::EventArgs^ e) override
		{
			__super::OnResize(e);
			if (buttons!=nullptr)
			{
			int xoffset = (this->ClientRectangle.Width-((5*202)+12))/2;
			int yoffset = (this->ClientRectangle.Height-((4*182)+12))/2;
			int i = 0;
			for (i = 0 ; i < 5 ; i++)
			{
				int j = 0;
				for (j = 0 ; j < 4 ; j++)
				{
					buttons[(5*j)+i]->Location = System::Drawing::Point(xoffset+((i+1)*12)+(i*190), yoffset+((j+1)*12)+(j*170));
				}
			}
			}
		}
	private:
		System::Collections::Queue^ msgQueue;
		TrackList^ tl;
		array<BAPSButton^>^ buttons;
		void audioWallClick(System::Object^ o, System::EventArgs^ e)
		{
			BAPSButton^ bb = static_cast<BAPSButton^>(o);
			int index = safe_cast<int>(bb->Tag);
			Command cmd = BAPSNET_PLAYBACK | BAPSNET_LOAD | tl->Channel;
			msgQueue->Enqueue(gcnew ActionMessageU32int(cmd, index));
			cmd = BAPSNET_PLAYBACK | BAPSNET_PLAY | tl->Channel;
			msgQueue->Enqueue(gcnew ActionMessage(cmd));
		}

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(AudioWall::typeid));
			this->SuspendLayout();
			// 
			// AudioWall
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(1026, 735);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"AudioWall";
			this->Text = L"Audio Wall";
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
