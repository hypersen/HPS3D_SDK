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

#ifndef __HPS3D_BASE_IF_H_
#define __HPS3D_BASE_IF_H_

#ifdef __cplusplus
extern "C"  /*C++*/
{
#endif

#include <stdint.h>
#ifdef _WIN32 /*windows*/

#ifndef _HPS3D_API
	#define _HPS3D_API extern  _declspec(dllexport)
	#else
	#define _HPS3D_API  extern _declspec(dllimport)
	#endif


#include <WinSock2.h>

#else  /*linux*/
	#define __stdcall  
	#define __cdecl  
	#define _HPS3D_API extern
#endif

#ifdef __cplusplus
}
#endif

#define     __IN
#define     __OUT
  
#define    HPS3D_MAX_ROI_NUMBER   (8)     /*支持最大ROI数量*/
#define    HPS3D_MAX_PIXEL_NUMBER (9600)  /*最大像素点数 160*60*/

#define	 	HPS3D_LOW_AMPLITUDE   	(65300) 						/*信号幅值低*/
#define	  	HPS3D_SATURATION 		(65400)     					/*饱和位饱和*/
#define	 	HPS3D_ADC_OVERFLOW  	(65500)   						/*ADC溢出*/
#define	 	HPS3D_INVALID_DATA 		(65530)    						/*无效数据*/
/**
 * @brief	     事件回调函数
 * @param        userPara 可为空
 * @see			
 * @note	     接收API异常输出、测量返回包等
 * @retval	     成功返回 1
 */
typedef void(__stdcall *HPS3DAPI_EVENT_CALLBACK)(int handle, int eventType, uint8_t *data,int dataLen, void *userPara);

/**
 * @brief	     USB设备连接
 * @param        portName端口号/设备名(Linux)
 * @param		 deviceHandler 返回的设备ID
 * @see
 * @note	     
 * @retval	     成功返回 1
 */
_HPS3D_API int			__stdcall HPS3DAPI_USBConnectDevice(__IN char* portName, __OUT int* deviceHandler);

/**
 * @brief	     Ethernet设备连接
 * @param        controllerIp 控制器IP
 * @param        controllerPort 控制器端口
 * @param		 deviceHandler 返回的设备ID
 * @see
 * @note	     
 * @retval	     成功返回 1
 */
_HPS3D_API int			__stdcall HPS3DAPI_EthernetConnectDevice(__IN char* controllerIp, __IN uint16_t controllerPort, __OUT int* deviceHandler);

/**
 * @brief	     Ethernet设备重连
 * @param		 deviceHandler 设备ID
 * @see
 * @note
 * @retval	     成功返回 1
 */
_HPS3D_API int			__stdcall HPS3DAPI_EthernetReconnectDevice(__IN int deviceHandler);

/**
 * @brief	     关闭设备
 * @param        handle 设备ID
 * @see
 * @note
 * @retval	     成功返回 1
 */
_HPS3D_API int			__stdcall HPS3DAPI_CloseDevice(__IN int handle);


/**
 * @brief	     以太网设备keep alive 时间
 * @param        handle 设备ID
 * @param        keepTime_ms  保活时间，单位ms
 * @see
 * @note
 * @retval	     成功返回 1
 */
_HPS3D_API int			__stdcall HPS3DAPI_SetEthernetKeepAlive(__IN int handle, __IN int keepTime_ms);

/**
 * @brief	     设备连接状态
 * @param        handle 设备ID
 * @see
 * @note
 * @retval	     已连接返回1
 */
_HPS3D_API int			__stdcall HPS3DAPI_IsConnect(__IN int handle);

/**
 * @brief	     设备连续测量状态
 * @param        handle 设备ID
 * @see
 * @note
 * @retval	     连续测量模式返回1
 */
_HPS3D_API int			__stdcall HPS3DAPI_IsStart(__IN int handle);

/**
 * @brief	     开始连续采集
 * @param        handle 设备ID
 * @see			 HPS3DAPI_EVENT_CALLBACK
 * @note		 测量结果使用回调函数通知返回
 * @retval	     成功返回1
 */
_HPS3D_API int			__stdcall HPS3DAPI_StartCapture(__IN int handle);

/**
 * @brief	     停止采集
 * @param        handle 设备ID
 * @see			 
 * @note		 
 * @retval	     成功返回1
 */
_HPS3D_API int			__stdcall HPS3DAPI_StopCapture(__IN int handle);

/**
 * @brief	     单次采集
 * @param        handle 设备ID
 * @see
 * @note
 * @retval	     成功返回1
 */
_HPS3D_API int			__stdcall HPS3DAPI_SingleCapture(__IN int handle, __OUT int *type, __OUT uint8_t **data, __OUT int *dataLen);

/**
 * @brief	     注册回调函数
 * @param        eventHandle 自定义回调函数
 * @param        userPara  自定义参数，可为空
 * @see
 * @note
 * @retval	     成功返回1
 */
