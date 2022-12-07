#include "redblack.h"

Tree* NewTree(){

    Tree *tree = malloc(sizeof(Tree));
    Node *node_nil = (Node *)malloc(sizeof(Node));
    
    node_nil->left = node_nil->right = node_nil->p = NULL;
    node_nil->color = BLACK;
    node_nil->key = 0;

    tree->null = node_nil;
    tree->root = tree->null;
    
    return tree;
}

void inOrder(Node *node){ //recursive function

    if(node->key != NULL){
        inOrder(node->left);
        printf("%d ", node->key);
        inOrder(node->right);
    }
}
void preOrder(Node *node){ //recursive function

    if(node->key != NULL){
        printf("%d ", node->key);
        inOrder(node->left);
        inOrder(node->right);
    }
}
void postOrder(Node *node){ //recursive function

    if(node->key != NULL){
        inOrder(node->left);
        inOrder(node->right);
        printf("%d ", node->key);
    }
}

void freeTree(Node* node){//recursive function
    if(node->key != NULL){
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

int treeHeight(Node *tree){
    if(tree->key == NULL){
        return -1;
    }else{
        int left = treeHeight(tree->left);
        int right = treeHeight(tree->right);

        if(left > right){
            return left + 1;
        }else{
            return right + 1;

        }
    }
}

Node* minimumKey(Tree* tree, Node *node){
    while(node->left!= tree->null) node = node->left;

    return node;
}

Node* maximumKey(Tree* tree, Node *node){
    while(node->right!= tree->null) node = node->right;

    return node;
}

Node *findNode(Tree *tree, Node *node, int k){
    while(node != tree->null && k != node->key){
        if(k < node->key)
            node = node->left;
        else
            node = node->right;
    }
        return node;
}

void leftRotate(Tree *tree, Node *node) {

    Node *y;

    y = node->right;
    node->right = node->left;
    
    if(y->left != tree->null)
        y->left->p = node;

    y->p = node->p; // node's parent becomes y's parent

    if(node->p == tree->null){
        tree->root = y;
    }else if(node == node->p->left){
        node->p->left = y;
    } else{
        node->p->right = y;
    }

    y->left = node; //put x in y ’s left child
    node->p = y;

}

void rightRotate(Tree *tree, Node *node) {

    Node *y;

    y = node->left;
    node->left = node->right;
    
    if(y->right != tree->null){
        y->left->p = node;
    }

    y->p = node->p; // node's parent becomes y's parent

    if(node->p == tree->null){
        tree->root = y;
    }else if(node == node->p->right){
        node->p->right = y;
    } else{
        node->p->left = y;
    }

    y->right = node; //put x in y ’s left child
    node->p = y;

}

void transplant(Tree *tree, Node *u, Node *v){
    if(u->p == tree->null){
        tree->root = v;
    } else if(u == u->p->left){
        u->p->left = v;
    }else{
        u->p->right = v;
    }

    v->p = u->p;
}

void insert(Tree *tree, int value){
    Node *x = tree->root;
    Node *y = tree->null;

    Node *z = (Node *)malloc(sizeof(Node)); //alloc new node z
    z->left = z->right = z->p = NULL;
    z->key = value;
    z->color = RED;

    while(x != tree->null) {
        y = x;
        if(z->key < x->key)
            x = x->left;
        else x = x->right;
    }
    z->p = y;

    if(y == tree->null){
        tree->root = z;
    } else if(z->key < y->key){
        y->left = z;
    } else{
        y->right = z;
    }

    z->left = z->right = tree->null;

    insertFixup(tree, z);
}

void insertFixup(Tree *tree, Node *z){
    Node *y;

    while(z->p->color == RED){
        if(z->p == z->p->p->left){
            y = z->p->p->right;
            if(y->color == RED){ //case 1
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }else{
                if(z == z->p->right) { //case 2
                    z = z->p;
                    leftRotate(tree, z);
                }
                //case 3
                z->p->color = BLACK;
                z->p->p->color = RED;
                rightRotate(tree, z->p->p);
            }

        }else {
            y = z->p->p->left;
            if(y->color == RED){ //case 1
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }else{
                if(z == z->p->left) { //case 2
                    z = z->p;
                    rightRotate(tree, z);
                }
                //case 3
                z->p->color = BLACK;
                z->p->p->color = RED;
                leftRotate(tree, z->p->p);
            }
        }
    }
    tree->root->color = BLACK;
}

void delete(Tree *tree, Node *z){
    Node *y = z; Node *x;
    enum COLOR yOriginalColor = y->color;

    if(z->left == tree->null){
        x = z->right;
        transplant(tree, z, z->right);
    }
    else if(z->right == tree->null){
        x = z->left;
        transplant(tree, z, z->left);
    }else{
        y = minimumKey(tree, z->right);
        yOriginalColor = y->color;
        x = y->right;
        if(y->p == z) {
            x->p = z;
        }else{
            transplant(tree, y, y->right);
            y->right = z->right;
            y->right->p = y;
        } 
            x->p = y;
            transplant(tree, z, y);
            y->left = z->left;
            y->left->p = y;
            y->color = z->color;

    }
    if(yOriginalColor == BLACK){
        deleteFixup(tree, x);
    }
}

void deleteFixup(Tree *tree, Node *x){
    Node *w;

    while(x != tree->root && x->color == BLACK){
        if(x == x->p->left){
            w = x->p->right;
            if(w->color == RED){ //case 1
                w->color = BLACK;
                x->p->color = RED;
                leftRotate(tree, x->p);
                w = x->p->right;
            }
            if(w->left->color == BLACK && w->right->color == BLACK){ // case 2
                w->color = RED;
                x = x->p;
            }
            else{
                if(w->right->color == BLACK){ //case 3
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(tree, w);
                    w = x->p->right;
                }
                // case 4
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                leftRotate(tree, x->p);
                x = tree->root;
            }
        } 
        else{
            w = x->p->left;
            if(w->color == RED){ //case 1
                w->color = BLACK;
                x->p->color = RED;
                rightRotate(tree, x->p);
                w = x->p->left;
            }
            if(w->left->color == BLACK && w->left->color == BLACK){ // case 2
                w->color = RED;
                x = x->p;
            }
            else{
                if(w->left->color == BLACK){ //case 3
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(tree, w);
                    w = x->p->left;
                }
                // case 4
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                rightRotate(tree, x->p);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}