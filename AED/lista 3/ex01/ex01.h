#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int tam;
    int num[MAX];
} Conjunto;

    int criaConjunto();
    int conjuntoVazio(C);
    int insereElementoConjunto(x, C);
    int excluirElementoConjunto(x, C);
    int tamanhoConjunto(C);
    int maior(x, C);
    int menor(x, C);
    int pertenceConjunto(x, C);
    int conjuntosIdenticos(C1, C2);
    int subconjunto(C1, C2);
    Conjunto complemento(C1, C2);
    Conjunto uniao(C1, C2);
    Conjunto interseccao(C1, C2);
    Conjunto diferenca(C1, C2);
    Conjunto conjuntoPartes(C);
    void mostraConjunto(C, ordem);
    int copiarConjunto(C1, C2);
    int destroiConjunto(C);