_HPS3D_API int			__stdcall HPS3DAPI_RegisterEventCallback(__IN HPS3DAPI_EVENT_CALLBACK eventHandle, __IN void *userPara);

/**
 * @brief	     注销回调函数
 * @param        handle 设备ID      
 * @see
 * @note
 * @retval	     成功返回1
 */
_HPS3D_API int			__stdcall HPS3DAPI_UnregisterEventCallback();

/**
 * @brief	     获取设备版本信息
 * @param        handle 设备ID
 * @see
 * @note
 * @retval	     返回设备版本信息
 */
_HPS3D_API const uint8_t*	__stdcall HPS3DAPI_GetDeviceVersion(__IN int handle);

/**
 * @brief	     获取SDK版本信息
 * @param        
 * @see
 * @note
 * @retval	     返回SDK版本信息
 */
_HPS3D_API const uint8_t*	__stdcall HPS3DAPI_GetSDKVersion();

/**
 * @brief	     获取设备序列号
 * @param        handle 设备ID
 * @see
 * @note
 * @retval	     返回设备序列号
 */
_HPS3D_API const uint8_t*	__stdcall HPS3DAPI_GetSerialNumber(__IN int handle);

/**
 * @brief	     设置用户自定义ID
 * @param		 handle 设备ID
 * @param        userID 用户自定义ID
 * @see
 * @note         支持范围 0-255
 * @retval	     成功返回1
 */
_HPS3D_API int			__stdcall HPS3DAPI_SetDeviceUserID(__IN int handle, __IN uint8_t userID);

/**
 * @brief	     设置ROI组ID
 * @param		 handle 设备ID
 * @param        groupID 组ID序号 范围是 0-15
 * @see
 * @note         如果该分组下没有设定ROI,测量数据包切换为深度数据包
 * @retval	     成功返回1
 */
_HPS3D_API int			__stdcall HPS3DAPI_SetROIGroupID(__IN int handle, __IN uint8_t groupID);

/**
 * @brief	     设置多机编号
 * @param		 handle 设备ID
 * @param        CameraCode 编号范围是 0-15
 * @see
 * @note         设定不同的多机编号,可解决设备间信号相互干扰
 * @retval	     成功返回1
 */
_HPS3D_API int			__stdcall HPS3DAPI_SetMultiCameraCode(__IN int handle, __IN uint8_t CameraCode);

/**
 * @brief	     从传感器导出当前配置
 * @param		 handle 设备ID
 * @param        settings 当前配置参数表
 * @see
 * @note         
 * @retval	     成功返回1
 */
_HPS3D_API int			__stdcall HPS3DAPI_ExportSettings(__IN int handle, __OUT uint8_t *settings);

/**
 * @brief	     保存当前配置至传感器
 * @param		 handle 设备ID
 * @see
 * @note
 * @retval	     成功返回1
 */
_HPS3D_API int			__stdcall HPS3DAPI_SaveSettings(__IN int handle);

/**
 * @brief	     设置距离滤波器
 * @param		 handle 设备ID
 * @param		 enable 开启或关闭
 * @param		 K 滤波系数，范围0-1,
 * @see
 * @note         K值越小滤波效果越明显
 * @retval	     成功返回1
 */
_HPS3D_API int			__stdcall HPS3DAPI_SetDistanceFilterConf(__IN int handle, __IN int enable, __IN float K);

/**
 * @brief	     设置平滑滤波器
 * @param		 handle 设备ID
 * @param		 type  0:关闭滤波器  1:平均滤波  2:高斯滤波
 * @param		 args  滤波参数 参考值为2、3
 * @see
 * @note         args值越大滤波效果越明显
 * @retval	     成功返回1
 */
_HPS3D_API int			__stdcall HPS3DAPI_SetSmoothFilterConf(__IN int handle, __IN int type, __IN int args);

/**
 * @brief	     设置距离补偿值
 * @param		 handle 设备ID
 * @param		 offset 补偿的距离值
 * @see
 * @note         offset 为正表示原基础上加补偿值，否则相减
 * @retval	     成功返回1
 */
_HPS3D_API int		    __stdcall HPS3DAPI_SetDistanceOffset(__IN int handle, __IN int16_t offset);

/**
 * @brief	     设置光程补偿
 * @param		 handle 设备ID
 * @param		 enbale 1 表示开启光程补偿  0表示关闭
 * @see
 * @note         光程补偿可将斜线距离转换为垂直距离
 * @retval	     成功返回1
 */
_HPS3D_API int		    __stdcall HPS3DAPI_SetOpticalPathCalibration(__IN int handle, __IN int enbale);

/**
 * @brief	     开启/关闭边缘滤波
 * @param		 handle 设备ID
 * @param		 enbale 1 表示开启  0表示关闭
 * @see
 * @note         可滤除部分边缘噪声
 * @retval	     成功返回1
 */
_HPS3D_API int		    __stdcall HPS3DAPI_SetEdgeFilterEnable(__IN int handle, __IN int enbale);

#endif  //__HPS3D_BASE_IF_H_

