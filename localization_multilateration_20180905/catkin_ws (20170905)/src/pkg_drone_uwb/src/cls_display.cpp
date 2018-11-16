#include "cls_display.h"


DisplayCLS::DisplayCLS()
{
    m_totnum_station  = -1;

    m_shape_station_a = visualization_msgs::Marker::SPHERE;
    m_shape_station_b = visualization_msgs::Marker::CYLINDER;


}

DisplayCLS::~DisplayCLS()
{


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DisplayCLS::set_info_station(int Totnum, double* Pos_x, double* Pos_y, double* Pos_z, string* Name)
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DisplayCLS::set_marker_station_a_upper(visualization_msgs::Marker &Marker, int IDX_station, string Frame_id, int Marker_id)
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// set marker for station (a) - upper part
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if( m_totnum_station < 0 )
    {
        printf("error in DisplayCLS::set_marker_station_a_upper()...\n");
        return;
    }


    uint32_t  shape = m_shape_station_a;

    double    pos_x = m_pos_x_station[IDX_station];
    double    pos_y = m_pos_y_station[IDX_station];
    double    pos_z = m_pos_z_station[IDX_station];


    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //// set marker
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    //// set the frame ID and timestamp
    //Marker.header.frame_id  = "odom";
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DisplayCLS::set_marker_station_b_lower(visualization_msgs::Marker &Marker, int IDX_station, string Frame_id, int Marker_id)
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// set marker for station (b) - lower part
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if( m_totnum_station < 0 )
    {
        printf("error in DisplayCLS::set_marker_station_b_lower()...\n");
        return;
    }

    uint32_t  shape = m_shape_station_b;

    double    pos_x = m_pos_x_station[IDX_station];
    double    pos_y = m_pos_y_station[IDX_station];
    double    pos_z = m_pos_z_station[IDX_station];

    double pos_z_b  = pos_z / 2.0;
    double scale_z  = pos_z;


    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //// set marker
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    //// set the frame ID and timestamp
    //Marker.header.frame_id  = "odom";
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DisplayCLS::set_marker_text_on_station(visualization_msgs::Marker &Marker, int IDX_station, string Frame_id, int Marker_id)
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DisplayCLS::set_marker_measurement_line(visualization_msgs::Marker &Marker, string Frame_id, int Marker_id)
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

