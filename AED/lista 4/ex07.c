#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int info; 
    struct Node *next;
} Node;

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

void print(List *list){
    Node *p;

    for(p = list->first; p != NULL; p = p->next){
        printf("%d ", p->info);
    }

    printf("\n");

    if(list->size == 0){
        printf("lista vazia\n");
    }
}

int insert(List *list, int x){
    Node *new = NULL;

    new = (Node *)malloc(sizeof(Node));
    if(new == NULL){ printf("failed to allocate memory\n"); return -1; }

    new->info = x;
    
    new->next= NULL;
    if(list->first == NULL) list->first = new;
    else list->last->next = new;

    list->last = new;
    list->size++;

}

int insertInList(List *list, int peopleP, int peopleE){
    Node *new = NULL;
    Node *p = NULL;

    new = (Node *)malloc(sizeof(Node));
    if(new == NULL){ printf("failed to allocate Memory"); return -1; }

    new->info = peopleP;

    for(p = list->first; p != NULL; p = p->next){
        if(p->info == peopleE){
            new->next = p->next;
            p->next = new;
            
            if(new->next == NULL) list->last = new;
            
            list->size++;
            return 1;
        }
    }

    return 0;
    
}

int removeList(List *list, int x){
    Node *p = NULL;
    Node *prev = NULL;

    for(p = list->first; p != NULL; prev = p, p = p->next){
        if(p->info == x){
            if(list->size == 1){ //caso tenha um único elemento da lista
                list->first = NULL;
                list->last = NULL;
            }else if(p == list->first){ // p for o primeiro
                list->first = p->next;
            }else if(p == list->last){ // p for o último
                list->last = prev;
                list->last->next = NULL;
            }else { // se não for o primeiro nem o último e tiver mais que um
                prev->next = p->next;
            }

            free(p);
            return 1;
        }
    }
    return 0;
}

int searchQuantity(List *list, int first, int last){
    Node *p = NULL;
    int i = 0;
    Node *firstFinded = NULL;
    int count = 0;

    for(p = list->first; p != NULL; p = p->next){
        if(p->info == first || p->info == last){
            firstFinded = p;
            break;
        }
    }

    for( p = firstFinded; p != NULL; p = p->next){
        count++;

        if(firstFinded->info == last){
            if(p->info == first){
                break;
            }
        }else if(firstFinded->info == first) {
            if(p->info == last){

                break;
            }
        }
    }

    return count-2;
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
int main(){

    int aux, aux2;
    int i = 0;
    char option;
    List list;

    list = newList();

    scanf("%d", &aux);
    for(i = 0; i < aux; i++){
        scanf("%d", &aux2);
        insert(&list, aux2);
    }

    while(1){
        scanf("%c", &option);
        switch (option){
        case 'I':
            scanf("%d", &aux);
            scanf("%d", &aux2);
            insertInList(&list, aux, aux2) == 1 ? printf("inserido %d\n", aux) : printf("error");
            break;
        case 'R':
            scanf("%d", &aux);
            removeList(&list, aux) == 1 ? printf("removido %d\n", aux) : printf("error");
            break;
        case 'C':
            scanf("%d", &aux);
            scanf("%d", &aux2);
            printf("quantidade %d\n" ,searchQuantity(&list, aux, aux2));
            break;
        case 'M':
            printf("lista ");
            print(&list);
            break;
        case 'F':
            printf("fim\n");
            freeList(&list);
            return 0;
            break;
        default:
            break;
        }
    }
    freeList(&list);
    return 0;
}