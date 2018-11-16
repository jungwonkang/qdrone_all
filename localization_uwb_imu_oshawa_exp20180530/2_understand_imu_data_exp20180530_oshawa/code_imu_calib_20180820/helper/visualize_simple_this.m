% 2018/08/12
% Jungwon Kang


function visualize_simple_this(IDX_data_packet, Time_now, Mat_body_rot, Mat_body_trans)

% Mat_body_rot           : (3 x 3)
% Mat_body_trans         : (1 x 3)


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% setting
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%% pos of fig
pos_fig_left    = 100;
pos_fig_bottom  = 100;
pos_fig_width   = 700;
pos_fig_height  = 700;

%%%%
view_az = 20;
view_el = 30;

x_axis_min = -3;
x_axis_max =  3;
y_axis_min = -3;
y_axis_max =  3;
z_axis_min = -3;
z_axis_max =  3;

%%%% visualization style (for current axis)
option_arrow_current_axis_x = 'r-2';
option_arrow_current_axis_y = 'g-2';
option_arrow_current_axis_z = 'b-2';

style_arrow_current_axis_w  = 0.5;
style_arrow_current_axis_h  = 0.5;
style_arrow_current_axis_ip = 0.1;


%%%% visualization length (for current axis)
length_axis  = 1.0;


format_fname_img_res = './screenshot_saved/img_res_%d.png';
fname_img_res        = sprintf(format_fname_img_res, IDX_data_packet);

format_str_title = 'Time: %fs';
str_title = sprintf(format_str_title, Time_now);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% compute axis
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%% GT
[vec_x_axis_current, ...
 vec_y_axis_current, ...
 vec_z_axis_current] = compute_axis(length_axis, Mat_body_rot, Mat_body_trans);



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% draw
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
close all;
h_fig = figure(1);
    set(h_fig, 'Position', [pos_fig_left, pos_fig_bottom, pos_fig_width, pos_fig_height]);
    set(h_fig, 'Color', [1 1 1]);


daspect([1 1 1])    % for arrow3
view(view_az, view_el);

grid on;
hold on;

xlabel('x', 'fontsize',16);
ylabel('y', 'fontsize',16);
zlabel('z', 'fontsize',16);
title(str_title, 'fontsize',16);

axis equal;
axis([x_axis_min, x_axis_max, y_axis_min, y_axis_max, z_axis_min, z_axis_max]);
camlight left;


%%%% draw axis (body)
arrow3(vec_x_axis_current(1,:), vec_x_axis_current(2,:), option_arrow_current_axis_x, style_arrow_current_axis_w, style_arrow_current_axis_h, style_arrow_current_axis_ip);
arrow3(vec_y_axis_current(1,:), vec_y_axis_current(2,:), option_arrow_current_axis_y, style_arrow_current_axis_w, style_arrow_current_axis_h, style_arrow_current_axis_ip);
arrow3(vec_z_axis_current(1,:), vec_z_axis_current(2,:), option_arrow_current_axis_z, style_arrow_current_axis_w, style_arrow_current_axis_h, style_arrow_current_axis_ip);


drawnow;
pause(0.01);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% save as img
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if 1,
    f = getframe(h_fig);
    colormap(f.colormap);
    imwrite(f.cdata, fname_img_res);
    pause(0.01);
end

%drawnow;
%saveas(gcf, fname_img_res);
% pause(0.001);



