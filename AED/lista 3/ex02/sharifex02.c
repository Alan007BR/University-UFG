//
// Arquivo data.h
//
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define MENOR -1
#define IGUAL 0
#define MAIOR 1

typedef struct Data {
    unsigned int dia;
    unsigned int mes;
    unsigned int ano;
} Data;

Data *criaData                  (unsigned int dia, unsigned int mes, unsigned int ano);
Data *copiaData                 (Data d);
void liberaData                 (Data * d);
Data *somaDiasData              (Data d, unsigned int dias);
Data *subtrairDiasData          (Data d, unsigned int dias);
void atribuirData               (Data * d, unsigned int dia, unsigned int mes, unsigned int ano);
unsigned int obtemDiaData       (Data d);
unsigned int obtemMesData       (Data d);
unsigned int obtemAnoData       (Data d);
unsigned int bissextoData       (Data d);
int comparaData                 (Data d1, Data d2);
unsigned int numeroDiasDatas    (Data d1, Data d2);
unsigned int numeroMesesDatas   (Data d1, Data d2);
unsigned int numeroAnosDatas    (Data d1, Data d2);
unsigned int obtemDiaSemanaData (Data d);
char *imprimeData               (Data d, char *formato);

//
//  Arquivo data.c
//
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include <string.h>


//AUXILIARES
int diasdoano(unsigned int dia, unsigned int mes, unsigned int ano){
    int totDias = dia;
    int countMes = 1;

    while(countMes < mes){
        if(countMes != 2 && countMes != 4 && countMes != 6 && countMes != 9 && countMes != 11){
            totDias += 31;
        }else if(countMes == 2) {  
            
                if(ano % 4 == 0) {
                totDias += 29;
                }   else{
                    
                    totDias += 28;
                }
        
        }else{
            totDias += 30;
        }                                                                                                                                                                              

    countMes++;
    }

    return totDias;
}

void int2string(int num, char *str) {
    int n, i, tam = 0;
    n = num;

    while(n != 0){ n /= 10; tam++; }
    
    for(i = 0; i < tam; i++) {
        str[tam - (i + 1)] = (num % 10) + '0';
        num /= 10;
    }
    str[tam] = '\0';

}
//---------


//criaData
Data *criaData(unsigned int dia, unsigned int mes, unsigned int ano){
    Data *d;

    d = (Data *)malloc(sizeof(Data));
    d->dia = dia;
    d->mes = mes;
    d->ano = ano;
    
    return d;
}
//CopiaData
Data *copiaData(Data d){
    Data *d2;

    d2 = (Data *)malloc(sizeof(Data));
    d2->dia = d.dia;
    d2->mes = d.mes;
    d2->ano = d.ano;

    return d2;
}
//liberaData
void liberaData(Data * d){
    free(d);
}
//somar dias data
Data *somaDiasData(Data d, unsigned int dias){
    Data *t;
    t = (Data *)malloc(sizeof(Data));
    int soma = d.dia + dias;
    t->mes = d.mes; //mes
    t->ano = d.ano;
    
        while(soma > 31 || soma > 30) {
            if(t->mes != 2 && t->mes != 4 && t->mes != 6 && t->mes != 9 && t->mes != 11){
                soma -=31;
                t->mes++;
                if(t->mes > 12){t->ano++; t->mes -= 12;}
                if(soma - 30 < 0){break;}
            }else if(t->mes == 2){
                if(t->ano % 4 == 0){
                soma -=29;
                t->mes++;
                if(t->mes > 12){t->ano++; t->mes -= 12;}
                if(soma - 30 < 0){break;}      
                }else{
                soma -=28;
                t->mes++;
                if(t->mes > 12){t->ano++; t->mes -= 12;}
                if(soma - 30 < 0){break;}                    
                }
            }else{
                soma -=30;
                t->mes++;
                if(t->mes > 12){t->ano++; t->mes -= 12;}
                if(soma - 30 < 0){break;}
            }
        }
            t->dia = soma; // dias
            return t;
}

Data *subtrairDiasData(Data d, unsigned int dias){
    Data * t;
    t = (Data *)malloc(sizeof(Data));
    int soma = dias - d.dia;
    t->mes = d.mes; //mes
    t->ano = d.ano;
    int flag = 0;
    t->mes--;
    if(t->mes < 1) {
        t->ano--; t->mes = 12;
    }

    while(soma > 0 || soma > 0) {
        if(t->mes != 2 && t->mes != 4 && t->mes != 6 && t->mes != 9 && t->mes != 11){
            soma -=31;
            t->mes--;
            if(t->mes < 1){t->ano--; t->mes += 12;}
        }else if(t->mes == 2){
            if(t->ano % 4 == 0){
            soma -=29;
            t->mes--;
            if(t->mes < 1){t->ano--; t->mes += 12;}
            }else{
            soma -=28;
            t->mes--;
            if(t->mes < 1){t->ano--; t->mes += 12;}
            }
        }else{
            soma -=30;
            t->mes--;
            if(t->mes < 1){t->ano--; t->mes += 12;}
        }
    }
    t->mes++;

    if(soma < 0 ) { soma *= -1;}
    if(t->mes > 12){
        t->ano++; t->mes = 1;
    }
            if(soma == 0){
            t->mes--;
            if(t->mes < 1){t->ano--; t->mes += 12;}
            if(t->mes != 2 && t->mes != 4 && t->mes != 6 && t->mes != 9 && t->mes != 11){
                soma = 31;
            }else if(t->mes == 2){
                if(t->ano % 4 == 0) {
                    soma = 29;
                } else{
                    soma = 28;
                }
            }else{
                soma = 30;
            }
        }
            t->dia = soma; // dias
            return t;
}
//atribuir a data
void atribuirData(Data * d, unsigned int dia, unsigned int mes, unsigned int ano){
    if(ano < 1900 || ano > 2200) {
        d = NULL;
        printf("error\n"); return 0;
    }
    d->dia = dia;
    d->mes = mes;
    d->ano = ano;
}

