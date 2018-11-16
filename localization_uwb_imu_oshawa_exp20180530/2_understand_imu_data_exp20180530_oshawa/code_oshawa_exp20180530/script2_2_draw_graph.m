% 2018/08/02
% Jungwon Kang

% draw graphs from output of [script2_analysis.m]

% You MUST first run 'script2_1_analysis.m'.


close all;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% setting
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%% pos of fig
pos_fig_left    = 10;
pos_fig_bottom  = 100;
pos_fig_width   = 1700;
pos_fig_height  = 300;

%%%% fname for showing
b_show_linear_acc   = false;
b_show_ang_vel      = false;
b_show_ori_rpy      = true;

b_show_height       = true;


b_save = false;
idx_dataset = 1;



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% draw two velocity comparison
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%
if b_show_linear_acc,
    h1 = figure(1);
    set(h1, 'Position', [pos_fig_left, pos_fig_bottom, pos_fig_width, pos_fig_height]);
    hold on;
    grid on;
    plot(set_vel_from_acc(:,1), set_vel_from_acc(:,2), 'b-');
    plot(set_vel_from_gt(:,1), set_vel_from_gt(:,2), 'r-');
    %title('x-vel from fc-acc (blue), x-vel from gt (red)');
    
    x_min = min([set_vel_from_acc(:,1)' set_vel_from_gt(:,1)']);
    x_max = max([set_vel_from_acc(:,1)' set_vel_from_gt(:,1)']);    
    xlim([x_min, x_max])
    
    if false,
        legend('Velocity from linear acc', 'Velocity from ground-truth position');
    end
    
    if b_save,
        fname_screenshot = sprintf('./screenshot/graph_vel_x_dataset_%d.png', idx_dataset);
        saveas(h1, fname_screenshot);
    end
end


%%%%
if b_show_linear_acc,
    h2 = figure(2);
    set(h2, 'Position', [pos_fig_left, pos_fig_bottom, pos_fig_width, pos_fig_height]);
    hold on;
    grid on;
    plot(set_vel_from_acc(:,1), set_vel_from_acc(:,3), 'b-');
    plot(set_vel_from_gt(:,1), set_vel_from_gt(:,3), 'r-');
    %title('y, vel from fc-acc (blue), vel from gt (red)');

    x_min = min([set_vel_from_acc(:,1)' set_vel_from_gt(:,1)']);
    x_max = max([set_vel_from_acc(:,1)' set_vel_from_gt(:,1)']);    
    xlim([x_min, x_max])
    
    if b_save,
        fname_screenshot = sprintf('./screenshot/graph_vel_y_dataset_%d.png', idx_dataset);
        saveas(gcf, fname_screenshot);
    end
end


