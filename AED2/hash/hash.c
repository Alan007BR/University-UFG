#include "hash.h"


double hash(double x){

    char* str = (char*) &x;
    unsigned int h = 5381;
    for (int i = 0; i < sizeof(double); i++)
        h = ((h << 5) + h) + str[i];

    return h % HASH_SIZE;
}

hashTable *MakeTable(){

    int i = 0;
    hashTable *T = (Node *)malloc(sizeof(Node));  //aloca a hash principal

    T->table = (Node **)malloc(HASH_SIZE * sizeof(Node*)); //aloca os demais nós da hash (50 m)

    for(i = 0; i < HASH_SIZE; i++){ //define todos como NULL
        T->table[i] = NULL;
    }

    return T;
}

int SizeTable(hashTable* T){
    Node *aux;
    int i = 0, count = 0;

    for(i = 0; i < HASH_SIZE; i++){
        if(T->table[i] != NULL){
            count += T->table[i]->tam;
        }
    }

    return count;
}

void InsertTable( hashTable* T, double key, char *value){  
    unsigned int index = hash(key); //hashing function

    Node *n = (Node *)malloc(sizeof(Node));

    n->key = key;
    n->value = strdup(value);
    //strcpy(n->value, value);
    n->next = T->table[index];
    n->pred = NULL;

    if(T->table[index] != NULL)
        T->table[index]->pred = n;
    else
        T->table[index] = n;

    if(T->table[index] != NULL){
        T->table[index]->tam++;
    }else{
    T->table[index]->tam = 0;
    }
}

void SearchTable(struct hashTable* T, double key){
    Node *aux, *print;
    int i = 0;

    for(i = 0; i < HASH_SIZE; i++){
        aux = T->table[i];

        if(aux != NULL && aux->key == key){
            printf("|%lf| :\n", aux->key);
            print = aux;
            while(print != NULL){

                printf("%s, ",print->value);
                print = print->pred;
            }
            printf("\n===\n");
            break;
        }
    }
    return ERROR;
}

void RemoveTable(hashTable* T, double key){
    int i = 0;
    Node *aux, *now;

    for(i = 0; i < HASH_SIZE; i++){
        if(T->table[i] != NULL && T->table[i]->key == key){
            aux = T->table[i];
            while(aux != NULL){
                now = aux;
                aux->value = NULL;
                aux->key = -1;
                aux = NULL;
                aux = now->pred;
            }
            T->table[i]->tam = 0;
        }
    }

}

void ShowTable(struct hashTable* T){
    int i = 0, j = 0;
    Node *aux, *print;

    for(i = 0; i < HASH_SIZE; i++){
        aux = T->table[i];

        if(aux != NULL && aux->key != -1){
            printf("%lf = ", aux->key);
            
            print = aux;
            while(print != NULL){
                printf("%s, ", print->value);
                print = print->pred;
            }
            printf("\n");
        }

    }
        printf("\n");
}


void DestroyTable(hashTable* T){
    int i = 0;
    Node* aux, *now;

    for(i = 0; i < HASH_SIZE; i++){
        now = T->table[i];
            while(now != NULL){
                aux = now;
                now = now->next;
                free(aux);
            }
    }
    free(T->table);
    free(T);
}