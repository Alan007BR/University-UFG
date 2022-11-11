#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    struct Node *left, *right, *p;
} Node;

typedef struct Tree{
    Node *root;
} Tree;


Tree NewTree();
Node* treeSearch(Node *node, int k);
Node* minimumKey(Node *node);
Node* maximumKey(Node *node);
void insert(Tree* tree, int key);
void transplant(Tree *tree, Node *node1, Node *node2);
void treeDelete(Tree *tree, int key);
void preOrder(Node* node);//recursive function
void postOrder(Node* node);//recursive function
void inOrder(Node* node);//recursive function
void freeTree(Node* node);//recursive function
