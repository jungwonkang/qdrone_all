
function [res_pos_mover_est] = func_solve6(B_show_msg, P, range_mea_set, w_set_norm)

b_z_pass = 0;
b_z_correction = 1;

W = eye(4);

if B_show_msg == 1,
    fprintf('---Trilateration: Recursive least square--- \n');
end

Nmat0_a = RecTrilateration_solve2_c123(P, range_mea_set, W);
Nmat0_b = RecTrilateration_solve2_c124(P, range_mea_set, W);
Nmat0_c = RecTrilateration_solve2_c134(P, range_mea_set, W);
Nmat0_d = RecTrilateration_solve2_c234(P, range_mea_set, W);


%Nmat = Nmat0(:,1:4);    % 3 -> 원래 5였음.
Nmat = [Nmat0_a, Nmat0_b, Nmat0_c, Nmat0_d];


if B_show_msg == 1,
    fprintf('Recursive solutions \n');
    disp(Nmat(2:4,:))
end


if b_z_pass == 1,
    Nmat_ = [];
    
    for i = 1:size(Nmat, 2),
        Nn_ = Nmat(:,i);
        Nn = Nn_(2:4);
        
        if Nn(3) < 0,
            continue;
        end
        
        Nmat_ = [Nmat_, Nn_];
    end
    
    Nmat = Nmat_;
    
    if size(Nmat, 2) == 0,
        disp('-- func_solve6: exceptional case --');
    end
end


[n_mat m_mat]=size(Nmat);
for i1=1:m_mat
    Nn = Nmat(:,i1);
    Nn = Nn(2:4);
        
    if b_z_correction == 1,
        if Nn(3) < 0,
            Nn(3) = -1*Nn(3);
        end
    end
    
    [Sn(i1,:) , F(i1)] = distanzen_w(Nn, P, range_mea_set, w_set_norm);
    % Diff(i1)= Nmat(1,i1) - (norm(Nn))^2;
end


[Fmin Imin] = min(F);
Nrec = Nmat(:,Imin);
Nrec = Nrec(2:4);

if b_z_correction == 1,
    if Nrec(3) < 0,
        Nrec(3) = -1*Nrec(3);
    end
end


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



