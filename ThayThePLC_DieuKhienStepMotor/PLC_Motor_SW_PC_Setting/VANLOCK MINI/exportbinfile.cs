using OfficeOpenXml;
using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Winform
{
    public class exportbinfile
    {
        private int xSize;        // chieu X cua mang 2 chieu 
        private int ySize;        // chieu Y cua mang 2 chieu 
        private int maxNumOutPut;  // so luong dau ra 
        private int numStt;         // so luong max hieu ung
        private int numrepeat;      // so lan lap lai hieu ung

        private int Ybegin = 5;     // hang bắt đầu viết hiệu ứng trong file excell
        private int Xbegin = 2;     // cot bắt đầu viết hiệu ứng trong file excell
        //  Ctrl + R + E
        private string ComPort;
        private byte[] arayData = new byte[5000];     

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

        public byte[] ArayData
        {
            get
            {
                return arayData;
            }

            set
            {
                arayData = value;
            }
        }

        public int XSize
        {
            get
            {
                return xSize;
            }

            set
            {
                xSize = value;
            }
        }

        public int YSize
        {
            get
            {
                return ySize;
            }

            set
            {
                ySize = value;
            }
        }

        public exportbinfile(ExcelPackage p,string a)
        {
            this.Cell = p;
            this.ComPort = a;
        }


        /// <summary>
        /// hamf suw dung doc du lieu tu file excell
        /// </summary>
        public void actionEff()
        {
            ExcelWorksheet workSheet = Cell.Workbook.Worksheets[1];
            MaxNumOutPut = int.Parse(workSheet.Cells[1, 2].Value.ToString());   // so kenh cua hieu ung
            Numrepeat = int.Parse(workSheet.Cells[2, 2].Value.ToString());      // so lan lap lai hieu ung
            NumStt = int.Parse(workSheet.Cells[3, 2].Value.ToString());         // chieu dai hieu ung

            if ((maxNumOutPut % 8) == 0)
            {
                XSize = maxNumOutPut / 8 + 2;
            }
            else XSize = maxNumOutPut / 8 + 1 + 2;      // gan gia tri chieu X  ( so byte can cho hieu ung + 2 byte cho thoi gian delay)

            YSize = NumStt;                             // gan gia tri chieu Y



            byte[,] data = new byte[YSize, XSize];    // data luu du lieu hieu ung

            for (int y = 0; y < numStt; y++)    // i la chi so hang trong  ysize
            {
                int[] buff = new int[maxNumOutPut +1];      // mang nay goomf gia tri dau tien la thoi gian delay, cac gia tri sau la trang thai bat tat hiue ung
                // gan chuoi thanh mang int
                for (int x = 0; x <= maxNumOutPut; x++)
                {
                    var value = workSheet.Cells[y + Ybegin, Xbegin +x].Value;
                    if (value != null)
                    {
                        buff[x] = int.Parse(value.ToString());
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
                int point = 2;       // bi tri dau tien cua mang ghi hieu ung, vi 2 vi tri dau la ghi thoi gian delay
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
                    if ((a == 9) && (sizedata< maxNumOutPut))
                    {
                        a = 1;
                        point++;
                        data[y, point] = 0x00;
                    }
                }
            }
            writedata((byte)XSize, (byte)numrepeat, numStt, data);
        }

        private void writedata(byte byteXSize, byte repeat, int efflong, byte[,] data)
        {
            
            
                try
                {
                    arayData[0] = byteXSize;              // write number byte used for save horizontal data
                    arayData[1] = (byte)(efflong >> 8);   // ghi 8 bit cao chieu dai hieu ung
                    arayData[2] = (byte)(efflong);        // ghi 8 bit thap chieu dai hieu ung
                    int count = 3;
                    for (int a = 0; a < efflong; a++)    // vong lap chieu dai hieu ung
                    {
                        for (int b = 0; b < (byteXSize); b++)
                        {
                            arayData[count] = data[a, b];
                            count++;
                        }
                    }
                }
                catch
                {
                    MessageBox.Show("Kiểm tra lại cổng kết nối.", "Lỗi Kết Nối.", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            
        }
    }
}
