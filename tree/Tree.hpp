#include <iostream>
using namespace std;

/**
 * @brief Struct que implementa a lógica de um nó de uma árvore binária
 *
 * @tparam Key
 */
template <typename Key>
struct Node {
    Key key;
    Node* left;
    Node* right;
};

/**
 * @brief Classe que implementa a lógica de uma árvore binária
 *
 * @tparam Key
 */
template <typename Key>
class Tree {
   private:
    Node<Key>* m_root{nullptr};  // root of the tree

   public:
    /**
     * @brief Construct a new Tree object
     *
     */
    Tree() = default;

    /**
     * @brief Função pública que recebe a chave val e adiciona ela na árvore, se não for repetida.
     * Se for repetida, não faz nada.
     *
     * @param val
     */
    void add(Key val) {
        m_root = _add(m_root, val);
    }

    /**
     * @brief Função pública que percorre a árvore em ordem simétrica
     *
     */
    void preOrdem() {
        _preOrdem(m_root);
    }

    /**
     * @brief Função pública que percorre a árvore em pré-ordem
     *
     */
    void inOrdem() {
        _inOrdem(m_root);
    }

    /**
     * @brief Função pública que percorre a árvore em pós-ordem
     *
     */
    void posOrdem() {
        _posOrdem(m_root);
    }

    /**
     * @brief Função pública que verifica se a árvore contém a chave val
     *
     * @param val chave a ser verificada
     * @return true se contém,
     * @return false caso contrário
     */
    bool contains(Key val) {
        return _contains(m_root, val) != nullptr;
    }

   private:
    /**
     * @brief Função recursiva que recebe a raiz de uma árvore e adiciona a chave val nela.
     * Retorna a raiz da nova árvore.
     *
     * @param node
     * @param val
     * @return Node*
     */
    Node<Key>* _add(Node<Key>* node, Key val) {
        // caso base
        if (node == nullptr) {
            return new Node<Key>{val, nullptr, nullptr};
        }
        // caso geral

        if (val < node->key) {  // se for menor -> esquerda
            node->left = _add(node->left, val);
        } else if (val > node->key) {  // se for maior -> direita
            node->right = _add(node->right, val);
        }
        return node;
    }

    /**
     * @brief Função recursiva que percorre a árvore em ordem simétrica
     *
     * @param node nó raiz da árvore
     */
    void _inOrdem(Node<Key>* node) {
        // caso base
        if (node == nullptr)
            return;

        // caso geral
        _inOrdem(node->left);
        cout << node->key << " ";
        _inOrdem(node->right);
    }
    /**
     * @brief Função recursiva que percorre a árvore em pré-ordem
     *
     * @param node nó raiz da árvore
     */
    void _preOrdem(Node<Key>* node) {
        // caso base
        if (node == nullptr)
            return;

        // caso geral
        cout << node->key << " ";
        _preOrdem(node->left);
        _preOrdem(node->right);
    }
    /**
     * @brief Função recursiva que percorre a árvore em pós-ordem
     *
     * @param node nó raiz da árvore
     */
    void _posOrdem(Node<Key>* node) {
        // caso base
        if (node == nullptr)
            return;

        // caso geral
        _posOrdem(node->left);
        _posOrdem(node->right);
        cout << node->key << " ";
    }

    /**
     * @brief Função privada recursiva que reebe a raiz de uma árvore e retorna o ponteiro para o nó com a chave val. Se não encontrar, retorna nullptr.
     *
     * @param node
     * @param val
     * @return Node<Key>*
     */
    Node<Key>* _contains(Node<Key>* node, Key val) {
        // caso base
        if (node == nullptr || node->key == val)
            return node;

        // caso geral
        if (val < node->key)
            return _contains(node->left, val);
        else
            return _contains(node->right, val);
    }

    /**
     * @brief Função privada recursiva que recebe a raiz de uma árvore e a chave val a ser removida.
     *
     * @param node
     * @param val
     * @return Node<Key>*
     */
    Node<Key>* _remove(Node<Key>* node, Key val) {
        // caso base
        if (node == nullptr)
            return node;

        // Caso "achei o nó"
        if (val == node->key)
            return _remove_node(node);

        // Caso "ainda não achei o nó"
        if (val < node->key)
            node->left = _remove(node->left, val);
        else
            node->right = _remove(node->right, val);
        return node;
    }

    Node<Key>* _remove_node(Node<Key>* node) {
        // Caso 1: nó folha
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }

        // Caso 2: nó com 1 filho
        if (node->left == nullptr) {
            Node<Key>* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node<Key>* temp = node->left;
            delete node;
            return temp;
        }

        // Caso 3: nó com 2 filhos
        Node<Key>* temp = _minValueNode(node->right);
        node->key = temp->key;
        node->right = _remove(node->right, temp->key);
        return node;
    }

    Node<Key>* _minValueNode(Node<Key>* node) {
        Node<Key>* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
};
