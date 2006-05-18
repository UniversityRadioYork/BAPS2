#pragma once

#include "BAPSScrollBar.h"
#include "decodeStructs.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::ComponentModel::Design;
using namespace System::Collections;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Windows::Forms::Design;
using namespace System::Security::Permissions;

namespace BAPSPresenter
{
	enum ChangeType
	{
		CHANGE_SELECTEDINDEX,
		CHANGE_MOVEINDEX,
		CHANGE_DELETEINDEX,
		CHANGE_ADD
	};
	ref struct TrackListDragDrop
	{
		int fromIndex;
		int fromChannel;
		bool moved;
		TrackListDragDrop(int _fromIndex, int _fromChannel)
			:fromIndex(_fromIndex), fromChannel(_fromChannel), moved(false)
		{}
	};

	ref struct EntryInfo
	{
		int type;
		System::String^ description;
		bool isSelectedTextItem;
		EntryInfo(int _type, System::String^ _description)
			:type(_type), description(_description), isSelectedTextItem(false)
		{}
		virtual System::String^ ToString() override
		{
			return description;
		}
	};

	ref class RequestChangeEventArgs : System::EventArgs
	{
	public:
		RequestChangeEventArgs(int _channel, ChangeType _ct, int _index)
			: channel(_channel), ct(_ct), index(_index)
		{}
		RequestChangeEventArgs(int _channel, ChangeType _ct, int _index, int _index2)
			: channel(_channel), ct(_ct), index(_index), index2(_index2)
		{}
		ChangeType ct;
		int index;
		int index2;
		int channel;
	};
	delegate void RequestChangeEventHandler(System::Object^, RequestChangeEventArgs^);

	public ref class TrackListDesigner: public System::Windows::Forms::Design::ControlDesigner
	{

	public:

		TrackListDesigner()
		{
		}

	protected:
		[ReflectionPermission(SecurityAction::Demand, Flags=ReflectionPermissionFlag::MemberAccess)]
		virtual void PreFilterProperties( System::Collections::IDictionary^ properties ) override
		{
			properties->Remove("LoadedIndex");
			properties->Remove("LoadedTextIndex");
			properties->Remove("OpLock");
			properties->Remove("LastIndexClicked");
		}
	};

