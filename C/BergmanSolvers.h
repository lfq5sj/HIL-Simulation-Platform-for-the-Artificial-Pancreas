#ifndef __EULER_SOLVER_H
#define __EULER_SOLVER_H

// Estados del modelo mínimo de Bergman
struct states {
	double G;
	double I;
	double X;
	double t;
};

// Parametros del modelo mínimo de Bergman
struct parameters {
	double p1;
	double p2;
	double p3;
	double tau;
	double n;
	double Gb;
	double u;
	double h;
};

// Parametros de la función de comida
struct food_parameters {
	double Dg;
	double Ag;
	double tmax_I;
	double tmax_G;
	double time_food;
	double Vg;

};

// Funciones 

double m(float t, struct food_parameters *food);
void eulerSolver(struct parameters *param, struct states *currentStates, struct food_parameters *food);
void rungeKutta4Solver(struct parameters *param, struct states *currentStates, struct food_parameters *food);

#endif
