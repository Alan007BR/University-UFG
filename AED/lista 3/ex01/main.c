#include "conjuntos.h"

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
    Conjunto *teste;

    while(1) {
        menu(choice);
        scanf("%d",&choice);    
        
            switch (choice) {
            case 1:
                C = criaConjunto();
                C2 = criaConjunto();
                criaConjunto2(&teste);
                //C = criaConjunto(C) == SUCESSO ? printf("Conjunto Criado\n") : printf("O Conjunto nao foi criado\n");
                teste == NULL ? printf("FALHA: O conjunto nao foi criado\n") : printf("SUCESSO: Conjunto criado\n");
                break;
            case 2:
                conjuntoVazio(&teste) == 1 ? printf("conjunto vazio.\n") : printf("conjunto nao-vazio.\n");
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