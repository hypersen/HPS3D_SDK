package HPS3D_SDK_Test;

import java.awt.Point;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Timer;
import java.util.TimerTask;

import javax.imageio.ImageIO;
import javax.imageio.stream.FileImageOutputStream;

import com.sun.jna.Callback;
import com.sun.jna.Pointer;

import HPS3D_SDK_Test.*;
import libhps3d32.AsyncIObserver_t;
import libhps3d32.HPS3D_HandleTypeDef;
import libhps3d32.Libhps3d32Library;
import libhps3d32.Libhps3d32Library.HPS3D_AddObserver_fun_callback;
import libhps3d32.Libhps3d32Library.RET_StatusTypeDef;

public class HPS3D_SDK_Demo {
	
	//Libhps3d32Library.HPS3D_AddObserver_fun_callback fun;
	static int upStatus = 0;
	static byte firstFlag = 1;
	static int frameCnt = 0;
	static libhps3d32.AsyncIObserver_t MyObserver = new AsyncIObserver_t();  
	static HPS3D_HandleTypeDef handle = new HPS3D_HandleTypeDef();  /*Save device parameters*/
	static byte[] distance_8bite = new byte[Libhps3d32Library.MAX_PIX_NUM];
	static libhps3d32.FullRoiDataTypeDef []full_roi_buf;
	//byte数组到图片到硬盘上
	public static void byte2image(byte[] data,String path)
	{
		   BufferedImage bi = new BufferedImage(Libhps3d32Library.RES_WIDTH, Libhps3d32Library.RES_HEIGHT, BufferedImage.TYPE_BYTE_GRAY);
		   for(int y=0;y<Libhps3d32Library.RES_HEIGHT;y++)
		   {
			   for(int x=0;x<Libhps3d32Library.RES_WIDTH;x++)
			   {
				   bi.setRGB(x, y, (int)data[x+y*bi.getWidth()]);
			   }
		   }
		  
		   try 
		   {
			   ImageIO.write(bi, "jpg", new File(path));
		   }
		   catch(IOException e)
		   {
			   e.printStackTrace();
		   }
	 }
	
	public static void timer2() {
        Timer timer = new Timer();
        timer.schedule(new TimerTask() {
            public void run() {
                System.out.println("fps=" + frameCnt);
                frameCnt = 0;
            }
        }, 0, 1000);
    }
	
	static Libhps3d32Library.HPS3D_AddObserver_fun_callback func = new HPS3D_AddObserver_fun_callback() {
		
		@Override
		public Pointer apply(HPS3D_HandleTypeDef HPS3D_HandleTypeDefPtr1, AsyncIObserver_t AsyncIObserver_tPtr1) {
			// TODO Auto-generated method stub
			frameCnt++;
			// TODO Auto-generated method stub				
			switch(AsyncIObserver_tPtr1.RetPacketType)
			{
				case Libhps3d32Library.RetPacketTypedef.SIMPLE_ROI_PACKET: 
					break;
				case Libhps3d32Library.RetPacketTypedef.FULL_ROI_PACKET:
					//System.out.println(AsyncIObserver_tPtr1.MeasureData.full_roi_data.frame_cnt);
					
					if(AsyncIObserver_tPtr1.MeasureData.full_roi_data.threshold_state!=0)
					{
						System.out.println("threshold_state = 1\n");
					}
					
					full_roi_buf = (libhps3d32.FullRoiDataTypeDef [])AsyncIObserver_tPtr1.MeasureData.full_roi_data.toArray(handle.RoiNumber);
					if(AsyncIObserver_tPtr1.MeasureData.full_roi_data.threshold_state!=0 && AsyncIObserver_tPtr1.MeasureData.full_roi_data.threshold_state != upStatus)
					{
						handle.RunMode = Libhps3d32Library.RunModeTypeDef.RUN_IDLE;
						Libhps3d32Library.HPS3D_SetRunMode(handle);
						Libhps3d32Library.HPS3D_SelectROIGroup(handle, (byte)1); /*切换ROI分组*/
						Libhps3d32Library.HPS3D_SingleMeasurement(handle);/*单次测量保存图片*/
						
						int pos = 0;
						int dist_avg = handle.MeasureData.full_roi_data.distance_average;
						for (int y = handle.MeasureData.full_roi_data.left_top_y; y <= handle.MeasureData.full_roi_data.right_bottom_y; y++)
		                {
		                    for (int x = handle.MeasureData.full_roi_data.left_top_x; x <= handle.MeasureData.full_roi_data.right_bottom_x; x++)
		                    {		                    	
		                    	distance_8bite[y * Libhps3d32Library.RES_WIDTH + x] = ((float)handle.MeasureData.full_roi_data.distance[pos] / (1.5*dist_avg) * 255.0) > 255 ? (byte)255: (byte)((float)handle.MeasureData.full_roi_data.distance[pos] / (1.5*dist_avg) *255.0) ;		                        
		                        pos++;
		                    }
		                }
						SimpleDateFormat df = new SimpleDateFormat("yyMMddHHmmss");//设置日期格式
						String filename = "./" + df.format(new Date())+".jpg";
						byte2image(distance_8bite,filename);						
						Libhps3d32Library.HPS3D_SelectROIGroup(handle, (byte)0); /*切换ROI分组*/
						handle.RunMode = Libhps3d32Library.RunModeTypeDef.RUN_CONTINUOUS;
						Libhps3d32Library.HPS3D_SetRunMode(handle);							
					}
					upStatus = AsyncIObserver_tPtr1.MeasureData.full_roi_data.threshold_state;
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
	
	
	public static void main(String[] args) throws InterruptedException {
		int flag = 0;

		
		do
		{			
			int retValue = 1;
			// ------------------------HPS3D_SetDebugEnable----------------------------
			byte debugFlag = 1;
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
			retValue = Libhps3d32Library.HPS3D_SetMeasurePacketType(Libhps3d32Library.MeasurePacketTypeDef.ROI_DATA_PACKET);
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
			
			Libhps3d32Library.HPS3D_AddObserver(func, handle, MyObserver);
			
			// --------------------------HPS3D ---------------------------
			byte en = 1;
			Libhps3d32Library.HPS3D_SetOpticalEnable(handle,en);
			Libhps3d32Library.HPS3D_SetPointCloudEn(en);
			
			Libhps3d32Library.HPS3D_SelectROIGroup(handle,(byte)0);
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
		
		//timer2(); //printf fps
		while(flag == 1)
		{
			Thread.sleep(1000);		
		}
		
		return;
	}
}
