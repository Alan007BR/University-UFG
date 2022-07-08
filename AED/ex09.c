/* +
soma dos seus divisores (exceto o próprio número) é igual a ele mesmo. Exemplo: 28 =
Elabore um programa na linguagem C para verificar se um número é perfeito, ou seja, se a
1+2+4+7+14
*/

#include <stdio.h>

int main() {

    int n;
    long int nums = 0;
    int i = 0;

    scanf("%d", &n);

    if(n < 1) { printf("erro"); return 0; }

    for (i = 1; i <= n/2; i++){

        if(n % i == 0){
            nums += i;
        }
    }

    nums == n ? printf("perfeito\n", n) : printf("imperfeito\n", n);

    return 0;
}