//obter dia da data
unsigned int obtemDiaData(Data d){
    return d.dia;
}
//obter mes da data
unsigned int obtemMesData(Data d){
    return d.mes;
}
//obter ano da data
unsigned int obtemAnoData(Data d){
    return d.ano;
}
//obter se o ano data e bissexto ou nao
unsigned int bissextoData(Data d){
    if(d.ano % 4 == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}
//comparar data
int comparaData(Data d1, Data d2){
    if(d1.ano < d2.ano) {
        return MENOR;
    } else if(d1.ano > d2.ano) {
        return MAIOR;
    }else if(d1.ano == d2.ano) {
        if(d1.mes < d2.mes) {
            return MENOR;
        } else if(d1.mes > d2.mes){
            return MAIOR;
        } else if(d1.mes == d2.mes) {
            if(d1.dia < d2.dia){
                return MENOR;
            }else if(d1.dia > d2.dia){
                return MAIOR;
            } else if(d1.dia == d2.dia){
                return IGUAL;
            }
        }
    }
}
//numero de dias entre  datas
unsigned int numeroDiasDatas(Data d1, Data d2){
    int flag;
    int ano1, ano2, ano1Aux, ano2Aux;
    int totalDias;
    
    flag = comparaData(d1, d2);
    if(flag == IGUAL) {return IGUAL;}

    ano1 = diasdoano(d1.dia, d1.mes, d1.ano);
    ano2 = diasdoano(d2.dia, d2.mes, d2.ano);
    
    if(d1.ano == d2.ano){
    totalDias = (ano2 - ano1);
    } else{
    totalDias = (ano2 - ano1) + (d2.ano - d1.ano) * 365;
    }
        
    ano1Aux = d1.ano;
    ano2Aux = d2.ano; 

    totalDias += (ano2Aux / 4) - (ano1Aux / 4);
    totalDias -= (ano2Aux / 100) - (ano1Aux / 100);
    totalDias += (ano2Aux / 400) - (ano1Aux / 400);

    if(totalDias < 0) totalDias *= -1;
    return totalDias;
}
//numero de meses entre datas
unsigned int numeroMesesDatas(Data d1, Data d2){
    int totalMeses = 0;

    totalMeses = ((d2.ano - d1.ano) * 12) + (d2.mes - d1.mes);

    if(totalMeses < 0) totalMeses *= -1;
    return totalMeses;
}

//numero de anos entre datas
unsigned int numeroAnosDatas(Data d1, Data d2){
    int totalAnos;

    totalAnos = d2.ano - d1.ano;

    if(totalAnos < 0) totalAnos *= -1;
    return totalAnos;
}
//o dia da semana corresponde a data
unsigned int obtemDiaSemanaData (Data d){
    int ano = d.ano;
    int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    if(d.mes < 3){ano -=1;}

    return (ano + ano/4 - ano/100 + ano/400 + t[d.mes-1] + d.dia) % 7;
}


char *imprimeData(Data d, char *formato){
    int i = 0, k = 0, g = 0, j = 0;

    //DDMMAAAA ...
    if(formato[0] == 'D' && formato[1] == 'D' && formato[2] == 'M' && formato[3] == 'M' && formato[4] == 'A' && formato[5] == 'A' && formato[6] == 'A' && formato[7] == 'A'){
        sprintf(formato, "%u/%u/%u", d.dia,d.mes, d.ano);

    }else if(formato[0] == 'D' && formato[1] == 'D' && formato[2] == 'M' && formato[3] == 'M' ) {//DDMM
        sprintf(formato, "%u/%u", d.dia,d.mes);
    }else if(formato[0] == 'D' && formato[1] == 'D' ){//DD
        sprintf(formato, "%u", d.dia);
    }

    //AAAAMMDD ...
    if(formato[0] == 'A' && formato[1] == 'A' && formato[2] == 'A' && formato[3] == 'A' && formato[4] == 'M' && formato[5] == 'M' && formato[6] == 'D' && formato[7] == 'D'){
        sprintf(formato, "%u/%u/%u", d.ano,d.mes, d.dia);
    }else if(formato[0] == 'A' && formato[1] == 'A' && formato[2] == 'A' && formato[3] == 'A' ) {//AAAA
        sprintf(formato, "%u", d.ano);
    }
    //MM
    if(formato[0] == 'M' && formato[1] == 'M' ){
        sprintf(formato, "%u", d.mes);

    }

    return formato;
}

//
// Corpo principal (main.c)
//
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