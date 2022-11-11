#include "binarytree.h"

Tree NewTree(){

    Tree tree;
    tree.root = NULL;
    return tree;
}

Node* treeSearch(Node *node, int k){
    while(node != NULL && k != node->key){
        if(k < node->key)
            node = node->left;
        else
            node = node->right;
        
    }
        return node;
}

Node* minimumKey(Node *node){
    while(node->left != NULL) node = node->left;

    return node;
}

Node* maximumKey(Node *node){
    while(node->right != NULL) node = node->right;

    return node;
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

void transplant(Tree *tree, Node *node1, Node *node2){

    if(node1 == tree->root){
        tree->root = node2;
    }

    if(node1->p == NULL){
        tree->root = node2;
    }else if(node1 == node1->p->left){
        node1->p->left = node2;
    }else {
        node1->p->right = node2;
        if(node2 != NULL){
            node2->p = node1->p;
        }
    }
}
void treeDelete(Tree *tree, int key){
    Node *z = treeSearch(tree, key);
    Node *y;

    if(z->left == NULL){
        transplant(tree, z, z->right);
    }else if(z->right == NULL){
        transplant(tree, z, z->left);
    }else {
        y = minimumKey(z->right);

        if(y != z->right){
            transplant(tree, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        transplant(tree, z, y);
        y->left = z->left;
        y->left->p = y;
    }
    free(z);
}

void preOrder(Node* node){ //recursive function
    
    if(node != NULL){
        printf("%d ", node->key);

        preOrder(node->left);
        preOrder(node->right);
    }

}

void inOrder(Node *node){ //recursive function

    if(node != NULL){

        inOrder(node->left);
        printf("%d ", node->key);
        inOrder(node->right);

    }
}

void postOrder(Node *node){ //recursive function

    if(node != NULL){

        postOrder(node->left);
        postOrder(node->right);

        printf("%d ", node->key);
    }
}

void freeTree(Node* node){//recursive function
    if(node != NULL){
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}