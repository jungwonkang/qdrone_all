// Generated by gencpp from file dji_sdk/MissionWpGetInfoResponse.msg
// DO NOT EDIT!


#ifndef DJI_SDK_MESSAGE_MISSIONWPGETINFORESPONSE_H
#define DJI_SDK_MESSAGE_MISSIONWPGETINFORESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <dji_sdk/MissionWaypointTask.h>

namespace dji_sdk
{
template <class ContainerAllocator>
struct MissionWpGetInfoResponse_
{
  typedef MissionWpGetInfoResponse_<ContainerAllocator> Type;

  MissionWpGetInfoResponse_()
    : waypoint_task()  {
    }
  MissionWpGetInfoResponse_(const ContainerAllocator& _alloc)
    : waypoint_task(_alloc)  {
  (void)_alloc;
    }



   typedef  ::dji_sdk::MissionWaypointTask_<ContainerAllocator>  _waypoint_task_type;
  _waypoint_task_type waypoint_task;




  typedef boost::shared_ptr< ::dji_sdk::MissionWpGetInfoResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::dji_sdk::MissionWpGetInfoResponse_<ContainerAllocator> const> ConstPtr;

}; // struct MissionWpGetInfoResponse_

typedef ::dji_sdk::MissionWpGetInfoResponse_<std::allocator<void> > MissionWpGetInfoResponse;

typedef boost::shared_ptr< ::dji_sdk::MissionWpGetInfoResponse > MissionWpGetInfoResponsePtr;
typedef boost::shared_ptr< ::dji_sdk::MissionWpGetInfoResponse const> MissionWpGetInfoResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::dji_sdk::MissionWpGetInfoResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::dji_sdk::MissionWpGetInfoResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace dji_sdk

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'nav_msgs': ['/opt/ros/kinetic/share/nav_msgs/cmake/../msg'], 'dji_sdk': ['/home/york1/catkin_ws/src/vai_uav0/dji_sdk/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg'], 'sensor_msgs': ['/opt/ros/kinetic/share/sensor_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::dji_sdk::MissionWpGetInfoResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::dji_sdk::MissionWpGetInfoResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::dji_sdk::MissionWpGetInfoResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::dji_sdk::MissionWpGetInfoResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::dji_sdk::MissionWpGetInfoResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::dji_sdk::MissionWpGetInfoResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::dji_sdk::MissionWpGetInfoResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "412556517acb90aa4c3e713fbb867865";
  }

  static const char* value(const ::dji_sdk::MissionWpGetInfoResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x412556517acb90aaULL;
  static const uint64_t static_value2 = 0x4c3e713fbb867865ULL;
};

template<class ContainerAllocator>
struct DataType< ::dji_sdk::MissionWpGetInfoResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "dji_sdk/MissionWpGetInfoResponse";
  }

  static const char* value(const ::dji_sdk::MissionWpGetInfoResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::dji_sdk::MissionWpGetInfoResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "MissionWaypointTask waypoint_task\n\
\n\
================================================================================\n\
MSG: dji_sdk/MissionWaypointTask\n\
# constant for action_on_finish\n\
uint8 FINISH_NO_ACTION       = 0  # no action\n\
uint8 FINISH_RETURN_TO_HOME  = 1  # return to home\n\
uint8 FINISH_AUTO_LANDING    = 2  # auto landing\n\
uint8 FINISH_RETURN_TO_POINT = 3  # return to point 0\n\
uint8 FINISH_NO_EXIT         = 4  # infinite mode， no exit\n\
\n\
# constant for yaw_mode\n\
uint8 YAW_MODE_AUTO     = 0       # auto mode (point to next waypoint)\n\
uint8 YAW_MODE_LOCK     = 1       # lock as an initial value\n\
uint8 YAW_MODE_RC       = 2       # controlled by RC\n\
uint8 YAW_MODE_WAYPOINT = 3       # use waypoint's yaw(tgt_yaw)\n\
\n\
# constant for trace_mode\n\
uint8 TRACE_POINT       = 0       # point to point, after reaching the target waypoint hover, complete waypt action (if any), then fly to the next waypt\n\
uint8 TRACE_COORDINATED = 1       # 1: Coordinated turn mode, smooth transition between waypts, no waypts task\n\
\n\
# constants for action_on_rc_lost\n\
uint8 ACTION_FREE       = 0       # exit waypoint and failsafe\n\
uint8 ACTION_AUTO       = 1       # continue the waypoint\n\
\n\
# constants for gimbal_pitch_mode\n\
uint8 GIMBAL_PITCH_FREE = 0       # free mode, no control on gimbal\n\
uint8 GIMBAL_PITCH_AUTO = 1       # auto mode, Smooth transition between waypoints on gimbal\n\
\n\
float32 velocity_range    # Maximum speed joystick input(2~15m)\n\
float32 idle_velocity     # Cruising Speed (without joystick input, no more than vel_cmd_range)\n\
uint8 action_on_finish    # See constants above for possible actions\n\
uint8 mission_exec_times  # 1: once ; 2: twice\n\
uint8 yaw_mode            # see constants above for possible yaw modes\n\
uint8 trace_mode          # see constants above for possible trace modes\n\
uint8 action_on_rc_lost   # see constants above for possible actions\n\
uint8 gimbal_pitch_mode   # see constants above for pissible gimbal modes\n\
MissionWaypoint[] mission_waypoint  # a vector of waypoints\n\
\n\
\n\
================================================================================\n\
MSG: dji_sdk/MissionWaypoint\n\
float64 latitude          # degree\n\
float64 longitude         # degree\n\
float32 altitude          # relative altitude from takeoff point\n\
float32 damping_distance  # Bend length (effective coordinated turn mode only)\n\
int16 target_yaw          # Yaw (degree)\n\
int16 target_gimbal_pitch # Gimbal pitch\n\
uint8 turn_mode           # 0: clockwise, 1: counter-clockwise\n\
uint8 has_action          # 0: no, 1: yes\n\
uint16 action_time_limit\n\
MissionWaypointAction waypoint_action\n\
\n\
================================================================================\n\
MSG: dji_sdk/MissionWaypointAction\n\
# action_repeat\n\
# lower 4 bit: Total number of actions\n\
# hight 4 bit: Total running times\n\
uint8 action_repeat\n\
uint8[16] command_list\n\
uint16[16] command_parameter\n\
";
  }

  static const char* value(const ::dji_sdk::MissionWpGetInfoResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::dji_sdk::MissionWpGetInfoResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.waypoint_task);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct MissionWpGetInfoResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::dji_sdk::MissionWpGetInfoResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::dji_sdk::MissionWpGetInfoResponse_<ContainerAllocator>& v)
  {
    s << indent << "waypoint_task: ";
    s << std::endl;
    Printer< ::dji_sdk::MissionWaypointTask_<ContainerAllocator> >::stream(s, indent + "  ", v.waypoint_task);
  }
};

} // namespace message_operations
} // namespace ros

#endif // DJI_SDK_MESSAGE_MISSIONWPGETINFORESPONSE_H
