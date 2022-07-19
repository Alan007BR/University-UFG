#include <stdio.h>
#include <stdlib.h>
#include "conjuntos.h"

void menu(choice) {
    printf("\n");
    printf("1 - criar um conjunto vazio\n");
    printf("2 - verifica se o conjunto e vazio\n");
    printf("3 - insere um numero no conjunto\n");
    printf("4 - excluir elemento do conjunto\n");
    printf("5 - tamanho do conjunto\n");
    printf("6 - maiores que X do conjunto\n");
    printf("7 - menores que X do conjunto\n");
    printf("8 - verifica se o elemento X pertence ao conjunto\n");
    printf("9 - verificar se os conjuntos sao identicos\n");
    printf("123 - criar um vetor vazio\n");
    printf("16 - Monstrar conjunto em ordem Crescente - 'C' ou decrescente - 'D' \n");
    printf("\n");
}

int main(){

    unsigned int choice;
    int x, check;
    char ordem;
    Conjunto *C;
    Conjunto *C2;

    while(1) {
        menu(choice);
        scanf("%d",&choice);    
        
            switch (choice) {
            case 1:
                //criaConjunto(C);
                //C2 = criaConjunto();
                criaConjunto(C) == SUCESSO ? printf("Conjunto Criado\n") : printf("O Conjunto nao foi criado\n");
                //C == NULL ? printf("FALHA: O conjunto nao foi criado\n") : printf("SUCESSO: Conjunto criado\n");
                break;
            case 2:
                conjuntoVazio(C) == 1 ? printf("conjunto vazio.\n") : printf("conjunto nao-vazio.\n");
                break;
            case 3:
                scanf("%d",&x);
                check = insereElementoConjunto(x, C);
                check == 1 ? printf("SUCESSO: Elemento Adicionado\n") : printf("FALHA: O elemento nao foi adicionado por alguma razao");
                break;
            case 4:
                scanf("%d",&x);
                excluirElementoConjunto(x, C);
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
                pertenceConjunto(x, C) == 1 ? printf("o numero %d pertence ao conjunto", x) : printf("Nao pertence ao conjunto", x);
                break;
            //op
            case 9:
                conjuntosIdenticos(C, C2) == 1 ? printf("Os conjuntos sao diferentes") : printf("Conjuntos identicos") ;
                break;
            case 10:
                criaConjunto(C);
                break;
            case 11:
                criaConjunto(C);
                break;
            case 12:
                criaConjunto(C);
                break;
            case 13:
                criaConjunto(C);
                break;
            case 14:
                criaConjunto(C);
                break;
            case 15:
                criaConjunto(C);
                break;
            case 16:
                //scanf("%c\n", &ordem);
                mostraConjunto(C, "C");
                break;
            case 17:
                criaConjunto(C);
                break;
            case 18:
                criaConjunto(C);
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
    //C = NULL;   
    return 0;
}