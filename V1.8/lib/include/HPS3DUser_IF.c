#include "HPS3DUser_IF.h"

#ifdef _WIN32 /*windows*/

#else
#include <stddef.h>
#include<stdlib.h>
#endif

/**
* @brief	     USB设备连接
* @param        portName端口号/设备名(Linux)
* @param		 deviceHandler 返回的设备ID
* @see
* @note
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef HPS3D_USBConnectDevice(__IN char* portName, __OUT int* deviceHandler)
{
	return (HPS3D_StatusTypeDef)HPS3DAPI_USBConnectDevice(portName, deviceHandler);
}

/**
* @brief	     Ethernet设备连接
* @param        controllerIp 控制器IP
* @param        controllerPort 控制器端口
* @param		 deviceHandler 返回的设备ID
* @see
* @note
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef HPS3D_EthernetConnectDevice(__IN char* controllerIp, __IN uint16_t controllerPort, __OUT int* deviceHandler)
{
	return (HPS3D_StatusTypeDef)HPS3DAPI_EthernetConnectDevice(controllerIp, controllerPort, deviceHandler);
}

/**
* @brief	     Ethernet设备重连
* @param		 deviceHandler 设备ID
* @see
* @note
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef HPS3D_EthternetReconnection(__IN int handle)
{
	return (HPS3D_StatusTypeDef)HPS3DAPI_EthernetReconnectDevice(handle);
}

/**
* @brief	     关闭设备
* @param        handle 设备ID
* @see
* @note
* @retval	     成功返回 1
*/
HPS3D_StatusTypeDef HPS3D_CloseDevice(__IN int handle)
{
	return (HPS3D_StatusTypeDef)HPS3DAPI_CloseDevice(handle);
}

/**
* @brief	     设备连接状态
* @param        handle 设备ID
* @see
* @note
* @retval	     已连接返回true
*/
bool HPS3D_IsConnect(__IN int handle)
{
	return HPS3DAPI_IsConnect(handle) == 1 ? true : false;
}

/**
* @brief	     设备连续测量状态
* @param        handle 设备ID
* @see
* @note
* @retval	     连续测量模式返回true
*/
bool HPS3D_IsStart(__IN int handle)
{
	return HPS3DAPI_IsStart(handle) == 1 ? true : false;
}

