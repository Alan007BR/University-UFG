/* (+)

Todo número natural estritamente positivo n N∗ possui um número reverso correspondente.
Por exemplo, considere que n seja escrito da seguinte maneira:
n = dkdk−1dk−2 · · · d2d1d0
onde k ∈ N∗ corresponde ao número de dígitos significativos que formam n, ou seja, dk ∈ {1, 2, 3, . . . , 9} e
di ∈ {0, 1, 2, . . . , 9}, com 0 ≤ i < k.
O número reverso de n é nr = dldl−1dl−2 · · · dk−2dk−1dk, sendo dl o primeiro dígito não nulo, tomados nesta
ordem, dentre dkdk−1dk−2 . . . d2d1d0 do número original n.

Escreva um programa em C usando recursividade que seja capaz de determinar o número reverso de um
certo número natural estritamente positivo n fornecido como entrada.
*/

#include <stdio.h>


int reverse(int n) {

    static rN = 0;
    if(n == 0) return 0;

    rN = rN * 10 + n % 10;
    reverse(n/10);

    return rN;
}

int main(){

    int n;

    scanf("%d",&n);
    printf("%d\n", reverse(n));

    return 0;
}