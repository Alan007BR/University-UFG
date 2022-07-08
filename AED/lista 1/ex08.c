/* (+) 
Elabore um programa na linguagem C para ler dois números inteiros e calcular o máximo
divisor comum desses números.
*/

#include <stdio.h>

    int mdc(long int m, long int n) {
        if(n == 0) return m;

        return mdc(n, m % n );
    }

int main() {

    int n1, n2;

    scanf("%d %d", &n1, &n2);
    printf("%d\n", mdc(n1, n2));

    return 0;
}