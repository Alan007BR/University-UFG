#include <stdio.h>
#include <stdlib.h>

void maior_menor(int **M, int l,int c, int *maior, int *menor) {

    int i = 0, j = 0;
    int m = 0, n = 1001;

    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            if (M[i][j] > m) {
                m = M[i][j];
            }
            if (M[i][j] < n) {
                n = M[i][j];
            }
        }
    }
    *maior = m;
    *menor = n;

}
    void liberar(int **M, int l) {
        int i = 0;

        for (i = 0; i < l; i++)
            free(M[i]);
        
        free(M);
    }

    float frequency (int **M, int l, int c, int *maior, int *menor, float *freqMenor, float *freqMaior) {
        float freqM = 0, freqMen = 0, freqMaior2 = 0, freqMenor2 = 0;
        int tot = l*c;
        int i = 0, j = 0;
        int a = 100;

        for (i = 0; i < l; i++) {
            for(j = 0; j < c; j++) {
                if (M[i][j] == *maior) {
                    freqMaior2++;
                }
                if (M[i][j] == *menor) {
                    freqMenor2++;
                }
            }
        }


        freqMen = (a*freqMenor2)/tot;
        freqM = (a*freqMaior2)/tot;

        *freqMaior = freqM;
        *freqMenor = freqMen;
    }

int main() {

    int l, c;
    int i = 0, j = 0;
    int **M, m = 0, n = 0, *maior = &m, *menor = &n;
    float freqMen = 0.0, freqM = 0.0, *freqMaior = &freqM, *freqMenor = &freqMen;
    scanf("%d %d", &l, &c);

    M = (int **)malloc(l*sizeof(int **));
    for (i = 0; i < l; i++) {
        M[i] = (int *)malloc(c*sizeof(int *));

    }

    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            scanf("%d", &M[i][j]);
        }
    }
    maior_menor(M, l, c, maior, menor);
    frequency(M, l, c, maior, menor, freqMenor, freqMaior);
    
    printf("%d %.2f%\n", *menor, *freqMenor);
    printf("%d %.2f%\n", *maior, *freqMaior);


    liberar(M, l);
    return 0;
}

