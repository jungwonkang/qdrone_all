clc
clear all;
close all;


%%%% set station position
P100 = [0.0, 0.0, 0.60]';
P101 = [5.0, 0.0, 1.20]';
P102 = [0.0, 5.0, 0.90]';
P103 = [5.0, 5.0, 1.8]';
P = [P100, P101, P102, P103];


b_use_noise = 0;
b_show_msg = 0;


%%%% gt position -> [x_mover, y_mover, z_mover] indicates GT pos of a mover.
x_mover = 3.0;
y_mover = 5.0;
z_mover = 10.0;
   
mag_noise = 0.3;


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
%res_pos_mover_est_solve1 = zeros(1,3);
% [res_pos_mover_est_solve1] = func_solve1(b_show_msg, P, range_mea_set, eye(4));


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% solve2 (multiple combination of 123 & 234 & 134)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
res_pos_mover_est_solve2 = zeros(1,3);
[res_pos_mover_est_solve2] = solve_mlat_stage1(b_show_msg, P, range_mea_set, eye(4));


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% solve3 (default + choose final solution by w)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%res_pos_mover_est_solve3 = zeros(1,3);
% [res_pos_mover_est_solve3] = func_solve3(b_show_msg, P, range_mea_set, w_set_norm);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% solve4 (multiple combination of 123 & 234 & 134 + choose final solution by w)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%res_pos_mover_est_solve4 = zeros(1,3);
% [res_pos_mover_est_solve4] = func_solve4(b_show_msg, P, range_mea_set, w_set_norm);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% solve5 (multiple combination of 123 & 234 & 134 + weighted RLS + choose final solution by w)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%res_pos_mover_est_solve5 = zeros(1,3);
% [res_pos_mover_est_solve5] = func_solve5(b_show_msg, P, range_mea_set, W, w_set_norm);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% solve6 (multiple combination of 123 & 234 & 134 + z_correction + choose final solution by w)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%res_pos_mover_est_solve6 = zeros(1,3);
%[res_pos_mover_est_solve6] = func_solve6(b_show_msg, P, range_mea_set, w_set_norm);








