namespace VANLOCK_MINI
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.tuyChonToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.chonFileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.congKetNoiToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tcbb_congketnoi = new System.Windows.Forms.ToolStripComboBox();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.button1 = new System.Windows.Forms.Button();
            this.proBar = new System.Windows.Forms.ProgressBar();
            this.tim_send_data = new System.Windows.Forms.Timer(this.components);
            this.serialPort_com = new System.IO.Ports.SerialPort(this.components);
            this.menuStrip1.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tuyChonToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(399, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // tuyChonToolStripMenuItem
            // 
            this.tuyChonToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.chonFileToolStripMenuItem,
            this.congKetNoiToolStripMenuItem});
            this.tuyChonToolStripMenuItem.Name = "tuyChonToolStripMenuItem";
            this.tuyChonToolStripMenuItem.Size = new System.Drawing.Size(71, 20);
            this.tuyChonToolStripMenuItem.Text = "Tuy Chon";
            // 
            // chonFileToolStripMenuItem
            // 
            this.chonFileToolStripMenuItem.Name = "chonFileToolStripMenuItem";
            this.chonFileToolStripMenuItem.Size = new System.Drawing.Size(145, 22);
            this.chonFileToolStripMenuItem.Text = "Chon File.";
            this.chonFileToolStripMenuItem.Click += new System.EventHandler(this.chonFileToolStripMenuItem_Click);
            // 
            // congKetNoiToolStripMenuItem
            // 
            this.congKetNoiToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tcbb_congketnoi});
            this.congKetNoiToolStripMenuItem.Name = "congKetNoiToolStripMenuItem";
            this.congKetNoiToolStripMenuItem.Size = new System.Drawing.Size(145, 22);
            this.congKetNoiToolStripMenuItem.Text = "Cong Ket Noi";
            this.congKetNoiToolStripMenuItem.Click += new System.EventHandler(this.congKetNoiToolStripMenuItem_Click);
            // 
            // tcbb_congketnoi
            // 
            this.tcbb_congketnoi.Name = "tcbb_congketnoi";
            this.tcbb_congketnoi.Size = new System.Drawing.Size(121, 23);
            this.tcbb_congketnoi.TextChanged += new System.EventHandler(this.tcbb_congketnoi_TextChanged);
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.Controls.Add(this.button1, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.proBar, 0, 1);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 24);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(399, 105);
            this.tableLayoutPanel1.TabIndex = 1;
            // 
            // button1
            // 
            this.button1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(192)))));
            this.button1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.button1.Font = new System.Drawing.Font("Times New Roman", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(163)));
            this.button1.Location = new System.Drawing.Point(3, 3);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(393, 79);
            this.button1.TabIndex = 0;
            this.button1.Text = "PROGRAM";
            this.button1.UseVisualStyleBackColor = false;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // proBar
            // 
            this.proBar.Dock = System.Windows.Forms.DockStyle.Fill;
            this.proBar.Location = new System.Drawing.Point(3, 88);
            this.proBar.Name = "proBar";
            this.proBar.Size = new System.Drawing.Size(393, 14);
            this.proBar.TabIndex = 1;
            this.proBar.Value = 100;
            // 
            // tim_send_data
            // 
            this.tim_send_data.Interval = 50;
            this.tim_send_data.Tick += new System.EventHandler(this.tim_send_data_Tick);
            // 
            // serialPort_com
            // 
            this.serialPort_com.PortName = "COM1i";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(399, 129);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.Text = "VANLOCK MINI";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem tuyChonToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem chonFileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem congKetNoiToolStripMenuItem;
        private System.Windows.Forms.ToolStripComboBox tcbb_congketnoi;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ProgressBar proBar;
        private System.Windows.Forms.Timer tim_send_data;
        private System.IO.Ports.SerialPort serialPort_com;
    }
}

