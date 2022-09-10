void bubblesort(int *vector, int size){
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
        }
    }
}