/*
Questao 06:
    Escreva um programa que leia, via teclado, tres numeros complexos, organizados em uma
    estrutura chamada Complex, e os salve as estruturas em um arquivo em modo BINARIO.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double r;
    double i;
} Complex;

int main() {
    FILE* arq = NULL;
    Complex numero;
    int i;

    arq = fopen("complex", "wb");

    if (arq == NULL) {
        printf("Error: nao foi possivel criar o arquivo.\n");
    } else {
        for (i = 0; i < 3; i++) {
            //deixei dessa forma ([a + ib]) para ficar apresentável, não sabia ao certo como você iria preferir.
            printf("Informe o %d.o numero complexo [a + ib]: ", (i + 1));
            scanf("%lf + i%lf", &numero.r, &numero.i);
            fwrite(&numero, sizeof(Complex), 1, arq);
        }

        fclose(arq);
    }   

    return 0;
}