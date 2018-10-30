using OfficeOpenXml;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using Winform;

namespace VANLOCK_MINI
{
    public partial class Form1 : Form
    {
        /// <summary>
        /// Khai bao cac bien su dung
        /// </summary>
        /// 
        string FilePatch;
        string ComPort;
        int Max_Lengh_Gata;
        byte[] ArayDaTaSend;
        public Form1()
        {
            InitializeComponent();
            btn_Test.BackColor = Color.Red;
            btn_Test.Text = "Not connect.";
        }

        /// <summary>
        /// This function will scan all available serial port in computer and show on Comlist
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void congKetNoiToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string[] ComList = SerialPort.GetPortNames();
            tcbb_congketnoi.Items.Clear();
            tcbb_congketnoi.Items.AddRange(ComList);
            
        }
        /// <summary>
        /// Luu Giá trị cổng Com
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tcbb_congketnoi_TextChanged(object sender, EventArgs e)
        {
            ComPort = tcbb_congketnoi.Text;
            serialPort_com.PortName = ComPort;
            try
            {
                serialPort_com.Open();
                btn_Test.BackColor = Color.BlueViolet;
                btn_Test.Text = "TEST";
                panel_genaral.Enabled = true;
                tim_checkconnect.Enabled = true;
            }
            catch
            {
                MessageBox.Show("This port can not connect !!!","Message",MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btn_Test_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort_com.WriteLine("VAT_TEST");
            }
            catch
            {
                ;
            }
        }

        private void btn_Setstep_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort_com.WriteLine("STEP_" + tb_setStep.Text + "#");
            }
            catch
            {
                MessageBox.Show("Can not communication with device.", "Message", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }


        private void btn_SetDelay_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort_com.WriteLine("DELAY_" + tb_setDelay.Text + "#");
            }
            catch
            {
                MessageBox.Show("Can not communication with device.", "Message", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }



        private void tim_checkconnect_Tick(object sender, EventArgs e)
        {
            if (!serialPort_com.IsOpen)
            {
                Application.Exit();
            }
        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!Char.IsDigit(e.KeyChar) && !Char.IsControl(e.KeyChar))
            {
                e.Handled = true;
            }
        }

        private void textBox2_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!Char.IsDigit(e.KeyChar) && !Char.IsControl(e.KeyChar))
            {
                e.Handled = true;
            }
        }

        
    }
}
