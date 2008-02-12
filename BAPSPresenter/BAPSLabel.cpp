#include "StdAfx.h"
#include "BAPSLabel.h"

using namespace BAPSPresenter;

void BAPSLabel::OnResize(System::EventArgs^ e)
{
	backBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(this->ClientRectangle,
							((isHighlighted)?highlightColor:System::Drawing::Color::Snow),
							System::Drawing::Color::AntiqueWhite,
							System::Drawing::Drawing2D::LinearGradientMode::Vertical );
	backBrush->SetBlendTriangularShape(0.5);
	offScreen = gcnew System::Drawing::Bitmap(this->ClientSize.Width, this->ClientSize.Height);
	prepareGraphics();
}

void BAPSLabel::OnPaint(System::Windows::Forms::PaintEventArgs^ e)
{
	e->Graphics->DrawImage(offScreen, 0, 0);
	System::Drawing::StringFormat^ sf = gcnew System::Drawing::StringFormat();
	sf->Alignment = System::Drawing::StringAlignment::Center;
	sf->LineAlignment = System::Drawing::StringAlignment::Center;
	System::Drawing::Rectangle rect = this->ClientRectangle;
	if (System::String::Compare(infoText, "") != 0)
	{
		System::Drawing::Font^ font = gcnew System::Drawing::Font(this->Font->FontFamily, 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
		e->Graphics->DrawString(infoText, font, gcnew System::Drawing::SolidBrush(ForeColor), 5.0,1.0);
		// have info text to display
		rect.Y += 12;
		rect.Height -= 12;
	}

	e->Graphics->DrawString(this->Text, this->Font, gcnew System::Drawing::SolidBrush(ForeColor), rect, sf);
}

void BAPSLabel::prepareGraphics()
{
	if (this->ClientRectangle.Width > 0 && this->ClientRectangle.Height > 0)
	{
		System::Drawing::Graphics^ gOffScreen = System::Drawing::Graphics::FromImage(offScreen);

		int curveWidth = ((this->ClientRectangle.Height>30)?20:this->ClientRectangle.Height/2);
		gOffScreen->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
		System::Drawing::Drawing2D::GraphicsPath^ gp = gcnew System::Drawing::Drawing2D::GraphicsPath();
		gp->AddArc(ClientRectangle.Width - (curveWidth+1), 0, curveWidth, curveWidth, 270, 90);
		gp->AddArc(ClientRectangle.Width - (curveWidth+1), ClientRectangle.Height - (curveWidth+1), curveWidth, curveWidth, 0, 90);
		gp->AddArc(0, ClientRectangle.Height - (curveWidth+1), curveWidth, curveWidth, 90, 90);
		gp->AddArc(0, 0, curveWidth, curveWidth, 180, 90);
		gp->CloseFigure();
		gOffScreen->FillPath(backBrush, gp);
		gOffScreen->DrawPath(System::Drawing::Pens::LightGray, gp);
		delete gOffScreen;
	}
}

void BAPSLabel::OnPaintBackground(System::Windows::Forms::PaintEventArgs^ e)
{
	__super::OnPaintBackground(e);
}

void BAPSLabel::HighlightChanged()
{
	if (this->ClientRectangle.Width >0 && this->ClientRectangle.Height>0)
	{
		backBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(this->ClientRectangle, 
								((isHighlighted)?highlightColor:System::Drawing::Color::Snow),
								System::Drawing::Color::AntiqueWhite,
								System::Drawing::Drawing2D::LinearGradientMode::Vertical );
		backBrush->SetBlendTriangularShape(0.5);		
		prepareGraphics();
		this->Invalidate();
	}
}