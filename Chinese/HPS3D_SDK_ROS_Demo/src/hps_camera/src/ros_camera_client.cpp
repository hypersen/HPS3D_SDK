#include "ros/ros.h"//ros
#include "std_msgs/String.h"
#include "hps_camera/camera.h"//srv
#include "../include/api.h"//api interface
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

HPS3D_HandleTypeDef handle;
AsyncIObserver_t My_Observer;
ObstacleConfigTypedef ObstacleConf;
ros::Publisher camera_pub;//Global variable, because the observer callback function needs to be used


//The observer callback function
void *User_Func(HPS3D_HandleTypeDef *handle, AsyncIObserver_t *event)
{
	pcl::PointCloud<pcl::PointXYZ> cloud;
	sensor_msgs::PointCloud2 output;
	uint16_t distance[MAX_PIX_NUM] = {0};
	if(event->AsyncEvent == ISubject_Event_DataRecvd)
	{
		switch(event->RetPacketType)
		{
			case SIMPLE_ROI_PACKET:				
				break;
			case FULL_ROI_PACKET:		
				break;
			case FULL_DEPTH_PACKET: /*point cloud data and depth data*/	
				if(ros::ok())
				{
					cloud.width = event->MeasureData.point_cloud_data->width;
					cloud.height = event->MeasureData.point_cloud_data->height;
					cloud.points.resize(cloud.width * cloud.height);
					for (size_t i = 0; i < cloud.points.size (); i++)
					{
						if(event->MeasureData.point_cloud_data[0].point_data[i].z < LOW_AMPLITUDE)
						{
							cloud.points[i].x  = event->MeasureData.point_cloud_data[0].point_data[i].x/1000.0;
							cloud.points[i].y = event->MeasureData.point_cloud_data[0].point_data[i].y/1000.0;
							cloud.points[i].z = event->MeasureData.point_cloud_data[0].point_data[i].z/1000.0;	
							//cloud.points[i].x  = i%cloud.width - cloud.width/2;
							//cloud.points[i].y = i/cloud.height - cloud.height/2;
							//cloud.points[i].z = event->MeasureData.full_depth_data->distance[i]/1000.0;	
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
				
				}
				break;
			case SIMPLE_DEPTH_PACKET:			
				break;
			case OBSTACLE_PACKET:			
				break;
			case NULL_PACKET:
				printf("null packet\n");
				break;
			default:
				printf("system error!\n");
				break;
		}
	}
}

//check ctrl+c signal
void signal_handler(int signo)
{
    if(HPS3D_RemoveDevice(&handle) != RET_OK)
    {
		printf("HPS3D_RemoveDevice faild\n");
    }
    else
    {	
        printf("HPS3D_RemoveDevice succeed\n");
    }
    exit(0);
}


//printf log callback function
void my_printf(char *str)
{
	std::cout<< str;
}


int main(int argc, char **argv)
{

	ros::init(argc, argv, "ros_camera_client");//ros init
	ros::NodeHandle n;//Create a node
	uint32_t a = 0;
	char fileName[10][20];
	uint32_t dev_cnt = 0;
	uint32_t indx = 0;
	RET_StatusTypeDef ret = RET_OK;
	AsyncIObserver_t My_Observer;

	std::stringstream sclient_name;

	//Install the signal
	if(signal(SIGINT,signal_handler) == SIG_ERR || signal(SIGTSTP,signal_handler) == SIG_ERR)
	{
		printf("sigint error");
	}
	
	//Create a topic
	camera_pub = n.advertise<sensor_msgs::PointCloud2> ("output", 1);
	
	//set debug enable and install printf log callback function
	HPS3D_SetDebugEnable(false);
	HPS3D_SetDebugFunc(&my_printf);
	//HPS3D_SetMeasurePacketType(ROI_DATA_PACKET);
	int b = 0;
	printf("select Transport type: 0:USB 1:Ethernet\n");
	scanf("%d",&b);
	if(b == 1)
	{
		HPS3D_SetEthernetServerInfo(&handle,(char *)"192.168.0.10",12345);	
	}
	else
	{
		dev_cnt = HPS3D_GetDeviceList((char *)"/dev/",(char *)"ttyACM",fileName);
		handle.DeviceName = fileName[0];
	}
	do
	{
		//Device Connection
		ret = HPS3D_Connect(&handle);
		if(ret != RET_OK)
		{
			printf("Device open failed,ret = %d\n",ret);
			break;
		}
		
		//Device init
		ret = HPS3D_ConfigInit(&handle);
		if(RET_OK != ret)
		{
			printf("Initialization failed:%d\n", ret);
			break;
		}
		printf("Initialization succeed\n");		
		HPS3D_SetEdgeDetectionEnable(true); 
		/*set convert point cloud data enable*/		
		HPS3D_SetOpticalEnable(&handle, true);
		HPS3D_SetPointCloudEn(true);
		
		//Add observer one
		My_Observer.AsyncEvent = ISubject_Event_DataRecvd;
		My_Observer.NotifyEnable = true;
		HPS3D_AddObserver(&User_Func, &handle, &My_Observer);		

		//Set running mode
		handle.RunMode = RUN_CONTINUOUS;
		HPS3D_SetRunMode(&handle);
		
	}while(0);

	if(ret != RET_OK)
	{
		//Remove device and disconnect
		HPS3D_RemoveDevice(&handle);
		printf("Initialization failed, Remove device\n");
		return 0;
	}
	
	while(1)
	{
		sleep(10);		
	}
		
	return 0;
}

