#include <stdio.h>

int main() {

    float x1, x2;

    scanf("%f %f", &x1, &x2);

       if (x1 > 5 || x1 < -5 || x2 > 5 || x2 < -5) {
        printf("POSICOES: %.2f e %.2f  (FORA DO EXPERIMENTO)\n", x1, x2);

    } 


    return 0;
}