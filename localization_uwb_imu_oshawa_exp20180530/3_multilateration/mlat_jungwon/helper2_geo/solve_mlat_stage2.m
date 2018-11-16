% 2018/8/27
% Jungwon Kang

% @ Passing Extra Parameters
%   https://www.mathworks.com/help/optim/ug/passing-extra-parameters.html

function [set_xyz_out] = solve_mlat_stage2(Set_pos_uwb, Set_range_uwb, Val_z_height, Set_xyz0)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% [Input]
%   Set_pos_uwb   : (M x 3), M: total number of uwb stations, 3: x,y,z
%   Set_range_uwb : (M X 1), range (m)
%   Val_z_height  : scalar (m), ex) height from flight controller
%   Set_xyz0      : (1 x 3), 3: x,y,z -> initial guess for optimization
% [Output]
%   set_xyz_out   : (1 x 3), 3: x,y,z
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%% declare
global g_mlat_pos_uwb_x1    g_mlat_pos_uwb_y1   g_mlat_pos_uwb_z1   g_mlat_range_uwb1;
global g_mlat_pos_uwb_x2    g_mlat_pos_uwb_y2   g_mlat_pos_uwb_z2   g_mlat_range_uwb2;
global g_mlat_pos_uwb_x3    g_mlat_pos_uwb_y3   g_mlat_pos_uwb_z3   g_mlat_range_uwb3;
global g_mlat_pos_uwb_x4    g_mlat_pos_uwb_y4   g_mlat_pos_uwb_z4   g_mlat_range_uwb4;
global g_mlat_z_height;


%%%% set
g_mlat_pos_uwb_x1 = Set_pos_uwb(1,1);    g_mlat_pos_uwb_y1 = Set_pos_uwb(1,2);    g_mlat_pos_uwb_z1 = Set_pos_uwb(1,3);
g_mlat_range_uwb1 = Set_range_uwb(1);

g_mlat_pos_uwb_x2 = Set_pos_uwb(2,1);    g_mlat_pos_uwb_y2 = Set_pos_uwb(2,2);    g_mlat_pos_uwb_z2 = Set_pos_uwb(2,3);
g_mlat_range_uwb2 = Set_range_uwb(2);

g_mlat_pos_uwb_x3 = Set_pos_uwb(3,1);    g_mlat_pos_uwb_y3 = Set_pos_uwb(3,2);    g_mlat_pos_uwb_z3 = Set_pos_uwb(3,3);
g_mlat_range_uwb3 = Set_range_uwb(3);

g_mlat_pos_uwb_x4 = Set_pos_uwb(4,1);    g_mlat_pos_uwb_y4 = Set_pos_uwb(4,2);    g_mlat_pos_uwb_z4 = Set_pos_uwb(4,3);
g_mlat_range_uwb4 = Set_range_uwb(4);

g_mlat_z_height   = Val_z_height;


%%%% optimize
set_xyz_out = lsqnonlin(@my_objfunc_mlat_stage2, Set_xyz0);

end

