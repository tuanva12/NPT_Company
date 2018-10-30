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
            this.congKetNoiToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tcbb_congketnoi = new System.Windows.Forms.ToolStripComboBox();
            this.panel_genaral = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.tb_setStep = new System.Windows.Forms.TextBox();
            this.tb_setDelay = new System.Windows.Forms.TextBox();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.btn_Setstep = new System.Windows.Forms.Button();
            this.btn_SetDelay = new System.Windows.Forms.Button();
            this.btn_Test = new System.Windows.Forms.Button();
            this.serialPort_com = new System.IO.Ports.SerialPort(this.components);
            this.tim_checkconnect = new System.Windows.Forms.Timer(this.components);
            this.menuStrip1.SuspendLayout();
            this.panel_genaral.SuspendLayout();
            this.tableLayoutPanel3.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tuyChonToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(637, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // tuyChonToolStripMenuItem
            // 
            this.tuyChonToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.congKetNoiToolStripMenuItem});
            this.tuyChonToolStripMenuItem.Name = "tuyChonToolStripMenuItem";
            this.tuyChonToolStripMenuItem.Size = new System.Drawing.Size(71, 20);
            this.tuyChonToolStripMenuItem.Text = "Tuy Chon";
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
            // panel_genaral
            // 
            this.panel_genaral.ColumnCount = 1;
            this.panel_genaral.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.panel_genaral.Controls.Add(this.tableLayoutPanel3, 0, 0);
            this.panel_genaral.Controls.Add(this.tableLayoutPanel2, 0, 1);
            this.panel_genaral.Controls.Add(this.btn_Test, 0, 2);
            this.panel_genaral.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel_genaral.Enabled = false;
            this.panel_genaral.Location = new System.Drawing.Point(0, 24);
            this.panel_genaral.Name = "panel_genaral";
            this.panel_genaral.RowCount = 3;
            this.panel_genaral.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 83.33334F));
            this.panel_genaral.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 45F));
            this.panel_genaral.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.panel_genaral.Size = new System.Drawing.Size(637, 215);
            this.panel_genaral.TabIndex = 1;
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.ColumnCount = 2;
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.Controls.Add(this.tb_setStep, 0, 0);
            this.tableLayoutPanel3.Controls.Add(this.tb_setDelay, 1, 0);
            this.tableLayoutPanel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel3.Location = new System.Drawing.Point(3, 3);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.RowCount = 1;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 135F));
            this.tableLayoutPanel3.Size = new System.Drawing.Size(631, 135);
            this.tableLayoutPanel3.TabIndex = 1;
            // 
            // tb_setStep
            // 
            this.tb_setStep.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tb_setStep.Font = new System.Drawing.Font("Microsoft Sans Serif", 72F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tb_setStep.Location = new System.Drawing.Point(3, 3);
            this.tb_setStep.Multiline = true;
            this.tb_setStep.Name = "tb_setStep";
            this.tb_setStep.Size = new System.Drawing.Size(309, 129);
            this.tb_setStep.TabIndex = 0;
            this.tb_setStep.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox1_KeyPress);
            // 
            // tb_setDelay
            // 
            this.tb_setDelay.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_setDelay.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tb_setDelay.Font = new System.Drawing.Font("Microsoft Sans Serif", 72F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tb_setDelay.Location = new System.Drawing.Point(318, 3);
            this.tb_setDelay.Multiline = true;
            this.tb_setDelay.Name = "tb_setDelay";
            this.tb_setDelay.Size = new System.Drawing.Size(310, 129);
            this.tb_setDelay.TabIndex = 1;
            this.tb_setDelay.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox2_KeyPress);
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 2;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.Controls.Add(this.btn_Setstep, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.btn_SetDelay, 1, 0);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(3, 144);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 1;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 39F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(631, 39);
            this.tableLayoutPanel2.TabIndex = 0;
            // 
            // btn_Setstep
            // 
            this.btn_Setstep.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btn_Setstep.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_Setstep.ForeColor = System.Drawing.Color.Blue;
            this.btn_Setstep.Location = new System.Drawing.Point(3, 3);
            this.btn_Setstep.Name = "btn_Setstep";
            this.btn_Setstep.Size = new System.Drawing.Size(309, 33);
            this.btn_Setstep.TabIndex = 0;
            this.btn_Setstep.Text = "SET STEP";
            this.btn_Setstep.UseVisualStyleBackColor = true;
            this.btn_Setstep.Click += new System.EventHandler(this.btn_Setstep_Click);
            // 
            // btn_SetDelay
            // 
            this.btn_SetDelay.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btn_SetDelay.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_SetDelay.ForeColor = System.Drawing.Color.Blue;
            this.btn_SetDelay.Location = new System.Drawing.Point(318, 3);
            this.btn_SetDelay.Name = "btn_SetDelay";
            this.btn_SetDelay.Size = new System.Drawing.Size(310, 33);
            this.btn_SetDelay.TabIndex = 1;
            this.btn_SetDelay.Text = "SET TIME DELAY";
            this.btn_SetDelay.UseVisualStyleBackColor = true;
            this.btn_SetDelay.Click += new System.EventHandler(this.btn_SetDelay_Click);
            // 
            // btn_Test
            // 
            this.btn_Test.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btn_Test.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_Test.Location = new System.Drawing.Point(3, 189);
            this.btn_Test.Name = "btn_Test";
            this.btn_Test.Size = new System.Drawing.Size(631, 23);
            this.btn_Test.TabIndex = 2;
            this.btn_Test.Text = "TEST";
            this.btn_Test.UseVisualStyleBackColor = true;
            this.btn_Test.Click += new System.EventHandler(this.btn_Test_Click);
            // 
            // serialPort_com
            // 
            this.serialPort_com.PortName = "COM1i";
            // 
            // tim_checkconnect
            // 
            this.tim_checkconnect.Tick += new System.EventHandler(this.tim_checkconnect_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(637, 239);
            this.Controls.Add(this.panel_genaral);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.Text = "Stepmotor Setting (V1.0)";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.panel_genaral.ResumeLayout(false);
            this.tableLayoutPanel3.ResumeLayout(false);
            this.tableLayoutPanel3.PerformLayout();
            this.tableLayoutPanel2.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem tuyChonToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem congKetNoiToolStripMenuItem;
        private System.Windows.Forms.ToolStripComboBox tcbb_congketnoi;
        private System.Windows.Forms.TableLayoutPanel panel_genaral;
        private System.IO.Ports.SerialPort serialPort_com;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.Button btn_Setstep;
        private System.Windows.Forms.Button btn_SetDelay;
        private System.Windows.Forms.Button btn_Test;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
        private System.Windows.Forms.TextBox tb_setStep;
        private System.Windows.Forms.TextBox tb_setDelay;
        private System.Windows.Forms.Timer tim_checkconnect;
    }
}

