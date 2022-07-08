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

double calcularEulerTaylor(double expoente, int qtd_termos) {

	int i;
	double somatorio = 0.00;


	for (i = 0; i <= qtd_termos; i++) {
		somatorio += pow(expoente, i)/calcularFatorial(i);
	}

	return somatorio;
}




int main() {

	double expoente = 0.00;
	int qtd_termos = 0;
	double resultado = 0.00;


	scanf("%lf", &expoente);
	scanf("%d", &qtd_termos);


	resultado = calcularEulerTaylor(expoente, qtd_termos);


	printf("e^%.2lf = %.6lf\n", expoente, resultado);

	return 0;
}