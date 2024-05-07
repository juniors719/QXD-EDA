/**
 * @file AVL.h
 * @author Júnior Silva (junior.silva@alu.ufc.br)
 * @brief TAD para representar uma árvore AVL. A árvore AVL é uma árvore binária de busca balanceada.
 * @version 0.1
 * @date 07-05-2024
 *
 *
 */

#ifndef AVL_H
#define AVL_H

#include <iostream>

/**
 * @brief Classe que representa uma árvore AVL
 *
 * @tparam T Tipo de dado a ser armazenado na árvore
 */
template <typename T>
class AVL_Tree {
   private:
    template <typename U>
    struct Node {
        U data{};       // dado armazenado no node
        Node* left{};   // ponteiro para o filho esquerdo
        Node* right{};  // ponteiro para o filho direito
        int height{};   // altura do node

        /**
         * @brief Construtor do Node
         *
         * @param data Dado a ser armazenado no node
         */
        Node(const T& data) : data(data), height(1) {}

        /**
         * @brief Destrutor do Node
         *
         */
        ~Node() {
            delete left;
            delete right;
        }
    };

    Node<T>* root{};  // raiz da arvore

    /**
     * @brief Método privado que retorna a altura de um node
     *
     * @param node
     * @return int
     */
    int height(Node<T>* node) {
        return (node != nullptr) ? node->height : 0;
    }

    /**
     * @brief Método privado que retorna o fator de balanceamento de um node
     *
     * @param node
     * @return int
     */
    int balance(Node<T>* node) {
        return height(node->right) - height(node->left);
    }

    /**
     * @brief Método privado que realiza a rotação à direita em um node p
     *
     * @param p Node a ser rotacionado
     * @return Ponteiro para a nova raiz da subárvore
     */
    Node<T>* rightRotation(Node<T>* p) {
        Node<T>* u = p->left;
        p->left = u->right;
        u->right = p;
        p->height = 1 + std::max(height(p->left), height(p->right));
        u->height = 1 + std::max(height(u->left), height(u->right));
        return u;
    }

    /**
     * @brief Método privado que realiza a rotação à esquerda em um node p
     *
     * @param p Node a ser rotacionado
     * @return Ponteiro para a nova raiz da subárvore
     */
    Node<T>* leftRotation(Node<T>* p) {
        Node<T>* u = p->right;
        p->right = u->left;
        u->left = p;
        p->height = 1 + std::max(height(p->left), height(p->right));
        u->height = 1 + std::max(height(u->left), height(u->right));
        return u;
    }

    /**
     * @brief Método privado que adiciona um elemento na árvore
     *
     * @param p Raiz da subárvore
     * @param data Dado a ser adicionado
     * @return Ponteiro para a nova raiz da subárvore
     */
    Node<T>* _add(Node<T>* p, const T& data) {
        if (p == nullptr) {  // subarvore vazia
            return new Node<T>(data);
        }
        if (data == p->data) {  // chave ja existe
            return p;
        }
        if (data < p->data) {
            p->left = _add(p->left, data);
        } else {
            p->right = _add(p->right, data);
        }
        p = fixup_node(p, data);  // regula o node p
        return p;
    }

    /**
     * @brief Método privado que regula o node p após a adição de um novo elemento
     *
     * @param p Node a ser regulado
     * @param data Dado adicionado
     * @return Ponteiro para o node regulado
     */
    Node<T>* fixup_node(Node<T>* p, const T& data) {
        p->height = 1 + std::max(height(p->left), height(p->right));
        int bal = balance(p);
        if (bal < -1 && data < p->left->data) {
            return rightRotation(p);
        } else if (bal < -1 && data > p->left->data) {
            p->left = leftRotation(p->left);
            return rightRotation(p);
        } else if (bal > 1 && data > p->right->data) {
            return leftRotation(p);
        } else if (bal > 1 && data < p->right->data) {
            p->right = rightRotation(p->right);
            return leftRotation(p);
        }
        return p;
    }

    /**
     * @brief Método privado que remove um elemento da árvore
     *
     * @param node Node raiz da subárvore
     * @param data Dado a ser removido
     * @return Ponteiro para a nova raiz da subárvore
     */
    Node<T>* _remove(Node<T>* node, const T& data) {
        if (node == nullptr) {  // node nao encontrado
            return nullptr;
        }
        if (data < node->data) {
            node->left = _remove(node->left, data);
        } else if (data > node->data) {
            node->right = _remove(node->right, data);
        } else if (node->right == nullptr) {
            Node<T>* temp = node->left;
            delete node;
            return temp;
        } else {
            node->right = remove_sucessor(node, node->right);
        }
        node = fixup_deletion(node);
        return node;
    }

    /**
     * @brief Método privado que remove o sucessor de um node
     *
     * @param root Node raiz da subárvore
     * @param node Node a ser removido
     * @return Ponteiro para a nova raiz da subárvore
     */
    Node<T>* remove_sucessor(Node<T>* root, Node<T>* node) {
        if (node->left != nullptr) {
            node->left = remove_sucessor(root, node->left);
        } else {
            Node<T>* temp = node->right;
            root->data = node->data;
            delete node;
            return temp;
        }
        node = fixup_deletion(node);
        return node;
    }

