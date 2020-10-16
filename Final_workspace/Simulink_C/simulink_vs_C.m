%% Universidad de Costa Rica
 % Facultad de Ingeniería
 % Escuelta de Ingeniería Eléctrica 
 % Proyecto Eléctrico 
 % Luisa Fernanda Quesada Camacho 
 % 30 Junio 2018 
 
 load("Final_workspace/Simulink_C/simulink_vs_C.mat")
 
 %% Prueba de señal del controlador PID en Simulink sobre modelo en C
 % Comida: 40g, Tiempo comida: 200min, Tiempo max: 1500min
 
 data_glucose = glucose_PID.Data;
 time = glucose_PID.Time;
 
filename_rk4_glucose_pid = "Final_Data/Simulink_C/rk4_glucose_PID.csv"
F_rk4_pid = csvread(filename_rk4_glucose_pid)
data_rk4_pid  = F_rk4_pid(:, 1);
figure(1)
plot(time, data_rk4_pid);
hold on 
plot(time, data_glucose)
 
 %% Prueba de la salida del proceso con el controlador PID en Simulink 
 %  sobre el controlador PID en C
 % Comida: 40g, Tiempo comida: 200min, Tiempo max: 1500min
 
 data_insulin = insulin_PID.Data;
 time = insulin_PID.Time;

  
filename_pid_insulin_rk4 = "Final_Data/Simulink_C/pid_insulin_rk4.csv"
F_pid_rk4 = csvread(filename_pid_insulin_rk4)
data_pid_rk4  = F_pid_rk4(:, 1);
figure(1)
plot(time, data_pid_rk4);
hold on 
plot(time, data_insulin)

 %% Prueba de señal del controlador LQR en Simulink sobre modelo en C
 % Comida: 40g, Tiempo comida: 200min, Tiempo max: 1500min
 
 data_glucose = glucose_LQR.Data;
 time = glucose_LQR.Time;
 
filename_rk4_glucose_lqr = "Final_Data/Simulink_C/rk4_glucose_LQR.csv"
F_rk4_lqr = csvread(filename_rk4_glucose_lqr)
data_rk4_lqr  = F_rk4_lqr(:, 1);
figure(1)
plot(time, data_rk4_lqr);
hold on 
plot(time, data_glucose)
 
 %% Prueba de la salida del proceso con el controlador LQR en Simulink 
 %  sobre el controlador PID en C
 % Comida: 40g, Tiempo comida: 200min, Tiempo max: 1500min
 
 data_insulin = insulin_LQR.Data;
 time = insulin_LQR.Time;

  
filename_lqr_insulin_rk4 = "Final_Data/Simulink_C/lqr_insulin_rk4.csv"
F_lqr_rk4 = csvread(filename_lqr_insulin_rk4)
data_lqr_rk4  = F_lqr_rk4(:, 1);
figure(1)
plot(time, data_lqr_rk4);
hold on 
plot(time, data_insulin)