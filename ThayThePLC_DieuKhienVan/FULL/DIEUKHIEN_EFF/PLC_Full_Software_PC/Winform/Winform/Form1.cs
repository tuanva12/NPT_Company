using OfficeOpenXml;
using OfficeOpenXml.Style;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Winform
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private void button1_Click(object sender, EventArgs e)
        {
            Form2 f2 = new Form2();
            f2.Show();
        }

        /// <summary>
        /// funtion using convert file effect to file .bin
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btn_convertFile_Click(object sender, EventArgs e)
        {
            string filepath = "";
            OpenFileDialog file = new OpenFileDialog();
            //file.Filter = "Excel | *.xlsx | Excel 2003 | *.xls";
            if (file.ShowDialog() == DialogResult.OK)
            {
                filepath = file.FileName;
            }
            try
            {
                // mở file excel
                var package = new ExcelPackage(new FileInfo(filepath));
                // lấy ra sheet đầu tiên để thao tác

                exportbinfile export = new exportbinfile(package);

                /*read file and export data to bin file*/
                export.actionEff();
                MessageBox.Show("Đã Xuất file hiệu ứng thành công.");

            }
            catch
            {
                MessageBox.Show("Err");
            }
        }
    }
}
