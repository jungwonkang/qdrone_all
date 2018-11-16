% 2018/07/30
% Jungwon Kang

% For converting quaternion into the roll-pitch-yaw, we need rvc tools.
%   Peter Corke's rvc tool: http://petercorke.com/wordpress/toolboxes/robotics-toolbox


clc;
clear all;
close all;

%%%% Do not edit
DATA_UWB    = 0;
DATA_IMU    = 2;
DATA_HEIGHT = 3;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% [USER setting] exp data
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
fname_exp_csv = './csv_exp20180530_gt/2018-05-30-11-15-17_exp1_groundtruth_added.csv';
%fname_exp_csv = './csv_exp20180530_gt/2018-05-30-11-31-47_exp2_groundtruth_added.csv';
%fname_exp_csv = './csv_exp20180530_gt/2018-05-30-13-13-21_exp3_big_circle_groundtruth_added.csv';
%fname_exp_csv = './csv_exp20180530_gt/2018-05-30-13-26-45_exp4_up_down_groundtruth_added.csv';
%fname_exp_csv = './csv_exp20180530_gt/2018-05-30-13-32-30_exp5_left_right_groundtruth_added.csv';


%%%% DO NOT EDIT BELOW
raw_data_loaded = csvread(fname_exp_csv);
num_data_packet = size(raw_data_loaded, 1)/3;   % /3: one packet consists of three rows.
    % completed to set
    %       raw_data_loaded
    %       num_data_packet

data_uwb = zeros(1,4);
    % c1: time(s), c2: module id, c3: range(m), c4: range error(m)
data_imu = zeros(1,11);
    % c1: time(s)
    % c2, c3, c4: angular vel - x,y,z
    % c5, c6, c7: linear acc - x,y,z
    % c8, c9, c10, c11: ori quaternion - x,y,z,w
data_height = 0;
data_xyz_GT = zeros(1,3);
    % All the data packets(data_packet_uwb/data_packet_imu/data_packet_height) are accompanied with data_packet_xyz_GT.
   
% [one packet]
%   row1: data_type (DATA_UWB(0)/DATA_IMU(2)/DATA_HEIGHT(3))
%   row2: data_uwb / data_imu / data_height (depending on data_type)
%   row3: data_xyz_GT


    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% gathering & rearranging
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%% init
set_imu_raw     = [];
set_height_raw  = [];


