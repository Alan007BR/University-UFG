#include <stdio.h>
#include <stdlib.h>

int bubblesortPar(int *vector, int size){
    int i = 0;
    int j = 0;
    int tmp;

    for(i = 0; i < size; i++){
        for(j = 0; j < size-1; j++){
            if(vector[j] > vector[j+1]){
                tmp = vector[j];
                vector[j] = vector[j+1];
                vector[j+1] = tmp;
            }
        }
    }
}

int bubblesortImpar(int *vector, int size){
    int i = 0;
    int j = 0;
    int tmp;

    for(i = 0; i < size; i++){
        for(j = 0; j < size-1; j++){
            if(vector[j] < vector[j+1]){
                tmp = vector[j+1];
                vector[j+1] = vector[j];
                vector[j] = tmp;
            }
        }
    }
}

int main(){

    int *pares = NULL;
    int *impares = NULL;

    int n, aux;
    int i = 0, p = 0, k = 0;

    scanf("%d", &n);
    
    pares = (int*)malloc(n*sizeof(int));
    impares = (int*)malloc(n*sizeof(int));

    for (i = 0; i < n; i++) {
        scanf("%d", &aux);

        if(aux % 2 == 0){
            pares[p++] = aux;
        }else{
            impares[k++] = aux;
        }
    }
    if(p != 0){
    bubblesortPar(pares, p);
        for(i = 0; i < p; i++){
            printf("%d ", pares[i]);
        }
    }

    printf("\n");
    
    if(k != 0){
    bubblesortImpar(impares, k);
        for(i = 0; i < k; i++){
            printf("%d ", impares[i]);
        }
    }
    printf("\n");
    return 0;
}