/**
* @brief	     开始连续采集
* @param        handle 设备ID
* @see			 HPS3DAPI_EVENT_CALLBACK
* @note		 测量结果使用回调函数通知返回
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef HPS3D_StartCapture(__IN int handle)
{
	return (HPS3D_StatusTypeDef)HPS3DAPI_StartCapture(handle);
}

/**
* @brief	     停止采集
* @param        handle 设备ID
* @see
* @note
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef HPS3D_StopCapture(__IN int handle)
{
	return (HPS3D_StatusTypeDef)HPS3DAPI_StopCapture(handle);
}

/**
* @brief	     单次采集
* @param        handle 设备ID
* @param        type 返回包类型
* @param        data 测量数据
* @see
* @note         测量数据需根据type类型进行选择
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef HPS3D_SingleCapture(__IN int handle, __OUT HPS3D_EventType_t *type, __OUT HPS3D_MeasureData_t *data)
{
	HPS3D_StatusTypeDef ret = HPS3D_RET_OK;
	do
	{
		uint8_t *ret_data = NULL;
		int dataLen = 0;
		ret = (HPS3D_StatusTypeDef)HPS3DAPI_SingleCapture(handle, (int *)type, (uint8_t **)&ret_data,&dataLen);
		if (ret != HPS3D_RET_OK)
		{
			break;
		}
		switch ((HPS3D_EventType_t)*type)
		{
			case HPS3D_SIMPLE_ROI_EVEN:
			case HPS3D_FULL_ROI_EVEN:
			case HPS3D_FULL_DEPTH_EVEN:
			case HPS3D_SIMPLE_DEPTH_EVEN:
				dataLen = HPS3D_ConvertToMeasureData(ret_data, data, *type);
				break;
			default:
				ret = HPS3D_RET_PACKET_ERR;
				break;
		}
	} while (0);

	return ret;
}

/**
* @brief	    将测量返回的buffer数据转换为HPS3D_MeasureData_t
* @param        handle 设备ID
* @see			HPS3D_MeasureData_t
* @note		    在回调函数中使用，将通知的数据转换为测量结构体
* @retval	    返回字节长度
*/
int HPS3D_ConvertToMeasureData(__IN uint8_t *data, __OUT HPS3D_MeasureData_t *resultData, __IN HPS3D_EventType_t Type)
{
	int len = 0;
	if (Type == HPS3D_SIMPLE_ROI_EVEN)
	{
		int num = (int)data[0];
		int i = 0;
		for (i = 0; i < num; i++)
		{
			resultData->simple_roi_data[i].roi_num = data[len++];
			resultData->simple_roi_data[i].group_id = data[len++];
			resultData->simple_roi_data[i].roi_id = data[len++];
			resultData->simple_roi_data[i].threshold_state = data[len++];

			resultData->simple_roi_data[i].distance_average = data[len++] << 8;
			resultData->simple_roi_data[i].distance_average += data[len++];

			resultData->simple_roi_data[i].distance_min = data[len++] << 8;
			resultData->simple_roi_data[i].distance_min += data[len++];

			resultData->simple_roi_data[i].saturation_count = data[len++] << 8;
			resultData->simple_roi_data[i].saturation_count += data[len++];

			resultData->simple_roi_data[i].frame_cnt = data[len++] << 24;
			resultData->simple_roi_data[i].frame_cnt += data[len++] << 16;
			resultData->simple_roi_data[i].frame_cnt += data[len++] << 8;
			resultData->simple_roi_data[i].frame_cnt += data[len++];
		}
	}
	else if (Type == HPS3D_FULL_ROI_EVEN)
	{
		int num = (int)data[0];
		int i = 0;
		for (i = 0; i < num; i++)
		{
			resultData->full_roi_data[i].roi_num = data[len++];
			resultData->full_roi_data[i].group_id = data[len++];
			resultData->full_roi_data[i].roi_id = data[len++];
			resultData->full_roi_data[i].threshold_state = data[len++];

			resultData->full_roi_data[i].left_top_x = data[len++] << 8;
			resultData->full_roi_data[i].left_top_x += data[len++];
			resultData->full_roi_data[i].left_top_y = data[len++] << 8;
			resultData->full_roi_data[i].left_top_y += data[len++];
			resultData->full_roi_data[i].right_bottom_x = data[len++] << 8;
			resultData->full_roi_data[i].right_bottom_x += data[len++];
			resultData->full_roi_data[i].right_bottom_y = data[len++] << 8;
			resultData->full_roi_data[i].right_bottom_y += data[len++];

			resultData->full_roi_data[i].distance_average = data[len++] << 8;
			resultData->full_roi_data[i].distance_average += data[len++];
			resultData->full_roi_data[i].distance_min = data[len++] << 8;
			resultData->full_roi_data[i].distance_min += data[len++];
			resultData->full_roi_data[i].saturation_count = data[len++] << 8;
			resultData->full_roi_data[i].saturation_count += data[len++];

			resultData->full_roi_data[i].pixel_number = data[len++] << 24;
			resultData->full_roi_data[i].pixel_number += data[len++] << 16;
			resultData->full_roi_data[i].pixel_number += data[len++] << 8;
			resultData->full_roi_data[i].pixel_number += data[len++];

			resultData->full_roi_data[i].frame_cnt = data[len++] << 24;
			resultData->full_roi_data[i].frame_cnt += data[len++] << 16;
			resultData->full_roi_data[i].frame_cnt += data[len++] << 8;
			resultData->full_roi_data[i].frame_cnt += data[len++];


			int pixNum = resultData->full_roi_data[i].pixel_number;
			int j = 0;
			for (j = 0; j < resultData->full_roi_data[i].pixel_number; j++)
			{
				resultData->full_roi_data[i].distance[j] = data[len++] << 8;
				resultData->full_roi_data[i].distance[j] += data[len++];
			}

			
			
		}
	}
	else if (Type == HPS3D_SIMPLE_DEPTH_EVEN)
	{
		resultData->simple_depth_data.distance_average = data[len++] << 8;
		resultData->simple_depth_data.distance_average += data[len++];
		resultData->simple_depth_data.distance_min = data[len++] << 8;
		resultData->simple_depth_data.distance_min += data[len++];
		resultData->simple_depth_data.saturation_count = data[len++] << 8;
		resultData->simple_depth_data.saturation_count += data[len++];

		resultData->simple_depth_data.frame_cnt = data[len++] << 24;
		resultData->simple_depth_data.frame_cnt += data[len++] << 16;
		resultData->simple_depth_data.frame_cnt += data[len++] << 8;
		resultData->simple_depth_data.frame_cnt += data[len++];
	}
	else if (Type == HPS3D_FULL_DEPTH_EVEN)
	{
		resultData->full_depth_data.distance_average = data[len++] << 8;
		resultData->full_depth_data.distance_average += data[len++];
		resultData->full_depth_data.distance_min = data[len++] << 8;
		resultData->full_depth_data.distance_min += data[len++];
		resultData->full_depth_data.saturation_count = data[len++] << 8;
		resultData->full_depth_data.saturation_count += data[len++];


		resultData->full_depth_data.frame_cnt = data[len++] << 24;
		resultData->full_depth_data.frame_cnt += data[len++] << 16;
		resultData->full_depth_data.frame_cnt += data[len++] << 8;
		resultData->full_depth_data.frame_cnt += data[len++];


		resultData->full_depth_data.point_cloud_data.width  = data[len++] << 8;
		resultData->full_depth_data.point_cloud_data.width += data[len++];
		resultData->full_depth_data.point_cloud_data.height = data[len++] << 8;
		resultData->full_depth_data.point_cloud_data.height += data[len++];
		resultData->full_depth_data.point_cloud_data.points = data[len++] << 8;
		resultData->full_depth_data.point_cloud_data.points += data[len++];

		
		int MAX_PIX_NUM = 9600;
		int point_start = len + MAX_PIX_NUM * 2;
		int x = 0, y = 0, z = 0;
		int i = 0;
		for (i = 0; i < MAX_PIX_NUM; i++)
		{
			resultData->full_depth_data.distance[i] = data[len++] << 8;
			resultData->full_depth_data.distance[i] += data[len++];

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
			resultData->full_depth_data.point_cloud_data.point_data[i].x = (float)(x / 100.0);
			resultData->full_depth_data.point_cloud_data.point_data[i].y = (float)(y / 100.0);
			resultData->full_depth_data.point_cloud_data.point_data[i].z = (float)(z / 100.0);
		}

		len = len + 14 * MAX_PIX_NUM;
	}
	return len;
}

