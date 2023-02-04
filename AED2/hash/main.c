#include "hash.c"

void option(){
    printf("1 - criar a tabela Hash");
    printf("2 - mostrar dados da tabela hash");
    printf("3 - destrua a tabela Hash");
    printf("4 - Cardinalidade da Tabela Hash");
    printf("5 - Insere um Elemento na tabela Hash");    
    printf("6 - Procurar uma chave x na tabela Hash");
    printf("7 - Remover um Elemento na tabela Hash");
    printf("8 - finalizar programa");

}

int main(){

    hashTable *T = MakeTable();
    double aux;

    InsertTable(T, 0.000001, "value1");
    InsertTable(T, 99999999.999999, "value2");
    InsertTable(T, 10, "value3");
    InsertTable(T, 1212, "value4");
    
    SearchTable(T, 10);

    printf("%d\n", SizeTable(T));
    RemoveTable(T, 10);
    ShowTable(T);


    DestroyTable(T);
    return 0;
}