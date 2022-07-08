#include <stdio.h>

int main() {

    int n, sum = 0;
    int cont = 1;

    scanf("%d", &n);
    printf("%d = ", n);

    if (n <= 0) {
        return 0;
    }

    for (cont = 1; cont <= n/2; cont++) {

        if (n % cont == 0) {
           

        if (cont == 1) {
        printf("%d", cont);
        } else {

        printf(" + %d", cont);
        }
        sum = sum + cont;
        }
        

    }
        printf(" = %d", sum);

        if (sum == n) {
            printf(" (NUMERO PERFEITO)");
        } else {
            printf(" (NUMERO NAO E PERFEITO)");
        }

    return 0;
}