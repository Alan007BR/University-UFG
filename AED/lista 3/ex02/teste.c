#include <stdio.h>

int2string(int num, char *str) {
    int n, i, tam = 0;
    n = num;

    while(n != 0){ n /= 10; tam++; }
    
    for(i = 0; i < tam; i++) {
        str[tam - (i + 1)] = (num % 10) + '0';
        num /= 10;
    }
    str[tam] = '\0';

}
int somadias(unsigned int dia, unsigned int mes, unsigned int dias, unsigned int ano) {

    int soma = dia + dias;
    printf("soma: %d\n", soma);

        while(soma > 31 || soma > 30) {
            if(mes != 2 && mes != 4 && mes != 6 && mes != 9 && mes != 11){
                soma -=31;
                mes++;
                if(mes > 12){ano++; mes -= 12;}
                if(soma - 30 < 0){break;}
            }else if(mes == 2){
                if(ano % 4 == 0){
                soma -=29;
                mes++;
                if(mes > 12){ano++; mes -= 12;}
                if(soma - 30 < 0){break;}      
                }else{
                soma -=28;
                mes++;
                if(mes > 12){ano++; mes -= 12;}
                if(soma - 30 < 0){break;}                    
                }
            }else{
                soma -=30;
                mes++;
                if(mes > 12){ano++; mes -= 12;}
                if(soma - 30 < 0){break;}
            }
        }
    printf("dia: %d\n", soma);
    printf("mes: %d\n", mes);
    printf("ano: %d\n", ano);
    printf("----------------\n");

}
int subtrairDiasData(unsigned int dia, unsigned int mes, unsigned int dias, unsigned int ano) {

    int soma = dias - dia;
    int flag = 0;
    printf("soma: %d\n", soma);
        mes--;
        if(mes < 1) {
            ano--; mes = 12;
        }
        while(soma > 0 || soma > 0) {
            if(mes != 2 && mes != 4 && mes != 6 && mes != 9 && mes != 11){
                soma -=31;
                mes--;
                if(mes < 1){ano--; mes += 12;}
            }else if(mes == 2){
                if(ano % 4 == 0){
                soma -=29;
                mes--;
                if(mes < 1){ano--; mes += 12;}
                }else{
                soma -=28;
                mes--;
                if(mes < 1){ano--; mes += 12;}
                }
            }else{
                soma -=30;
                mes--;
                if(mes < 1){ano--; mes += 12;}
            }
        }
        mes++;
    if(soma < 0 ) { soma *= -1;}
    if(mes > 12){
        ano++; mes = 1;
    }
            if(soma == 0){
            mes--;
            if(mes < 1){ano--; mes += 12;}
            if(mes != 2 && mes != 4 && mes != 6 && mes != 9 && mes != 11){
                soma = 31;
            }else if(mes == 2){
                if(ano % 4 == 0) {
                    soma = 29;
                } else{
                    soma = 28;
                }
            }else{
                soma = 30;
            }
        }
    printf("dia: %d\n", soma);
    printf("mes: %d\n", mes);
    printf("ano: %d\n", ano);
    printf("----------------\n");

}

int decompormesemdia(unsigned int dia, unsigned int mes, unsigned int ano) {

    int i = 1;
    int soma = 0;

    for(i = 1; i < mes; i++) {

        if(i == 2){
            if(ano % 4 == 0) {
                soma+= 29;
            printf("%d ", soma - 29);
            }else{
                soma += 28;
            printf("%d ", soma - 28);
            }
        }
        else if(i % 2 != 0 && i != 2) {
            soma += 31;
            printf("%d ", soma - 31);
        } else if (i % 2 == 0 && i != 2) {
            soma += 30;
            printf("%d ", soma - 30);
        }
    }
    return soma + dia - 1;
}

int main(){

    unsigned int dia = 8, dias = 800;
    unsigned int mes = 1;
    unsigned int ano = 1979;
    unsigned int soma;
    char str[10];


    // soma = decompormesemdia(dia, mes, ano);
    // printf("-%d\n", soma);

    // soma = subtrairDiasData(dia, mes, dias, ano);
    // printf("-%d-\n", soma);

    scanf("%d", &soma);
    int2string(soma, str);
    printf("%s-", str);
    return 0;
}