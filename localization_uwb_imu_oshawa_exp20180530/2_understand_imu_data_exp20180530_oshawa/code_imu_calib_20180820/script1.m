% 2018/08/20
% Jungwon Kang

% For converting quaternion into the roll-pitch-yaw, we need rvc tools.
%   Peter Corke's rvc tool: http://petercorke.com/wordpress/toolboxes/robotics-toolbox


clc;
clear all;
close all;

%%%% Do not edit
DATA_IMU    = 2;
DATA_HEIGHT = 3;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% [USER setting] exp data
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%fname_exp_csv = './csv/2018-08-20-15-59-41_abs_rot0_exp1.csv';          % roll,  x, counter-clockwise
%fname_exp_csv = './csv/2018-08-20-16-00-37_abs_rot0_exp2.csv';        % roll,  x, clockwise
%fname_exp_csv = './csv/2018-08-20-16-01-10_abs_rot0_exp3.csv';        % pitch, y, counter-clockwise
%fname_exp_csv = './csv/2018-08-20-16-01-39_abs_rot0_exp4.csv';        % pitch, y, clockwise
%fname_exp_csv = './csv/2018-08-20-16-02-18_abs_rot0_exp5.csv';        % yaw,   z, counter-clockwise
%fname_exp_csv = './csv/2018-08-20-16-02-47_abs_rot0_exp6.csv';        % yaw,   z, clockwise
% 
%fname_exp_csv = './csv/2018-08-20-16-04-22_abs_rot135_exp1.csv';      % roll,  x, counter-clockwise
%fname_exp_csv = './csv/2018-08-20-16-04-22_abs_rot135_exp2.csv';      % roll,  x, clockwise
%fname_exp_csv = './csv/2018-08-20-16-04-22_abs_rot135_exp3.csv';      % pitch, y, counter-clockwise
%fname_exp_csv = './csv/2018-08-20-16-06-08_abs_rot135_exp4.csv';      % pitch, y, clockwise
%fname_exp_csv = './csv/2018-08-20-16-06-41_abs_rot135_exp5.csv';      % yaw,   z, counter-clockwise
fname_exp_csv = './csv/2018-08-20-16-07-10_abs_rot135_exp6.csv';      % yaw,   z, clockwise


%%%% DO NOT EDIT BELOW
raw_data_loaded = csvread(fname_exp_csv);
num_data_packet = size(raw_data_loaded, 1)/2;   % /2: one packet consists of three rows.
    % completed to set
    %       raw_data_loaded
    %       num_data_packet

data_imu = zeros(1,11);
    % c1: time(s)
    % c2, c3, c4: angular vel - x,y,z
    % c5, c6, c7: linear acc - x,y,z
    % c8, c9, c10, c11: ori quaternion - x,y,z,w
data_height = 0;
   
