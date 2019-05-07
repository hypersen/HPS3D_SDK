package HPS3D_SDK_Test;

import java.awt.Point;
import java.io.File;
import java.nio.ByteBuffer;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.imageio.stream.FileImageOutputStream;

import com.sun.jna.Callback;
import com.sun.jna.Pointer;

import HPS3D_SDK_Test.*;
import libhps3d32.AsyncIObserver_t;
import libhps3d32.HPS3D_HandleTypeDef;
import libhps3d32.Libhps3d32Library;
import libhps3d32.Libhps3d32Library.RET_StatusTypeDef;

public class HPS3D_SDK_Demo {
	
	Libhps3d32Library.HPS3D_AddObserver_fun_callback fun;
	
	//byte数组到图片到硬盘上
	public static void byte2image(byte[] data,String path)
	{
	   if(path.equals("")) return;//判断输入的byte是否为空
	   try
	   {
		   FileImageOutputStream imageOutput = new FileImageOutputStream(new File(path));//打开输入流
		   imageOutput.write(data, 0, data.length);//将byte写入硬盘
		   imageOutput.close();
	   } 
	   catch(Exception ex) 
	   {
	     System.out.println("Exception: " + ex);
	     ex.printStackTrace();
	   }
	 }
	
	
	public static void main(String[] args) throws InterruptedException {
		int flag = 0;
		libhps3d32.AsyncIObserver_t MyObserver = new AsyncIObserver_t();  
		HPS3D_HandleTypeDef handle = new HPS3D_HandleTypeDef();  /*Save device parameters*/
		
		/*CallBack func*/
		Libhps3d32Library.HPS3D_AddObserver_fun_callback  fun  = 
		 new Libhps3d32Library.HPS3D_AddObserver_fun_callback() {			
			@Override
			public Pointer apply(libhps3d32.HPS3D_HandleTypeDef HPS3D_HandleTypeDefPtr1, libhps3d32.AsyncIObserver_t AsyncIObserver_tPtr1) {
				
				// TODO Auto-generated method stub				
				switch(AsyncIObserver_tPtr1.RetPacketType)
				{
					case Libhps3d32Library.RetPacketTypedef.SIMPLE_ROI_PACKET: 
						break;
					case Libhps3d32Library.RetPacketTypedef.FULL_ROI_PACKET:
						//libhps3d32.FullRoiDataTypeDef []full_roi_buf = (libhps3d32.FullRoiDataTypeDef [])AsyncIObserver_tPtr1.MeasureData.full_roi_data.toArray(handle.RoiNumber);
						System.out.println("threshold_state:" +AsyncIObserver_tPtr1.MeasureData.full_roi_data.threshold_state);
						if(AsyncIObserver_tPtr1.MeasureData.full_roi_data.threshold_state!=0)
						{
							System.out.println("threshold_state:" + AsyncIObserver_tPtr1.MeasureData.full_roi_data.threshold_state);
							handle.RunMode = Libhps3d32Library.RunModeTypeDef.RUN_IDLE;
							Libhps3d32Library.HPS3D_SetRunMode(handle);
							Libhps3d32Library.HPS3D_SelectROIGroup(handle, (byte)1); /*切换ROI分组*/
							Libhps3d32Library.HPS3D_SingleMeasurement(handle);/*单次测量保存图片*/
							byte[] distance_8bite = new byte[Libhps3d32Library.MAX_PIX_NUM];
							int pos = 0;
							for (int y = handle.MeasureData.full_roi_data.left_top_y; y <= handle.MeasureData.full_roi_data.right_bottom_y; y++)
			                {
			                    for (int x = handle.MeasureData.full_roi_data.left_top_x; x <= handle.MeasureData.full_roi_data.right_bottom_x; x++)
			                    {
			                    	distance_8bite[y * Libhps3d32Library.RES_WIDTH + x] = (byte)handle.MeasureData.full_roi_data.distance[pos];		                        
			                        pos++;
			                    }
			                }
							SimpleDateFormat df = new SimpleDateFormat("yyMMddHHmmss");//设置日期格式
							String filename = "./" + df.format(new Date())+".jpg";
							System.out.println("save start:" + filename);
							byte2image(distance_8bite,filename);
							System.out.println("save end:" + filename);
							Libhps3d32Library.HPS3D_SelectROIGroup(handle, (byte)0); /*切换ROI分组*/
							handle.RunMode = Libhps3d32Library.RunModeTypeDef.RUN_CONTINUOUS;
							Libhps3d32Library.HPS3D_SetRunMode(handle);
						}
						break;
					case Libhps3d32Library.RetPacketTypedef.SIMPLE_DEPTH_PACKET:
						break;
					case Libhps3d32Library.RetPacketTypedef.FULL_DEPTH_PACKET:  /*depth data and point cloud data*/
						System.out.println("Observer ID:" + AsyncIObserver_tPtr1.ObserverID + 
						"    Distacne average:" + AsyncIObserver_tPtr1.MeasureData.full_depth_data.distance_average);							
						break;
					case Libhps3d32Library.RetPacketTypedef.OBSTACLE_PACKET:
						break;
					case Libhps3d32Library.RetPacketTypedef.NULL_PACKET:
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
			// ------------------------HPS3D_SetDebugEnable----------------------------
			byte debugFlag = 0;
			Libhps3d32Library.HPS3D_SetDebugEnable(debugFlag);
			Libhps3d32Library.HPS3D_SetDebugFunc(new Libhps3d32Library.HPS3D_SetDebugFunc_Call_Back_callback() {
				@Override
				public void apply(Pointer str) {
					String string2 = str.getString(0, "ASCII");
					System.out.println(string2);
				}
			});
			
			// ------------------------HPS3D_GetSDKVersion----------------------------
			libhps3d32.Version_t version = Libhps3d32Library.HPS3D_GetSDKVersion();
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
			retValue = Libhps3d32Library.HPS3D_SetEthernetServerInfo(handle,serverIPBuff, serverPort);
			if(retValue != Libhps3d32Library.RET_StatusTypeDef.RET_OK)
			{
				System.out.println("HPS3D_SetEthernetServerInfo failed:"+ retValue);
				break;
			}
			// ------------------------HPS3D_SetMeasurePacketType----------------------------
			/*default MeasurePacketType  = DEPTH_DATA_PACKET*/
			//retValue = Libhps3d32Library.HPS3D_SetMeasurePacketType(Libhps3d32Library.MeasurePacketTypeDef.ROI_DATA_PACKET);
			if(retValue != Libhps3d32Library.RET_StatusTypeDef.RET_OK)
			{
				System.out.println("HPS3D_SetMeasurePacketType failed:"+ retValue);
				break;
			}
					
			// ------------------------HPS3D_Connect----------------------------
			retValue = Libhps3d32Library.HPS3D_Connect(handle);
			if(retValue != Libhps3d32Library.RET_StatusTypeDef.RET_OK)
			{
				System.out.println("HPS3D_Connect failed:"+ retValue);
				break;
			}
			
			// ------------------------HPS3D_ConfigInit----------------------------
			retValue = Libhps3d32Library.HPS3D_ConfigInit(handle);
			if(retValue != Libhps3d32Library.RET_StatusTypeDef.RET_OK)
			{
				System.out.println("HPS3D_ConfigInit failed:"+ retValue);
				break;
			}
			
			// --------------------------HPS3D_AddObserver---------------------------
			MyObserver.AsyncEvent = Libhps3d32Library.AsyncISubjectEvent.ISubject_Event_DataRecvd;
			MyObserver.NotifyEnable = 1; /*enable = true*/
			MyObserver.ObserverID  = 0; 		
			Libhps3d32Library.HPS3D_AddObserver(fun, handle, MyObserver);
			
			// --------------------------HPS3D ---------------------------
			byte en = 1;
			Libhps3d32Library.HPS3D_SetOpticalEnable(handle,en);
			Libhps3d32Library.HPS3D_SetPointCloudEn(en);
			
			// --------------------------HPS3D_SetRunMode---------------------------
			handle.RunMode = Libhps3d32Library.RunModeTypeDef.RUN_CONTINUOUS;
			Libhps3d32Library.HPS3D_SetRunMode(handle);
			System.out.println("HPS3D Start measurement");	
			flag = 1;
		}while(false);
		
		/*config param failed，remove device*/
		if(flag == 0)
		{
			Libhps3d32Library.HPS3D_RemoveDevice(handle);
		}
		
		
		while(flag == 1)
		{
			Thread.sleep(1000);		
		}
		
		return;
	}
}
