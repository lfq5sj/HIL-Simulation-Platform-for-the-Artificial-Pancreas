# Parametros del modelo
 
## Dinamica de la glucosa luego de una comida 
#     [9] Hovorka, R., et al. Nonlinear Model Predictive Control of Glucose
#     Concentration in Subjects with Type 1 Diabetes. 
 
Dg = 20.0 #carbohidratos (mg)
Ag = 0.8 #constante del modelo
tmax_I = 55.0 #tiempo pico de absorcion (s)
tmax_G = 40.0
time_food = 50
Vg = 13.79
 
## Parametros del sistema glucosa/insulina 
#     [7] Chen, J., et al. Continuous Drug Infusion for Diabetes Therapy: A 
#     Closed Loop Control System Design. 
 
p1=0.0337 #[min^-1]
p2=0.0209 #[min^-1]
p3=7.5*10**(-6) #[L/(mU*min^2)]
tau=0.08333 #[L^-1]
n=0.214 #[min^-1]
Gb=144.0 #[mg/dL]
u = 0.0
 
## Condiciones iniciales
I_0 = 0.0
X_0 = 0.0
G_0 = 144.0
t_0 = 0.0
 
h = 1
