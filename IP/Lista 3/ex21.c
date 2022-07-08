#include <stdio.h>

int main() {

    int num[6];
    int apostas, ganho = 0;
    int apostados[50000][6];//as apostas vao ser ser numeros, sendo eles no max 500000
    int resul;

    int i = 0, j = 0, k = 0;
    int quina = 0, quadra = 0, sena = 0;

    for (i = 0; i < 6; i++) {
        scanf("%d", &num[i]);
    }

    scanf("%d", &apostas);//numero de apostas

    for (i = 0; i < apostas; i++) {//indice maior, representa a quantidade de apostas
        for (j = 0; j < 6; j++) {//aqui é para salvar os numeros apostados, sendo no max 500000 e em casa, 6 numeros, uma matriz;
            scanf("%d", &apostados[i][j]);
        }
    }

    //resul = sorteio(apostas);
    for (i = 0; i < apostas; i++) {
        for (j = 0; j < 6; j++) {
            for (k = 0; k < 6; k++) {
                if(apostados[i][j] == num[k]) {
                    ganho++;
                }
            }
        }

    if (ganho == 4) {quadra++;}
    if (ganho == 5) {quina++;}
    if (ganho == 6) {sena++;}
    ganho = 0; //resetar valor dos acertos
    }
    //sena
    if (sena!=0) { printf("Houve %d acertador(es) da sena\n", sena);}
    else {printf("Nao houve acertador para sena\n");}

    //quina
    if (quina!=0) { printf("Houve %d acertador(es) da quina\n", quina);}
    else {printf("Nao houve acertador para quina\n");}

    //quadra
    if (quadra!=0) { printf("Houve %d acertador(es) da quadra\n", quadra);}
    else {printf("Nao houve acertador para quadra\n");}


    return 0;
}