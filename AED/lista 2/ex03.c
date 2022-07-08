/* ex03 (++)

Escreva um programa, em C, que receba um número natural n N, representado utilizando a notação
decimal, e o converta para sua notação binária. O programa deve utilizar uma “função recursiva” para
realizar a conversão
*/

#include <stdio.h>

int convert(int n) {

    if (n == 0 || n == 1)
        printf("%d", n);
    else {
        convert(n / 2);
        printf("%d", n % 2);
    }
}

int main() {

    int n, num;

    scanf("%d", &n);

    while(n--){
    scanf("%d", &num);
    convert(num);
    printf("\n");
    }
    
    return 0;
}