%%%% loop
for idx_data_packet = 1:num_data_packet,    
    fprintf('Getting data packet [%d / %d] (perc: %f)\n', idx_data_packet, num_data_packet, (idx_data_packet/num_data_packet)*100);
    
    %%%%================================================================================================
    %%%% Read raw sensor data (Starting here)
    %%%%================================================================================================

    %%%% get row idx & row
    idx_r1 = 3*idx_data_packet - 2;
    idx_r2 = idx_r1 + 1;
    idx_r3 = idx_r1 + 2;
    
    data_r1 = raw_data_loaded(idx_r1, :);   % data_type
    data_r2 = raw_data_loaded(idx_r2, :);   % sensor data
    data_r3 = raw_data_loaded(idx_r3, :);   % xyz_GT
    
    %%%% parse
    data_type = data_r1(1);
    
    if data_type == DATA_UWB,           % DATA_UWB(0)
        data_uwb = data_r2(1:4);
    elseif data_type == DATA_IMU,       % DATA_IMU(2)
        data_imu = data_r2(1:11);
    elseif data_type == DATA_HEIGHT,    % DATA_HEIGHT(3)
        data_height = data_r2(1);
    else
        fprintf('Invalid data packet...\n');
    end
    
    data_xyz_GT = data_r3(1:3);
        % At this moment, completed to set
        %   row1: data_type (DATA_UWB(0)/DATA_IMU(2)/DATA_HEIGHT(3))
        %
        %   row2: data_uwb / data_imu / data_height (depending on data_type)
        %           data_uwb
        %               c1: time(s), c2: module id, c3: range(m), c4: range error(m)
        %           data_imu
        %               c1: time(s)
        %               c2, c3, c4: angular vel - x,y,z
        %               c5, c6, c7: linear acc - x,y,z
        %               c8, c9, c10, c11: ori quaternion - x,y,z,w
        %           data_height
        %               c1: height (Note that c1 here is not time.)
        %
        %   row3: data_xyz_GT
                    
    %%%%================================================================================================
    %%%% Read raw sensor data (Ending here)
    %%%%================================================================================================

    %%%%================================================================================================
    %%%% Rearrange data (Starting here)
    %%%%================================================================================================

    %%%% rearrage DATA_IMU
    if data_type == DATA_IMU,        
        time_this       = data_imu(1);        

        x_gt_this       = data_xyz_GT(1);
        y_gt_this       = data_xyz_GT(2);
        z_gt_this       = data_xyz_GT(3);
        
        ang_vel_x_this  = data_imu(2);
        ang_vel_y_this  = data_imu(3);
        ang_vel_z_this  = data_imu(4);
        
        acc_x_this      = data_imu(5);
        acc_y_this      = data_imu(6);
        acc_z_this      = data_imu(7);

        quart_x_this    = data_imu(8);
        quart_y_this    = data_imu(9);
        quart_z_this    = data_imu(10);
        quart_w_this    = data_imu(11);
        
        
        %%%% accumulate in set_imu_raw
        temp_row    = [time_this, ...                                                   % c1
                        x_gt_this, y_gt_this, z_gt_this, ...                            % c2, c3, c4
                        acc_x_this, acc_y_this, acc_z_this, ...                         % c5, c6, c7
                        ang_vel_x_this, ang_vel_y_this, ang_vel_z_this, ...             % c8, c9, c10
                        quart_x_this, quart_y_this, quart_z_this, quart_w_this, ...     % c11, c12, c13, c14
                        ];

        set_imu_raw = [set_imu_raw; temp_row];
    end
    
    %%%% rearrage DATA_HEIGHT
    if data_type == DATA_HEIGHT,
        % Because there is no time for the DATA_HEIGHT, we just used the nearest time from IMU time.
        x_gt_this   = data_xyz_GT(1);
        y_gt_this   = data_xyz_GT(2);
        z_gt_this   = data_xyz_GT(3);

        height_this = data_height;
        
        %%%% accumulate in set_height_raw
        temp_row    = [time_this, ...                           % c1
                        x_gt_this, y_gt_this, z_gt_this, ...    % c2, c3, c4
                        height_this, ...                        % c5
                        ];

        set_height_raw = [set_height_raw; temp_row];
    end
    
    %%%%================================================================================================
    %%%% Rearrange data (Ending here)
    %%%%================================================================================================
end
% At this time, completed to set
%   set_imu_raw 
%       time_this, ...                                                % c1
%       x_gt_this, y_gt_this, z_gt_this, ...                          % c2, c3, c4
%       acc_x_this, acc_y_this, acc_z_this, ...                       % c5, c6, c7
%       ang_vel_x_this, ang_vel_y_this, ang_vel_z_this, ...           % c8, c9, c10
%       quart_x_this, quart_y_this, quart_z_this, quart_w_this, ...   % c11, c12, c13, c14
%
%   set_height_raw
%       time_this, ...                          % c1
%       x_gt_this, y_gt_this, z_gt_this, ...    % c2, c3, c4
%       height_this, ...                        % c5


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% converting 1: quaternion -> rpy
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if true,
    set_ori_rpy = [];

    for idx_data = 1:size(set_imu_raw, 1),
        t_now = set_imu_raw(idx_data, 1);      % time
        qx    = set_imu_raw(idx_data, 11);     % quaternion - i
        qy    = set_imu_raw(idx_data, 12);     % quaternion - j
        qz    = set_imu_raw(idx_data, 13);     % quaternion - k
        qw    = set_imu_raw(idx_data, 14);     % quaternion - scalar

        quat_this = UnitQuaternion([qw qx qy qz]);
        rpy_val   = quat_this.torpy('deg');
        temp_row  = [t_now, rpy_val];
        
        set_ori_rpy = [set_ori_rpy; temp_row];
    end
    % completed to set
    %       set_ori_rpy
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% converting 2: xyz_GT -> vel(x,y,z)_GT
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
set_vel_from_gt = [];

