#include <stdio.h>

int somaDivisores(int numero) {

	int i;
	int soma = 1;


	for (i = 2; i <= (numero/2); i++) {
		if (numero % i == 0)
			soma += i;
	}

	return soma;
}


int main() {

	int qtd_numeros_amigos = 0, i = 0;
	int numero = 1;
	int soma_divisores = 0;


	scanf("%d", &qtd_numeros_amigos);


	while (1) {
		soma_divisores = somaDivisores(numero);

		if ((somaDivisores(soma_divisores) == numero) && (soma_divisores > numero)) {
			printf("(%d,%d)\n", numero, soma_divisores);
			i++;
		}

		if (i == qtd_numeros_amigos)
			break;

		numero++;
	}

	return 0;
}