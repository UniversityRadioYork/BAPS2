#include "StdAfx.h"
#include "TrackTime.h"

using namespace BAPSPresenter;

void TrackTime::OnPaint(System::Windows::Forms::PaintEventArgs^ e) 
{
	__super::OnPaint(e);
	e->Graphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
	e->Graphics->FillPath(backBrush, backgroundPath);
	//Paint the Text property on the control
	
	if (duration != 0)
	{
		float division = (float)ClientRectangle.Width/(float)duration;
		int positionPoint = (int)(division*(float)position);
		int silencePoint = (int)(division*(float)silencePosition);
		int cuePoint =(int)(division*(float)cuePosition);
		int introPoint =(int)(division*(float)introPosition);

		if (introPoint < curveWidth/2)
		{
			e->Graphics->FillRectangle(introBrush, 0, curveWidth/2, introPoint, ClientRectangle.Height - curveWidth);
		}
		else
		{
			e->Graphics->FillPath(introBrush, introPath);
		}
		if (cuePoint < curveWidth/2)
		{
			e->Graphics->FillRectangle(cueBrush, 0, curveWidth, cuePoint, ClientRectangle.Height - (int)1.5*curveWidth);
		}
		else
		{
			e->Graphics->FillPath(cueBrush, cuePath);
		}

		if (silencePoint < curveWidth/2)
		{
			e->Graphics->FillRectangle(System::Drawing::Brushes::Black, 0, curveWidth/2, silencePoint, ClientRectangle.Height - curveWidth);
		}
		else
		{
			e->Graphics->FillPath(System::Drawing::Brushes::Black, silencePath);
		}

		e->Graphics->FillRectangle(System::Drawing::Brushes::Red, System::Drawing::Rectangle(0, BASE_Y_LINE-2, positionPoint, 2));

		int markerCount = (duration/10000);
		int i = 0;
		for (i = 10000; i < duration ; i+=10000)
		{
			int markerHeight = 2;
			if (i%60000 == 0)
			{
				markerHeight = 4;
			}
			e->Graphics->DrawLine(System::Drawing::Pens::Black,
								(int)(division*(float)i),
								BASE_Y_LINE-markerHeight,
								(int)(division*(float)i),
								BASE_Y_LINE);
		}
		/** Draw the cue arrow and text **/
		e->Graphics->DrawLine(System::Drawing::Pens::Brown, cuePoint, BASE_Y_LINE+BASE_Y_CUE_ARROW, cuePoint, BASE_Y_LINE+BASE_Y_CUE_ARROW+HEIGHT_CUE_ARROW);
		e->Graphics->DrawLine(System::Drawing::Pens::Brown, cuePoint, BASE_Y_LINE+BASE_Y_CUE_ARROW+HEIGHT_CUE_ARROW_HALF, cuePoint+4, BASE_Y_LINE+BASE_Y_CUE_ARROW);
		e->Graphics->DrawLine(System::Drawing::Pens::Brown, cuePoint, BASE_Y_LINE+BASE_Y_CUE_ARROW+HEIGHT_CUE_ARROW_HALF, cuePoint+4, BASE_Y_LINE+BASE_Y_CUE_ARROW+HEIGHT_CUE_ARROW);
		e->Graphics->DrawLine(System::Drawing::Pens::Brown, cuePoint, BASE_Y_LINE+BASE_Y_CUE_ARROW+HEIGHT_CUE_ARROW_HALF, cuePoint+8, BASE_Y_LINE+BASE_Y_CUE_ARROW+HEIGHT_CUE_ARROW_HALF);
		e->Graphics->DrawString(MillisecondsToTimeString(cuePosition), 
								Font, 
								gcnew System::Drawing::SolidBrush(ForeColor), 
								System::Drawing::Rectangle(cuePoint+12, BASE_Y_LINE+BASE_Y_CUE_ARROW-2, 50, 12));
		/** Draw the intro arrow and text **/
		e->Graphics->DrawLine(System::Drawing::Pens::Brown, introPoint, BASE_Y_INTRO_ARROW, introPoint, BASE_Y_INTRO_ARROW+HEIGHT_INTRO_ARROW);
		e->Graphics->DrawLine(System::Drawing::Pens::Brown, introPoint, BASE_Y_INTRO_ARROW+HEIGHT_INTRO_ARROW_HALF, introPoint+4, BASE_Y_INTRO_ARROW);
		e->Graphics->DrawLine(System::Drawing::Pens::Brown, introPoint, BASE_Y_INTRO_ARROW+HEIGHT_INTRO_ARROW_HALF, introPoint+4, BASE_Y_INTRO_ARROW+HEIGHT_INTRO_ARROW);
		e->Graphics->DrawLine(System::Drawing::Pens::Brown, introPoint, BASE_Y_INTRO_ARROW+HEIGHT_INTRO_ARROW_HALF, introPoint+WIDTH_INTRO_ARROW, BASE_Y_INTRO_ARROW+HEIGHT_INTRO_ARROW_HALF);
		e->Graphics->DrawString(MillisecondsToTimeString(introPosition), 
								Font, 
								gcnew System::Drawing::SolidBrush(ForeColor), 
								System::Drawing::Rectangle(introPoint+12, BASE_Y_INTRO_ARROW-2, 50, 12));
		/** Draw the position arrow **/
		array<System::Drawing::Point>^ positionPointer = gcnew array<System::Drawing::Point>(5)
											   {System::Drawing::Point(positionPoint, BASE_Y_LINE-2),
												System::Drawing::Point(positionPoint+5, BASE_Y_LINE-7),
												System::Drawing::Point(positionPoint+5, BASE_Y_LINE-22),
												System::Drawing::Point(positionPoint-5, BASE_Y_LINE-22),
												System::Drawing::Point(positionPoint-5, BASE_Y_LINE-7)};
		e->Graphics->FillPolygon(System::Drawing::Brushes::Black, positionPointer, System::Drawing::Drawing2D::FillMode::Alternate);
	}
	e->Graphics->DrawLine(System::Drawing::Pens::Black, 0, BASE_Y_LINE, ClientRectangle.Width, BASE_Y_LINE);
	e->Graphics->DrawLine(System::Drawing::Pens::Black, 0, BASE_Y_LINE-5, 0, BASE_Y_LINE+5);
	e->Graphics->DrawLine(System::Drawing::Pens::Black, ClientRectangle.Width-1, BASE_Y_LINE+5, ClientRectangle.Width-1, BASE_Y_LINE-5);

	/** draw a box round it all **/
	/*System::Drawing::Pen^ myPen = System::Drawing::Pens::LightGray;
	if (this->Focused)
	{
		myPen = System::Drawing::Pens::Red;
	}
	e->Graphics->DrawPath(myPen, backgroundPath);*/
}

