using OfficeOpenXml;
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
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Di chuyen form
        /// </summary>
        int newLocationX;
        int newLocationY;
        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Left)
                return;
            newLocationX = e.X;
            newLocationY = e.Y;
        }

        private void panel1_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Left)
                return;

            Left = Left + (e.X - newLocationX);
            Top = Top + (e.Y - newLocationY);
        }
        /// <summary>
        ///  dong Form
        /// </summary>
        private void btn_huy_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        /// <summary>
        /// Xuat file lap trinh
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btn_OK_Click(object sender, EventArgs e)
        {
            string filePath = "";
            // tạo SaveFileDialog để lưu file excel
            SaveFileDialog dialog = new SaveFileDialog();

            // chỉ lọc ra các file có định dạng Excel
            dialog.Filter = "Excel | *.xlsx | Excel 2003 | *.xls";

            // Nếu mở file và chọn nơi lưu file thành công sẽ lưu đường dẫn lại dùng
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                filePath = dialog.FileName;
            }

            // nếu đường dẫn null hoặc rỗng thì báo không hợp lệ và return hàm
            if (string.IsNullOrEmpty(filePath))
            {
                MessageBox.Show("Đường dẫn báo cáo không hợp lệ");
                return;
            }

            using (ExcelPackage p = new ExcelPackage())
            {
                try
                {
                    costomExcel paint = new costomExcel(p);
                    paint.MaxNumOutPut = int.Parse(tb_sokenh.Text);
                    paint.NumStt = 99;
                    paint.Numrepeat = int.Parse(tb_repeat.Text);
                    paint.paintcell();
                    Byte[] bin = p.GetAsByteArray();
                    File.WriteAllBytes(filePath, bin);
                    MessageBox.Show("OK");
                }
                catch
                {
                    MessageBox.Show("ERR");
                }
            };
            this.Close();
        }
    }
}
