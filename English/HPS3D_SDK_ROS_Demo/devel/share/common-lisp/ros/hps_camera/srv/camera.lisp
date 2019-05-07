; Auto-generated. Do not edit!


(cl:in-package hps_camera-srv)


;//! \htmlinclude camera-request.msg.html

(cl:defclass <camera-request> (roslisp-msg-protocol:ros-message)
  ((client_node_name
    :reader client_node_name
    :initarg :client_node_name
    :type cl:string
    :initform ""))
)

(cl:defclass camera-request (<camera-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <camera-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'camera-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hps_camera-srv:<camera-request> is deprecated: use hps_camera-srv:camera-request instead.")))

(cl:ensure-generic-function 'client_node_name-val :lambda-list '(m))
(cl:defmethod client_node_name-val ((m <camera-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hps_camera-srv:client_node_name-val is deprecated.  Use hps_camera-srv:client_node_name instead.")
  (client_node_name m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <camera-request>) ostream)
  "Serializes a message object of type '<camera-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'client_node_name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'client_node_name))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <camera-request>) istream)
  "Deserializes a message object of type '<camera-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'client_node_name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'client_node_name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<camera-request>)))
  "Returns string type for a service object of type '<camera-request>"
  "hps_camera/cameraRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'camera-request)))
  "Returns string type for a service object of type 'camera-request"
  "hps_camera/cameraRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<camera-request>)))
  "Returns md5sum for a message object of type '<camera-request>"
  "856731728679b0f365031a50c1aa4795")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'camera-request)))
  "Returns md5sum for a message object of type 'camera-request"
  "856731728679b0f365031a50c1aa4795")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<camera-request>)))
  "Returns full string definition for message of type '<camera-request>"
  (cl:format cl:nil "string client_node_name~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'camera-request)))
  "Returns full string definition for message of type 'camera-request"
  (cl:format cl:nil "string client_node_name~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <camera-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'client_node_name))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <camera-request>))
  "Converts a ROS message object to a list"
  (cl:list 'camera-request
    (cl:cons ':client_node_name (client_node_name msg))
))
;//! \htmlinclude camera-response.msg.html

(cl:defclass <camera-response> (roslisp-msg-protocol:ros-message)
  ((control_cmd
    :reader control_cmd
    :initarg :control_cmd
    :type cl:string
    :initform ""))
)

(cl:defclass camera-response (<camera-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <camera-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'camera-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hps_camera-srv:<camera-response> is deprecated: use hps_camera-srv:camera-response instead.")))

(cl:ensure-generic-function 'control_cmd-val :lambda-list '(m))
(cl:defmethod control_cmd-val ((m <camera-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hps_camera-srv:control_cmd-val is deprecated.  Use hps_camera-srv:control_cmd instead.")
  (control_cmd m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <camera-response>) ostream)
  "Serializes a message object of type '<camera-response>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'control_cmd))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'control_cmd))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <camera-response>) istream)
  "Deserializes a message object of type '<camera-response>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'control_cmd) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'control_cmd) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<camera-response>)))
  "Returns string type for a service object of type '<camera-response>"
  "hps_camera/cameraResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'camera-response)))
  "Returns string type for a service object of type 'camera-response"
  "hps_camera/cameraResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<camera-response>)))
  "Returns md5sum for a message object of type '<camera-response>"
  "856731728679b0f365031a50c1aa4795")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'camera-response)))
  "Returns md5sum for a message object of type 'camera-response"
  "856731728679b0f365031a50c1aa4795")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<camera-response>)))
  "Returns full string definition for message of type '<camera-response>"
  (cl:format cl:nil "string control_cmd~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'camera-response)))
  "Returns full string definition for message of type 'camera-response"
  (cl:format cl:nil "string control_cmd~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <camera-response>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'control_cmd))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <camera-response>))
  "Converts a ROS message object to a list"
  (cl:list 'camera-response
    (cl:cons ':control_cmd (control_cmd msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'camera)))
  'camera-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'camera)))
  'camera-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'camera)))
  "Returns string type for a service object of type '<camera>"
  "hps_camera/camera")