% [one packet]
%   row1: data_type (DATA_IMU(2)/DATA_HEIGHT(3))
%   row2: data_imu / data_height (depending on data_type)


    
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
    idx_r1 = 2*idx_data_packet - 1;
    idx_r2 = idx_r1 + 1;
    
    data_r1 = raw_data_loaded(idx_r1, :);   % data_type
    data_r2 = raw_data_loaded(idx_r2, :);   % sensor data
    
    %%%% parse
    data_type = data_r1(1);
    
    if data_type == DATA_IMU,       % DATA_IMU(2)
        data_imu = data_r2(1:11);
    elseif data_type == DATA_HEIGHT,    % DATA_HEIGHT(3)
        data_height = data_r2(1);
    else
        fprintf('Invalid data packet...\n');
    end
        % At this moment, completed to set
        %   row1: data_type (DATA_IMU(2)/DATA_HEIGHT(3))
        %
        %   row2: data_imu / data_height (depending on data_type)
        %           data_imu
        %               c1: time(s)
        %               c2, c3, c4: angular vel - x,y,z
        %               c5, c6, c7: linear acc - x,y,z
        %               c8, c9, c10, c11: ori quaternion - x,y,z,w
        %           data_height
        %               c1: height (Note that c1 here is not time.)
                    
    %%%%================================================================================================
    %%%% Read raw sensor data (Ending here)
    %%%%================================================================================================

    %%%%================================================================================================
    %%%% Rearrange data (Starting here)
    %%%%================================================================================================

    %%%% rearrage DATA_IMU
    if data_type == DATA_IMU,        
        time_this       = data_imu(1);        
        
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
                        acc_x_this, acc_y_this, acc_z_this, ...                         % c2, c3, c4
                        ang_vel_x_this, ang_vel_y_this, ang_vel_z_this, ...             % c5, c6, c7
                        quart_x_this, quart_y_this, quart_z_this, quart_w_this, ...     % c8, c9, c10, c11
                        ];

        set_imu_raw = [set_imu_raw; temp_row];
    end
    
    %%%% rearrage DATA_HEIGHT
    if data_type == DATA_HEIGHT,
        % Because there is no time for the DATA_HEIGHT, we just used the nearest time from IMU time.
        height_this = data_height;
        
        %%%% accumulate in set_height_raw
        temp_row    = height_this;                      % c1

        set_height_raw = [set_height_raw; temp_row];
    end
    
    %%%%================================================================================================
    %%%% Rearrange data (Ending here)
    %%%%================================================================================================
end
% At this time, completed to set
%   set_imu_raw 
%       time_this, ...                                                  % c1
%       acc_x_this, acc_y_this, acc_z_this, ...                         % c2, c3, c4
%       ang_vel_x_this, ang_vel_y_this, ang_vel_z_this, ...             % c5, c6, c7
%       quart_x_this, quart_y_this, quart_z_this, quart_w_this          % c8, c9, c10, c11
%
%   set_height_raw
%       height_this                 % c1


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% converting 1: quaternion -> rpy
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
set_ori_rpy = [];

for idx_data = 1:size(set_imu_raw, 1),
    t_now = set_imu_raw(idx_data, 1);       % time
    qx    = set_imu_raw(idx_data, 8);       % quaternion - i
    qy    = set_imu_raw(idx_data, 9);       % quaternion - j
    qz    = set_imu_raw(idx_data, 10);      % quaternion - k
    qw    = set_imu_raw(idx_data, 11);      % quaternion - scalar
    
    quat_this = UnitQuaternion([qw qx qy qz]);
    rpy_val   = quat_this.torpy('deg');
    temp_row  = [t_now, rpy_val];

    set_ori_rpy = [set_ori_rpy; temp_row];
end
% completed to set
%       set_ori_rpy
%           t_now, ...              % c1
%           roll, pitch, yaw        % c2, c3, c4


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% In conclusion, here we have
%   set_imu_raw 
%       time_this, ...                                                  % c1
%       acc_x_this, acc_y_this, acc_z_this, ...                         % c2, c3, c4
%       ang_vel_x_this, ang_vel_y_this, ang_vel_z_this, ...             % c5, c6, c7
%       quart_x_this, quart_y_this, quart_z_this, quart_w_this          % c8, c9, c10, c11
%
%   set_height_raw
%       height_this                 % c1
%
%       set_ori_rpy
%           t_now, ...              % c1
%           roll, pitch, yaw        % c2, c3, c4
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% setting
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%% pos of fig
pos_fig_left    = 10;
pos_fig_bottom  = 100;
pos_fig_width   = 1700;
pos_fig_height  = 300;

%%%% fname for showing
b_show_linear_acc   = true;
b_show_ang_vel      = true;
b_show_ori_rpy      = true;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% draw linear acc
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%
if b_show_linear_acc,
    h1 = figure(1);
    set(h1, 'Position', [pos_fig_left, pos_fig_bottom, pos_fig_width, pos_fig_height]);
    hold on;
    grid on;
    plot(set_imu_raw(:,1), set_imu_raw(:,2), 'b-');
    title('linear acc (x)');
    
    x_min = min( set_imu_raw(:,1) );
    x_max = max( set_imu_raw(:,1) );
    xlim([x_min, x_max])
end