for idx_data = 1:( size(set_imu_raw, 1) - 1),
    time0 = set_imu_raw(idx_data, 1);
    x_gt0 = set_imu_raw(idx_data, 2);
    y_gt0 = set_imu_raw(idx_data, 3);
    z_gt0 = set_imu_raw(idx_data, 4);
    
    time1 = set_imu_raw((idx_data + 1), 1);
    x_gt1 = set_imu_raw((idx_data + 1), 2);
    y_gt1 = set_imu_raw((idx_data + 1), 3);
    z_gt1 = set_imu_raw((idx_data + 1), 4);

    %%%% convert x,y to ENU
    x_gt0_enu = x_gt0;
    y_gt0_enu = y_gt0;
    
    x_gt1_enu = x_gt1;
    y_gt1_enu = y_gt1;

    %%%% compute vel
    dt    = time1 - time0;
    vel_x = (x_gt1_enu - x_gt0_enu)/dt;     % enu
    vel_y = (y_gt1_enu - y_gt0_enu)/dt;
    vel_z = (z_gt1 - z_gt0)/dt;
    
    temp_row = [(time0 + time1)/2, vel_x, vel_y, vel_z];
    set_vel_from_gt = [set_vel_from_gt; temp_row];    
end
% completed to set
%       set_vel_from_gt
    
           
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% converting 3: flight controller acc(x,y,z) -> vel(x,y,z)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
set_vel_from_acc = [];

vel_x0 = 0;
vel_y0 = 0;
vel_z0 = 0;

for idx_data = 1:( size(set_imu_raw, 1) - 1),
    time0 = set_imu_raw(idx_data, 1);
    time1 = set_imu_raw((idx_data + 1), 1);
    dt    = time1 - time0;
    
    acc_x = set_imu_raw(idx_data, 5);
    acc_y = set_imu_raw(idx_data, 6);
    acc_z = set_imu_raw(idx_data, 7);

    vel_x = vel_x0 +  0.1*acc_x*dt;
    vel_y = vel_y0 +  0.1*acc_y*dt;
    vel_z = vel_z0 + -0.1*acc_z*dt;
    
    temp_row = [time1, vel_x, vel_y, vel_z];
    set_vel_from_acc = [set_vel_from_acc; temp_row];
    
    % store for the next step
    vel_x0 = vel_x;
    vel_y0 = vel_y;
    vel_z0 = vel_z;
end
% completed to set
%       set_vel_from_acc


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% draw 1: velocity
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if false,
    figure(1),
        hold on;
        grid on;
        plot(set_vel_from_acc(:,1), set_vel_from_acc(:,2), 'b-');
        plot(set_vel_from_gt(:,1), set_vel_from_gt(:,2), 'r-');
        title('x, vel from fc-acc (blue), vel from gt (red)');

    figure(2),
        hold on;
        grid on;
        plot(set_vel_from_acc(:,1), set_vel_from_acc(:,3), 'b-');
        plot(set_vel_from_gt(:,1), set_vel_from_gt(:,3), 'r-');
        title('y, vel from fc-acc (blue), vel from gt (red)');

    figure(3),
        hold on;
        grid on;    
        plot(set_vel_from_acc(:,1), set_vel_from_acc(:,4), 'b-');
        plot(set_vel_from_gt(:,1), set_vel_from_gt(:,4), 'r-');
        title('z, vel from fc-acc (blue), vel from gt (red)');
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% draw 2: xyz_GT
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if false,    
    max_idx = 10000;
    
    figure(10),    
        plot( set_imu_raw(1:max_idx, 2), set_imu_raw(1:max_idx, 3), 'b-');
        axis equal;        
end


fprintf('Finished...\n');


%   set_imu_raw 
%       time_this, ...                                                % c1
%       x_gt_this, y_gt_this, z_gt_this, ...                          % c2, c3, c4
%       acc_x_this, acc_y_this, acc_z_this, ...                       % c5, c6, c7
%       ang_vel_x_this, ang_vel_y_this, ang_vel_z_this, ...           % c8, c9, c10
%       quart_x_this, quart_y_this, quart_z_this, quart_w_this, ...   % c11, c12, c13, c14












