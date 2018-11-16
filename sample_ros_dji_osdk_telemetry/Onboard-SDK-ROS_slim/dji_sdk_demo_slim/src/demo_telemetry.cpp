/** @file demo_telemetry.cpp
 *  @version 3.3
 *  @date Feb, 2018
 *
 *  written by Jungwon Kang
 *  originated by 'demo_flight_control.cpp' provided by DJI
 *  might only work for DJI M100
 *
 *  @brief
 *  demo sample of how to get telemetry
 *
 */


#include "dji_sdk_demo/demo_telemetry.h"
#include "dji_sdk/dji_sdk.h"


const float deg2rad = C_PI/180.0;
const float rad2deg = 180.0/C_PI;


// global variables for subscribed topics
uint8_t flight_status = 255;
uint8_t display_mode  = 255;
sensor_msgs::NavSatFix current_gps;
geometry_msgs::Quaternion current_atti;
geometry_msgs::Point current_local_pos;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
  ros::init(argc, argv, "demo_telemetry_node");
  ros::NodeHandle nh;

  // Subscribe to messages from dji_sdk_node
  ros::Subscriber attitudeSub     = nh.subscribe("dji_sdk/attitude",       10, &callback_attitude);
  ros::Subscriber gpsSub          = nh.subscribe("dji_sdk/gps_position",   10, &callback_gps);
  ros::Subscriber flightStatusSub = nh.subscribe("dji_sdk/flight_status",  10, &callback_flight_status);
  ros::Subscriber displayModeSub  = nh.subscribe("dji_sdk/display_mode",   10, &callback_display_mode);
  ros::Subscriber localPosition   = nh.subscribe("dji_sdk/local_position", 10, &callback_local_position);


  ros::spin();
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void callback_attitude(const geometry_msgs::QuaternionStamped::ConstPtr& msg)
{
  current_atti = msg->quaternion;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void callback_local_position(const geometry_msgs::PointStamped::ConstPtr& msg)
{
  current_local_pos = msg->point;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void callback_gps(const sensor_msgs::NavSatFix::ConstPtr& msg)
{
  static ros::Time start_time = ros::Time::now();
  ros::Duration elapsed_time = ros::Time::now() - start_time;
  current_gps = *msg;


  float altitude = current_gps.altitude;

  ROS_INFO("altitude: %f ....", altitude);


  /*
  // Down sampled to 50Hz loop
  if(elapsed_time > ros::Duration(0.02))
  {
    start_time = ros::Time::now();
    switch(square_mission.state)
    {
      case 0:
        break;

      case 1:
        if(!square_mission.finished)
        {
          square_mission.step();
        }
        else
        {
          square_mission.reset();
          square_mission.start_gps_location = current_gps;
          square_mission.start_local_position = current_local_pos;
          square_mission.setTarget(20, 0, 0, 0);
          square_mission.state = 2;
          ROS_INFO("##### Start route %d ....", square_mission.state);
        }
        break;

      case 2:
        if(!square_mission.finished)
        {
          square_mission.step();
        }
        else
        {
          square_mission.reset();
          square_mission.start_gps_location = current_gps;
          square_mission.start_local_position = current_local_pos;
          square_mission.setTarget(0, -20, 0, 0);
          square_mission.state = 3;
          ROS_INFO("##### Start route %d ....", square_mission.state);
        }
        break;
      case 3:
        if(!square_mission.finished)
        {
          square_mission.step();
        }
        else
        {
          square_mission.reset();
          square_mission.start_gps_location = current_gps;
          square_mission.start_local_position = current_local_pos;
          square_mission.setTarget(-20, 0, 0, 0);
          square_mission.state = 4;
          ROS_INFO("##### Start route %d ....", square_mission.state);
        }
        break;
      case 4:
        if(!square_mission.finished)
        {
          square_mission.step();
        }
        else
        {
          ROS_INFO("##### Mission %d Finished ....", square_mission.state);
          square_mission.state = 0;
        }
        break;
    }
  }
  */

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void callback_flight_status(const std_msgs::UInt8::ConstPtr& msg)
{
  flight_status = msg->data;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void callback_display_mode(const std_msgs::UInt8::ConstPtr& msg)
{
  display_mode = msg->data;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