%%%%
if b_show_linear_acc,
    h2 = figure(2);
    set(h2, 'Position', [pos_fig_left, pos_fig_bottom, pos_fig_width, pos_fig_height]);
    hold on;
    grid on;
    plot(set_imu_raw(:,1), set_imu_raw(:,3), 'b-');
    title('linear acc (y)');

    x_min = min( set_imu_raw(:,1) );
    x_max = max( set_imu_raw(:,1) );
    xlim([x_min, x_max])
end


%%%%
if b_show_linear_acc,
    h3 = figure(3);
    set(h3, 'Position', [pos_fig_left, pos_fig_bottom, pos_fig_width, pos_fig_height]);
    hold on;
    grid on;    
    plot(set_imu_raw(:,1), set_imu_raw(:,4), 'b-');
    title('linear acc (z)');

    x_min = min( set_imu_raw(:,1) );
    x_max = max( set_imu_raw(:,1) );
    xlim([x_min, x_max])
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% draw angular velocity
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%
if b_show_ang_vel,
    h1 = figure(10);
    set(h1, 'Position', [pos_fig_left, pos_fig_bottom, pos_fig_width, pos_fig_height]);
    hold on;
    grid on;
    plot(set_imu_raw(:,1), set_imu_raw(:,5), 'b-');
    title('angular vel (x)');
    
    x_min = min( set_imu_raw(:,1) );
    x_max = max( set_imu_raw(:,1) );
    xlim([x_min, x_max])
end


%%%%
if b_show_ang_vel,
    h2 = figure(11);
    set(h2, 'Position', [pos_fig_left, pos_fig_bottom, pos_fig_width, pos_fig_height]);
    hold on;
    grid on;
    plot(set_imu_raw(:,1), set_imu_raw(:,6), 'b-');
    title('angular vel (y)');

    x_min = min( set_imu_raw(:,1) );
    x_max = max( set_imu_raw(:,1) );
    xlim([x_min, x_max])
end


%%%%
if b_show_ang_vel,
    h3 = figure(12);
    set(h3, 'Position', [pos_fig_left, pos_fig_bottom, pos_fig_width, pos_fig_height]);
    hold on;
    grid on;    
    plot(set_imu_raw(:,1), set_imu_raw(:,7), 'b-');
    title('angular vel (z)');

    x_min = min( set_imu_raw(:,1) );
    x_max = max( set_imu_raw(:,1) );
    xlim([x_min, x_max])
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% draw orientation rpy
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%
if b_show_ori_rpy,
    h1 = figure(20);
    set(h1, 'Position', [pos_fig_left, pos_fig_bottom, pos_fig_width, pos_fig_height]);
    hold on;
    grid on;
    plot(set_ori_rpy(:,1), set_ori_rpy(:,2), 'r-', 'LineWidth', 2);
    title('ori roll (x)');
    
    x_min = min( set_ori_rpy(:,1) );
    x_max = max( set_ori_rpy(:,1) ); 
    xlim([x_min, x_max])
end


%%%%
if b_show_ori_rpy,
    h2 = figure(21);
    set(h2, 'Position', [pos_fig_left, pos_fig_bottom, pos_fig_width, pos_fig_height]);
    hold on;
    grid on;
    plot(set_ori_rpy(:,1), set_ori_rpy(:,3), 'r-', 'LineWidth', 2);
    title('ori pitch (y)');

    x_min = min( set_ori_rpy(:,1) );
    x_max = max( set_ori_rpy(:,1) );
    xlim([x_min, x_max])
end


%%%%
if b_show_ori_rpy,
    h3 = figure(22);
    set(h3, 'Position', [pos_fig_left, pos_fig_bottom, pos_fig_width, pos_fig_height]);
    hold on;
    grid on;
    plot(set_ori_rpy(:,1), set_ori_rpy(:,4), 'r-', 'LineWidth', 2);
    title('ori yaw (z)');

    x_min = min( set_ori_rpy(:,1) );
    x_max = max( set_ori_rpy(:,1) );
    xlim([x_min, x_max])
end


