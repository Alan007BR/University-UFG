#include <stdio.h>

int ehPermutacao( int matriz[500][500], int n, int *soma ) {

    int i = 0, j = 0;//contadores
    int nulos = 0, elem = 0, s;//contadores de zero, um, e soma dos elementos
    int infra = 0;//infracoes

    for ( i = 0; i < n; i++ ) {
        for ( j = 0; j < n; j++ ) {
            if ( matriz[i][j] == 0 ) {
                nulos++;
            }//contagem de zeroz
            if ( matriz[i][j] == 1 ) {
                elem++;
            }//contagem de n um
            
            if ( matriz[i][j] != 0 ) {
            s = s + matriz[i][j];

            }//soma de todos os elementos diferentes de zero
        }

        if ( nulos != n-1 && elem != 1 ) {
            infra++;
        }//para cara nulos totais menor que n-1 e mais que um numero um por linha, adicionar uma infracao 

        nulos = 0;//resetar variaveis para continuar o trampo
        elem = 0;
    }
    *soma = s;//o ponteiro de soma que liga ao sum do main vai resceber o valor da soma
    if (infra > 0) { //se tiver mais que uma infracao vai retornar 0
        return 0;
    }

    return 1;//caso o contrario, retornar um, diezendo que é permutacao
}


int main() {

    int n, resul;//tam da matriz, resultado para receber a funcao
    int i = 0, j = 0;//contadores para scanear elem da matriz
    
    int sum = 0;
    int *soma = &sum;//ponteiro soma que recebe o valor de sum
    int M[500][500];//matriz maxima de 500 por 500

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &M[i][j]);
        }
    }

    resul = ehPermutacao( M, n, soma );
    printf("%d\n", n);// m,n da matriz

    if (resul == 0) { printf("NAO EH PERMUTACAO\n"); }//se e o n permutacao
    if (resul == 1) { printf("PERMUTACAO\n");}
    printf("%d\n", *soma);//soma via ponteiro

    return 0;
}