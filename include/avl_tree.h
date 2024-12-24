// include/avl_tree.h

#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

Node* insert(Node* node, int key);
Node* deleteNode(Node* root, int key);
void preOrder(Node* root);
void inOrder(Node* root);
void postOrder(Node* root);
Node* newNode(int key);
Node* rightRotate(Node* y);
Node* leftRotate(Node* x);
int getBalance(Node* N);
int height(Node* N);
int max(int a, int b);

#endif // AVL_TREE_H
