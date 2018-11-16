
% Trilateration algorithm
% paper "An algebraic solution to the multilateration problem"
% Author: Norrdine, Abdelmoumen  (norrdine@hotmail.de)
% https://www.researchgate.net/publication/275027725_An_Algebraic_Solution_to_the_Multilateration_Problem
% usage: [N1 N2] = RecTrilateration(P,S,W) 
% P = [P1 P2 P3 P4 ..] Reference points matrix
% S = [s1 s2 s3 s4 ..] distance matrix.
% W : Weights Matrix (Statistics).
% N : calculated solution
% THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY!!
function Nmat = RecTrilateration_np3(P,S,W)
[mp,np] = size(P);

ns = length(S);
if (ns~=np)
    error('Anzahl der Referenzpunkte und der Strecken sind nicht gleich');
end
A=[]; b=[];
for i1=1:np
    x = P(1,i1); y = P(2,i1); z = P(3,i1);
    s = S(i1);
    A = [A ; 1 -2*x  -2*y  -2*z]; 
    b= [b ; s^2-x^2-y^2-z^2 ];
end

if (np==3)
    warning off;
    Xp= A\b;  % Gaussian elimination 
    % or Xp=pinv(A)*b; 
   % the matrix  inv(A'*A)*A' or inv(A'*C*A)*A'*C or pinv(A)
    % depend only on the reference points
    % it could be computed only once
    xp = Xp(2:4,:);
    Z = null(A);
    z = Z(2:4,:);
    if rank (A)==3
        %Polynom coeff.
        a2 = z(1)^2 + z(2)^2 + z(3)^2 ;
        a1 = 2*(z(1)*xp(1) + z(2)*xp(2) + z(3)*xp(3))-Z(1);
        a0 = xp(1)^2 + xp(2)^2 + xp(3)^2 - Xp(1);
        p = [a2 a1 a0];
        
        %%%% my own trick
        ca = p(1);
        cb = p(2);
        cc = p(3);
        
		val_temp = (cb*cb - 4.0*ca*cc);

        if val_temp < 0.0,	
			val_t1 = -1.0*cb;
			val_t2 = -1.0*cb;
        else
			val_t1 = -1.0*cb + sqrt(cb*cb - 4.0*ca*cc);
			val_t2 = -1.0*cb - sqrt(cb*cb - 4.0*ca*cc);
        end
        
		t(1) = val_t1 / (2.0*ca);
		t(2) = val_t2 / (2.0*ca);
        % t = roots(p);

        %L�sungen
        N1 = Xp + t(1)*Z;
        N2 = Xp + t(2)*Z;
        Nmat(:,1) = N1;
        Nmat(:,2) = N2;
    end
end

