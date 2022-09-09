#include <stdio.h>

#define MAX 31
typedef struct Node{
    char name[MAX];
    int number;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct List {
    Node* first;
    Node* last;
    int size;
} List;

List newList(){
    List p;
    p.first = NULL;
    p.last = NULL;
    p.size = 0;

    return p;
}

int insertList(List *list, char *x, int number){
    Node *new = NULL;

    new = (Node *)malloc(sizeof(Node));

    strcpy(new->name, x);
    new->number = number;

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
    Node *p = NULL;
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
    Node *p = NULL;
    Node *tmp = NULL;
    int i = 1, size = list->size;
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
    int n, end;
    char auxName[MAX];
    int auxNumber;
    int i = 0;

    listCircle = newList();

    scanf("%d", &n);    

    for(i = 0; i < n; i++){
        scanf("%s%*c%d%*c", &auxName, &auxNumber);
        insertList(&listCircle, auxName, auxNumber);  
    }

    end = listCircle.first->number;

    while(listCircle.size > 1){
        if(end % 2 == 0){ // se o num for par, vai começar no sentido horário
            p = listCircle.last;
            for(i = 1; i < end; i++){
                p = p->prev;
            }
        } else{ // sentido anti-horário
            p = listCircle.first->next;
            for(i = 1; i < end; i++){
                p = p->next;
            }
        }

        end = p->number;
        removeList(&listCircle, p->name);
    }

    printf("%s\n", listCircle.first->name);
    freeList(&listCircle);

    return 0;
}