void TrackTime::OnMouseDown(System::Windows::Forms::MouseEventArgs^ e)
{
	__super::OnMouseDown(e);
	if (movingItem != TTMT_NONE)
	{
		System::Windows::Forms::Cursor::Current = System::Windows::Forms::Cursors::SizeWE;
	}
	else
	{
		System::Windows::Forms::Cursor::Current = System::Windows::Forms::Cursors::Default;
	}
}

void TrackTime::OnMouseMove(System::Windows::Forms::MouseEventArgs^ e)
{
	__super::OnMouseMove(e);
	if (e->Button == System::Windows::Forms::MouseButtons::Left)
	{
		int newPosition;
		if (e->X < 0)
		{
			newPosition = 0;
		}
		else if (e->X > ClientRectangle.Width-1)
		{
			newPosition = duration;
		}
		else
		{
			newPosition = (int)(((float)e->X)/division);
		}
		switch (movingItem)
		{
		case TTMT_POSITION:
			if (position != newPosition)
			{
				if (newPosition >= cuePosition)
				{
					position = newPosition;
				}
				else
				{
					position = cuePosition;
				}
				//this->Invalidate();
				PositionChanged(this, nullptr);
			}
			break;
		case TTMT_CUEPOSITION:
			if (cuePosition != newPosition)
			{
				cuePosition = newPosition;
				//this->Invalidate();
				CuePositionChanged(this, nullptr);
				if (cuePosition > position)
				{
					position = cuePosition;
					PositionChanged(this, nullptr);
				}
			}
			break;
		case TTMT_INTROPOSITION:
			if (introPosition != newPosition)
			{
				introPosition = newPosition;
				this->Invalidate();
				IntroPositionChanged(this, nullptr);
			}
			break;
		}
	}
	else
	{
		System::Drawing::Point pt = System::Drawing::Point(e->X,e->Y);
		//Check if we hit the position bar
		if (intersectsWithPositionMarker(pt))
		{
			movingItem = TTMT_POSITION;
		}
		//Check if we hit the intro bar
		else if (intersectsWithIntroMarker(pt))
		{
			movingItem = TTMT_INTROPOSITION;
			tooltip->SetToolTip(this, "Intro Position");
		}
		//Check if we hit the cue bar
		else if (intersectsWithCueMarker(pt))
		{
			movingItem = TTMT_CUEPOSITION;
			tooltip->SetToolTip(this, "Cue Position");
		}
		else
		{
			tooltip->SetToolTip(this, nullptr);
			movingItem = TTMT_NONE;
		}
		if (movingItem != TTMT_NONE)
		{
			System::Windows::Forms::Cursor::Current = System::Windows::Forms::Cursors::SizeWE;
		}
		else
		{
			System::Windows::Forms::Cursor::Current = System::Windows::Forms::Cursors::Default;
		}
	}
}
