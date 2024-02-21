using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UmaCustomControl
{
    public partial class RoundedButton : Button
    {
        #region Fields
        private int _radius = 10;
        #endregion

        #region Properties
        [Browsable(true)] // 讓 Radius 可在屬性視窗中顯示
        public int Radius { get { return _radius; } set { _radius = value; } }
        #endregion

        public RoundedButton()
        {
            InitializeComponent();
        }

        protected override void OnPaint(PaintEventArgs pe)
        {
            base.OnPaint(pe);

            this.SetStyle(ControlStyles.Selectable, false);

            RectangleF Rect = new RectangleF(0, 0, this.Width, this.Height);
            using (System.Drawing.Drawing2D.GraphicsPath GraphPath = this._GetRoundPath(Rect, Radius))
            {
                this.Region = new Region(GraphPath);
                using (Pen pen = new Pen(Color.Empty, 0))
                {
                    pen.Alignment = System.Drawing.Drawing2D.PenAlignment.Inset;
                    pe.Graphics.DrawPath(pen, GraphPath);
                }
            }
        }

        private System.Drawing.Drawing2D.GraphicsPath _GetRoundPath(RectangleF Rect, int radius)
        {
            float r2 = radius / 2f;
            System.Drawing.Drawing2D.GraphicsPath GraphPath = new System.Drawing.Drawing2D.GraphicsPath();
            GraphPath.AddArc(Rect.X, Rect.Y, radius, radius, 180, 90);
            GraphPath.AddLine(Rect.X + r2, Rect.Y, Rect.Width - r2, Rect.Y);
            GraphPath.AddArc(Rect.X + Rect.Width - radius, Rect.Y, radius, radius, 270, 90);
            GraphPath.AddLine(Rect.Width, Rect.Y + r2, Rect.Width, Rect.Height - r2);
            GraphPath.AddArc(Rect.X + Rect.Width - radius, Rect.Y + Rect.Height - radius, radius, radius, 0, 90);
            GraphPath.AddLine(Rect.Width - r2, Rect.Height, Rect.X + r2, Rect.Height);
            GraphPath.AddArc(Rect.X, Rect.Y + Rect.Height - radius, radius, radius, 90, 90);
            GraphPath.AddLine(Rect.X, Rect.Height - r2, Rect.X, Rect.Y + r2);
            GraphPath.CloseFigure();
            return GraphPath;
        }
    }
}
