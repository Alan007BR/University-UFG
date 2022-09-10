#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int info;
    struct Node *next;
} Node;

typedef struct List {
    Node *first, *last;
    int size;
} List;

List newStack(){
    List p;

    p.first = NULL;
    p.last = NULL;
    p.size = 0;

    return p;
}

void freeList(List *list){
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

int up(List *list, int info){
    Node *new = NULL;

    new = (Node *)malloc(sizeof(Node));
    if(new == NULL){ printf("Memory allocation failed\n"); return -1; }

    new->info = info;
    new->next = NULL;

    if(list->first == NULL){
        list->first = new;
    }

    if(list->last != NULL){
        list->last->next = new;
    }

    list->last = new;
    list->size++;

    return 1;
}
int un(List *list){
    Node *p = NULL;
    int last;

    if(list->size == 0) return 0;
    
    if(list->size == 1){
        last = list->first->info;
        freeList(list);
        return last;
    }

    for(p = list->first; p->next != list->last; p = p->next);
        p->next = NULL;
        last = list->last->info;
        free(list->last);
        list->last = p;
        list->size--;

        return last;
    
}

int main(){

    char str[1001], last;
    List stack; //pilha
    int i = 0;
    
    stack = newStack();
    scanf("%[^\n]%*c", str);

    for(i = 0; str[i] != '\0'; i++){
        if(str[i] == '(') up(&stack, str[i]);
        if(str[i] == ')'){
            last = un(&stack);
            if(last != '('){
                printf("incorreta\n");
                freeList(&stack);
                return 0;
            }
        }
    }

    printf("correta\n");
    freeList(&stack);
    return 0;
}