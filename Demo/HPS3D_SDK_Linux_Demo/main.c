/**********************************************************************
* COPYRIGHT NOTICE - HYPERSEN TECHNOLOGY
*
* Copyright (c) 2018, Hypersen Technology, Inc.
*
* All rights reserved.
*
*======================================================================
* \file main.c
* \brief TODO
* \author Kevin
* \email Kevin_Wang@hypersen.com
* \version 1.0.0
* \date 2018年11月12日 下午5:06:03
* \license private & classified
*---------------------------------------------------------------------
* Remark: This project is still under construction.
*======================================================================
* Change History:
*---------------------------------------------------------------------
* <Date>			| <Version>	| <Author>			| <Description>
*---------------------------------------------------------------------
* 2018年11月12日			| V1.0.0	| Kevin				| Create file
*======================================================================
* Detailed Notes:
*---------------------------------------------------------------------
* <Version>		| <Description>
*---------------------------------------------------------------------
* V1.0.0		| TODO
*---------------------------------------------------------------------

**********************************************************************/

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "api.h"
#include <unistd.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <math.h>

HPS3D_HandleTypeDef handle[DEV_NUM];
AsyncIObserver_t My_Observer[DEV_NUM];
ObstacleConfigTypedef ObstacleConf;
uint8_t connect_number = 0; 
/*
 * User processing function,Continuous measurement or asynchronous mode
 * in which the observer notifies the callback function
 * */
void* User_Func(HPS3D_HandleTypeDef *handle,AsyncIObserver_t *event)
{
	switch(event->RetPacketType)
	{
		case SIMPLE_ROI_PACKET:
			printf("observer id = %d, distance average:%d\n",event->ObserverID,event->MeasureData.simple_roi_data[0].distance_average);
			break;
		case FULL_ROI_PACKET:
			printf("observer id = %d, distance average:%d\n",event->ObserverID,event->MeasureData.full_roi_data[0].distance_average);
			break;
		case FULL_DEPTH_PACKET:
			printf("observer id = %d, distance average:%d\n",event->ObserverID,event->MeasureData.full_depth_data->distance_average);		
			break;
		case SIMPLE_DEPTH_PACKET:
			printf("observer id = %d, distance average:%d\n",event->ObserverID,event->MeasureData.simple_depth_data->distance_average);
			break;
		case OBSTACLE_PACKET:
			printf("observer id = %d\n",event->ObserverID);
			printf(" Obstacle ID：%d\n",event->MeasureData.Obstacle_data->Id);
			printf(" LeftPoint:(%f,%f,%f)\n",event->MeasureData.Obstacle_data->LeftPoint.x,event->MeasureData.Obstacle_data->LeftPoint.y,event->MeasureData.Obstacle_data->LeftPoint.z);
			printf(" RightPoint:(%f,%f,%f)\n",event->MeasureData.Obstacle_data->RightPoint.x,event->MeasureData.Obstacle_data->RightPoint.y,event->MeasureData.Obstacle_data->RightPoint.z);
			printf(" UpperPoint:(%f,%f,%f)\n",event->MeasureData.Obstacle_data->UpperPoint.x,event->MeasureData.Obstacle_data->UpperPoint.y,event->MeasureData.Obstacle_data->UpperPoint.z);
			printf(" UnderPoint:(%f,%f,%f)\n",event->MeasureData.Obstacle_data->UnderPoint.x,event->MeasureData.Obstacle_data->UnderPoint.y,event->MeasureData.Obstacle_data->UnderPoint.z);
			printf(" MinPoint:(%f,%f,%f)\n",event->MeasureData.Obstacle_data->MinPoint.x,event->MeasureData.Obstacle_data->MinPoint.y,event->MeasureData.Obstacle_data->MinPoint.z);
			printf(" DistanceAverage:%d\n\n",event->MeasureData.Obstacle_data->DistanceAverage);
			break;
		case NULL_PACKET:
			printf(" packet is null\n");
			break;
		default:
			printf(" system error\n");
			break;
	}
}

/*
 * Debugging use
 * */
void User_Printf(char *str)
{
	printf("%s\n",str);
}


void signal_handler(int signo)
{
	HPS3D_RemoveDevice(handle);
    exit(0);
}


int main()
{
	uint8_t fileName[DEV_NUM][DEV_NAME_SIZE] = {0};
	uint32_t i = 0;
	uint32_t n = 0;
	uint32_t a = 0;
	int b  = 0;
	int indx = 0;
	RET_StatusTypeDef ret = RET_OK;

	do
	{
		if(signal(SIGINT,signal_handler) == SIG_ERR)
		{
			printf("sigint error");
			break;
		}

		HPS3D_SetDebugEnable(true);
		HPS3D_SetDebugFunc(&User_Printf);

		printf("Select Transport:(0:USB 1:Ethernet)\n");
		scanf("%d",&b);
		if(b == 1)
		{
			/*set device server IP*/
			ret = HPS3D_SetEthernetServerInfo(&handle[0],"192.168.0.10",12345);
			if(ret != RET_OK)
			{
				printf("HPS3D_SetEthernetServerInfo error ,ret = %d\n",ret);
				break;
			}	
		}
		
		/*initialization device*/
		connect_number = HPS3D_AutoConnectAndInitConfigDevice(handle);
		printf("connect_number = %d\n",connect_number);
		if(connect_number == 0)
		{
			break;
		}
		for(i = 0;i < connect_number;i++)
		{
			My_Observer[i].AsyncEvent = ISubject_Event_DataRecvd;
			My_Observer[i].NotifyEnable = true;
			My_Observer[i].ObserverID = i;
			My_Observer[i].RetPacketType = NULL_PACKET;
		}
		/*Adding asynchronous observers,Only valid in asynchronous or continuous measurement mode*/
		HPS3D_AddObserver(&User_Func,handle,My_Observer);
		/*Enable point cloud conversion output*/	
		HPS3D_SetPointCloudEn(true);
		for(i = 0;i<connect_number;i++)
		{
			HPS3D_SetOpticalEnable(&handle[i],true);
			/*Set to continuous measurement mode*/
			handle[i].RunMode = RUN_CONTINUOUS;
			HPS3D_SetRunMode(&handle[i]);
		}

		a = 1;
	}while(0);

	while(a)
	{
		usleep(100000);
	}

	
	return 0;
}

