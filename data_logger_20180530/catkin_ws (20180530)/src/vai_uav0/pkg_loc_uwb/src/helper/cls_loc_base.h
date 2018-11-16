/** @ cls_loc_base.h
 *  @ Feb, 2018
 *
 *  written by Jungwon Kang
 *
 */


// https://raw.githubusercontent.com/ros/ros_tutorials/groovy-devel/roscpp_tutorials/listener_class/listener_class.cpp
// https://answers.ros.org/question/59725/publishing-to-a-topic-via-subscriber-callback-function/?answer=59738#post-id-59738


#ifndef CLS_LOC_BASE_H
#define CLS_LOC_BASE_H

//// ROS includes
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


//// Loc core
#include "core/loc_core_void.h"
#include "cls_visualize.h"

#include "common_header.h"

//#include <stdint.h>
#include <inttypes.h>

// msg
//#include "dji_sdk/dji_sdk.h"
//#include "pkg_timedomain_uwb/msg_timedomain_uwb.h"


class CLS_loc_base
{
  public:
    CLS_loc_base();
    ~CLS_loc_base();

    void  transfer_sensor_data_to_loc_base(MySensorData data_in);   // called by sensor data input
    void  callback_timer1(const ros::TimerEvent& timer_event);      // called periodically for output

private:
    void _init_data_for_visualize();

  private:
    ros::NodeHandle m_nh;
    ros::Timer      m_timer1;

    Loc_core_void   m_loc_core_void;
    CLS_visualize   m_obj_visualize;

    bool            m_b_visualize;
    tf::TransformBroadcaster  m_br_tf_a;
    tf::TransformBroadcaster  m_br_tf_b;

    bool            m_b_save_data_in_file;
    FILE*           m_fp1;

    ros::Time       m_ros_time_uwb_this;    // for UWB
    ros::Time       m_ros_time_uwb_prev;

    ros::Time       m_ros_time_att_this;    // for DJI-attitude
    ros::Time       m_ros_time_att_prev;

    ros::Time       m_ros_time_imu_this;    // for DJI-imu
    ros::Time       m_ros_time_imu_prev;

    ros::Time       m_ros_time0;
    bool            m_b_set_ros_time0;

};


#endif // CLS_LOC_BASE_H

