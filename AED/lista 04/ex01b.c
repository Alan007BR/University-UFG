#include <stdio.h>

typedef struct Paciente {
    int CheckInTime;
    int criticalTimeout;
} Paciente;

typedef struct Node {
    Paciente p;
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

int insert(List *list, int h, int m, int c){
    Node *newNode = NULL;
    newNode = (Node *)malloc(sizeof(Node));
    if(newNode == NULL){ printf("Error"); return NULL; }

    newNode->p.criticalTimeout = c;
    newNode->p.CheckInTime = (h * 60) + m;

    if(list->size == 0) list->first = newNode;
    else list->last->next = newNode;

    list->last = newNode;
    newNode->next = NULL;

    list->size++;

    return 1;
}

Paciente unStack(List *list) {
    Node *tmp = NULL;
    Paciente p;

    tmp = list->first;
    list->first = list->first->next;
    p = tmp->p;
    free(tmp);
    list->size--;

    return p;

}


void freeList(List *list) {
    Node *p = NULL;
    Node *aux = NULL;

    for(p = list->first; p != NULL; p = aux){
        aux = p->next;
        free(p);
    }

    list->first = NULL;
    list->last = NULL;
    list->size = 0;

}

int main(){

    List list;
    int n, h, m, c;
    int i = 0;
    int hours;
    int flag = 0;
    Paciente tmp;

    list = newList();

    scanf("%d", &n);

    while (n--){
        scanf("%d %d %d", &h, &m, &c);
        insert(&list, h, m, c);       
    }

    tmp = unStack(&list);
    hours = tmp.CheckInTime + 30;

    while(list.size > 0){
        tmp = unStack(&list);

        if(tmp.CheckInTime > hours){
            hours = tmp.CheckInTime + 30;
            continue;
        }

        if(hours > tmp.CheckInTime + tmp.criticalTimeout){
            flag++;
        }
        hours +=30;
    }

    printf("%d\n", flag);
    freeList(&list);

    return 0;
}