    /**
     * @brief Método privado que regula o node após a remoção de um elemento
     *
     * @param node Node a ser regulado
     * @return Ponteiro para o node regulado
     */
    Node<T>* fixup_deletion(Node<T>* node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
        int bal = balance(node);
        if (bal < -1 && balance(node->left) <= 0) {
            return rightRotation(node);
        } else if (bal < -1 && balance(node->left) > 0) {
            node->left = leftRotation(node->left);
            return rightRotation(node);
        } else if (bal > 1 && balance(node->right) >= 0) {
            return leftRotation(node);
        } else if (bal > 1 && balance(node->right) < 0) {
            node->right = rightRotation(node->right);
            return leftRotation(node);
        }
        return node;
    }

    /**
     * @brief Método privado que retorna uma string com a representação da árvore em pré-ordem
     *
     * @param node Node raiz da subárvore
     * @return String com a representação da árvore em pré-ordem
     */
    std::string _inOrder(Node<T>* node) {
        std::string s = "";
        if (node != nullptr) {
            s += _inOrder(node->left);
            s += std::to_string(node->data) + " ";
            s += _inOrder(node->right);
        }
        return s;
    }

    /**
     * @brief Método privado que verifica se a árvore contém um dado
     *
     * @param node Node raiz da subárvore
     * @param data Dado a ser verificado
     * @return true se contém,
     * @return false caso contrário
     */
    Node<T>* _contains(Node<T>* node, const T& data) {
        if (node == nullptr) {
            return nullptr;
        }
        if (data == node->data) {
            return node;
        }
        if (data < node->data) {
            return _contains(node->left, data);
        }
        return _contains(node->right, data);
    }

    /**
     * @brief Método privado que retorna o menor elemento da árvore
     *
     * @param node Node raiz da subárvore
     * @return Valor do menor elemento
     */
    T& _minimum(Node<T>* node) {
        Node<T>* p = node;
        while (p->left != nullptr) {
            p = p->left;
        }
        return p->data;
    }

    /**
     * @brief Método privado que retorna o maior elemento da árvore
     *
     * @param node Node raiz da subárvore
     * @return Valor do maior elemento
     */
    T& _maximum(Node<T>* node) {
        Node<T>* p = node;
        while (p->right != nullptr) {
            p = p->right;
        }
        return p->data;
    }

   public:
    /**
     * @brief Construtor padrão da classe AVL_Tree
     *
     */
    AVL_Tree() = default;

    /**
     * @brief Metodo para adicionar um elemento na arvore
     *
     * @param data
     */
    void add(const T& data) {
        root = _add(root, data);
    }

    /**
     * @brief Metodo para remover um elemento da arvore
     *
     * @param data
     */
    void remove(const T& data) {
        root = _remove(root, data);
    }

    /**
     * @brief Método que remove todos os elementos da árvore.
     *
     */
    void clear() {
        delete root;
        root = nullptr;
    }

    /**
     * @brief Método que troca o conteúdo de duas árvores AVL. Apenas troca os ponteiros para as raízes.
     *
     * @param other Árvore AVL a ser trocada
     */
    void swap(AVL_Tree<T>& other) {
        std::swap(root, other.root);
    }

    /**
     * @brief Método que retorna o menor elemento da árvore
     *
     * @return Valor do menor elemento
     */
    T& minimum() {
        return _minimum(root);
    }

    /**
     * @brief Método que retorna o maior elemento da árvore
     *s
     * @return Valor do maior elemento
     */
    T& maximum() {
        return _maximum(root);
    }

    /**
     * @brief Método que retorna o sucessor de um elemento
     *
     * @param key Elemento a ser verificado
     * @return Sucessor do elemento
     */
    T& successor(const T& key) {
        if (!contains(key)) {
            throw std::runtime_error("Elemento não está no conjunto");
        }
        Node<T>* p = root;
        Node<T>* sucessor = nullptr;
        while (p != nullptr) {
            if (p->data > key) {
                sucessor = p;
                p = p->left;
            } else {
                p = p->right;
            }
        }
        if (sucessor == nullptr) {
            throw std::runtime_error("Não existe sucessor");
        }
        return sucessor->data;
    }

    /**
     * @brief Método que retorna o antecessor de um elemento
     *
     * @param key Elemento a ser verificado
     * @return Antecessor do elemento
     */
    T& predecessor(const T& key) {
        if (!contains(key)) {
            throw std::runtime_error("Elemento não está no conjunto");
        }
        Node<T>* p = root;
        Node<T>* pred = nullptr;
        while (p != nullptr) {
            if (p->data < key) {
                pred = p;
                p = p->right;
            } else {
                p = p->left;
            }
        }
        if (pred == nullptr) {
            throw std::runtime_error("Não existe antecessor");
        }
        return pred->data;
    }

    /**
     * @brief Método que retorna uma string com a representação da árvore em pré-ordem
     *
     * @return String com a representação da árvore em pré-ordem
     */
    std::string inOrder() {
        return _inOrder(root);
    }

    /**
     * @brief Função pública que verifica se a árvore contém a chave val
     *
     * @param val chave a ser verificada
     * @return true se contém,
     * @return false caso contrário
     */
    bool contains(const T& val) {
        return _contains(root, val) != nullptr;
    }
};

#endif  // AVL_H