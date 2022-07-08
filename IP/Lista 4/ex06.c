#include <stdio.h>

int main() {

    int ll = 0, cc = 0, l = 0, c = 0, i = 0, j = 0;
    int M[6][6];
    int maior = 0, menor = 0;
    int combinacoes[16], comb = 0, soma = 0;
    int neg = 0;

    for (l = 0; l < 6; l++) {
        for (c = 0; c < 6; c++) {
            scanf("%d", &M[l][c]);
        }
    }

    for (l = 0; l < 6; l++) {
        for (c = 0; c < 6; c++) {

            //comeco
            while(ll < 4 && cc < 4) {
                    for (i = ll; i < ll+3; i++) {
                        for (j = cc; j < cc+3; j++) {
                            if (i == ll+1 && j == cc+0 || i == ll+1 && j == cc+2) {
                            } else {
                            soma = soma + M[i][j];
                            }
                        }
                    }
                    combinacoes[comb] = soma;
                    soma = 0;
                    comb++;
                cc++;
                if (cc >= 4) {
                ll++;
                cc = 0;
                }
            }
          //fim  

        }
    }

    for(comb = 0; comb < 16; comb++) {
        if (combinacoes[comb] < 0) {
            neg++;
        }
        if (combinacoes[comb] > maior) {
            maior = combinacoes[comb];
        }

        if (combinacoes[comb] < menor) {
            menor = combinacoes[comb];
        }

    }   
    if ( neg == 16) {
        printf("%d\n", menor);
    } else {
        printf("%d\n", maior);
    }

    return 0;
}