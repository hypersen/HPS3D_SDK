///////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Copyright (c) 2017-2021 Hypersen Technology Co. Ltd.						//
// All rights reserved.                                                     //
//                                                                          //
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY   //
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE      //
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A               //
// PARTICULAR PURPOSE.                                                      //
//                                                                          //
// Website: www.hypersen.com                                                //
// Email: sales@hypersen.com												//
//////////////////////////////////////////////////////////////////////////////

#ifndef __HPS3D_USER_IF_H__
#define __HPS3D_USER_IF_H__

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <stdbool.h>
#include "HPS3DBase_IF.h"


/*函数返回的结果*/
typedef enum
{
	HPS3D_RET_OK = 0x01,           /*成功返回*/
	HPS3D_RET_ERROR = 0x02,        /*错误返回*/
	HPS3D_RET_BUSY = 0x03,         /*忙返回*/
	HPS3D_RET_CONNECT_FAILED,      /*连接失败返回*/
	HPS3D_RET_CREAT_PTHREAD_ERR,   /*线程创建失败返回*/
	HPS3D_RET_WRITE_ERR,		   /*写数据错误返回*/
	HPS3D_RET_READ_ERR,            /*读数据错误返回*/    
	HPS3D_RET_PACKET_HEAD_ERR,     /*报头错误返回*/    
	HPS3D_RET_PACKET_ERR,          /*数据包错误返回*/ 
	HPS3D_RET_BUFF_EMPTY,          /*内存分配失败返回*/ 
	HPS3D_RET_VER_MISMATCH,        /*版本不匹配错误返回*/ 
}HPS3D_StatusTypeDef;


/*设备当前参数*/
typedef struct
{
	int user_id;                   /*用户自定义ID，默认为0*/   
	int max_resolution_X;          /*X方向分辨率，默认160*/   
	int max_resolution_Y;          /*Y方向分辨率，默认60*/
	int max_roi_group_number;      /*支持的最大ROI分组数，默认为16*/   
	int max_roi_number;            /*支持的最大ROI数，默认为8*/  
	int max_threshold_number;      /*支持的最大阈值报警数，默认为3*/   
	int max_multiCamera_code;	   /*支持的最大多机编号，默认为16*/   

	int dist_filter_enable;        /*距离滤波器开启状态，默认为false*/
	float dist_filter_K;           /*距离滤波器比例系数*/
	int  smooth_filter_type;       /*平滑滤波器类型*/
	int  smooth_filter_args;       /*平滑滤波器参数*/
	int cur_group_id;			   /*当前ROI分组*/
	int cur_multiCamera_code;      /*当前多机编号*/
	int dist_offset;               /*当前多机编号*/
	int optical_path_calibration;  /*光程补偿开启状态*/
	int edge_filter_enable;       /*边缘滤波开启状态*/
}HPS3D_DeviceSettings_t;

/*平滑滤波器的类型*/
typedef enum
{
	HPS3D_SMOOTH_FILTER_DISABLE = 0,		/*关闭滤波器*/
	HPS3D_SMOOTH_FILTER_AVERAGE = 1,		/*均值滤波器*/
	HPS3D_SMOOTH_FILTER_GAUSS				/*高斯滤波器*/
}HPS3D_SmoothFilterType_t;


/*通知事件类型*/
typedef enum
{
	HPS3D_NULL_EVEN = 0x0,				/*无事件通知*/
	HPS3D_SIMPLE_ROI_EVEN = 0x01,		/*简单ROI数据包（不含深度图数据）@see HPS3D_SimpleRoiData_t*/
	HPS3D_FULL_ROI_EVEN = 0x02,			/*完整ROI数据包（含深度图数据）@see HPS3D_FullRoiData_t*/
	HPS3D_FULL_DEPTH_EVEN = 0x03,		/*完整深度数据包（含深度图数据）@see HPS3D_DepthData_t*/
	HPS3D_SIMPLE_DEPTH_EVEN = 0x04,		/*简单深度数据包（不含深度图数据）@see HPS3D_DepthData_t*/
	HPS3D_SYS_EXCEPTION_EVEN = 0x07,	/*系统异常事件*/
	HPS3D_DISCONNECT_EVEN = 0x08,		/*异常断开事件*/
}HPS3D_EventType_t;


/*ROI简单数据包*/
typedef struct
{
	uint8_t roi_num;						/*ROI总数量*/
	uint8_t group_id;						/*组ID*/
	uint8_t roi_id;							/*ROI ID*/
	uint8_t threshold_state;				/*报警状态指示位,bit0:阈值0报警, bit1:阈值1报警, bit2:阈值2报警*/
	uint16_t distance_average;				/*平均距离值*/
	uint16_t distance_min;					/*最小距离值*/
	uint16_t saturation_count;				/*饱和像素点数*/
	uint32_t frame_cnt;						/*帧计数器*/
}HPS3D_SimpleRoiData_t;

