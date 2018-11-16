clc
clear all;
close all;


%%%% set station position
P100 = [0.0, 0.0, 0.60]';
P101 = [5.0, 0.0, 1.20]';
P102 = [0.0, 5.0, 0.90]';
P103 = [5.0, 5.0, 1.8]';
P = [P100, P101, P102, P103];


res_table = [];

mag_noise = 0.1;
z_mover = 2.0;

b_use_noise = 1;


% for y_mover = -5.0:1.0:10.0,
%     for x_mover = -5.0:1.0:10.0,
for y_mover = -5.0,
    for x_mover = -3.0,

        % note that [x_mover, y_mover, z_mover] indicates GT pos of a mover.
        pos_mover = [x_mover, y_mover, z_mover]';
        
        range_P100_gt = norm(P100 - pos_mover);
        range_P101_gt = norm(P101 - pos_mover);
        range_P102_gt = norm(P102 - pos_mover);
        range_P103_gt = norm(P103 - pos_mover);
        
        
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
            
            w_set = 1.0 - abs(noise_in_range)./mag_noise;
            
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
        
%         fprintf('---Trilateration: Direct solution --- \n');
%         [N1 N2] = Trilateration(P, range_mea_set, W);
%         Nsol1 = N1(2:4,1);
%         disp([Nsol1])
%         fprintf('\n');

        fprintf('---Trilateration: Recursive least square--- \n');
        Nmat0 = RecTrilateration_raw(P, range_mea_set, W);
        Nmat = Nmat0(:,1:4);    % 3 -> 원래 5였음.
        fprintf('Recursive solutions \n');
        disp(Nmat(2:4,:))
        [n_mat m_mat]=size(Nmat);
        for i1=1:m_mat
            Nn = Nmat(:,i1);
            Nn = Nn(2:4);
            [Sn(i1,:) , F(i1)] = distanzen(Nn,P,range_mea_set);
            Diff(i1)= Nmat(1,i1) - (norm(Nn))^2;
        end
        
        
        [Fmin Imin] = min(F);
        Nrec = Nmat(:,Imin);
        fprintf('\n The solution which minimizes the error square sum \n');
        Nrec = Nrec(2:4);
        disp(Nrec);
        disp(Fmin);
        
%         Nrec_r = sign(real(Nrec)).*abs(Nrec);
%         [Sneu Fneu ] = distanzen(Nrec,P,range_mea_set);
%         fprintf('\n Calculated distances (Distances to solution)\n');
%         disp(Sneu )
%         fprintf('\n Error norm\n');
%         disp(Fneu)
        
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        %%%% store res
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        res_pos_mover_gt = [x_mover, y_mover, z_mover];
        res_pos_mover_est = [Nrec(1), Nrec(2), Nrec(3)];
        
        res_now = [res_pos_mover_gt, res_pos_mover_est, range_mea_set];
        res_table = [res_table; res_now];
                
    end
end

