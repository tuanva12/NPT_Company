using OfficeOpenXml;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Winform
{
    public class exportbinfile
    {
        private int xSize;        // chieu X cua mang 2 chieu , la chieu rong cua mang
        private int ySize;        // chieu Y cua mang 2 chieu , la chieu cao cua mang
        private int maxNumOutPut;  // so luong dau ra
        private int numStt;         // so luong max hieu ung
        private int numrepeat;      // so lan lap lai hieu ung

        private int Ybegin = 5;     // hang bắt đầu viết hiệu ứng
        private int Xbegin = 3;     // cot bắt đầu viết hiệu ứng


        private ExcelPackage cell = new ExcelPackage();
        public ExcelPackage Cell
        {
            get
            {
                return cell;
            }

            set
            {
                cell = value;
            }
        }
        public int MaxNumOutPut
        {
            get
            {
                return maxNumOutPut;
            }

            set
            {
                maxNumOutPut = value;
            }
        }

        public int NumStt
        {
            get
            {
                return numStt;
            }

            set
            {
                numStt = value;
            }
        }

        public int Numrepeat
        {
            get
            {
                return numrepeat;
            }

            set
            {
                numrepeat = value;
            }
        }
        public exportbinfile(ExcelPackage p)
        {
            this.Cell = p;
        }

        public void actionEff()
        {
            ExcelWorksheet workSheet = Cell.Workbook.Worksheets[1];  // open worksheet of file excel for read data

            MaxNumOutPut = int.Parse(workSheet.Cells[1, 2].Value.ToString());   // so kenh cua hieu ung
            Numrepeat = int.Parse(workSheet.Cells[2, 2].Value.ToString());      // so lan lap lai hieu ung
            NumStt = int.Parse(workSheet.Cells[3, 2].Value.ToString());         // chieu dai hieu ung

            if ((maxNumOutPut % 8) == 0)
            {
                xSize = maxNumOutPut / 8 + 2;
            }
            else xSize = maxNumOutPut / 8 + 1 + 2;      // gan gia tri chieu X  ( so byte can cho hieu ung + 2 byte cho thoi gian delay)

            ySize = NumStt;                        // gan gia tri chieu Y

            byte[,] data = new byte[ySize, xSize];    // Mang nay se luu du lieu chay va ghi vao memory card



            int Y_Count = 0;                   // Bien Y_Count su dung de lay data trong file
            int Y_StartGr = 0;
            int Sub_Repeat = 1;                // Bien su dung de luu tru so lan lap lai
            string Current_Groupt = "A";
            string Current_Groupt_name;

            for (int y = 0; y < ySize; y++)    // y la chi so hang trong  ysize, y chay tu hang dau tien bat dau hieu ung den cuoi cung cua hang
            {
                int[] buff = new int[maxNumOutPut +1];
                Current_Groupt_name = workSheet.Cells[Y_Count + Ybegin,1].Value.ToString();
                if((Current_Groupt_name != Current_Groupt) || (Current_Groupt_name == "#"))
                {
                    if(int.Parse(workSheet.Cells[Y_Count + Ybegin - 1,2].Value.ToString()) != Sub_Repeat)  // Neu chua lap du so lan
                    {
                        Sub_Repeat ++;
                        Y_Count = Y_StartGr;
                    }
                    else // Neu da lap du so lan roi thi chuyen sang nhom moi, gan laij vi tri bat dau cho nhom moi,
                    {
                        Y_StartGr = Y_Count;                    // gan laij vi tri bat dau cho nhom moi,
                        Current_Groupt = Current_Groupt_name;    // Gan lai ten cho ten cho group moi
                        Sub_Repeat = 1;
                    }
                }

                // gan chuoi thanh mang int
                for (int x = 0; x <= maxNumOutPut; x++)
                {
                    var value = workSheet.Cells[Y_Count + Ybegin, Xbegin +x].Value;
                    if (value != null)
                    {
                        if (x != 0)
                        {
                            if (int.Parse(value.ToString()) == 1)
                            {
                                buff[x] = 1;
                            }
                        }
                        else
                        {
                            try
                            {
                                buff[x] = int.Parse(value.ToString());
                            }
                            catch
                            {
                                MessageBox.Show(String.Format("Kiểm tra lại dòng thứ {0}!!!", Y_Count), "Lỗi", MessageBoxButtons.OK);
                                buff[x] = int.Parse(value.ToString());
                               
                            }
                        }
                    }
                    else
                    {
                        buff[x] = 0;
                    }
                }
                // ghi 2 byte gia tri delay vao 2 vi tri dau tien cua mang 2 chieu
                data[y, 0] = (byte)(buff[0] >> 8);
                data[y, 1] = (byte)(buff[0]);

               // ghi byte hieu ung.
                int a = 1;
                int point = 2;
                data[y, point] = 0x00;
                for (int sizedata = 1; sizedata <= maxNumOutPut ; sizedata++)    // vong lap so byte su dung de luu data
                {
                    if (buff[sizedata] == 1)
                    {
                        switch (a)
                        {
                            case 1:
                                data[y, point] |= 0x80;
                                break;
                            case 2:
                                data[y, point] |= 0x40;
                                break;
                            case 3:
                                data[y, point] |= 0x20;
                                break;
                            case 4:
                                data[y, point] |= 0x10;
                                break;
                            case 5:
                                data[y, point] |= 0x08;
                                break;
                            case 6:
                                data[y, point] |= 0x04;
                                break;
                            case 7:
                                data[y, point] |= 0x02;
                                break;
                            case 8:
                                data[y, point] |= 0x01;
                                break;
                        }
                    }
                    a++;
                    if((a == 9) && (sizedata < maxNumOutPut))
                    {
                        a = 1;
                        point++;
                        data[y, point] = 0x00;
                    }
                }
                Y_Count ++;
            }
            /*write data to .bin file*/
            writedata((byte)xSize,(byte)numrepeat, ySize, data);
        }
        /// <summary>
        /// Ghi du lieu vao file lan luot theo thu tu:
        /// 1 Byte do rong cua mang 2 chieu, byte nay cho biet co bao nhieu byte su dung de luu du lieu cua hieu ung trong mot lan xuat hieu ung cho cac kenh, vi du dang xay dung hieu ung cho 24 kenh, thi can 3 byte de luu data, 2 byte de luu thoi gian delay suyra byte can ghi nay co gia tri = 5
        /// 1 Byte so lan lap lai cua hieu ung
        /// 2 byte ghi chieu dai cua hieu ung la bao nhieu
        /// Ghi data theo thu tu tu trai qua phai va tu tren xuong duoi
        /// </summary>
        /// <param name="X_Size"></param>
        /// <param name="repeat"></param>
        /// <param name="efflong"></param>
        /// <param name="data"></param>

        private void writedata(byte X_Size, byte repeat, int efflong, byte[,] data)
        {
            string filepath = "";
            SaveFileDialog file = new SaveFileDialog();
            file.Filter = "Bin files (*.BIN)|*.BIN";
            if (file.ShowDialog() == DialogResult.OK)
            {
                filepath = file.FileName;
            }
           // try
           // {
                using (FileStream stream = new FileStream(filepath, FileMode.Create))
                {
                    using (BinaryWriter writer = new BinaryWriter(stream))
                    {
                        writer.Write(X_Size);  // write 8 bit hight of int number chanel
                        writer.Write(repeat);  // ghi so lan lap lai hieu ung
                        writer.Write((byte)(efflong>>8)); // ghi chieu dai hieu ung
                        writer.Write((byte)efflong);      // ghi chieu dai hieu ung
                        for (int a = 0; a < efflong; a++)    // vong lap chieu dai hieu ung
                        {
                            for (int b = 0 ; b < X_Size; b++)
                            {
                                writer.Write(data[a,b]);
                            }
                        }
                        writer.Close();
                    }
                }
              //  MessageBox.Show("Ok");
           // }
           // catch
          //  {
          //      MessageBox.Show("Err");
           // }
        }
    }
}
