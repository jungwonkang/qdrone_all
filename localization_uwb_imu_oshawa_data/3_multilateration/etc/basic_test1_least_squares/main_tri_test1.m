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


%%%% i = 101
r_101_100_2 = ( pos_station_uwb101(1)^2 - pos_station_uwb100(1)^2 ) + ( pos_station_uwb101(2)^2 - pos_station_uwb100(2)^2 ) + ( pos_station_uwb101(3)^2 - pos_station_uwb100(3)^2 );
r_term101 = (range_uwb101^2) - (range_uwb100^2) - r_101_100_2;
a101 = -2*( pos_station_uwb101(1) - pos_station_uwb100(1) );
b101 = -2*( pos_station_uwb101(2) - pos_station_uwb100(2) );
c101 = -2*( pos_station_uwb101(3) - pos_station_uwb100(3) );


%%%% i = 102
r_102_100_2 = ( pos_station_uwb102(1)^2 - pos_station_uwb100(1)^2 ) + ( pos_station_uwb102(2)^2 - pos_station_uwb100(2)^2 ) + ( pos_station_uwb102(3)^2 - pos_station_uwb100(3)^2 );
r_term102 = (range_uwb102^2) - (range_uwb100^2) - r_102_100_2;
a102 = -2*( pos_station_uwb102(1) - pos_station_uwb100(1) );
b102 = -2*( pos_station_uwb102(2) - pos_station_uwb100(2) );
c102 = -2*( pos_station_uwb102(3) - pos_station_uwb100(3) );


%%%% i = 103
r_103_100_2 = ( pos_station_uwb103(1)^2 - pos_station_uwb100(1)^2 ) + ( pos_station_uwb103(2)^2 - pos_station_uwb100(2)^2 ) + ( pos_station_uwb103(3)^2 - pos_station_uwb100(3)^2 );
r_term103 = (range_uwb103^2) - (range_uwb100^2) - r_103_100_2;
a103 = -2*( pos_station_uwb103(1) - pos_station_uwb100(1) );
b103 = -2*( pos_station_uwb103(2) - pos_station_uwb100(2) );
c103 = -2*( pos_station_uwb103(3) - pos_station_uwb100(3) );


mat_a = [a101, b101, c101;
         a102, b102, c102;
         a103, b103, c103;];

mat_b = [r_term101;
         r_term102;
         r_term103;];
     
x = pinv(mat_a)*mat_b;




