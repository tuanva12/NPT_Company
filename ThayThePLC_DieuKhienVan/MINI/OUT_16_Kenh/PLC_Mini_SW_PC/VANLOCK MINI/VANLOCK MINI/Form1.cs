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
        }
        /// <summary>
        /// Chọn file excel để lấy hiệu ứng
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void chonFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog file = new OpenFileDialog();
            //file.Filter = "Excel | *.xlsx | Excel 2003 | *.xls";
            if (file.ShowDialog() == DialogResult.OK)
            {
                FilePatch = file.FileName;
            }
        }
        /// <summary>
        /// Chọn Cổng kết với module
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
        }
        /// <summary>
        /// nạp chương trình cho module
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button1_Click(object sender, EventArgs e)
        {
            button1.Enabled = false;
            proBar.Value = 0;
            try
            {
                serialPort_com.Open();
            }
            catch
            {
                MessageBox.Show("ERROR", "ERR", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                button1.Enabled = true;
            }

            if (serialPort_com.IsOpen)
            {
                try
                {
                    var package = new ExcelPackage(new FileInfo(FilePatch));
                    exportbinfile export = new exportbinfile(package, ComPort);
                    export.actionEff();   // lay du lieu cho vcao mang export.ArayData
                    Max_Lengh_Gata = (export.XSize * export.YSize) + 3;    // 
                    ArayDaTaSend = export.ArayData;
                    if (ArayDaTaSend[0] > 6)
                    {
                        MessageBox.Show("Phần cứng chỉ hỗ trợ 4 Module.", "Lỗi.", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        button1.Enabled = true;
                        serialPort_com.Close();
                    }
                    else
                    {
                        tim_send_data.Enabled = true;// enable timer for send data from PC to MC
                    }
                                     
                }
                catch
                {
                    MessageBox.Show("Không thể đọc được dữ liệu file.", "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    serialPort_com.Close();
                    button1.Enabled = true;
                }

            }



        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        /// 
        int Count = 0;
        private void tim_send_data_Tick(object sender, EventArgs e)
        {
            try
            {
                if (Count < (Max_Lengh_Gata / 32))
                {
                    serialPort_com.Write(ArayDaTaSend, Count * 32, 32);
                    Count++;
                   if(Count < 4) proBar.Value += 20;
                }
                else
                {
                    if ((Max_Lengh_Gata % 32) != 0)
                    {
                        serialPort_com.Write(ArayDaTaSend, (Max_Lengh_Gata / 32) * 32 , Max_Lengh_Gata % 32);
                    }
                    tim_send_data.Enabled = false;
                    serialPort_com.Close();
                    button1.Enabled = true;
                    Count = 0;
                    proBar.Value = 100;
                }
            }
            catch
            {
                MessageBox.Show("Lõi đường truyền !", "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }
    }
}
