#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 50000000
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

double hash( double key);  //hash function
hashTable *MakeTable(); //criar a tabela Hash
void ShowTable(struct hashTable* T); //mostrar dados da tabela hash
void DestroyTable(hashTable* T); //destrua a tabela Hash
int SizeTable(hashTable* T); //Cardinalidade da Tabela Hash
void InsertTable(hashTable* T, double x, char *value); //Insere um Elemento na tabela Hash
double SearchTable(hashTable* T, double x); //Procurar uma chave x na tabela Hash
void RemoveTable(hashTable* T, double x); //Remover um Elemento na tabela Hash