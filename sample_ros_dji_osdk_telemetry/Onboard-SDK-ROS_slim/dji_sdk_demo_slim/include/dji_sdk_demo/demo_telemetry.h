/** @file demo_telemetry.h
 *  @date Feb, 2018
 *
 *  written by Jungwon Kang
 *  originated by 'demo_flight_control.h' provided by DJI
 *  might only work for DJI M100
 *
 *  @brief
 *  demo sample of how to get telemetry
 *
 */

#ifndef DEMO_TELEMETRY_H
#define DEMO_TELEMETRY_H

// ROS includes
#include <ros/ros.h>
#include <geometry_msgs/QuaternionStamped.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <sensor_msgs/NavSatFix.h>
#include <std_msgs/UInt8.h>

#include <tf/tf.h>
#include <sensor_msgs/Joy.h>

#define C_EARTH (double)6378137.0
#define C_PI (double)3.141592653589793
#define DEG2RAD(DEG) ((DEG) * ((C_PI) / (180.0)))

void callback_attitude(const geometry_msgs::QuaternionStamped::ConstPtr& msg);
void callback_gps(const sensor_msgs::NavSatFix::ConstPtr& msg);
void callback_flight_status(const std_msgs::UInt8::ConstPtr& msg);
void callback_display_mode(const std_msgs::UInt8::ConstPtr& msg);
void callback_local_position(const geometry_msgs::PointStamped::ConstPtr& msg);


#endif // DEMO_TELEMETRY_H
