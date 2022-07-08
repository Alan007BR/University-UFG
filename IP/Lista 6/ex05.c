/*
Questao 05:
    Escreva um programa que abra o arquivo "abc" gerado pela questao 4 e imprima em cada linha
    da tela o simbolo e codigo dos caracteres que compoem o texto.
*/
#include <stdio.h>

int main() {
    FILE* arq = NULL;
    char c;

    arq = fopen("abc", "r");

    if (arq == NULL) {
        printf("Error: nao possivel abrir o arquivo para leitura.\n");
    } else {
        while (fscanf(arq, "%c", &c) != EOF) {
            printf("%c = %d\n", c, c);
        }

        fclose (arq);
    }

    return 0;
}