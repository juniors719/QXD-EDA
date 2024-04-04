// NAO MEXA NESSE ARQUIVO, ELE JA ESTA FINALIZADO E PRONTO PARA USO
#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
using namespace std;

/*****************************
 * Definicao do struct Node
 *****************************/
struct Node {
    int key;
    Node *left;
    Node *right;

    // Construtor
    Node(int k, Node *l = nullptr, Node *r = nullptr) {
        this->key = k;
        this->left = l;
        this->right = r;
    }
};

/************************
 * Declaracao da classe
 ************************/
class BST {
   public:
    BST();
    BST(int k);
    void bshow();
    void add(int k);
    int height();
    ~BST();

   private:
    Node *root;
    void bshow(Node *node, std::string heranca);
    Node *clear(Node *node);
    int height(Node *node);
};

/*****************************
 * Implementacao da classe
 *****************************/
BST::BST() {
    root = nullptr;
}

BST::BST(int k) {
    root = new Node(k);
}

void BST::bshow() {
    bshow(root, "");
}

void BST::bshow(Node *node, std::string heranca) {
    if (node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->right, heranca + "r");
    for (int i = 0; i < (int)heranca.size() - 1; i++)
        std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
    if (heranca != "")
        std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
    if (node == nullptr) {
        std::cout << "#" << std::endl;
        return;
    }
    std::cout << node->key << std::endl;
    if (node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->left, heranca + "l");
}

Node *BST::clear(Node *node) {
    if (node != nullptr) {
        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
    }
    return nullptr;
}

BST::~BST() {
    root = clear(root);
}

int BST::height() {
    return height(root);
}

int BST::height(Node *node) {
    if (node == nullptr)
        return 0;
    else
        return 1 + std::max(height(node->left), height(node->right));
}

void BST::add(int k) {
    if (root == nullptr) {
        root = new Node(k);
        return;
    }
    Node *pai = nullptr;
    Node *atual = root;
    while (atual != nullptr) {
        pai = atual;
        if (k < atual->key)
            atual = atual->left;
        else if (k > atual->key)
            atual = atual->right;
        else
            return;
    }
    if (k < pai->key)
        pai->left = new Node(k);
    else
        pai->right = new Node(k);
}

#endif