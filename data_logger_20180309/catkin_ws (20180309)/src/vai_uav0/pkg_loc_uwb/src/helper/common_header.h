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
#define   SENSORDATA_UWB                    0
#define   SENSORDATA_DJI_ATTITUDE           1
#define   SENSORDATA_DJI_IMU_ORIENTATION    2

typedef struct{
    ros::Time   time_this;
    int         sensor_type;  // 0(uwb), 1(dji, imu-orientation), 2(dji, attitude)

    //// SENSORDATA_UWB
    int     data_uwb_id_module;
    double  data_uwb_range;
    double  data_uwb_range_err;

    //// SENSORDATA_DJI_IMU_ORI / SENSORDATA_DJI_ATTITUDE
    geometry_msgs::Quaternion data_quaternion;

} MySensorData;


#endif // COMMON_HEADER_H

