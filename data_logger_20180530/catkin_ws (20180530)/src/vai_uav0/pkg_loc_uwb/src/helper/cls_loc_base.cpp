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

  m_ros_time_att_this = ros::Time::now();
  m_ros_time_att_prev = ros::Time::now();

  m_ros_time_imu_this = ros::Time::now();
  m_ros_time_imu_prev = ros::Time::now();

  m_b_set_ros_time0   = false;



  //// create timer
//  m_timer1 = m_nh.createTimer(ros::Duration(0.1), &CLS_loc_base::callback_timer1, this);


  //// init for visualize
  m_b_visualize = true;

  if( m_b_visualize )
  {
    _init_data_for_visualize();
    m_obj_visualize.init_marker();
  }


  //// init for saving data as file
  m_b_save_data_in_file = true;

  m_fp1 = NULL;

  if( m_b_save_data_in_file )
  {
    //m_fp1 = fopen("/home/york1/Desktop/temp_csv/data.csv", "w");
    m_fp1 = fopen("/home/york1/Desktop/imu_calib/data.csv", "w");
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

  double sensor_data_quaternion[4];


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


    //// save in file
    if( m_b_save_data_in_file )
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



  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //// SENSORDATA_DJI_ATTITUDE
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if( sensor_type == SENSORDATA_DJI_ATTITUDE )
  {
    //// get time
    m_ros_time_att_this = data_in.time_this;


    //// get dtime
    ros::Duration dtime_att = m_ros_time_att_this - m_ros_time0;


    //// get dtime (for DJI-att data) (debugging)
    if(0)
    {
      ros::Duration dtime_debug = m_ros_time_att_this - m_ros_time_att_prev;

      double   dtime_debug_sec  = dtime_debug.toSec();
      uint64_t dtime_debug_nsec = dtime_debug.toNSec();
      printf("   att - dtime(sec): %lf, dtime(nsec): %ld\n", dtime_debug_sec, dtime_debug_nsec);
    }


    //// get data
    geometry_msgs::Quaternion data_att_quaternion = data_in.data_dji_att_quaternion;

      sensor_data_quaternion[0] = (double)data_att_quaternion.x;
      sensor_data_quaternion[1] = (double)data_att_quaternion.y;
      sensor_data_quaternion[2] = (double)data_att_quaternion.z;
      sensor_data_quaternion[3] = (double)data_att_quaternion.w;


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
        tf_this.transform.rotation      = data_att_quaternion;

      //// broadcast
      m_br_tf_a.sendTransform(tf_this);
    }


    //// call func -> meaningless
    m_loc_core_void.run_loc(sensor_data_quaternion);


    //// save in file
    if( m_b_save_data_in_file )
    {
      double dtime_att_db = (double)(dtime_att.toNSec());
      double dtime_sec    = dtime_att_db/1000000000.0;

      fprintf(m_fp1, "%d\n", SENSORDATA_DJI_ATTITUDE);
      fprintf(m_fp1, "%lf, %lf, %lf, %lf, %lf\n",
                          dtime_sec, sensor_data_quaternion[0], sensor_data_quaternion[1], sensor_data_quaternion[2], sensor_data_quaternion[3]);
    }


    //// print dtime
    if(0)
    {
      //uint64_t dtime_nsec = m_time_nsec_att_this - m_time_nsec_att_prev;
      //ROS_INFO("   dtime_nsec(att): %u", dtime_nsec);
    }


    //// shift
    m_ros_time_att_prev = m_ros_time_att_this;
  }



  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //// SENSORDATA_DJI_IMU
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if( sensor_type == SENSORDATA_DJI_IMU )
  {
    double vel_ang_imu[3];  // [0](x), [1](y), [2](z)
    double acc_lin_imu[3];  // [0](x), [1](y), [2](z)


    //// get time
    m_ros_time_imu_this = data_in.time_this;


    //// get dtime
    ros::Duration dtime_imu = m_ros_time_imu_this - m_ros_time0;


    //// get dtime (for DJI-imu data) (debugging)
    if(0)
    {
      ros::Duration dtime_debug = m_ros_time_imu_this - m_ros_time_imu_prev;

      double   dtime_debug_sec  = dtime_debug.toSec();
      uint64_t dtime_debug_nsec = dtime_debug.toNSec();
      printf("   imu - dtime(sec): %lf, dtime(nsec): %ld\n", dtime_debug_sec, dtime_debug_nsec);
    }


    //// get data
    geometry_msgs::Quaternion data_imu_quaternion = data_in.data_dji_imu_quaternion;

      sensor_data_quaternion[0] = (double)data_imu_quaternion.x;
      sensor_data_quaternion[1] = (double)data_imu_quaternion.y;
      sensor_data_quaternion[2] = (double)data_imu_quaternion.z;
      sensor_data_quaternion[3] = (double)data_imu_quaternion.w;


    geometry_msgs::Vector3    data_imu_vel_ang  = data_in.data_dji_imu_vel_ang;

      vel_ang_imu[0] = (double)data_imu_vel_ang.x;
      vel_ang_imu[1] = (double)data_imu_vel_ang.y;
      vel_ang_imu[2] = (double)data_imu_vel_ang.z;


    geometry_msgs::Vector3    data_imu_acc_lin  = data_in.data_dji_imu_acc_lin;

      acc_lin_imu[0] = (double)data_imu_acc_lin.x;
      acc_lin_imu[1] = (double)data_imu_acc_lin.y;
      acc_lin_imu[2] = (double)data_imu_acc_lin.z;


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
        tf_this.transform.rotation      = data_imu_quaternion;

      //// broadcast
      m_br_tf_b.sendTransform(tf_this);
    }


    //// call func -> meaningless
    m_loc_core_void.run_loc(sensor_data_quaternion);


    //// save in file
    if( m_b_save_data_in_file )
    {
      double dtime_imu_db = (double)(dtime_imu.toNSec());
      double dtime_sec    = dtime_imu_db/1000000000.0;

      fprintf(m_fp1, "%d\n", SENSORDATA_DJI_IMU);
      fprintf(m_fp1, "%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf\n",
                          dtime_sec, vel_ang_imu[0], vel_ang_imu[1], vel_ang_imu[2],
                                              acc_lin_imu[0], acc_lin_imu[1], acc_lin_imu[2],
                                              sensor_data_quaternion[0], sensor_data_quaternion[1], sensor_data_quaternion[2], sensor_data_quaternion[3]);
    }


    //// print dtime
    if(0)
    {
      //uint64_t dtime_nsec = m_time_nsec_imu_this - m_time_nsec_imu_prev;
      //ROS_INFO("   dtime_nsec(ori): %u", dtime_nsec);
    }


    //// shift
    m_ros_time_imu_prev = m_ros_time_imu_this;
  }


  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //// SENSORDATA_DJI_HEIGHT
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if( sensor_type == SENSORDATA_DJI_HEIGHT )
  {
    //// get time
    // Note that time is not unavailable for height.


    //// get data
    double data_dji_height = data_in.data_dji_height;


    //// save in file
    if( m_b_save_data_in_file )
    {
      fprintf(m_fp1, "%d\n", SENSORDATA_DJI_HEIGHT);
      fprintf(m_fp1, "%lf\n", data_dji_height);
    }

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


