#include "ros/ros.h"//ros
#include "../include/HPS3DUser_IF.h"//hps3d160 interface
#include <sstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
// PCL specific includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

int g_handle = -1;
static HPS3D_MeasureData_t g_measureData;
ros::Publisher camera_pub;//Global variable, because the observer callback function needs to be used

static bool PrintResultData(HPS3D_EventType_t type, HPS3D_MeasureData_t data)
{
	int num = 0;
	int i = 0;
	pcl::PointCloud<pcl::PointXYZ> cloud;
	sensor_msgs::PointCloud2 output;
	switch (type)
	{
	case HPS3D_SIMPLE_ROI_EVEN: 
		printf("*************  HPS3D_SIMPLE_ROI_EVEN  ********************\n");
		num = data.simple_roi_data[0].roi_num;

		for (i = 0; i < num; i++)
		{
			printf("  ********GroupID:%d  ROIID:%d  *******\n", data.simple_roi_data[i].group_id, data.simple_roi_data[i].roi_id);
			printf("    distance_average:%d\n", data.simple_roi_data[i].distance_average);
			printf("    distance_min    :%d\n", data.simple_roi_data[i].distance_min);
			printf("    saturation_count:%d\n", data.simple_roi_data[i].saturation_count);
			printf("    threshold_state :%d\n", data.simple_roi_data[i].threshold_state);
			printf("    =====================================\n\n");
		}
		break;
	case HPS3D_FULL_ROI_EVEN: 
		printf("*************  HPS3D_FULL_ROI_EVEN  ********************\n");
		num = data.full_roi_data[0].roi_num;
		for (i = 0; i < num; i++)
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
	case HPS3D_SIMPLE_DEPTH_EVEN: 
		printf("*************  HPS3D_SIMPLE_DEPTH_EVEN  ********************\n");
		printf(" distance_average:%d\n", data.simple_depth_data.distance_average);
		printf(" distance_min    :%d\n", data.simple_depth_data.distance_min);
		printf(" saturation_count:%d\n", data.simple_depth_data.saturation_count);
		printf("==========================================================\n\n");
		break;
	case HPS3D_FULL_DEPTH_EVEN: 
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
		if(!ros::ok())
		{
			break;
		}	
		cloud.width = data.full_depth_data.point_cloud_data.width;
		cloud.height = data.full_depth_data.point_cloud_data.height;
		cloud.points.resize(cloud.width * cloud.height);
		for (size_t i = 0; i < cloud.points.size (); i++)
		{
			if(data.full_depth_data.point_cloud_data.point_data[i].z < 65530)
			{
				cloud.points[i].x  = data.full_depth_data.point_cloud_data.point_data[i].x/1000.0;
				cloud.points[i].y = data.full_depth_data.point_cloud_data.point_data[i].y/1000.0;
				cloud.points[i].z = data.full_depth_data.point_cloud_data.point_data[i].z/1000.0;	
			}
			else
			{
				cloud.points[i].x  = 0;
				cloud.points[i].y = 0;
				cloud.points[i].z = 0;	
			}						
			
		}					
		//Convert the cloud to ROS message
		pcl::toROSMsg(cloud, output);
		output.header.frame_id = "hps";
		camera_pub.publish(output);
		printf("frame_id = hps\n\n");
		break;
	default:
		break;
	}

	return true;
}


static void EventCallBackFunc(int handle, int eventType, uint8_t *data,int dataLen, void *userPara)
{
	switch ((HPS3D_EventType_t)eventType)
	{
		case HPS3D_SIMPLE_ROI_EVEN:
		case HPS3D_FULL_ROI_EVEN:
		case HPS3D_FULL_DEPTH_EVEN:
		case HPS3D_SIMPLE_DEPTH_EVEN:
                        HPS3D_ConvertToMeasureData(data,&g_measureData, (HPS3D_EventType_t)eventType);
                        PrintResultData((HPS3D_EventType_t)eventType, g_measureData);
			break;
		case HPS3D_SYS_EXCEPTION_EVEN: 
			printf("SYS ERR :%s\n", data);
			break;
		case HPS3D_DISCONNECT_EVEN: 
			printf("Device disconnected!\n");
			HPS3D_CloseDevice(handle);
			break;
		case HPS3D_NULL_EVEN: 
		default:
			break;
	}
}

void signal_handler(int signo)
{
	HPS3D_StopCapture(g_handle);
	HPS3D_CloseDevice(g_handle);
	printf("Device disconnected!\n\n");
    exit(0);
}

int main(int argc, char **argv)
{
        ros::init(argc, argv, "hps_camera");//ros init
	ros::NodeHandle n;//Create a node
	printf("HPS3D160 ROS Demo (Linux)\n\n");

	printf("SDK Ver:%s\n", HPS3D_GetSDKVersion());
	if(signal(SIGINT,signal_handler) == SIG_ERR || signal(SIGTSTP,signal_handler) == SIG_ERR)
	{
		printf("sigint error");
	}
        //Create a topic
	camera_pub = n.advertise<sensor_msgs::PointCloud2> ("hps_output", 1);



	HPS3D_StatusTypeDef ret = HPS3D_RET_ERROR;
	do
	{
            ret = HPS3D_MeasureDataInit(&g_measureData);
            if (ret != HPS3D_RET_OK)
            {
                    printf("MeasureDataInit faild,Err:%d\n", ret);
                    break;
            }
            //ret = HPS3D_USBConnectDevice((char *)"/dev/ttyACM0",&handle);
            ret = HPS3D_EthernetConnectDevice((char *)"192.168.0.10", 12345, &g_handle);
            if (ret != HPS3D_RET_OK)
            {
                    printf("connect faild,Err:%d\n", ret);
                    break;
            }
            printf("Dev Ver:%s\n", HPS3D_GetDeviceVersion(g_handle));
            printf("SN:%s\n\n", HPS3D_GetSerialNumber(g_handle));

            HPS3D_RegisterEventCallback(EventCallBackFunc, NULL);

            HPS3D_DeviceSettings_t settings;
            ret = HPS3D_ExportSettings(g_handle, &settings);
            if (ret != HPS3D_RET_OK)
            {
                    printf("ExportSettings,Err:%d\n", ret);
                    break;
            }
            printf("resolution:%d X %d\n", settings.max_resolution_X, settings.max_resolution_Y);
            printf("max_roi_group_number:%d  cur_group_id：%d\n", settings.max_roi_group_number, settings.cur_group_id);
            printf("max_roi_number:%d\n", settings.max_roi_number);
            printf("max_multiCamera_code:%d，cur_multiCamera_code:%d\n", settings.max_multiCamera_code, settings.cur_multiCamera_code);
            printf("user_id：%d\n", settings.user_id);
            printf("optical_path_calibration: %d\n\n", settings.optical_path_calibration);

            HPS3D_StartCapture(g_handle);
            while (1)
            {
                    usleep(1000);
            }
	} while (0);

	HPS3D_StopCapture(g_handle);
	HPS3D_CloseDevice(g_handle);
        HPS3D_MeasureDataFree(&g_measureData);
	return 0;
}




