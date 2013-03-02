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
						  (System::Windows::Forms::ControlStyles::UserPaint|
						  System::Windows::Forms::ControlStyles::SupportsTransparentBackColor|
						   System::Windows::Forms::ControlStyles::OptimizedDoubleBuffer),
						   true);
			infoText = "";
			this->TabStop = false;
			highlightColor = System::Drawing::Color::Red;
			isHighlighted = false;
			backBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(System::Drawing::Rectangle(0,0,10,10), System::Drawing::Color::Tan, System::Drawing::Color::Snow,System::Drawing::Drawing2D::LinearGradientMode::Vertical );
			offScreen = gcnew System::Drawing::Bitmap(1,1);
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
		property System::String^ Text
		{
			virtual System::String^ get() override
			{
				return __super::Text;
			}
			virtual void set(System::String^ value) override
			{
				__super::Text = value;
				prepareGraphics();
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
				prepareGraphics();
				this->Invalidate();
			}
		}

	virtual void OnResize(System::EventArgs^ e) override;
	virtual void OnPaint(System::Windows::Forms::PaintEventArgs^ e) override;
	virtual void OnPaintBackground(System::Windows::Forms::PaintEventArgs^ e) override;
	private:
		void prepareGraphics();
		void HighlightChanged();
		System::Drawing::Drawing2D::LinearGradientBrush^ backBrush;
		System::String^ infoText;
		bool isHighlighted;
		System::Drawing::Color highlightColor;
		System::Drawing::Bitmap^ offScreen;
	};
}