/**
* @brief	     注册回调函数
* @param        eventHandle 自定义回调函数
* @param        userPara  自定义参数，可为空
* @see
* @note
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef HPS3D_RegisterEventCallback(__IN HPS3DAPI_EVENT_CALLBACK eventHandle, __IN void *userPara)
{
	return (HPS3D_StatusTypeDef)HPS3DAPI_RegisterEventCallback(eventHandle, userPara);
}

/**
* @brief	     注销回调函数
* @param        handle 设备ID
* @see
* @note
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef HPS3D_UnregisterEventCallback()
{
	return (HPS3D_StatusTypeDef)HPS3DAPI_UnregisterEventCallback();
}

/**
* @brief	     获取设备版本信息
* @param        handle 设备ID
* @see
* @note
* @retval	     返回设备版本信息
*/
const uint8_t* HPS3D_GetDeviceVersion(__IN int handle)
{
	return HPS3DAPI_GetDeviceVersion(handle);
}

/**
* @brief	     获取SDK版本信息
* @param
* @see
* @note
* @retval	     返回SDK版本信息
*/
const uint8_t* HPS3D_GetSDKVersion()
{
	return HPS3DAPI_GetSDKVersion();
}

/**
* @brief	     获取设备序列号
* @param        handle 设备ID
* @see
* @note
* @retval	     返回设备序列号
*/
const uint8_t* HPS3D_GetSerialNumber(__IN int handle)
{
	return HPS3DAPI_GetSerialNumber(handle);
}

