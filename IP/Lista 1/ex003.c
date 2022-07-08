#include <stdio.h>


int main() {

    float a, b, c, delta;

    //printf("Digite o valor de A: ");
    scanf("%f", &a);

    //printf("Digite o valor de B: ");
    scanf("%f", &b);

    //printf("Digite o valor de C: ");
    scanf("%f", &c);

    delta = b*b - 4 * a*c;

    printf("O VALOR DE DELTA E = %.2f", delta);

    return 0;
}