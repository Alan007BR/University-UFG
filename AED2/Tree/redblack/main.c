#include "redblack.c"

int main(){

    Tree *tree = NewTree();
    Node *temp;

    insert(tree, 10);
    printf("%d\n", tree->root->key);
    insert(tree, 20);
    insert(tree, 7);
    insert(tree, 13);
    insert(tree, 15);
    insert(tree, 8);
    inOrder(tree->root);
    printf("\n");
    printf("%d\n", treeHeight(tree->root));

    delete(tree, findNode(tree, tree->root, 15));
    delete(tree, findNode(tree, tree->root, 7));

    delete(tree, findNode(tree, tree->root, 10));
    
    inOrder(tree->root);
    printf("\n");

    
    printf("\n");
    temp = maximumKey(tree, tree->root);
    printf("MAX: %d\n", temp->key);
    temp = minimumKey(tree, tree->root);
    printf("MIN: %d\n", temp->key);

    inOrder(tree->root); printf("\n");
    preOrder(tree->root); printf("\n");
    postOrder(tree->root); printf("\n");

    freeTree(tree->root);
    return 0;
}