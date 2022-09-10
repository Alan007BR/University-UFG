    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
     
    typedef struct People {
        int calls;
        char name[100];
        char number[100];
    } People;
     
    typedef struct Node {
        People people;
        struct Node *next;
        struct Node *prev;
    } Node;
     
    typedef struct list {
        Node *first;
        Node *last;
        int size;
     
    } list;
     
     
     
    void stringCopy(char **dest, char *src) {
        int size;
        
        *dest = NULL;
        size = strlen(src) + 1;
     
        *dest = (char *) malloc(size * sizeof(char));
        strcpy(*dest, src);
    }
     
    void freeNode(Node *node) {
        freePeople(&node->people);
        free(node);
    }
     
    void freePeople(People *p){
        free(p->number);
        free(p->name);
    }
     
     
    void insert(list *l, char *name, char *phone_number, int calls) {
        Node *new = NULL;
        Node *p = NULL;
     
        new = (Node *) malloc(sizeof(Node));
        if(new == NULL) return 0;
     
        strcpy(new->people.name, name);
        strcpy(new->people.number, phone_number);
        new->people.calls = calls;
     
            if(l->size == 0) {
                l->first = new;
            }else {
                l->last->next = new;
            }

            l->last = new;
            new->prev = l->last;
            new->next = NULL;
            l->size++;        
    }
     
    bool removeList(list *l, char *name) {
        Node * p = NULL;
        Node * prev = NULL;
     
        for(p = l->first; p != NULL; prev = p, p = p->next) {
        if(strcmp(p->people.name, name) == 0) {
            if(l->size == 1) {
                freeList(l);
                return true;
            }

            if(p == l->first) l->first = p->next;
            else if(p == l->last) l->last = p->prev;
            else {
                p->prev->next = p->next;
                p->next->prev = p->prev;
            } 

            l->first->prev = NULL;
            l->last->next = NULL;
            l->size--;

            free(p);


            return true;
        }
        }
     
        return false;
    }
     
     
    list newList(){
        list p;
        p.first = NULL;
        p.last = NULL;
        p.size = 0;
     
        return p;
    }
     
    void freeList(list *l) {
        Node * p = NULL;
        Node * tmp = NULL;
     
        for(p = l->first; p != NULL; p = tmp) {
            tmp = p->next;
            free(p);
        }
        *l = newList();
    }
     
    Node *search(list *list, char *name){
        Node *p = NULL;
     
        for(p = list->first; p != NULL; p = p->next){
            if(strcmp(p->people.name, name) == 0){
                return p;
            }
        }
     
        return false;
    }
     
    void print(list *list){
        Node *p = NULL;
     
        for(p = list->first; p != NULL; p = p->next){
            printf("%s - %s %d\n", p->people.name, p->people.number, p->people.calls);
        }
    }
    void copyPerson(People *dest, People src) {
    dest->calls = src.calls;
    strcpy(dest->name, src.name);
    strcpy(dest->number, src.number);
    }

    void sort(list *list){
        Node *p = NULL, *q = NULL, *m = NULL;
        People tmp;

        for(p = list->first; p != NULL; p = p->next){
            m = p;

            for(q = p->next; q != NULL; q = q->next){
                if(q->people.calls > m->people.calls){
                    m = q;
                }
                if(m !=p){
            copyPerson(&tmp, p->people);
            copyPerson(&p->people, m->people);
            copyPerson(&m->people, tmp);
                }
            }
        }
    }
     
    int main(){
            
        list list;
        char option, name[100], number[100];
        int v;
        Node *aux = NULL;
     
        list = newList();
        insert(&list, "Hermanoteu", "4523-2248", 300);
        insert(&list, "Ooloneia", "4523-4887", 299);
     
        while(1){
     
            scanf("%c", &option);

            switch (option){
     
            case 'I':
                scanf("%s %s %d",&name, &number, &v);
                insert(&list, name, number, v);
                break;
            case 'R':
                scanf("%s", name);
                removeList(&list, name);
                break;
            case 'L':
                scanf("%s", name);
                aux = search(&list, name);
                if(aux != NULL) aux->people.calls++;
                break;
            case 'F':
                sort(&list);
                print(&list);
                freeList(&list);
                return 0;
            }
        }
    }