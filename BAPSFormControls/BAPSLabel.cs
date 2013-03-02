using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace BAPSFormControls
{
    public partial class BAPSLabel : Control
    {
        public BAPSLabel()
        {
            InitializeComponent();
            this.SetStyle((System.Windows.Forms.ControlStyles)
                           (System.Windows.Forms.ControlStyles.UserPaint |
                           System.Windows.Forms.ControlStyles.OptimizedDoubleBuffer),
                           true);
            infoText = "ddd";
            this.TabStop = false;
            highlightColor = System.Drawing.Color.Red;
            isHighlighted = false;
            backBrush = new System.Drawing.Drawing2D.LinearGradientBrush(new System.Drawing.Rectangle(0, 0, 10, 10), System.Drawing.Color.Tan, System.Drawing.Color.Snow, System.Drawing.Drawing2D.LinearGradientMode.Vertical);
            offScreen = new System.Drawing.Bitmap(1, 1);
        }
        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            e.Graphics.DrawImage(offScreen, 1, 1);
            System.Drawing.StringFormat sf = new System.Drawing.StringFormat();
            sf.Alignment = System.Drawing.StringAlignment.Center;
            sf.LineAlignment = System.Drawing.StringAlignment.Center;
            System.Drawing.Rectangle rect = this.ClientRectangle;
            if (System.String.Compare(infoText, "") != 0)
            {
                System.Drawing.Font font = new System.Drawing.Font(this.Font.FontFamily, 8, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
                e.Graphics.DrawString(infoText, font, new System.Drawing.SolidBrush(ForeColor), (float)5.0, (float)1.0);
                // have info text to display
                rect.Y += 12;
                rect.Height -= 12;
            }

            e.Graphics.DrawString(this.Text, this.Font, new System.Drawing.SolidBrush(ForeColor), rect, sf);

        }
        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
	        backBrush = new System.Drawing.Drawing2D.LinearGradientBrush(this.ClientRectangle,
							        ((isHighlighted)?highlightColor:System.Drawing.Color.Snow),
							        System.Drawing.Color.AntiqueWhite,
							        System.Drawing.Drawing2D.LinearGradientMode.Vertical );
	        backBrush.SetBlendTriangularShape((float)0.5);
	        offScreen = new System.Drawing.Bitmap(this.ClientSize.Width - 1, this.ClientSize.Height - 2);
	        prepareGraphics();
        }
        void prepareGraphics()
        {
            if (this.ClientRectangle.Width > 0 && this.ClientRectangle.Height > 0)
            {
                System.Drawing.Graphics gOffScreen = System.Drawing.Graphics.FromImage(offScreen);

                int curveWidth = ((this.ClientRectangle.Height > 30) ? 20 : this.ClientRectangle.Height / 2);
                gOffScreen.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
                System.Drawing.Drawing2D.GraphicsPath gp = new System.Drawing.Drawing2D.GraphicsPath();
                gp.AddArc(ClientRectangle.Width - (curveWidth + 1), 0, curveWidth, curveWidth, 270, 90);
                gp.AddArc(ClientRectangle.Width - (curveWidth + 1), ClientRectangle.Height - (curveWidth + 1), curveWidth, curveWidth, 0, 90);
                gp.AddArc(0, ClientRectangle.Height - (curveWidth + 1), curveWidth, curveWidth, 90, 90);
                gp.AddArc(0, 0, curveWidth, curveWidth, 180, 90);
                gp.CloseFigure();
                gOffScreen.FillPath(backBrush, gp);
                gOffScreen.DrawPath(System.Drawing.Pens.LightGray, gp);
            }
        }

        System.Drawing.Drawing2D.LinearGradientBrush backBrush;
        System.String infoText;
        bool isHighlighted;
        System.Drawing.Color highlightColor;
        System.Drawing.Bitmap offScreen;
    }
}
