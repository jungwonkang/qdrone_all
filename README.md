# Codes for QDrone project

This repository includes codes for the [quality-driven drone (simply QDrone) project](https://github.com/yorku-ausml/qdrone).

This is a part of our work 'Ultra-Wideband Aided UAV Positioning Using Incremental Smoothing with Ranges and Multilateration' (IROS 2020). 
However, we don't have a plan for releasing a full code, due to the company-related IP matter.

* Oshawa dataset: dataset obtained from Oshawa indoor aircargo experiment on May 30 2018
<br/>


## Samples
* [Sample ROS package for DJI OSDK-ROS telemetry](./sample_ros_dji_osdk_telemetry)

* [Sample ROS package for TimeDomain UWB P440](./sample_ros_time_domain_uwb)
  - Used for Uxbridge experiment on Oct 15 2018

* [Sample c++ code for multilateration](./sample_multilateration)
<br/>

 
## Data logger
* [ROS package for DJI M100 telemetry (such as IMU) and TimeDomain P440 UWB](./data_logger_oshawa_exp20180530)
  - Used for producing Oshawa dataset
<br/>
   
## UWB-aided localization
* [ROS package for drone localization using only multilateration](./localization_multilateration_20180905)

* [Matlab implementation for drone localization with simulated IMU & UWB data](./localization_uwb_imu_simulation)
  - Implemented for CSRS 2018
  
* [Matlab implementation for drone localization with IMU & UWB data in Oshawa dataset](./localization_uwb_imu_oshawa_exp20180530)
<br/>


