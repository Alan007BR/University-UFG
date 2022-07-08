#include <stdio.h>

int main() {

    int n1, n2, n3;
    int c;

    //printf("Digite o primeiro numero inteiro: ");
    scanf("%i", &n1);

    //printf("Digite o primeiro numero inteiro: ");
    scanf("%i", &n2);

    //printf("Digite o primeiro numero inteiro: ");
    scanf("%i", &n3);

            if(n1>9 || n2>9 || n3>9 || n1 <0 || n2 < 0 || n3 < 0 ){

                printf("DIGITO INVALIDO");

            } else {
                
                c = n1*100 + n2*10 + n3;
                printf("%d, %d\n", c, c*c);
            }

    return 0;
}