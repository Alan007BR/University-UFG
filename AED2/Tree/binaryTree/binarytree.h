typedef struct Node{
    int key;
    struct Node *left, *right, *p;
} Node;

typedef struct Tree{
    Node *root;
} Tree;


