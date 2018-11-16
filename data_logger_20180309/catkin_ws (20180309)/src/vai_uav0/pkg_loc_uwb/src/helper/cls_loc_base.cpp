/** @ cls_loc_base.cpp
 *  @ Feb, 2018
 *
 *  written by Jungwon Kang
 *
 */


#include "cls_loc_base.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CLS_loc_base::CLS_loc_base()
{
  //// init
  time_nsec_att_this = 0.0;
  time_nsec_att_prev = 0.0;

  time_nsec_uwb_this = 0.0;
  time_nsec_uwb_prev = 0.0;


  //// create timer
  m_timer1 = m_nh.createTimer(ros::Duration(0.1), &CLS_loc_base::callback_timer1, this);


  //// init for visualize
  m_b_visualize = true;

  if( m_b_visualize )
  {
    _init_data_for_visualize();
    m_obj_visualize.init_marker();
  }


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CLS_loc_base::~CLS_loc_base()
{

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLS_loc_base::_init_data_for_visualize()
{
  //// init data for visualize

  //// set data (user defined)
  double pos_x_station[4];
  double pos_y_station[4];
  double pos_z_station[4];
  string name_station [4];

  const int  totnum_station = 4;

  pos_x_station[0] = -3.0;    pos_y_station[0] = -3.0;    pos_z_station[0] = 0.3;
  pos_x_station[1] =  3.0;    pos_y_station[1] = -3.0;    pos_z_station[1] = 0.6;
  pos_x_station[2] = -3.0;    pos_y_station[2] =  3.0;    pos_z_station[2] = 0.9;
  pos_x_station[3] =  3.0;    pos_y_station[3] =  3.0;    pos_z_station[3] = 1.2;

  name_station[0] = "S100";
  name_station[1] = "S101";
  name_station[2] = "S102";
  name_station[3] = "S103";


  //// set
  m_obj_visualize.init_data_station(totnum_station, pos_x_station, pos_y_station, pos_z_station, name_station);


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLS_loc_base::transfer_sensor_data_to_loc_base(MySensorData data_in)
{
  ROS_INFO("CLS_loc_base::transfer_sensor_data_to_loc_base()...");

  int sensor_type = data_in.sensor_type;

  double sensor_data_quaternion[4];


  ////////////////////////////////////////////////////////////////////////////////////////
  if( sensor_type == SENSORDATA_UWB )
  {
    //// get time
    time_nsec_uwb_this = data_in.time_this.toNSec();

    //// get data
    int    id_module_this = data_in.data_uwb_id_module;
    double range_this     = data_in.data_uwb_range;
    double range_err_this = data_in.data_uwb_range_err;


    //// visualize
    if( m_b_visualize )
    {
      int idx_module;

      if( id_module_this == 100 ) { idx_module = 0; }
      if( id_module_this == 101 ) { idx_module = 1; }
      if( id_module_this == 102 ) { idx_module = 2; }
      if( id_module_this == 103 ) { idx_module = 3; }

      m_obj_visualize.set_marker_text(idx_module, range_this, range_err_this);
      m_obj_visualize.pub_marker_station();
      m_obj_visualize.pub_marker_text_on_station(idx_module);
    }


    //// print dtime
    if(1)
    {
      double dtime_nsec = time_nsec_uwb_this - time_nsec_uwb_prev;
      ROS_INFO("   dtime_nsec(uwb): %lf", dtime_nsec);
    }


    //// shift
    time_nsec_uwb_prev = time_nsec_uwb_this;
  }


  ////////////////////////////////////////////////////////////////////////////////////////
  if( sensor_type == SENSORDATA_DJI_ATTITUDE )
  {
    //// get time
    time_nsec_att_this = data_in.time_this.toNSec();

    //// get data
    geometry_msgs::Quaternion data_quaternion = data_in.data_quaternion;

      sensor_data_quaternion[0] = (double)data_quaternion.x;
      sensor_data_quaternion[1] = (double)data_quaternion.y;
      sensor_data_quaternion[2] = (double)data_quaternion.z;
      sensor_data_quaternion[3] = (double)data_quaternion.w;


    //// visualize
    if( m_b_visualize )
    {
      geometry_msgs::TransformStamped   tf_this;

        tf_this.header.frame_id         = "base";
        tf_this.child_frame_id          = "link1";
        tf_this.header.stamp            = data_in.time_this;
        tf_this.transform.translation.x = 0.0;
        tf_this.transform.translation.y = 0.0;
        tf_this.transform.translation.z = 0.0;
        tf_this.transform.rotation      = data_quaternion;

      //// broadcast
      m_br_tf_a.sendTransform(tf_this);
    }


    //// call func -> meaningless
    m_loc_core_void.run_loc(sensor_data_quaternion);


    //// print dtime
    if(1)
    {
      double dtime_nsec = time_nsec_att_this - time_nsec_att_prev;
      ROS_INFO("   dtime_nsec(att): %lf", dtime_nsec);
    }


    //// shift
    time_nsec_att_prev = time_nsec_att_this;
  }


  ////////////////////////////////////////////////////////////////////////////////////////
  if( sensor_type == SENSORDATA_DJI_IMU_ORIENTATION )
  {
    //// get time
    time_nsec_ori_this = data_in.time_this.toNSec();

    //// get data
    geometry_msgs::Quaternion data_quaternion = data_in.data_quaternion;

      sensor_data_quaternion[0] = (double)data_quaternion.x;
      sensor_data_quaternion[1] = (double)data_quaternion.y;
      sensor_data_quaternion[2] = (double)data_quaternion.z;
      sensor_data_quaternion[3] = (double)data_quaternion.w;


    //// visualize
    if( m_b_visualize )
    {
      geometry_msgs::TransformStamped   tf_this;

        tf_this.header.frame_id         = "base";
        tf_this.child_frame_id          = "link1";
        tf_this.header.stamp            = data_in.time_this;
        tf_this.transform.translation.x = 0.0;
        tf_this.transform.translation.y = 0.0;
        tf_this.transform.translation.z = 0.0;
        tf_this.transform.rotation      = data_quaternion;

      //// broadcast
      m_br_tf_b.sendTransform(tf_this);
    }


    //// call func -> meaningless
    m_loc_core_void.run_loc(sensor_data_quaternion);


    //// print dtime
    if(1)
    {
      double dtime_nsec = time_nsec_ori_this - time_nsec_ori_prev;
      ROS_INFO("   dtime_nsec(ori): %lf", dtime_nsec);
    }


    //// shift
    time_nsec_ori_prev = time_nsec_ori_this;
  }



}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLS_loc_base::callback_timer1(const ros::TimerEvent& timer_event)
{
  ROS_INFO("CLS_loc_base::callback_timer1()...");

  geometry_msgs::Quaternion data_quaternion;

    data_quaternion.x = (float)m_loc_core_void.get_pose_uav_ori_x();
    data_quaternion.y = (float)m_loc_core_void.get_pose_uav_ori_y();
    data_quaternion.z = (float)m_loc_core_void.get_pose_uav_ori_z();
    data_quaternion.w = (float)m_loc_core_void.get_pose_uav_ori_w();


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


