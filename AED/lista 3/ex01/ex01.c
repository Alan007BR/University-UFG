//==============================================================================
// Arquivo ponto.h
//==============================================================================
//
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int tam;
    int num[MAX];
} Conjunto;

    int *criaConjunto();
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
//==============================================================================
// Arquivo ponto.c
//==============================================================================
//
// SUCESSO = 1; FALHA = 0;
#include <limits.h>
#include <stdio.h>

int main(){

    unsigned int choice;
    Conjunto *C;    

    scanf("%d",&choice);

    switch (choice) {
    case 1:
        printf("",criaConjunto(C) == 1 ? printf("conjunto criado com sucesso.\n") : printf("falha ao criar o conjunto.\n"));
        break;
    case 2:
        criaConjunto();
        break;
    case 3:
        criaConjunto();
        break;
    case 4:
        criaConjunto();
        break;
    case 5:
        criaConjunto();
        break;
    case 6:
        criaConjunto();
        break;
    case 7:
        criaConjunto();
        break;
    case 8:
        criaConjunto();
        break;
    case 9:
        criaConjunto();
        break;
    case 10:
        criaConjunto();
        break;
    case 11:
        criaConjunto();
        break;
    case 12:
        criaConjunto();
        break;
    case 13:
        criaConjunto();
        break;
    case 14:
        criaConjunto();
        break;
    case 15:
        criaConjunto();
        break;
    case 16:
        criaConjunto();
        break;
    case 17:
        criaConjunto();
        break;
    case 18:
        criaConjunto();
        break;
    
    default:
        printf("operacao inexistente, verifique a ortografia.\n"); return 0;
        break;
    }    


    liberar(C);
    return 0;
}

int *criaConjunto(Conjunto *C) {

    C = (Conjunto *)malloc(sizeof(Conjunto));
    C->tam = 0;

    return 1;
}

void liberar(Conjunto const *C) {
    free(C->tam);
    free(C->num);
    free((Conjunto *)C);
}