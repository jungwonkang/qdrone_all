clc
clear all;
close all;


%%%% set station position
P100 = [0.0, 0.0, 0.60]';
P101 = [5.0, 0.0, 1.20]';
P102 = [0.0, 5.0, 0.90]';
P103 = [5.0, 5.0, 1.8]';
P = [P100, P101, P102, P103];


res_table_solve1 = [];
res_table_solve2 = [];
res_table_solve3 = [];
res_table_solve4 = [];
res_table_solve5 = [];
res_table_solve6 = [];


mag_noise_set = 0.0:0.1:1;
totnum_try = 5000;
b_use_noise = 1;
b_show_msg = 0;
z_mover = 10.0;


%%% init
vec_mean_err_only_x_on_noise_solve1 = zeros(1, length(mag_noise_set));
vec_mean_err_only_y_on_noise_solve1 = zeros(1, length(mag_noise_set));
vec_mean_err_only_z_on_noise_solve1 = zeros(1, length(mag_noise_set));
vec_mean_err_xyz_on_noise_solve1    = zeros(1, length(mag_noise_set));

vec_mean_err_only_x_on_noise_solve2 = zeros(1, length(mag_noise_set));
vec_mean_err_only_y_on_noise_solve2 = zeros(1, length(mag_noise_set));
vec_mean_err_only_z_on_noise_solve2 = zeros(1, length(mag_noise_set));
vec_mean_err_xyz_on_noise_solve2    = zeros(1, length(mag_noise_set));

vec_mean_err_only_x_on_noise_solve3 = zeros(1, length(mag_noise_set));
vec_mean_err_only_y_on_noise_solve3 = zeros(1, length(mag_noise_set));
vec_mean_err_only_z_on_noise_solve3 = zeros(1, length(mag_noise_set));
vec_mean_err_xyz_on_noise_solve3    = zeros(1, length(mag_noise_set));

vec_mean_err_only_x_on_noise_solve4 = zeros(1, length(mag_noise_set));
vec_mean_err_only_y_on_noise_solve4 = zeros(1, length(mag_noise_set));
vec_mean_err_only_z_on_noise_solve4 = zeros(1, length(mag_noise_set));
vec_mean_err_xyz_on_noise_solve4    = zeros(1, length(mag_noise_set));

vec_mean_err_only_x_on_noise_solve5 = zeros(1, length(mag_noise_set));
vec_mean_err_only_y_on_noise_solve5 = zeros(1, length(mag_noise_set));
vec_mean_err_only_z_on_noise_solve5 = zeros(1, length(mag_noise_set));
vec_mean_err_xyz_on_noise_solve5    = zeros(1, length(mag_noise_set));

vec_mean_err_only_x_on_noise_solve6 = zeros(1, length(mag_noise_set));
vec_mean_err_only_y_on_noise_solve6 = zeros(1, length(mag_noise_set));
vec_mean_err_only_z_on_noise_solve6 = zeros(1, length(mag_noise_set));
vec_mean_err_xyz_on_noise_solve6    = zeros(1, length(mag_noise_set));


for idx_mag_noise = 1:length(mag_noise_set),

    fprintf('idx_mag_noise: [%d]...\n', idx_mag_noise);
    
    %%%% init
    sum_err_x_solve1 = 0;
    sum_err_y_solve1 = 0;
    sum_err_z_solve1 = 0;
    sum_err_xyz_solve1 = 0;
    
    sum_err_x_solve2 = 0;
    sum_err_y_solve2 = 0;
    sum_err_z_solve2 = 0;
    sum_err_xyz_solve2 = 0;

    sum_err_x_solve3 = 0;
    sum_err_y_solve3 = 0;
    sum_err_z_solve3 = 0;
    sum_err_xyz_solve3 = 0;

    sum_err_x_solve4 = 0;
    sum_err_y_solve4 = 0;
    sum_err_z_solve4 = 0;
    sum_err_xyz_solve4 = 0;

    sum_err_x_solve5 = 0;
    sum_err_y_solve5 = 0;
    sum_err_z_solve5 = 0;
    sum_err_xyz_solve5 = 0;

    sum_err_x_solve6 = 0;
    sum_err_y_solve6 = 0;
    sum_err_z_solve6 = 0;
    sum_err_xyz_solve6 = 0;
    
    cnt_try = 0;
    
    mag_noise = mag_noise_set(idx_mag_noise);
    
    for idx_try = 1:totnum_try,
