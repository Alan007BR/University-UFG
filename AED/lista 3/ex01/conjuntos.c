#include <stdio.h>
#include <stdlib.h>
#include "conjuntos.h"

    Conjunto *criaConjunto() {

        Conjunto *C = (Conjunto *)malloc(sizeof(Conjunto));
        C->tam = 0;

        if(C == NULL) return 0;

        return C;
    }

    int conjuntoVazio(Conjunto *C) {
        if(C == NULL){ printf("Error: esse conjunto nao existe.\n"); return 0;}
        else {
        printf("verificando...\n");
        if(C->tam == 0) return 1;
        else return 0;
        }

    }

    int insereElementoConjunto(int x, Conjunto *C) {
        printf("inserindo elemento...\n");
        C->num[C->tam++] = x;
        return 1;

    }

    void liberar(Conjunto *C) {
        int i = 0;
        free(C->num);
        free(C);
    }

    int excluirElementoConjunto (int x, Conjunto *C) {
        int finded = 0;
        int i = 0, j = 0;

        finded = search(x, C);

        if(C->num[finded] != x){ printf("nao encontrado\n"); return 0;}
        else {
            printf("encontrado\n");

            //refazer o vetor só que excluindo o elemento que vamos remover
            for(i = 0; i < C->tam && C->num[i] != x; i++) {
                printf("%d--", C->num[i]);
            for(i++; i < C->tam; i++) {
                C->num[i-1] = C->num[i];
            }
            }
        }

            C->tam--;
    }

    int maior(int x, Conjunto *C){
        int i = 0;
        int m = 0;

        for(i = 0; i < C->tam; i++){
            if(C->num[i] > x){
                m++;
            }
        }

        return m;
    }
    int menor(int x, Conjunto *C){
        int i = 0;
        int m = 0;

        for(i = 0; i < C->tam; i++){
            if(C->num[i] < x){
                m++;
            }
        }

        return m;
    }

    int pertenceConjunto(int x, Conjunto *C){
        int i = 0;

        for(i = 0; i < C->tam; i++){
            if(C->num[i] == x) {
                return 1;
            }
        }

        return 0;
    }

    int tamanhoConjunto(Conjunto *C){

        return C->tam;
    }
    void mostraConjunto(Conjunto *C, char ordem){

        if(C == NULL) {
            printf("Conjunto inexistente"); return 0;
        }
        if(C->tam == 0){
            printf("o conjunto esta vazio"); return 0;
        }
        int i = 0, j = 0;
            //provisorio, so pra mostrar mesmo
            for(i = 0; i < C->tam; i++){
                printf(" [%d] -", C->num[i]);
            }

        printf("\n");
    }

    conjuntosIdenticos(Conjunto *C, Conjunto *C2){
        if(C == NULL || C2 == NULL){
            printf("Conjunto inexistente"); return 0;
        }

        int i = 0, j = 0, flag = 0;
        if(C->tam == C2->tam){
            
            for(i = 0; i < C->tam; i++){
                if(C->num[i] != C2->num[i]){
                    flag++;
                }
            }

        }

        if(flag == 0){
            return 0;
        } else {return 1;}
    }

//AUXILIARES
int search(int x, Conjunto *C){ 
    int i = 0;

    for(i = 0; i < C->tam; i++){
        if(C->num[i] == x) return i;
    }

    return 0;
}
