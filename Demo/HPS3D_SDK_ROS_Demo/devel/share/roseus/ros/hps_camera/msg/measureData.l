;; Auto-generated. Do not edit!


(when (boundp 'hps_camera::measureData)
  (if (not (find-package "HPS_CAMERA"))
    (make-package "HPS_CAMERA"))
  (shadow 'measureData (find-package "HPS_CAMERA")))
(unless (find-package "HPS_CAMERA::MEASUREDATA")
  (make-package "HPS_CAMERA::MEASUREDATA"))

(in-package "ROS")
;;//! \htmlinclude measureData.msg.html


(defclass hps_camera::measureData
  :super ros::object
  :slots (_point_cloud_data ))

(defmethod hps_camera::measureData
  (:init
   (&key
    ((:point_cloud_data __point_cloud_data) (instance hps_camera::PointCloudData :init))
    )
   (send-super :init)
   (setq _point_cloud_data __point_cloud_data)
   self)
  (:point_cloud_data
   (&rest __point_cloud_data)
   (if (keywordp (car __point_cloud_data))
       (send* _point_cloud_data __point_cloud_data)
     (progn
       (if __point_cloud_data (setq _point_cloud_data (car __point_cloud_data)))
       _point_cloud_data)))
  (:serialization-length
   ()
   (+
    ;; hps_camera/PointCloudData _point_cloud_data
    (send _point_cloud_data :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; hps_camera/PointCloudData _point_cloud_data
       (send _point_cloud_data :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; hps_camera/PointCloudData _point_cloud_data
     (send _point_cloud_data :deserialize buf ptr-) (incf ptr- (send _point_cloud_data :serialization-length))
   ;;
   self)
  )

(setf (get hps_camera::measureData :md5sum-) "d25e7f28a0c985f85d20386b940737b5")
(setf (get hps_camera::measureData :datatype-) "hps_camera/measureData")
(setf (get hps_camera::measureData :definition-)
      "hps_camera/PointCloudData point_cloud_data

================================================================================
MSG: hps_camera/PointCloudData
float32[] x
float32[] y
float32[] z
uint16 width
uint16 height
uint16 points

uint16 distance_average


")



(provide :hps_camera/measureData "d25e7f28a0c985f85d20386b940737b5")


