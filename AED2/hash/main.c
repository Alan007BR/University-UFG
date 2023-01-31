#include "hash.c"

int main(){

    hashTable *T = MakeTable();
    double aux;

    InsertTable(T, 11, "value1");
    InsertTable(T, 10, "value2");
    InsertTable(T, 10, "value3");
    InsertTable(T, 1212, "value4");
    
    SearchTable(T, 10);

    printf("%d\n", SizeTable(T));
    RemoveTable(T, 10);
    ShowTable(T);


    DestroyTable(T);
    return 0;
}