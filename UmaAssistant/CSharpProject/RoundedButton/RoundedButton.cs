using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UmaCustomControl
{
    public partial class RoundedButton : Button
    {
        #region Fields
        private float m_Radius = 10;
        #endregion

        #region Properties
        [Browsable(true)] // 讓 Radius 顯示在屬性視窗上
        public float Radius { get { return m_Radius; } set { m_Radius = value; } }
        #endregion

        public RoundedButton()
        {
            InitializeComponent();
        }

        protected override void OnPaint(PaintEventArgs pe)
        {
            base.OnPaint(pe);
            pe.Graphics.SmoothingMode = SmoothingMode.AntiAlias;

            this.SetStyle(ControlStyles.Selectable, false);

            RectangleF Rect = new RectangleF(0, 0, this.Width, this.Height);
            using (GraphicsPath GraphPath = this.m_GetRoundPath(Rect, Radius))
            {
                this.Region = new Region(GraphPath);
                using (Pen pen = new Pen(Color.Empty, 0))
                {
                    pen.Alignment = PenAlignment.Inset;
                    pe.Graphics.DrawPath(pen, GraphPath);
                }
            }
        }

        //private System.Drawing.Drawing2D.GraphicsPath m_GetRoundPath(RectangleF Rect, float radius)
        //{
        //    float r2 = radius / 2f;
        //    System.Drawing.Drawing2D.GraphicsPath GraphPath = new System.Drawing.Drawing2D.GraphicsPath();
        //    GraphPath.AddArc(Rect.X, Rect.Y, radius, radius, 180f, 90f);
        //    GraphPath.AddLine(Rect.X + r2, Rect.Y, Rect.Width - r2, Rect.Y);
        //    GraphPath.AddArc(Rect.X + Rect.Width - radius, Rect.Y, radius, radius, 270f, 90f);
        //    GraphPath.AddLine(Rect.Width, Rect.Y + r2, Rect.Width, Rect.Height - r2);
        //    GraphPath.AddArc(Rect.X + Rect.Width - radius, Rect.Y + Rect.Height - radius, radius, radius, 0f, 90f);
        //    GraphPath.AddLine(Rect.Width - r2, Rect.Height, Rect.X + r2, Rect.Height);
        //    GraphPath.AddArc(Rect.X, Rect.Y + Rect.Height - radius, radius, radius, 90f, 90f);
        //    GraphPath.AddLine(Rect.X, Rect.Height - r2, Rect.X, Rect.Y + r2);
        //    GraphPath.CloseFigure();
        //    return GraphPath;
        //}

        private GraphicsPath m_GetRoundPath(RectangleF Rect, float radius)
        {
            GraphicsPath GraphPath = new GraphicsPath();

            // 上左角弧形
            GraphPath.AddArc(Rect.X, Rect.Y, radius, radius, 180, 90);
            // 上右角弧形
            GraphPath.AddArc(Rect.Width - radius, Rect.Y, radius, radius, 270, 90);
            // 下右角弧形
            GraphPath.AddArc(Rect.Width - radius, Rect.Height - radius, radius, radius, 0, 90);
            // 下左角弧形
            GraphPath.AddArc(Rect.X, Rect.Height - radius, radius, radius, 90, 90);

            GraphPath.CloseFigure();
            return GraphPath;
        }
    }
}
