#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 1000000
#define SUCESSO 1
#define FALHA 0
#define TRUE 1
#define FALSE 0
#define CRESCENTE 1
#define DECRESCENTE 0

typedef struct {
    int tam;
    int num[MAX];
    
} Conjunto;

    Conjunto *criaConjunto    ();
    //int criaConjunto            (Conjunto *C);
    int conjuntoVazio           (Conjunto *C);
    int insereElementoConjunto  (int x, Conjunto *C);
    int excluirElementoConjunto (int x, Conjunto *C);
    int tamanhoConjunto         (Conjunto *C);
    int maior                   (int x, Conjunto *C);
    int menor                   (int x, Conjunto *C);
    int pertenceConjunto        (int x, Conjunto *C);
    int conjuntosIdenticos      (Conjunto *C1, Conjunto *C2);
    int subconjunto             (Conjunto *C1, Conjunto *C2);
    Conjunto *complemento        (Conjunto *C1, Conjunto *C2);
    Conjunto *uniao              (Conjunto *C1, Conjunto *C2);
    Conjunto *interseccao        (Conjunto *C1, Conjunto *C2);
    Conjunto *diferenca          (Conjunto *C1, Conjunto *C2);
    Conjunto *conjuntoPartes     (Conjunto *C);
    void mostraConjunto         (Conjunto *C, char * ordem);
    int copiarConjunto          (Conjunto *C1, Conjunto *C2);
    int destroiConjunto         (Conjunto *C);
    void liberar                (Conjunto *C);