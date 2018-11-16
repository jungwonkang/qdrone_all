/** @ cls_sensor.h
 *  @ Feb, 2018
 *
 *  written by Jungwon Kang
 *
 */


// https://raw.githubusercontent.com/ros/ros_tutorials/groovy-devel/roscpp_tutorials/listener_class/listener_class.cpp
// https://answers.ros.org/question/59725/publishing-to-a-topic-via-subscriber-callback-function/?answer=59738#post-id-59738


#ifndef CLS_SENSOR_H
#define CLS_SENSOR_H

// ROS includes
#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/QuaternionStamped.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/Float32.h>

#include "common_header.h"

// msg
//#include "dji_sdk/dji_sdk.h"
//#include "pkg_timedomain_uwb/msg_timedomain_uwb.h"
#include "/home/york2/catkin_ws/devel/include/pkg_timedomain_uwb/msg_timedomain_uwb.h"

#include "cls_loc_base.h"


class CLS_sensor
{
  public:
    CLS_sensor();
    CLS_sensor(CLS_loc_base* pobj);
    ~CLS_sensor();

    void callback_timedomain_uwb (const pkg_timedomain_uwb::msg_timedomain_uwb::ConstPtr& msg);

  private:
    void _init_subs();

  private:
    ros::NodeHandle m_nh;
    ros::Subscriber m_subs_uwb;

    CLS_loc_base*   m_pobj_loc;

};


#endif // CLS_SENSOR_H

