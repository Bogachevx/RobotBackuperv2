using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace KawasakiRobotBackuper
{
    public partial class Console : RichTextBox
    {
        public void WriteLine(string s, Color color = default(Color))
        {
            if (color.IsEmpty)
            {
                color = Color.Black;
            }
            AppendText("[" + DateTime.Now.ToString("HH:mm:ss") + "]: " + s + Environment.NewLine, color);
        }

        private void AppendText(string s, Color color)
        {
            SuspendLayout();
            SelectionColor = color;
            AppendText(s);
            ScrollToCaret();
            ResumeLayout();
        }

        public Console()
        {
            InitializeComponent();
        }
    }
}
