;; Auto-generated. Do not edit!


(when (boundp 'hps_camera::distance)
  (if (not (find-package "HPS_CAMERA"))
    (make-package "HPS_CAMERA"))
  (shadow 'distance (find-package "HPS_CAMERA")))
(unless (find-package "HPS_CAMERA::DISTANCE")
  (make-package "HPS_CAMERA::DISTANCE"))

(in-package "ROS")
;;//! \htmlinclude distance.msg.html


(defclass hps_camera::distance
  :super ros::object
  :slots (_distance_average ))

(defmethod hps_camera::distance
  (:init
   (&key
    ((:distance_average __distance_average) 0)
    )
   (send-super :init)
   (setq _distance_average (round __distance_average))
   self)
  (:distance_average
   (&optional __distance_average)
   (if __distance_average (setq _distance_average __distance_average)) _distance_average)
  (:serialization-length
   ()
   (+
    ;; uint16 _distance_average
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint16 _distance_average
       (write-word _distance_average s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint16 _distance_average
     (setq _distance_average (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get hps_camera::distance :md5sum-) "7abbfa2a9d95604277f1b4a37d989bb6")
(setf (get hps_camera::distance :datatype-) "hps_camera/distance")
(setf (get hps_camera::distance :definition-)
      "uint16 distance_average

")



(provide :hps_camera/distance "7abbfa2a9d95604277f1b4a37d989bb6")


