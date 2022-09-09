#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
typedef struct Node {
    char name[MAX];
    struct Node* next;
    struct Node* prev;
}   Node;

typedef struct List {
    Node *first;
    Node *last;
    int size;
} List;

List newList(){
    List p;
    p.first = NULL;
    p.last = NULL;
    p.size = 0;

    return p;
}

int insert(List *list, char *x){
    Node *new = NULL;

    new = (Node *)malloc(sizeof(Node));

    strcpy(new->name, x);

    if(list->size == 0){
        list->first = new;
        list->last = new;
        
        new->next = list->first; // como estamos lidando com um circulo, o próximo do último vai ser o primeiro
        new->prev = list->last;

        list->size++;

        return 1;
    }

    list->last->next = new;
    list->first->prev = new;
    new->next = list->first; // como estamos lidando com um circulo, o próximo do último vai ser o primeiro
    new->prev = list->last;
    list->last = new;
    list->size++;

    return 1;
}

int removeList(List *list, char *name){
    Node *p;
    int i = 0;

    if(list->size == 1){
        if(strcmp(list->first->name, name) == 0){
            freeList(list);
            return 1;
        }
    }

    for(p = list->first, i = 0; i < list->size; p = p->next, i++){
        if(strcmp(p->name, name) == 0){
            p->prev->next = p->next;
            p->next->prev = p->prev;

            if(p == list->last) list->last = p->prev;
            if(p == list->first) list->first = p->next;

            list->size--;
            free(p);
            return 1;
        }
    }

    return 0;
}

void freeList(List *list){
    Node *p;
    Node *tmp;
    int i = 0, size = list->size;
    for(p = list->first, i = 0; i < size; p = tmp, i++){
        tmp = p->next;
        free(p);
    }

    list->first = NULL;
    list->last = NULL;
    list->size = 0;
}
int main(){
    List listCircle;
    Node *p = NULL;
    int x;
    int netos = 0, score = 0, i = 0;
    char aux[MAX], aux2[MAX];

    listCircle = newList();
    insert(&listCircle, "Vovo");

    while(1){
        scanf("%s%*c", aux);
        if(strcmp(aux, "FIM") != 0){
            insert(&listCircle, aux);
            netos++;
        }else{
            break;
        }
    }

    while(netos > 0){
        scanf("%s%*c", aux);
        scanf("%s%*c", aux2);

        if(strcmp(aux2, "horario") == 0){
            for(p = listCircle.first->next, i = 0; i < 2; p = p->next, i++){
                if(strcmp(p->name, aux) == 0){
                    removeList(&listCircle, p->name);
                    score++;
                    break;
                }
            }
        }else if(strcmp(aux2, "anti-horario") == 0){
            for(p = listCircle.last, i = 0; i < 2; p = p->prev, i++){
                if(strcmp(p->name, aux) == 0){
                    removeList(&listCircle, p->name);
                    score++;
                    break;
                }
            }        
        }

        netos--;
    }

    printf("%d\n", score);
    freeList(&listCircle);

    return 0;
}