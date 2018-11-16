#include <string>
#include <ros/ros.h>
#include "helper/cls_timedomain.h"
#include "pkg_timedomain_uwb/msg_timedomain_uwb.h"

using namespace std;

#define MODE0_OPER_REAL      0
#define MODE1_OPER_VIRTUAL   1

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int     g_mode_operation  = MODE0_OPER_REAL;
        // 0: real, 1: virtual

char    g_port_recv[]     = "/dev/ttyACM0";

double  g_loop_rate       = 40.0;     // hz   -> effective hz = g_loop_rate / 4
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ros::init(argc, argv, "node_timedomain_uwb");
    ros::NodeHandle nh;

    TimeDomainCLS   obj_timedomain;


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// init uwb receiver
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if( g_mode_operation == MODE0_OPER_REAL )
    {
      int ret = obj_timedomain.init(g_port_recv);
      sleep(1);

      if( ret < 0 )
      {
          printf("main()[in node_drone_uwb.cpp]: Failed to init uwb receiver...\n");
          return -1;
      }

      printf("main()[in node_drone_uwb.cpp]: Completed to init uwb receiver...\n");
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// init pub
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ros::Publisher pub1 = nh.advertise<pkg_timedomain_uwb::msg_timedomain_uwb>("timedomain_uwb/range", 10);


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// loop
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int id_module_uwb = 101;    // anchor

    ros::Rate loop_rate(g_loop_rate);

    int cnt_temp = 0;

    while (ros::ok())
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        //// get range (between receiver <-> station)
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        double range = 0.0;
        double range_err = 0.0;


        //// get range & range_err
        if( g_mode_operation == MODE0_OPER_REAL )
        {
          obj_timedomain.get_range2(id_module_uwb, range, range_err);
        }
        else if( g_mode_operation == MODE1_OPER_VIRTUAL )
        {
          range     = ((double)(rand()%1000))/100.0;
          range_err = ((double)(rand()%1000))/100.0;
        }
          // completed to set
          //    range     : invalid if -1
          //    range_err : invalid if -1


        //// publish
        pkg_timedomain_uwb::msg_timedomain_uwb msg_this;

        if( range > 0.0 )
        {
          msg_this.header.stamp   = ros::Time::now();
          msg_this.id_module_uwb  = id_module_uwb;
          msg_this.range          = range;
          msg_this.range_err      = range_err;

          pub1.publish(msg_this);
        }


        ////////////////////////////////////////////////////////////////////////////////////////////////////
        //// update idx_module (anchor)
        ////////////////////////////////////////////////////////////////////////////////////////////////////        
        //if( id_module_uwb == 100 ) { id_module_uwb = 101; }
        //else if( id_module_uwb == 101 ) { id_module_uwb = 102; }
        //else if( id_module_uwb == 102 ) { id_module_uwb = 103; }
        //else if( id_module_uwb == 103 ) { id_module_uwb = 100; }

        ROS_INFO("  cnt_temp: [%d]", cnt_temp);
        cnt_temp++;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        //// sleep
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        loop_rate.sleep();
    }

    return 0;
}




