#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace BAPSPresenter
{
	public ref class BAPSButton : public System::Windows::Forms::Control, public System::Windows::Forms::IButtonControl
	{
	public:
		BAPSButton()
		{
			this->SetStyle((System::Windows::Forms::ControlStyles)
						   (System::Windows::Forms::ControlStyles::UserPaint |
						   System::Windows::Forms::ControlStyles::AllPaintingInWmPaint |
						   System::Windows::Forms::ControlStyles::DoubleBuffer |
						   System::Windows::Forms::ControlStyles::Selectable |
						   System::Windows::Forms::ControlStyles::StandardClick |
						   System::Windows::Forms::ControlStyles::SupportsTransparentBackColor |
						   System::Windows::Forms::ControlStyles::UserMouse),
						   true);
			highlightColor = System::Drawing::Color::Red;
			isHighlighted = false;
			voffset = 0;
			myDialogResult = System::Windows::Forms::DialogResult::None;
			IsDefault = false;
			backBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(System::Drawing::Rectangle(0,0,10,10), System::Drawing::Color::Tan, System::Drawing::Color::Snow,System::Drawing::Drawing2D::LinearGradientMode::Vertical );
		}
		property bool Highlighted
		{
			bool get()
			{
				return isHighlighted;
			}
			void set(bool value)
			{
				isHighlighted = value;
				HighlightChanged();
			}
		}
		property System::Drawing::Color HighlightColor
		{
			System::Drawing::Color get()
			{
				return highlightColor;
			}
			void set(System::Drawing::Color value)
			{
				highlightColor = value;
				HighlightChanged();
			}
		}
		virtual property System::String^ Text
		{
			System::String^ get() override
			{
				return __super::Text;
			}
			void set(System::String^ value) override
			{
				__super::Text = value;
				this->Invalidate();
			}
		}
		property System::Windows::Forms::DialogResult DialogResult 
		{
			// Add implementation to the IButtonControl.DialogResult property.
			virtual System::Windows::Forms::DialogResult get()
			{
				return this->myDialogResult;
			}

			virtual void set( System::Windows::Forms::DialogResult value )
			{
				if ( Enum::IsDefined( System::Windows::Forms::DialogResult::typeid, value ) )
				{
					this->myDialogResult = value;
				}
			}
		}
		// Add implementation to the IButtonControl.NotifyDefault method.
		virtual void NotifyDefault( bool value )
		{
			if ( this->IsDefault != value )
			{
				this->IsDefault = value;
			}
		}

		// Add implementation to the IButtonControl.PerformClick method.
		virtual void PerformClick()
		{
			if ( this->CanSelect )
			{
				this->OnClick( EventArgs::Empty );
			}
		}
	protected:
	virtual void OnKeyDown(System::Windows::Forms::KeyEventArgs^ e) override;
	virtual void OnMouseDown(System::Windows::Forms::MouseEventArgs^ e) override;
	virtual void OnMouseUp(System::Windows::Forms::MouseEventArgs^ e) override;
	virtual void OnMouseEnter(System::EventArgs^ e) override;
	virtual void OnMouseLeave(System::EventArgs^ e) override;
	virtual void OnResize(System::EventArgs^ e) override;
	virtual void OnPaint(System::Windows::Forms::PaintEventArgs^ e) override;
	virtual void OnPaintBackground(System::Windows::Forms::PaintEventArgs^ e) override;
	virtual void OnGotFocus(System::EventArgs^e)override
	{
		this->Invalidate();
	}
	virtual void OnEnabledChanged(System::EventArgs^ e) override
	{
		__super::OnEnabledChanged(e);
		this->Invalidate();
	}
	virtual void OnLostFocus(System::EventArgs^e)override
	{
		this->Invalidate();
	}
	void HighlightChanged();
	private:
		bool IsDefault;
		int voffset;
		bool isHighlighted;
		System::Drawing::Color highlightColor;
		System::Windows::Forms::DialogResult myDialogResult;
		System::Drawing::Drawing2D::LinearGradientBrush^ backBrush;
	};
}