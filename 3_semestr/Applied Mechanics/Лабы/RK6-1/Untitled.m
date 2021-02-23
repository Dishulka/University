l = 200;
b = 10;
h = 30;
F = 30;
J = (b * h^3) / 12;
E = 2e5;
N_el = 4;
E_sys = [E, E, E, E];
L_sys = [l/2, l, l, l/2];
N_dofs = 2*(N_el + 1);
K_glob = zeros(N_dofs);
U_node = [1,1,  0,0,  1,0,  0,0,  1,1];
F_node = [0,0,  2*F,-F*l,  0,3*F*l,  -2*F,0,  0,0];
K_loc = zeros(4);
Index_M = [1:4;3:6;5:8;7:10;];

for i = 1:N_el
    L = L_sys(i);
    E = E_sys(i);
    K_loc = [12*E*J/(L^3), 6*E*J/(L^2), -12*E*J/(L^3), 6*E*J/(L^2);6*E*J/(L^2), 4*E*J/L, -6*E*J/(L^2), 2*E*J/L;-12*E*J/(L^3), -6*E*J/(L^2), 12*E*J/(L^3), -6*E*J/(L^2);6*E*J/(L^2), 2*E*J/L, -6*E*J/(L^2), 4*E*J/L];
    for j = 1:4
        for k = 1:4
            K_glob(Index_M(i, j),Index_M(i, k)) = K_glob(Index_M(i, j),Index_M(i, k))+K_loc(j,k);
        end
    end 
end 

for i = 1:N_dofs
    if(U_node(i) == 1)
        K_glob(i, :) = 0; 
        K_glob(:, i) = 0; 
        K_glob(i, i) = 1; 
    end
end

U = (K_glob .* pinv(K_glob)) * (F_node);
for i = 1:N_dofs
    if(rem(i,2) == 1)
        disp(sprintf('%.8f mm',U(i)))
    else
        disp(sprintf('%.8f deg',U(i)*180/pi))
    end
end