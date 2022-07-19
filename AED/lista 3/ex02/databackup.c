#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include <string.h>


//AUXILIARES

int decompormesemdia(unsigned int dia, unsigned int mes, unsigned int ano) {

    int i = 1;
    int soma = 0;

    for(i = 1; i < mes; i++) {

        if(i == 2){
            if(ano % 4 == 0) {
                soma+= 29;
            }else{
                soma += 28;
            }
        }
        else if(i % 2 != 0 && i != 2) {
            soma += 31;
        } else if (i % 2 == 0 && i != 2) {
            soma += 30;
        }
    }
    return soma + dia - 1;
}




//criaData
Data *criaData(unsigned int dia, unsigned int mes, unsigned int ano){
    Data *d;

    d = (Data *)malloc(sizeof(Data));
    d->dia = dia;
    d->mes = mes;
    d->ano = ano;
    
    printf("dia: %d\n", d->dia);
    printf("mes: %d\n", d->mes);
    printf("ano: %d\n", d->ano);
    return d;
}
//CopiaData
Data *copiaData(Data * d){
    Data *d2;

    d2 = (Data *)malloc(sizeof(Data));
    d2->dia = d->dia;
    d2->mes = d->mes;
    d2->ano = d->ano;

    return d2;
}
//liberaData
void liberaData(Data * d){
    free(d);
}
//somar dias data
Data *somaDiasData(Data *d, unsigned int dias){
    Data *t;
    t = (Data *)malloc(sizeof(Data));
    int soma = d->dia + dias;
    t->mes = d->mes; //mes
    t->ano = d->ano;
    
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

Data *subtrairDiasData(Data *d, unsigned int dias){
    Data *t;
    t = (Data *)malloc(sizeof(Data));
    int soma = dias - d->dia;
    t->mes = d->mes; //mes
    t->ano = d->ano;
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
char *imprimeData(Data *d, char *formato){
    int i = 0, k = 0;
    char formatado[10];

    for(i=0; formato[i] != '\0'; i++){
        if(formato[i] == 'a' || formato[i] == 'A'){
            //aaaammdd || aaaa
        }
        if(formato[i] == 'd' || formato[i] == 'D'){
            //ddmmaaaa || ddmm || dd
            if(formato[i] == 'd' && formato[i+1] == 'd' && formato[i+2] == 'm' && formato[i+3] == 'm' && formato[i+4] == 'a'){
            //ddmmaa...
            for(k = 0; k < 10; k++){
                if(k == 2 || k == 5){
                    formatado[k] = '/';
                }
                if(k < 2) {
                sprintf(formatado, "%d", d->dia);
                printf("%s ", formatado);
                }
                if(k> 2 && k < 5) {
                sprintf(formatado, "%d", d->mes);
                printf("%s ", formatado);

                }
                if(k > 5 && k < 10) {
                sprintf(formatado, "%d", d->ano);
                printf("%s ", formatado);
                //formatado[k] = ( (d->ano % 10) + '0' );
                }
            //printf(" %c ", formatado[k]);
            }

            return formatado;
            printf("%u/%u/%u", d->dia, d->mes, d->ano);
            } 
            else if(formato[i] == 'd' && formato[i+1] == 'd' && formato[i+2] == 'm' && formato[i+3] == 'm'){
            //ddmm
            printf("%u/%u", d->dia, d->mes);
            }
            else if(formato[i] == 'd' && formato[i+1] == 'd'){
            //dd
            printf("%u", d->dia);
            }
        }
        if(formato[i] == 'm' || formato[i] == 'M'){
            if(formato[i] == 'm' && formato[i+1] == 'm') {
                printf("%u", d->mes);
            }
        }
    }

    return formato;
}