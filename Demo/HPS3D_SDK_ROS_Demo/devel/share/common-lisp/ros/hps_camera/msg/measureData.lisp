; Auto-generated. Do not edit!


(cl:in-package hps_camera-msg)


;//! \htmlinclude measureData.msg.html

(cl:defclass <measureData> (roslisp-msg-protocol:ros-message)
  ((point_cloud_data
    :reader point_cloud_data
    :initarg :point_cloud_data
    :type hps_camera-msg:PointCloudData
    :initform (cl:make-instance 'hps_camera-msg:PointCloudData)))
)

(cl:defclass measureData (<measureData>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <measureData>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'measureData)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hps_camera-msg:<measureData> is deprecated: use hps_camera-msg:measureData instead.")))

(cl:ensure-generic-function 'point_cloud_data-val :lambda-list '(m))
(cl:defmethod point_cloud_data-val ((m <measureData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hps_camera-msg:point_cloud_data-val is deprecated.  Use hps_camera-msg:point_cloud_data instead.")
  (point_cloud_data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <measureData>) ostream)
  "Serializes a message object of type '<measureData>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'point_cloud_data) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <measureData>) istream)
  "Deserializes a message object of type '<measureData>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'point_cloud_data) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<measureData>)))
  "Returns string type for a message object of type '<measureData>"
  "hps_camera/measureData")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'measureData)))
  "Returns string type for a message object of type 'measureData"
  "hps_camera/measureData")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<measureData>)))
  "Returns md5sum for a message object of type '<measureData>"
  "d25e7f28a0c985f85d20386b940737b5")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'measureData)))
  "Returns md5sum for a message object of type 'measureData"
  "d25e7f28a0c985f85d20386b940737b5")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<measureData>)))
  "Returns full string definition for message of type '<measureData>"
  (cl:format cl:nil "hps_camera/PointCloudData point_cloud_data~%~%================================================================================~%MSG: hps_camera/PointCloudData~%float32[] x~%float32[] y~%float32[] z~%uint16 width~%uint16 height~%uint16 points~%~%uint16 distance_average~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'measureData)))
  "Returns full string definition for message of type 'measureData"
  (cl:format cl:nil "hps_camera/PointCloudData point_cloud_data~%~%================================================================================~%MSG: hps_camera/PointCloudData~%float32[] x~%float32[] y~%float32[] z~%uint16 width~%uint16 height~%uint16 points~%~%uint16 distance_average~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <measureData>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'point_cloud_data))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <measureData>))
  "Converts a ROS message object to a list"
  (cl:list 'measureData
    (cl:cons ':point_cloud_data (point_cloud_data msg))
))
