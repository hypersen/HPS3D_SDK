#include <iostream>
#include<tchar.h>
#include "HPS3D160_IF/HPS3DUser_IF.h"

//预先分配内存
static HPS3D_MeasureData_t g_measureData;

static bool PrintResultData(HPS3D_EventType_t type, HPS3D_MeasureData_t data)
{
	int num = 0;
	switch (type)
	{
	case HPS3D_SIMPLE_ROI_EVEN: //简单ROI数据包  不含每个点的深度数据
		printf("*************  HPS3D_SIMPLE_ROI_EVEN  ********************\n");
		num = data.simple_roi_data[0].roi_num;
		for (int i = 0; i < num; i++)
		{
			printf("  ********GroupID:%d  ROIID:%d  *******\n", data.simple_roi_data[i].group_id, data.simple_roi_data[i].roi_id);
			printf("    distance_average:%d\n", data.simple_roi_data[i].distance_average);
			printf("    distance_min    :%d\n", data.simple_roi_data[i].distance_min);
			printf("    saturation_count:%d\n", data.simple_roi_data[i].saturation_count);
			printf("    threshold_state :%d\n", data.simple_roi_data[i].threshold_state);
			printf("    =====================================\n\n");
		}
		break;
	case HPS3D_FULL_ROI_EVEN: //完整ROI数据包
		printf("*************  HPS3D_FULL_ROI_EVEN  ********************\n");
		num = data.full_roi_data[0].roi_num;
		for (int i = 0; i < num; i++)
		{
			printf("  ********GroupID:%d  ROIID:%d  *******\n", data.full_roi_data[i].group_id, data.full_roi_data[i].roi_id);
			printf("    ROI Left Top    :(%d,%d)\n", data.full_roi_data[i].left_top_x, data.full_roi_data[i].left_top_y);
			printf("    ROI Right Bottom:(%d,%d)\n", data.full_roi_data[i].right_bottom_x, data.full_roi_data[i].right_bottom_y);
			printf("    ROI Pixel Number:%d\n", data.full_roi_data[i].pixel_number);
			printf("    distance_average:%d\n", data.full_roi_data[i].distance_average);
			printf("    distance_min    :%d\n", data.full_roi_data[i].distance_min);
			printf("    saturation_count:%d\n", data.full_roi_data[i].saturation_count);
			printf("    threshold_state :%d\n", data.full_roi_data[i].threshold_state);
			printf("    =====================================\n\n");
		}
		break;
	case HPS3D_SIMPLE_DEPTH_EVEN: //简单深度数据包，不含每个点距离及点云数据
		printf("*************  HPS3D_SIMPLE_DEPTH_EVEN  ********************\n");
		printf(" distance_average:%d\n", data.simple_depth_data.distance_average);
		printf(" distance_min    :%d\n", data.simple_depth_data.distance_min);
		printf(" saturation_count:%d\n", data.simple_depth_data.saturation_count);
		printf("==========================================================\n\n");
		break;
	case HPS3D_FULL_DEPTH_EVEN: //完整深度图数据包，含点云数据
		printf("*************  HPS3D_FULL_DEPTH_EVEN    ********************\n");
		printf("distance_average:%d\n", data.full_depth_data.distance_average);
		printf("distance_min    :%d\n", data.full_depth_data.distance_min);
		printf("saturation_count:%d\n", data.full_depth_data.saturation_count);

		printf("distance[0]     :%d\n", data.full_depth_data.distance[0]);
		printf("pointCloud[0]   :(%f,%f.%f)\n", data.full_depth_data.point_cloud_data.point_data[0].x,
			data.full_depth_data.point_cloud_data.point_data[0].y, data.full_depth_data.point_cloud_data.point_data[0].z);

		printf("distance[1]     :%d\n", data.full_depth_data.distance[1]);
		printf("pointCloud[1]   :(%f,%f.%f)\n", data.full_depth_data.point_cloud_data.point_data[1].x,
			data.full_depth_data.point_cloud_data.point_data[1].y, data.full_depth_data.point_cloud_data.point_data[1].z);

		printf("==========================================================\n\n");
		break;
	default:
		break;
	}

	return true;
}

