/* (++)
Pode-se definir uma função f ̈(n), fatorial duplo de n, com n ∈ N, como sendo o produto de todos os
números naturais ímpares de 1 até n, inclusive este, quando ele é ímpar. Assim, por exemplo, tem-se que:
f ̈(1) = 1
f ̈(2) = 1
f ̈(3) = 3
f ̈(5) = 15
Você deve escrever uma função recursiva, em C, que seja capaz de, recebendo n, imprimir o valor de
f ̈(n).
*/
long int dfat(long int n) {

    if(n == 0 || n == 1) return 1;
    if(n % 2 != 0) return n * dfat(n-2);

    else return dfat(n-1);
}

#include <stdio.h>


int main(){

    long int n;

    scanf("%lu",&n);
    if(n > 100 && n < 1) return 0;
    printf("%lu", dfat(n));

    return 0;
}