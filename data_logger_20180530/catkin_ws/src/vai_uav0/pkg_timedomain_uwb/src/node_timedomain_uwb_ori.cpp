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

double  g_loop_rate       = 10.0;     // hz
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
    ros::Rate loop_rate(g_loop_rate);

    while (ros::ok())
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        //// get range (between receiver <-> station)
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        double range[4];
        double range_err[4];


        for(int idx_module = 0; idx_module < 4; idx_module++)
        {
            //// set id_module_uwb
            int id_module_uwb;

            if( idx_module == 0 ) { id_module_uwb = 100; }
            if( idx_module == 1 ) { id_module_uwb = 101; }
            if( idx_module == 2 ) { id_module_uwb = 102; }
            if( idx_module == 3 ) { id_module_uwb = 103; }
                // completed to set
                //      id_module_uwb


            //// get range & range_err
            if( g_mode_operation == MODE0_OPER_REAL )
            {
              obj_timedomain.get_range2(id_module_uwb, range[idx_module], range_err[idx_module]);
            }
            else if( g_mode_operation == MODE1_OPER_VIRTUAL )
            {
              range[idx_module]     = ((double)(rand()%1000))/100.0;
              range_err[idx_module] = ((double)(rand()%1000))/100.0;
            }
              // completed to set
              //    range[]     : invalid if -1
              //    range_err[] : invalid if -1


            //// publish
            pkg_timedomain_uwb::msg_timedomain_uwb msg_this;

            if( range[idx_module] > 0.0 )
            {
              msg_this.header.stamp   = ros::Time::now();
              msg_this.id_module_uwb  = id_module_uwb;
              msg_this.range          = range[idx_module];
              msg_this.range_err      = range_err[idx_module];

              pub1.publish(msg_this);
            }
        }


        ////////////////////////////////////////////////////////////////////////////////////////////////////
        //// sleep
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        loop_rate.sleep();
    }

    return 0;
}


//ros::Time time_this = msg->header.stamp;


