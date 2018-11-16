#include "cls_visualize.h"


CLS_visualize::CLS_visualize()
{
  m_pub_marker = m_nh.advertise<visualization_msgs::Marker>("visualization_marker", 100);


  m_totnum_station  = -1;

  m_shape_station_a = visualization_msgs::Marker::SPHERE;
  m_shape_station_b = visualization_msgs::Marker::CYLINDER;



}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CLS_visualize::~CLS_visualize()
{


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLS_visualize::init_marker()
{
  //// set frame_id
  string frame_id = "base";

  //// set marker for station (a) upper part
  _set_marker_station_a_upper(m_marker_station_a_upper[0], 0, frame_id, 0);
  _set_marker_station_a_upper(m_marker_station_a_upper[1], 1, frame_id, 1);
  _set_marker_station_a_upper(m_marker_station_a_upper[2], 2, frame_id, 2);
  _set_marker_station_a_upper(m_marker_station_a_upper[3], 3, frame_id, 3);

  //// set marker for station (b) lower part
  _set_marker_station_b_lower(m_marker_station_b_lower[0], 0, frame_id, 10);
  _set_marker_station_b_lower(m_marker_station_b_lower[1], 1, frame_id, 11);
  _set_marker_station_b_lower(m_marker_station_b_lower[2], 2, frame_id, 12);
  _set_marker_station_b_lower(m_marker_station_b_lower[3], 3, frame_id, 13);

  //// set marker for text on station
  _set_marker_text_on_station(m_marker_text_on_station[0], 0, frame_id, 20);
  _set_marker_text_on_station(m_marker_text_on_station[1], 1, frame_id, 21);
  _set_marker_text_on_station(m_marker_text_on_station[2], 2, frame_id, 22);
  _set_marker_text_on_station(m_marker_text_on_station[3], 3, frame_id, 23);

  //// set marker for measurement line
  _set_marker_line_measurement(m_marker_mea_line[0], frame_id, 30);
  _set_marker_line_measurement(m_marker_mea_line[1], frame_id, 31);
  _set_marker_line_measurement(m_marker_mea_line[2], frame_id, 32);
  _set_marker_line_measurement(m_marker_mea_line[3], frame_id, 33);


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLS_visualize::set_marker_text(int idx, double val_range, double val_range_err)
{
  //// update marker for text on station

  char text_on_station[100];

  snprintf(text_on_station, sizeof(text_on_station), "%.2lfm (%.2lfm)\n%s", val_range, val_range_err, m_name_station[idx].c_str());

  m_marker_text_on_station[idx].text = text_on_station;

  if( val_range > 0.0 )
  {
      m_marker_text_on_station[idx].color.r = 1.0f;
      m_marker_text_on_station[idx].color.g = 1.0f;
      m_marker_text_on_station[idx].color.b = 1.0f;
  }
  else
  {
      m_marker_text_on_station[idx].color.r = 1.0f;
      m_marker_text_on_station[idx].color.g = 0.0f;
      m_marker_text_on_station[idx].color.b = 0.0f;
   }


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLS_visualize::pub_marker_station()
{
  m_pub_marker.publish(m_marker_station_a_upper[0]);
  m_pub_marker.publish(m_marker_station_a_upper[1]);
  m_pub_marker.publish(m_marker_station_a_upper[2]);
  m_pub_marker.publish(m_marker_station_a_upper[3]);

  m_pub_marker.publish(m_marker_station_b_lower[0]);
  m_pub_marker.publish(m_marker_station_b_lower[1]);
  m_pub_marker.publish(m_marker_station_b_lower[2]);
  m_pub_marker.publish(m_marker_station_b_lower[3]);

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLS_visualize::pub_marker_text_on_station(int idx)
{
  m_pub_marker.publish(m_marker_text_on_station[idx]);

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLS_visualize::init_data_station(int Totnum, double* Pos_x, double* Pos_y, double* Pos_z, string* Name)
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// set station info
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    m_totnum_station = Totnum;


    int i;

    for(i = 0; i < Totnum; i++)
    {
        m_pos_x_station[i] = Pos_x[i];
        m_pos_y_station[i] = Pos_y[i];
        m_pos_z_station[i] = Pos_z[i];

        m_name_station [i] = Name [i];
    }
    // completed to set
    //    m_pox_X_station[]
    //    m_name_station []


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLS_visualize::_set_marker_station_a_upper(visualization_msgs::Marker &Marker, int IDX_station, string Frame_id, int Marker_id)
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// set marker for station (a) - upper part
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if( m_totnum_station < 0 )
    {
        printf("error in CLS_visualize::_set_marker_station_a_upper()...\n");
        return;
    }


    uint32_t  shape = m_shape_station_a;

    double pos_x  = m_pos_x_station[IDX_station];
    double pos_y  = m_pos_y_station[IDX_station];
    double pos_z  = m_pos_z_station[IDX_station];


    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //// set marker
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    //// set the frame ID and timestamp
    Marker.header.frame_id  = Frame_id;
    Marker.header.stamp     = ros::Time::now();

    //// set the namespace and id for this marker
    Marker.ns   = "pub_markers";
    Marker.id   = Marker_id;

    //// set the marker type
    Marker.type = shape;

    //// set the marker action
    Marker.action = visualization_msgs::Marker::ADD;

    //// set the pose of the marker
    Marker.pose.position.x = pos_x;
    Marker.pose.position.y = pos_y;
    Marker.pose.position.z = pos_z;
    Marker.pose.orientation.x = 0.0;
    Marker.pose.orientation.y = 0.0;
    Marker.pose.orientation.z = 0.0;
    Marker.pose.orientation.w = 1.0;

    //// set the scale of the marker
    Marker.scale.x = 0.2;
    Marker.scale.y = 0.2;
    Marker.scale.z = 0.2;

    //// set the color
    Marker.color.r = 0.0f;
    Marker.color.g = 1.0f;
    Marker.color.b = 0.0f;
    Marker.color.a = 1.0;


    Marker.lifetime = ros::Duration();


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLS_visualize::_set_marker_station_b_lower(visualization_msgs::Marker &Marker, int IDX_station, string Frame_id, int Marker_id)
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// set marker for station (b) - lower part
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if( m_totnum_station < 0 )
    {
        printf("error in CLS_visualize::_set_marker_station_b_lower()...\n");
        return;
    }

    uint32_t  shape = m_shape_station_b;

    double pos_x    = m_pos_x_station[IDX_station];
    double pos_y    = m_pos_y_station[IDX_station];
    double pos_z    = m_pos_z_station[IDX_station];

    double pos_z_b  = pos_z / 2.0;
    double scale_z  = pos_z;


    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //// set marker
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    //// set the frame ID and timestamp
    Marker.header.frame_id  = Frame_id;
    Marker.header.stamp     = ros::Time::now();

    //// set the namespace and id for this marker
    Marker.ns   = "pub_markers";
    Marker.id   = Marker_id;

    //// set the marker type
    Marker.type = shape;

    //// set the marker action
    Marker.action = visualization_msgs::Marker::ADD;

    //// set the pose of the marker
    Marker.pose.position.x = pos_x;
    Marker.pose.position.y = pos_y;
    Marker.pose.position.z = pos_z_b;
    Marker.pose.orientation.x = 0.0;
    Marker.pose.orientation.y = 0.0;
    Marker.pose.orientation.z = 0.0;
    Marker.pose.orientation.w = 1.0;

    //// set the scale of the marker
    Marker.scale.x = 0.05;
    Marker.scale.y = 0.05;
    Marker.scale.z = pos_z;

    //// set the color
    Marker.color.r = 1.0f;
    Marker.color.g = 0.5f;
    Marker.color.b = 0.0f;
    Marker.color.a = 1.0;


    Marker.lifetime = ros::Duration();


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLS_visualize::_set_marker_text_on_station(visualization_msgs::Marker &Marker, int IDX_station, string Frame_id, int Marker_id)
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// set marker for text on station
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    double  pos_x = m_pos_x_station[IDX_station];
    double  pos_y = m_pos_y_station[IDX_station];
    double  pos_z = m_pos_z_station[IDX_station];


    //// set the frame ID and timestamp
    Marker.header.frame_id  = Frame_id;
    Marker.header.stamp     = ros::Time::now();

    //// set the namespace and id for this marker
    Marker.ns   = "pub_markers";
    Marker.id   = Marker_id;

    //// set the marker type
    Marker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;

    //// set the marker action
    Marker.action = visualization_msgs::Marker::ADD;

    //// set the pose of the marker
    Marker.pose.position.x = pos_x;
    Marker.pose.position.y = pos_y;
    Marker.pose.position.z = pos_z + 0.4;
    Marker.pose.orientation.x = 0.0;
    Marker.pose.orientation.y = 0.0;
    Marker.pose.orientation.z = 0.0;
    Marker.pose.orientation.w = 1.0;

    //// set the scale of the marker
    //Marker.scale.x = 0.0;
    //Marker.scale.y = 0.0;
    Marker.scale.z = 0.3;

    //// set the color
    Marker.color.r = 1.0f;
    Marker.color.g = 1.0f;
    Marker.color.b = 1.0f;
    Marker.color.a = 1.0;


    Marker.lifetime = ros::Duration();


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLS_visualize::_set_marker_line_measurement(visualization_msgs::Marker &Marker, string Frame_id, int Marker_id)
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// set marker for measurement line (between station and receiver)
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //// set the frame ID and timestamp
    Marker.header.frame_id  = Frame_id;
    Marker.header.stamp     = ros::Time::now();

    //// set the namespace and id for this marker
    Marker.ns   = "pub_markers";
    Marker.id   = Marker_id;

    //// set the marker type
    Marker.type = visualization_msgs::Marker::LINE_LIST;

    //// set the marker action
    Marker.action = visualization_msgs::Marker::ADD;

    //// set the pose of the marker
    Marker.pose.orientation.x = 0.0;
    Marker.pose.orientation.y = 0.0;
    Marker.pose.orientation.z = 0.0;
    Marker.pose.orientation.w = 1.0;

    //// set the scale of the marker
    Marker.scale.x = 0.01;
    //Marker.scale.y = 1.0;
    //Marker.scale.z = 1.0;

    //// set the color
    Marker.color.r = 0.0f;
    Marker.color.g = 0.0f;
    Marker.color.b = 1.0f;
    Marker.color.a = 1.0;


    Marker.lifetime = ros::Duration();


}

