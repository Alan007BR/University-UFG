#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    struct Node *left, *right, *p;
} Node;

typedef struct Tree{
    Node *root;
} Tree;

Tree NewTree(){

    Tree tree;
    tree.root = NULL;
    return tree;
}

int treeSearch(Node *node, int k){
    while(node != NULL && k != node->key){
        if(k < node->key)
            node = node->left;
        else
            node = node->right;
        
        return node->key;
    }
}

int minimumKey(Node *node){
    while(node->left != NULL) node = node->left;

    return node->key;
}

int maximumKey(Node *node){
    while(node->right != NULL) node = node->right;

    return node->key;
}

void insert(Tree* tree, int key){
    Node* x = tree->root;
    Node* y = NULL;

    Node* z = (Node*)malloc(sizeof(Node)); //alloc new node z
    z->left = z->right = NULL; //define z childs and z key
    z->key = key;

    while(x != NULL){// find the last child of Tree
    y = x;
        if(z->key < x->key)
            x = x->left;
        else
            x = x->right;
        
    }
    z->p = y;// define y as parent of z-Node
    
    if(y == NULL){
        tree->root = z;
    }else if(z->key < y->key){
        y->left = z;
    }else {
        y->right = z;
    }

}

void delete(Tree *tree, int key){

}

void PreOrder(Node* node){ //recursive function
    
    if(node != NULL){
        printf("%d ", node->key);

        PreOrder(node->left);
        PreOrder(node->right);
    }

}

void freeTree(Node* node){
    if(node != NULL){
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

int main(){


    Tree tree = NewTree();

    insert(&tree, 10);
    insert(&tree, 20);
    insert(&tree, 7);
    insert(&tree, 13);

    PreOrder(tree.root);
    printf("\n");
    
    printf("The lowest num: %d\n", minimumKey(tree.root));
    printf("The biggest num: %d\n", maximumKey(tree.root));
    printf("num %d in %d\n", 20, treeSearch(tree.root, 20));
    
    
    freeTree(tree.root);
    return 0;
}