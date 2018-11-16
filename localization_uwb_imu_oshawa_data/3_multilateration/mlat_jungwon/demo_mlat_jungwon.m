% 2018/8/25
% Jungwon Kang

clc;
clear all;
close all;


addpath('./helper1_alg');
addpath('./helper2_geo');


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% user setting - uwb-station position / uwb range / ground-truth drone position
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
pos_station_uwb100  = [0.0,  0.0, 0.6];
pos_station_uwb101  = [8.0,  0.0, 0.9];
pos_station_uwb102  = [0.0, 10.0, 1.2];
pos_station_uwb103  = [8.0, 10.0, 1.5];

pos_drone_GT        = [3.0, 2.0, 10.0];

range_uwb100 = norm( pos_drone_GT - pos_station_uwb100 );
range_uwb101 = norm( pos_drone_GT - pos_station_uwb101 );
range_uwb102 = norm( pos_drone_GT - pos_station_uwb102 );
range_uwb103 = norm( pos_drone_GT - pos_station_uwb103 );

set_pos_uwb   = [pos_station_uwb100; pos_station_uwb101; pos_station_uwb102; pos_station_uwb103];
set_range_uwb = [range_uwb100; range_uwb101; range_uwb102; range_uwb103];
    % completed to set
    %   set_pos_uwb   : (M x 3), M: total number of UWB stations, 3: x,y,z
    %   set_range_uwb : (M x 1)
    %   pos_drone_GT  : (1 x 3), 3: x,y,z


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% run
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
[set_xyz_stage1_out, set_xyz_stage2_out] = solve_mlat_jungwon(set_pos_uwb, set_range_uwb, true, pos_drone_GT(3));
    % completed to set
    %   set_xyz_stage1_out : (1 x 3), 3: x,y,z
    %   set_xyz_stage2_out : (1 x 3), 3: x,y,z


if 1,
    fprintf('xyz_GT:\n');           disp(pos_drone_GT)    
    fprintf('xyz_stage1_out:\n');   disp(set_xyz_stage1_out)    
    fprintf('xyz_stage2_out:\n');   disp(set_xyz_stage2_out)
end



