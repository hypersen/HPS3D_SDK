#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "api.h"
#include <QMessageBox>
#include <QtCore>
#include <QThread>
#include <windows.h>

HPS3D_HandleTypeDef HPS_handle;

QTimer *UpdateTimer;
AsyncIObserver_t Observer;
uint16_t FullRoiDistance[MAX_PIX_NUM];
uint16_t dist_average = 0;
uint16_t FrameCount = 0;
uint16_t cnt = 0;
QImage dist_img;
bool showImagFlag = false;

/*Define function Pointers to call dynamic link libraries*/
RET_StatusTypeDef(*SetDebugEnable)(bool en) = NULL;
RET_StatusTypeDef(*SetDebugFunc)(void *Call_Back) = NULL;
RET_StatusTypeDef(*Connect)(HPS3D_HandleTypeDef *handle) = NULL;
RET_StatusTypeDef(*DisConnect)(HPS3D_HandleTypeDef *handle) = NULL;
RET_StatusTypeDef(*ConfigInit)(HPS3D_HandleTypeDef *handle) = NULL;
RET_StatusTypeDef (*AddObserver)(void * (*fun)(HPS3D_HandleTypeDef *, AsyncIObserver_t *), HPS3D_HandleTypeDef *handle, AsyncIObserver_t *Observer_t) = NULL;
RET_StatusTypeDef(*SetRunMode)(HPS3D_HandleTypeDef *handle) = NULL;
RET_StatusTypeDef(*RemoveDevice)(HPS3D_HandleTypeDef *handle) = NULL;
RET_StatusTypeDef(*SingleMeasurement)(HPS3D_HandleTypeDef *handle) = NULL;
uint32_t (*GetDeviceList)(uint8_t * dirPath, uint8_t *prefix, uint8_t fileName[DEV_NUM][DEV_NAME_SIZE]) = NULL;
RET_StatusTypeDef (*SetPointCloudEn)(bool en) = NULL;
bool (*GetPointCloudEn)(void) = NULL;
RET_StatusTypeDef (*SetEthernetServerInfo)(HPS3D_HandleTypeDef *handle,uint8_t *serverIP,uint16_t serverPort) = NULL;
RET_StatusTypeDef (*SavePlyFile)(uint8_t *filename,PointCloudDataTypeDef point_cloud_data) = NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*LoadLibrary */
    HMODULE module = LoadLibraryA((LPCSTR)"libhps3d.dll");
    if (module == NULL)
    {
        DWORD error_id = GetLastError();
        printf("error load %d\n",error_id);
        return;
    }

    /*Debug print interface*/
    SetDebugEnable =  (RET_StatusTypeDef(*)(bool en))GetProcAddress(module, "HPS3D_SetDebugEnable");
    SetDebugFunc = (RET_StatusTypeDef(*)(void *Call_Back))GetProcAddress(module,"HPS3D_SetDebugFunc");
    /*Device connect interface*/
    Connect = (RET_StatusTypeDef(*)(HPS3D_HandleTypeDef *handle))GetProcAddress(module, "HPS3D_Connect");
    /*Device disconnect interface*/
    DisConnect = (RET_StatusTypeDef(*)(HPS3D_HandleTypeDef *handle))GetProcAddress(module, "HPS3D_DisConnect");
    /*Device Init. interface*/
    ConfigInit = (RET_StatusTypeDef(*)(HPS3D_HandleTypeDef *handle))GetProcAddress(module, "HPS3D_ConfigInit");
    /*Adds an observer function interface in asynchronous mode*/
    AddObserver = (RET_StatusTypeDef(*)(void* (*fun)(HPS3D_HandleTypeDef *, AsyncIObserver_t *), HPS3D_HandleTypeDef *, AsyncIObserver_t *))GetProcAddress(module, "HPS3D_AddObserver");
    /*Set the measurement run mode function*/
    SetRunMode = (RET_StatusTypeDef(*)(HPS3D_HandleTypeDef *handle))GetProcAddress(module, "HPS3D_SetRunMode");
    /*Device Remove function*/
    RemoveDevice = (RET_StatusTypeDef(*)(HPS3D_HandleTypeDef *handle))GetProcAddress(module, "HPS3D_RemoveDevice");
    /*Single measurement function in synchronous mode*/
    SingleMeasurement = (RET_StatusTypeDef(*)(HPS3D_HandleTypeDef *))GetProcAddress(module, "HPS3D_SingleMeasurement");
    /*Gets the current connection COM interface function*/
    GetDeviceList = (uint32_t(*)(uint8_t * , uint8_t *, uint8_t fileName[DEV_NUM][DEV_NAME_SIZE]))GetProcAddress(module, "HPS3D_GetDeviceList");
    /*Set/get point cloud enable conversion*/
    SetPointCloudEn = (RET_StatusTypeDef(*)(bool en))GetProcAddress(module, "HPS3D_SetPointCloudEn");
    GetPointCloudEn = (bool (*)(void))GetProcAddress(module, "HPS3D_GetPointCloudEn");
    SavePlyFile = (RET_StatusTypeDef (*)(uint8_t *filename,PointCloudDataTypeDef point_cloud_data))GetProcAddress(module, "HPS3D_SavePlyFile");;
    SetEthernetServerInfo = (RET_StatusTypeDef (*)(HPS3D_HandleTypeDef *,uint8_t *,uint16_t))GetProcAddress(module, "HPS3D_SetEthernetServerInfo");

    uint8_t fileName[10][20];
    ui->DeviceName->clear();
