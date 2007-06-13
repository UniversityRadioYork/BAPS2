#include "StdAfx.h"
#include "TimeLine.h"

using namespace BAPSPresenter;

void TimeLine::OnResize(System::EventArgs^ e)
{
}

void TimeLine::OnPaint(System::Windows::Forms::PaintEventArgs^ e)
{
	static const int drawStartPosition = 20;
	System::Drawing::StringFormat^ sf = gcnew System::Drawing::StringFormat();
	sf->Alignment = System::Drawing::StringAlignment::Center;
	sf->LineAlignment = System::Drawing::StringAlignment::Center;
	System::DateTime dt = cachedTime;
	int i = 0;
	for (i = 0 ; i < 3 ;i++)
	{
		System::Drawing::Rectangle rect = System::Drawing::Rectangle(2, (i*11)-2, 10, 14);
		e->Graphics->DrawString((i+1).ToString(),this->Font,System::Drawing::Brushes::Black, rect);
		int width = (((trackDuration[i]-(locked[i]?trackPosition[i]:0))/1000)*thirtySecondPixels)/30;
		int startOffset = 0;
		int timeOffset = 0;
		if (startTime[i] != -1)
		{
			startOffset = ((startTime[i]/1000)*thirtySecondPixels)/30;
			timeOffset = startTime[i];
		}
		if (startOffset + moveOffset[i] < 0)
		{
			moveOffset[i] = -startOffset;
			startOffset = 0;
		}
		else
		{
			startOffset += moveOffset[i];
		}
		timeOffset += (moveOffset[i]*30000)/thirtySecondPixels;
		rect = System::Drawing::Rectangle(drawStartPosition+40+startOffset, i*11, width, 8);
		boundingBox[i] = rect;
		e->Graphics->FillRectangle((locked[i])?runningColour:stoppedColour,rect);
		int starttextx = rect.X-50;
		rect.X += rect.Width+1;
		rect.Y -= 2;
		rect.Height += 4;
		rect.Width = 50;
		if (width != 0)
		{
			e->Graphics->DrawString(dt.AddMilliseconds(timeOffset+trackDuration[i]-(locked[i]?trackPosition[i]:0)).ToString("T"),this->Font,System::Drawing::Brushes::Black, rect);
		}
		if (timeOffset != 0)
		{
			rect.X = starttextx;
			e->Graphics->DrawString(dt.AddMilliseconds(timeOffset).ToString("T"),this->Font,System::Drawing::Brushes::Black, rect);
		}
	}

	e->Graphics->DrawLine(System::Drawing::Pens::Black, 0,33, this->ClientRectangle.Width, 33);

	System::Drawing::Rectangle rect = System::Drawing::Rectangle(drawStartPosition+10, 40, thirtySecondPixels, 10);

	while (rect.X+thirtySecondPixels-5 < this->ClientRectangle.Width)
	{
		e->Graphics->DrawLine(System::Drawing::Pens::Black, rect.X+30,0, rect.X+30, 38);
		e->Graphics->DrawString(dt.ToString("T"), this->Font, (rect.X==drawStartPosition+10)?System::Drawing::Brushes::Black:System::Drawing::Brushes::DarkGray, rect, sf);
		rect.X += thirtySecondPixels;
		dt = dt.AddSeconds(30);
	}

}

void TimeLine::OnPaintBackground(System::Windows::Forms::PaintEventArgs^ e)
{
	__super::OnPaintBackground(e);

}

void TimeLine::OnMouseDown(System::Windows::Forms::MouseEventArgs ^e)
{
	__super::OnMouseDown(e);
	if (!dragEnabled)
	{
		return;
	}
	System::Windows::Forms::Cursor::Current = System::Windows::Forms::Cursors::Default;
	int i;
	for (i = 0 ; i < 3 ; i++)
	{
		if (boundingBox[i].Contains(e->X, e->Y) && !locked[i])
		{
			moveStatus = (TimeLineMoveStatus)i;
			startMoveAtX = e->X;
			System::Windows::Forms::Cursor::Current = System::Windows::Forms::Cursors::SizeWE;
			break;
		}
	}	
}
void TimeLine::OnMouseMove(System::Windows::Forms::MouseEventArgs ^e)
{
	__super::OnMouseMove(e);
	if (moveStatus != TIMELINE_MOVE_NONE && e->Button == System::Windows::Forms::MouseButtons::Left)
	{
		moveOffset[moveStatus] = e->X - startMoveAtX;
		this->Invalidate();
	}
}
void TimeLine::OnMouseUp(System::Windows::Forms::MouseEventArgs ^e)
{
	__super::OnMouseUp(e);
	if (moveStatus != TIMELINE_MOVE_NONE)
	{
		startTime[moveStatus] = startTime[moveStatus]+(moveOffset[moveStatus]*30000)/thirtySecondPixels;
		startTimeCache[moveStatus] = startTime[moveStatus];
		if (startTime[moveStatus] > 0)
		{
			StartTimeChanged(this, gcnew TimeLineEventArgs(moveStatus, (((cachedTime.Minute*60)+cachedTime.Second)*1000)+
																		cachedTime.Millisecond+
																		startTime[moveStatus]));
		}
	}
	moveStatus = TIMELINE_MOVE_NONE;
	int i = 0;
	for (i = 0 ; i < 3 ; i++)
	{
		trackDuration[i] = trackDurationCache[i];
		trackPosition[i] = trackPositionCache[i];
		startTime[i] = startTimeCache[i];
		moveOffset[i] = 0;
	}
	this->Invalidate();
}