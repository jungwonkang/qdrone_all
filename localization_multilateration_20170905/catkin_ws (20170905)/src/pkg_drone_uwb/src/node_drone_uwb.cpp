#include <string>
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <visualization_msgs/Marker.h>
#include "cls_display.h"
#include "cls_timedomain.h"
#include "lib_my/LibTrilateration.h"


using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ros::init(argc, argv, "node_drone_uwb");
    ros::NodeHandle handle_node;
    tf::TransformBroadcaster broadcaster;

    ros::Rate loop_rate(10);

    DisplayCLS          obj_disp;
    TimeDomainCLS       obj_timedomain;
    CLibTrilateration   obj_trilateration;


    int i, ret;


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// init uwb receiver
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    char PORT_RECV[]   = "/dev/ttyACM0";
    ret = obj_timedomain.init(PORT_RECV);
    sleep(1);

    if( ret < 0 )
    {
        printf("main()[in node_drone_uwb.cpp]: Failed to init uwb receiver...\n");
        return -1;
    }

    printf("main()[in node_drone_uwb.cpp]: Completed to init uwb receiver...\n");



    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// user input - EDIT THIS
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    double pos_x_station[4];
    double pos_y_station[4];
    double pos_z_station[4];
    string name_station [4];


    const int  mode_run   = 1;              // 0: gathering UWB data only, 1: tri
    const bool b_save_log_as_file = true;

    const int  totnum_station = 4;

    //pos_x_station[0] = 0.0;       pos_y_station[0] = 0.0;       pos_z_station[0] = 1.041;
    //pos_x_station[1] = 6.539;     pos_y_station[1] = 0.0;       pos_z_station[1] = 1.270;
    //pos_x_station[2] = -0.029;    pos_y_station[2] = 6.558;     pos_z_station[2] = 1.546;
    //pos_x_station[3] = 6.408;     pos_y_station[3] = 6.634;     pos_z_station[3] = 1.800;

    pos_x_station[0] = 0.0;       pos_y_station[0] = 0.0;       pos_z_station[0] = 2.0;
    pos_x_station[1] = 14.889;    pos_y_station[1] = 0.0;       pos_z_station[1] = 0.3;
    pos_x_station[2] = -0.123;    pos_y_station[2] = 15.241;    pos_z_station[2] = 1.0;
    pos_x_station[3] = 14.827;    pos_y_station[3] = 15.144;    pos_z_station[3] = 1.5;


    name_station[0] = "S100";
    name_station[1] = "S101";
    name_station[2] = "S102";
    name_station[3] = "S103";


    const double thres_range_err_valid = 0.3;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// DO NOT edit
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //// set info station for display
    obj_disp.set_info_station(totnum_station, pos_x_station, pos_y_station, pos_z_station, name_station);


    //// set station pos
    double* set_pos_xyz_station = new double [totnum_station*3];

    set_pos_xyz_station[0 * 3 + 0] = pos_x_station[0];
    set_pos_xyz_station[0 * 3 + 1] = pos_y_station[0];
    set_pos_xyz_station[0 * 3 + 2] = pos_z_station[0];

    set_pos_xyz_station[1 * 3 + 0] = pos_x_station[1];
    set_pos_xyz_station[1 * 3 + 1] = pos_y_station[1];
    set_pos_xyz_station[1 * 3 + 2] = pos_z_station[1];

    set_pos_xyz_station[2 * 3 + 0] = pos_x_station[2];
    set_pos_xyz_station[2 * 3 + 1] = pos_y_station[2];
    set_pos_xyz_station[2 * 3 + 2] = pos_z_station[2];

    set_pos_xyz_station[3 * 3 + 0] = pos_x_station[3];
    set_pos_xyz_station[3 * 3 + 1] = pos_y_station[3];
    set_pos_xyz_station[3 * 3 + 2] = pos_z_station[3];
      // completed to set
      //    set_pos_xyz_station[]


    FILE* fp_log = NULL;

    if( b_save_log_as_file == true )
    {
        fp_log = fopen("/home/york1/Desktop/uwb_log/uwb_log.txt", "w");
        fprintf(fp_log, "frame(c0), b100(c1), r100(c2), rerr100(c3), b101(c4), r101(c5), rerr101(c6), b102(c7), r102(c8), rerr102(c9), b103(c10), r103(c11), rerr103(c12), pos_x_receiver(c13), pos_y_receiver(c14), pos_z_receiver(c15)\n");
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// set (common)
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string frame_id = "odom";


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// set
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ros::Publisher marker_pub = handle_node.advertise<visualization_msgs::Marker>("visualization_marker", 100);

    visualization_msgs::Marker marker_station_a_upper[4];
    visualization_msgs::Marker marker_station_b_lower[4];
    visualization_msgs::Marker marker_text_on_station[4];
    visualization_msgs::Marker marker_mea_line       [4];



    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //// set marker for station (a) upper part
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    obj_disp.set_marker_station_a_upper(marker_station_a_upper[0], 0, frame_id, 0);
    obj_disp.set_marker_station_a_upper(marker_station_a_upper[1], 1, frame_id, 1);
    obj_disp.set_marker_station_a_upper(marker_station_a_upper[2], 2, frame_id, 2);
    obj_disp.set_marker_station_a_upper(marker_station_a_upper[3], 3, frame_id, 3);


    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //// set marker for station (b) lower part
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    obj_disp.set_marker_station_b_lower(marker_station_b_lower[0], 0, frame_id, 10);
    obj_disp.set_marker_station_b_lower(marker_station_b_lower[1], 1, frame_id, 11);
    obj_disp.set_marker_station_b_lower(marker_station_b_lower[2], 2, frame_id, 12);
    obj_disp.set_marker_station_b_lower(marker_station_b_lower[3], 3, frame_id, 13);


    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //// set marker for text on station
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    obj_disp.set_marker_text_on_station(marker_text_on_station[0], 0, frame_id, 20);
    obj_disp.set_marker_text_on_station(marker_text_on_station[1], 1, frame_id, 21);
    obj_disp.set_marker_text_on_station(marker_text_on_station[2], 2, frame_id, 22);
    obj_disp.set_marker_text_on_station(marker_text_on_station[3], 3, frame_id, 23);


    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //// set marker for measurement line
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    obj_disp.set_marker_measurement_line(marker_mea_line[0], frame_id, 30);
    obj_disp.set_marker_measurement_line(marker_mea_line[1], frame_id, 31);
    obj_disp.set_marker_measurement_line(marker_mea_line[2], frame_id, 32);
    obj_disp.set_marker_measurement_line(marker_mea_line[3], frame_id, 33);


    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //// set tf
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.frame_id = frame_id;
    odom_trans.child_frame_id = "base_link";


    geometry_msgs::Point pnt_a, pnt_b;


    //// temp
    const double degree = M_PI/180;

    // robot state
    double angle=0;

    double pos_x_receiver;
    double pos_y_receiver;
    double pos_z_receiver;

    int idx_frame = 0;


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// loop
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    while (ros::ok()) 
    {
        //// init
        bool b_valid_range[4];

        b_valid_range[0] = false;
        b_valid_range[1] = false;
        b_valid_range[2] = false;
        b_valid_range[3] = false;


        ////////////////////////////////////////////////////////////////////////////////////////////////////
        //// get range (between receiver <-> station)
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        double vec_range[4];
        double vec_range_err[4];

        obj_timedomain.get_range2(100, vec_range[0], vec_range_err[0]);
        obj_timedomain.get_range2(101, vec_range[1], vec_range_err[1]);
        obj_timedomain.get_range2(102, vec_range[2], vec_range_err[2]);
        obj_timedomain.get_range2(103, vec_range[3], vec_range_err[3]);
            // completed to set
            //    vec_range[]     : invalid if -1
            //    vec_range_err[] : invalid if -1


        //// set valid bit
        if( vec_range[0] > 0.0 ) { b_valid_range[0] = true; }
        if( vec_range[1] > 0.0 ) { b_valid_range[1] = true; }
        if( vec_range[2] > 0.0 ) { b_valid_range[2] = true; }
        if( vec_range[3] > 0.0 ) { b_valid_range[3] = true; }
            // completed to set
            //    b_valid_range[]


        ////////////////////////////////////////////////////////////////////////////////////////////////////
        //// compute pos of receiver
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        double vec_w[4];
        double vec_pos_xyz_receiver[3];

        vec_pos_xyz_receiver[0] = 0.0;
        vec_pos_xyz_receiver[1] = 0.0;
        vec_pos_xyz_receiver[2] = 0.0;


        if( (b_valid_range[0] == true) && (b_valid_range[1] == true) && (b_valid_range[2] == true) && (b_valid_range[3] == true) )
        {
            if( mode_run == 1 )
            {
                //// compute weight of range
                obj_trilateration.compute_vec_w(vec_range_err, 4, thres_range_err_valid, vec_w);
                    // completed to set
                    //    vec_w[]: (1 x 4)

                //// run tri
                obj_trilateration.run_tri_recursive_np4(set_pos_xyz_station, vec_range, vec_w, totnum_station, vec_pos_xyz_receiver);
                    // completed to set
                    //    vec_pos_xyz_receiver[]: x,y,z

                if(1)
                {
                    printf("------------------------------------------------------------------------\n");
                    printf("vec_pos_xyz_receiver1 - x:[%.2lf], y:[%.2lf], z:[%.2lf]\n", vec_pos_xyz_receiver[0], vec_pos_xyz_receiver[1], vec_pos_xyz_receiver[2]);
                }
            }
        }

        pos_x_receiver = vec_pos_xyz_receiver[0];
        pos_y_receiver = vec_pos_xyz_receiver[1];
        pos_z_receiver = vec_pos_xyz_receiver[2];
        //pos_x_receiver = cos(angle)*2;
        //pos_y_receiver = sin(angle)*2;
        //pos_z_receiver = 3.0;



        ////////////////////////////////////////////////////////////////////////////////////////////////////
        //// [visualize] update marker for text on station
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        char text_on_station0[100];
        char text_on_station1[100];
        char text_on_station2[100];
        char text_on_station3[100];

        snprintf(text_on_station0, sizeof(text_on_station0), "%.2lfm (%.2lfm)\n%s", vec_range[0], vec_range_err[0], name_station[0].c_str());
        snprintf(text_on_station1, sizeof(text_on_station1), "%.2lfm (%.2lfm)\n%s", vec_range[1], vec_range_err[1], name_station[1].c_str());
        snprintf(text_on_station2, sizeof(text_on_station2), "%.2lfm (%.2lfm)\n%s", vec_range[2], vec_range_err[2], name_station[2].c_str());
        snprintf(text_on_station3, sizeof(text_on_station3), "%.2lfm (%.2lfm)\n%s", vec_range[3], vec_range_err[3], name_station[3].c_str());

        marker_text_on_station[0].text = text_on_station0;
        marker_text_on_station[1].text = text_on_station1;
        marker_text_on_station[2].text = text_on_station2;
        marker_text_on_station[3].text = text_on_station3;

        for(i = 0; i < 4; i++)
        {
            if( vec_range[i] > 0.0 )
            {
                marker_text_on_station[i].color.r = 1.0f;
                marker_text_on_station[i].color.g = 1.0f;
                marker_text_on_station[i].color.b = 1.0f;
            }
            else
            {
                marker_text_on_station[i].color.r = 1.0f;
                marker_text_on_station[i].color.g = 0.0f;
                marker_text_on_station[i].color.b = 0.0f;
             }
        }


        ////////////////////////////////////////////////////////////////////////////////////////////////////
        //// [visualize] update marker for measurement line
        ////////////////////////////////////////////////////////////////////////////////////////////////////

        //// clear
        marker_mea_line[0].points.clear();
        marker_mea_line[1].points.clear();
        marker_mea_line[2].points.clear();
        marker_mea_line[3].points.clear();


        pnt_b.x = pos_x_receiver;       pnt_b.y = pos_y_receiver;       pnt_b.z = pos_z_receiver;

        pnt_a.x = pos_x_station[0];     pnt_a.y = pos_y_station[0];     pnt_a.z = pos_z_station[0];
        marker_mea_line[0].points.push_back(pnt_a);
        marker_mea_line[0].points.push_back(pnt_b);


        pnt_a.x = pos_x_station[1];     pnt_a.y = pos_y_station[1];     pnt_a.z = pos_z_station[1];
        marker_mea_line[1].points.push_back(pnt_a);
        marker_mea_line[1].points.push_back(pnt_b);


        pnt_a.x = pos_x_station[2];     pnt_a.y = pos_y_station[2];     pnt_a.z = pos_z_station[2];
        marker_mea_line[2].points.push_back(pnt_a);
        marker_mea_line[2].points.push_back(pnt_b);


        pnt_a.x = pos_x_station[3];     pnt_a.y = pos_y_station[3];     pnt_a.z = pos_z_station[3];
        marker_mea_line[3].points.push_back(pnt_a);
        marker_mea_line[3].points.push_back(pnt_b);



        ////////////////////////////////////////////////////////////////////////////////////////////////////
        //// publish the marker
        ////////////////////////////////////////////////////////////////////////////////////////////////////        
        marker_pub.publish(marker_station_a_upper[0]);
        marker_pub.publish(marker_station_a_upper[1]);
        marker_pub.publish(marker_station_a_upper[2]);
        marker_pub.publish(marker_station_a_upper[3]);

        marker_pub.publish(marker_station_b_lower[0]);
        marker_pub.publish(marker_station_b_lower[1]);
        marker_pub.publish(marker_station_b_lower[2]);
        marker_pub.publish(marker_station_b_lower[3]);

        marker_pub.publish(marker_text_on_station[0]);
        marker_pub.publish(marker_text_on_station[1]);
        marker_pub.publish(marker_text_on_station[2]);
        marker_pub.publish(marker_text_on_station[3]);

        if( (b_valid_range[0] == true) && (mode_run == 1) ) { marker_pub.publish(marker_mea_line[0]); }
        if( (b_valid_range[1] == true) && (mode_run == 1) ) { marker_pub.publish(marker_mea_line[1]); }
        if( (b_valid_range[2] == true) && (mode_run == 1) ) { marker_pub.publish(marker_mea_line[2]); }
        if( (b_valid_range[3] == true) && (mode_run == 1) ) { marker_pub.publish(marker_mea_line[3]); }

        //while(marker_pub.getNumSubscribers() < 1)
        //{
        //    if( !ros::ok() ) { return -1; }
        //
        //    ROS_WARN_ONCE("Please create a subscriber to the marker");
        //    sleep(1);
        //}


        ////////////////////////////////////////////////////////////////////////////////////////////////////
        //// tf (for drone drawing)
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        if( (b_valid_range[0] == true) && (b_valid_range[1] == true) && (b_valid_range[2] == true) && (b_valid_range[3] == true) )
        {
            if( mode_run == 1 )
            {
                //// update tf
                odom_trans.header.stamp            = ros::Time::now();
                odom_trans.transform.translation.x = pos_x_receiver;
                odom_trans.transform.translation.y = pos_y_receiver;
                odom_trans.transform.translation.z = pos_z_receiver;
                odom_trans.transform.rotation      = tf::createQuaternionMsgFromYaw(angle+M_PI/2);


                //// send tf (for drone drawing)
                broadcaster.sendTransform(odom_trans);
            }
        }



        ////////////////////////////////////////////////////////////////////////////////////////////////////
        //// save data as file
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        if( (b_save_log_as_file == true) && (fp_log != NULL) )
        {
            // frame (c0)
            // b100(c1), r100(c2), rerr100(c3)
            // b101(c4), r101(c5), rerr101(c6)
            // b102(c7), r102(c8), rerr102(c9)
            // b103(c10), r103(c11), rerr103(c12)
            // pos_x_receiver(c13), pos_y_receiver(c14), pos_z_receiver(c15)

            fprintf(fp_log, "%d %d %lf %lf %d %lf %lf %d %lf %lf %d %lf %lf %lf %lf %lf\n",
                                                                          idx_frame,
                                                                          b_valid_range[0], vec_range[0], vec_range_err[0],
                                                                          b_valid_range[1], vec_range[1], vec_range_err[1],
                                                                          b_valid_range[2], vec_range[2], vec_range_err[2],
                                                                          b_valid_range[3], vec_range[3], vec_range_err[3],
                                                                          pos_x_receiver, pos_y_receiver, pos_z_receiver);
        }



        ////////////////////////////////////////////////////////////////////////////////////////////////////
        //// sleep
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        loop_rate.sleep();


        //// update frame
        idx_frame++;

        //// temp - create new robot state
        //angle += degree/4;
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// release
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    delete [] set_pos_xyz_station;


    //// close file
    if( fp_log != NULL ) { fclose(fp_log); }

    return 0;
}

