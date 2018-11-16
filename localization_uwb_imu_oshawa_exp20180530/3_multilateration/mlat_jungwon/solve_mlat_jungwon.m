% 2018/8/27
% Jungwon Kang


function [set_xyz_stage1_out, set_xyz_stage2_out] = solve_mlat_jungwon(Set_pos_uwb, Set_range_uwb, B_run_stage2, Val_z_height)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% [Input]
%   Set_pos_uwb   : (M x 3), M: total number of uwb stations, 3: xyz
%   Set_range_uwb : (M X 1), range (m)
%   B_run_stage2  : true/false for running stage2
%
% [Output]
%   set_xyz_stage1_out: (1 x 3), 3: x,y,z
%   set_xyz_stage2_out: (1 x 3), 3: x,y,z
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%% stage 1
[set_xyz_stage1_out] = solve_mlat_stage1(false, Set_pos_uwb', Set_range_uwb', eye(4));
    % completed to set
    %   set_xyz_stage1_out: (1 x 3), 3: x,y,z

    
%%%% stage 2
if B_run_stage2,
    %%%% change z
    set_xyz0    = set_xyz_stage1_out;
    set_xyz0(3) = Val_z_height;
    
    [set_xyz_stage2_out] = solve_mlat_stage2(Set_pos_uwb, Set_range_uwb, Val_z_height, set_xyz0);
        % completed to set
        %   set_xyz_stage2_out: (1 x 3), 3: x,y,z
end


end
