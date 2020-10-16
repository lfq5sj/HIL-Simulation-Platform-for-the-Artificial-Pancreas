#include <stdio.h>  
#include <math.h>
#include "BergmanSolvers.h"

// Función de comida

double m(float t, struct food_parameters *food) {
	double m;
	if (t < food->time_food) {
		m = 0.0;
	}
	else {
		t = t - food->time_food;
		m = 100.0 * food->Dg*food->Ag*t*exp(-t / food->tmax_I) / (food->Vg*pow(food->tmax_G, 2.0));
	}
	return m;

};

// Solucionador de Euler 

void eulerSolver(struct parameters *param, struct states *currentStates, struct food_parameters *food) {
	double I_prox, X_prox, G_prox, t_prox;
	
	// Calculo de proximos valores
	I_prox = currentStates->I + param->h * ((-param->n * currentStates->I) + (param->tau * param->u));
	X_prox = currentStates->X + param->h * ((-param->p2 * currentStates->X) + (param->p3 * currentStates->I));
	G_prox = currentStates->G + param->h * (-(param->p1 + currentStates->X)*(currentStates->G) + param->p1 * param->Gb + m(currentStates->t, food));
	t_prox = currentStates->t + param->h;

	// Guardar en la estructura los valores calculados
	currentStates->t = t_prox;
	currentStates->I = I_prox;
	currentStates->G = G_prox;
	currentStates->X = X_prox;
};

// Solucionador de Runge Kutta 4

void rungeKutta4Solver(struct parameters *param, struct states *currentStates, struct food_parameters *food) {
	
	// Inicializacion de parametros de Runge Kutta Orden 4
	double a1;
	double b1;
	double c1;
	double t_1;
	double I_1;
	double X_1;
	double G_1;
	double a2;
	double b2;
	double c2;
	double t_2;
	double I_2;
	double X_2;
	double G_2;
	double a3;
	double b3;
	double c3;
	double t_3;
	double I_3;
	double X_3;
	double G_3;
	double a4;
	double b4;
	double c4;
	double t_prox;
	double I_prox;
	double X_prox;
	double G_prox;

	// Ecuaciones de Runge Kutta Orden 4
	a1 = (-param->n * currentStates->I) + (param->tau * param->u);
	b1 = (-param->p2 * currentStates->X) + (param->p3 * currentStates->I);
	c1 = -(param->p1 + currentStates->X)*currentStates->G + param->p1 * param->Gb + m(currentStates->t, food);

	t_1 = currentStates->t + (param->h / 2.0);
	I_1 = currentStates->I + (param->h / 2.0) * a1;
	X_1 = currentStates->X + (param->h / 2.0) * b1;
	G_1 = currentStates->G + (param->h / 2.0) * c1;
	a2 = (-param->n * I_1) + (param->tau * param->u);
	b2 = (-param->p2 * X_1) + (param->p3 * I_1);
	c2 = -(param->p1 + X_1)*currentStates->G + param->p1 * param->Gb + m(t_1, food);

	t_2 = currentStates->t + (param->h / 2.0);
	I_2 = currentStates->I + (param->h / 2.0) * a2;
	X_2 = currentStates->X + (param->h / 2.0) * b2;
	G_2 = currentStates->G + (param->h / 2.0) * c2;
	a3 = (-param->n * I_2) + (param->tau * param->u);
	b3 = (-param->p2 * X_2) + (param->p3 * I_2);
	c3 = -(param->p1 + X_2)*currentStates->G + param->p1 * param->Gb + m(t_2, food);

	t_3 = currentStates->t + param->h;
	I_3 = currentStates->I + param->h * a3;
	X_3 = currentStates->X + param->h * b3;
	G_3 = currentStates->G + param->h * c3;
	a4 = (-param->n * I_3) + (param->tau * param->u);
	b4 = (-param->p2 * X_3) + (param->p3 * I_3);
	c4 = -(param->p1 + X_3)*currentStates->G + param->p1 * param->Gb + m(t_3, food);

	t_prox = currentStates->t + param->h;
	I_prox = currentStates->I + (param->h / 6.0) * (a1 + 2.0 * a2 + 2.0 * a3 + a4);
	X_prox = currentStates->X + (param->h / 6.0) * (b1 + 2.0 * b2 + 2.0 * b3 + b4);
	G_prox = currentStates->G + (param->h / 6.0) * (c1 + 2.0 * c2 + 2.0 * c3 + c4);

	// Guardar en la estructura los valores calculados
	currentStates->t = t_prox;
	currentStates->I = I_prox;
	currentStates->G = G_prox;
	currentStates->X = X_prox;
};

int main() {

	// Estructuras 
	struct states currentStates;
	struct parameters param;
	struct food_parameters food;

    // Condiciones iniciales del modelo
	currentStates.I = 0.0;
	currentStates.X = 0.0;
	currentStates.G = 144.0;
	currentStates.t = 0.0;

	// Parámetros del paciente
	param.p1 = 0.0337;
	param.p2 = 0.0209;
	param.p3 = 7.5 * pow(10, -6);
	param.tau = 0.083333;
	param.n = 0.214;
	param.Gb = 144.0;
	param.h = 1.0;
	param.u = 48.2328;

	// Parámetros de una comida
	food.Dg = 40.0;
	food.Ag = 0.8;
	food.tmax_I = 55.0;
	food.tmax_G = 40.0;
	food.time_food = 200.0;
	food.Vg = 13.79;
	
	FILE *f = fopen("rk_c.csv", "w");
	if (f == NULL) return -1;
    
	for (int x = 0; x < 1501; x++) {
		fprintf(f, "%lf\n", currentStates.G);
		//eulerSolver(&param, &currentStates, &food);
		rungeKutta4Solver(&param, &currentStates, &food);
		};

	fclose(f);
	return 0;
};