static void EventCallBackFunc(int handle, int eventType, uint8_t *data, int dataLen, void *userPara)
{
	switch ((HPS3D_EventType_t)eventType)
	{
		//测量数据通知事件
	case HPS3D_SIMPLE_ROI_EVEN:
	case HPS3D_FULL_ROI_EVEN:
	case HPS3D_FULL_DEPTH_EVEN:
	case HPS3D_SIMPLE_DEPTH_EVEN:
		HPS3D_ConvertToMeasureData(data, &g_measureData, (HPS3D_EventType_t)eventType);
		PrintResultData((HPS3D_EventType_t)eventType, g_measureData);
		break;
	case HPS3D_SYS_EXCEPTION_EVEN: /*系统异常通知事件*/
		printf("SYS ERR :%s\n", data);
		break;
	case HPS3D_DISCONNECT_EVEN: /*连接异常断开通知事件*/
		printf("Device disconnected!\n");
		HPS3D_CloseDevice(handle);
		HPS3D_MeasureDataFree(&g_measureData);
		break;
	case HPS3D_NULL_EVEN:  //空事件通知
	default:
		break;
	}
}

int main()
{
	printf("HPS3D160 C/C++ Demo (Visual Statudio 2017)\n\n");

	printf("SDK Ver:%s\n", HPS3D_GetSDKVersion());

	//内存分配
	HPS3D_MeasureDataInit(&g_measureData);

	int handle = -1;
	HPS3D_StatusTypeDef ret = HPS3D_RET_OK;
	do
	{
		printf("选择设备类型: HPS3D160-U(1)  HPS3D160-L(2)  退出(其他)\n");
		char sel = getchar();
		getchar(); //过滤回车
		if (sel == '1')
		{
			ret = HPS3D_USBConnectDevice((char *)_T("COM3"), &handle);
		}
		else if (sel == '2')
		{
			ret = HPS3D_EthernetConnectDevice((char *)"192.168.0.10", 12345, &handle);
		}
		else
		{
			return 0;
		}
		if (ret != HPS3D_RET_OK)
		{
			printf("设备连接失败,Err:%d\n", ret);
			break;
		}


		//注册事件回调函数，用于接收连续返回数据包，及调用异常等;
		HPS3D_RegisterEventCallback(EventCallBackFunc, NULL);

		printf("设备版本为:%s\n", HPS3D_GetDeviceVersion(handle));
		printf("设备序列号:%s\n\n", HPS3D_GetSerialNumber(handle));

		HPS3D_DeviceSettings_t settings;
		ret = HPS3D_ExportSettings(handle, &settings);
		if (ret != HPS3D_RET_OK)
		{
			printf("导出设备参数失败,Err:%d\n", ret);
			break;
		}
		printf("分辨率为:%d X %d\n", settings.max_resolution_X, settings.max_resolution_Y);
		printf("支持最大ROI分组数量为:%d  当前ROI分组：%d\n", settings.max_roi_group_number, settings.cur_group_id);
		printf("支持最大ROI数量为:%d\n", settings.max_roi_number);
		printf("支持最大多机编号为:%d，当前设备多机编号:%d\n", settings.max_multiCamera_code, settings.cur_multiCamera_code);
		printf("当前设备用户ID为：%d\n", settings.user_id);
		printf("光路补偿是否开启: %d\n\n", settings.optical_path_calibration);

		bool isContinuous = false;
		do
		{
			printf("选择测量模式: 单次测量(1)  连续测量(2)  退出(其他)\n");
			char sel = getchar();
			getchar(); //过滤回车
			if (sel == '1')
			{
				//单次测量模式
				HPS3D_EventType_t type = HPS3D_NULL_EVEN;
				ret = HPS3D_SingleCapture(handle, &type, &g_measureData);
				if (ret != HPS3D_RET_OK)
				{
					printf("单次测量失败,Err:%d\n", ret);
					break;
				}
				PrintResultData(type, g_measureData);
			}
			else if (sel == '2')
			{
				isContinuous = true;
				HPS3D_StartCapture(handle);
				break;
			}
			else
			{
				isContinuous = false;
				break;
			}
		} while (1);

		if (isContinuous)
		{
			while (1)
			{
				Sleep(10);
			}
		}
	} while (0);

	HPS3D_StopCapture(handle);
	HPS3D_CloseDevice(handle);
	HPS3D_MeasureDataFree(&g_measureData);
	system("pause");
}


