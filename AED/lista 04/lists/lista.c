#include <stdio.h>
#include <stdbool.h>
#include "list.c"

typedef struct NodeV { //lista estática
    int info, next;
};


typedef struct Node { //lista dinâmica
    int info;
    struct Node *next;

} Node;

typedef struct List{ //edereçador da lista (opcional)
    Node *first;
    Node *last;
    int size;
}List;


Node newList(){
    Node *p;
    p = (Node *)malloc(sizeof(Node));

    return p;
}

void freeNode(Node p){
    free(p);
}


int main(){

    Node p;
    p = newList();


    freeNode(p);
    return 0;
}