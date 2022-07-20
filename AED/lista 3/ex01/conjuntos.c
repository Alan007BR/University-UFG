#include <stdio.h>
#include <stdlib.h>
#include "conjuntos.h"


//AUXILIARES
int searchInVetor(int x, Conjunto *C){ 
    int i = 0;

    for(i = 0; i < C->tam; i++){
        if(C->num[i] == x) return i;
    }

    return 0;
}

void liberar(Conjunto *C) {
    free(C);
}


    Conjunto *criaConjunto() {

        Conjunto *C = (Conjunto *)malloc(sizeof(Conjunto));
        C->tam = 0;

        if(C == NULL) return 0;

        return C;
    }

    // int criaConjunto(Conjunto *C) {
    //     C = (Conjunto *)malloc(sizeof(Conjunto));
    //     C->tam = 0;
    //     //(*C)->tam = dec->tam;
    //     //(*C) = (Conjunto *)malloc(sizeof(Conjunto));
    //     //C->tam = 0;

    //     return SUCESSO;
    // }

    int conjuntoVazio(Conjunto *C) {
        if(C == NULL){ printf("Error: esse conjunto nao existe.\n"); return FALHA;}
        else {
        printf("verificando...\n");
        if(C->tam == 0) return SUCESSO;
        else return FALHA;
        }
    }

    int insereElementoConjunto(int x, Conjunto *C) {
        C->num[C->tam++] = x;
        return 1;
    }

    int excluirElementoConjunto (int x, Conjunto *C) {
        int finded = 0;
        int i = 0, j = 0;

        finded = searchInVetor(x, C);

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

    int conjuntosIdenticos(Conjunto *C, Conjunto *C2){
        if(C == NULL || C2 == NULL){
            printf("Conjunto inexistente\n"); return 0;
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

    int subconjunto(Conjunto *C1, Conjunto *C2){
        int i = 0, j = 0, flag = 0;

        if(C1->tam > C2->tam){
            return FALSE;
        }
        for(i = 0; i < C1->tam; i++){
            for(j = 0; j < C2->tam; j++){
                if(C1->num[i] == C2->num[j]){
                    flag++;
                }
            }

            if(flag == 0){return FALSE;} else{flag = 0;}
        }

        return TRUE;
    }

    Conjunto *complemento(Conjunto *C1, Conjunto *C2){

        Conjunto *result = criaConjunto();
        int check;
        int flag = 0;
        int i = 0;
        
            for(i = 0; i < C2->tam; i++){
            check = searchInVetor(C2->num[i], C1);
            if(check == 0){
                printf("%d\n", C2->num[i]);
                insereElementoConjunto(C2->num[i], result);  
                }
            }

        return result;
    }
    Conjunto *uniao(Conjunto *C1, Conjunto *C2){
        Conjunto *resul = criaConjunto();
        int check;
        int flag = 0;
        int i = 0;

            for(i = 0; i < C1->tam; i++){
                insereElementoConjunto(C1->num[i], resul);
            }
            for(i = 0; i < C2->tam; i++){
                check = searchInVetor(C2->num[i], resul);
                if(check == 0){
                insereElementoConjunto(C2->num[i], resul);
                }
            }

        return resul;
    }

    Conjunto *interseccao(Conjunto *C1, Conjunto *C2){
        Conjunto *resul = criaConjunto();
        int check;
        int flag = 0;
        int i = 0;

        // if(C1->tam >= C2->tam) {
        //     for(i = 0; i < C1->tam; i++){
        //         check = searchInVetor(C1->num[i], C2);
        //         if(check != 0){
        //             insereElementoConjunto(C1->num[i], resul);
        //         }
        //     }
        // }

        //if(C2->tam > C1->tam){
            printf("c1: %d ", C1->num[0]);
            printf("c2: %d\n", C2->num[0]);
            if(C1->num[0] == C2->num[0]){
                insereElementoConjunto(C1->num[i], resul);  
            }

            for(i = 1; i < C2->tam; i++){
                check = searchInVetor(C2->num[i], C1);
                if(check != 0){
                    insereElementoConjunto(C2->num[i], resul);
                }
            }
       // }

        return resul;
    }

    Conjunto *diferenca(Conjunto *C1, Conjunto *C2){

        Conjunto *result = criaConjunto();
        int check = 0;
        int flag = 0;
        int i = 0;
            
            for(i = 0; i < C1->tam; i++){

            check = searchInVetor(C1->num[i], C2);
            if(check == 0){
                insereElementoConjunto(C1->num[i], result);  
                }
            }

        return result;
    }


    void mostraConjunto(Conjunto *C, char *ordem){

        if(C == NULL) {
            printf("Conjunto inexistente\n");
            exit(0);
        }
        if(C->tam == 0){
            printf("o conjunto esta vazio\n");
            exit(0);
        }
        int i = 0;

            for(i = 0; i < C->tam; i++){
                printf("[%d] - ", C->num[i]);
            }

        printf("\n");
    }

    int destroiConjunto(Conjunto *C){
        if(C != NULL){
            free(C);
        }

        if(C == NULL){
            return SUCESSO;
        }else{
            return FALHA;
        }
    }