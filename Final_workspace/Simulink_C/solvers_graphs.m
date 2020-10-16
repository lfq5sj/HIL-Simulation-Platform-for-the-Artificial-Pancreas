%% Universidad de Costa Rica
 % Facultad de Ingenier�a
 % Escuelta de Ingenier�a El�ctrica 
 % Proyecto El�ctrico 
 % Luisa Fernanda Quesada Camacho 
 % 30 Junio 2018 
 
%% Gr�ficas de los solucionadores de Euler y RK4 para el modelo m�nimo
 % de Bergman en Python 

% Euler
time = linspace(0,700,701) 
filename_20g_e = "Final_Data/Solvers_Python/euler_py_20g.csv"
filename_40g_e = "Final_Data/Solvers_Python/euler_py_40g.csv"
filename_60g_e = "Final_Data/Solvers_Python/euler_py_60g.csv"
F_20_e = csvread(filename_20g_e)
F_40_e = csvread(filename_40g_e)
F_60_e = csvread(filename_60g_e)
data_20_e  = F_20_e(:, 1);
data_40_e  = F_40_e(:, 1);
data_60_e  = F_60_e(:, 1);
figure(1)
plot(time, data_20_e);
hold on 
plot(time, data_40_e);
plot(time, data_60_e);

% Runge Kutta 4 
filename_20g_rk = "Final_Data/Solvers_Python/rk4_py_20g.csv"
filename_40g_rk = "Final_Data/Solvers_Python/rk4_py_40g.csv"
filename_60g_rk = "Final_Data/Solvers_Python/rk4_py_60g.csv"
F_20_rk = csvread(filename_20g_rk)
F_40_rk = csvread(filename_40g_rk)
F_60_rk = csvread(filename_60g_rk)
data_20_rk  = F_20_rk(:, 1);
data_40_rk  = F_40_rk(:, 1);
data_60_rk  = F_60_rk(:, 1);
figure(2)
plot(time, data_20_rk);
hold on 
plot(time, data_40_rk);
plot(time, data_60_rk);

% IAE entre las soluciones y el modelo en Simulink 

% Comparaci�n para una comida de 40g
data_40_sim = modelo_40g.Data;
figure(3)
plot(time, data_40_sim, M1 = "sim");
hold on
plot(time, data_40_e, M2 = "euler");
plot(time, data_40_rk, M3 = "rk4");

error_e = data_40_sim - data_40_e;
error_rk = data_40_sim - data_40_rk;
IAE_e = sum(abs(error_e));
IAE_rk = sum(abs(error_rk));

%% Gr�ficas de los solucionadores de Euler y RK4 para el modelo m�nimo de 
% de Bergman en C

% Euler
time = linspace(0,700,701) 
filename_20g_e = "Final_Data/Solvers_C/euler_c_20g.csv"
filename_40g_e = "Final_Data/Solvers_C/euler_c_40g.csv"
filename_60g_e = "Final_Data/Solvers_C/euler_c_60g.csv"
F_20_e = csvread(filename_20g_e)
F_40_e = csvread(filename_40g_e)
F_60_e = csvread(filename_60g_e)
data_20_e  = F_20_e(:, 1);
data_40_e  = F_40_e(:, 1);
data_60_e  = F_60_e(:, 1);
figure(1)
plot(time, data_20_e);
hold on 
plot(time, data_40_e);
plot(time, data_60_e);

% Runge Kutta 4
time = linspace(0,700,701) 
filename_20g_rk = "Final_Data/Solvers_C/rk4_c_20g.csv"
filename_40g_rk = "Final_Data/Solvers_C/rk4_c_40g.csv"
filename_60g_rk = "Final_Data/Solvers_C/rk4_c_60g.csv"
F_20_rk = csvread(filename_20g_rk)
F_40_rk = csvread(filename_40g_rk)
F_60_rk = csvread(filename_60g_rk)
data_20_rk  = F_20_rk(:, 1);
data_40_rk  = F_40_rk(:, 1);
data_60_rk  = F_60_rk(:, 1);
figure(2)
plot(time, data_20_rk);
hold on 
plot(time, data_40_rk);
plot(time, data_60_rk);

% IAE entre las soluciones y el modelo en Simulink

% Comparaci�n para una comida de 40g
data_40_sim = modelo_40g.Data;
figure(3)
plot(time, data_40_sim);
hold on
plot(time, data_40_e);
plot(time, data_40_rk);

error_e = data_40_sim - data_40_e;
error_rk = data_40_sim - data_40_rk;
IAE_e = sum(abs(error_e));
IAE_rk = sum(abs(error_rk));