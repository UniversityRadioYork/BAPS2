#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace BAPSPresenter
{
	public ref class BAPSLabel : public System::Windows::Forms::Control
	{
	public:
		BAPSLabel()
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
			infoText = "";
			this->TabStop = false;
			backBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(System::Drawing::Rectangle(0,0,10,10), System::Drawing::Color::Tan, System::Drawing::Color::Snow,System::Drawing::Drawing2D::LinearGradientMode::Vertical );
		}
		property System::String^ Text
		{
			virtual System::String^ get() override
			{
				return __super::Text;
			}
			virtual void set(System::String^ value) override
			{
				__super::Text = value;
				this->Invalidate();
			}
		}
		property System::String^ InfoText
		{
			System::String^ get()
			{
				return infoText;
			}
			void set(System::String^ value)
			{
				infoText = value;
				this->Invalidate();
			}
		}
	virtual void OnResize(System::EventArgs^ e) override;
	virtual void OnPaint(System::Windows::Forms::PaintEventArgs^ e) override;
	virtual void OnPaintBackground(System::Windows::Forms::PaintEventArgs^ e) override;
	private:
		System::Drawing::Drawing2D::LinearGradientBrush^ backBrush;
		System::String^ infoText;
	};
}