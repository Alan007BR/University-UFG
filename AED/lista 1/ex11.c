/* (+) 
Elabore um programa na linguagem C para receber a temperatura máxima de cada um dos dias
de um mês de um ano e exibir as seguintes informações: a) o(s) dia(s) que teve(tiveram) a maior
temperatura máxima registrada e qual foi essa temperatura; b) a média da temperatura máxima
no mês. O algoritmo deve receber inicialmente o ano que será considerado, o mês dento do ano
que será considerado e finalmente cada um dos dias com a respectiva temperatura máxima
registrada. (++)
*/
#include <stdio.h>

void BigDayTemp(int * days, int quant) {

    int i = 0;
    int m = 0;

    for(i = 0; i < quant; i++) {
        if(days[i] >= m) m = days[i];
    }
    printf("%d", m);

    for(i = 0; i < quant; i++) {
        if(days[i] == m) {
            printf(" %d", i+1);
        }
    }

    printf("\n");

}

int registerDays(int * days, int quant) {

    int i = 0;

    for(i = 0; i < quant; i++) {
        scanf("%d", &days[i]);
            if(days[i] > 100 || days[i] < -100){ 
                printf("erro"); 
                return 0;
            }
    }

    return 1;
}

float sumDaysTemp(int * days, int quant) {

    float med;
    int i = 0;

    for(i = 0; i < quant; i++) {
        med += days[i];
    }
    med = med / (float)quant;
    
    return med;
}

int main() {

    int year, month, med;
    int days[31];
    int i = 0;

    scanf("%d", &year);
    if(year < 2000 || year > 2022){ printf("erro\n"); return 0; }
    scanf("%d", &month);
    if(month < 1 || month > 12){ printf("erro\n"); return 0; } 

    if(month == 4 || month == 6 || month == 9 || month == 11) {//teste 8 e 9
        registerDays(days, 30);
        BigDayTemp(days, 30);
        printf("%.1f\n", sumDaysTemp(days, 30));
        return 0;
    }

    if(month == 2) { // entradas 5 e 1
        if(year % 4 == 0) {
            if (registerDays(days, 29) == 0) { return 0; }
            BigDayTemp(days, 29);
            printf("%.1f\n", sumDaysTemp(days, 29));
            return 0;
        } else {
            if (registerDays(days, 28) == 0) { return 0; }
            BigDayTemp(days, 28);
            printf("%.1f\n", sumDaysTemp(days, 28));
            return 0;
        }
    }

    if (registerDays(days, 31) == 0) { return 0; }// teste 6 e 7
    BigDayTemp(days, 31);
    printf("%.1f\n", sumDaysTemp(days, 31));

    return 0;
}