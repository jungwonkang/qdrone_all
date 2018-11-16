
% Calculate distance between Nn and referece points Pi
% berechnet Abst?de zwischen Nn und die Referenzpunkte Pi
% P= [P1 P2 ...]  ; measured distances : S=[s1 s2 ...]
% Sn = []: calculated distances 
% F : Error norm
function [S_expected , F] = distanzen_w(Nn, P, S_real, w_set_norm)
% global P S

for i = 1:length(S_real),
    S_expected(i) = norm(P(:,i) - Nn);
end

% Sn: expected
% S: real

%F = norm(S-S_expected);

F = 0;

for i = 1:length(S_real),
    d_val = S_expected(i) - S_real(i);
    Fi = w_set_norm(i)*d_val^2;
    F = F + Fi;
end
