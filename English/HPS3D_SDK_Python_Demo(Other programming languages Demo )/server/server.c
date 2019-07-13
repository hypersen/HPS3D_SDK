/**********************************************************************
* COPYRIGHT NOTICE - HYPERSEN TECHNOLOGY
*
* Copyright (c) 2018, Hypersen Technology, Inc.
*
* All rights reserved.
*
*======================================================================
* \file server.c
* \brief TODO
* \author Kevin
* \email Kevin_Wang@hypersen.com
* \version 1.0.0
* \date 2019年7月8日 下午5:06:03
* \license private & classified
*---------------------------------------------------------------------
* Remark: This project is still under construction.
*======================================================================
* Change History:
*---------------------------------------------------------------------
* <Date>			| <Version>	| <Author>			| <Description>
*---------------------------------------------------------------------
* 2019年8月8日		| V1.0.0	| Kevin				| Create file
*======================================================================
* Detailed Notes:
*---------------------------------------------------------------------
* <Version>		| <Description>
*---------------------------------------------------------------------
* V1.0.0		| TODO
*---------------------------------------------------------------------

**********************************************************************/
#include "api.h"
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>

#define SERVER_PORT 12345
#define SIZE 1024
HPS3D_HandleTypeDef g_handle[DEV_NUM];
AsyncIObserver_t g_Observer[DEV_NUM];
uint8_t g_connect_number = 0;
int g_listen_socket = 0;
int listen_socket = 0;
int client_socket = 0;
char printBuff[1024]={0};
uint8_t g_RemoveDeviceFlag = 0;

void printfToClient(const char *str, ...)
{
	va_list arg;
	char ret_str[256] = {0};
	char temp_str [256] = {0};
	char *str_tmp = NULL;
	va_start(arg, str);

	do
	{
		while(*str != '\0')
		{
			if(*str == '%')
			{
				str++;
				switch(*str)
				{
					case 'c':
						sprintf(temp_str,"%c",va_arg(arg,const int));
						strcat(ret_str, (const char *)temp_str);
						break;
					case 'd':
						sprintf(temp_str,"%d",va_arg(arg,const int));
						strcat(ret_str, (const char *)temp_str);
						break;
					case 'x':
					case 'X':
						sprintf(temp_str,"%x",va_arg(arg,const int));
						strcat(ret_str, (const char *)temp_str);
						break;
					case 's':
						str_tmp = (char *)va_arg(arg, const char*);
						strcat(ret_str, (const char *)str_tmp);
						break;
					default:
						break;
				}
			}
			else
			{
				strncat(ret_str, str, 1);
			}
			str++;
		}
		va_end(arg);

		/*Send data to the client*/
		int writelen = write(client_socket,ret_str,strlen(ret_str));
		if(writelen < 0)
		{

		}
	}while(0);
}


/*
 * User processing function,Continuous measurement or asynchronous mode
 * in which the observer notifies the callback function
 * */
void* User_Func(HPS3D_HandleTypeDef *handle,AsyncIObserver_t *event)
{
	switch(event->RetPacketType)
	{
		case SIMPLE_ROI_PACKET:
			break;
		case FULL_ROI_PACKET:
			break;
		case FULL_DEPTH_PACKET:
			printfToClient("observer id = %d, distance average:%d\n",event->ObserverID,event->MeasureData.full_depth_data->distance_average);
			break;
		case SIMPLE_DEPTH_PACKET:
			break;
		case OBSTACLE_PACKET:
			break;
		case NULL_PACKET:
			printfToClient(" packet is null\n");
			break;
		default:
			printfToClient(" system error\n");
			break;
	}
	return (void *)0;
}

/*
 * Debugging use
 * */
void User_Printf(char *str)
{
	printfToClient("%s\n",str);
}

