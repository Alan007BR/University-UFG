/* +
É atribuído ao aço produzido o grau 10 se ele passar por todos os testes. É atribuído ao aço
produzido o grau 9 se ele passar somente nos testes 1 e 2. É atribuído ao aço produzido o grau 8
se passar apenas no teste 1. É atribuído ao aço produzido o grau 7 se ele não passar nos 3 testes.
Elabore um programa em C que receba o conteúdo do carbono (CC), a dureza Rockwell (DR) e a
resistência à tração (RT) de um lote de aço produzido e exiba o grau de pureza do lote fornecido.
*/

#include <stdio.h>


int main() {

    float carb;
    int durez;
    int resist;

    scanf("%f", &carb);
    if(carb > 30 || carb < 0) {
        printf("erro\n");
        return 0;
    }

    scanf("%d", &durez);
    if(durez > 100 || durez < 0) {
        printf("erro\n");
        return 0;
    }

    scanf("%d", &resist);
    if(resist > 100000 || resist < 0) {
        printf("erro\n");
        return 0;
    }


    if(carb < 7 && durez > 50 && resist > 80000) {
        printf("10\n");
    } else if(carb < 7 && durez > 50) {
        printf("9\n");
    } else if(carb < 7) {
        printf("8\n");
    } else {
        printf("7\n");
    }

    return 0;
}