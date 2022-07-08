#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *arq = NULL;
    long int numero = 0;
    //long int pois os valores são altos de mais para um valor int normal

    arq = fopen("abc", "wb");

    if (arq == NULL) {
        printf("Error: nao foi possivel criar o arquivo.\n");
    } else {
        for (numero = 1629495328; numero <= 1629495330; numero++) {
            fwrite(&numero, sizeof(long int), 1, arq);
        }
        fclose(arq);
    }

    /* 
    Hello teacher.

    O resultado são os bytes armazenados no arquivo binário
    como se trata de um long int em um sistema 64bits, então cada número
    vai ter 8 bytes.
    */

    return 0;
}