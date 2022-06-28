namespace HPS3D160_CSharpDemo
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            this.button_Connect = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.button_disconnect = new System.Windows.Forms.Button();
            this.textBox_host = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.comboBox_ports = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.textBox_port = new System.Windows.Forms.TextBox();
            this.radioButton_Ethernet = new System.Windows.Forms.RadioButton();
            this.radioButton_USB = new System.Windows.Forms.RadioButton();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.button_Single = new System.Windows.Forms.Button();
            this.button_Continuous = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.comboBox_GroupID = new System.Windows.Forms.ComboBox();
            this.comboBox_CameraCode = new System.Windows.Forms.ComboBox();
            this.button_saveSettings = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.comboBox_SmoothFilter = new System.Windows.Forms.ComboBox();
            this.comboBox_OpticalPathCalibration = new System.Windows.Forms.ComboBox();
            this.comboBox_DistanceFilterEnable = new System.Windows.Forms.ComboBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button_setDistanceOffset = new System.Windows.Forms.Button();
            this.button_setSmoothFilter = new System.Windows.Forms.Button();
            this.button_setDistanceFilter = new System.Windows.Forms.Button();
            this.label16 = new System.Windows.Forms.Label();
            this.button_setCameraCode = new System.Windows.Forms.Button();
            this.label13 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.textBox_DistanceOffset = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.textBox_SmoothFilter = new System.Windows.Forms.TextBox();
            this.button_setGroupID = new System.Windows.Forms.Button();
            this.textBox_DitanceFilter = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.button_setUserID = new System.Windows.Forms.Button();
            this.textBox_UserID = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.textBox_roi_num = new System.Windows.Forms.TextBox();
            this.label20 = new System.Windows.Forms.Label();
            this.comboBox_sel_roi = new System.Windows.Forms.ComboBox();
            this.label19 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.label18 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.textBox_group_id = new System.Windows.Forms.TextBox();
            this.textBox_threshold_state = new System.Windows.Forms.TextBox();
            this.textBox_roi_id = new System.Windows.Forms.TextBox();
            this.textBox_dist = new System.Windows.Forms.TextBox();
            this.textBox_minDist = new System.Windows.Forms.TextBox();
            this.label_PackType = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label_dist = new System.Windows.Forms.Label();
            this.textBox_Sat = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label_SDKVer = new System.Windows.Forms.Label();
            this.label_DevVer = new System.Windows.Forms.Label();
            this.label_SN = new System.Windows.Forms.Label();
            this.label_isConnect = new System.Windows.Forms.Label();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.timer_Update = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackColor = System.Drawing.Color.Black;
            this.pictureBox1.Location = new System.Drawing.Point(250, 33);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(480, 240);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(253, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "Image";
            // 
            // button_Connect
            // 
            this.button_Connect.Location = new System.Drawing.Point(15, 154);
            this.button_Connect.Name = "button_Connect";
            this.button_Connect.Size = new System.Drawing.Size(75, 23);
            this.button_Connect.TabIndex = 2;
            this.button_Connect.Text = "Connect";
            this.button_Connect.UseVisualStyleBackColor = true;
            this.button_Connect.Click += new System.EventHandler(this.button_Connect_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.button_disconnect);
            this.groupBox1.Controls.Add(this.textBox_host);
            this.groupBox1.Controls.Add(this.button_Connect);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.comboBox_ports);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.textBox_port);
            this.groupBox1.Controls.Add(this.radioButton_Ethernet);
            this.groupBox1.Controls.Add(this.radioButton_USB);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(228, 191);
            this.groupBox1.TabIndex = 174;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Communication Settings";
            // 
            // button_disconnect
            // 
            this.button_disconnect.Location = new System.Drawing.Point(132, 154);
            this.button_disconnect.Name = "button_disconnect";
            this.button_disconnect.Size = new System.Drawing.Size(75, 23);
            this.button_disconnect.TabIndex = 179;
            this.button_disconnect.Text = "Disconnect";
            this.button_disconnect.UseVisualStyleBackColor = true;
            this.button_disconnect.Click += new System.EventHandler(this.button_disconnect_Click);
            // 
            // textBox_host
            // 
            this.textBox_host.Location = new System.Drawing.Point(41, 82);
            this.textBox_host.Name = "textBox_host";
            this.textBox_host.Size = new System.Drawing.Size(166, 21);
            this.textBox_host.TabIndex = 176;
            this.textBox_host.Text = "192.168.0.10";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3.Location = new System.Drawing.Point(7, 115);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(33, 12);
            this.label3.TabIndex = 177;
            this.label3.Text = "Port";
            // 
            // comboBox_ports
            // 
            this.comboBox_ports.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_ports.Enabled = false;
            this.comboBox_ports.FormattingEnabled = true;
            this.comboBox_ports.Location = new System.Drawing.Point(41, 52);
            this.comboBox_ports.Name = "comboBox_ports";
            this.comboBox_ports.Size = new System.Drawing.Size(166, 20);
            this.comboBox_ports.TabIndex = 174;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4.Location = new System.Drawing.Point(13, 85);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(19, 12);
            this.label4.TabIndex = 175;
            this.label4.Text = "IP";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.Location = new System.Drawing.Point(12, 55);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(26, 12);
            this.label2.TabIndex = 173;
            this.label2.Text = "COM";
            // 
            // textBox_port
            // 
            this.textBox_port.Location = new System.Drawing.Point(41, 112);
            this.textBox_port.Name = "textBox_port";
            this.textBox_port.Size = new System.Drawing.Size(166, 21);
            this.textBox_port.TabIndex = 178;
            this.textBox_port.Text = "12345";
            // 
            // radioButton_Ethernet
            // 
            this.radioButton_Ethernet.AutoSize = true;
            this.radioButton_Ethernet.Checked = true;
            this.radioButton_Ethernet.Location = new System.Drawing.Point(136, 26);
            this.radioButton_Ethernet.Name = "radioButton_Ethernet";
            this.radioButton_Ethernet.Size = new System.Drawing.Size(71, 16);
            this.radioButton_Ethernet.TabIndex = 172;
            this.radioButton_Ethernet.TabStop = true;
            this.radioButton_Ethernet.Text = "Ethernet";
            this.radioButton_Ethernet.UseVisualStyleBackColor = true;
            this.radioButton_Ethernet.CheckedChanged += new System.EventHandler(this.radioButton_Ethernet_CheckedChanged);
            // 
            // radioButton_USB
            // 
            this.radioButton_USB.AutoSize = true;
            this.radioButton_USB.Location = new System.Drawing.Point(27, 26);
            this.radioButton_USB.Name = "radioButton_USB";
            this.radioButton_USB.Size = new System.Drawing.Size(41, 16);
            this.radioButton_USB.TabIndex = 170;
            this.radioButton_USB.Text = "USB";
            this.radioButton_USB.UseVisualStyleBackColor = true;
            this.radioButton_USB.CheckedChanged += new System.EventHandler(this.radioButton_USB_CheckedChanged);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.button_Single);
            this.groupBox2.Controls.Add(this.button_Continuous);
            this.groupBox2.Location = new System.Drawing.Point(12, 209);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(228, 64);
            this.groupBox2.TabIndex = 180;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Capture Mode";
            // 
            // button_Single
            // 
            this.button_Single.Location = new System.Drawing.Point(132, 25);
            this.button_Single.Name = "button_Single";
            this.button_Single.Size = new System.Drawing.Size(75, 23);
            this.button_Single.TabIndex = 1;
            this.button_Single.Text = "Single";
            this.button_Single.UseVisualStyleBackColor = true;
            this.button_Single.Click += new System.EventHandler(this.button_Single_Click);
            // 
            // button_Continuous
            // 
            this.button_Continuous.Location = new System.Drawing.Point(15, 25);
            this.button_Continuous.Name = "button_Continuous";
            this.button_Continuous.Size = new System.Drawing.Size(75, 23);
            this.button_Continuous.TabIndex = 0;
            this.button_Continuous.Text = "Continuous";
            this.button_Continuous.UseVisualStyleBackColor = true;
            this.button_Continuous.Click += new System.EventHandler(this.button_Continuous_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.comboBox_GroupID);
            this.groupBox3.Controls.Add(this.comboBox_CameraCode);
            this.groupBox3.Controls.Add(this.button_saveSettings);
            this.groupBox3.Controls.Add(this.button2);
            this.groupBox3.Controls.Add(this.comboBox_SmoothFilter);
            this.groupBox3.Controls.Add(this.comboBox_OpticalPathCalibration);
            this.groupBox3.Controls.Add(this.comboBox_DistanceFilterEnable);
            this.groupBox3.Controls.Add(this.button1);
            this.groupBox3.Controls.Add(this.button_setDistanceOffset);
            this.groupBox3.Controls.Add(this.button_setSmoothFilter);
            this.groupBox3.Controls.Add(this.button_setDistanceFilter);
            this.groupBox3.Controls.Add(this.label16);
            this.groupBox3.Controls.Add(this.button_setCameraCode);
            this.groupBox3.Controls.Add(this.label13);
            this.groupBox3.Controls.Add(this.label12);
            this.groupBox3.Controls.Add(this.textBox_DistanceOffset);
            this.groupBox3.Controls.Add(this.label7);
            this.groupBox3.Controls.Add(this.textBox_SmoothFilter);
            this.groupBox3.Controls.Add(this.button_setGroupID);
            this.groupBox3.Controls.Add(this.textBox_DitanceFilter);
            this.groupBox3.Controls.Add(this.label6);
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Controls.Add(this.button_setUserID);
            this.groupBox3.Controls.Add(this.textBox_UserID);
            this.groupBox3.Controls.Add(this.label11);
            this.groupBox3.Location = new System.Drawing.Point(12, 279);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(505, 247);
            this.groupBox3.TabIndex = 181;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Advance Settings";
            // 
            // comboBox_GroupID
            // 
            this.comboBox_GroupID.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_GroupID.FormattingEnabled = true;
            this.comboBox_GroupID.Location = new System.Drawing.Point(98, 72);
            this.comboBox_GroupID.Name = "comboBox_GroupID";
            this.comboBox_GroupID.Size = new System.Drawing.Size(102, 20);
            this.comboBox_GroupID.TabIndex = 9;
            // 
            // comboBox_CameraCode
            // 
            this.comboBox_CameraCode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_CameraCode.FormattingEnabled = true;
            this.comboBox_CameraCode.Location = new System.Drawing.Point(98, 47);
            this.comboBox_CameraCode.Name = "comboBox_CameraCode";
            this.comboBox_CameraCode.Size = new System.Drawing.Size(102, 20);
            this.comboBox_CameraCode.TabIndex = 8;
            // 
            // button_saveSettings
            // 
            this.button_saveSettings.Location = new System.Drawing.Point(206, 209);
            this.button_saveSettings.Name = "button_saveSettings";
            this.button_saveSettings.Size = new System.Drawing.Size(292, 23);
            this.button_saveSettings.TabIndex = 7;
            this.button_saveSettings.Text = "SaveSettings";
            this.button_saveSettings.UseVisualStyleBackColor = true;
            this.button_saveSettings.Click += new System.EventHandler(this.button_saveSettings_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(5, 209);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(196, 23);
            this.button2.TabIndex = 1;
            this.button2.Text = "ExportSettings";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button_ExportSettings_Click);
            // 
            // comboBox_SmoothFilter
            // 
            this.comboBox_SmoothFilter.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_SmoothFilter.FormattingEnabled = true;
            this.comboBox_SmoothFilter.Items.AddRange(new object[] {
            "DISABLE",
            "AVERAGE",
            "GAUSS"});
            this.comboBox_SmoothFilter.Location = new System.Drawing.Point(98, 155);
            this.comboBox_SmoothFilter.Name = "comboBox_SmoothFilter";
            this.comboBox_SmoothFilter.Size = new System.Drawing.Size(103, 20);
            this.comboBox_SmoothFilter.TabIndex = 6;
            // 
            // comboBox_OpticalPathCalibration
            // 
            this.comboBox_OpticalPathCalibration.AutoCompleteCustomSource.AddRange(new string[] {
            "true",
            "false"});
            this.comboBox_OpticalPathCalibration.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_OpticalPathCalibration.FormattingEnabled = true;
            this.comboBox_OpticalPathCalibration.Items.AddRange(new object[] {
            "true",
            "false"});
            this.comboBox_OpticalPathCalibration.Location = new System.Drawing.Point(98, 184);
            this.comboBox_OpticalPathCalibration.Name = "comboBox_OpticalPathCalibration";
            this.comboBox_OpticalPathCalibration.Size = new System.Drawing.Size(103, 20);
            this.comboBox_OpticalPathCalibration.TabIndex = 6;
            // 
            // comboBox_DistanceFilterEnable
            // 
            this.comboBox_DistanceFilterEnable.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_DistanceFilterEnable.FormattingEnabled = true;
            this.comboBox_DistanceFilterEnable.Items.AddRange(new object[] {
            "true",
            "false"});
            this.comboBox_DistanceFilterEnable.Location = new System.Drawing.Point(98, 129);
            this.comboBox_DistanceFilterEnable.Name = "comboBox_DistanceFilterEnable";
            this.comboBox_DistanceFilterEnable.Size = new System.Drawing.Size(103, 20);
            this.comboBox_DistanceFilterEnable.TabIndex = 6;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(206, 182);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(293, 23);
            this.button1.TabIndex = 5;
            this.button1.Text = "SetOpticalPathCalibration";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button_SetOpticalPathCalibration);
            // 
            // button_setDistanceOffset
            // 
            this.button_setDistanceOffset.Location = new System.Drawing.Point(206, 97);
            this.button_setDistanceOffset.Name = "button_setDistanceOffset";
            this.button_setDistanceOffset.Size = new System.Drawing.Size(293, 23);
            this.button_setDistanceOffset.TabIndex = 5;
            this.button_setDistanceOffset.Text = "SetDistOffset";
            this.button_setDistanceOffset.UseVisualStyleBackColor = true;
            this.button_setDistanceOffset.Click += new System.EventHandler(this.button_SetDistanceOffset_Click);
            // 
            // button_setSmoothFilter
            // 
            this.button_setSmoothFilter.Location = new System.Drawing.Point(261, 154);
            this.button_setSmoothFilter.Name = "button_setSmoothFilter";
            this.button_setSmoothFilter.Size = new System.Drawing.Size(238, 23);
            this.button_setSmoothFilter.TabIndex = 5;
            this.button_setSmoothFilter.Text = "SetSmoothFilter";
            this.button_setSmoothFilter.UseVisualStyleBackColor = true;
            this.button_setSmoothFilter.Click += new System.EventHandler(this.button_SetSmoothFilter_Click);
            // 
            // button_setDistanceFilter
            // 
            this.button_setDistanceFilter.Location = new System.Drawing.Point(261, 128);
            this.button_setDistanceFilter.Name = "button_setDistanceFilter";
            this.button_setDistanceFilter.Size = new System.Drawing.Size(238, 23);
            this.button_setDistanceFilter.TabIndex = 5;
            this.button_setDistanceFilter.Text = "SetDistanceFilter";
            this.button_setDistanceFilter.UseVisualStyleBackColor = true;
            this.button_setDistanceFilter.Click += new System.EventHandler(this.button_SetDistanceFilter_Click);
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(3, 187);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(89, 12);
            this.label16.TabIndex = 4;
            this.label16.Text = "OpticalPathCal";
            // 
            // button_setCameraCode
            // 
            this.button_setCameraCode.Location = new System.Drawing.Point(206, 46);
            this.button_setCameraCode.Name = "button_setCameraCode";
            this.button_setCameraCode.Size = new System.Drawing.Size(293, 23);
            this.button_setCameraCode.TabIndex = 5;
            this.button_setCameraCode.Text = "SetCameraCode";
            this.button_setCameraCode.UseVisualStyleBackColor = true;
            this.button_setCameraCode.Click += new System.EventHandler(this.button_SetCameraCode_Click);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(3, 102);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(65, 12);
            this.label13.TabIndex = 4;
            this.label13.Text = "DistOffset";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(3, 159);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(77, 12);
            this.label12.TabIndex = 4;
            this.label12.Text = "SmoothFilter";
            // 
            // textBox_DistanceOffset
            // 
            this.textBox_DistanceOffset.Location = new System.Drawing.Point(98, 98);
            this.textBox_DistanceOffset.Name = "textBox_DistanceOffset";
            this.textBox_DistanceOffset.Size = new System.Drawing.Size(103, 21);
            this.textBox_DistanceOffset.TabIndex = 3;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(3, 133);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(89, 12);
            this.label7.TabIndex = 4;
            this.label7.Text = "DistanceFilter";
            // 
            // textBox_SmoothFilter
            // 
            this.textBox_SmoothFilter.Location = new System.Drawing.Point(206, 155);
            this.textBox_SmoothFilter.Name = "textBox_SmoothFilter";
            this.textBox_SmoothFilter.Size = new System.Drawing.Size(51, 21);
            this.textBox_SmoothFilter.TabIndex = 3;
            // 
            // button_setGroupID
            // 
            this.button_setGroupID.Location = new System.Drawing.Point(206, 71);
            this.button_setGroupID.Name = "button_setGroupID";
            this.button_setGroupID.Size = new System.Drawing.Size(293, 23);
            this.button_setGroupID.TabIndex = 5;
            this.button_setGroupID.Text = "SetGroupID";
            this.button_setGroupID.UseVisualStyleBackColor = true;
            this.button_setGroupID.Click += new System.EventHandler(this.button_SetGroupID_Click);
            // 
            // textBox_DitanceFilter
            // 
            this.textBox_DitanceFilter.Location = new System.Drawing.Point(206, 129);
            this.textBox_DitanceFilter.Name = "textBox_DitanceFilter";
            this.textBox_DitanceFilter.Size = new System.Drawing.Size(51, 21);
            this.textBox_DitanceFilter.TabIndex = 3;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(3, 51);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(65, 12);
            this.label6.TabIndex = 4;
            this.label6.Text = "CameraCode";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(3, 76);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(47, 12);
            this.label5.TabIndex = 4;
            this.label5.Text = "GroupID";
            // 
            // button_setUserID
            // 
            this.button_setUserID.Location = new System.Drawing.Point(206, 20);
            this.button_setUserID.Name = "button_setUserID";
            this.button_setUserID.Size = new System.Drawing.Size(293, 23);
            this.button_setUserID.TabIndex = 2;
            this.button_setUserID.Text = "SetUserID";
            this.button_setUserID.UseVisualStyleBackColor = true;
            this.button_setUserID.Click += new System.EventHandler(this.button_SetUserID_Click);
            // 
            // textBox_UserID
            // 
            this.textBox_UserID.Location = new System.Drawing.Point(98, 21);
            this.textBox_UserID.Name = "textBox_UserID";
            this.textBox_UserID.Size = new System.Drawing.Size(103, 21);
            this.textBox_UserID.TabIndex = 1;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(3, 25);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(41, 12);
            this.label11.TabIndex = 0;
            this.label11.Text = "UserID";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.textBox_roi_num);
            this.groupBox4.Controls.Add(this.label20);
            this.groupBox4.Controls.Add(this.comboBox_sel_roi);
            this.groupBox4.Controls.Add(this.label19);
            this.groupBox4.Controls.Add(this.label17);
            this.groupBox4.Controls.Add(this.label18);
            this.groupBox4.Controls.Add(this.label10);
            this.groupBox4.Controls.Add(this.textBox_group_id);
            this.groupBox4.Controls.Add(this.textBox_threshold_state);
            this.groupBox4.Controls.Add(this.textBox_roi_id);
            this.groupBox4.Controls.Add(this.textBox_dist);
            this.groupBox4.Controls.Add(this.textBox_minDist);
            this.groupBox4.Controls.Add(this.label_PackType);
            this.groupBox4.Controls.Add(this.label15);
            this.groupBox4.Controls.Add(this.label_dist);
            this.groupBox4.Controls.Add(this.textBox_Sat);
            this.groupBox4.Controls.Add(this.label8);
            this.groupBox4.Controls.Add(this.label14);
            this.groupBox4.Controls.Add(this.label9);
            this.groupBox4.Location = new System.Drawing.Point(530, 279);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(200, 247);
            this.groupBox4.TabIndex = 182;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Measure Data";
            this.groupBox4.Enter += new System.EventHandler(this.groupBox4_Enter);
            // 
            // textBox_roi_num
            // 
            this.textBox_roi_num.Enabled = false;
            this.textBox_roi_num.Location = new System.Drawing.Point(72, 117);
            this.textBox_roi_num.Name = "textBox_roi_num";
            this.textBox_roi_num.Size = new System.Drawing.Size(86, 21);
            this.textBox_roi_num.TabIndex = 214;
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(9, 121);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(41, 12);
            this.label20.TabIndex = 213;
            this.label20.Text = "RoiNum";
            // 
            // comboBox_sel_roi
            // 
            this.comboBox_sel_roi.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_sel_roi.FormattingEnabled = true;
            this.comboBox_sel_roi.Location = new System.Drawing.Point(72, 143);
            this.comboBox_sel_roi.Name = "comboBox_sel_roi";
            this.comboBox_sel_roi.Size = new System.Drawing.Size(86, 20);
            this.comboBox_sel_roi.TabIndex = 212;
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(9, 224);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(41, 12);
            this.label19.TabIndex = 211;
            this.label19.Text = "Status";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(9, 172);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(47, 12);
            this.label17.TabIndex = 211;
            this.label17.Text = "GroupID";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(9, 198);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(35, 12);
            this.label18.TabIndex = 211;
            this.label18.Text = "RoiID";
            // 
            // label10
            // 
            this.label10.Location = new System.Drawing.Point(9, 147);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(47, 12);
            this.label10.TabIndex = 0;
            this.label10.Text = "SelROI";
            // 
            // textBox_group_id
            // 
            this.textBox_group_id.Enabled = false;
            this.textBox_group_id.Location = new System.Drawing.Point(72, 168);
            this.textBox_group_id.Name = "textBox_group_id";
            this.textBox_group_id.Size = new System.Drawing.Size(86, 21);
            this.textBox_group_id.TabIndex = 210;
            // 
            // textBox_threshold_state
            // 
            this.textBox_threshold_state.Enabled = false;
            this.textBox_threshold_state.Location = new System.Drawing.Point(72, 220);
            this.textBox_threshold_state.Name = "textBox_threshold_state";
            this.textBox_threshold_state.Size = new System.Drawing.Size(86, 21);
            this.textBox_threshold_state.TabIndex = 210;
            // 
            // textBox_roi_id
            // 
            this.textBox_roi_id.Enabled = false;
            this.textBox_roi_id.Location = new System.Drawing.Point(72, 194);
            this.textBox_roi_id.Name = "textBox_roi_id";
            this.textBox_roi_id.Size = new System.Drawing.Size(86, 21);
            this.textBox_roi_id.TabIndex = 210;
            // 
            // textBox_dist
            // 
            this.textBox_dist.Location = new System.Drawing.Point(72, 39);
            this.textBox_dist.Name = "textBox_dist";
            this.textBox_dist.Size = new System.Drawing.Size(86, 21);
            this.textBox_dist.TabIndex = 203;
            this.textBox_dist.Text = "0";
            // 
            // textBox_minDist
            // 
            this.textBox_minDist.Location = new System.Drawing.Point(72, 65);
            this.textBox_minDist.Name = "textBox_minDist";
            this.textBox_minDist.Size = new System.Drawing.Size(86, 21);
            this.textBox_minDist.TabIndex = 208;
            this.textBox_minDist.Text = "0";
            // 
            // label_PackType
            // 
            this.label_PackType.AutoSize = true;
            this.label_PackType.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label_PackType.Location = new System.Drawing.Point(6, 24);
            this.label_PackType.Name = "label_PackType";
            this.label_PackType.Size = new System.Drawing.Size(82, 12);
            this.label_PackType.TabIndex = 209;
            this.label_PackType.Text = "PacketType:";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label15.Location = new System.Drawing.Point(9, 69);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(54, 12);
            this.label15.TabIndex = 206;
            this.label15.Text = "MinDist";
            // 
            // label_dist
            // 
            this.label_dist.AutoSize = true;
            this.label_dist.Location = new System.Drawing.Point(158, 44);
            this.label_dist.Name = "label_dist";
            this.label_dist.Size = new System.Drawing.Size(29, 12);
            this.label_dist.TabIndex = 202;
            this.label_dist.Text = "(mm)";
            // 
            // textBox_Sat
            // 
            this.textBox_Sat.Location = new System.Drawing.Point(72, 91);
            this.textBox_Sat.Name = "textBox_Sat";
            this.textBox_Sat.Size = new System.Drawing.Size(86, 21);
            this.textBox_Sat.TabIndex = 204;
            this.textBox_Sat.Text = "0";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label8.Location = new System.Drawing.Point(9, 95);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(47, 12);
            this.label8.TabIndex = 205;
            this.label8.Text = "SatCnt";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(159, 70);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(29, 12);
            this.label14.TabIndex = 207;
            this.label14.Text = "(mm)";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label9.Location = new System.Drawing.Point(9, 43);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(54, 12);
            this.label9.TabIndex = 201;
            this.label9.Text = "AvgDist";
            // 
            // label_SDKVer
            // 
            this.label_SDKVer.AutoSize = true;
            this.label_SDKVer.Location = new System.Drawing.Point(134, 29);
            this.label_SDKVer.Name = "label_SDKVer";
            this.label_SDKVer.Size = new System.Drawing.Size(53, 12);
            this.label_SDKVer.TabIndex = 183;
            this.label_SDKVer.Text = "SDK Ver:";
            // 
            // label_DevVer
            // 
            this.label_DevVer.AutoSize = true;
            this.label_DevVer.Location = new System.Drawing.Point(323, 29);
            this.label_DevVer.Name = "label_DevVer";
            this.label_DevVer.Size = new System.Drawing.Size(59, 12);
            this.label_DevVer.TabIndex = 184;
            this.label_DevVer.Text = "DEV Ver: ";
            // 
            // label_SN
            // 
            this.label_SN.AutoSize = true;
            this.label_SN.Location = new System.Drawing.Point(527, 29);
            this.label_SN.Name = "label_SN";
            this.label_SN.Size = new System.Drawing.Size(29, 12);
            this.label_SN.TabIndex = 185;
            this.label_SN.Text = "SN: ";
            // 
            // label_isConnect
            // 
            this.label_isConnect.AutoSize = true;
            this.label_isConnect.Location = new System.Drawing.Point(13, 29);
            this.label_isConnect.Name = "label_isConnect";
            this.label_isConnect.Size = new System.Drawing.Size(77, 12);
            this.label_isConnect.TabIndex = 186;
            this.label_isConnect.Text = "disconnected";
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.label_SN);
            this.groupBox5.Controls.Add(this.label_isConnect);
            this.groupBox5.Controls.Add(this.label_DevVer);
            this.groupBox5.Controls.Add(this.label_SDKVer);
            this.groupBox5.Location = new System.Drawing.Point(12, 532);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(718, 54);
            this.groupBox5.TabIndex = 187;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Info";
            // 
            // timer_Update
            // 
            this.timer_Update.Enabled = true;
            this.timer_Update.Tick += new System.EventHandler(this.timer_Update_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(743, 589);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.pictureBox1);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "HPS3D160_SDK CSharpDemo";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button_Connect;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton radioButton_Ethernet;
        private System.Windows.Forms.RadioButton radioButton_USB;
        private System.Windows.Forms.ComboBox comboBox_ports;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button_disconnect;
        private System.Windows.Forms.TextBox textBox_host;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBox_port;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button button_Single;
        private System.Windows.Forms.Button button_Continuous;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Label label_SDKVer;
        private System.Windows.Forms.Label label_DevVer;
        private System.Windows.Forms.Label label_SN;
        private System.Windows.Forms.TextBox textBox_minDist;
        private System.Windows.Forms.TextBox textBox_dist;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label_dist;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox textBox_Sat;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label_PackType;
        private System.Windows.Forms.TextBox textBox_UserID;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Button button_setUserID;
        private System.Windows.Forms.Label label_isConnect;
        private System.Windows.Forms.Button button_setGroupID;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button button_setCameraCode;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button button_setDistanceFilter;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textBox_DitanceFilter;
        private System.Windows.Forms.Button button_setSmoothFilter;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox textBox_SmoothFilter;
        private System.Windows.Forms.Button button_setDistanceOffset;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.TextBox textBox_DistanceOffset;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.ComboBox comboBox_DistanceFilterEnable;
        private System.Windows.Forms.ComboBox comboBox_SmoothFilter;
        private System.Windows.Forms.ComboBox comboBox_OpticalPathCalibration;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Timer timer_Update;
        private System.Windows.Forms.Button button_saveSettings;
        private System.Windows.Forms.TextBox textBox_roi_id;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.ComboBox comboBox_sel_roi;
        private System.Windows.Forms.TextBox textBox_group_id;
        private System.Windows.Forms.TextBox textBox_threshold_state;
        private System.Windows.Forms.ComboBox comboBox_CameraCode;
        private System.Windows.Forms.ComboBox comboBox_GroupID;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.TextBox textBox_roi_num;
    }
}

