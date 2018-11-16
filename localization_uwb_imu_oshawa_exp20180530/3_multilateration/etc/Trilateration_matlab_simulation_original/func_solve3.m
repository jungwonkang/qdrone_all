
function [res_pos_mover_est] = func_solve3(B_show_msg, P, range_mea_set, w_set_norm)

W = eye(4);

if B_show_msg == 1,
    fprintf('---Trilateration: Recursive least square--- \n');
end

Nmat0 = RecTrilateration(P, range_mea_set, W);
Nmat = Nmat0(:,1:4);    % 3 -> 원래 5였음.

if B_show_msg == 1,
    fprintf('Recursive solutions \n');
    disp(Nmat(2:4,:))
end

[n_mat m_mat]=size(Nmat);
for i1=1:m_mat
    Nn = Nmat(:,i1);
    Nn = Nn(2:4);
    [Sn(i1,:) , F(i1)] = distanzen_w(Nn, P, range_mea_set, w_set_norm);
    %Diff(i1)= Nmat(1,i1) - (norm(Nn))^2;
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

% Nrec_r = sign(real(Nrec)).*abs(Nrec);
% [Sneu Fneu ] = distanzen(Nrec,P,range_mea_set);
% fprintf('\n Calculated distances (Distances to solution)\n');
% disp(Sneu )
% fprintf('\n Error norm\n');
% disp(Fneu)



