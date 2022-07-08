/* +++
Elabore um programa em C que receba o valor de n conforme anteriormente definido, calcule o
Número de Fibonacci correspondente e a sua fatoração. Considere que 0 ≤ n ≤ 100. Lembrando
que a fatoração de um número é a multiplicação de números primos que resulta no número
dado. 
*/

#include <stdio.h>

    void fat(long int n) {

        int fat = 2;
        int mult = 0;
        while (n > 1) {

            while(n % fat == 0) {

                if( mult == 0 ) {
                printf("%d", fat);
                mult++;
                } else {
                printf(" %d", fat);
                }

                n /= fat;
            }

            fat++;
        }

    }

    long int fibonacci(long int n) {

        long int fib1 = 1, fib2 = 1;
        long int i = 0, sum;

        for(i=2; i<n; i++) {
            sum = fib1 + fib2;
            fib1 = fib2;
            fib2 = sum;
        }

        return(fib2);
    }

    int main() {

        long int n, nn;
        int i = 0,   detect = 0;

        scanf("%lu", &n);

        if(n >= 3 && n <= 100){

        nn = fibonacci(n);
        printf("%lu\n", nn);
        fat(nn);
        }else{printf("erro\n"); return 0;}

        return 0;
    }