% 2018/8/27
% Jungwon Kang

function [res_pos_mover_est] = solve_mlat_stage1(B_show_msg, P, range_mea_set, W)

if B_show_msg == 1,
    fprintf('---Trilateration: Recursive least square--- \n');
end

Nmat0_a = RecTrilateration_solve2_c123(P, range_mea_set, W);
Nmat0_b = RecTrilateration_solve2_c134(P, range_mea_set, W);
Nmat0_c = RecTrilateration_solve2_c234(P, range_mea_set, W);


%Nmat = Nmat0(:,1:4);    % 3 -> 원래 5였음.
Nmat = [Nmat0_a, Nmat0_b, Nmat0_c];

if B_show_msg == 1,
    fprintf('Recursive solutions \n');
    disp(Nmat(2:4,:))
end

[n_mat m_mat]=size(Nmat);
for i1=1:m_mat
    Nn = Nmat(:,i1);
    Nn = Nn(2:4);
    [Sn(i1,:) , F(i1)] = distanzen(Nn,P,range_mea_set);
    Diff(i1)= Nmat(1,i1) - (norm(Nn))^2;
end


[Fmin Imin] = min(F);
Nrec = Nmat(:,Imin);
Nrec = Nrec(2:4);

if B_show_msg == 1,                
    fprintf('\n The solution which minimizes the error square sum \n');
    disp(Nrec);
    disp(Fmin);
end

res_pos_mover_est = [Nrec(1), Nrec(2), Nrec(3)];




