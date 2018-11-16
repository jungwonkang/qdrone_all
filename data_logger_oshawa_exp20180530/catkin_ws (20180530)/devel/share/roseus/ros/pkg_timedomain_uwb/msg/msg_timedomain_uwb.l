;; Auto-generated. Do not edit!


(when (boundp 'pkg_timedomain_uwb::msg_timedomain_uwb)
  (if (not (find-package "PKG_TIMEDOMAIN_UWB"))
    (make-package "PKG_TIMEDOMAIN_UWB"))
  (shadow 'msg_timedomain_uwb (find-package "PKG_TIMEDOMAIN_UWB")))
(unless (find-package "PKG_TIMEDOMAIN_UWB::MSG_TIMEDOMAIN_UWB")
  (make-package "PKG_TIMEDOMAIN_UWB::MSG_TIMEDOMAIN_UWB"))

(in-package "ROS")
;;//! \htmlinclude msg_timedomain_uwb.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass pkg_timedomain_uwb::msg_timedomain_uwb
  :super ros::object
  :slots (_header _id_module_uwb _range _range_err ))

(defmethod pkg_timedomain_uwb::msg_timedomain_uwb
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:id_module_uwb __id_module_uwb) 0)
    ((:range __range) 0.0)
    ((:range_err __range_err) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _id_module_uwb (round __id_module_uwb))
   (setq _range (float __range))
   (setq _range_err (float __range_err))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:id_module_uwb
   (&optional __id_module_uwb)
   (if __id_module_uwb (setq _id_module_uwb __id_module_uwb)) _id_module_uwb)
  (:range
   (&optional __range)
   (if __range (setq _range __range)) _range)
  (:range_err
   (&optional __range_err)
   (if __range_err (setq _range_err __range_err)) _range_err)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; uint32 _id_module_uwb
    4
    ;; float64 _range
    8
    ;; float64 _range_err
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; uint32 _id_module_uwb
       (write-long _id_module_uwb s)
     ;; float64 _range
       (sys::poke _range (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _range_err
       (sys::poke _range_err (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; uint32 _id_module_uwb
     (setq _id_module_uwb (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _range
     (setq _range (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _range_err
     (setq _range_err (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get pkg_timedomain_uwb::msg_timedomain_uwb :md5sum-) "5832270dc2da80beb97f2d958efffd99")
(setf (get pkg_timedomain_uwb::msg_timedomain_uwb :datatype-) "pkg_timedomain_uwb/msg_timedomain_uwb")
(setf (get pkg_timedomain_uwb::msg_timedomain_uwb :definition-)
      "Header  header
uint32  id_module_uwb
float64 range
float64 range_err


================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

")



(provide :pkg_timedomain_uwb/msg_timedomain_uwb "5832270dc2da80beb97f2d958efffd99")


