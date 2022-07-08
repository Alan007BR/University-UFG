/*
Questao 07:
    Escreva um programa que leia os tres numeros complexos salvos no arquivo da questao 6
    usando a estrutura Complex e os apresente na tela.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double r;
    double i;
} Complex;

int main() {
    FILE* arq = NULL;
    Complex n;

    arq = fopen("complex", "rb");

    if (arq == NULL) {

        printf("Error: nao foi possivel ler o arquivo!\n");
    } else {
        
        while (fread(&n, sizeof(Complex), 1, arq)) {

            printf("%.2lf + i%.2lf\n", n.r, n.i);
            if (feof(arq)) break;
        }

        fclose(arq);
    }

    return 0;
}