/** @ main_loc.cpp
 *  @ Feb, 2018
 *
 *  written by Jungwon Kang
 *  originated by 'demo_flight_control.cpp' provided by DJI
 *  might only work for DJI M100
 *
 *  @brief
 *  sample of getting telemetry of DJI
 *
 */


#include "helper/cls_loc_base.h"
#include "helper/cls_sensor.h"


int main(int argc, char** argv)
{
  ros::init(argc, argv, "main_loc");

  CLS_loc_base  obj_loc_base;
  CLS_sensor    obj_sensor(&obj_loc_base);

  ros::spin();

  return 0;

}

