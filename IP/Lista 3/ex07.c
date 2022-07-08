#include <stdio.h>

void nums(int *vet, int tam, int maior) {

    int i = 0;
    int j = 0;

    int m = 0;
        for (i = 0; i <= maior; i++) {
            for (j = 0; j < tam; j++) {
                if (vet[j] <= i) {
                    m++;
                }
            }        
        printf("(%d) %d\n", i, m);
        m = 0;
        }
}

void maiorN(int *vet, int tam, int *maior){
    int i;
    *maior = *vet;
    for(i = 1; i < tam; i++){
        if(*maior < *(vet + i))
            *maior = *(vet + i);
    }
}

int main() {

    int tam = 1;
    int i = 0;
    int maior;


    while (tam != 0 ) {


    scanf("%d", &tam);
        if (tam == 0) return 0;

    int v[tam];

    for (i = 0; i < tam; i++) {
        scanf("%d", &v[i]);
    }

    maiorN(v, tam, &maior);
    nums(v, tam, maior);
    }

}