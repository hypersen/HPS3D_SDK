;; Auto-generated. Do not edit!


(when (boundp 'hps_camera::camera)
  (if (not (find-package "HPS_CAMERA"))
    (make-package "HPS_CAMERA"))
  (shadow 'camera (find-package "HPS_CAMERA")))
(unless (find-package "HPS_CAMERA::CAMERA")
  (make-package "HPS_CAMERA::CAMERA"))
(unless (find-package "HPS_CAMERA::CAMERAREQUEST")
  (make-package "HPS_CAMERA::CAMERAREQUEST"))
(unless (find-package "HPS_CAMERA::CAMERARESPONSE")
  (make-package "HPS_CAMERA::CAMERARESPONSE"))

(in-package "ROS")





(defclass hps_camera::cameraRequest
  :super ros::object
  :slots (_client_node_name ))

(defmethod hps_camera::cameraRequest
  (:init
   (&key
    ((:client_node_name __client_node_name) "")
    )
   (send-super :init)
   (setq _client_node_name (string __client_node_name))
   self)
  (:client_node_name
   (&optional __client_node_name)
   (if __client_node_name (setq _client_node_name __client_node_name)) _client_node_name)
  (:serialization-length
   ()
   (+
    ;; string _client_node_name
    4 (length _client_node_name)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _client_node_name
       (write-long (length _client_node_name) s) (princ _client_node_name s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _client_node_name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _client_node_name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass hps_camera::cameraResponse
  :super ros::object
  :slots (_control_cmd ))

(defmethod hps_camera::cameraResponse
  (:init
   (&key
    ((:control_cmd __control_cmd) "")
    )
   (send-super :init)
   (setq _control_cmd (string __control_cmd))
   self)
  (:control_cmd
   (&optional __control_cmd)
   (if __control_cmd (setq _control_cmd __control_cmd)) _control_cmd)
  (:serialization-length
   ()
   (+
    ;; string _control_cmd
    4 (length _control_cmd)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _control_cmd
       (write-long (length _control_cmd) s) (princ _control_cmd s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _control_cmd
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _control_cmd (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass hps_camera::camera
  :super ros::object
  :slots ())

(setf (get hps_camera::camera :md5sum-) "856731728679b0f365031a50c1aa4795")
(setf (get hps_camera::camera :datatype-) "hps_camera/camera")
(setf (get hps_camera::camera :request) hps_camera::cameraRequest)
(setf (get hps_camera::camera :response) hps_camera::cameraResponse)

(defmethod hps_camera::cameraRequest
  (:response () (instance hps_camera::cameraResponse :init)))

(setf (get hps_camera::cameraRequest :md5sum-) "856731728679b0f365031a50c1aa4795")
(setf (get hps_camera::cameraRequest :datatype-) "hps_camera/cameraRequest")
(setf (get hps_camera::cameraRequest :definition-)
      "string client_node_name
---
string control_cmd

")

(setf (get hps_camera::cameraResponse :md5sum-) "856731728679b0f365031a50c1aa4795")
(setf (get hps_camera::cameraResponse :datatype-) "hps_camera/cameraResponse")
(setf (get hps_camera::cameraResponse :definition-)
      "string client_node_name
---
string control_cmd

")



(provide :hps_camera/camera "856731728679b0f365031a50c1aa4795")


