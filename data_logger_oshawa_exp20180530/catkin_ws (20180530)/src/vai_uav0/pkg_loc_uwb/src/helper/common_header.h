/** @ common_header.h
 *  @ Feb, 2018
 *
 *  written by Jungwon Kang
 *
 */

#ifndef COMMON_HEADER_H
#define COMMON_HEADER_H

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


//// our definition
#define   SENSORDATA_UWB              0
#define   SENSORDATA_DJI_ATTITUDE     1
#define   SENSORDATA_DJI_IMU          2
#define   SENSORDATA_DJI_HEIGHT       3

typedef struct{
    ros::Time   time_this;
    int         sensor_type;  // 0(uwb), 1(dji_attitude), 2(dji_imu), 3(dji_height)

    //// SENSORDATA_UWB
    int     data_uwb_id_module;
    double  data_uwb_range;
    double  data_uwb_range_err;


    //// SENSORDATA_DJI_ATTITUDE
    geometry_msgs::Quaternion data_dji_att_quaternion;


    //// SENSORDATA_DJI_IMU
    geometry_msgs::Quaternion data_dji_imu_quaternion;
    geometry_msgs::Vector3    data_dji_imu_vel_ang;
    geometry_msgs::Vector3    data_dji_imu_acc_lin;


    //// SENSORDATA_HEIGHT
    double  data_dji_height;

} MySensorData;


#endif // COMMON_HEADER_H

