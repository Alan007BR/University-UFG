#include "binarytree.c"


int main(){


    Tree tree = NewTree();

    insert(&tree, 10);
    insert(&tree, 20);
    insert(&tree, 7);
    insert(&tree, 13);
    insert(&tree, 15);
    insert(&tree, 8);

    preOrder(tree.root);
    printf("\n");
    
    printf("The lowest num: %d\n", minimumKey(tree.root)->key);
    printf("The biggest num: %d\n", maximumKey(tree.root)->key);
    //printf("num %d in %d\n", 8, treeSearch(tree.root, 8));
    
    treeDelete(tree.root, 13);

    preOrder(tree.root); printf("\n");
    inOrder(tree.root); printf("\n");
    postOrder(tree.root); printf("\n");

    printf("%d\n", tree.root->key);    
    freeTree(tree.root);
    
    return 0;
}