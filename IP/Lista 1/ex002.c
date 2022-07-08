#include <stdio.h>

int main() {

    float tempF;
    float polegada;
    float tempC;
    float mm;

   // printf("\n================================\n");
    //printf("Digite a temperatura em Fahrenheit: ");
    scanf("%f", &tempF);

   // printf("Digite a quantidade de chua por polegada: ");
    scanf("%f", &polegada);

    tempC = (5*(tempF - 32))/9;

    mm = polegada * 25.4;

    printf("O VALOR EM CELSIUS = %.2f\n", tempC);
    printf("A QUANTIDADE DE CHUVA E = %.2f\n", mm);


    return 0;
}