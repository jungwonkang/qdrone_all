% 2018/8/25
% Jungwon Kang

% @ How to combine multiple objective functions for lsqnonlin
%   https://www.mathworks.com/matlabcentral/answers/285211-how-to-combine-multiple-objective-functions-for-lsqnonlin
%   https://www.gnu.org/software/gsl/manual/html_node/Computing-the-covariance-matrix-of-best-fit-parameters.html
% 
% @ Passing Extra Parameters
%   https://www.mathworks.com/help/optim/ug/passing-extra-parameters.html

function set_err = my_objfunc_mlat_stage2(params)

global g_mlat_pos_uwb_x1    g_mlat_pos_uwb_y1   g_mlat_pos_uwb_z1   g_mlat_range_uwb1;
global g_mlat_pos_uwb_x2    g_mlat_pos_uwb_y2   g_mlat_pos_uwb_z2   g_mlat_range_uwb2;
global g_mlat_pos_uwb_x3    g_mlat_pos_uwb_y3   g_mlat_pos_uwb_z3   g_mlat_range_uwb3;
global g_mlat_pos_uwb_x4    g_mlat_pos_uwb_y4   g_mlat_pos_uwb_z4   g_mlat_range_uwb4;
global g_mlat_z_height;


x_drone = params(1);    % values to be estimated
y_drone = params(2);
z_drone = params(3);


e_uwb1 = g_mlat_range_uwb1 - sqrt( (x_drone - g_mlat_pos_uwb_x1)^2 + (y_drone - g_mlat_pos_uwb_y1)^2 + (z_drone - g_mlat_pos_uwb_z1)^2 );
e_uwb2 = g_mlat_range_uwb2 - sqrt( (x_drone - g_mlat_pos_uwb_x2)^2 + (y_drone - g_mlat_pos_uwb_y2)^2 + (z_drone - g_mlat_pos_uwb_z2)^2 );
e_uwb3 = g_mlat_range_uwb3 - sqrt( (x_drone - g_mlat_pos_uwb_x3)^2 + (y_drone - g_mlat_pos_uwb_y3)^2 + (z_drone - g_mlat_pos_uwb_z3)^2 );
e_uwb4 = g_mlat_range_uwb4 - sqrt( (x_drone - g_mlat_pos_uwb_x4)^2 + (y_drone - g_mlat_pos_uwb_y4)^2 + (z_drone - g_mlat_pos_uwb_z4)^2 );
e_z    = z_drone - g_mlat_z_height;

set_err = [e_uwb1; e_uwb2; e_uwb3; e_uwb4; e_z];

end


