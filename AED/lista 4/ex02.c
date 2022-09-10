#include <stdio.h>

#define MAX 6001
typedef struct Fila {
    int tam[MAX];
    int front, rear;

} Fila;

insert(int x, Fila *fila){
    if(fila->rear == MAX-1){
        fila->rear = 0;
    }else{
        (fila->rear)++;
    }

    if(fila->rear == fila->front){ // ocorrencia de estouro
        return 0;
    }

    fila->tam[fila->rear] = x;

    return;
}


    int searchInVetor(int x, Fila *fila2){
        int i = 0;

        for(i = 0; i < fila2->rear - fila2->front + MAX; i++){
            if(fila2->tam[i] == x){
                return 1;
            }
        }

        return 0;
    }

int main(){

    int quat;
    int i = 0, x, j, k = 0;
    Fila fila;
    Fila fila2;
    fila.front = fila.rear = MAX-1;
    fila2.front = fila2.rear = MAX-1;

    scanf("%d", &quat);

    for(i = 0; i < quat; i++){
        scanf("%d", &x);
        insert(x, &fila);
    }

    scanf("%d", &x);
    for(i = 0; i < x; i++){
        scanf("%d", &j);
        insert(j, &fila2);
    }

    for(i = 0; i < fila.rear - fila.front + MAX; i++){
            if(searchInVetor(fila.tam[i], &fila2) == 0){
                printf("%d ", fila.tam[i]);
            }
    }
    printf("\n");


    return 0;
}