# Sample Code for DJI OSDK-ROS Telemetry

This repository contains a sample code for *DJI OSDK(Onboard SDK)-ROS* telemetry.
The sample was tested on *Ubuntu 16.04 / ROS-kinetic / DJI OSDK 3.4 / DJI OSDK-ROS 3.6* with *DJI M100* and *Intel NUC 7i7BNH* (as a drone payload).
<br/>
<br/>


## Hardware setup
We followed the hardware setup described in the section '*M100 + PC/Linux machine*' of the 
[Hardware Setup Guide](https://developer.dji.com/onboard-sdk/documentation/development-workflow/hardware-setup.html).

We had DJI M100, Intel NUC (as a drone payload for getting telemetry), 
and a laptop (for setting drone related options and running simulation). 

Then, the DJI M100 and the Intel NUC are connected by a USB-TTL cable, and the DJI M100 and the laptop are connected by a USB-microUSB cable.

In the laptop, we installed the 'DJI Assistant 2' for setting drone related options and running simulation.

In the 'DJI Assistant 2', enable 'OSDK API' by checking a 'Enable API Control' in the 'SDK' menu.
<br/>
<br/>


## Software setup
We followed the procedures in the section '*ROS Onboard Computer*' of the 
[Setting up Samples](https://developer.dji.com/onboard-sdk/documentation/sample-doc/sample-setup.html#ros-oes).

Note that we used '*DJI OSDK 3.4*' and '*DJI OSDK-ROS 3.6*'.
In addition, the flight controller version was 3.1.10.0.
<br/>
<br/>


### Installing [DJI OSDK](https://github.com/dji-sdk/Onboard-SDK) 

We followed the procedure in the section '*Installing the OSDK*' of '*ROS Onboard Computer*' of the 
[Setting up Samples](https://developer.dji.com/onboard-sdk/documentation/sample-doc/sample-setup.html#ros-oes).


The newest DJI OSDK is version 3.6. However, the DJI M100 is only supported by DJI OSDK 3.4. 
So, we got the DJI OSDK 3.4:
```
$ git clone -b 3.4 https://github.com/dji-sdk/Onboard-SDK.git
```

Then, we went throught the following procedure:
```
$ sudo -s
...
$ cd build
$ cmake ..
$ make djiosdk-core
$ sudo make install djiosdk-core
```
<br/>


### Installing files in this repository

You may create a catkin workspace, unless you don't have it:
```
$ mkdir catkin_ws
$ cd catkin_ws
$ mkdir src
$ cd src
$ catkin_init_workspace
```

Then, download files in this repository, and place the files so that it becomes:

- ~/catkin_ws/src/Onboard-SDK-ROS_slim/dji_sdk

- ~/catkin_ws/src/Onboard-SDK-ROS_slim/dji_sdk_demo_slim


Actually, the above file placing corresponds to the step of cloning the [DJI OSDK-ROS](https://github.com/dji-sdk/Onboard-SDK-ROS) 
using the command ```$ git clone https://github.com/dji-sdk/Onboard-SDK-ROS.git```, 
described the section '*Building the ROS Nodes*' of '*ROS Onboard Computer*' of the 
[Setting up Samples](https://developer.dji.com/onboard-sdk/documentation/sample-doc/sample-setup.html#ros-oes).
<br/>
<br/>


### Building DJI OSDK-ROS

Build it:
```
$ cd ..
$ catkin_make
```
<br/>


### Configuration
Edit the launch file for entering your App ID, Key, Baudrate and Port name:
```
$ sudo -s 
$ source devel/setup.bash
$ rosed dji_sdk sdk.launch
```
<br/>


### Running (1/2): *dji_sdk*, a node for starting
Run:

```
$ roslaunch dji_sdk sdk.launch
```
Then, you would get the following message:

```
... logging to /home/oooo/.ros/log/af09ec36-10f2-11e8-b3fc-f8633f3b1474/roslaunch-oooo-desktop-7385.log
Checking log directory for disk usage. This may take awhile.
Press Ctrl-C to interrupt
Done checking log file disk usage. Usage is <1GB.

started roslaunch server http://localhost:34561/

SUMMARY
========

PARAMETERS
 * /dji_sdk/align_time: False
 * /dji_sdk/app_id: oooo
 * /dji_sdk/app_version: 1
 * /dji_sdk/baud_rate: 230400
 * /dji_sdk/enc_key: oooo...
 * /dji_sdk/serial_name: /dev/ttyUSB0
 * /dji_sdk/use_broadcast: False
 * /rosdistro: kinetic
 * /rosversion: 1.12.7

NODES
  /
    dji_sdk (dji_sdk/dji_sdk_node)

auto-starting new master
process[master]: started with pid [7397]
ROS_MASTER_URI=http://localhost:11311

setting /run_id to oooo
process[rosout-1]: started with pid [7410]
started core service [/rosout]
process[dji_sdk-2]: started with pid [7413]

STATUS/1 @ init, L55: Attempting to open device /dev/ttyUSB0 with baudrate 230400...

STATUS/1 @ init, L65: ...Serial started successfully.
[ INFO] [1518549514.515978557]: Succeeded to read from serial device

STATUS/1 @ init, L55: Attempting to open device /dev/ttyUSB0 with baudrate 230400...

STATUS/1 @ init, L65: ...Serial started successfully.

STATUS/1 @ parseDroneVersionInfo, L630: Device Serial No. = 041DE21071

STATUS/1 @ parseDroneVersionInfo, L632: Hardware = M100

STATUS/1 @ parseDroneVersionInfo, L633: Firmware = 3.1.10.0

STATUS/1 @ parseDroneVersionInfo, L636: Version CRC = 0xA6453AAC

ERROR/1 @ functionalSetUp, L154: Subscriber not supported!

STATUS/1 @ functionalSetUp, L188: MFIO not supported!

ERROR/1 @ functionalSetUp, L206: Hardware Sync not supported!

STATUS/1 @ activate, L1083: version 0x3010A00

STATUS/1 @ activate, L1096: Activation successful
[ INFO] [1518549517.559675745]: drone activated
[ INFO] [1518549517.630634153]: Use legacy data broadcast to get telemetry data!
```
<br/>


### Running (2/2): *demo_telemetry*, a node for getting telemetry

Open up a new terminal and 'cd' to your catkin_ws, and run *demo_telemetry*

```
$ sudo -s
$ source devel/setup.bash
$ rosrun dji_sdk_demo_slim demo_telemetry
```
<br/>


## Etc
- The DJI M100 and the intel NUC are connected by a USB-TTL cable. You can see current connection state using the following command: 

    ```
    $ dmesg | grep tty
    root@york1-desktop:~# dmesg | grep tty
    [    0.000000] console [tty0] enabled
    [    3.078189] usb 1-2: cp210x converter now attached to ttyUSB0
    ```
<br/>

- The DJI OSDK provides a large number of telemetry. Please go to the following links for more details:
    - http://wiki.ros.org/dji_sdk

    - http://wiki.ros.org/dji_sdk/Tutorials


