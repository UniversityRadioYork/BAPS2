#pragma once

#include "BAPSScrollBar.h"

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
	public ref class BAPSListBoxDesigner: public System::Windows::Forms::Design::ControlDesigner
	{

	public:

		BAPSListBoxDesigner()
		{
		}

	protected:
		[ReflectionPermission(SecurityAction::Demand, Flags=ReflectionPermissionFlag::MemberAccess)]
		virtual void PreFilterProperties( System::Collections::IDictionary^ properties ) override
		{
			properties->Remove("SelectedIndex");
		}
	};

	[DesignerAttribute(BAPSListBoxDesigner::typeid)]
	ref class BAPSListBox : System::Windows::Forms::Control
    {
	public:
        BAPSListBox()
        {
			this->SetStyle((System::Windows::Forms::ControlStyles)
						   (System::Windows::Forms::ControlStyles::UserPaint |
						   System::Windows::Forms::ControlStyles::Selectable |
						   System::Windows::Forms::ControlStyles::StandardClick |
						   System::Windows::Forms::ControlStyles::SupportsTransparentBackColor |
						   System::Windows::Forms::ControlStyles::UserMouse),
						   true);
			itemHeight         = -1;
			selectedIndex = -1;
			selectedIndexEnabled = true;
			scroll = gcnew BAPSScrollBar();
			scroll->Parent = this;
            scroll->Visible     = false;
			scroll->TopIndexChanged += gcnew System::EventHandler(this, &BAPSListBox::ScrollValueChanged);
			this->Controls->Add(scroll);
			items = gcnew System::Collections::ArrayList();
            // Determine what the item height should be
            // by adding 30% padding after measuring
            // the letter A with the selected font.
			System::Drawing::Graphics^ g = this->CreateGraphics();
            ItemHeight = (int)(g->MeasureString("A", this->Font).Height * 1.3);
            delete g;
        }
		void addItem(System::Object^ descr)
		{
			items->Add(descr);
			showHideScrollBar();
			this->Invalidate();
		}
		System::Object^ getItem(int index)
		{
			return items[index];
		}
		void removeItem(int _index)
		{
			int viewableItemCount = this->ClientSize.Height / ItemHeight;
			// fix the scroll bar 
			if (items->Count-_index < viewableItemCount && scroll->IndexAtTop != 0)
			{
				scroll->IndexAtTop -=1;
			}
			items->RemoveAt(_index);
			if (SelectedIndex == _index)
			{
				selectedIndex = -1;
			}
			else if (SelectedIndex > _index)
			{
				SelectedIndex -=1;
			}
			showHideScrollBar();
			this->Invalidate();
		}
		int itemCount()
		{
			return items->Count;
		}
		void clearList()
		{
			items->Clear();
			selectedIndex = -1;
			showHideScrollBar();
			this->Invalidate();
		}

        // Get or set index of selected item.
        property int SelectedIndex
        {
            int get()
            {
                return selectedIndex;
            }

            void set(int value)
            {
				if (value > -1)
				{
					selectedIndex = value;
					EnsureVisible(selectedIndex);
				}
				SelectedIndexChanged(this, System::EventArgs::Empty);
			}
        }
		property bool SelectedIndexEnabled
		{
			bool get()
			{
				return selectedIndexEnabled;
			}
			void set(bool value)
			{
				selectedIndexEnabled = value;
				this->Invalidate();
			}
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

        // If the requested index is before the first visible index then set the
        // first item to be the requested index. If it is after the last visible
        // index, then set the last visible index to be the requested index.
        void EnsureVisible(int index)
        {
            if(index < scroll->IndexAtTop)
            {
                scroll->IndexAtTop = index;
            }
            else if(index >= scroll->IndexAtTop + DrawCount)
            {
                scroll->IndexAtTop = index - DrawCount+1;
            }
			this->Refresh();
        }
		event System::EventHandler^ SelectedIndexChanged;
	protected:
		virtual void OnPaint(System::Windows::Forms::PaintEventArgs^ e) override;
		virtual void OnKeyDown(System::Windows::Forms::KeyEventArgs^ e) override;
		virtual void OnMouseDown(System::Windows::Forms::MouseEventArgs^ e) override;
		virtual void OnMouseWheel(System::Windows::Forms::MouseEventArgs^ e) override;
		virtual void OnGotFocus(System::EventArgs^e)override
		{
			__super::OnGotFocus(e);
			this->Invalidate();
		}
		virtual bool ProcessDialogKey(System::Windows::Forms::Keys keyData) override;
		bool HandleKey(System::Windows::Forms::Keys keyData);
		virtual void OnLostFocus(System::EventArgs^ e)override
		{
			__super::OnLostFocus(e);
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
			__super::OnResize(e);
			scroll->Bounds = System::Drawing::Rectangle(this->ClientSize.Width - SCROLL_WIDTH,
                0,
                SCROLL_WIDTH,
                this->ClientSize.Height);
			showHideScrollBar();
        }
		private:
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

			static const int SCROLL_WIDTH = 20;
			int itemHeight;
			int selectedIndex;
			bool selectedIndexEnabled;
			System::Drawing::Bitmap^ offScreen;
			System::Collections::ArrayList^ items;
			BAPSScrollBar^ scroll;

    };

};