#if false
    uint32_t n = GetDeviceList(NULL,NULL,fileName);
    for(int i=0;i<n;i++)
    {
        QString list = QString::fromUtf8((char *)fileName[i]);
        ui->DeviceName->addItem(list);
    }
#else
     ui->DeviceName->addItem("192.168.0.10");
#endif
}

void my_printf(uint8_t *str)
{
    printf("%s\n", str);
}


/*Convert distance data to grayscale for display*/
QImage CharToImage(uint16_t *data,uint16_t dist_avg,int width,int height)
{
  int byteCount = width * height ;
  char distData[byteCount];
  for(int i = 0;i<width*height;i++)
  {
      distData[i] = ((float)data[i] / (2*dist_avg) * 255.0) > 255 ? 255: ((float)data[i] / (2*dist_avg) *255.0) ;
  }

  QByteArray imageByteArray = QByteArray( (const char*)distData, byteCount);

  uchar*  transData = (unsigned char*)imageByteArray.data();

  QImage desImage = QImage(transData, width, height, QImage::Format_Grayscale8);

  desImage = desImage.scaled(width*2,height*2,Qt::KeepAspectRatio);
  return desImage;
}



/*Obtain the measurement results obtained from the sensor*/
void * UserGetDataFromSensor(HPS3D_HandleTypeDef *handle,AsyncIObserver_t *event)
{
    do
    {
        if(event->AsyncEvent == ISubject_Event_DataRecvd)
        {
            switch(event->RetPacketType)/*Returns the packet data type*/
            {
                case SIMPLE_ROI_PACKET:
                    dist_average = event->MeasureData.simple_roi_data[0].distance_average;
                    break;
                case FULL_ROI_PACKET:
                    dist_average = event->MeasureData.full_roi_data[0].distance_average;
                    dist_img = CharToImage(FullRoiDistance,dist_average,160,60);
                    break;
                case FULL_DEPTH_PACKET:
                     dist_average = event->MeasureData.full_depth_data->distance_average;
                     dist_img = CharToImage((uint16_t *)event->MeasureData.full_depth_data->distance,dist_average,160,60);
                     if(event->MeasureData.full_depth_data->frame_cnt - FrameCount != 1)
                     {
                         cnt++;
                     }
                     FrameCount = event->MeasureData.full_depth_data->frame_cnt;

                     showImagFlag = true;

                    char acTmpBuf[128] = { 0 };
                    static int iCount = 0;
                    time_t timep;
                    time(&timep);
                    struct tm *l = localtime(&timep);
                    snprintf(acTmpBuf, sizeof(acTmpBuf), "./ply/Cloud_%04d%02d%02d%02d%02d%02d_%05d.ply",
                                l->tm_year + 1900, l->tm_mon + 1, l->tm_mday, l->tm_hour, l->tm_min, l->tm_sec, iCount++);
                   // printf("%s %d\n", acTmpBuf, event->MeasureData.point_cloud_data->points);
                    SavePlyFile((uint8_t *)acTmpBuf,event->MeasureData.point_cloud_data[0]);
                    break;
            }

        }
    }while(0);

    return (void*)0;
}


