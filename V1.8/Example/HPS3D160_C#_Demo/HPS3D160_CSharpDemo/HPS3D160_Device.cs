using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace HPS3D160_CSharpDemo
{
    /*函数返回的结果*/
    public enum HPS3D_StatusTypeDef
    {
        HPS3D_RET_OK = 0x01,           /*成功返回*/
        HPS3D_RET_ERROR = 0x02,        /*错误返回*/
        HPS3D_RET_BUSY = 0x03,         /*忙返回*/
        HPS3D_RET_CONNECT_FAILED,      /*连接失败返回*/
        HPS3D_RET_CREAT_PTHREAD_ERR,   /*线程创建失败返回*/
        HPS3D_RET_WRITE_ERR,           /*写数据错误返回*/
        HPS3D_RET_READ_ERR,            /*读数据错误返回*/
        HPS3D_RET_PACKET_HEAD_ERR,     /*报头错误返回*/
        HPS3D_RET_PACKET_ERR,          /*数据包错误返回*/
        HPS3D_RET_BUFF_EMPTY,          /*内存分配失败返回*/
        HPS3D_RET_VER_MISMATCH,        /*版本不匹配错误返回*/
    };

    /*设备当前参数*/
    public struct HPS3D_DeviceSettings_t
    {
        public int user_id;                   /*用户自定义ID，默认为0*/
        public int max_resolution_X;          /*X方向分辨率，默认160*/
        public int max_resolution_Y;          /*Y方向分辨率，默认60*/
        public int max_roi_group_number;      /*支持的最大ROI分组数，默认为16*/
        public int max_roi_number;            /*支持的最大ROI数，默认为8*/
        public int max_threshold_number;      /*支持的最大阈值报警数，默认为3*/
        public int max_multiCamera_code;      /*支持的最大多机编号，默认为16*/

        public int dist_filter_enable;        /*距离滤波器开启状态，默认为false*/
        public float dist_filter_K;           /*距离滤波器比例系数*/
        public int smooth_filter_type;       /*平滑滤波器类型*/
        public int smooth_filter_args;       /*平滑滤波器参数*/
        public int cur_group_id;              /*当前ROI分组*/
        public int cur_multiCamera_code;      /*当前多机编号*/
        public int dist_offset;               /*当前多机编号*/
        public int optical_path_calibration;  /*光程补偿开启状态*/
    };

    /*平滑滤波器的类型*/
    enum HPS3D_SmoothFilterType_t
    {
        HPS3D_SMOOTH_FILTER_DISABLE = 0,        /*关闭滤波器*/
        HPS3D_SMOOTH_FILTER_AVERAGE = 1,        /*均值滤波器*/
        HPS3D_SMOOTH_FILTER_GAUSS               /*高斯滤波器*/
    };

    /*通知事件类型*/
    public enum HPS3D_EventType_t
    {
        HPS3D_NULL_EVEN = 0x0,              /*无事件通知*/
        HPS3D_SIMPLE_ROI_EVEN = 0x01,       /*简单ROI数据包（不含深度图数据）@see HPS3D_SimpleRoiData_t*/
        HPS3D_FULL_ROI_EVEN = 0x02,         /*完整ROI数据包（含深度图数据）@see HPS3D_FullRoiData_t*/
        HPS3D_FULL_DEPTH_EVEN = 0x03,       /*完整深度数据包（含深度图数据）@see HPS3D_DepthData_t*/
        HPS3D_SIMPLE_DEPTH_EVEN = 0x04,     /*简单深度数据包（不含深度图数据）@see HPS3D_DepthData_t*/
        HPS3D_SYS_EXCEPTION_EVEN = 0x07,    /*系统异常事件*/
        HPS3D_DISCONNECT_EVEN = 0x08,		/*异常断开事件*/
    }

    // 事件委托类型
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void UserEventCallbackHandleDelegate(int handle, HPS3D_EventType_t arg, IntPtr data, int dataLen,IntPtr userPara);

    /*ROI简单数据包*/
    public struct HPS3D_SimpleRoiData_t
    {
        public byte roi_num;                     /*ROI总数量*/
        public byte group_id;                    /*组ID*/
        public byte roi_id;                      /*ROI ID*/
        public byte threshold_state;             /*报警状态指示位,bit0:阈值0报警, bit1:阈值1报警, bit2:阈值2报警*/
        public UInt16 distance_average;          /*平均距离值*/
        public UInt16 distance_min;              /*最小距离值*/
        public UInt16 saturation_count;          /*饱和像素点数*/
        public UInt32 frame_cnt;				 /*帧计数器*/
    };

    /*完整ROI数据包*/
    public struct HPS3D_FullRoiData_t
    {
        public byte roi_num;                        /*被激活的ROI总数*/
        public byte group_id;                       /*ROI组 ID号*/
        public byte roi_id;                         /*ROI ID号*/
        public byte threshold_state;                /*报警状态指示位,bit0:阈值0报警, bit1:阈值1报警, bit2:阈值2报警*/
        public UInt16 left_top_x;                   /*左上角x坐标*/
        public UInt16 left_top_y;                   /*左上角y坐标*/
        public UInt16 right_bottom_x;               /*右下角x坐标*/
        public UInt16 right_bottom_y;               /*右下角y坐标*/
        public UInt16 distance_average;             /*平均距离值*/
        public UInt16 distance_min;                 /*最小距离值*/
        public UInt16 saturation_count;             /*饱和像素点数*/
        public UInt32 pixel_number;                 /*ROI像素点总数*/
        public UInt32 frame_cnt;                        /*帧计数器*/
        public UInt16[] distance;/*深度数据，按顺序储存*/
    };

    /*点云坐标值*/
    public struct HPS3D_PerPointCloudData_t
    {
        public float x;
        public float y;
        public float z;
    };

    /*有序点云数据*/
    public struct HPS3D_PointCloudData_t
    {
        public HPS3D_PerPointCloudData_t[] point_data;  /*存储点云数据，按像素顺序存储*/
        public UInt16 width;                          /*水平方向点数*/
        public UInt16 height;                        /*垂直方向点数*/
        public UInt32 points;						 /*总点数*/
    };

    /*深度数据*/
    public struct HPS3D_DepthData_t
    {
        public UInt16 distance_average;             /*整个视野有效距离的平均值*/
        public UInt16 distance_min;                 /*最小距离估算值*/
        public UInt16 saturation_count;             /*饱和像素点数*/
        public UInt32 frame_cnt;                    /*帧计数器，可用于丢帧检测*/
        public UInt16[] distance;                   /*深度数据，按顺序储存，当输出数据类型为 简单包时不可用*/
        public HPS3D_PointCloudData_t point_cloud_data; /*有序点云数据，按顺序储存，当输出数据类型为 简单包时不可用*/
    };


    /*测量数据返回结构体*/
    public struct HPS3D_MeasureData_t
    {
        public HPS3D_SimpleRoiData_t[] simple_roi_data; /*简单ROI数据包 @see HPS3D_SimpleRoiData_t*/
        public HPS3D_FullRoiData_t[] full_roi_data;     /*完整ROI数据包 @see HPS3D_FullRoiData_t*/
        public HPS3D_DepthData_t simple_depth_data;     /*简单深度图数据包  @see HPS3D_DepthData_t*/
        public HPS3D_DepthData_t full_depth_data;		/*完整ROI数据包 @see HPS3D_DepthData_t*/
    };

    class HPS3D160_Device
    {
        public static int MAX_ROI_NUMBER = 8;     /*支持最大ROI数量*/
        public static int MAX_PIXEL_NUMBER = 9600;  /*最大像素点数 160*60*/
        public static int MAX_WIDTH = 160;          /*x方向分辨率*/
        public static int MAX_HEIGHT = 60;          /*y方向分辨率*/

        [DllImport("HPS3D160_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        extern static int HPS3DAPI_USBConnectDevice(string portName, ref int handle);

        [DllImport("HPS3D160_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        extern static int HPS3DAPI_EthernetConnectDevice(byte[] controllerIp,UInt16 controllerPort, ref int handle);

        [DllImport("HPS3D160_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        extern static int HPS3DAPI_CloseDevice(int handle);

        [DllImport("HPS3D160_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        extern static int HPS3DAPI_IsConnect(int handle);

        [DllImport("HPS3D160_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        extern static int HPS3DAPI_IsStart(int handle);


        [DllImport("HPS3D160_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        extern static int HPS3DAPI_StartCapture(int handle);

        [DllImport("HPS3D160_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        extern static int HPS3DAPI_StopCapture(int handle);

        [DllImport("HPS3D160_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        extern static int HPS3DAPI_SingleCapture(int handle,ref int type, ref IntPtr data,ref int dataLen);

        [DllImport("HPS3D160_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        extern static int HPS3DAPI_RegisterEventCallback(UserEventCallbackHandleDelegate eventHandle, IntPtr userPara);

        [DllImport("HPS3D160_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        extern static int HPS3DAPI_UnregisterEventCallback();

        [DllImport("HPS3D160_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        extern static IntPtr HPS3DAPI_GetDeviceVersion(int handle);
        
        [DllImport("HPS3D160_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        extern static IntPtr HPS3DAPI_GetSDKVersion();

        [DllImport("HPS3D160_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        extern static IntPtr HPS3DAPI_GetSerialNumber(int handle);

        [DllImport("HPS3D160_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        extern static int HPS3DAPI_SetDeviceUserID(int handle,byte userID);

        [DllImport("HPS3D160_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        extern static int HPS3DAPI_SetROIGroupID(int handle, byte groupID);

        [DllImport("HPS3D160_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        extern static int HPS3DAPI_SetMultiCameraCode(int handle, byte CameraCode);

        [DllImport("HPS3D160_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        extern static int HPS3DAPI_ExportSettings(int handle, ref HPS3D_DeviceSettings_t settings);

        [DllImport("HPS3D160_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        extern static int HPS3DAPI_SaveSettings(int handle);

        [DllImport("HPS3D160_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        extern static int HPS3DAPI_SetDistanceFilterConf(int handle, int enable, float K);

        [DllImport("HPS3D160_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        extern static int HPS3DAPI_SetSmoothFilterConf(int handle, int type, int args);

        [DllImport("HPS3D160_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        extern static int HPS3DAPI_SetDistanceOffset(int handle,Int16 offset);
        [DllImport("HPS3D160_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        extern static int HPS3DAPI_SetOpticalPathCalibration(int handle, int enbale);

        /// <summary>
        ///   USB设备连接
        /// </summary>
        /// <param name="portName"></param> 端口号
        /// <param name="deviceHandler"></param> 返回的设备ID
        /// <returns></returns>
        public static HPS3D_StatusTypeDef HPS3D_USBConnectDevice(string portName, ref int deviceHandler)
        {
             return (HPS3D_StatusTypeDef)HPS3DAPI_USBConnectDevice(portName,ref deviceHandler);
        }

        public static HPS3D_StatusTypeDef HPS3D_EthernetConnectDevice(string controllerIp, UInt16 controllerPort, ref int handle)
        {
            byte[] Ip = System.Text.Encoding.UTF8.GetBytes(controllerIp);
            return (HPS3D_StatusTypeDef)HPS3DAPI_EthernetConnectDevice(Ip, controllerPort,ref handle);
        }

        public static HPS3D_StatusTypeDef HPS3D_CloseDevice(int handle)
        {
            return (HPS3D_StatusTypeDef)HPS3DAPI_CloseDevice(handle);
        }

        public static bool HPS3D_IsConnect(int handle)
        {
            return HPS3DAPI_IsConnect(handle) == 1 ? true : false;
        }

        public static bool HPS3D_IsStart(int handle)
        {
            return HPS3DAPI_IsStart(handle) == 1 ? true : false;
        }

        public static HPS3D_StatusTypeDef HPS3D_StartCapture(int handle)
        {
            return (HPS3D_StatusTypeDef)HPS3DAPI_StartCapture(handle);
        }

        public static HPS3D_StatusTypeDef HPS3D_StopCapture(int handle)
        {
            return (HPS3D_StatusTypeDef)HPS3DAPI_StopCapture(handle);
        }

        public static int HPS3D_ConvertToMeasureData(byte[] data,out HPS3D_MeasureData_t resultData, HPS3D_EventType_t type)
        {
            int len = 0;
            resultData = new HPS3D_MeasureData_t();
            if (type == HPS3D_EventType_t.HPS3D_SIMPLE_ROI_EVEN)
            {
                resultData.simple_roi_data = new HPS3D_SimpleRoiData_t[MAX_ROI_NUMBER];
                int num = (int)data[0];
                for (int i = 0; i < num; i++)
                {
                    resultData.simple_roi_data[i].roi_num = data[len++];
                    resultData.simple_roi_data[i].group_id = data[len++];
                    resultData.simple_roi_data[i].roi_id = data[len++];
                    resultData.simple_roi_data[i].threshold_state = data[len++];

                    resultData.simple_roi_data[i].distance_average = (UInt16)(data[len++] << 8);
                    resultData.simple_roi_data[i].distance_average += data[len++];

                    resultData.simple_roi_data[i].distance_min = (UInt16)(data[len++] << 8);
                    resultData.simple_roi_data[i].distance_min += data[len++];

                    resultData.simple_roi_data[i].saturation_count = (UInt16)(data[len++] << 8);
                    resultData.simple_roi_data[i].saturation_count += data[len++];

                    resultData.simple_roi_data[i].frame_cnt = (UInt32)(data[len++] << 24);
                    resultData.simple_roi_data[i].frame_cnt += (UInt32)(data[len++] << 16);
                    resultData.simple_roi_data[i].frame_cnt += (UInt32)(data[len++] << 8);
                    resultData.simple_roi_data[i].frame_cnt += data[len++];
                }
            }
            else if (type == HPS3D_EventType_t.HPS3D_FULL_ROI_EVEN)
            {
                resultData.full_roi_data = new HPS3D_FullRoiData_t[MAX_ROI_NUMBER];
                int num = (int)data[0];
                for (int i = 0; i < num; i++)
                {
                    resultData.full_roi_data[i].distance = new UInt16[MAX_PIXEL_NUMBER];
                    resultData.full_roi_data[i].roi_num = data[len++];
                    resultData.full_roi_data[i].group_id = data[len++];
                    resultData.full_roi_data[i].roi_id = data[len++];
                    resultData.full_roi_data[i].threshold_state = data[len++];

                    resultData.full_roi_data[i].left_top_x = (UInt16)(data[len++] << 8);
                    resultData.full_roi_data[i].left_top_x += data[len++];
                    resultData.full_roi_data[i].left_top_y = (UInt16)(data[len++] << 8);
                    resultData.full_roi_data[i].left_top_y += data[len++];
                    resultData.full_roi_data[i].right_bottom_x = (UInt16)(data[len++] << 8);
                    resultData.full_roi_data[i].right_bottom_x += data[len++];
                    resultData.full_roi_data[i].right_bottom_y = (UInt16)(data[len++] << 8);
                    resultData.full_roi_data[i].right_bottom_y += data[len++];

                    resultData.full_roi_data[i].distance_average = (UInt16)(data[len++] << 8);
                    resultData.full_roi_data[i].distance_average += data[len++];
                    resultData.full_roi_data[i].distance_min = (UInt16)(data[len++] << 8);
                    resultData.full_roi_data[i].distance_min += data[len++];
                    resultData.full_roi_data[i].saturation_count = (UInt16)(data[len++] << 8);
                    resultData.full_roi_data[i].saturation_count += data[len++];

                    resultData.full_roi_data[i].pixel_number = (UInt32)(data[len++] << 24);
                    resultData.full_roi_data[i].pixel_number += (UInt32)(data[len++] << 16);
                    resultData.full_roi_data[i].pixel_number += (UInt32)(data[len++] << 8);
                    resultData.full_roi_data[i].pixel_number += data[len++];

                    resultData.full_roi_data[i].frame_cnt = (UInt32)(data[len++] << 24);
                    resultData.full_roi_data[i].frame_cnt += (UInt32)(data[len++] << 16);
                    resultData.full_roi_data[i].frame_cnt += (UInt32)(data[len++] << 8);
                    resultData.full_roi_data[i].frame_cnt += data[len++];

                    int pixNum = (int)resultData.full_roi_data[i].pixel_number;
                    for (int j = 0; j < pixNum; j++)
                    {
                        resultData.full_roi_data[i].distance[j] = (UInt16)(data[len++] << 8);
                        resultData.full_roi_data[i].distance[j] += data[len++];
                    }
                }
            }
            else if (type == HPS3D_EventType_t.HPS3D_SIMPLE_DEPTH_EVEN)
            {
                resultData.simple_depth_data.distance_average = (UInt16)(data[len++] << 8);
                resultData.simple_depth_data.distance_average += data[len++];
                resultData.simple_depth_data.distance_min = (UInt16)(data[len++] << 8);
                resultData.simple_depth_data.distance_min += data[len++];
                resultData.simple_depth_data.saturation_count = (UInt16)(data[len++] << 8);
                resultData.simple_depth_data.saturation_count += data[len++];

                resultData.simple_depth_data.frame_cnt = (UInt32)(data[len++] << 24);
                resultData.simple_depth_data.frame_cnt += (UInt32)(data[len++] << 16);
                resultData.simple_depth_data.frame_cnt += (UInt32)(data[len++] << 8);
                resultData.simple_depth_data.frame_cnt += data[len++];
            }
            else if (type == HPS3D_EventType_t.HPS3D_FULL_DEPTH_EVEN)
            {
                resultData.full_depth_data.distance_average = (UInt16)(data[len++] << 8);
                resultData.full_depth_data.distance_average += data[len++];
                resultData.full_depth_data.distance_min = (UInt16)(data[len++] << 8);
                resultData.full_depth_data.distance_min += data[len++];
                resultData.full_depth_data.saturation_count = (UInt16)(data[len++] << 8);
                resultData.full_depth_data.saturation_count += data[len++];


                resultData.full_depth_data.frame_cnt = (UInt32)(data[len++] << 24);
                resultData.full_depth_data.frame_cnt += (UInt32)(data[len++] << 16);
                resultData.full_depth_data.frame_cnt += (UInt32)(data[len++] << 8);
                resultData.full_depth_data.frame_cnt += data[len++];


                resultData.full_depth_data.point_cloud_data.width = (UInt16)(data[len++] << 8);
                resultData.full_depth_data.point_cloud_data.width += data[len++];
                resultData.full_depth_data.point_cloud_data.height = (UInt16)(data[len++] << 8);
                resultData.full_depth_data.point_cloud_data.height += data[len++];
                resultData.full_depth_data.point_cloud_data.points = (UInt16)(data[len++] << 8);
                resultData.full_depth_data.point_cloud_data.points += data[len++];


                int MAX_PIX_NUM = MAX_PIXEL_NUMBER;
                resultData.full_depth_data.distance = new UInt16[MAX_PIX_NUM];
                resultData.full_depth_data.point_cloud_data.point_data = new HPS3D_PerPointCloudData_t[MAX_PIX_NUM];
                int point_start = len + MAX_PIX_NUM * 2;
                int x = 0, y = 0, z = 0;
                for (int i = 0; i < MAX_PIX_NUM; i++)
                {
                    resultData.full_depth_data.distance[i] = (UInt16)(data[len++] << 8);
                    resultData.full_depth_data.distance[i] += data[len++];

                    x = data[point_start++] << 24;
                    x += data[point_start++] << 16;
                    x += data[point_start++] << 8;
                    x += data[point_start++] << 0;

                    y = data[point_start++] << 24;
                    y += data[point_start++] << 16;
                    y += data[point_start++] << 8;
                    y += data[point_start++] << 0;

                    z = data[point_start++] << 24;
                    z += data[point_start++] << 16;
                    z += data[point_start++] << 8;
                    z += data[point_start++] << 0;
                    resultData.full_depth_data.point_cloud_data.point_data[i].x = (float)(x / 100.0);
                    resultData.full_depth_data.point_cloud_data.point_data[i].y = (float)(y / 100.0);
                    resultData.full_depth_data.point_cloud_data.point_data[i].z = (float)(z / 100.0);
                }

                len = len + 14 * MAX_PIX_NUM;
            }
            return len;
        }

        public static HPS3D_StatusTypeDef HPS3D_SingleCapture(int handle, ref HPS3D_EventType_t type, ref HPS3D_MeasureData_t data)
        {
            HPS3D_StatusTypeDef ret = HPS3D_StatusTypeDef.HPS3D_RET_OK;
            do
            {
                IntPtr ret_data = IntPtr.Zero;
                int t = 0;
                int len = 0;
                ret = (HPS3D_StatusTypeDef)HPS3DAPI_SingleCapture(handle, ref t,ref ret_data,ref len);
                if (ret != HPS3D_StatusTypeDef.HPS3D_RET_OK)
                {
                    break;
                }
                type = (HPS3D_EventType_t)t;

                switch (type)
                {
                    case HPS3D_EventType_t.HPS3D_SIMPLE_ROI_EVEN:
                    case HPS3D_EventType_t.HPS3D_FULL_ROI_EVEN:
                    case HPS3D_EventType_t.HPS3D_FULL_DEPTH_EVEN:
                    case HPS3D_EventType_t.HPS3D_SIMPLE_DEPTH_EVEN:
                        byte[] r_buff = new byte[len];
                        Marshal.Copy(ret_data, r_buff, 0, len);
                        HPS3D_ConvertToMeasureData(r_buff, out data, type);
                        break;
                    default:
                        ret = HPS3D_StatusTypeDef.HPS3D_RET_PACKET_ERR;
                        break;
                }
            } while (false);

            return ret;
        }

        public static HPS3D_StatusTypeDef HPS3D_RegisterEventCallback(UserEventCallbackHandleDelegate eventHandle,IntPtr userPara)
        {
            return (HPS3D_StatusTypeDef)HPS3DAPI_RegisterEventCallback(eventHandle, userPara);
        }

        public static HPS3D_StatusTypeDef HPS3D_UnregisterEventCallback()
        {
            return (HPS3D_StatusTypeDef)HPS3DAPI_UnregisterEventCallback();
        }

        public static string HPS3D_GetDeviceVersion(int handle)
        {
            string ret = "";
            IntPtr ptr = HPS3DAPI_GetDeviceVersion(handle);
            ret = Marshal.PtrToStringAnsi(ptr);
            return ret;
        }

        public static string HPS3D_GetSDKVersion()
        {
            string ret = "";
            IntPtr ptr = HPS3DAPI_GetSDKVersion();
            ret = Marshal.PtrToStringAnsi(ptr);
            return ret;
        }

        public static string HPS3D_GetSerialNumber(int handle)
        {
            string ret = "";
            IntPtr ptr = HPS3DAPI_GetSerialNumber(handle);
            ret = Marshal.PtrToStringAnsi(ptr);
            return ret;
        }

        public static HPS3D_StatusTypeDef HPS3D_SetDeviceUserID(int handle,byte userID)
        {
            return (HPS3D_StatusTypeDef)HPS3DAPI_SetDeviceUserID(handle,userID);
        }

        public static HPS3D_StatusTypeDef HPS3D_SetROIGroupID(int handle, byte groupID)
        {
            return (HPS3D_StatusTypeDef)HPS3DAPI_SetROIGroupID(handle, groupID);
        }

        public static HPS3D_StatusTypeDef HPS3D_SetMultiCameraCode(int handle, byte CameraCode)
        {
            return (HPS3D_StatusTypeDef)HPS3DAPI_SetMultiCameraCode(handle, CameraCode);
        }


        public static HPS3D_StatusTypeDef HPS3D_ExportSettings(int handle,ref HPS3D_DeviceSettings_t settings)
        {
            return (HPS3D_StatusTypeDef)HPS3DAPI_ExportSettings(handle,ref settings);
        }


        public static HPS3D_StatusTypeDef HPS3D_SaveSettings(int handle)
        {
            return (HPS3D_StatusTypeDef)HPS3DAPI_SaveSettings(handle);
        }

        public static HPS3D_StatusTypeDef HPS3D_SetDistanceFilterConf(int handle,int enable,float K)
        {
            return (HPS3D_StatusTypeDef)HPS3DAPI_SetDistanceFilterConf(handle, enable, K);
        }

        public static HPS3D_StatusTypeDef HPS3D_SetSmoothFilterConf(int handle, HPS3D_SmoothFilterType_t type, int args)
        {
            return (HPS3D_StatusTypeDef)HPS3DAPI_SetSmoothFilterConf(handle, (int)type, args);
        }

        public static HPS3D_StatusTypeDef HPS3D_SetDistanceOffset(int handle, Int16 offset)
        {
            return (HPS3D_StatusTypeDef)HPS3DAPI_SetDistanceOffset(handle, offset);
        }

        public static HPS3D_StatusTypeDef HPS3D_SetOpticalPathCalibration(int handle, int enbale)
        {
            return (HPS3D_StatusTypeDef)HPS3DAPI_SetOpticalPathCalibration(handle, enbale);
        }

    }
}