/**
* @brief	     设置用户自定义ID
* @param		 handle 设备ID
* @param        userID 用户自定义ID
* @see
* @note         支持范围 0-255
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef HPS3D_SetDeviceUserID(__IN int handle, __IN uint8_t userID)
{
	return (HPS3D_StatusTypeDef)HPS3DAPI_SetDeviceUserID(handle,userID);
}

/**
* @brief	     设置ROI组ID
* @param		 handle 设备ID
* @param        groupID 组ID序号 范围是 0-15
* @see
* @note         如果该分组下没有设定ROI,测量数据包切换为深度数据包
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef HPS3D_SetROIGroupID(__IN int handle, __IN uint8_t groupID)
{
	return (HPS3D_StatusTypeDef)HPS3DAPI_SetROIGroupID(handle, groupID);
}

/**
* @brief	     设置多机编号
* @param		 handle 设备ID
* @param        CameraCode 编号范围是 0-15
* @see
* @note         设定不同的多机编号,可解决设备间信号相互干扰
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef HPS3D_SetMultiCameraCode(__IN int handle, __IN uint8_t CameraCode)
{
	return (HPS3D_StatusTypeDef)HPS3DAPI_SetMultiCameraCode(handle, CameraCode);
}

/**
* @brief	     从传感器导出当前配置
* @param		 handle 设备ID
* @param        settings 当前配置参数表
* @see
* @note
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef HPS3D_ExportSettings(__IN int handle, __OUT HPS3D_DeviceSettings_t *settings)
{
	return (HPS3D_StatusTypeDef)HPS3DAPI_ExportSettings(handle, (uint8_t *)settings);
}

/**
* @brief	     保存当前配置至传感器
* @param		 handle 设备ID
* @see
* @note
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef HPS3D_SaveSettings(__IN int handle)
{
	return (HPS3D_StatusTypeDef)HPS3DAPI_SaveSettings(handle);
}

/**
* @brief	     设置距离滤波器
* @param		 handle 设备ID
* @param		 enable 开启或关闭
* @param		 K 滤波系数，范围0-1,
* @see
* @note         K值越小滤波效果越明显
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef HPS3D_SetDistanceFilterConf(__IN int handle, __IN bool enable, __IN float K)
{
	return (HPS3D_StatusTypeDef)HPS3DAPI_SetDistanceFilterConf(handle, enable==true ?1:0, K);
}

/**
* @brief	     设置平滑滤波器
* @param		 handle 设备ID
* @param		 type  0:关闭滤波器  1:平均滤波  2:高斯滤波
* @param		 args  滤波参数 参考值为2、3
* @see
* @note         args值越大滤波效果越明显
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef HPS3D_SetSmoothFilterConf(__IN int handle, __IN HPS3D_SmoothFilterType_t type, __IN int args)
{
	return (HPS3D_StatusTypeDef)HPS3DAPI_SetSmoothFilterConf(handle, (int)type, args);
}

/**
* @brief	     设置距离补偿值
* @param		 handle 设备ID
* @param		 offset 补偿的距离值
* @see
* @note         offset 为正表示原基础上加补偿值，否则相减
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef HPS3D_SetDistanceOffset(__IN int handle, __IN int16_t offset)
{
	return (HPS3D_StatusTypeDef)HPS3DAPI_SetDistanceOffset(handle, offset);
}

/**
* @brief	     设置光程补偿
* @param		 handle 设备ID
* @param		 enbale 1 表示开启光程补偿  0表示关闭
* @see
* @note          光程补偿可将斜线距离转换为垂直距离
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef HPS3D_SetOpticalPathCalibration(__IN int handle, __IN bool enbale)
{
	return (HPS3D_StatusTypeDef)HPS3DAPI_SetOpticalPathCalibration(handle, enbale);
}

/**
 * @brief	     开启/关闭边缘滤波
 * @param		 handle 设备ID
 * @param		 enbale 1 表示开启  0表示关闭
 * @see
 * @note         可滤除部分边缘噪声
 * @retval	     成功返回1
 */
