# ROS Package for Data Logging of DJI M100 Telemetry and TimeDomain P440 UWB

This repository includes a data logger ROS package for acquiring sensor data from a flight controller and UWB modules.
We used *N1* flight controller (in DJI M100) and Time Domain P440 UWB modules.


## Hardware & software setup

We had the following hardwares and related softwares:
  - DJI M100 (with N1 flight controller)
  - Time Domain P440 UWB modules
  - Intel NUC 7i7BNH (as a drone payload for getting the data) with 
    - Ubuntu 16.04
    - ROS-kinetic
    - [DJI OSDK 3.4](https://github.com/dji-sdk/Onboard-SDK)
    - [DJI OSDK-ROS 3.6](https://github.com/dji-sdk/Onboard-SDK-ROS) or [My variant of DJI OSDK-ROS 3.6](../sample_ros_dji_osdk_telemetry)
  - [Optional] a laptop
    - We used this for running simulation.

Basically, we followed the hardware setup described in the section '*M100 + PC/Linux machine*' of the 
[Hardware Setup Guide](https://developer.dji.com/onboard-sdk/documentation/development-workflow/hardware-setup.html).
It means that the DJI M100 and the Intel NUC are connected by a USB-TTL and a TTL-UART cable, 
and the Intel NUC and one Time Domain P440 module (Module ID:104) are connected by a USB-microUSB cable.
In addition, the DJI M100 and the laptop are connected by a USB-microUSB cable.
<br/>
<br/>


## Packages & nodes
    
### Description of individual package and node
  - Package 1: **dji_sdk**
    - This package is from [DJI OSDK-ROS 3.6](https://github.com/dji-sdk/Onboard-SDK-ROS), or [My variant of DJI OSDK-ROS 3.6](../sample_ros_dji_osdk_telemetry).
    - It acquires data from N1 flight controller in DJI M100, and publishes acquired data as the following two (topic) messages: 
        - *dji_sdk/attitude* : quaternion
        - *dji_sdk/imu* : quaternion

  - Package 2: **pkg_timedomain_uwb**
    - The node [*node_timedomain_uwb.cpp*] acquires ranging data from Time Domain UWB P440 modules, and publishes the data through the following message: 
        - *timedomain_uwb/range* : range, range error

  - Package 3: **pkg_loc_uwb**
    - The **cls_sensor** subscribes messages, which contain sensor data, from the above two nodes, and transfers the data to **cls_loc_base**.
    - The **cls_loc_base** again transfers the data **Loc_core_void** (by function call), and is doing visualization.
        - The visualization includes publishing 'visualization_msgs/Marker' for UWB, and broadcasting 'tf' for DJI drone axes.
        - [For future use] The **cls_loc_base** also has a timer call for producing output at regular time intervals. 
          Now it is just called, doing nothing. 
        - [For future use] The **Loc_core_void** is now an empty class for future use. 
          Algorithm core for localization can be implemented in this class.
    - The following figures will help you understand the overall structure:
        - [Overall structure](./doc/description1.PNG)
        - [**cls_loc_base**](./doc/description2.PNG)

### Parameters
  - *cls_sensor.cpp*: true/false for selecting messages to be subscribed
  - *node_timedomain_uwb.cpp*: operation mode (real/virtual), port (e.g. "/dev/ttyACM0"), loop rate for acquiring UWB data
  - *cls_loc_base.cpp*: loop rate for output by timer (now, not meaningful)
<br/>


## How to run

### Hardware configuration
For the data from *N1* flight controller (in DJI M100), the DJI M100 and the Intel NUC should be connected by a USB-TTL and a TTL-UART cable. 
For the data from UWB modules, the Intel NUC and one Time Domain P440 module (Module ID:104, in our case) should be connected by a USB-microUSB cable.

You might need a laptop for running simulation by the 'DJI Assistant 2'. 
In such a case, the DJI M100 and the laptop should be connected by a USB-microUSB cable.
<br/>
<br/>


### Placing & building files of this repository
Suppose that the ROS-kinetic is installed, and its workspace is **~/catkin_ws**. 
Furthermore, the DJI OSDK 3.4 is supposed be installed. 
You need to place the folder **vai_uav0** (of this repository) into the workspace, 
so that it becomes **~/catkin_ws/src/vai_uav0**.
Then, build it.
<br/>
<br/>


### Running
1. Turn on DJI M100.
    - Make sure that the LED in the DJI M100 is blinking with green color.
<br/>

2. Turn on DJI remote controller.
    - Make sure that the LED in the remote controller becomes green.
<br/>

3. [Optional] In the 'DJI Assistant 2', start simulation.
    - Instead of simulation, you can also try real operation.
<br/>

4. Run the ROS packages:

    Open three terminals.

    #### At terminal 1
    Run the publisher of data from *N1* flight controller (in DJI M100):
    ```
    $ sudo -s
    ...
    $ roslaunch dji_sdk sdk.launch
    ```

    #### At terminal 2
    Run the publisher of data from Time Domain P440 UWB modules:

    ```
    $ sudo -s
    ...
    $ roslaunch pkg_timedomain_uwb pkg_timedomain_uwb.launch
    ```

    #### At terminal 3
    Run the subscriber:
    ```
    $ sudo -s
    ...
    $ roslaunch pkg_loc_uwb pkg_loc_uwb.launch
    ```
    If it works, then 'rviz' pops up. In the 'rviz', insert the text **base** in the 'Fixed Frame' of 'Global Options' and, add TF.

    \* **Note that running at terminal 1 and terminal 2 is optional. Depending on your case, you can run only one of them.**
<br/>


5. [Optional] record as a bag file

    ```
    $ rosbag record -a
    ```
    or
    ```
    $ rosbag record SPECIFIC_TOPICS
    ```
<br/>


## Etc
- The DJI M100 and the intel NUC are connected by a USB-TTL and a TTL-UART cable. You can see current connection state using the following command: 

    <pre>
    $ dmesg | grep tty
    root@york1-desktop:~# dmesg | grep tty
    [    0.000000] console [tty0] enabled
    [    3.078189] usb 1-2: cp210x converter now attached to <b>ttyUSB0</b></pre>
<br/>


- The Time Domain UWB P440 module and the intel NUC are connected by a USB-microUSB cable. You can see current connection state using the following command: 

    <pre>
    $ dmesg | grep tty
    root@york1-desktop:~# dmesg | grep tty
    ...
    [ 3678.375082] cdc_acm 1-4:1.0: <b>ttyACM0</b>: USB ACM device</pre>
<br/>


- The DJI OSDK provides a large number of telemetry. Please go to the following links for more details:
    - http://wiki.ros.org/dji_sdk

    - http://wiki.ros.org/dji_sdk/Tutorials
