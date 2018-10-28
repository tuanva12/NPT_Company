using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OfficeOpenXml;
using OfficeOpenXml.Style;
using System.Windows.Forms;
using System.IO;

namespace Winform
{
    public class costomExcel
    {
        private int maxNumOutPut;   // so luong dau ra 
        private int numStt;         // so luong max hieu ung
        private int numrepeat;
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

        public costomExcel(ExcelPackage p)
        {
            this.Cell = p;
        }

        public void paintcell()
        {
            // đặt tên người tạo file
            Cell.Workbook.Properties.Author = "ATV";
            // đặt tiêu đề cho file
            Cell.Workbook.Properties.Title = "EFF";

            //Tạo một sheet để làm việc trên đó
            Cell.Workbook.Worksheets.Add("NPT");

            // lấy sheet vừa add ra để thao tác
            ExcelWorksheet sheets = Cell.Workbook.Worksheets[1];
            sheets.View.FreezePanes(5,3);   // đóng băng để hiển thị 
            // đặt tên cho sheet
            sheets.Name = "Main Program";
            // fontsize mặc định cho cả sheet
            sheets.Cells.Style.Font.Size = 11;
            // font family mặc định cho cả sheet
            sheets.Cells.Style.Font.Name = "Times New Roman";

            // bang thong so tong quan
            sheets.Cells[1, 1, 3 , 3].Style.HorizontalAlignment = ExcelHorizontalAlignment.Center;   // can giua
            // đổi màu cho header
            sheets.Cells[1, 1, 3, 3].Style.Fill.PatternType = ExcelFillStyle.LightDown;
            sheets.Cells[1, 1, 3, 3].Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.Cyan);
            
            //////////////////    So kenh
            var X = sheets.Cells[1, 1];
            X.Value = "So Kenh";
            X.Style.Border.Left.Style =
            X.Style.Border.Right.Style =
            X.Style.Border.Top.Style =
            X.Style.Border.Bottom.Style = ExcelBorderStyle.Thick;

            var XX = sheets.Cells[1, 2];
            XX.Value = maxNumOutPut.ToString();
            XX.Style.Border.Left.Style =
            XX.Style.Border.Right.Style =
            XX.Style.Border.Top.Style =
            XX.Style.Border.Bottom.Style = ExcelBorderStyle.Thick;

            /////////////////////// So lan lap hieu ung
            var y = sheets.Cells[2, 1];
            y.Value = "REPEAT";
            y.Style.Border.Left.Style =
            y.Style.Border.Right.Style =
            y.Style.Border.Top.Style =
            y.Style.Border.Bottom.Style = ExcelBorderStyle.Thick;

            var YY = sheets.Cells[2, 2];
            YY.Value = numrepeat.ToString();
            YY.Style.Border.Left.Style =
            YY.Style.Border.Right.Style =
            YY.Style.Border.Top.Style =
            YY.Style.Border.Bottom.Style = ExcelBorderStyle.Thick;

            /////////////////////// Chieu dai hieu ung
            var Z = sheets.Cells[3, 1];
            Z.Value = "MAX";
            Z.Style.Border.Left.Style =
            Z.Style.Border.Right.Style =
            Z.Style.Border.Top.Style =
            Z.Style.Border.Bottom.Style = ExcelBorderStyle.Thick;

            var ZZ = sheets.Cells[3, 2];
            ZZ.Value = numStt.ToString();
            ZZ.Style.Border.Left.Style =
            ZZ.Style.Border.Right.Style =
            ZZ.Style.Border.Top.Style =
            ZZ.Style.Border.Bottom.Style = ExcelBorderStyle.Thick;



            // tieu de

            var title = sheets.Cells[1, 3, 3, maxNumOutPut +2];      // O viet tieu de
            // merge các column lại từ column 1 đến số column header
            // gán giá trị cho cell vừa merge là Thống kê thông tni User Kteam
            title.Value = "Bảng Thiết Kế Hiệu Ứng";
            title.Merge = true;
            title.Style.Border.Left.Style =
            title.Style.Border.Right.Style =
            title.Style.Border.Top.Style =
            title.Style.Border.Bottom.Style = ExcelBorderStyle.Thick;
            // in đậm
            title.Style.Font.Bold = true;
            // căn giữa
            title.Style.HorizontalAlignment = ExcelHorizontalAlignment.Left;
            // đổi màu cho header
            title.Style.Fill.PatternType = ExcelFillStyle.Solid;
            title.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.SeaGreen);
            title.Style.Font.Color.SetColor(System.Drawing.Color.Yellow);// doi mau chu viet
            title.Style.Font.Size = 30;  // thay doi size cua chu viet



            // tao hàng so kenh
            for (int a = 0; a <= maxNumOutPut; a++)
            {
                var x = sheets.Cells[4, a + 2];
                if (a != 0)
                {
                    x.Value = "Kenh " + (a).ToString();
                    x.Style.Fill.PatternType = ExcelFillStyle.Solid;        // doi mau nen
                    x.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.DarkSlateBlue);   // noi mau nen
                }
                else
                {
                    x.Value = "Delay";
                    x.Style.Fill.PatternType = ExcelFillStyle.Solid;        // doi mau nen
                    x.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.Aquamarine);   // noi mau nen
                }
                x.Style.HorizontalAlignment = ExcelHorizontalAlignment.Center;    // can giua
                
                // ve khung
                x.Style.Border.Left.Style =
                x.Style.Border.Right.Style =
                x.Style.Border.Top.Style =
                x.Style.Border.Bottom.Style = ExcelBorderStyle.Thin;
            }

            // Danh STT
           
            for (int a = 0; a <= numStt; a++)
            {
                var x = sheets.Cells[4 + a,1];
                if (a == 0)
                {
                    x.Value = "STT";
                    x.Style.HorizontalAlignment = ExcelHorizontalAlignment.Center;    // can giua
                    x.Style.Fill.PatternType = ExcelFillStyle.Solid;        // doi mau nen
                    x.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.Aqua);   // noi mau nen
                                                                                        // ve khung
                    x.Style.Border.Left.Style =
                    x.Style.Border.Top.Style =
                    x.Style.Border.Bottom.Style = ExcelBorderStyle.Thin;
                    x.Style.Border.Right.Style = ExcelBorderStyle.Thick;
                }
                else
                {
                    x.Value = a.ToString();
                    x.Style.HorizontalAlignment = ExcelHorizontalAlignment.Center;    // can giua
                    x.Style.Fill.PatternType = ExcelFillStyle.Solid;        // doi mau nen
                    x.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.Aqua);   // noi mau nen
                                                                                        // ve khung
                    x.Style.Border.Left.Style =
                    x.Style.Border.Top.Style =
                    x.Style.Border.Bottom.Style = ExcelBorderStyle.Thin;
                    x.Style.Border.Right.Style = ExcelBorderStyle.Thin;
                    // ve body cho cot delay
                    x = sheets.Cells[4 + a, 2];
                    x.Style.HorizontalAlignment = ExcelHorizontalAlignment.Center;    // can giua
                    x.Style.Fill.PatternType = ExcelFillStyle.Solid;        // doi mau nen
                    x.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.Aquamarine);   // noi mau nen
                    // ve khung
                    x.Style.Border.Left.Style =
                    x.Style.Border.Top.Style =
                    x.Style.Border.Bottom.Style = ExcelBorderStyle.Thin;
                    x.Style.Border.Right.Style = ExcelBorderStyle.Thick;
                }
            }
        }
    }
}
