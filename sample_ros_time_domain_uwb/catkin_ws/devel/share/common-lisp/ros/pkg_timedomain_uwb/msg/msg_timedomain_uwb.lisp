; Auto-generated. Do not edit!


(cl:in-package pkg_timedomain_uwb-msg)


;//! \htmlinclude msg_timedomain_uwb.msg.html

(cl:defclass <msg_timedomain_uwb> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (id_module_uwb
    :reader id_module_uwb
    :initarg :id_module_uwb
    :type cl:integer
    :initform 0)
   (range
    :reader range
    :initarg :range
    :type cl:float
    :initform 0.0)
   (range_err
    :reader range_err
    :initarg :range_err
    :type cl:float
    :initform 0.0))
)

(cl:defclass msg_timedomain_uwb (<msg_timedomain_uwb>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <msg_timedomain_uwb>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'msg_timedomain_uwb)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name pkg_timedomain_uwb-msg:<msg_timedomain_uwb> is deprecated: use pkg_timedomain_uwb-msg:msg_timedomain_uwb instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <msg_timedomain_uwb>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pkg_timedomain_uwb-msg:header-val is deprecated.  Use pkg_timedomain_uwb-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'id_module_uwb-val :lambda-list '(m))
(cl:defmethod id_module_uwb-val ((m <msg_timedomain_uwb>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pkg_timedomain_uwb-msg:id_module_uwb-val is deprecated.  Use pkg_timedomain_uwb-msg:id_module_uwb instead.")
  (id_module_uwb m))

(cl:ensure-generic-function 'range-val :lambda-list '(m))
(cl:defmethod range-val ((m <msg_timedomain_uwb>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pkg_timedomain_uwb-msg:range-val is deprecated.  Use pkg_timedomain_uwb-msg:range instead.")
  (range m))

(cl:ensure-generic-function 'range_err-val :lambda-list '(m))
(cl:defmethod range_err-val ((m <msg_timedomain_uwb>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pkg_timedomain_uwb-msg:range_err-val is deprecated.  Use pkg_timedomain_uwb-msg:range_err instead.")
  (range_err m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <msg_timedomain_uwb>) ostream)
  "Serializes a message object of type '<msg_timedomain_uwb>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id_module_uwb)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'id_module_uwb)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'id_module_uwb)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'id_module_uwb)) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'range))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'range_err))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <msg_timedomain_uwb>) istream)
  "Deserializes a message object of type '<msg_timedomain_uwb>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id_module_uwb)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'id_module_uwb)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'id_module_uwb)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'id_module_uwb)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'range) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'range_err) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<msg_timedomain_uwb>)))
  "Returns string type for a message object of type '<msg_timedomain_uwb>"
  "pkg_timedomain_uwb/msg_timedomain_uwb")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'msg_timedomain_uwb)))
  "Returns string type for a message object of type 'msg_timedomain_uwb"
  "pkg_timedomain_uwb/msg_timedomain_uwb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<msg_timedomain_uwb>)))
  "Returns md5sum for a message object of type '<msg_timedomain_uwb>"
  "5832270dc2da80beb97f2d958efffd99")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'msg_timedomain_uwb)))
  "Returns md5sum for a message object of type 'msg_timedomain_uwb"
  "5832270dc2da80beb97f2d958efffd99")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<msg_timedomain_uwb>)))
  "Returns full string definition for message of type '<msg_timedomain_uwb>"
  (cl:format cl:nil "Header  header~%uint32  id_module_uwb~%float64 range~%float64 range_err~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'msg_timedomain_uwb)))
  "Returns full string definition for message of type 'msg_timedomain_uwb"
  (cl:format cl:nil "Header  header~%uint32  id_module_uwb~%float64 range~%float64 range_err~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <msg_timedomain_uwb>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <msg_timedomain_uwb>))
  "Converts a ROS message object to a list"
  (cl:list 'msg_timedomain_uwb
    (cl:cons ':header (header msg))
    (cl:cons ':id_module_uwb (id_module_uwb msg))
    (cl:cons ':range (range msg))
    (cl:cons ':range_err (range_err msg))
))
