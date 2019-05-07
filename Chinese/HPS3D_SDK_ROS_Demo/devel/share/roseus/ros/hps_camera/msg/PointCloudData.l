;; Auto-generated. Do not edit!


(when (boundp 'hps_camera::PointCloudData)
  (if (not (find-package "HPS_CAMERA"))
    (make-package "HPS_CAMERA"))
  (shadow 'PointCloudData (find-package "HPS_CAMERA")))
(unless (find-package "HPS_CAMERA::POINTCLOUDDATA")
  (make-package "HPS_CAMERA::POINTCLOUDDATA"))

(in-package "ROS")
;;//! \htmlinclude PointCloudData.msg.html


(defclass hps_camera::PointCloudData
  :super ros::object
  :slots (_x _y _z _width _height _points _distance_average ))

(defmethod hps_camera::PointCloudData
  (:init
   (&key
    ((:x __x) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:y __y) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:z __z) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:width __width) 0)
    ((:height __height) 0)
    ((:points __points) 0)
    ((:distance_average __distance_average) 0)
    )
   (send-super :init)
   (setq _x __x)
   (setq _y __y)
   (setq _z __z)
   (setq _width (round __width))
   (setq _height (round __height))
   (setq _points (round __points))
   (setq _distance_average (round __distance_average))
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:z
   (&optional __z)
   (if __z (setq _z __z)) _z)
  (:width
   (&optional __width)
   (if __width (setq _width __width)) _width)
  (:height
   (&optional __height)
   (if __height (setq _height __height)) _height)
  (:points
   (&optional __points)
   (if __points (setq _points __points)) _points)
  (:distance_average
   (&optional __distance_average)
   (if __distance_average (setq _distance_average __distance_average)) _distance_average)
  (:serialization-length
   ()
   (+
    ;; float32[] _x
    (* 4    (length _x)) 4
    ;; float32[] _y
    (* 4    (length _y)) 4
    ;; float32[] _z
    (* 4    (length _z)) 4
    ;; uint16 _width
    2
    ;; uint16 _height
    2
    ;; uint16 _points
    2
    ;; uint16 _distance_average
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32[] _x
     (write-long (length _x) s)
     (dotimes (i (length _x))
       (sys::poke (elt _x i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[] _y
     (write-long (length _y) s)
     (dotimes (i (length _y))
       (sys::poke (elt _y i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[] _z
     (write-long (length _z) s)
     (dotimes (i (length _z))
       (sys::poke (elt _z i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; uint16 _width
       (write-word _width s)
     ;; uint16 _height
       (write-word _height s)
     ;; uint16 _points
       (write-word _points s)
     ;; uint16 _distance_average
       (write-word _distance_average s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32[] _x
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _x (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _x i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;; float32[] _y
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _y (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _y i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;; float32[] _z
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _z (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _z i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;; uint16 _width
     (setq _width (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _height
     (setq _height (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _points
     (setq _points (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _distance_average
     (setq _distance_average (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get hps_camera::PointCloudData :md5sum-) "9512facb125a4b5d4f71e2234ee7eaf8")
(setf (get hps_camera::PointCloudData :datatype-) "hps_camera/PointCloudData")
(setf (get hps_camera::PointCloudData :definition-)
      "float32[] x
float32[] y
float32[] z
uint16 width
uint16 height
uint16 points

uint16 distance_average


")



(provide :hps_camera/PointCloudData "9512facb125a4b5d4f71e2234ee7eaf8")


