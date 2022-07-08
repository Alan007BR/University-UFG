#include <stdio.h>

int main() {

    float a, b, c, d, m;

    //printf("Primeiro valor da matriz: ");
    scanf("%f", &a);

    //printf("Primeiro valor da matriz: ");
    scanf("%f", &b);

    //printf("Primeiro valor da matriz: ");
    scanf("%f", &c);

    //printf("Primeiro valor da matriz: ");
    scanf("%f", &d);

    m = (a * d) - (b * c);

    printf("O VALOR DO DETERMINANTE E = %.2f", m);

    return 0;
}