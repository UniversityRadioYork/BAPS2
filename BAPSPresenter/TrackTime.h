#pragma once
#include "Globals.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::ComponentModel::Design;
using namespace System::Collections;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Windows::Forms::Design;
using namespace System::Security::Permissions;

#define BASE_Y_LINE				44

#define BASE_Y_INTRO_ARROW		8
#define WIDTH_INTRO_ARROW		8
#define HEIGHT_INTRO_ARROW		8
#define HEIGHT_INTRO_ARROW_HALF	4

#define BASE_Y_CUE_ARROW		12
#define WIDTH_CUE_ARROW			8
#define HEIGHT_CUE_ARROW		8
#define HEIGHT_CUE_ARROW_HALF	4

namespace BAPSPresenter
{
	enum TrackTimeMovingType
	{
		TTMT_NONE,
		TTMT_POSITION,
		TTMT_INTROPOSITION,
		TTMT_CUEPOSITION
	};

	public ref class TrackTime : public System::Windows::Forms::Control
	{
	public:
		TrackTime()
			: System::Windows::Forms::Control(),
			  duration(0),
			  position(0),
			  silencePosition(0),
			  cuePosition(0),
			  introPosition(0),
			  channel(0),
			  movingItem(TTMT_NONE),
			  division(0.0)
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
			tooltip = gcnew System::Windows::Forms::ToolTip();
			// Set up the delays for the ToolTip.
			tooltip->AutoPopDelay = 5000;
			tooltip->InitialDelay = 1000;
			tooltip->ReshowDelay = 500;
			// Force the ToolTip text to be displayed whether or not the form is active.
			tooltip->ShowAlways = true;

			backBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(System::Drawing::Rectangle(0,0,10,10), System::Drawing::Color::Snow, System::Drawing::Color::AntiqueWhite,System::Drawing::Drawing2D::LinearGradientMode::Vertical );
			cueBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(System::Drawing::Rectangle(0,0,10,10), System::Drawing::Color::Snow, System::Drawing::Color::DarkOrchid,System::Drawing::Drawing2D::LinearGradientMode::Vertical );
			introBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(System::Drawing::Rectangle(0,0,10,10), System::Drawing::Color::Snow, System::Drawing::Color::DarkOrchid,System::Drawing::Drawing2D::LinearGradientMode::Vertical );
			curveWidth = 20;
		}
		virtual void OnResize(System::EventArgs ^e) override
		{
			__super::OnResize(e);
			backBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(this->ClientRectangle, System::Drawing::Color::Snow, System::Drawing::Color::AntiqueWhite,System::Drawing::Drawing2D::LinearGradientMode::Vertical );
			backBrush->SetBlendTriangularShape(0.5);
			cueBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(this->ClientRectangle, System::Drawing::Color::Snow, System::Drawing::Color::Crimson,System::Drawing::Drawing2D::LinearGradientMode::Vertical );
			cueBrush->SetBlendTriangularShape(0.5);
			introBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(this->ClientRectangle, System::Drawing::Color::Snow, System::Drawing::Color::ForestGreen,System::Drawing::Drawing2D::LinearGradientMode::Vertical );
			introBrush->SetBlendTriangularShape(0.5);
			backgroundPath = gcnew System::Drawing::Drawing2D::GraphicsPath();
			backgroundPath->AddArc(ClientRectangle.Width - (curveWidth+1), 0, curveWidth, curveWidth, 270, 90);
			backgroundPath->AddArc(ClientRectangle.Width - (curveWidth+1), ClientRectangle.Height - (curveWidth+1), curveWidth, curveWidth, 0, 90);
			backgroundPath->AddArc(0, ClientRectangle.Height - (curveWidth+1), curveWidth, curveWidth, 90, 90);
			backgroundPath->AddArc(0, 0, curveWidth, curveWidth, 180, 90);
			backgroundPath->CloseFigure();
		}
		event System::EventHandler^ PositionChanged;
		event System::EventHandler^ IntroPositionChanged;
		event System::EventHandler^ CuePositionChanged;

		property int Channel
		{
			int get()
			{
				return channel;
			}
			void set(int _channel)
			{
				channel = _channel;
			}
		}
		property int Position
		{
			int get()
			{
				return position;
			}
			void set(int _position)
			{
				bool diff = position!=_position;
				position = _position;
				this->Invalidate();

			}
		}

