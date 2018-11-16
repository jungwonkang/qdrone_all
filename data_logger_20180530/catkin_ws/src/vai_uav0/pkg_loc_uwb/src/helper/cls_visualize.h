// Jungwon Kang
// Aug 12 2017

#ifndef CLS_VISUALIZE_H
#define CLS_VISUALIZE_H

#include <string>
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

using namespace std;


class CLS_visualize
{
  public:
    CLS_visualize();
    ~CLS_visualize();

  public:
    void  init_data_station(int Totnum, double* Pos_x, double* Pos_y, double* Pos_z, string* Name);
    void  init_marker();

    void  set_marker_text(int idx, double val_range, double val_range_err);

    void  pub_marker_station();
    void  pub_marker_text_on_station(int idx);

private:
    void  _set_marker_station_a_upper (visualization_msgs::Marker &Marker, int IDX_station, string Frame_id, int Marker_id);
    void  _set_marker_station_b_lower (visualization_msgs::Marker &Marker, int IDX_station, string Frame_id, int Marker_id);
    void  _set_marker_text_on_station (visualization_msgs::Marker &Marker, int IDX_station, string Frame_id, int Marker_id);
    void  _set_marker_line_measurement(visualization_msgs::Marker &Marker, string Frame_id, int Marker_id);

  private:
    ros::NodeHandle   m_nh;
    ros::Publisher    m_pub_marker;

    visualization_msgs::Marker m_marker_station_a_upper[4];
    visualization_msgs::Marker m_marker_station_b_lower[4];
    visualization_msgs::Marker m_marker_text_on_station[4];
    visualization_msgs::Marker m_marker_mea_line       [4];


    int       m_totnum_station;

    double    m_pos_x_station[4];
    double    m_pos_y_station[4];
    double    m_pos_z_station[4];

    double    m_clr_r_station[4];   // 0.0 ~ 1.0
    double    m_clr_g_station[4];
    double    m_clr_b_station[4];

    string    m_name_station [4];

    uint32_t  m_shape_station_a;
    uint32_t  m_shape_station_b;


};

#endif // CLS_VISUALIZE_H
