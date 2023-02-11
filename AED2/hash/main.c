#include "hash.c"

void option(){
    printf("\n");
    printf("1 - criar a tabela Hash\n");
    printf("2 - mostrar dados da tabela hash\n");
    printf("3 - destrua a tabela Hash\n");
    printf("4 - Cardinalidade da Tabela Hash\n");
    printf("5 - Insere um Elemento na tabela Hash\n");    
    printf("6 - Procurar uma chave x na tabela Hash\n");
    printf("7 - Remover um Elemento na tabela Hash\n");
    printf("8 - finalizar programa\n");
    printf("\n");
}

int main(){


    double aux;
    char aux2[128];
    int opt;

    while(1){
        option();
        scanf("%d",&opt);
        switch (opt){
        case 1:
            
            hashTable *T = MakeTable();
            break;
        case 2:
            ShowTable(T);
            break;
        case 3:
            DestroyTable(T);
            break;
        case 4:
            printf("%d\n", SizeTable(T));
            break;
        case 5:
            printf("tecle '-1' para terminar a execucao\n padrao: \n(chave)\n(dado-satelite)\n");
            while(aux != -1){

                scanf("%lf", &aux);
                scanf("%s", &aux2);

            if(searchX(T, aux) == ERROR){
                printf("essa chave ja existe dentro da tabela\n");
                continue;
            }
            
                InsertTable(T, aux, aux2);
            }
            break;
        case 6:
            scanf("%lf", &aux);
            SearchTable(T, aux);
            break;

        case 7:
            scanf("%lf", &aux);
            RemoveTable(T, aux);
            break;
        case 8:
            if(T->table != NULL){
                DestroyTable(T);
            }
            return 0;
            break;
        
        default:
            break;
        }
    }

    return 0;
}