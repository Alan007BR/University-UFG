#include <stdio.h>
#include <stdlib.h>

enum COLOR {RED, BLACK};

typedef struct Node {
    int key;
    enum COLOR color;
    struct Node *left, *right, *p;
} Node;

typedef struct Tree {
    Node *root;
    Node *null;
} Tree;


Tree* NewTree();
Node* minimumKey(Tree* tree, Node *node);
Node* maximumKey(Tree* tree, Node *node);
void insert(Tree *tree, int key);
void insertFixup(Tree *tree, Node *z);
void deleteFixup(Tree *tree, Node *z);
void leftRotate(Tree *tree, Node *node);
void rightRotate(Tree *tree, Node *node);
void transplant(Tree *tree, Node *u, Node *v);
void delete(Tree *tree, Node *z);
int treeHeight(Node *tree);
void preOrder(Node* node);//recursive function
void postOrder(Node* node);//recursive function
void inOrder(Node* node);//recursive function
void freeTree(Node* node);//recursive function
Node* findNode(Tree *tree, Node *node, int k);//recursive function
