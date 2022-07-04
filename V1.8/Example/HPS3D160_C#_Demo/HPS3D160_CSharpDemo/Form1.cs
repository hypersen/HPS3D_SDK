using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO.Ports;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace HPS3D160_CSharpDemo
{
    public partial class Form1 : Form
    {
        private int handle;
        HPS3D_MeasureData_t resultData;
        delegate void updateUIHandler(object[] args);
        UserEventCallbackHandleDelegate eventFunc;
        private static Bitmap DistanceBitmap = ToGrayBitmap(new byte[HPS3D160_Device.MAX_PIXEL_NUMBER], HPS3D160_Device.MAX_WIDTH, HPS3D160_Device.MAX_HEIGHT);

        public Form1()
        {
            InitializeComponent();
        }

        /// <summary>
        /// 将一个字节数组转换为8bit灰度位图
        /// </summary>
        /// <param name="rawValues">显示字节数组</param>
        /// <param name="width">图像宽度</param>
        /// <param name="height">图像高度</param>
        /// <returns>位图</returns>
        public static Bitmap ToGrayBitmap(byte[] rawValues, int width, int height)
        {
            //// 申请目标位图的变量，并将其内存区域锁定
            Bitmap bmp = new Bitmap(width, height, PixelFormat.Format8bppIndexed);
            BitmapData bmpData = bmp.LockBits(new Rectangle(0, 0, width, height),
                ImageLockMode.WriteOnly, PixelFormat.Format8bppIndexed);

            //// 获取图像参数
            int stride = bmpData.Stride;  // 扫描线的宽度
            int offset = stride - width;  // 显示宽度与扫描线宽度的间隙
            IntPtr iptr = bmpData.Scan0;  // 获取bmpData的内存起始位置
            int scanBytes = stride * height;   // 用stride宽度，表示这是内存区域的大小
            //// 下面把原始的显示大小字节数组转换为内存中实际存放的字节数组
            int posScan = 0, posReal = 0;   // 分别设置两个位置指针，指向源数组和目标数组
            byte[] pixelValues = new byte[scanBytes];  //为目标数组分配内存
            for (int x = 0; x < height; x++)
            {
                //// 下面的循环节是模拟行扫描
                for (int y = 0; y < width; y++)
                {
                    pixelValues[posScan++] = (byte)(rawValues[posReal++] & 0xFF);
                }
                posScan += offset;  //行扫描结束，要将目标位置指针移过那段“间隙”
            }

            //// 用Marshal的Copy方法，将刚才得到的内存字节数组复制到BitmapData中
            System.Runtime.InteropServices.Marshal.Copy(pixelValues, 0, iptr, scanBytes);
            bmp.UnlockBits(bmpData);  // 解锁内存区域

            //// 下面的代码是为了修改生成位图的索引表，从伪彩修改为灰度
            ColorPalette tempPalette;
            using (Bitmap tempBmp = new Bitmap(1, 1, PixelFormat.Format8bppIndexed))
            {
                tempPalette = tempBmp.Palette;
            }
            for (int i = 0; i < 256; i++)
            {
                tempPalette.Entries[i] = Color.FromArgb(i, i, i);
            }

            bmp.Palette = tempPalette;

            //// 算法到此结束，返回结果
            return bmp;
        }



        private void radioButton_Ethernet_CheckedChanged(object sender, EventArgs e)
        {
            comboBox_ports.Enabled = false;
            textBox_host.Enabled = true;
            textBox_port.Enabled = true;
        }

        private void radioButton_USB_CheckedChanged(object sender, EventArgs e)
        {
            string[] ports = SerialPort.GetPortNames();
            comboBox_ports.Items.Clear();
            foreach (string port in ports)
            {
                comboBox_ports.Items.Add(port);
            }
            comboBox_ports.Enabled = true;
            textBox_host.Enabled = false;
            textBox_port.Enabled = false;
        }

        private void button_SetUserID_Click(object sender, EventArgs e)
        {
            if (!HPS3D160_Device.HPS3D_IsConnect(handle))
            {
                MessageBox.Show("Device not connected!");
                return;
            }
            int UserID= Convert.ToInt32(textBox_UserID.Text);
            if (UserID < 0 || UserID > 255)
            {
                return;
            }
            HPS3D_StatusTypeDef ret = HPS3D_StatusTypeDef.HPS3D_RET_OK;
            ret = HPS3D160_Device.HPS3D_SetDeviceUserID(handle, Convert.ToByte(textBox_UserID.Text));
            if (ret != HPS3D_StatusTypeDef.HPS3D_RET_OK)
            {
                MessageBox.Show("SetDeviceUserID ERR:" + ret);
                return;
            }
        }

        /// <summary>
        /// 更新UI控件
        /// </summary>
        /// <param name="args"></param>
        void updateUI(object[] args)
        {
            HPS3D_EventType_t e = (HPS3D_EventType_t)args[0];
            HPS3D_MeasureData_t data = new HPS3D_MeasureData_t();
            switch (e)
            {
                case HPS3D_EventType_t.HPS3D_SIMPLE_ROI_EVEN:
                    data = (HPS3D_MeasureData_t)args[1];
                    label_PackType.Text = "PacketType: SIMPLE_ROI";
                    textBox_dist.Text = data.simple_roi_data[0].distance_average.ToString();
                    textBox_minDist.Text = data.simple_roi_data[0].distance_min.ToString();
                    textBox_Sat.Text = data.simple_roi_data[0].saturation_count.ToString();
                    textBox_roi_num.Text = data.simple_roi_data[0].roi_num.ToString();
                    if (comboBox_sel_roi.SelectedIndex >= data.simple_roi_data[0].roi_num)
                    {
                        comboBox_sel_roi.SelectedIndex = 0;
                    }
                    textBox_group_id.Text = data.simple_roi_data[comboBox_sel_roi.SelectedIndex].group_id.ToString();
                    textBox_roi_id.Text = data.simple_roi_data[comboBox_sel_roi.SelectedIndex].roi_id.ToString();
                    textBox_threshold_state.Text = data.simple_roi_data[comboBox_sel_roi.SelectedIndex].threshold_state.ToString();
                    break;
                case HPS3D_EventType_t.HPS3D_SIMPLE_DEPTH_EVEN:
                    label_PackType.Text = "PacketType: SIMPLE_DEPTH";
                    data = (HPS3D_MeasureData_t)args[1];
                    textBox_dist.Text = data.simple_depth_data.distance_average.ToString();
                    textBox_minDist.Text = data.simple_depth_data.distance_min.ToString();
                    textBox_Sat.Text = data.simple_depth_data.saturation_count.ToString();
                    break;
                case HPS3D_EventType_t.HPS3D_FULL_ROI_EVEN:
                    label_PackType.Text = "PacketType: FULL_ROI";
                    data = (HPS3D_MeasureData_t)args[1];
                    textBox_dist.Text = data.full_roi_data[0].distance_average.ToString();
                    textBox_minDist.Text = data.full_roi_data[0].distance_min.ToString();
                    textBox_Sat.Text = data.full_roi_data[0].saturation_count.ToString();
                    textBox_roi_num.Text = data.full_roi_data[0].roi_num.ToString();
                    if (comboBox_sel_roi.SelectedIndex >= data.full_roi_data[0].roi_num)
                    {
                        comboBox_sel_roi.SelectedIndex = 0;
                    }
                    textBox_group_id.Text = Convert.ToString(data.full_roi_data[comboBox_sel_roi.SelectedIndex].group_id);
                    textBox_roi_id.Text = data.full_roi_data[comboBox_sel_roi.SelectedIndex].roi_id.ToString();
                    textBox_threshold_state.Text = data.full_roi_data[comboBox_sel_roi.SelectedIndex].threshold_state.ToString();
                    break;
                case HPS3D_EventType_t.HPS3D_FULL_DEPTH_EVEN:
                    label_PackType.Text = "PacketType: FULL_DEPTH";
                    data = (HPS3D_MeasureData_t)args[1];
                    byte[] gray_8bit = new byte[data.full_depth_data.distance.Length];
                    for (int i = 0; i < data.full_depth_data.distance.Length; i++)
                    {
                        gray_8bit[i] = (byte)(data.full_depth_data.distance[i] >> 4);
                    }
                    DistanceBitmap = ToGrayBitmap(gray_8bit, HPS3D160_Device.MAX_WIDTH, HPS3D160_Device.MAX_HEIGHT);
                    textBox_dist.Text = data.full_depth_data.distance_average.ToString();
                    textBox_minDist.Text = data.full_depth_data.distance_min.ToString();
                    textBox_Sat.Text = data.full_depth_data.saturation_count.ToString();
                    
                    break;
                case HPS3D_EventType_t.HPS3D_SYS_EXCEPTION_EVEN:
                    break;
                case HPS3D_EventType_t.HPS3D_DISCONNECT_EVEN:
                    label_isConnect.Text = "disconnected";
                    break;
                case HPS3D_EventType_t.HPS3D_NULL_EVEN:
                default:
                    break;
            }
        }


        private void UserEventCallback(int handle, HPS3D_EventType_t e, IntPtr data,int dataLen, IntPtr userPara)
        {
            updateUIHandler updateHandler = new updateUIHandler(updateUI);
            object[] args = new object[4];
            args[0] = e;
            byte[] r_buff = new byte[dataLen];
            HPS3D_MeasureData_t retData = new HPS3D_MeasureData_t() ;
            Marshal.Copy(data, r_buff, 0, dataLen);
            switch (e)
            {
                case HPS3D_EventType_t.HPS3D_SIMPLE_ROI_EVEN:
                case HPS3D_EventType_t.HPS3D_SIMPLE_DEPTH_EVEN:
                case HPS3D_EventType_t.HPS3D_FULL_ROI_EVEN:
                case HPS3D_EventType_t.HPS3D_FULL_DEPTH_EVEN:
                    HPS3D160_Device.HPS3D_ConvertToMeasureData(r_buff,out retData, e);
                    args[1] = retData;
                    break;
                case HPS3D_EventType_t.HPS3D_SYS_EXCEPTION_EVEN:
                    args[1] = "SYS ERROR:" + System.Text.Encoding.Default.GetString(r_buff);
                    break;
                case HPS3D_EventType_t.HPS3D_DISCONNECT_EVEN:
                    args[1] = "Device is Closed!";
                    HPS3D160_Device.HPS3D_CloseDevice(handle);
                    break;
                case HPS3D_EventType_t.HPS3D_NULL_EVEN:
                default:
                    break;
            }

            if (this.IsHandleCreated)
            {
                BeginInvoke(updateHandler, new object[] { args });
            }
        }

        private void InitMeasureData(out HPS3D_MeasureData_t data)
        {
            data = new HPS3D_MeasureData_t();

            data.simple_roi_data = new HPS3D_SimpleRoiData_t[HPS3D160_Device.MAX_ROI_NUMBER];
            data.full_roi_data = new HPS3D_FullRoiData_t[HPS3D160_Device.MAX_ROI_NUMBER];
            data.simple_depth_data = new HPS3D_DepthData_t();
            data.full_depth_data = new HPS3D_DepthData_t();

            for (int i = 0; i < data.full_roi_data.Length; i++)
            {
                data.full_roi_data[i].distance = new UInt16[HPS3D160_Device.MAX_PIXEL_NUMBER];
            }
            data.full_depth_data.distance = new UInt16[HPS3D160_Device.MAX_PIXEL_NUMBER];
            data.full_depth_data.point_cloud_data.point_data = new HPS3D_PerPointCloudData_t[HPS3D160_Device.MAX_PIXEL_NUMBER];

        }


        private void button_Connect_Click(object sender, EventArgs e)
        {
            HPS3D_StatusTypeDef ret = HPS3D_StatusTypeDef.HPS3D_RET_OK;
            if (radioButton_USB.Checked == true)
            {
                ret = HPS3D160_Device.HPS3D_USBConnectDevice(comboBox_ports.Text, ref handle);
            }
            else if (radioButton_Ethernet.Checked == true)
            {
                
                UInt16 EPort = Convert.ToUInt16(textBox_port.Text);
                ret = HPS3D160_Device.HPS3D_EthernetConnectDevice(textBox_host.Text,EPort,ref handle);
            }

            if (ret != HPS3D_StatusTypeDef.HPS3D_RET_OK)
            {
                label_isConnect.Text = "disconnected";
                MessageBox.Show("connect faild! err: " + ret);
                return;
            }

            label_isConnect.Text = "connected";
            button_disconnect.Enabled = true;
            button_Connect.Enabled = false;

            // InitMeasureData(out resultData);

            eventFunc = new UserEventCallbackHandleDelegate(UserEventCallback);
            HPS3D160_Device.HPS3D_RegisterEventCallback(eventFunc, new IntPtr());

            label_SDKVer.Text = "SDK Ver:" + HPS3D160_Device.HPS3D_GetSDKVersion();
            label_DevVer.Text = "DEV Ver:" + HPS3D160_Device.HPS3D_GetDeviceVersion(handle);
            label_SN.Text = "SN:" +HPS3D160_Device.HPS3D_GetSerialNumber(handle);

            updateSettings();
        }

        /// <summary>
        /// disconnect
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_disconnect_Click(object sender, EventArgs e)
        {
            if (HPS3D160_Device.HPS3D_IsConnect(handle))
            {
                HPS3D160_Device.HPS3D_CloseDevice(handle);
                label_isConnect.Text = "disconnected";
                button_disconnect.Enabled = false;
                button_Connect.Enabled = true;
            }
        }

        private void button_Continuous_Click(object sender, EventArgs e)
        {
      
            if (!HPS3D160_Device.HPS3D_IsConnect(handle))
            {
                MessageBox.Show("Device not connected!");
                return;
            }
            if (!HPS3D160_Device.HPS3D_IsStart(handle))
            {
                HPS3D160_Device.HPS3D_StartCapture(handle);
                button_Continuous.Text = "Stop";
            }
            else
            {
                HPS3D160_Device.HPS3D_StopCapture(handle);
                button_Continuous.Text = "Continuous";
            } 
        }

        private void button_Single_Click(object sender, EventArgs e)
        {
            if (!HPS3D160_Device.HPS3D_IsConnect(handle))
            {
                MessageBox.Show("Device not connected!");
                return;
            }

            HPS3D_EventType_t type = HPS3D_EventType_t.HPS3D_NULL_EVEN;
            HPS3D_MeasureData_t retData = new HPS3D_MeasureData_t();
            if (HPS3D_StatusTypeDef.HPS3D_RET_OK != HPS3D160_Device.HPS3D_SingleCapture(handle, ref type,ref retData))
            {
                MessageBox.Show("Single capture faild!");
                return;
            }

            updateUIHandler updateHandler = new updateUIHandler(updateUI);
            object[] args = new object[4];
            args[0] = type;
            args[1] = retData;
            if (this.IsHandleCreated)
            {
                BeginInvoke(updateHandler, new object[] { args });
            }
        }


        private void button_SetGroupID_Click(object sender, EventArgs e)
        {
            if (!HPS3D160_Device.HPS3D_IsConnect(handle))
            {
                MessageBox.Show("Device not connected!");
                return;
            }
            string GroupID = comboBox_GroupID.Text;
            HPS3D_StatusTypeDef ret = HPS3D_StatusTypeDef.HPS3D_RET_OK;
            ret = HPS3D160_Device.HPS3D_SetROIGroupID(handle, Convert.ToByte(GroupID));
            if (ret != HPS3D_StatusTypeDef.HPS3D_RET_OK)
            {
                MessageBox.Show("SetROIGroupID ERR:" + ret);
                return;
            }
        }

        private void button_SetCameraCode_Click(object sender, EventArgs e)
        {
            if (!HPS3D160_Device.HPS3D_IsConnect(handle))
            {
                MessageBox.Show("Device not connected!");
                return;
            }
            string CameraCode = comboBox_CameraCode.Text;
            HPS3D_StatusTypeDef ret = HPS3D_StatusTypeDef.HPS3D_RET_OK;
            ret = HPS3D160_Device.HPS3D_SetMultiCameraCode(handle,Convert.ToByte(CameraCode));
            if (ret != HPS3D_StatusTypeDef.HPS3D_RET_OK)
            {
                MessageBox.Show("SetMultiCameraCode ERR:" + ret);
                return;
            }
        }

        private void button_SetDistanceFilter_Click(object sender, EventArgs e)
        {
            if (!HPS3D160_Device.HPS3D_IsConnect(handle))
            {
                MessageBox.Show("Device not connected!");
                return;
            }
            string enable = comboBox_DistanceFilterEnable.Text;
            HPS3D_StatusTypeDef ret = HPS3D_StatusTypeDef.HPS3D_RET_OK;
            ret = HPS3D160_Device.HPS3D_SetDistanceFilterConf(handle, "true" == enable ? 1 : 0, (float)Convert.ToDouble(textBox_DitanceFilter.Text));
            if (ret != HPS3D_StatusTypeDef.HPS3D_RET_OK)
            {
                MessageBox.Show("SetDistanceFilterConf ERR:" + ret);
                return;
            }
        }

        private void button_SetSmoothFilter_Click(object sender, EventArgs e)
        {
            if (!HPS3D160_Device.HPS3D_IsConnect(handle))
            {
                MessageBox.Show("Device not connected!");
                return;
            }
            HPS3D_SmoothFilterType_t type;
            string SmoothFilterType = comboBox_SmoothFilter.Text;
            if ("DISABLE" == SmoothFilterType)
            {
                type = HPS3D_SmoothFilterType_t.HPS3D_SMOOTH_FILTER_DISABLE;
            }
            else if ("AVERAGE" == SmoothFilterType)
            {
                type = HPS3D_SmoothFilterType_t.HPS3D_SMOOTH_FILTER_AVERAGE;
            }
            else
            {
                type = HPS3D_SmoothFilterType_t.HPS3D_SMOOTH_FILTER_GAUSS;
            }
            HPS3D_StatusTypeDef ret = HPS3D_StatusTypeDef.HPS3D_RET_OK;
            ret = HPS3D160_Device.HPS3D_SetSmoothFilterConf(handle, type, Convert.ToInt32(textBox_SmoothFilter.Text));
            if (ret != HPS3D_StatusTypeDef.HPS3D_RET_OK)
            {
                MessageBox.Show("SetSmoothFilterConf ERR:" + ret);
                return;
            }
        }


        private void button_SetOpticalPathCalibration(object sender, EventArgs e)
        {
            if (!HPS3D160_Device.HPS3D_IsConnect(handle))
            {
                MessageBox.Show("Device not connected!");
                return;
            }
            HPS3D_StatusTypeDef ret = HPS3D_StatusTypeDef.HPS3D_RET_OK;
            string enable = comboBox_OpticalPathCalibration.Text;
            ret = HPS3D160_Device.HPS3D_SetOpticalPathCalibration(handle, "true" == enable ? 1 : 0);
            if (ret != HPS3D_StatusTypeDef.HPS3D_RET_OK)
            {
                MessageBox.Show("SetOpticalPathCalibration ERR:" + ret);
                return;
            }
        }

        private void button_SetDistanceOffset_Click(object sender, EventArgs e)
        {
            if (!HPS3D160_Device.HPS3D_IsConnect(handle))
            {
                MessageBox.Show("Device not connected!");
                return;
            }
            HPS3D_StatusTypeDef ret = HPS3D_StatusTypeDef.HPS3D_RET_OK;
            ret = HPS3D160_Device.HPS3D_SetDistanceOffset(handle,Convert.ToInt16(textBox_DistanceOffset.Text));
            if (ret != HPS3D_StatusTypeDef.HPS3D_RET_OK)
            {
                MessageBox.Show("SetDistanceOffset ERR:" + ret);
                return;
            }
        }

        private void updateSettings()
        {
            if (!HPS3D160_Device.HPS3D_IsConnect(handle))
            {
                MessageBox.Show("Device not connected!");
                return;
            }
            HPS3D_DeviceSettings_t settings = new HPS3D_DeviceSettings_t();
            HPS3D_StatusTypeDef ret = HPS3D_StatusTypeDef.HPS3D_RET_OK;
            ret = HPS3D160_Device.HPS3D_ExportSettings(handle, ref settings);
            if (ret != HPS3D_StatusTypeDef.HPS3D_RET_OK)
            {
                MessageBox.Show("ExportSettings ERR:" + ret);
                return;
            }
            textBox_UserID.Text = settings.user_id.ToString();
            int max_multiCamera_code = settings.max_multiCamera_code;
            for (int i = 0; i < max_multiCamera_code; i++)
            {
                comboBox_CameraCode.Items.Add(i);
            }
            comboBox_CameraCode.SelectedIndex = settings.cur_multiCamera_code;
            int max_roi_group_number = settings.max_roi_group_number;
            for (int i = 0; i < max_roi_group_number; i++)
            {
                comboBox_GroupID.Items.Add(i);
            }
            comboBox_GroupID.SelectedIndex = settings.cur_group_id;
            textBox_DistanceOffset.Text = settings.dist_offset.ToString();
            comboBox_DistanceFilterEnable.SelectedIndex = 1 - settings.dist_filter_enable;
            textBox_DitanceFilter.Text = settings.dist_filter_K.ToString();
            comboBox_SmoothFilter.SelectedIndex = settings.smooth_filter_type;
            textBox_SmoothFilter.Text = settings.smooth_filter_args.ToString();
            comboBox_OpticalPathCalibration.SelectedIndex = 1 - settings.optical_path_calibration;
            int max_roi_number = settings.max_roi_number;
            for (int i = 0; i < max_roi_number; i++)
            {
                comboBox_sel_roi.Items.Add(i);
            }
            comboBox_sel_roi.SelectedIndex = 0;
            textBox_roi_num.Text = "0";
        }

        private void button_ExportSettings_Click(object sender, EventArgs e)
        {
            updateSettings();
        }

        private void timer_Update_Tick(object sender, EventArgs e)
        {
            pictureBox1.Image = DistanceBitmap;
        }

        private void button_saveSettings_Click(object sender, EventArgs e)
        {
            if (!HPS3D160_Device.HPS3D_IsConnect(handle))
            {
                MessageBox.Show("Device not connected!");
                return;
            }
            HPS3D_StatusTypeDef ret = HPS3D_StatusTypeDef.HPS3D_RET_OK;
            ret = HPS3D160_Device.HPS3D_SaveSettings(handle);
            if (ret != HPS3D_StatusTypeDef.HPS3D_RET_OK)
            {
                MessageBox.Show("ExportSettings ERR:" + ret);
                return;
            }
        }

        private void groupBox4_Enter(object sender, EventArgs e)
        {

        }
    }
}
