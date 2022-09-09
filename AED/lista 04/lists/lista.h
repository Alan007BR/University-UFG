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

List *createNewList();
int addInListInitial(List * l, int x);
int addInListFInal(List * l, int x);
int removeInList(List * l, int x);
int SearchInList(List * l, int x);
void print(List * l);
void freeList(List * l);