%         for y_mover = -5.0:1.0:10.0,
%             for x_mover = -5.0:1.0:10.0,
        for y_mover = 2.0,
           for x_mover = 3.0,

                % note that [x_mover, y_mover, z_mover] indicates GT pos of a mover.
                
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                %%%% set input (xyz_mover, range)
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                
                pos_mover_gt = [x_mover, y_mover, z_mover]';
                
                range_P100_gt = norm(P100 - pos_mover_gt);
                range_P101_gt = norm(P101 - pos_mover_gt);
                range_P102_gt = norm(P102 - pos_mover_gt);
                range_P103_gt = norm(P103 - pos_mover_gt);

                range_gt_set = [range_P100_gt, range_P101_gt, range_P102_gt, range_P103_gt];
                range_mea_set = range_gt_set;


                w_set = [];

                if b_use_noise == 1,
                    noise_in_range_ = mag_noise*rand(1,4);    % [0, 1]
                    sign_noise = randn(1,4);
                    noise_in_range = zeros(1,4);

                    for i = 1:4,
                        if sign_noise(i) >= 0.0,
                            noise_in_range(i) = noise_in_range_(i);
                        else
                            noise_in_range(i) = -1.0*noise_in_range_(i);                
                        end                                
                    end

                    term_noise = abs(noise_in_range)./mag_noise;
                    w_set = 1.0 - term_noise.^2;

                    range_mea_set = range_gt_set + noise_in_range;
                end

                %%%% norm
                w_set_norm = w_set./norm(w_set);


                W = diag(ones(1,length(range_mea_set)));

                if b_use_noise == 1,
                    W(1,1) = w_set_norm(1);
                    W(2,2) = w_set_norm(2);
                    W(3,3) = w_set_norm(3);
                    W(4,4) = w_set_norm(4);
                end

                % fprintf('---Trilateration: Direct solution --- \n');
                % [N1 N2] = Trilateration(P, range_mea_set, W);
                % Nsol1 = N1(2:4,1);
                % disp([Nsol1])
                % fprintf('\n');
                
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                %%%% solve1 (default)
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                res_pos_mover_est_solve1 = zeros(1,3);
                [res_pos_mover_est_solve1] = func_solve1(b_show_msg, P, range_mea_set, eye(4));
                
                
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                %%%% solve2 (multiple combination of 123 & 234 & 134)
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                res_pos_mover_est_solve2 = zeros(1,3);
                % [res_pos_mover_est_solve2] = func_solve2(b_show_msg, P, range_mea_set, eye(4));
                

                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                %%%% solve3 (default + choose final solution by w)
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                res_pos_mover_est_solve3 = zeros(1,3);
                % [res_pos_mover_est_solve3] = func_solve3(b_show_msg, P, range_mea_set, w_set_norm);

                
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                %%%% solve4 (multiple combination of 123 & 234 & 134 + choose final solution by w)
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                res_pos_mover_est_solve4 = zeros(1,3);
                % [res_pos_mover_est_solve4] = func_solve4(b_show_msg, P, range_mea_set, w_set_norm);
                

                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                %%%% solve5 (multiple combination of 123 & 234 & 134 + weighted RLS + choose final solution by w)
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                res_pos_mover_est_solve5 = zeros(1,3);
                % [res_pos_mover_est_solve5] = func_solve5(b_show_msg, P, range_mea_set, W, w_set_norm);
                
                
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                %%%% solve6 (multiple combination of 123 & 234 & 134 + z_correction + choose final solution by w)
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                res_pos_mover_est_solve6 = zeros(1,3);
                [res_pos_mover_est_solve6] = func_solve6(b_show_msg, P, range_mea_set, w_set_norm);

                
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                %%%% store res
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                res_now_solve1 = [pos_mover_gt', res_pos_mover_est_solve1, range_mea_set];
                res_now_solve2 = [pos_mover_gt', res_pos_mover_est_solve2, range_mea_set];
                res_now_solve3 = [pos_mover_gt', res_pos_mover_est_solve3, range_mea_set];
                res_now_solve4 = [pos_mover_gt', res_pos_mover_est_solve4, range_mea_set];
                res_now_solve5 = [pos_mover_gt', res_pos_mover_est_solve5, range_mea_set];
                res_now_solve6 = [pos_mover_gt', res_pos_mover_est_solve6, range_mea_set];

                res_table_solve1 = [res_table_solve1; res_now_solve1];
                res_table_solve2 = [res_table_solve2; res_now_solve2];
                res_table_solve3 = [res_table_solve3; res_now_solve3];
                res_table_solve4 = [res_table_solve4; res_now_solve4];
                res_table_solve5 = [res_table_solve5; res_now_solve5];
                res_table_solve6 = [res_table_solve6; res_now_solve6];


                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                %%%% compute err
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                vec_err_this_solve1 = abs( res_pos_mover_est_solve1 - pos_mover_gt' );
                vec_err_this_solve2 = abs( res_pos_mover_est_solve2 - pos_mover_gt' );
                vec_err_this_solve3 = abs( res_pos_mover_est_solve3 - pos_mover_gt' );
                vec_err_this_solve4 = abs( res_pos_mover_est_solve4 - pos_mover_gt' );
                vec_err_this_solve5 = abs( res_pos_mover_est_solve5 - pos_mover_gt' );
                vec_err_this_solve6 = abs( res_pos_mover_est_solve6 - pos_mover_gt' );
                
                val_err_xyz_solve1 = norm(vec_err_this_solve1);
                val_err_xyz_solve2 = norm(vec_err_this_solve2);
                val_err_xyz_solve3 = norm(vec_err_this_solve3);
                val_err_xyz_solve4 = norm(vec_err_this_solve4);
                val_err_xyz_solve5 = norm(vec_err_this_solve5);
                val_err_xyz_solve6 = norm(vec_err_this_solve6);
                
                
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                %%%% sum err
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                sum_err_x_solve1 = sum_err_x_solve1 + vec_err_this_solve1(1);
                sum_err_y_solve1 = sum_err_y_solve1 + vec_err_this_solve1(2);
                sum_err_z_solve1 = sum_err_z_solve1 + vec_err_this_solve1(3);
                sum_err_xyz_solve1 = sum_err_xyz_solve1 + val_err_xyz_solve1;
                
                sum_err_x_solve2 = sum_err_x_solve2 + vec_err_this_solve2(1);
                sum_err_y_solve2 = sum_err_y_solve2 + vec_err_this_solve2(2);
                sum_err_z_solve2 = sum_err_z_solve2 + vec_err_this_solve2(3);
                sum_err_xyz_solve2 = sum_err_xyz_solve2 + val_err_xyz_solve2;

                sum_err_x_solve3 = sum_err_x_solve3 + vec_err_this_solve3(1);
                sum_err_y_solve3 = sum_err_y_solve3 + vec_err_this_solve3(2);
                sum_err_z_solve3 = sum_err_z_solve3 + vec_err_this_solve3(3);
                sum_err_xyz_solve3 = sum_err_xyz_solve3 + val_err_xyz_solve3;

                sum_err_x_solve4 = sum_err_x_solve4 + vec_err_this_solve4(1);
                sum_err_y_solve4 = sum_err_y_solve4 + vec_err_this_solve4(2);
                sum_err_z_solve4 = sum_err_z_solve4 + vec_err_this_solve4(3);
                sum_err_xyz_solve4 = sum_err_xyz_solve4 + val_err_xyz_solve4;
                
                sum_err_x_solve5 = sum_err_x_solve5 + vec_err_this_solve5(1);
                sum_err_y_solve5 = sum_err_y_solve5 + vec_err_this_solve5(2);
                sum_err_z_solve5 = sum_err_z_solve5 + vec_err_this_solve5(3);
                sum_err_xyz_solve5 = sum_err_xyz_solve5 + val_err_xyz_solve5;

                sum_err_x_solve6 = sum_err_x_solve6 + vec_err_this_solve6(1);
                sum_err_y_solve6 = sum_err_y_solve6 + vec_err_this_solve6(2);
                sum_err_z_solve6 = sum_err_z_solve6 + vec_err_this_solve6(3);
                sum_err_xyz_solve6 = sum_err_xyz_solve6 + val_err_xyz_solve6;
                
                
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                %%%% update cnt
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                cnt_try = cnt_try + 1;
                
            end
        end
               
    end % -> end of idx_try loop
    
    
    %%%% compute mean err
    mean_err_x_solve1 = sum_err_x_solve1/cnt_try;
    mean_err_y_solve1 = sum_err_y_solve1/cnt_try;
    mean_err_z_solve1 = sum_err_z_solve1/cnt_try;
    mean_err_xyz_solve1 = sum_err_xyz_solve1/cnt_try;
    
    mean_err_x_solve2 = sum_err_x_solve2/cnt_try;
    mean_err_y_solve2 = sum_err_y_solve2/cnt_try;
    mean_err_z_solve2 = sum_err_z_solve2/cnt_try;
    mean_err_xyz_solve2 = sum_err_xyz_solve2/cnt_try;

    mean_err_x_solve3 = sum_err_x_solve3/cnt_try;
    mean_err_y_solve3 = sum_err_y_solve3/cnt_try;
    mean_err_z_solve3 = sum_err_z_solve3/cnt_try;
    mean_err_xyz_solve3 = sum_err_xyz_solve3/cnt_try;

    mean_err_x_solve4 = sum_err_x_solve4/cnt_try;
    mean_err_y_solve4 = sum_err_y_solve4/cnt_try;
    mean_err_z_solve4 = sum_err_z_solve4/cnt_try;
    mean_err_xyz_solve4 = sum_err_xyz_solve4/cnt_try;

    mean_err_x_solve5 = sum_err_x_solve5/cnt_try;
    mean_err_y_solve5 = sum_err_y_solve5/cnt_try;
    mean_err_z_solve5 = sum_err_z_solve5/cnt_try;
    mean_err_xyz_solve5 = sum_err_xyz_solve5/cnt_try;

    mean_err_x_solve6 = sum_err_x_solve6/cnt_try;
    mean_err_y_solve6 = sum_err_y_solve6/cnt_try;
    mean_err_z_solve6 = sum_err_z_solve6/cnt_try;
    mean_err_xyz_solve6 = sum_err_xyz_solve6/cnt_try;
    
    vec_mean_err_only_x_on_noise_solve1(idx_mag_noise) = mean_err_x_solve1;
    vec_mean_err_only_y_on_noise_solve1(idx_mag_noise) = mean_err_y_solve1;
    vec_mean_err_only_z_on_noise_solve1(idx_mag_noise) = mean_err_z_solve1;
    vec_mean_err_xyz_on_noise_solve1(idx_mag_noise) = mean_err_xyz_solve1;

    vec_mean_err_only_x_on_noise_solve2(idx_mag_noise) = mean_err_x_solve2;
    vec_mean_err_only_y_on_noise_solve2(idx_mag_noise) = mean_err_y_solve2;
    vec_mean_err_only_z_on_noise_solve2(idx_mag_noise) = mean_err_z_solve2;
    vec_mean_err_xyz_on_noise_solve2(idx_mag_noise) = mean_err_xyz_solve2;
    
    vec_mean_err_only_x_on_noise_solve3(idx_mag_noise) = mean_err_x_solve3;
    vec_mean_err_only_y_on_noise_solve3(idx_mag_noise) = mean_err_y_solve3;
    vec_mean_err_only_z_on_noise_solve3(idx_mag_noise) = mean_err_z_solve3;
    vec_mean_err_xyz_on_noise_solve3(idx_mag_noise) = mean_err_xyz_solve3;
    
    vec_mean_err_only_x_on_noise_solve4(idx_mag_noise) = mean_err_x_solve4;
    vec_mean_err_only_y_on_noise_solve4(idx_mag_noise) = mean_err_y_solve4;
    vec_mean_err_only_z_on_noise_solve4(idx_mag_noise) = mean_err_z_solve4;
    vec_mean_err_xyz_on_noise_solve4(idx_mag_noise) = mean_err_xyz_solve4;

    vec_mean_err_only_x_on_noise_solve5(idx_mag_noise) = mean_err_x_solve5;
    vec_mean_err_only_y_on_noise_solve5(idx_mag_noise) = mean_err_y_solve5;
    vec_mean_err_only_z_on_noise_solve5(idx_mag_noise) = mean_err_z_solve5;
    vec_mean_err_xyz_on_noise_solve5(idx_mag_noise) = mean_err_xyz_solve5;
    
    vec_mean_err_only_x_on_noise_solve6(idx_mag_noise) = mean_err_x_solve6;
    vec_mean_err_only_y_on_noise_solve6(idx_mag_noise) = mean_err_y_solve6;
    vec_mean_err_only_z_on_noise_solve6(idx_mag_noise) = mean_err_z_solve6;
    vec_mean_err_xyz_on_noise_solve6(idx_mag_noise) = mean_err_xyz_solve6;
    
end


figure(1),
    hold on;
    plot(mag_noise_set, vec_mean_err_only_x_on_noise_solve1, 'r-');
    plot(mag_noise_set, vec_mean_err_only_y_on_noise_solve1, 'g-');
    plot(mag_noise_set, vec_mean_err_only_z_on_noise_solve1, 'b-');
    plot(mag_noise_set, vec_mean_err_xyz_on_noise_solve1, 'y-');

figure(2),
    hold on;
    plot(mag_noise_set, vec_mean_err_only_x_on_noise_solve2, 'r-');
    plot(mag_noise_set, vec_mean_err_only_y_on_noise_solve2, 'g-');
    plot(mag_noise_set, vec_mean_err_only_z_on_noise_solve2, 'b-');
    plot(mag_noise_set, vec_mean_err_xyz_on_noise_solve2, 'y-');

figure(3),
    hold on;
    plot(mag_noise_set, vec_mean_err_only_x_on_noise_solve3, 'r-');
    plot(mag_noise_set, vec_mean_err_only_y_on_noise_solve3, 'g-');
    plot(mag_noise_set, vec_mean_err_only_z_on_noise_solve3, 'b-');
    plot(mag_noise_set, vec_mean_err_xyz_on_noise_solve3, 'y-');
    
figure(4),
    hold on;
    plot(mag_noise_set, vec_mean_err_only_x_on_noise_solve4, 'r-');
    plot(mag_noise_set, vec_mean_err_only_y_on_noise_solve4, 'g-');
    plot(mag_noise_set, vec_mean_err_only_z_on_noise_solve4, 'b-');
    plot(mag_noise_set, vec_mean_err_xyz_on_noise_solve4, 'y-');
    
figure(5),
    hold on;
    plot(mag_noise_set, vec_mean_err_only_x_on_noise_solve5, 'r-');
    plot(mag_noise_set, vec_mean_err_only_y_on_noise_solve5, 'g-');
    plot(mag_noise_set, vec_mean_err_only_z_on_noise_solve5, 'b-');
    plot(mag_noise_set, vec_mean_err_xyz_on_noise_solve5, 'y-');
    
figure(6),
    hold on;
    plot(mag_noise_set, vec_mean_err_only_x_on_noise_solve6, 'r-');
    plot(mag_noise_set, vec_mean_err_only_y_on_noise_solve6, 'g-');
    plot(mag_noise_set, vec_mean_err_only_z_on_noise_solve6, 'b-');
    plot(mag_noise_set, vec_mean_err_xyz_on_noise_solve6, 'y-');

vec_mean_err_xyz_on_noise_solve1
vec_mean_err_xyz_on_noise_solve2
vec_mean_err_xyz_on_noise_solve3
vec_mean_err_xyz_on_noise_solve4
vec_mean_err_xyz_on_noise_solve5
vec_mean_err_xyz_on_noise_solve6

