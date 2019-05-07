; Auto-generated. Do not edit!


(cl:in-package hps_camera-msg)


;//! \htmlinclude distance.msg.html

(cl:defclass <distance> (roslisp-msg-protocol:ros-message)
  ((distance_average
    :reader distance_average
    :initarg :distance_average
    :type cl:fixnum
    :initform 0))
)

(cl:defclass distance (<distance>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <distance>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'distance)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hps_camera-msg:<distance> is deprecated: use hps_camera-msg:distance instead.")))

(cl:ensure-generic-function 'distance_average-val :lambda-list '(m))
(cl:defmethod distance_average-val ((m <distance>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hps_camera-msg:distance_average-val is deprecated.  Use hps_camera-msg:distance_average instead.")
  (distance_average m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <distance>) ostream)
  "Serializes a message object of type '<distance>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'distance_average)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'distance_average)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <distance>) istream)
  "Deserializes a message object of type '<distance>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'distance_average)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'distance_average)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<distance>)))
  "Returns string type for a message object of type '<distance>"
  "hps_camera/distance")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'distance)))
  "Returns string type for a message object of type 'distance"
  "hps_camera/distance")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<distance>)))
  "Returns md5sum for a message object of type '<distance>"
  "7abbfa2a9d95604277f1b4a37d989bb6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'distance)))
  "Returns md5sum for a message object of type 'distance"
  "7abbfa2a9d95604277f1b4a37d989bb6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<distance>)))
  "Returns full string definition for message of type '<distance>"
  (cl:format cl:nil "uint16 distance_average~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'distance)))
  "Returns full string definition for message of type 'distance"
  (cl:format cl:nil "uint16 distance_average~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <distance>))
  (cl:+ 0
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <distance>))
  "Converts a ROS message object to a list"
  (cl:list 'distance
    (cl:cons ':distance_average (distance_average msg))
))
