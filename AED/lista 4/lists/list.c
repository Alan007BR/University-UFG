#include "lista.h"

List *createNewList(){

    List *p = (List *)malloc(sizeof(List));
    if(p != NULL){
        p->first = p->last = NULL;
        p->size = 0;
    }
    return p;
}
void freeList(List * l){
    if(l != NULL){
        Node * no;

        while((l->first) != NULL){
            no = l->first;
            l->first = l->first->next;
            free(no);
        }
        free(l);
    }
}
int addInListInitial(List * l, int x) {
    if(l == NULL){
        return 0;
    }
    Node *no = (Node *)malloc(sizeof(Node));
    if(no == NULL){
        return 0;
    }

    no->info = x;
    no->next = l->first;
    if(l->first == NULL)
    l->last = no;
    l->first = no;
    l->size++;
    return 1;
}

int addInListFInal(List * l, int x){
    if(l == NULL) return 0;
    Node *no = (Node *)malloc(sizeof(Node)); // criando novo laço (nó)
    if(no == NULL) return 0;

    no->info = x; //novo nó recebendo a informação
    no->next = NULL; // já que é o final, no->next tem que ser NULL
    
    if(l->first == NULL) l->first = no; //lista vazia, insere no início
    else
    l->last->next = no; //o final da lista passa a apontar pro nó
    l->last = no;   //mudar o descritor para apontar o final pro nó
    l->size++;  //aumentar a quantidade de nó (elementos) no descritor
    return 1;

}

void print(List * l) {
    Node *p = NULL;

    for(p = l->first; p != NULL; p = p->next){
        printf("%d\n", p->info);
    }
}