/*Timer processing function, UI update*/
void MainWindow::timerUpDate()
{
    if(showImagFlag == true)
    {
        ui->label_pic->setPixmap(QPixmap::fromImage(dist_img));
        ui->dist_Labe->setText(QString::number(dist_average));
        ui->FrameCount->setText(QString::number(cnt-1));
        showImagFlag = false;
    }
}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_Connect_clicked()
{
#if false
    QByteArray fileName = ui->DeviceName->currentText().toLatin1();
    HPS_handle.DeviceName = (uint8_t *)fileName.data();
#else
    SetEthernetServerInfo(&HPS_handle,(uint8_t *)"192.168.0.10",12345);
#endif
    /*Device connect*/
    if(RET_OK != Connect(&HPS_handle))
    {
        QMessageBox::information(this, "ConnectStatus", "Connect Falied", "OK");
    }
    else
    {
        /*device init.*/
        if(ConfigInit(&HPS_handle) != RET_OK)
        {
            QMessageBox::information(this, "ConfigInit", "Init Falied", "OK");
            return;
        }

        /*add observer*/
        if(HPS_handle.SyncMode == ASYNC)
        {
            Observer.AsyncEvent = ISubject_Event_DataRecvd;
            Observer.NotifyEnable = true;
            Observer.ObserverID = 0;
            AddObserver(&UserGetDataFromSensor,&HPS_handle,&Observer);
        }

        SetDebugEnable(false);
        SetDebugFunc((void *)&my_printf);
        SetPointCloudEn(true);
        UpdateTimer = new QTimer(this);
        connect(UpdateTimer,SIGNAL(timeout()),this,SLOT(timerUpDate()));
        UpdateTimer->start(1);
        QMessageBox::information(this, "ConnectStatus", "Connect Succeed", "OK");
    }
}

void MainWindow::on_DisConnect_clicked()
{
   if(RET_OK != DisConnect(&HPS_handle))
   {
       QMessageBox::information(this, "ConnectStatus", "DisConnect Falied", "OK");
   }

   UpdateTimer->stop();

   if(RemoveDevice(&HPS_handle) != RET_OK)
   {
        QMessageBox::information(this, "RemoveDevice", "RemoveDevice Falied", "OK");
   }
   else
   {
        QMessageBox::information(this, "ConnectStatus", "DisConnect Succeed", "OK");
   }
}

void MainWindow::on_SingleMeasure_clicked()
{
    MeasureDataTypeDef data;

    if(SingleMeasurement(&HPS_handle) != RET_OK)
    {
         QMessageBox::information(this, "Tip", "SingleMeasurement error!", "OK");
    }
    else
    {

    }

    switch(HPS_handle.RetPacketType)
    {
        case SIMPLE_ROI_PACKET:
            dist_average = HPS_handle.MeasureData.simple_roi_data[0].distance_average;
            break;
        case FULL_ROI_PACKET:
            dist_average = HPS_handle.MeasureData.full_roi_data[0].distance_average;
            dist_img = CharToImage(FullRoiDistance,dist_average,160,60);
            break;
        case FULL_DEPTH_PACKET:
             dist_average = HPS_handle.MeasureData.full_depth_data->distance_average;
             dist_img = CharToImage((uint16_t *)HPS_handle.MeasureData.full_depth_data->distance,dist_average,160,60);
             break;
        case SIMPLE_DEPTH_PACKET:
            dist_average = HPS_handle.MeasureData.simple_depth_data->distance_average;
            break;
        default:
            break;
    }
    ui->dist_Labe->setText(QString::number(dist_average));
    ui->label_pic->setPixmap(QPixmap::fromImage(dist_img));
}

void MainWindow::on_Start_clicked()
{
   HPS_handle.SyncMode = ASYNC;
   HPS_handle.RunMode = RUN_CONTINUOUS;
   SetRunMode(&HPS_handle);

}

void MainWindow::on_Stop_clicked()
{            
    HPS_handle.RunMode = RUN_IDLE;
    SetRunMode(&HPS_handle);
}
