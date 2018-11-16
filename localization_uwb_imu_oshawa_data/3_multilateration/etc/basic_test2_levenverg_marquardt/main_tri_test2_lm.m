% 2018/8/25
% Jungwon Kang

clc;
clear all;
close all;


addpath('./helper');

pos_station_uwb100  = [0.0,  0.0, 0.6];
pos_station_uwb101  = [8.0,  0.0, 0.9];
pos_station_uwb102  = [0.0, 10.0, 1.2];
pos_station_uwb103  = [8.0, 10.0, 1.5];

pos_drone_GT        = [3.0, 3.0, 2.0];

range_uwb100 = norm( pos_drone_GT - pos_station_uwb100 );
range_uwb101 = norm( pos_drone_GT - pos_station_uwb101 );
range_uwb102 = norm( pos_drone_GT - pos_station_uwb102 );
range_uwb103 = norm( pos_drone_GT - pos_station_uwb103 );
    % completed to set
    %       pos_station_uwb1XX
    %       range_uwb1XX



global r100 x100 y100 z100;
global r101 x101 y101 z101;
global r102 x102 y102 z102;
global r103 x103 y103 z103;
global z_fc


r100 = range_uwb100;     x100 = pos_station_uwb100(1);       y100 = pos_station_uwb100(2);       z100 = pos_station_uwb100(3);
r101 = range_uwb101;     x101 = pos_station_uwb101(1);       y101 = pos_station_uwb101(2);       z101 = pos_station_uwb101(3);
r102 = range_uwb102;     x102 = pos_station_uwb102(1);       y102 = pos_station_uwb102(2);       z102 = pos_station_uwb102(3);
r103 = range_uwb103;     x103 = pos_station_uwb103(1);       y103 = pos_station_uwb103(2);       z103 = pos_station_uwb103(3);
z_fc = 1.5;


pos_drone_GT = [3.0, 2.0, 2.0]';

x0 = pos_drone_GT';
x  = lsqnonlin(@my_objfunc, x0);




