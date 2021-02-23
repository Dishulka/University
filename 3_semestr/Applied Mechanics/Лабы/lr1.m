function beam_fem
format long
E = [ 2e11; 2e11; 2e11; 2e11 ]; % ��
L_beam = 0.2;
L = [ L_beam; L_beam; 1.5*L_beam; L_beam ]; % �
b = 10e-3; % �
h = 20e-3; % �
F = 10; % �
I = [ b*h^3/12; b*h^3/12; b*h^3/12; b*h^3/12 ]; % ������ �������
f = [ 0; 0; -6*F; 0; 0; -3*F*L_beam; 4*F; 2*F*L_beam; 0; 0 ];
u_flag = [ 0; 0; 1; 1; 0; 1; 1; 0; 1; 1 ];
N_el = 4; % ���������� ���������
N_dof = 2; % ���������� �������� ������� � ����
N_nod = 5; % ���������� �����
N_k = N_nod * N_dof; % ����� ���������� �������� �������
Matrix_index = [ 1, 2, 3, 4;
 3, 4, 5, 6;
 5, 6, 7, 8;
7, 8, 9, 10 ];
K_el = zeros(4, 4); % ������� ��������� ��� ������ ��������
K_glob = zeros(10, 10); % ���������� ������� ���������
for i = 1:N_el
K_el = Kel_calc(E(i), L(i), I(i));
for j = 1:size(Matrix_index, 2)
for k = 1:size(K_el, 1)
K_glob(Matrix_index(i, k), Matrix_index(i, j))= K_glob(Matrix_index(i, k), Matrix_index(i, j)) + K_el(k, j);
end
end
end
for i = 1:size(u_flag, 1)
if (u_flag(i) == 0)
K_glob(i, :) = 0;
K_glob(:, i) = 0;
K_glob(i, i) = 1;
end
end
u = inv(K_glob)*f % inv(K_glob) - ����������������� ������� ���������
end
function K_el = Kel_calc(E, L, I)
K_el = [ 12*E*I/L^3, 6*E*I/L^2, -12*E*I/L^2, 6*E*I/L^2;
 6*E*I/L^2, 4*E*I/L, -6*E*I/L^2, 2*E*I/L;
 -12*E*I/L^2, -6*E*I/L^2, 12*E*I/L^3, -6*E*I/L^2;
 6*E*I/L^2, 2*E*I/L, -6*E*I/L^2, 4*E*I/L ];
end