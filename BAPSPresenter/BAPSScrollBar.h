#pragma once

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
	ref class BAPSScrollBar : System::Windows::Forms::Control
    {
	public:
        BAPSScrollBar()
        {
			this->SetStyle((System::Windows::Forms::ControlStyles)
						   (System::Windows::Forms::ControlStyles::UserPaint |
						   System::Windows::Forms::ControlStyles::AllPaintingInWmPaint |
						  // System::Windows::Forms::ControlStyles::DoubleBuffer |
						   System::Windows::Forms::ControlStyles::Selectable |
						   System::Windows::Forms::ControlStyles::StandardClick |
						   System::Windows::Forms::ControlStyles::SupportsTransparentBackColor |
						   System::Windows::Forms::ControlStyles::UserMouse),
						   true);
			viewableItems = 0;
			totalItems = 0;
			indexAtTop = 0;
			scrolling = false;
			scrollStart = 0;
			scrollButtonHeight = 1;
			this->TabStop = false;
			backBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(System::Drawing::Rectangle(0,0,10,10), System::Drawing::Color::Snow, System::Drawing::Color::AntiqueWhite,System::Drawing::Drawing2D::LinearGradientMode::Vertical );
			slideBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(System::Drawing::Rectangle(0,0,10,10), System::Drawing::Color::Snow, System::Drawing::Color::RoyalBlue,System::Drawing::Drawing2D::LinearGradientMode::Horizontal );
		}
		property int TotalItems
		{
			int get(){return totalItems;}
			void set(int value)
			{
				totalItems=value;
				resizeSlider();
			}
		}
		property int IndexAtTop
		{
			int get(){return indexAtTop;}
			void set(int value)
			{
				indexAtTop=value;
				resizeSlider();
			}
		}

		property int ViewableItems
		{
			int get(){return viewableItems;}
			void set(int value)
			{
				viewableItems=value;
				resizeSlider();
			}
		}
		event System::EventHandler^ TopIndexChanged;
	protected:
		virtual void OnPaint(System::Windows::Forms::PaintEventArgs^ e) override;
		virtual void OnResize(System::EventArgs^ e) override;
		virtual void OnPaintBackground(System::Windows::Forms::PaintEventArgs^ e) override;
		virtual void OnMouseDown(System::Windows::Forms::MouseEventArgs^ e) override;
		virtual void OnMouseUp(System::Windows::Forms::MouseEventArgs^ e) override;
		virtual void OnMouseMove(System::Windows::Forms::MouseEventArgs^ e) override;
		virtual void OnGotFocus(System::EventArgs^e) override
		{
			__super::OnGotFocus(e);
			this->Parent->Focus();
		}
	private:
		void resizeSlider()
		{
			if (totalItems == 0)
			{
				sliderHeight = sliderAreaHeight;
				sliderPosition = 0;
			}
			else
			{
				sliderHeight = (int)(sliderAreaHeight*viewableItems)/totalItems;
				sliderPosition = (int)(sliderAreaHeight*indexAtTop)/totalItems;
			}
			this->Invalidate();
		}
		bool scrolling;
		int scrollStart;
		int sliderPosition;
		int sliderAreaHeight;
		int sliderHeight;
		int totalItems;
		int indexAtTop;
		int viewableItems;
		int scrollButtonHeight;
		System::Drawing::Bitmap^ offScreen;
		System::Drawing::Drawing2D::LinearGradientBrush^ backBrush;
		System::Drawing::Drawing2D::LinearGradientBrush^ slideBrush;
	};
};