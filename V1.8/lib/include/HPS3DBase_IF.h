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
	#define _HPS3D_API  _declspec(dllexport)
	#else
	#define _HPS3D_API  _declspec(dllimport)
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
  
#define    HPS3D_MAX_ROI_NUMBER   (8)     /*Support the maximum number of ROI*/
#define    HPS3D_MAX_PIXEL_NUMBER (9600)  /*max pixel number 160*60*/

/*Invalid data*/
#define	 	HPS3D_LOW_AMPLITUDE   	(65300) 						/*Low signal amplitude*/
#define	  	HPS3D_SATURATION 		(65400)     					/*Saturation bit saturation*/
#define	 	HPS3D_ADC_OVERFLOW  	(65500)   						/*ADC overflow*/
#define	 	HPS3D_INVALID_DATA 		(65530)    						/*Invalid data*/
/**
 * @brief	     Event callback function
 * @param        userPara Can be empty
 * @see			
 * @note	     Receive API exceptions, measurement return packages, etc.
 * @retval	     Successfully returned 1
 */
typedef void(__stdcall *HPS3DAPI_EVENT_CALLBACK)(int handle, int eventType, uint8_t *data,int dataLen, void *userPara);

/**
 * @brief	     USB Device connection
 * @param        portName Port number/device name(Linux)
 * @param		 deviceHandler: Return device ID
 * @see
 * @note	     
 * @retval	     Successfully returned 1
 */
_HPS3D_API int			__stdcall HPS3DAPI_USBConnectDevice(__IN char* portName, __OUT int* deviceHandler);

/**
 * @brief	     Ethernet Device connection
 * @param        controllerIp 
 * @param        controllerPort 
 * @param		 deviceHandler: Return device ID
 * @see
 * @note	     
 * @retval	     Successfully returned 1
 */
_HPS3D_API int			__stdcall HPS3DAPI_EthernetConnectDevice(__IN char* controllerIp, __IN uint16_t controllerPort, __OUT int* deviceHandler);

/**
 * @brief	     Close device
 * @param        handle: device ID
 * @see
 * @note
 * @retval	     Successfully returned 1
 */
_HPS3D_API int			__stdcall HPS3DAPI_CloseDevice(__IN int handle);

/**
 * @brief	     Device connection status
 * @param        handle: device ID
 * @see
 * @note
 * @retval	     Connected to return 1
 */
_HPS3D_API int			__stdcall HPS3DAPI_IsConnect(__IN int handle);

/**
 * @brief	     device continuous measurement status
 * @param        handle: device ID
 * @see
 * @note
 * @retval	     Continuous measurement mode returns 1
 */
_HPS3D_API int			__stdcall HPS3DAPI_IsStart(__IN int handle);

/**
 * @brief	     Start continuous capture
 * @param        handle: device ID
 * @see			 HPS3DAPI_EVENT_CALLBACK
 * @note		 The measurement result is returned using the callback function notification
 * @retval	     Successfully returned 1
 */
_HPS3D_API int			__stdcall HPS3DAPI_StartCapture(__IN int handle);

/**
 * @brief	     Stop capture
 * @param        handle: device ID
 * @see			 
 * @note		 
 * @retval	     Successfully returned 1
 */
_HPS3D_API int			__stdcall HPS3DAPI_StopCapture(__IN int handle);

/**
 * @brief	     Single Capture
 * @param        handle: device ID
 * @see
 * @note
 * @retval	     Successfully returned 1
 */
_HPS3D_API int			__stdcall HPS3DAPI_SingleCapture(__IN int handle, __OUT int *type, __OUT uint8_t **data, __OUT int *dataLen);

/**
 * @brief	     Register callback function
 * @param        eventHandle :Custom callback function
 * @param        userPara  :Custom parameter, can be empty
 * @see
 * @note
 * @retval	     Successfully returned 1
 */
_HPS3D_API int			__stdcall HPS3DAPI_RegisterEventCallback(__IN HPS3DAPI_EVENT_CALLBACK eventHandle, __IN void *userPara);

/**
 * @brief	     Logout callback function
 * @param        handle: device ID      
 * @see
 * @note
 * @retval	     Successfully returned 1
 */
