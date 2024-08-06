#pragma once

#include <stdexcept>

class BST {
    struct Node {
        int key;
        Node* left;
        Node* right;
        Node(int key) : key(key), left(nullptr), right(nullptr) {}
        ~Node() {
            delete left;
            delete right;
        }
    };

   private:
    Node* root;

    // Função privada recursiva para inserção.
    // Complexidade: O(h), onde h é a altura da árvore.
    // Melhor árvore: O(log n), numa árvore cheia e balanceada.
    // Pior árvore: O(n), numa árvore degenerada.
    // Média: O(log n), numa árvore balanceada.
    Node* _insert(Node* node, int key) {
        if (node == nullptr) {  // Se a árvore estiver vazia, cria um novo nó
            return new Node(key);
        }
        if (key > node->key)  // Se a chave for maior que a chave do nó atual, insere na subárvore direita
            node->right = _insert(node->right, key);
        else if (key < node->key)  // Se a chave for menor que a chave do nó atual, insere na subárvore esquerda
            node->left = _insert(node->left, key);
        return node;  // Retorna o nó atual
    }

    // Função privada recursiva para busca.
    // Complexidade: O(h), onde h é a altura da árvore.
    // Melhor árvore: O(log n), numa árvore cheia e balanceada.
    // Pior árvore: O(n), numa árvore degenerada.
    // Média: O(log n), numa árvore balanceada.
    Node* _busca(Node* node, int k) {
        if (node == nullptr || node->key == k)  // Se a árvore estiver vazia ou a chave for encontrada,
            return node;                        // retorna o nó atual

        if (k > node->key)                  // Se a chave for maior que a chave do nó atual:
            return _busca(node->right, k);  // busca na subárvore direita e retorna o resultado da busca
        else                                // Se a chave for menor que a chave do nó atual:
            return _busca(node->left, k);   // busca na subárvore esquerda e retorna o resultado da busca
    }

    // Função privada para remover um nó.
    // Retorna o nó que substituirá a raiz.
    // Complexidade: O(h), onde h é a altura da árvore.
    Node* _remove(Node* node, int k) {
        if (node == nullptr) return node;           // Se a árvore estiver vazia, retorna nullptr
        if (node->key == k)                         // Se a chave for encontrada:
            return _removeRoot(node);               // Remove a raiz da subárvore
        else if (k > node->key)                     // Se a chave for maior que a chave do nó atual:
            node->right = _remove(node->right, k);  // Remove na subárvore direita
        else                                        // Se a chave for menor que a chave do nó atual:
            node->left = _remove(node->left, k);    // Remove na subárvore esquerda
        return node;                                // Retorna o nó atual
    }

    // Função privada para remover a raiz da subárvore.
    // Complexidade: O(h), onde h é a altura da árvore.
    Node* _removeRoot(Node* node) {
        Node *pai, *q;
        if (node->right == nullptr)  // Se a subárvore direita for nula, retorna a raiz da subárvore esquerda
            q = node->left;
        else {  // Senão, encontra o nó mais à esquerda da subárvore direita
            pai = node;
            q = node->right;
            while (q->left != nullptr) {  // Enquanto houver nó à esquerda
                pai = q;
                q = q->left;
            }
            if (pai != node) {           // Se o nó mais à esquerda não for o filho direito da raiz
                pai->left = q->right;    // O pai do nó mais à esquerda aponta para o filho direito do nó mais à esquerda
                q->right = node->right;  // O filho direito do nó mais à esquerda aponta para a subárvore direita da raiz
            }
            q->left = node->left;  // O filho esquerdo do nó mais à esquerda aponta para a subárvore esquerda da raiz
        }
        delete node;  // Deleta a raiz
        return q;     // Retorna o nó que substituirá a raiz
    }

   public:
    BST() : root(nullptr) {}
    ~BST() {
        delete root;
    }

    void insert(int key) {
        root = _insert(root, key);
    }

    void remove(int key) {
        root = _remove(root, key);
    }

    Node* busca(int k) {
        return _busca(root, k);
    }

    bool contains(int k) {
        return busca(k) != nullptr;
    }
};