		property int Duration
		{
			int get()
			{
				return duration;
			}
			void set(int _duration)
			{
				duration = _duration;
				division = (float)ClientRectangle.Width/(float)duration;
				this->Invalidate();
			}
		}
		property int CuePosition
		{
			int get()
			{
				return cuePosition;
			}
			void set(int _cuePosition)
			{
				cuePosition = _cuePosition;
				int cuePoint =(int)(division*(float)cuePosition);
				cuePath = gcnew System::Drawing::Drawing2D::GraphicsPath();
				cuePath->AddArc(cuePoint - curveWidth, curveWidth, curveWidth, curveWidth, 270, 90);
				cuePath->AddArc(cuePoint - curveWidth, ClientRectangle.Height - curveWidth, curveWidth, curveWidth, 0, 90);
				cuePath->AddArc(0, ClientRectangle.Height - curveWidth, curveWidth, curveWidth, 90, 90);
				cuePath->AddArc(0, curveWidth, curveWidth, curveWidth, 180, 90);
				cuePath->CloseFigure();
				this->Invalidate();
			}
		}
		property int SilencePosition
		{
			int get()
			{
				return silencePosition;
			}
			void set(int _silencePosition)
			{
				silencePosition = _silencePosition;
				int silencePoint = (int)(division*(float)silencePosition);
				silencePath = gcnew System::Drawing::Drawing2D::GraphicsPath();
				silencePath->AddArc(silencePoint - curveWidth, 0, curveWidth, curveWidth, 270, 90);
				silencePath->AddArc(silencePoint - curveWidth, ClientRectangle.Height - curveWidth, curveWidth, curveWidth, 0, 90);
				silencePath->AddArc(0, ClientRectangle.Height - curveWidth, curveWidth, curveWidth, 90, 90);
				silencePath->AddArc(0, 0, curveWidth, curveWidth, 180, 90);
				silencePath->CloseFigure();
				this->Invalidate();
			}
		}
		property int IntroPosition
		{
			int get()
			{
				return introPosition;
			}
			void set(int _introPosition)
			{
				introPosition = _introPosition;
				int introPoint =(int)(division*(float)introPosition);
				introPath = gcnew System::Drawing::Drawing2D::GraphicsPath();
				introPath->AddArc(introPoint - curveWidth, curveWidth/2, curveWidth, curveWidth, 270, 90);
				introPath->AddArc(introPoint - curveWidth, ClientRectangle.Height - curveWidth, curveWidth, curveWidth, 0, 90);
				introPath->AddArc(0, ClientRectangle.Height - curveWidth, curveWidth, curveWidth, 90, 90);
				introPath->AddArc(0, curveWidth/2, curveWidth, curveWidth, 180, 90);
				introPath->CloseFigure();
				this->Invalidate();
			}
		}

	protected:

		virtual void OnMouseDown(System::Windows::Forms::MouseEventArgs^ e) override;
		virtual void OnMouseMove(System::Windows::Forms::MouseEventArgs^ e) override;
		virtual void OnPaint(System::Windows::Forms::PaintEventArgs^ e) override;
		virtual void OnGotFocus(System::EventArgs^ e) override
		{
			__super::OnGotFocus(e);
			this->Invalidate();
		}
		virtual void OnLostFocus(System::EventArgs^ e) override
		{
			__super::OnLostFocus(e);
			this->Invalidate();
		}

	private:

		inline bool intersectsWithPositionMarker(System::Drawing::Point p)
		{
			int positionPoint = (int)(division*(float)position);
			System::Drawing::Rectangle rect = System::Drawing::Rectangle(positionPoint-5, BASE_Y_LINE-22, 10,20);
			return rect.Contains(p);
		}
		inline bool intersectsWithCueMarker(System::Drawing::Point p)
		{
			int cuePoint =(int)(division*(float)cuePosition);
			System::Drawing::Rectangle rect = System::Drawing::Rectangle(cuePoint-2, 0, 4, ClientRectangle.Height);
			System::Drawing::Rectangle rect2 = System::Drawing::Rectangle(cuePoint, BASE_Y_LINE+BASE_Y_CUE_ARROW, WIDTH_CUE_ARROW, HEIGHT_CUE_ARROW);
			return rect.Contains(p) || rect2.Contains(p);
		}
		inline bool intersectsWithIntroMarker(System::Drawing::Point p)
		{
			int introPoint =(int)(division*(float)introPosition);
			System::Drawing::Rectangle rect = System::Drawing::Rectangle(introPoint-2, 0, 4, ClientRectangle.Height);
			System::Drawing::Rectangle rect2 = System::Drawing::Rectangle(introPoint, BASE_Y_INTRO_ARROW, WIDTH_INTRO_ARROW, HEIGHT_INTRO_ARROW);
			return rect.Contains(p) || rect2.Contains(p);
		}
		TrackTimeMovingType movingItem;
		int duration;
		float division;
		int position;
		int silencePosition;
		int cuePosition;
		int introPosition;
		int channel;
		System::Drawing::Drawing2D::LinearGradientBrush^ backBrush;
		System::Drawing::Drawing2D::LinearGradientBrush^ introBrush;
		System::Drawing::Drawing2D::LinearGradientBrush^ cueBrush;
		System::Drawing::Drawing2D::GraphicsPath^ backgroundPath;
		System::Drawing::Drawing2D::GraphicsPath^ introPath;
		System::Drawing::Drawing2D::GraphicsPath^ cuePath;
		System::Drawing::Drawing2D::GraphicsPath^ silencePath;

		System::Windows::Forms::ToolTip^ tooltip;
		int curveWidth;
	};
};