#include <stdio.h>
#include <math.h>



int calcularFatorial(int numero) {

	int fatorial = 1;


	while (numero > 1) {
		fatorial *= numero;
		numero--;
	}

	return fatorial;
}

double cossenoSerieTaylor(double radianos, int n) {

	int i;
	double somatorio = 0.00;


	for (i = 0; i <= n; i++) {
		somatorio += ((pow(-1, i) * pow(radianos, 2 * i))/calcularFatorial(2 * i));
	}	

	return somatorio;
}


int main() {

	double x = 0.00;
	int n = 0;
	double cosseno = 0.00;

	scanf("%lf", &x);
	scanf("%d", &n);

	cosseno = cossenoSerieTaylor(x, n);

	printf("cos(%.2lf) = %.6lf\n", x, cosseno);

	return 0;
}