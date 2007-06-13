#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace BAPSPresenter
{
	enum TimeLineMoveStatus
	{
		TIMELINE_MOVE_CHAN0 = 0,
		TIMELINE_MOVE_CHAN1 = 1,
		TIMELINE_MOVE_CHAN2 = 2,
		TIMELINE_MOVE_NONE
	};

	public ref class TimeLineEventArgs : public System::EventArgs
	{
	public:
		int channel;
		int startTime;
		TimeLineEventArgs(int _channel, int _startTime)
		{
			channel = _channel;
			startTime = _startTime;
		}
	};
	public delegate void TimeLineEventHandler(Object^ sender, TimeLineEventArgs^ e);

	public ref class TimeLine : public System::Windows::Forms::Control
	{
	public:
		TimeLine()
		{
			this->SetStyle((System::Windows::Forms::ControlStyles)
						   (System::Windows::Forms::ControlStyles::UserPaint |
						   System::Windows::Forms::ControlStyles::AllPaintingInWmPaint |
						   System::Windows::Forms::ControlStyles::DoubleBuffer |
						   System::Windows::Forms::ControlStyles::SupportsTransparentBackColor),
						   true);
			this->TabStop = false;
			currentTime = 0;
			trackDuration = gcnew array<int, 1>(3);
			trackDuration[0] = 0;
			trackDuration[1] = 0;
			trackDuration[2] = 0;

			trackPosition = gcnew array<int, 1>(3);
			trackPosition[0] = 0;
			trackPosition[1] = 0;
			trackPosition[2] = 0;

			startTime = gcnew array<int, 1>(3);
			startTime[0] = -1;
			startTime[1] = -1;
			startTime[2] = -1;

			trackDurationCache = gcnew array<int, 1>(3);
			trackDurationCache[0] = 0;
			trackDurationCache[1] = 0;
			trackDurationCache[2] = 0;

			trackPositionCache = gcnew array<int, 1>(3);
			trackPositionCache[0] = 0;
			trackPositionCache[1] = 0;
			trackPositionCache[2] = 0;

			startTimeCache = gcnew array<int, 1>(3);
			startTimeCache[0] = -1;
			startTimeCache[1] = -1;
			startTimeCache[2] = -1;

			moveOffset = gcnew array<int, 1>(3);
			moveOffset[0] = 0;
			moveOffset[1] = 0;
			moveOffset[2] = 0;

			locked = gcnew array<bool, 1>(3);
			locked[0] = false;
			locked[1] = false;
			locked[2] = false;

			moveStatus = TIMELINE_MOVE_NONE;
			startMoveAtX = 0;

			boundingBox = gcnew array<System::Drawing::Rectangle,1>(3);
			boundingBox[0] = System::Drawing::Rectangle(0,0,0,0);
			boundingBox[1] = System::Drawing::Rectangle(0,0,0,0);
			boundingBox[2] = System::Drawing::Rectangle(0,0,0,0);

			stoppedColour = System::Drawing::Brushes::DeepSkyBlue;
			runningColour = System::Drawing::Brushes::Orchid;

			cachedTime = System::DateTime::Now;

			dragEnabled = true;

			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	
		}
		void UpdateDuration(int channel, int duration)
		{
			trackDurationCache[channel] = duration;
			if (moveStatus == TIMELINE_MOVE_NONE)
			{
				trackDuration[channel] = duration;
			}
		}
		void UpdatePosition(int channel, int position)
		{
			trackPositionCache[channel] = position;
			if (moveStatus == TIMELINE_MOVE_NONE)
			{
				trackPosition[channel] = position;
			}
		}
		void UpdateStartTime(int channel, int newStartTime)
		{
			startTimeCache[channel] = newStartTime;
			if (moveStatus == TIMELINE_MOVE_NONE)
			{
				startTime[channel] = newStartTime;
			}
		}
		property bool DragEnabled
		{
			void set(bool value)
			{
				dragEnabled = value;
				UpdateStartTime(0,0);
				UpdateStartTime(1,0);
				UpdateStartTime(2,0);
			}
		}
	event TimeLineEventHandler^ StartTimeChanged;

	virtual void OnResize(System::EventArgs^ e) override;
	virtual void OnPaint(System::Windows::Forms::PaintEventArgs^ e) override;
	virtual void OnPaintBackground(System::Windows::Forms::PaintEventArgs^ e) override;
	virtual void OnMouseDown(System::Windows::Forms::MouseEventArgs ^e) override;
	virtual void OnMouseMove(System::Windows::Forms::MouseEventArgs ^e) override;
	virtual void OnMouseUp(System::Windows::Forms::MouseEventArgs ^e) override;

	void tick()
	{
		if (moveStatus == TIMELINE_MOVE_NONE)
		{
			cachedTime = System::DateTime::Now;
			this->Invalidate();
		}
	}
		array<bool, 1>^ locked;
	private:
		int currentTime;
		bool dragEnabled;
		array<int, 1>^ trackDuration;
		array<int, 1>^ trackPosition;
		array<int, 1>^ startTime;
		array<int, 1>^ trackDurationCache;
		array<int, 1>^ trackPositionCache;
		array<int, 1>^ startTimeCache;
		array<int, 1>^ moveOffset;
		array<System::Drawing::Rectangle, 1>^ boundingBox;
		System::DateTime cachedTime;
		System::Drawing::Brush^ runningColour;
		System::Drawing::Brush^ stoppedColour;
		TimeLineMoveStatus moveStatus;
		int startMoveAtX;
		static const int thirtySecondPixels = 60;
	};
}