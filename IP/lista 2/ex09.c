#include <stdio.h>

int converteEmNotasMoedas (int n, int n100, int n50, int n10, int n1) {

    n50 = 0, n10 = 0, n1 = 0;

    n1 = n;

    n100 = n1 / 100;
    n1 = n1 - (n100*100);

    n50 = n1 / 50;
    n1 = n1 - (n50*50);

    n10 = n1 / 10;
    n1 = n1 - (n10*10);


    printf("NOTAS DE 100 = %d\n", n100); 
    printf("NOTAS DE 50 = %d\n", n50); 
    printf("NOTAS DE 10 = %d\n", n10); 
    printf("MOEDAS DE 1 = %d\n", n1); 
    return n100, n50, n10, n1;
}


int main() {

    int n, n100, n50, n10, n1;

    scanf("%d", &n);

    converteEmNotasMoedas(n, n100, n50, n10, n1);


    return 0;
}