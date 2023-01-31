#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 5
#define ERROR -1

typedef struct Node {

    double key;
    char *value;
    int tam;

    struct Node *next;
    struct Node *pred; //duplamente encadeada, pois a tabela terá que suportar eliminação de elementos

} Node;


typedef struct hashTable{    
    Node **table;
}   hashTable;

double hash( double key);
hashTable *MakeTable();
void ShowTable(struct hashTable* T);
void DestroyTable(hashTable* T);
int SizeTable(hashTable* T);
void InsertTable(hashTable* T, double x, char *value);
void SearchTable(hashTable* T, double x);
void RemoveTable(hashTable* T, double x);