/*完整ROI数据包*/
typedef struct
{
	uint8_t roi_num;						/*被激活的ROI总数*/
	uint8_t group_id;						/*ROI组 ID号*/
	uint8_t roi_id;							/*ROI ID号*/
	uint8_t threshold_state;				/*报警状态指示位,bit0:阈值0报警, bit1:阈值1报警, bit2:阈值2报警*/
	uint16_t left_top_x;					/*左上角x坐标*/
	uint16_t left_top_y;					/*左上角y坐标*/
	uint16_t right_bottom_x;				/*右下角x坐标*/
	uint16_t right_bottom_y;				/*右下角y坐标*/
	uint16_t distance_average;				/*平均距离值*/
	uint16_t distance_min;					/*最小距离值*/
	uint16_t saturation_count;				/*饱和像素点数*/
	uint32_t pixel_number;					/*ROI像素点总数*/
	uint32_t frame_cnt;						/*帧计数器*/
	uint16_t *distance;/*深度数据，按顺序储存*/
}HPS3D_FullRoiData_t;

/*点云坐标值*/
typedef struct
{
	float x;
	float y;
	float z;
}HPS3D_PerPointCloudData_t;

/*有序点云数据*/
typedef struct
{
	HPS3D_PerPointCloudData_t *point_data;  /*存储点云数据，按像素顺序存储*/
	uint16_t width;							/*水平方向点数*/
	uint16_t height;						/*垂直方向点数*/
	uint32_t points;						/*总点数*/
}HPS3D_PointCloudData_t;

/*深度数据*/
typedef struct
{
	uint16_t distance_average;				/*整个视野有效距离的平均值*/
	uint16_t distance_min;					/*最小距离估算值*/
	uint16_t saturation_count;				/*饱和像素点数*/
	uint32_t frame_cnt;						/*帧计数器，可用于丢帧检测*/
	uint16_t *distance;/*深度数据，按顺序储存，当输出数据类型为 简单包时不可用*/
	HPS3D_PointCloudData_t point_cloud_data; /*有序点云数据，按顺序储存，当输出数据类型为 简单包时不可用*/
}HPS3D_DepthData_t;


/*测量数据返回结构体*/
typedef struct
{
	HPS3D_SimpleRoiData_t *simple_roi_data;	/*简单ROI数据包 @see HPS3D_SimpleRoiData_t*/
	HPS3D_FullRoiData_t *full_roi_data;		/*完整ROI数据包 @see HPS3D_FullRoiData_t*/
	HPS3D_DepthData_t simple_depth_data;		/*简单深度图数据包  @see HPS3D_DepthData_t*/
	HPS3D_DepthData_t full_depth_data;			/*完整ROI数据包 @see HPS3D_DepthData_t*/
}HPS3D_MeasureData_t;


/**
* @brief	     USB设备连接
* @param        portName端口号/设备名(Linux)
* @param		 deviceHandler 返回的设备ID
* @see
* @note
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef	HPS3D_USBConnectDevice(__IN char* portName, __OUT int* deviceHandler);

/**
* @brief	     Ethernet设备连接
* @param        controllerIp 控制器IP
* @param        controllerPort 控制器端口
* @param		 deviceHandler 返回的设备ID
* @see
* @note
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef	HPS3D_EthernetConnectDevice(__IN char* controllerIp, __IN uint16_t controllerPort, __OUT int* deviceHandler);

/**
* @brief	     Ethernet设备连接
* @param		 deviceHandler 设备ID
* @see
* @note
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef HPS3D_EthternetReconnection(__IN int handle);

/**
* @brief	     关闭设备
* @param        handle 设备ID
* @see
* @note
* @retval	     成功返回 1
*/
HPS3D_StatusTypeDef	HPS3D_CloseDevice(__IN int handle);
	

/**
* @brief	     设备连接状态
* @param        handle 设备ID
* @see
* @note
* @retval	     已连接返回true
*/
bool	HPS3D_IsConnect(__IN int handle);

/**
* @brief	     设备连续测量状态
* @param        handle 设备ID
* @see
* @note
* @retval	     连续测量模式返回true
*/
bool	HPS3D_IsStart(__IN int handle);

/**
* @brief	     开始连续采集
* @param        handle 设备ID
* @see			 HPS3DAPI_EVENT_CALLBACK
* @note		 测量结果使用回调函数通知返回
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef	HPS3D_StartCapture(__IN int handle);

/**
* @brief	     停止采集
* @param        handle 设备ID
* @see
* @note
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef	HPS3D_StopCapture(__IN int handle);

/**
* @brief	     单次采集
* @param        handle 设备ID
* @param        type 返回包类型
* @param        data 测量数据
* @see
* @note         测量数据需根据type类型进行选择
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef	HPS3D_SingleCapture(__IN int handle, __OUT HPS3D_EventType_t *type, __OUT HPS3D_MeasureData_t *data);

/**
* @brief	    将测量返回的buffer数据转换为HPS3D_MeasureData_t
* @param        handle 设备ID
* @see			HPS3D_MeasureData_t
* @note		    在回调函数中使用，将通知的数据转换为测量结构体
* @retval	    返回字节长度
*/
int HPS3D_ConvertToMeasureData(__OUT uint8_t *data, __IN HPS3D_MeasureData_t *resultData, __IN HPS3D_EventType_t Type);

