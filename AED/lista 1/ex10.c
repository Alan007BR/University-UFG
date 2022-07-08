/* +
Elabore um programa na linguagem C para verificar se um determinado número inteiro
positivo é primo.
*/
#include <stdio.h>

int main() {

    int n, i = 2;
    int flag = 0;


    scanf("%d", &n);

    if (n < 1) { printf("erro\n"); return 0; }

    for (i = 2; i <= n / 2; i++) {
        if(n % i == 0) {
            flag++;
            break;
        }
    }
    if( n == 2 || n == 1) {
        printf("nao\n"); return 0;
    }
    if(flag == 0) {
        printf("primo\n", n);
    } else {
        printf("nao\n", n);
    }


    return 0;
}