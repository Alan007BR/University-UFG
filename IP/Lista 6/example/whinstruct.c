#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[10];
    int idade;
    char sexo;
} Pessoa;

int main() {

    Pessoa p = {"Joao", 20, 'M'};
    Pessoa p2 = {.sexo = 'F', .idade = 19, .nome = "Maria"};

    memset(p.nome, 0, 10);
    memset(p2.nome, 0, 10);

    strcpy(p.nome, "Joao");
    strcpy(p.nome, "Maria");


    FILE *arq = NULL;
    arq = fopen("struct.bin", "wb");

    fwrite(&p, sizeof(Pessoa), 1, arq);

    fclose(arq);
    return 0;
}