/**
* @brief	     注册回调函数
* @param        eventHandle 自定义回调函数
* @param        userPara  自定义参数，可为空
* @see
* @note
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef	HPS3D_RegisterEventCallback(__IN HPS3DAPI_EVENT_CALLBACK eventHandle, __IN void *userPara);
	
/**
* @brief	     注销回调函数
* @param        handle 设备ID
* @see
* @note
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef	HPS3D_UnregisterEventCallback();

/**
* @brief	     获取设备版本信息
* @param        handle 设备ID
* @see
* @note
* @retval	     返回设备版本信息
*/
const uint8_t*	 HPS3D_GetDeviceVersion(__IN int handle);
	
/**
* @brief	     获取SDK版本信息
* @param
* @see
* @note
* @retval	     返回SDK版本信息
*/
const uint8_t*	 HPS3D_GetSDKVersion();

/**
* @brief	     获取设备序列号
* @param        handle 设备ID
* @see
* @note
* @retval	     返回设备序列号
*/
const uint8_t*   HPS3D_GetSerialNumber(__IN int handle);

/**
* @brief	     设置用户自定义ID
* @param		 handle 设备ID
* @param        userID 用户自定义ID
* @see
* @note         支持范围 0-255
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef	HPS3D_SetDeviceUserID(__IN int handle, __IN uint8_t userID);
	
/**
* @brief	     设置ROI组ID
* @param		 handle 设备ID
* @param        groupID 组ID序号 范围是 0-15
* @see
* @note         如果该分组下没有设定ROI,测量数据包切换为深度数据包
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef	HPS3D_SetROIGroupID(__IN int handle, __IN uint8_t groupID);
	
/**
* @brief	     设置多机编号
* @param		 handle 设备ID
* @param        CameraCode 编号范围是 0-15
* @see
* @note         设定不同的多机编号,可解决设备间信号相互干扰
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef	HPS3D_SetMultiCameraCode(__IN int handle, __IN uint8_t CameraCode);
	
/**
* @brief	     从传感器导出当前配置
* @param		 handle 设备ID
* @param        settings 当前配置参数表
* @see
* @note
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef	HPS3D_ExportSettings(__IN int handle, __OUT HPS3D_DeviceSettings_t *settings);

/**
* @brief	     保存当前配置至传感器
* @param		 handle 设备ID
* @see
* @note
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef	HPS3D_SaveSettings(__IN int handle);

/**
* @brief	     设置距离滤波器
* @param		 handle 设备ID
* @param		 enable 开启或关闭
* @param		 K 滤波系数，范围0-1,
* @see
* @note         K值越小滤波效果越明显
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef	HPS3D_SetDistanceFilterConf(__IN int handle, __IN bool enable, __IN float K);

/**
* @brief	     设置平滑滤波器
* @param		 handle 设备ID
* @param		 type  0:关闭滤波器  1:平均滤波  2:高斯滤波
* @param		 args  滤波参数 参考值为2、3
* @see
* @note         args值越大滤波效果越明显
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef	HPS3D_SetSmoothFilterConf(__IN int handle, __IN HPS3D_SmoothFilterType_t type, __IN int args);

/**
* @brief	     设置距离补偿值
* @param		 handle 设备ID
* @param		 offset 补偿的距离值
* @see
* @note         offset 为正表示原基础上加补偿值，否则相减
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef	HPS3D_SetDistanceOffset(__IN int handle, __IN int16_t offset);

/**
* @brief	     设置光程补偿
* @param		 handle 设备ID
* @param		 enbale 1 表示开启光程补偿  0表示关闭
* @see
* @note         光程补偿可将斜线距离转换为垂直距离
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef HPS3D_SetOpticalPathCalibration(__IN int handle, __IN bool enbale);

/**
 * @brief	     开启/关闭边缘滤波
 * @param		 handle 设备ID
 * @param		 enbale 1 表示开启  0表示关闭
 * @see
 * @note         可滤除部分边缘噪声
 * @retval	     成功返回1
 */

HPS3D_StatusTypeDef HPS3D_SetEdgeFilterEnable(__IN int handle, __IN bool enbale);
/**
* @brief	     为测量结果缓冲区分配内存
* @param		 data
* @see			 HPS3D_MeasureData_t
* @note
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef HPS3D_MeasureDataInit(__IN HPS3D_MeasureData_t *data);

/**
* @brief	     释放内存
* @param		 data
* @see			 HPS3D_MeasureData_t
* @note
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef HPS3D_MeasureDataFree(__IN HPS3D_MeasureData_t *data);

#ifdef __cplusplus
}
#endif

#endif //__HPS3D_USER_IF_H__
