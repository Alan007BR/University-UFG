#include <stdio.h>

int main() {
    int num = 0, pares = 0, impares = 0, contpares = 0, contimpares = 0;
    double mediapar, mediaimpar;

    scanf("%d", &num);

    while (num != 0) {
        if (num % 2 == 0) {
            pares += num;
            contpares++;
        }
            else {
            impares += num;
            contimpares++;
        }
        scanf("%d", &num);
    }

    if (contpares != 0) {
        mediapar =  (double) pares / contpares;
    }
        printf("MEDIA PAR: %lf\n", mediapar);


    if (contimpares != 0) {
        mediaimpar = (double) impares / contimpares;
    }
        printf("MEDIA IMPAR: %lf\n", mediaimpar);


    return 0;
}