_HPS3D_API int			__stdcall HPS3DAPI_UnregisterEventCallback();

/**
 * @brief	     Get device version information
 * @param        handle: device ID
 * @see
 * @note
 * @retval	     Return device version information
 */
_HPS3D_API const uint8_t*	__stdcall HPS3DAPI_GetDeviceVersion(__IN int handle);

/**
 * @brief	     Get SDK version information
 * @param        
 * @see
 * @note
 * @retval	     Return SDK version information
 */
_HPS3D_API const uint8_t*	__stdcall HPS3DAPI_GetSDKVersion();

/**
 * @brief	     Get device serial number
 * @param        handle: device ID
 * @see
 * @note
 * @retval	     Return device serial number
 */
_HPS3D_API const uint8_t*	__stdcall HPS3DAPI_GetSerialNumber(__IN int handle);

/**
 * @brief	     Set user-defined ID
 * @param		 handle: device ID
 * @param        userID 
 * @see
 * @note         userID range 0-255
 * @retval	     Successfully returned 1
 */
_HPS3D_API int			__stdcall HPS3DAPI_SetDeviceUserID(__IN int handle, __IN uint8_t userID);

/**
 * @brief	     Set ROI group ID
 * @param		 handle: device ID
 * @param        groupID :range is 0-15
 * @see
 * @note         If ROI is not set under this group, the measurement data packet is switched to the depth data packet
 * @retval	     Successfully returned 1
 */
_HPS3D_API int			__stdcall HPS3DAPI_SetROIGroupID(__IN int handle, __IN uint8_t groupID);

/**
 * @brief	     Set multi-camera code
 * @param		 handle: device ID
 * @param        CameraCode range is 0-15
 * @see
 * @note         Set different multi-camera code to solve the mutual interference of signals between devices
 * @retval	     Successfully returned 1
 */
_HPS3D_API int			__stdcall HPS3DAPI_SetMultiCameraCode(__IN int handle, __IN uint8_t CameraCode);

/**
 * @brief	     Export current configuration from sensor
 * @param		 handle: device ID
 * @param        settings :Current configuration parameter table
 * @see
 * @note         
 * @retval	     Successfully returned 1
 */
_HPS3D_API int			__stdcall HPS3DAPI_ExportSettings(__IN int handle, __OUT uint8_t *settings);

/**
 * @brief	     Save the current configuration to the sensor
 * @param		 handle: device ID
 * @see
 * @note
 * @retval	     Successfully returned 1
 */
_HPS3D_API int			__stdcall HPS3DAPI_SaveSettings(__IN int handle);

/**
 * @brief	     Set the distance filter
 * @param		 handle: device ID
 * @param		 enable: true or  false
 * @param		 K :Filter coefficient，range :0-1,
 * @see
 * @note         The smaller the K value, the more obvious the filtering effect
 * @retval	     Successfully returned 1
 */
_HPS3D_API int			__stdcall HPS3DAPI_SetDistanceFilterConf(__IN int handle, __IN int enable, __IN float K);

/**
 * @brief	     Set the smooth filter 
 * @param		 handle: device ID
 * @param		 type  0:disable  1:average filter  2: guass filter
 * @param		 args  Filter parameter reference value is 2, 3
 * @see
 * @note         The larger the args value, the more obvious the filtering effect
 * @retval	     Successfully returned 1
 */
_HPS3D_API int			__stdcall HPS3DAPI_SetSmoothFilterConf(__IN int handle, __IN int type, __IN int args);

/**
 * @brief	     Set the distance offset
 * @param		 handle: device ID
 * @param		 offset
 * @see
 * @note  
 * @retval	     Successfully returned 1
 */
_HPS3D_API int		    __stdcall HPS3DAPI_SetDistanceOffset(__IN int handle, __IN int16_t offset);

/**
 * @brief	     Set optical path compensation
 * @param		 handle: device ID
 * @param		 enbale: 1 or 0
 * @see
 * @note         Optical path compensation can convert oblique line distance to vertical distance
 * @retval	     Successfully returned 1
 */
_HPS3D_API int		    __stdcall HPS3DAPI_SetOpticalPathCalibration(__IN int handle, __IN int enbale);

#endif  //__HPS3D_BASE_IF_H_

