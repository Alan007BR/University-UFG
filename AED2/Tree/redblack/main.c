#include "redblack.c"

void opti(){
    printf("1- adicionar um dado a arvore\n");
    printf("2- remover dado a arvore\n");
    printf("3- achar maior dado na arvore\n");
    printf("4- achar menor dado na arvore\n");
    printf("5- procurar um dado na arvore\n");
    printf("6- printar inorder\n");
    printf("7- printar preorder\n");
    printf("8- printar postorder\n");
    printf("9- sair\n");
    printf("\n");
}

int main(){

    Tree *tree = NewTree();
    Node *temp, temp2;
    int option, t;

    while(1){

        opti();
        scanf("%d", &option);
        switch (option){
        case 1:

            printf("\n");
            printf("Digite o numero do novo no: ");
            scanf("%d", &t);
            insert(tree, t);
            
            inOrder(tree->root); printf("\n");
            break;
        case 2:

            printf("\n");
            printf("Digite a chave do no que deseja remover: ");
            scanf("%d", &t);
            temp = findNode(tree, tree->root, t);
            if(temp->key != NULL){
            
            delete(tree, temp);
            }else{
                printf("nao encontrado\n");
            }
            printf("\n");
            
            inOrder(tree->root); printf("\n");
            break;
        case 3:

            printf("\n");
            temp = maximumKey(tree, tree->root);
            printf("maximo: %d\n", temp->key);
            break;
        case 4:

            printf("\n");
            temp = minimumKey(tree, tree->root);
            printf("minimo: %d\n", temp->key);
            break;
        case 5:

            printf("\n");
            printf("Digite a chave do no que deseja procurar: ");
            scanf("%d", &t);
            temp = findNode(tree, tree->root, t);
            if(temp->key == t){
            printf("%d ", temp->key);
            printf("encontrado\n");
            }else{
                printf("nao encontrado\n");
            }
            break;
        case 6:
            
            inOrder(tree->root); printf("\n");
            printf("\n");
            break;
        case 7:
            
            preOrder(tree->root); printf("\n");
            printf("\n");
            break;
        case 8:
            
            postOrder(tree->root); printf("\n");
            printf("\n");
            break;
        case 9:
            
            freeTree(tree->root);
            return 0;
            break;
        
        default:
            break;
        }
    }
    return 0;
}