RET_StatusTypeDef HPS3D_DevicInit(HPS3D_HandleTypeDef *handle,AsyncIObserver_t *observer)
{
	RET_StatusTypeDef ret = RET_OK;
	do
	{
		char fileName[DEV_NUM][DEV_NAME_SIZE] = {0};
		HPS3D_GetDeviceList("/dev/","ttyACM",fileName);
		handle->DeviceName = fileName[handle->ConnectionNumber];

		ret = HPS3D_Connect(handle);
		if(RET_OK != ret)
		{
			printfToClient("connect error\n");
			break;
		}

		/*Device initialization*/
		ret = HPS3D_ConfigInit(handle);
		if(RET_OK != ret)
		{
			printfToClient("Initialization failed! error code is:%d\n", ret);
			break;
		}

		ret = HPS3D_SetOpticalEnable(handle,true);
		if(RET_OK != ret)
		{
			printfToClient("SetOpticalEnable failed, error code is:%d\n", ret);
			break;
		}

		/*Adding asynchronous observers,Only valid in asynchronous or continuous measurement mode*/
		ret = HPS3D_AddObserver(&User_Func,handle,observer);
		if(RET_OK != ret)
		{
			printfToClient("AddObserver failed, error code is:%d\n", ret);
			break;
		}

		/*enable point cloud data*/
		ret = HPS3D_SetPointCloudEn(true);
		if(RET_OK != ret)
		{
			printfToClient("SetPointCloudEn failed, error code is:%d\n", ret);
			break;
		}
		g_connect_number++;

	}while(0);

	return ret;
}


/**
 * @brief	Creat socket
 * @param[in] server ip  and server port
 * @note
 * @retval	Return socket
 */
int Creat_socket(uint32_t server_ip,uint16_t server_port)
{
	int ret = 0;

	do
	{
		listen_socket = socket(AF_INET, SOCK_STREAM, 0);
		if(listen_socket == -1)
		{
			ret = listen_socket;
			printfToClient("socket");
			break;
		}
		struct sockaddr_in addr;
		memset(&addr, 0, sizeof(addr));

		addr.sin_family = AF_INET;
		addr.sin_port = htons(server_port);
		addr.sin_addr.s_addr = htonl(server_ip);
		//connect
		ret = bind(listen_socket, (struct sockaddr *)&addr, sizeof(addr));
		if(ret == -1)
		{
			printfToClient("bind error");
			break;
		}

		ret = listen(listen_socket, 5);
		if(ret == -1)
		{
			printfToClient("listen error");
			break;
		}
		ret = listen_socket;
	}while(0);

	return ret;
}

/**
 * @brief	wait client
 * @param[in] listen_socket
 * @note
 * @retval	Return socket
 */
int wait_client(int listen_socket)
{
	struct sockaddr_in cliaddr;
	int client_socket = 0;
	int ret = 0;
	int addrlen = sizeof(struct sockaddr_in);
	do
	{
		printf("Waiting for client connection......\n");
		client_socket = accept(listen_socket, (struct sockaddr *)&cliaddr, (socklen_t *)&addrlen);
		ret = client_socket;
		if(ret == -1)
		{
			perror("accept");
			break;
		}
		printf("Client connection\n");

	}while(0);
	return ret;
}

