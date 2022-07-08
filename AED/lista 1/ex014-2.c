#include <stdio.h>

int fat(int n) {

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

        printf("\n");

}

int fibonacci(int n) {

        int fib1 = 1, fib2 = 1;
        int i = 0, sum;

        for(i=2; i<n; i++) {
            sum = fib1 + fib2;
            fib1 = fib2;
            fib2 = sum;
        }

        return(fib2);
} 

int main() {

    int n;
    int fibo;

    scanf("%d", &n);
    if(n < 3 || n > 100) {  printf("erro"); return 0;}

    fibo = fibonacci(n + 1);

    printf("%d\n", fibo);

    fat(fibo);

    return 0;
}