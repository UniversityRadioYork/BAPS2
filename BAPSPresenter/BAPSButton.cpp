#include "StdAfx.h"
#include "BAPSButton.h"

using namespace BAPSPresenter;

void BAPSButton::OnResize(System::EventArgs^ e)
{
	backBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(this->ClientRectangle,
							((isHighlighted)?highlightColor:System::Drawing::Color::Tan),
							System::Drawing::Color::Snow,
							System::Drawing::Drawing2D::LinearGradientMode::Vertical );
	backBrush->SetBlendTriangularShape(0.5);
}

void BAPSButton::OnMouseDown(System::Windows::Forms::MouseEventArgs^ e)
{
	if (e->Button == System::Windows::Forms::MouseButtons::Left)
	{
		backBrush->SetBlendTriangularShape((float)0.55);
		voffset = (int)(0.1*this->ClientRectangle.Height);
		this->Invalidate();
	}
	__super::OnMouseDown(e);

}
void BAPSButton::OnMouseUp(System::Windows::Forms::MouseEventArgs^ e)
{
	if (e->Button == System::Windows::Forms::MouseButtons::Left)
	{
		backBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(this->ClientRectangle, 
								System::Drawing::Color::Chocolate, 
								System::Drawing::Color::Snow,
								System::Drawing::Drawing2D::LinearGradientMode::Vertical );
		backBrush->SetBlendTriangularShape(0.5);
		voffset = 0;
		this->Invalidate();
	}
	__super::OnMouseUp(e);
}
void BAPSButton::OnMouseEnter(System::EventArgs^ e)
{
	backBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(this->ClientRectangle, 
							System::Drawing::Color::Chocolate,
							System::Drawing::Color::Snow,
							System::Drawing::Drawing2D::LinearGradientMode::Vertical );
	backBrush->SetBlendTriangularShape(0.5);
	voffset = 0;
	this->Invalidate();
	__super::OnMouseEnter(e);
}
void BAPSButton::OnMouseLeave(System::EventArgs^ e)
{
	backBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(this->ClientRectangle, 
							((isHighlighted)?highlightColor:System::Drawing::Color::Tan),
							System::Drawing::Color::Snow,
							System::Drawing::Drawing2D::LinearGradientMode::Vertical );
	backBrush->SetBlendTriangularShape(0.5);
	voffset = 0;
	this->Invalidate();
	__super::OnMouseLeave(e);
}
void BAPSButton::OnPaint(System::Windows::Forms::PaintEventArgs^ e)
{
	e->Graphics->TextRenderingHint = System::Drawing::Text::TextRenderingHint::AntiAliasGridFit;
	int curveWidth = ((this->ClientRectangle.Height>30)?20:this->ClientRectangle.Height/2);
	e->Graphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
	System::Drawing::Drawing2D::GraphicsPath^ gp = gcnew System::Drawing::Drawing2D::GraphicsPath();
	gp->AddArc(ClientRectangle.Width - (curveWidth+1), 0, curveWidth, curveWidth, 270, 90);
	gp->AddArc(ClientRectangle.Width - (curveWidth+1), ClientRectangle.Height - (curveWidth+1), curveWidth, curveWidth, 0, 90);
	gp->AddArc(0, ClientRectangle.Height - (curveWidth+1), curveWidth, curveWidth, 90, 90);
	gp->AddArc(0, 0, curveWidth, curveWidth, 180, 90);
	gp->CloseFigure();
	e->Graphics->FillPath(backBrush, gp);
	System::Drawing::StringFormat^ sf = gcnew System::Drawing::StringFormat();
	sf->Alignment = System::Drawing::StringAlignment::Center;
	sf->LineAlignment = System::Drawing::StringAlignment::Center;
	System::Drawing::Rectangle rect = this->ClientRectangle;
	rect.Y+=voffset;
	rect.Height-=voffset;
	e->Graphics->DrawString(this->Text, this->Font, System::Drawing::Brushes::Black, rect, sf);
	if (this->Focused)
	{
		e->Graphics->DrawPath(System::Drawing::Pens::DarkOrange, gp);
	}
	if (!this->Enabled)
	{
		System::Drawing::Color col = System::Drawing::Color::FromArgb(100, 50,50,50);
		System::Drawing::SolidBrush^ disabledBrush = gcnew System::Drawing::SolidBrush(col);
		e->Graphics->FillPath(disabledBrush, gp);
	}
}
void BAPSButton::OnPaintBackground(System::Windows::Forms::PaintEventArgs^ e)
{
	__super::OnPaintBackground(e);
	int curveWidth = ((this->ClientRectangle.Height>30)?20:this->ClientRectangle.Height/2);
	e->Graphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
	System::Drawing::Drawing2D::GraphicsPath^ gp = gcnew System::Drawing::Drawing2D::GraphicsPath();
	gp->AddArc(ClientRectangle.Width - (curveWidth+1), 0, curveWidth, curveWidth, 270, 90);
	gp->AddArc(ClientRectangle.Width - (curveWidth+1), ClientRectangle.Height - (curveWidth+1), curveWidth, curveWidth, 0, 90);
	gp->AddArc(0, ClientRectangle.Height - (curveWidth+1), curveWidth, curveWidth, 90, 90);
	gp->AddArc(0, 0, curveWidth, curveWidth, 180, 90);
	gp->CloseFigure();
	e->Graphics->DrawPath(System::Drawing::Pens::LightGray, gp);

}
void BAPSButton::HighlightChanged()
{
	if (this->ClientRectangle.Width >0 && this->ClientRectangle.Height>0)
	{
		backBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(this->ClientRectangle, 
								((isHighlighted)?highlightColor:System::Drawing::Color::Tan),
								System::Drawing::Color::Snow,
								System::Drawing::Drawing2D::LinearGradientMode::Vertical );
		backBrush->SetBlendTriangularShape(0.5);
		this->Invalidate();
	}
}
void BAPSButton::OnKeyDown(System::Windows::Forms::KeyEventArgs^ e)
{
	if (e->KeyCode == Keys::Space || e->KeyCode == Keys::Enter)
	{
		__super::OnClick(System::EventArgs::Empty);
		e->Handled = true;
	}
}