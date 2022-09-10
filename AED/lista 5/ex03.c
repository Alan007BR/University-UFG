#include <stdio.h>

#define MAX 1001

void insertionSort(int *vector, int n){
    int i = 1, j = 0, aux;

    for(i = 1; i < n; i++){
        aux = vector[i];
        for(j = i-1; j>= 0 &&  aux < vector[j] ; j--){// < ou >
            vector[j+1] = vector[j];
        }
        vector[j+1] = aux;
    }
}

int main(){

    int vector[MAX];
    int n, l, k, i = 0;

    scanf("%d", &n);

    for(i = 0; i < n; i++){
        scanf("%d", &vector[i]);
    }
    
    scanf("%d %d", &l, &k);

    insertionSort(vector, n);
    printf("%d\n", vector[l-1] + vector[k-1]);

    return 0;
}