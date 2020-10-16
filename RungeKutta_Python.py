import csv
from math import exp
from bergman_parameters import p1, p2, p3, tau, n, Gb, u, I_0, X_0, G_0, t_0, h, Dg, Ag, tmax_I, tmax_G, time_food, Vg; 

# Función de comida
# Si el tiempo es menor al tiempo de comida la salida es igual a cero, sino hace el cálculo de la ecuación de comida
def m(t): 
    if t < time_food:
        m = 0
    else:
        #Ingesta de carbohidratos
        t = t - time_food
        m = 100*Dg*Ag*t*exp(-t/tmax_I)/(Vg*tmax_G**2)

    return m

# Ecuaciones del método de Runge Kutta 4 para el modelo mínimo de Bergman
def RungeKutta4(t, I, X, G):
    
    a1 =  (-n * I) + (tau * u)
    b1 = (-p2 * X) + (p3 * I)
    c1 = -(p1 + X)*G + p1*Gb + m(t)
 
    t_1 = t + (h/2.0)
    I_1 = I + (h/2.0) * a1
    X_1 = X + (h/2.0) * b1
    G_1 = G + (h/2.0) * c1
    a2 =  (-n * I_1) + (tau * u)
    b2 = (-p2 * X_1) + (p3 * I_1)
    c2 = -(p1 + X_1)*G + p1*Gb + m(t_1)
 
    t_2 = t + (h/2.0)
    I_2 = I + (h/2.0) * a2
    X_2 = X + (h/2.0) * b2
    G_2 = G + (h/2.0) * c2
    a3 =  (-n * I_2) + (tau * u)
    b3 = (-p2 * X_2) + (p3 * I_2)
    c3 = -(p1 + X_2)*G + p1*Gb + m(t_2)
 
    t_3 = t + h
    I_3 = I + h * a3
    X_3 = X + h * b3
    G_3 = G + h * c3
    a4 =  (-n * I_3) + (tau * u)
    b4 = (-p2 * X_3) + (p3 * I_3)
    c4 = -(p1 + X_3)*G + p1*Gb + m(t_3)
 
    t_prox = t + h
    I_prox = I + (h/6.0) * (a1 + 2.0 * a2 + 2.0 * a3 + a4)
    X_prox = X + (h/6.0) * (b1 + 2.0 * b2 + 2.0 * b3 + b4)
    G_prox = G + (h/6.0) * (c1 + 2.0 * c2 + 2.0 * c3 + c4)
 
    return t_prox, I_prox, X_prox, G_prox
    
def main():

	# Se crean los vectores para guardar los datos
    i = 0
    t = []
    I = []
    X = []
    G = []

	# Se agregan las condiciones iniciales
    t.append(t_0)
    I.append(I_0)
    X.append(X_0)
    G.append(G_0)

	# Se calculan 700 minutos del modelo
    while(i < 700):
        t_prox, I_prox, X_prox, G_prox = RungeKutta4(t[i], I[i], X[i], G[i])
        t.append(t_prox);
        I.append(I_prox);
        X.append(X_prox);
        G.append(G_prox);
        i = i + 1

	# Se guardan los datos en un csv
    with open('rk4_py_20g.csv', 'wb') as f:
        writer = csv.writer(f)
        for data in G:
            writer.writerow([data])

if __name__ == "__main__":
    main()
