#include <stdio.h>

typedef struct Node {
    char info[21];
    struct Node *next;
} Node;

typedef struct list {
    Node *first;
    Node *last;
    int size;
} list;

list newStack(){

    list p;
    p.first = NULL;
    p.last = NULL;
    p.size = 0;

    return p;
}

void freeList(list *list){
    Node *p = NULL;
    Node *tmp = NULL;

    for(p = list->first; p != NULL; p = tmp){
        tmp = p->next;
        free(p);
    }

    list->first = NULL;
    list->last = NULL;
    list->size = 0;
}

int up(list *list, char *info){
    Node *new = NULL;

    new = (Node *)malloc(sizeof(Node));
    if(new == NULL){ printf("Memory allocation failed\n"); return -1; }

    strcpy(new->info, info);
    new->next = NULL;

    if(list->first == NULL) list->first = new;
    if(list->last != NULL) list->last->next = new;
    list->last = new;
    list->size++;

    return;
}

int un(list *list,  char *last){
    Node *p = NULL;

    if(list->size == 0) return -1;

    if(list->size == 1){
        strcpy(last, list->first->info);
        freeList(list);
        return;
    }

    for(p = list->first; p->next != list->last; p = p->next);

    p->next = NULL;
    strcpy(last, list->last->info);
    free(list->last);
    list->last = p;
    list->size--;

    return;

}

int main(){

    list stack;
    stack = newStack();

    char instruction[21];

    while (strcmp(instruction, "ESCOLA") != 0){
        scanf("%s", instruction);

        up(&stack, instruction);
    }
    
    while(stack.size != 0){
        un(&stack, instruction);

        if(strcmp(stack.last->info, "ESQUERDA") == 0) printf("Vire a DIREITA ");
        else{
        printf("Vire a ESQUERDA ");
        }

        un(&stack, instruction);
        if(stack.size >=1){
        printf("na rua %s.\n", stack.last);
        }else{
        printf("para chegar em CASA.\n");
        }
    }

    return 0;
}