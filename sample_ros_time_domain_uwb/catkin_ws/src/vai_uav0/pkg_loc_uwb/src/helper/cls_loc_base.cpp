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
  m_ros_time_uwb_this = ros::Time::now();
  m_ros_time_uwb_prev = ros::Time::now();

  m_b_set_ros_time0   = false;


  //// init for visualize
  m_b_visualize = false;

  if( m_b_visualize )
  {
    sleep(1);
    _init_data_for_visualize();
    m_obj_visualize.init_marker();
    m_obj_visualize.pub_marker_station();
  }


  //// init for saving data as file
  m_fp1 = NULL;

  if(1)
  {
    m_fp1 = fopen("/home/york2/data.csv", "w");
  }


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CLS_loc_base::~CLS_loc_base()
{

  //// close fp
  if( m_fp1 != NULL ) { fclose(m_fp1); }


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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLS_loc_base::transfer_sensor_data_to_loc_base(MySensorData data_in)
{
  ROS_INFO("CLS_loc_base::transfer_sensor_data_to_loc_base()...");

  int sensor_type = data_in.sensor_type;


  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //// set time0
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if( (sensor_type == SENSORDATA_UWB) || (sensor_type == SENSORDATA_DJI_ATTITUDE) || ( sensor_type == SENSORDATA_DJI_IMU ) )
  {
    if( m_b_set_ros_time0 == false )
    {
      m_ros_time0       = data_in.time_this;
      m_b_set_ros_time0 = true;
    }
  }


  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //// SENSORDATA_UWB
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if( sensor_type == SENSORDATA_UWB )
  {
    //// get time
    m_ros_time_uwb_this = data_in.time_this;


    //// get dtime
    ros::Duration dtime_uwb = m_ros_time_uwb_this - m_ros_time0;


    //// get dtime (for UWB data) (debugging)
    if(0)
    {
      ros::Duration dtime_debug = m_ros_time_uwb_this - m_ros_time_uwb_prev;

      double   dtime_debug_sec  = dtime_debug.toSec();
      uint64_t dtime_debug_nsec = dtime_debug.toNSec();
      printf("   uwb - dtime(sec): %lf, dtime(nsec): %ld\n", dtime_debug_sec, dtime_debug_nsec);
    }


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


    //// save in file (v2)
    if(1)
    {
      double time_uwb_now_db  = m_ros_time_uwb_this.toSec();
      fprintf(m_fp1, "%lf, %d, %lf, %lf\n", time_uwb_now_db, id_module_this, range_this, range_err_this);
    }


    //// save in file (v1)
    if(0)
    {
      double dtime_uwb_db = (double)(dtime_uwb.toNSec());
      double dtime_sec    = dtime_uwb_db/1000000000.0;

      fprintf(m_fp1, "%lf, %d, %lf, %lf\n", dtime_sec, id_module_this, range_this, range_err_this);
    }


    //// save in file (v0)
    if(0)
    {
      double dtime_uwb_db = (double)(dtime_uwb.toNSec());
      double dtime_sec    = dtime_uwb_db/1000000000.0;

      fprintf(m_fp1, "%d\n", SENSORDATA_UWB);
      fprintf(m_fp1, "%lf, %d, %lf, %lf\n", dtime_sec, id_module_this, range_this, range_err_this);
    }


    //// print dtime
    if(0)
    {
      //uint64_t dtime_nsec = m_time_nsec_uwb_this - m_time_nsec_uwb_prev;
      //ROS_INFO("   dtime_nsec(uwb): %u", dtime_nsec);
    }


    //// shift
    m_ros_time_uwb_prev = m_ros_time_uwb_this;
  }



}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


