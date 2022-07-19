#include <stdio.h>
#include <stdlib.h>
#include "data.h"

void menu(int choice) {
    printf("\n");
    printf("1 - criar data\n");
    printf("2 - copiar data\n");
    printf("3 - liberar(destruir) data\n");
    printf("4 - somar data\n");
    printf("5 - subtrair data\n");
    printf("6 - atribuir dia/mes/ano a data\n");
    printf("7 - mostrar dia da data\n");
    printf("8 - mostrar mes da data\n");
    printf("9 - mostrar ano da data\n");
    printf("10 - verificar se o ano e bissexto\n");
    printf("11 - comparar datas (d1 <|==|> d2)\n");
    printf("12 - numero de dias entre duas datas\n");
    printf("13 - numero de meses entre duas datas\n");
    printf("14 - numero de anos entre as datas\n");
    printf("15 - mostrar o dia da semana correspondente a data\n");
    printf("16 - mostrar data em formato especifico\n");
    printf("\n");
}

int main(){

    unsigned int choice, dia, mes, ano;
    unsigned int dias;
    int check;
    char formato[10] = "DDMMAAAA";
    char formatado[9];
    Data *d, *d2, *soma;
    int i = 0;

    while(1) {
        menu(choice);
        scanf("%d",&choice);    
        
            switch (choice) {
            case 1:
                printf("Digite a data: \n..\n");
                scanf("%u %u %u", &dia, &mes, &ano);
                d = criaData(dia, mes, ano);
                printf("dia: %d\n", d->dia);
                printf("mes: %d\n", d->mes);
                printf("ano: %d\n", d->ano);
                break;
            case 2:
                d2 = copiaData(*d);
                printf("%u %u %u", d2->dia, d2->mes, d2->ano);
                break;
            case 3:
                liberaData(d);
                break;
            case 4:
                printf("Digite a quantidade de dias: \n..\n");
                scanf("%u", &dias);
                soma = somaDiasData(*d, dias);
                printf("++ %u/%u/%u ++", soma->dia, soma->mes, soma->ano);
                break;
            case 5:
                printf("Digite a quantidade de dias: \n..\n");
                scanf("%u", &dias);
                soma = subtrairDiasData(*d, dias);
                printf("-- %u/%u/%u --", soma->dia, soma->mes, soma->ano);
                break;
            case 6:
                printf("Digite a data: \n..\n");
                scanf("%u %u %u", &dia, &mes, &ano);
                atribuirData(d, dia, mes, ano);
                printf("atibuido: %u/%u/%u\n", d->dia, d->mes, d->ano);
                break;
            case 7:
                printf("Dia: %u",  obtemDiaData(*d));
                break;
            case 8:
                printf("Mes: %u",  obtemMesData(*d));
                break;
            case 9:
                printf("Ano: %u",  obtemAnoData(*d));
                break;
            case 10:
                bissextoData(*d) == TRUE ? printf("O ano: %u e bissexto", d->ano) : printf("O ano: %u nao e bissexto", d->ano); 
                break;
            case 11:
                printf("Digite as datas: \n..\n");
                scanf("%u %u %u", &dia, &mes, &ano);
                d = criaData(dia, mes, ano);

                printf("Data 2:\n");

                scanf("%u %u %u", &dia, &mes, &ano);
                d2 = criaData(dia, mes, ano);

                printf("\n Verificando.. \n");
                check = comparaData(*d, *d2);
                if(check == MAIOR){ printf("MAIOR: %u e maior que %u\n", d->ano, d2->ano);}
                if(check == MENOR){ printf("MENOR: %u e menor que %u\n", d->ano, d2->ano);}
                if(check == IGUAL){ printf("IGUAL: %u e igual a %u\n", d->ano, d2->ano);}
                break;
            case 12:
                printf("Digite as datas: \n..\n");
                scanf("%u %u %u", &dia, &mes, &ano);
                d = criaData(dia, mes, ano);

                printf("Data 2:\n");

                scanf("%u %u %u", &dia, &mes, &ano);
                d2 = criaData(dia, mes, ano);

                printf("\n Verificando.. \n");
                check = numeroDiasDatas(*d, *d2);
                if(check == IGUAL) { printf("IGUAIS: As datas sao iguais, entao o numero de dias entre as datas e 0\n"); }
                else{
                    printf("o total de dias entre D1 e D2 e: %u\n", check);
                }
                liberaData(d);liberaData(d2);
                break;
            case 13:
                printf("Digite as datas: \n..\n");
                scanf("%u %u %u", &dia, &mes, &ano);
                d = criaData(dia, mes, ano);

                printf("Data 2:\n");

                scanf("%u %u %u", &dia, &mes, &ano);
                d2 = criaData(dia, mes, ano);

                printf("\n Verificando.. \n");
                check = numeroMesesDatas(*d, *d2);
                if(check == IGUAL) { printf("IGUAIS: As datas sao iguais, entao o numero de dias entre as datas e 0\n"); }
                else{
                    printf("o total de meses entre D1 e D2 e: %u\n", check);
                }
                liberaData(d);liberaData(d2);
                break;
            case 14:
                printf("Digite as datas: \n..\n");
                scanf("%u %u %u", &dia, &mes, &ano);
                d = criaData(dia, mes, ano);

                printf("Data 2:\n");

                scanf("%u %u %u", &dia, &mes, &ano);
                d2 = criaData(dia, mes, ano);

                printf("\n Verificando.. \n");
                check = numeroAnosDatas(*d, *d2);
                if(check == IGUAL) { printf("IGUAIS: As datas sao iguais, entao o numero de dias entre as datas e 0\n"); }
                else{
                    printf("o total de meses entre D1 e D2 e: %u\n", check);
                }
                break;
            case 15:
                printf("Digite a data: \n..\n");
                scanf("%u %u %u", &dia, &mes, &ano);
                d = criaData(dia, mes, ano);

                check = obtemDiaSemanaData(*d);
                check == 0 ? printf("[%u/%u/%u] - Domingo", d->dia, d->mes, d->ano) :
                check == 1 ? printf("[%u/%u/%u] - Segunda", d->dia, d->mes, d->ano) :
                check == 2 ? printf("[%u/%u/%u] - Terca", d->dia, d->mes,   d->ano) :
                check == 3 ? printf("[%u/%u/%u] - Quarta", d->dia, d->mes,  d->ano) :
                check == 4 ? printf("[%u/%u/%u] - Quinta", d->dia, d->mes,  d->ano) :
                check == 5 ? printf("[%u/%u/%u] - Sexta", d->dia, d->mes,   d->ano) : printf("[%u/%u/%u] - Sabado", d->dia, d->mes, d->ano);
                
                liberaData(d);
                break;
            case 16:
                    printf("Digite a data: \n..\n");
                    scanf("%u %u %u", &dia, &mes, &ano);
                    d = criaData(dia, mes, ano);
                    printf("digite um formato: \n");
                    printf("DDMMAAAA -");
                    printf("DDMM -");
                    printf("DD\n");
                    printf("AAAAMMDD -");
                    printf("AAAA -");
                    printf("MM\n");
                    scanf("%s", formato);
                    printf("\n-%s-\n", imprimeData(*d, formato));
                    liberaData(d);
                break;
            
            default:
                printf("operacao inexistente, verifique a ortografia.\n"); return 0;
                break;
            }
    }

    liberaData(d);
    return 0;
}