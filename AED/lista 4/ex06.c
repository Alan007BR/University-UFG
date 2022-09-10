#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1000

typedef struct Node {
    char par;
    struct Node* next;
} Node;

typedef struct Stack {
    Node *first;
    Node *last;
    int size;
} Stack;

Stack newStack(){
    Stack s;

    s.first = NULL;
    s.last = NULL;
    s.size = 0;

    return s;
}

void freeList(Stack *list){
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

int up(Stack *list, char info){
    Node *new = NULL;

    new = (Node *)malloc(sizeof(Node));
    if(new == NULL){ printf("Memory allocation failed\n"); return -1; }

    new->par = info;
    new->next = NULL;

    if(list->first == NULL) list->first = new;

    if(list->last != NULL) list->last->next = new;

    list->last = new;
    list->size++;

    return 1;
}

char un(Stack *l){
    Node *p = NULL;
    int last;

    if(l->size == 0) return -1;

    if(l->size == 1) {
        last = l->first->par;
        freeList(l);
        return last;
    }

    for(p = l->first; p->next != l->last; p = p->next);

    p->next = NULL;
    last = l->last->par;
    free(l->last);
    l->last = p;
    l->size--;

    return last;
}

bool balanceamento(char *str) {
    Stack stack;
    char last;
    int i;
    bool correct;

    stack = newStack();
    correct = true;
    i = 0;
    while(str[i] != '\0') {
        if(str[i] == '(') up(&stack, str[i]);

        if(str[i] == ')') {
            last = un(&stack);
            if(last != '(') {
                correct = false;
                break;
            }
        }

        i++;
    }

    if(stack.size != 0) correct = false;
    freeList(&stack);

    return correct;
}

bool tabelaDePrioridade(char c, char t){
    int pc, pt;

    if(c == '^') pc = 4;
    else if(c == '*' || c == '/') pc = 2;
    else if(c == '+' || c == '-') pc = 1;
    else if(c == '(') pc = 4;

    if(t == '^') pt = 3;
    else if(t == '*' || t == '/') pt = 2;
    else if(t == '+' || t == '-') pt = 1;
    else if(t == '(') pt = 0;

    return (pc > pt);
}

void AfterSentence(char *infix, char *before) {
    Stack p;
    int i, j;
    char c, t;

    memset(before, '\0', MAX);
    p = newStack();
    up(&p, '(');

    i = 0;
    j = 0;
    do {
        c = infix[i];
        i++;
        if(isalnum(c)){
            before[j] = c;
            j++;
        } else if(c == '(') {
            up(&p, '(');
        } else if(c == ')' || c == '\0') {
            do {
                t = un(&p);
                if(t != '(') {
                    before[j] = t;
                    j++;
                }
            } while(t != '(');
        } else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            while(true) {
                t = un(&p);
                if(tabelaDePrioridade(c, t)) {
                    up(&p, t);
                    up(&p, c);
                    break;
                }

                before[j] = t;
                j++;
            }
        }
    } while(c != '\0');

    freeList(&p);
}

int main(){

    char aux[MAX], aux2[MAX];
    int cases;
    int i = 0, j = 0;

    scanf("%d%*c", &cases);

    for(j = 0; j < cases; j++) {
        scanf("%[^\n]%*c", aux);

        if(balanceamento(aux) == 0) {
            printf("mal-formada\n");
            continue;
        }

        AfterSentence(aux, aux2);
        i = 0;
        while(aux2[i] != '\0') {
            if(aux2[i+1] == '\n') printf("%c", aux2[i]);
            else printf("%c ", aux2[i]);
            i++;
        }
        printf("\n");
    
    }

    return 0;
}