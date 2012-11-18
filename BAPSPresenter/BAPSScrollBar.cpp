#include "StdAfx.h"
#include "BAPSScrollBar.h"
using namespace BAPSPresenter;

void BAPSScrollBar::OnPaint(System::Windows::Forms::PaintEventArgs^ e)
{
	//__super::OnPaint(e);
	System::Drawing::Graphics^ gOffScreen = System::Drawing::Graphics::FromImage(offScreen);
	System::Drawing::Rectangle rect = System::Drawing::Rectangle(this->ClientRectangle.X, this->ClientRectangle.Y, this->ClientRectangle.Width-1, this->ClientRectangle.Height-1);
	gOffScreen->FillRectangle(backBrush, rect);
	gOffScreen->DrawRectangle(System::Drawing::Pens::LightGray, rect);
	System::Drawing::Drawing2D::GraphicsPath^ gp = gcnew System::Drawing::Drawing2D::GraphicsPath();
	array<System::Drawing::Point>^ pts = gcnew array<System::Drawing::Point>(3)
		{System::Drawing::Point((int)(this->ClientRectangle.Width/2), (int)(scrollButtonHeight*0.25)),
		 System::Drawing::Point((int)(scrollButtonHeight*0.25), (int)(scrollButtonHeight*0.75)),
		 System::Drawing::Point((int)(scrollButtonHeight*0.75), (int)(scrollButtonHeight*0.75))};
	gp->AddPolygon(pts);
	gp->CloseFigure();
	gOffScreen->FillPath(System::Drawing::Brushes::Black, gp);
	gp->Reset();
	pts[0] = System::Drawing::Point((int)(this->ClientRectangle.Width/2),this->ClientRectangle.Height-(int)(scrollButtonHeight*0.25));
	pts[1] = System::Drawing::Point((int)(scrollButtonHeight*0.25),this->ClientRectangle.Height-(int)(scrollButtonHeight*0.75));
	pts[2] = System::Drawing::Point((int)(scrollButtonHeight*0.75),this->ClientRectangle.Height-(int)(scrollButtonHeight*0.75));
	gp->AddPolygon(pts);
	gp->CloseFigure();
	gOffScreen->FillPath(System::Drawing::Brushes::Black, gp);

	gOffScreen->DrawRectangle(System::Drawing::Pens::LightGray, this->ClientRectangle.X, this->ClientRectangle.Y, this->ClientRectangle.Width-1, scrollButtonHeight);
	gOffScreen->DrawRectangle(System::Drawing::Pens::LightGray, this->ClientRectangle.X, this->ClientRectangle.Y+this->ClientRectangle.Height-1-scrollButtonHeight, this->ClientRectangle.Width-1, scrollButtonHeight);
	rect = System::Drawing::Rectangle(this->ClientRectangle.X, sliderPosition+scrollButtonHeight, this->ClientRectangle.Width-1, sliderHeight);

	gOffScreen->FillRectangle(slideBrush, rect);

	gOffScreen->DrawRectangle(System::Drawing::Pens::LightGray, rect);
	e->Graphics->DrawImage(offScreen, 0, 0);
	delete gOffScreen;
}

void BAPSScrollBar::OnPaintBackground(System::Windows::Forms::PaintEventArgs^ e)
{
	//__super::OnPaintBackground(e);


}

void BAPSScrollBar::OnResize(System::EventArgs^ e)
{
	__super::OnResize(e);
	offScreen = gcnew System::Drawing::Bitmap(this->ClientSize.Width, this->ClientSize.Height);
	scrollButtonHeight = this->ClientRectangle.Width;
	backBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(this->ClientRectangle, System::Drawing::Color::Snow, System::Drawing::Color::AntiqueWhite,System::Drawing::Drawing2D::LinearGradientMode::Horizontal );
	backBrush->SetBlendTriangularShape(0.5);
	slideBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(this->ClientRectangle, System::Drawing::Color::Tan, System::Drawing::Color::Snow,System::Drawing::Drawing2D::LinearGradientMode::Horizontal );
	slideBrush->SetBlendTriangularShape(0.5);
	sliderAreaHeight = (this->ClientRectangle.Height-(1+(2*scrollButtonHeight)));
	resizeSlider();
}

void BAPSScrollBar::OnMouseDown(System::Windows::Forms::MouseEventArgs^ e)
{
	__super::OnMouseDown(e);
	System::Drawing::Rectangle rect = System::Drawing::Rectangle(0,0, scrollButtonHeight, scrollButtonHeight);
	if (rect.Contains(e->X, e->Y) && indexAtTop > 0)
	{
		// clicked in top button
		indexAtTop -= 1;
		TopIndexChanged(this, System::EventArgs::Empty);
		goingUp = true;
		timer->Interval = 100;
		timer->Enabled=true;
	}
	rect.Y = this->ClientRectangle.Height-scrollButtonHeight;
	if (rect.Contains(e->X, e->Y) && totalItems-viewableItems>indexAtTop)
	{
		// clicked in bottom button
		indexAtTop += 1;
		TopIndexChanged(this, System::EventArgs::Empty);
		goingUp = false;
		timer->Interval = 100;
		timer->Enabled=true;
	}
	rect.Y = sliderPosition+scrollButtonHeight;
	rect.Height = sliderHeight;
	if (rect.Contains(e->X, e->Y))
	{
		scrolling = true;
		scrollStart = e->Y;
	}
	resizeSlider();
}
void BAPSScrollBar::OnMouseUp(System::Windows::Forms::MouseEventArgs^ e)
{
	__super::OnMouseUp(e);
	scrolling = false;
	timer->Enabled = false;
}
void BAPSScrollBar::OnMouseMove(System::Windows::Forms::MouseEventArgs^ e)
{
	__super::OnMouseMove(e);
	if (scrolling)
	{
		int newSliderPosition = sliderPosition;
		if (e->Y > scrollStart)
		{
			// we are going down
			if ((e->Y-scrollStart)+sliderHeight+sliderPosition>sliderAreaHeight)
			{
				newSliderPosition = sliderAreaHeight-sliderHeight;
			}
			else
			{
				newSliderPosition += e->Y-scrollStart;
				scrollStart = e->Y;
			}
		}
		else if (e->Y < scrollStart)
		{
			// we are going up
			if (sliderPosition-(scrollStart - e->Y)>=0)
			{
				newSliderPosition -= scrollStart-e->Y;
				scrollStart = e->Y;
			}
			else
			{
				newSliderPosition = 0;
			}
		}
		if (newSliderPosition != sliderPosition)
		{
			sliderPosition = newSliderPosition;
			this->Refresh();
		}
		int newTopIndex = (int)((sliderPosition*totalItems)/sliderAreaHeight);
		if (newTopIndex != IndexAtTop)
		{
			indexAtTop = newTopIndex;
			TopIndexChanged(this, System::EventArgs::Empty);
		}
	}
}