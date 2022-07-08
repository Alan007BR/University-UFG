#include <stdio.h>

int main() {

    int n, cont = 1;
    int fator;


        scanf("%d", &n);
    while (n <= 1) {

        printf("Fatoracao nao e possivel para o numero %d!\n", n);
        scanf("%d", &n);
    }
    printf("%d = ", n);
    fator = 2;
    while (n > 1) {
        while ( n % fator == 0) {
            n /= fator;
            printf("%d", fator);
                if ( n > 1) {
                    printf(" x ");
                }
        }
        fator++;
    }
    printf("\n");


    return 0;
}