%%%%
if b_show_linear_acc,
    h3 = figure(3);
    set(h3, 'Position', [pos_fig_left, pos_fig_bottom, pos_fig_width, pos_fig_height]);
    hold on;
    grid on;    
    plot(set_vel_from_acc(:,1), set_vel_from_acc(:,4), 'b-');
    plot(set_vel_from_gt(:,1), set_vel_from_gt(:,4), 'r-');
    %title('z, vel from fc-acc (blue), vel from gt (red)');

    x_min = min([set_vel_from_acc(:,1)' set_vel_from_gt(:,1)']);
    x_max = max([set_vel_from_acc(:,1)' set_vel_from_gt(:,1)']);    
    xlim([x_min, x_max])

    if b_save,
        fname_screenshot = sprintf('./screenshot/graph_vel_z_dataset_%d.png', idx_dataset);
        saveas(gcf, fname_screenshot);
    end
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
    plot(set_imu_raw(:,1), set_imu_raw(:,8), 'b-');
    %title('angular vel x');
    
    x_min = min( set_imu_raw(:,1)' );
    x_max = max( set_imu_raw(:,1)' );
    xlim([x_min, x_max])
    
    
    if b_save,
        fname_screenshot = sprintf('./screenshot/ang_z_dataset_%d.png', idx_dataset);
        saveas(h1, fname_screenshot);
    end
end


%%%%
if b_show_ang_vel,
    h2 = figure(11);
    set(h2, 'Position', [pos_fig_left, pos_fig_bottom, pos_fig_width, pos_fig_height]);
    hold on;
    grid on;
    plot(set_imu_raw(:,1), set_imu_raw(:,9), 'b-');
    %title('angular vel y');

    x_min = min( set_imu_raw(:,1)' );
    x_max = max( set_imu_raw(:,1)' );
    xlim([x_min, x_max])
    
    if b_save,
        fname_screenshot = sprintf('./screenshot/ang_z_dataset_%d.png', idx_dataset);
        saveas(gcf, fname_screenshot);
    end
end


%%%%
if b_show_ang_vel,
    h3 = figure(12);
    set(h3, 'Position', [pos_fig_left, pos_fig_bottom, pos_fig_width, pos_fig_height]);
    hold on;
    grid on;    
    plot(set_imu_raw(:,1), set_imu_raw(:,10), 'b-');
    %title('angular vel z');

    x_min = min( set_imu_raw(:,1)' );
    x_max = max( set_imu_raw(:,1)' );
    xlim([x_min, x_max])

    if b_save,
        fname_screenshot = sprintf('./screenshot/ang_z_dataset_%d.png', idx_dataset);
        saveas(gcf, fname_screenshot);
    end
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
    plot(set_ori_rpy(:,1), set_ori_rpy(:,2), 'b.', 'MarkerSize', 3);
    %title('ori roll - x');
    
    x_min = min( set_ori_rpy(:,1)' );
    x_max = max( set_ori_rpy(:,1)' ); 
    xlim([x_min, x_max])
        
    if b_save,
        fname_screenshot = sprintf('./screenshot/ori_roll_dataset_%d.png', idx_dataset);
        saveas(h1, fname_screenshot);
    end
end


%%%%
if b_show_ori_rpy,
    h2 = figure(21);
    set(h2, 'Position', [pos_fig_left, pos_fig_bottom, pos_fig_width, pos_fig_height]);
    hold on;
    grid on;
    plot(set_ori_rpy(:,1), set_ori_rpy(:,3), 'b.', 'MarkerSize', 3);
    %title('ori pitch - y');

    x_min = min( set_ori_rpy(:,1)' );
    x_max = max( set_ori_rpy(:,1)' );
    xlim([x_min, x_max])
    
    if b_save,
        fname_screenshot = sprintf('./screenshot/ori_pitch_dataset_%d.png', idx_dataset);
        saveas(gcf, fname_screenshot);
    end
end


%%%%
if b_show_ori_rpy,
    h3 = figure(22);
    set(h3, 'Position', [pos_fig_left, pos_fig_bottom, pos_fig_width, pos_fig_height]);
    hold on;
    grid on;
    plot(set_ori_rpy(:,1), set_ori_rpy(:,4), 'b.', 'MarkerSize', 3);
    %title('ori yaw - z');

    x_min = min( set_ori_rpy(:,1)' );
    x_max = max( set_ori_rpy(:,1)' );
    xlim([x_min, x_max])

    if b_save,
        fname_screenshot = sprintf('./screenshot/ori_yaw_dataset_%d.png', idx_dataset);
        saveas(gcf, fname_screenshot);
    end
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% draw flight controller height vs ground truth height
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%
if b_show_height,
    h1 = figure(30);
    set(h1, 'Position', [pos_fig_left, pos_fig_bottom, pos_fig_width, pos_fig_height]);
    hold on;
    grid on;

    plot(set_height_raw(:,1), set_height_raw(:,5), 'b-');       % flight controller
    plot(set_height_raw(:,1), set_height_raw(:,4), 'r-');       % gt
        
    x_min = min( set_ori_rpy(:,1)' );   % Note that in order to synchronize with set_ori_rpy, we used this min, max.
    x_max = max( set_ori_rpy(:,1)' ); 
    xlim([x_min, x_max])
        
    if b_save,
        fname_screenshot = sprintf('./screenshot/height_dataset_%d.png', idx_dataset);
        saveas(h1, fname_screenshot);
    end
end





