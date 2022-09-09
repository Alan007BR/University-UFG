#include <stdio.h>
#define MAXQUEUE 50

typedef struct Queue {
    int tam[MAXQUEUE-1];
    int front, rear;
} Queue;

void create_queue(Queue *queue){
    queue->front = queue->rear = MAXQUEUE-1;
}

void insert(Queue *p, int x){
    if(p->rear == MAXQUEUE-1){
        p->rear = 0;
    } else{
        (p->rear)++;
    }

    if(p->rear == p->front){
        printf("vai estourar");
    }
    p->tam[p->rear] = x;
}

int empty_queue(Queue *p){
    return( p->front == p->rear) ? 0 : 1;
}

int main(){

    Queue p;
    int x = 10;
    int i = 0;

    p.front = p.rear = MAXQUEUE-1;
    //create_queue(p);
    empty_queue(&p) == 0 ? printf("vazia\n") : printf("cheia\n");

    for(i=0;i<MAXQUEUE-1;i++){
    insert(&p, x);
    }

    for(i = 0; i < MAXQUEUE-1; i++){
        printf("%d ", p.tam[i]);
    }
    return 0;
}