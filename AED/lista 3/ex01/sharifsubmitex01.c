//
// Arquivo conjuntos.h
//
#include <stdio.h>
#include <stdlib.h>
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

//
//  Arquivo conjuntos.c
//

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

        if(C->num[finded] != x){ return FALHA;}
        else {
            //refazer o vetor só que excluindo o elemento que vamos remover
            for(i = 0; i < C->tam && C->num[i] != x; i++); 
                for(i++; i < C->tam; i++) {
                    C->num[i-1] = C->num[i];
                }
        }
            C->tam--;
            return SUCESSO;
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

        return resul;
    }

    Conjunto *diferenca(Conjunto *C1, Conjunto *C2){

        Conjunto *result = criaConjunto();
        int check = 0;
        int flag = 0;
        int i = 0, j = 0;
            
            for(i = 0; i < C1->tam; i++){
                for(j = 0; j < C2->tam; j++){
                    if(C1->num[i] == C2->num[j]){
                        flag++;
                    }
                }
                if(flag == 0){
                insereElementoConjunto(C1->num[i], result);  
                }
            flag = 0;
            }

        return result;
    }

    Conjunto *conjuntoPartes(Conjunto *C){
        int i = 0;
        int numCombTot = 1;
        int comb;
        int buffer_int;

        for(i = 0; i < C->tam; i++){
            numCombTot *= 2;
        }
        printf("\n");
        for(comb = 0; comb < numCombTot; comb++){
            buffer_int = comb;
        printf(" [");
            for(i = 0; i < C->tam; i++){
                if(buffer_int % 2 == 1){
                    printf(" %d ", C->num[i]);
                }
                buffer_int /= 2;
            }
        printf("] ");

        if(comb % 2 == 0){
            printf("\n");
        }
        }
        printf("\n");
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
        int j = 0;
        int aux;

        if(ordem == "C"){
            for(i = C->tam - 1; i > 0; i--){
                for(j = 0; j < i; j++){
                    if(C->num[j] > C->num[j + 1]){
                        aux = C->num[j];
                        C->num[j] = C->num[j + 1];
                        C->num[j + 1] = aux;
                    }
                }
            }
        }

        if(ordem == "D"){
            for(i = C->tam - 1; i > 0; i--){
                for(j = 0; j < i; j++){
                    if(C->num[j] < C->num[j + 1]){
                        aux = C->num[j];
                        C->num[j] = C->num[j + 1];
                        C->num[j + 1] = aux;
                    }
                }
            }
        }

            for(i = 0; i < C->tam; i++){
                printf("  [%d]  ", C->num[i]);

                if(i % 6 == 0 && i != 0){
                    printf("\n");
                }
            }

        printf("\n");
    }

    int copiarConjunto(Conjunto *C1, Conjunto *C2){
        int i = 0;
        int check;
        check = C2->tam;

        for(i = 0; i < C1->tam; i++){
            insereElementoConjunto(C1->num[i], C2);
        }
        if(C2->tam > check){
        return SUCESSO;

        }else{
            return FALHA;
        }
    }


    int destroiConjunto(Conjunto *C){
        if(C != NULL){
            free(C);

            return SUCESSO;
        }
            return FALHA;
    }

//
// Corpo principal (main.c)
//
void menu(int choice) {
    printf("\n");
    printf("1 -  Criar um conjunto vazio\n");
    printf("2 -  Verifica se o conjunto e vazio\n");
    printf("3 -  Insere um numero no conjunto\n");
    printf("4 -  Excluir elemento do conjunto\n");
    printf("5 -  Tamanho do conjunto\n");
    printf("6 -  Maiores que X do conjunto\n");
    printf("7 -  Menores que X do conjunto\n");
    printf("8 -  Verifica se o elemento X pertence ao conjunto\n");
    printf("9 -  Verificar se os conjuntos sao identicos\n");
    printf("10 - Subconjunto\n");
    printf("11 - Complemento de C1 e C2 \n");
    printf("12 - Uniao de C1 e C2\n");
    printf("13 - Interseccao do conjunto C1 com C2\n");
    printf("14 - Diferenca\n");
    printf("15 - Mostrar conjunto das partes\n");
    printf("16 - Monstrar conjunto em ordem Crescente - 'C' ou decrescente - 'D' \n");
    printf("17 - Copiar conjunto de C1 para C2\n");
    printf("18 - destruir(liberar) Conjunto\n");

    printf("\n");
}

