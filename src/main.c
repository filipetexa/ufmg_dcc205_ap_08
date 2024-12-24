// src/main.c

#include "../include/avl_tree.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Node* root = NULL;
    int n, key;
    char operation;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf(" %c %d", &operation, &key);
        if (operation == 'i') {
            root = insert(root, key);
        } else if (operation == 'r') {
            root = deleteNode(root, key);
        }
    }

    preOrder(root);
    printf("\n");
    inOrder(root);
    printf("\n");
    postOrder(root);
    printf("\n");

    return 0;
}
