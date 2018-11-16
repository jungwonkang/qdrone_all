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


#include "cls_visualize.h"

#include "common_header.h"

//#include <stdint.h>
#include <inttypes.h>


class CLS_loc_base
{
  public:
    CLS_loc_base();
    ~CLS_loc_base();

    void  transfer_sensor_data_to_loc_base(MySensorData data_in);   // called by sensor data input

private:
    void _init_data_for_visualize();

  private:
    ros::NodeHandle m_nh;
    ros::Timer      m_timer1;

    CLS_visualize   m_obj_visualize;

    bool            m_b_visualize;

    bool            m_b_save_data_in_file;
    FILE*           m_fp1;

    ros::Time       m_ros_time_uwb_this;    // for UWB
    ros::Time       m_ros_time_uwb_prev;

    ros::Time       m_ros_time0;
    bool            m_b_set_ros_time0;

};


#endif // CLS_LOC_BASE_H