HPS3D_StatusTypeDef HPS3D_SetEdgeFilterEnable(__IN int handle, __IN bool enbale)
{
	return (HPS3D_StatusTypeDef)HPS3DAPI_SetEdgeFilterEnable(handle, enbale);
}

/**
* @brief	     为测量结果缓冲区分配内存
* @param		 data
* @see			 HPS3D_MeasureData_t
* @note
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef HPS3D_MeasureDataInit(__IN HPS3D_MeasureData_t *data)
{
	HPS3D_StatusTypeDef ret = HPS3D_RET_OK;

	data->full_depth_data.point_cloud_data.point_data = NULL;
	uint32_t i = 0;
	do
	{
		//分配ROI内存
		data->full_roi_data = NULL;
		data->full_roi_data = (HPS3D_FullRoiData_t *)malloc(sizeof(HPS3D_FullRoiData_t) * HPS3D_MAX_ROI_NUMBER);
		if (data->full_roi_data == NULL)
		{
			ret = HPS3D_RET_BUFF_EMPTY;
			break;
		}
		for (i = 0; i < HPS3D_MAX_ROI_NUMBER; i++)
		{
			data->full_roi_data[i].distance = NULL;
			data->full_roi_data[i].distance = (uint16_t *)malloc(sizeof(uint16_t) * HPS3D_MAX_PIXEL_NUMBER);
			if (data->full_roi_data[i].distance == NULL)
			{
				ret = HPS3D_RET_BUFF_EMPTY;
				break;
			}
		}

		data->simple_roi_data = NULL;
		data->simple_roi_data = (HPS3D_SimpleRoiData_t *)malloc(sizeof(HPS3D_SimpleRoiData_t) * HPS3D_MAX_ROI_NUMBER);
		if (data->simple_roi_data == NULL)
		{
			ret = HPS3D_RET_BUFF_EMPTY;
			break;
		}

		/*完整深度数据*/
		data->full_depth_data.distance = NULL;
		data->full_depth_data.distance = (uint16_t *)malloc(sizeof(uint16_t)* HPS3D_MAX_PIXEL_NUMBER);
		if (data->full_depth_data.distance == NULL)
		{
			ret = HPS3D_RET_BUFF_EMPTY;
			break;
		}


		/*点云数据分配*/
		data->full_depth_data.point_cloud_data.point_data = (HPS3D_PerPointCloudData_t *)malloc(sizeof(HPS3D_PerPointCloudData_t)*HPS3D_MAX_PIXEL_NUMBER);
		if (data->full_depth_data.point_cloud_data.point_data == NULL)
		{
			ret = HPS3D_RET_BUFF_EMPTY;
			break;
		}

	} while (0);

	return ret;
}

/**
* @brief	     释放内存
* @param		 data
* @see			 HPS3D_MeasureData_t
* @note
* @retval	     成功返回 HPS3D_RET_OK
*/
HPS3D_StatusTypeDef HPS3D_MeasureDataFree(__IN HPS3D_MeasureData_t *data)
{
	HPS3D_StatusTypeDef ret = HPS3D_RET_OK;
	uint32_t i = 0;
	do
	{
		for (i = 0; i < HPS3D_MAX_ROI_NUMBER; i++)
		{
			if (data->full_roi_data[i].distance != NULL)
			{
				free(data->full_roi_data[i].distance);
			}
		}
		if (data->full_roi_data != NULL)
		{
			free(data->full_roi_data);
		}
		if (data->simple_roi_data != NULL)
		{
			free(data->simple_roi_data);
		}

		if (data->full_depth_data.distance != NULL)
		{
			free(data->full_depth_data.distance);
		}

		if (data->full_depth_data.point_cloud_data.point_data != NULL)
		{
			free(data->full_depth_data.point_cloud_data.point_data);
		}
	} while (0);
	return ret;
}
