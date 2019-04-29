#include "ros/ros.h"//ros
#include "hps_camera/distance.h"//msg
#include "hps_camera/camera.h"//srv
#include <string.h>

//订阅回调函数
void chatterCallback(const hps_camera::distance& msg)
{  
	printf("distance_average = %d\n", msg.distance_average);
} 

//接收到客户端服务和做出的响应
bool send_cmd(hps_camera::camera::Request  &req, hps_camera::camera::Response &res)
{
	std::stringstream scmd;
	//客户端发送来的请求
	printf("client_name: %s\n", req.client_node_name.c_str() );
	if( strcmp(req.client_node_name.c_str(), "camera_client" ) == 0 )
	{
		scmd<< "start";
		//做出的响应
		res.control_cmd = scmd.str();
		printf("send_cmd: %s\n", res.control_cmd.c_str() );
	}
	return true;
}

int main(int argc, char **argv)
{  
	//ros初始化
	ros::init(argc, argv, "ros_camera_server");   
	//创建节点
	ros::NodeHandle n;  
	//创建服务
	ros::ServiceServer service = n.advertiseService("client_login", send_cmd);
	//订阅话题
	ros::Subscriber sub = n.subscribe("camera", 1000, chatterCallback);
	printf("waiting client login\n");
	ros::spin();   
	return 0;
}