/*String command parsing and calling the corresponding function in the API*/
RET_StatusTypeDef HPS3D_CommandProcessFunc(char *command)
{
	RET_StatusTypeDef ret = RET_OK;
	do
	{
		if(command == NULL)
		{
			ret = RET_BUFF_EMPTY;
			break;
		}
		char list[100][100]={0};
		char rule[] = ",";
		char *token;
		int i = 0;
		int deviceID = 0;
		token = strtok(command, rule);

		while(token!= NULL)
		{
			memcpy(list[i],token,strlen(token));
			i++;
			token = strtok(NULL, rule);
		}
		/*command process*/
		if(!strcmp(list[0],"HPS3D_DevicInit"))
		{
			printf("HPS3D_DevicInit\n");
			deviceID = atoi(list[1]);
			g_handle[deviceID].ConnectionNumber = deviceID;
			g_Observer[deviceID].AsyncEvent = ISubject_Event_DataRecvd;
			g_Observer[deviceID].NotifyEnable = true;
			g_Observer[deviceID].ObserverID = deviceID;
			ret = HPS3D_DevicInit(&g_handle[deviceID],&g_Observer[deviceID]);
		}
		else if(!strcmp(list[0],"HPS3D_SetRunMode"))
		{
			printf("HPS3D_SetRunMode\n");
			deviceID = atoi(list[1]);
			int Runmode = atoi(list[2]);
			g_handle[deviceID].RunMode = (RunModeTypeDef)Runmode;
			ret = HPS3D_SetRunMode(&g_handle[deviceID]);
		}
		else if(!strcmp(list[0],"HPS3D_SetEthernetServerInfo"))
		{
			printf("HPS3D_SetEthernetServerInfo\n");
			deviceID = atoi(list[1]);
			uint16_t serverPort = atoi(list[3]);
			ret = HPS3D_SetEthernetServerInfo(&g_handle[deviceID],list[2],serverPort);
		}
		else if(!strcmp(list[0],"HPS3D_RemoveDevice"))
		{
			printf("HPS3D_RemoveDevice\n");
			deviceID = atoi(list[1]);
			ret = HPS3D_RemoveDevice(&g_handle[deviceID]);
			if(ret == RET_OK)
			{
				printfToClient("OK");
			}

		}
		else if(!strcmp(list[0],"HPS3D_RemoveDevice All"))
		{
			printf("HPS3D_RemoveDevice All,g_connect_number = %d\n",g_connect_number);
			uint8_t stat = 0;

			for(int i = 0;i<g_connect_number;i++)
			{
				ret = HPS3D_RemoveDevice(&g_handle[i]);
				printf("HPS3D_RemoveDevice i=%d\n",i);
				if(ret != RET_OK)
				{
					stat = 1;
				}
			}
			if(stat == 0)
			{
				printfToClient("OK");
				printf("HPS3D_RemoveDevice succeed\n");
			}
			g_RemoveDeviceFlag = stat == 0 ? 1 : 0;

		}
		else
		{
			printfToClient("No Command\n");
			ret = RET_ERROR;
		}
	}while(0);

	return ret;
}


/**
 * @brief	handle client
 * @param[in] listen_socket and client_socket
 * @note
 * @retval	none
 */
void hanld_client(int listen_socket, int client_socket)
{
	char buf[SIZE];
	int readlen = 0;
	int retlen = 0;
	char tmp;

	RET_StatusTypeDef ret = RET_OK;
	while(1)
	{
		retlen = read(client_socket, &tmp, 1);
		if(retlen > 0)
		{
			if(tmp == '\n')
			{
				ret = HPS3D_CommandProcessFunc(buf);
				if(ret!=RET_OK)
				{
					 printfToClient("HPS3D_CommandProcessFunc failed:%d\n",ret);
					 g_RemoveDeviceFlag = 1;
				}
				else
				{
					printfToClient("OK");
				}
				memset(buf,0,readlen);
				readlen = 0;
			}
			else
			{
				buf[readlen] = tmp;
				readlen++;
			}
		}
		if(g_RemoveDeviceFlag)
		{
			break;
		}
		usleep(200000);
	}
}


int main()
{
	listen_socket = Creat_socket(INADDR_ANY,SERVER_PORT);
	while(1)
	{
		client_socket = wait_client(listen_socket);
		int pid = fork();
		if(pid == -1)
		{
			perror("fork");
			break;
		}
		if(pid > 0)
		{
			close(client_socket);
			continue;
		}
		if(pid == 0)
		{
			hanld_client(listen_socket, client_socket);
			close(listen_socket);
			break;
		}
	}
	close(listen_socket);
	return 0;
}
