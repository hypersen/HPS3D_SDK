package HPS3D_SDK_Test;

import java.awt.Point;
import java.nio.ByteBuffer;

import com.sun.jna.Callback;
import com.sun.jna.Pointer;

import HPS3D_SDK_Test.*;
import libhps3d64.AsyncIObserver_t;
import libhps3d64.HPS3D_HandleTypeDef;
import libhps3d64.Libhps3d64Library;
import libhps3d64.Libhps3d64Library.RET_StatusTypeDef;

public class HPS3D_SDK_Demo {
	
	Libhps3d64Library.HPS3D_AddObserver_fun_callback fun;
	
	public static void main(String[] args) throws InterruptedException {
		int flag = 0;
		libhps3d64.AsyncIObserver_t MyObserver = new AsyncIObserver_t();  
		libhps3d64.HPS3D_HandleTypeDef handle = new libhps3d64.HPS3D_HandleTypeDef();  /*Save device parameters*/
		
		/*CallBack func*/
		Libhps3d64Library.HPS3D_AddObserver_fun_callback  fun  = 
		 new Libhps3d64Library.HPS3D_AddObserver_fun_callback() {			
			@Override
			public Pointer apply(libhps3d64.HPS3D_HandleTypeDef HPS3D_HandleTypeDefPtr1, libhps3d64.AsyncIObserver_t AsyncIObserver_tPtr1) {
				// TODO Auto-generated method stub
				
				switch(AsyncIObserver_tPtr1.RetPacketType)
				{
					case Libhps3d64Library.RetPacketTypedef.SIMPLE_ROI_PACKET: 
						break;
					case Libhps3d64Library.RetPacketTypedef.FULL_ROI_PACKET:
						break;
					case Libhps3d64Library.RetPacketTypedef.SIMPLE_DEPTH_PACKET:
						break;
					case Libhps3d64Library.RetPacketTypedef.FULL_DEPTH_PACKET:  /*depth data and point cloud data*/
						System.out.println("Observer ID:" + AsyncIObserver_tPtr1.ObserverID + 
								"    Distacne average:" + AsyncIObserver_tPtr1.MeasureData.full_depth_data.distance_average);							
						break;
					case Libhps3d64Library.RetPacketTypedef.OBSTACLE_PACKET:
						break;
					case Libhps3d64Library.RetPacketTypedef.NULL_PACKET:
						break;
					default: 
						break;
				}
				return null;
			}
		};
		
		
		do
		{
			int retValue = 1;
			byte debugFlag = 1;
			Libhps3d64Library.HPS3D_SetDebugEnable(debugFlag);
			Libhps3d64Library.HPS3D_SetDebugFunc(new Libhps3d64Library.HPS3D_SetDebugFunc_Call_Back_callback() {
				@Override
				public void apply(Pointer str) {
					String string2 = str.getString(0, "ASCII");
					System.out.println(string2);
				}
			});
			libhps3d64.Version_t version = Libhps3d64Library.HPS3D_GetSDKVersion();
			System.out.println(version.year + "." + version.month + "."
					+ version.day + "." + version.major + "." + version.minor + "."
					+ version.rev);
					
			// ------------------------HPS3D_SetEthernetServerInfo----------------------------
			ByteBuffer serverIPBuff = ByteBuffer.allocate(13);
			String serverIP = "192.168.0.10\0"; 
			byte [] src = serverIP.getBytes();
			serverIPBuff.put(src);  /*position = 13*/
			serverIPBuff.position(0);  /*set position = 0*/
			short serverPort = 12345;			 
			retValue = Libhps3d64Library.HPS3D_SetEthernetServerInfo(handle,serverIPBuff, serverPort);
			if(retValue != Libhps3d64Library.RET_StatusTypeDef.RET_OK)
			{
				System.out.println("HPS3D_SetEthernetServerInfo failed:"+ retValue);
				break;
			}
			// ------------------------HPS3D_SetMeasurePacketType----------------------------
			/*default MeasurePacketType  = DEPTH_DATA_PACKET*/
			retValue = Libhps3d64Library.HPS3D_SetMeasurePacketType(Libhps3d64Library.MeasurePacketTypeDef.DEPTH_DATA_PACKET);
			if(retValue != Libhps3d64Library.RET_StatusTypeDef.RET_OK)
			{
				System.out.println("HPS3D_SetMeasurePacketType failed:"+ retValue);
				break;
			}
			// ------------------------HPS3D_Connect----------------------------
			retValue = Libhps3d64Library.HPS3D_Connect(handle);
			if(retValue != Libhps3d64Library.RET_StatusTypeDef.RET_OK)
			{
				System.out.println("HPS3D_Connect failed:"+ retValue);
				break;
			}
			
			// ------------------------HPS3D_ConfigInit----------------------------
			retValue = Libhps3d64Library.HPS3D_ConfigInit(handle);
			if(retValue != Libhps3d64Library.RET_StatusTypeDef.RET_OK)
			{
				System.out.println("HPS3D_ConfigInit failed:"+ retValue);
				break;
			}
			
			// --------------------------HPS3D_AddObserver---------------------------
			MyObserver.AsyncEvent = Libhps3d64Library.AsyncISubjectEvent.ISubject_Event_DataRecvd;
			MyObserver.NotifyEnable = 1; /*enable = true*/
			MyObserver.ObserverID  = 0; 
			
			Libhps3d64Library.HPS3D_AddObserver(fun, handle, MyObserver);
			// --------------------------HPS3D_SetRunMode---------------------------
			handle.RunMode = Libhps3d64Library.RunModeTypeDef.RUN_CONTINUOUS;
			Libhps3d64Library.HPS3D_SetRunMode(handle);
			System.out.println("HPS3D Start measurement");	
			flag = 1;
		}while(false);
		
		if(flag == 0)
		{
			Libhps3d64Library.HPS3D_RemoveDevice(handle);
		}
		
		while(flag == 1)
		{
			Thread.sleep(1000);		
		}
		
		return;
	}
}