	[DesignerAttribute(TrackListDesigner::typeid)]
	ref class TrackList : System::Windows::Forms::Control
    {
	public:
        TrackList()
        {
			this->SetStyle((System::Windows::Forms::ControlStyles)
						   (System::Windows::Forms::ControlStyles::UserPaint |
						   System::Windows::Forms::ControlStyles::Selectable |
						   System::Windows::Forms::ControlStyles::StandardClick |
						   System::Windows::Forms::ControlStyles::UserMouse),
						   true);

			opLock = gcnew System::Threading::Mutex();
			itemHeight         = -1;
			hoverIndex = -1;
			fromIndex = -1;
			selectedIndex = -1;
			pendingLoadRequest = false;
			lastIndexClicked = -1;
			selectedTextEntry = nullptr;
			addTo = false;
			scroll = gcnew BAPSScrollBar();
			scroll->Parent = this;
            scroll->Visible     = false;
			scroll->TopIndexChanged += gcnew System::EventHandler(this, &TrackList::ScrollValueChanged);
			this->Controls->Add(scroll);
			items = gcnew System::Collections::Generic::List<EntryInfo^>();
			this->AllowDrop = true;
            // Determine what the item height should be
            // by adding 30% padding after measuring
            // the letter A with the selected font.
			System::Drawing::Graphics^ g = this->CreateGraphics();
            ItemHeight = (int)(g->MeasureString("A", this->Font).Height * 1.3);
            delete g;
        }
		EntryInfo^ getTrack(int i)
		{
			if (i < items->Count)
			{
				return items[i];
			}
			else
			{
				return gcnew EntryInfo(BAPSNET_TEXTITEM, "NONE");
			}
		}
		void addTrack(int type, System::String^ descr)
		{
			opLock->WaitOne();
			items->Add(gcnew EntryInfo(type,descr));
			opLock->ReleaseMutex();
			showHideScrollBar();
			this->Invalidate();
		}
		void removeTrack(int _index)
		{
			opLock->WaitOne();
			if (_index == items->IndexOf(selectedTextEntry))
			{
				selectedTextEntry = nullptr;
			}
			int viewableItemCount = this->ClientSize.Height / ItemHeight;
			// fix the scroll bar 
			if (items->Count-_index < viewableItemCount && scroll->IndexAtTop != 0)
			{
				scroll->IndexAtTop -=1;
			}
			items->RemoveAt(_index);
			if (LoadedIndex == _index)
			{
				selectedIndex = -1;
			}
			else if (LoadedIndex > _index)
			{
				LoadedIndex -=1;
			}
			opLock->ReleaseMutex();
			showHideScrollBar();
			this->Invalidate();
		}
		void moveTrack(int oldIndex, int newIndex)
		{
			opLock->WaitOne();
			EntryInfo^ temp = items[oldIndex];
			items->RemoveAt(oldIndex);
			items->Insert(newIndex,temp);
			if (LoadedIndex == oldIndex)
			{
				LoadedIndex = newIndex;
			}
			else if (oldIndex < LoadedIndex &&
					 newIndex >= LoadedIndex)
			{
				selectedIndex -=1;
			}
			else if (oldIndex > LoadedIndex &&
					 newIndex <= LoadedIndex)
			{
				LoadedIndex +=1;
			}
			opLock->ReleaseMutex();
			this->Invalidate();
		}
		void clearTrackList()
		{
			opLock->WaitOne();
			items->Clear();
			selectedIndex = -1;
			pendingLoadRequest = false;
			selectedTextEntry = nullptr;
			opLock->ReleaseMutex();
			showHideScrollBar();
			this->Invalidate();
		}
		/** What index did the mouse last click over (for use in the context menu **/
		property int LastIndexClicked
		{
			int get()
			{
				return lastIndexClicked;
			}
			void set(int value)
			{
				lastIndexClicked=value;
			}
		}
		property int Channel
		{
			int get()
			{
				return channel;
			}
			void set(int value)
			{
				channel=value;
			}
		}
        // Get or set index of selected item.
        property int LoadedIndex
        {
            int get()
            {
                return selectedIndex;
            }

            void set(int value)
            {
				opLock->WaitOne();
				if (value < items->Count && value >= 0)
				{
					if (items[value]->type != BAPSNET_TEXTITEM)
					{
						selectedIndex = value;
						pendingLoadRequest = false;
						EnsureVisible(selectedIndex);
						this->Invalidate();
					}
				}
				opLock->ReleaseMutex();
			}
        }
        property int LoadedTextIndex
        {
            void set(int value)
            {
				opLock->WaitOne();
				if (selectedTextEntry!=nullptr)
				{
					selectedTextEntry->isSelectedTextItem = false;
				}
				if ((value < items->Count && value >= 0) &&
				    (items[value]->type == BAPSNET_TEXTITEM))
				{
					selectedTextEntry = items[value];
					items[value]->isSelectedTextItem = true;
				}
				this->Invalidate();
				opLock->ReleaseMutex();
			}
        }
		property System::Threading::Mutex^ OpLock
		{
			System::Threading::Mutex^ get()
			{
				return opLock;
			}
		}
		property int TrackCount
		{
			int get()
			{
				return items->Count;
			}
		}

        // If the requested index is before the first visible index then set the
        // first item to be the requested index. If it is after the last visible
        // index, then set the last visible index to be the requested index.
        void EnsureVisible(int index)
        {
            if(index < scroll->IndexAtTop)
            {
                scroll->IndexAtTop = index;
				this->Refresh();
            }
            else if(index >= scroll->IndexAtTop + DrawCount)
            {
                scroll->IndexAtTop = index - DrawCount+1;
                this->Refresh();
            }
        }

		event RequestChangeEventHandler^ RequestChange;
	protected:
		virtual void OnMouseDown(System::Windows::Forms::MouseEventArgs^ e) override;
		virtual void OnDragEnter(System::Windows::Forms::DragEventArgs ^  e) override;
		virtual void OnPaint(System::Windows::Forms::PaintEventArgs^ e) override;
		virtual void OnDragDrop(System::Windows::Forms::DragEventArgs ^  e) override;
		virtual void OnDragOver(System::Windows::Forms::DragEventArgs ^  e) override;
		virtual void OnDragLeave(System::EventArgs ^  e) override;
		virtual void OnKeyDown(System::Windows::Forms::KeyEventArgs^ e) override;
		virtual void OnMouseWheel(System::Windows::Forms::MouseEventArgs^ e) override;
		virtual void OnGotFocus(System::EventArgs^e)override
		{
			this->Invalidate();
		}
		virtual bool ProcessDialogKey(System::Windows::Forms::Keys keyData) override;
		bool HandleKey(System::Windows::Forms::Keys keyData);
		virtual void OnLostFocus(System::EventArgs^ e)override
		{
			this->Invalidate();
		}
		// Draws the external border around the control.
		virtual void OnPaintBackground(System::Windows::Forms::PaintEventArgs^ e) override
        {
			e->Graphics->DrawRectangle(System::Drawing::Pens::LightGray, 0, 0, ClientSize.Width-1, ClientSize.Height - 1);
        }

		void ScrollValueChanged(System::Object^ o, System::EventArgs^ e)
        {
            this->Refresh();
        }

        property int ItemHeight
        {
            int get()
            {
                return itemHeight;
            }

            void set(int value)
            {
                itemHeight = value;
            }
        }

        // Calculate how many items we can draw given the height of the control.
        property int DrawCount
        {
            int get()
            {
				return this->ClientRectangle.Height/itemHeight;
            }
        }

		virtual void OnResize(System::EventArgs^ e)override
        {

			scroll->Bounds = System::Drawing::Rectangle(this->ClientSize.Width - SCROLL_WIDTH,
                0,
                SCROLL_WIDTH,
                this->ClientSize.Height);
			showHideScrollBar();
        }
		private:
			int findAudioItem(int startIndex, bool goingUp);
			void showHideScrollBar()
			{
				int viewableItemCount = this->ClientSize.Height / ItemHeight;

				// Determine if scrollbars are needed
				if(items->Count > viewableItemCount)
				{
					scroll->Visible = true;
					scroll->ViewableItems = viewableItemCount;
					offScreen = gcnew System::Drawing::Bitmap(this->ClientSize.Width - SCROLL_WIDTH - 1, this->ClientSize.Height - 2);
				}
				else
				{
					scroll->Visible = false;
					scroll->IndexAtTop = 0;
					scroll->ViewableItems = items->Count;
					offScreen = gcnew System::Drawing::Bitmap(this->ClientSize.Width - 1, this->ClientSize.Height - 2);
				}
				scroll->TotalItems = items->Count;
			}
			int indexFromY(int y)
			{
				int index = scroll->IndexAtTop + (y / ItemHeight);
				if (index >= items->Count)
				{
					return -1;
				}
				else
				{
					return index;
				}
			}
			static const int SCROLL_WIDTH = 20;
			int itemHeight;
			int selectedIndex;
			bool pendingLoadRequest;
			int lastIndexClicked;
			EntryInfo^ selectedTextEntry;
			int channel;
			int hoverIndex;
			int fromIndex;
			bool addTo;
			System::Drawing::Bitmap^ offScreen;
			System::Collections::Generic::List<EntryInfo^>^ items;
			BAPSScrollBar^ scroll;
			System::Threading::Mutex^ opLock;
    };

};