int main(){

    unsigned int choice;
    int x, check, aux, i = 0;
    char ordem[2] = "AN";
    Conjunto *C;
    Conjunto *C2;
    Conjunto *C3;

    while(1) {
        menu(choice);
        scanf("%d",&choice);    
        
            switch (choice) {
            case 1:
                C = criaConjunto();
                C2 = criaConjunto(); 
                //C = criaConjunto(C) == SUCESSO ? printf("Conjunto Criado\n") : printf("O Conjunto nao foi criado\n");
                C == NULL ? printf("FALHA: O conjunto nao foi criado\n") : printf("SUCESSO: Conjunto criado\n");
                break;
            case 2:
                conjuntoVazio(C) == 1 ? printf("conjunto vazio.\n") : printf("conjunto nao-vazio.\n");
                break;
            case 3:
                scanf("%d",&x);
                check = insereElementoConjunto(x, C);
                check == 1 ? printf("SUCESSO: Elemento Adicionado\n") : printf("FALHA: O elemento nao foi adicionado por alguma razao");
                printf("conjunto 2: \n");
                break;
            case 4:
                scanf("%d",&x);
                excluirElementoConjunto(x, C) == FALHA ? printf("FALHA: numero nao encontrado\n") : printf("elemento encontrado e retirado\n");
                mostraConjunto(C, ordem);
                break;
            case 5:
                printf("cardinalidade: %d", tamanhoConjunto(C));
                break;
            case 6:
                scanf("%d",&x);
                check = maior(x, C);
                check == 0 ? printf("todos os elementos do conjunto sao maiores que %d", check) : printf("existem %d maiores do que %d\n", check, x);
                break;
            case 7:
                scanf("%d",&x);
                check = menor(x, C);
                check == 0 ? printf("todos os elementos do conjunto sao menores que %d", check) : printf("existem %d menores do que %d\n", check, x);
                break;
            case 8:
                scanf("%d",&x);
                pertenceConjunto(x, C) == 1 ? printf("o numero %d pertence ao conjunto", x) : printf("Nao pertence ao conjunto");
                break;
            //op
            case 9:
                conjuntosIdenticos(C, C2) == 1 ? printf("Os conjuntos sao diferentes") : printf("Conjuntos identicos") ;
                break;
            case 10:
                C = criaConjunto();
                C2 = criaConjunto(); 
                printf("quantos elementos tera em C1?\n");
                scanf("%d", &aux);
                printf("insira os elementos de C1: \n ...\n");
                for(i = 0; i < aux; i++){
                    scanf("%d", &check);
                    insereElementoConjunto(check, C);
                }
                printf("quantos elementos tera em C2?\n");
                scanf("%d", &aux);
                printf("insira os elementos de C2: \n ...\n");
                for(i = 0; i < aux; i++){
                    scanf("%d", &check);
                    insereElementoConjunto(check, C2);
                }

                subconjunto(C, C2) == TRUE ? printf("C1 e subconjunto de C2\n") : printf("C1 nao e subconjunto de C2\n");
                break;
            case 11:
                C = criaConjunto();
                C2 = criaConjunto(); 
                printf("quantos elementos tera em C1?\n");
                scanf("%d", &aux);
                printf("insira os elementos de C1: \n ...\n");
                for(i = 0; i < aux; i++){
                    scanf("%d", &check);
                    insereElementoConjunto(check, C);
                }
                printf("quantos elementos tera em C2?\n");
                scanf("%d", &aux);
                printf("insira os elementos de C2: \n ...\n");
                for(i = 0; i < aux; i++){
                    scanf("%d", &check);
                    insereElementoConjunto(check, C2);
                }

                C3 = complemento(C, C2);
                mostraConjunto(C3, "C");
                break;
            case 12:
                C = criaConjunto();
                C2 = criaConjunto(); 
                printf("quantos elementos tera em C1?\n");
                scanf("%d", &aux);
                printf("insira os elementos de C1: \n ...\n");
                for(i = 0; i < aux; i++){
                    scanf("%d", &check);
                    insereElementoConjunto(check, C);
                }
                printf("quantos elementos tera em C2?\n");
                scanf("%d", &aux);
                printf("insira os elementos de C2: \n ...\n");
                for(i = 0; i < aux; i++){
                    scanf("%d", &check);
                    insereElementoConjunto(check, C2);
                }

                C3 = uniao(C, C2);
                mostraConjunto(C3, "C");
                break;
            case 13:
                C = criaConjunto();
                C2 = criaConjunto(); 
                printf("quantos elementos tera em C1?\n");
                scanf("%d", &aux);
                printf("insira os elementos de C1: \n ...\n");
                for(i = 0; i < aux; i++){
                    scanf("%d", &check);
                    insereElementoConjunto(check, C);
                }
                printf("quantos elementos tera em C2?\n");
                scanf("%d", &aux);
                printf("insira os elementos de C2: \n ...\n");
                for(i = 0; i < aux; i++){
                    scanf("%d", &check);
                    insereElementoConjunto(check, C2);
                }

                C3 = interseccao(C, C2);
                conjuntoVazio(C3) == 1 ? printf("conjunto vazio.\n") : printf("conjunto nao-vazio.\n");
                mostraConjunto(C3, "C");
                break;
            case 14:
                C = criaConjunto();
                C2 = criaConjunto(); 
                printf("quantos elementos tera em C1?\n");
                scanf("%d", &aux);
                printf("insira os elementos de C1: \n ...\n");
                for(i = 0; i < aux; i++){
                    scanf("%d", &check);
                    insereElementoConjunto(check, C);
                }
                printf("quantos elementos tera em C2?\n");
                scanf("%d", &aux);
                printf("insira os elementos de C2: \n ...\n");
                for(i = 0; i < aux; i++){
                    scanf("%d", &check);
                    insereElementoConjunto(check, C2);
                }

                C3 = diferenca(C, C2);
                conjuntoVazio(C3) == 1 ? printf("conjunto vazio.\n") : printf("conjunto nao-vazio.\n");
                mostraConjunto(C3, "C");
                break;
            case 15:
                C = criaConjunto();
                printf("quantos elementos tera em C1?\n");
                scanf("%d", &aux);
                printf("insira os elementos de C1: \n ...\n");
                for(i = 0; i < aux; i++){
                    scanf("%d", &check);
                    insereElementoConjunto(check, C);
                }
                
                conjuntoPartes(C);
                break;
            case 16:
                scanf("%s", ordem);
                mostraConjunto(C, ordem);
                break;
            case 17:
                C = criaConjunto();
                C2 = criaConjunto(); 
                printf("quantos elementos tera em C1?\n");
                scanf("%d", &aux);
                printf("insira os elementos de C1: \n ...\n");
                for(i = 0; i < aux; i++){
                    scanf("%d", &check);
                    insereElementoConjunto(check, C);
                }
                printf("quantos elementos tera em C2?\n");
                scanf("%d", &aux);
                printf("insira os elementos de C2: \n ...\n");
                for(i = 0; i < aux; i++){
                    scanf("%d", &check);
                    insereElementoConjunto(check, C2);
                }

                copiarConjunto(C, C2) == SUCESSO ? printf("Concluido com sucesso\n") : printf("Algo deu errado\n");

                mostraConjunto(C2, ordem);
                break;
            case 18:
                destroiConjunto(C) == SUCESSO ? printf("conjunto destruido\n") : printf("por alguma razao, nao foi possivel destruir o conjunto\n");
                break;
            case 19:
                printf("liberando memoria\n");
                liberar(C);
                return(0);
                break;
            
            default:
                printf("operacao inexistente, verifique a ortografia.\n"); return 0;
                break;
            }
    }
    printf("liberando memoria\n");
    liberar(C);
    return 0;
}