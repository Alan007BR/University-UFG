#include <stdio.h>
#include <stdlib.h>

#define MAX 1001

static int selection = 0;
static int insertion = 0;

void insertionSort(int *vector, int n){
    int i = 1, j = 0, aux;

    for(i = 1; i < n; i++){
        aux = vector[i];
        for(j = i-1; j>= 0 &&  aux < vector[j] ; j--){// < ou >
            vector[j+1] = vector[j];
            insertion++; //troca

        }
        vector[j+1] = aux;
        insertion++; //troca
    }
}

void selectionSort(int *vector, int n){
    int i= 0, j = 0, aux;
    int min;

    for(i = 0; i < n-1; i++){ //for de cada elemento do vetor desorganizado
        min = i;    //achar o elemento mínimo
        for(j = i+1; j < n; j++){ // < ou > para decrescente ou crescente
            if(vector[j] < vector[min]){
                min = j;
            }
        }
        if(vector[i] != vector[min]){ // realizar a troca
            aux = vector[i];
            vector[i] = vector[min];
            vector[min] = aux;
            selection++; //troca
        }
    }
}

int main(){

    int vector[MAX], vector2[MAX];
    int n, i = 0;


    scanf("%d", &n);
    for(i = 0; i < n; i++){
        scanf("%d", &vector[i]);
        vector2[i] = vector[i];
    }
        
    insertionSort(vector, n);
    selectionSort(vector2, n);

    printf("%d", insertion - selection);
    return 0;
} 