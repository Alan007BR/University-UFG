#include <stdio.h>
#define TAM 10

void insertionSort(int *vector){
    int i = 1, j = 0, aux;

    for(i = 1; i < TAM; i++){
        aux = vector[i];
        for(j = i-1; j>= 0 && vector[j] < aux; j--){// < ou >
            vector[j+1] = vector[j];
        }
        vector[j+1] = aux;
    }
}

void selectionSort(int *vector, int n){
    int i= 0, j = 0, aux;

    for(i = 0; i < n-1; i++){
        
    }
}

int main(){

    int vector[TAM];

    for(int i = 0; i < TAM; i++){
        scanf("%d", &vector[i]);
    }

    insertionSort(vector);

    for(int i = 0; i < TAM; i++){
        printf("%d\n", vector[i]);
    }
    return 0;
} 