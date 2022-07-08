#include <stdio.h>
#define MAX 10000

int main() {

    int i = 0, j = 0;
    int pos_mair, testes = 0, n = 1, m = 1, limsup, liminf, entrada, maior;
    char str[MAX], apagados[MAX];


    while (scanf("%d %d", &n, &m) && (n+m)!=0) {
        
        for(i = 0; i < n;) {
            scanf("%c", &entrada);

            if(entrada >= '0' && entrada <='9') {
                str[i]=entrada;
                i++;
            }
        }

    liminf = 0;
    limsup = n-m;

    for (i=0; i<m; i++) {

        for (j= liminf, maior=0; j<=limsup; j++) {
            if(str[j] > maior){
                maior = str[j];
                pos_mair = j;
            }
        }

        apagados[i] = maior;
        liminf = pos_mair + 1;
        limsup++;
    }

    apagados[i] = '\0';
    printf("%s\n", apagados);
    testes++;
    }


    return 0;
}