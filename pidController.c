#include "pidController.h"

double pidController(struct pid_param *params, struct pid_calc *calc)
{
	double ctrlsig_u;

	// Calculo de valores actuales
	calc->proportional = params->Kp * (params->beta * calc->setpoint - calc->procout);
	calc->der_term = (params->alpha * params->Td) / (params->alpha * params->Td + params->Ts);
	calc->derivative = calc->der_term * calc->past_derivative - calc->der_term * (calc->procout - calc->past_procout);
	calc->ctrlsignal_u = 48.2328 + calc->proportional + calc->integral + calc->derivative; // salida del controlador

    // Calculo de valores anteriores
	calc->past_derivative = calc->derivative;
	calc->past_setpoint = calc->setpoint;
	calc->past_procout = calc->procout;
	calc->integral = calc->next_integral;

	// Calculo de valores siguientes
	calc->int_term = params->Ts * params->Kp / params->Ti;
	calc->next_integral = calc->integral + calc->int_term * (calc->setpoint - calc->procout);

	ctrlsig_u = calc->ctrlsignal_u;
	return ctrlsig_u;

};

int main() {

	// Abrir archivo para guardar los datos
	FILE *f = fopen("pid_glucose.csv", "w");
	if (f == NULL) return -1;

	// Crear e inicializar estructuras de parametros y calculos
	struct pid_param params = { 0 };
	struct pid_calc calc = { 0 };

	params.Ts = 1;
	params.Kp = -1.228;
	params.Ti = 81.26;
	params.Td = 19.5;
	params.beta = 1;
	params.alpha = 0.01;

	calc.past_procout = 120.0;
	calc.setpoint = calc.past_setpoint = 120.0;

	// Otras variables 
	double glucose_pid_20[] = {120, 120.0047, ...}
	int counter = 0;
	double g;
	double ctrlsig_u;
	double integral;

	// Loop de 2000 minutos
	while (counter < 1501) {
		g = glucose_pid_20[counter];
		calc.procout = g;
		ctrlsig_u = pidController(&params, &calc);
		fprintf(f, "%lf\n", calc.procout);
		counter++;
	};

	return 0;
}
