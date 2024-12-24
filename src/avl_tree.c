// include/avl_tree.c

#include "avl_tree.h"
#include <stdio.h>
#include <stdlib.h>

int height(Node* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  // Novo nó inicialmente adicionado na folha
    return node;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Função para inserir um novo nó com uma chave dada na árvore AVL e
// balanceá-la conforme necessário
Node* insert(Node* node, int key) {
    // 1. Realizar a inserção normal de uma árvore de busca binária
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Chaves duplicadas não são permitidas na AVL
        return node;

    // 2. Atualizar a altura deste nó ancestral
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Obter o fator de balanceamento deste nó ancestral para verificar se este nó se tornou desbalanceado
    int balance = getBalance(node);

    // Se este nó se torna desbalanceado, então há 4 casos

    // Caso Esquerda-Esquerda
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Caso Direita-Direita
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Caso Esquerda-Direita
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso Direita-Esquerda
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // retornar o ponteiro do nó (inalterado)
    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}


// Função recursiva para deletar um nó com uma chave dada da árvore AVL
Node* deleteNode(Node* root, int key) {
    // PASSO 1: PERFORMAR A DELEÇÃO PADRÃO BST
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if(key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Este nó é o que vamos deletar
        if((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;

            // Sem filho
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else // Um filho
             *root = *temp; // Copia o conteúdo do filho não-vazio

            free(temp);
        }
        else {
            // Nó com dois filhos: Pegue o sucessor em ordem (menor na subárvore direita)
            Node* temp = minValueNode(root->right);

            // Copie o dado do sucessor em ordem para este nó
            root->key = temp->key;

            // Delete o sucessor em ordem
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // Se a árvore tinha apenas um nó então retorna
    if (root == NULL)
      return root;

    // PASSO 2: ATUALIZAR A ALTURA DO NÓ ATUAL
    root->height = 1 + max(height(root->left), height(root->right));

    // PASSO 3: OBTER O FATOR DE BALANCEAMENTO DESTE NÓ (para verificar se este nó se tornou desbalanceado)
    int balance = getBalance(root);

    // Se este nó se torna desbalanceado, então há 4 casos

    // Caso Esquerda-Esquerda
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Caso Esquerda-Direita
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Caso Direita-Direita
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Caso Direita-Esquerda
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


// Funções de caminhamento
void preOrder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

void postOrder(Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->key);
    }
}


