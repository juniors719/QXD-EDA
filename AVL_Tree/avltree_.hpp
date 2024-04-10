#ifndef AVLTREE_HPP
#define AVLTREE_HPP

/**
 * @brief Classe que representa uma Árvore AVL.
 *
 * Uma árvore AVL é uma árvore binária de busca balanceada, onde a diferença de altura entre as subárvores
 * esquerda e direita de cada nó é no máximo 1.
 *
 * @tparam T O tipo de dado armazenado na árvore.
 */
template <typename T>
class AVLTree {
   private:
    /**
     * @brief Estrutura de nó para uma árvore AVL.
     *
     * @tparam T O tipo de dado armazenado no nó.
     */
    template <typename T>
    struct Node {
        T data{};         /**< O dado armazenado no nó. */
        Node<T>* left{};  /**< O ponteiro para o filho esquerdo. */
        Node<T>* right{}; /**< O ponteiro para o filho direito. */
        int height{};     /**< A altura do nó. */

        /**
         * @brief Construtor para a criação de um nó com um valor específico.
         *
         * @param value O valor a ser armazenado no nó.
         */
        explicit Node(const T& value) : data(value), height(1) {}
    };

    Node<T>* m_root{nullptr}; /**< O ponteiro para a raiz da árvore AVL. */

    /**
     * Retorna a altura de um nó da árvore AVL.
     *
     * @param node O nó para o qual se deseja obter a altura.
     * @return A altura do nó. Se o nó for nulo, retorna 0.
     */
    int height(Node<T>* node) {
        if (node == nullptr) return 0;
        return node->height;
    }

    /**
     * Calcula o fator de balanceamento de um nó da árvore AVL.
     *
     * O fator de balanceamento é definido como a diferença entre a altura da subárvore esquerda
     * e a altura da subárvore direita do nó.
     *
     * @param node O nó para o qual o fator de balanceamento será calculado.
     * @return O fator de balanceamento do nó.
     */
    int balanceFactor(Node<T>* node) const {
        if (node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }

    /**
     * Realiza uma rotação à direita na árvore AVL.
     *
     * @param y O nó a ser rotacionado.
     * @return O novo nó raiz da subárvore após a rotação.
     */
    Node<T>* rightRotate(Node<T>* y) {
        // Na rotação à direita, o filho esquerdo de y (x) se torna a nova raiz da subárvore.
        // O antigo nó raiz da subárvore (y) se torna o filho direito de x.
        // O filho direito de x (T2) se torna o filho esquerdo de y.

        Node<T>* x = y->left;    // Salva o filho esquerdo de y
        Node<T>* T2 = x->right;  // Salva o filho direito de x.

        x->right = y;  // y se torna o filho direito de x
        y->left = T2;  // T2 se torna o filho esquerdo de y

        // Atualiza as alturas dos nós
        y->height = 1 + std::max(height(y->left), height(y->right));
        x->height = 1 + std::max(height(x->left), height(x->right));
        // Usamos max pois queremos a maior altura entre os filhos.

        return x;  // Retorna a nova raiz da subárvore
    }

    /**
     * Realiza uma rotação à esquerda na árvore AVL.
     *
     * @param x O nó a ser rotacionado.
     * @return O novo nó raiz da subárvore após a rotação.
     */
    Node<T>* leftRotate(Node<T>* x) {
        // Na rotação à esquerda, o filho direito de x (y) se torna a nova raiz da subárvore.
        // O antigo nó raiz da subárvore (x) se torna o filho esquerdo de y.
        // O filho esquerdo de y (T2) se torna o filho direito de x.

        Node<T>* y = x->right;  // Salva o filho direito de x
        Node<T>* T2 = y->left;  // Salva o filho esquerdo de y

        y->left = x;    // x se torna o filho esquerdo de y
        x->right = T2;  // T2 se torna o filho direito de x

        // Atualiza as alturas dos nós
        x->height = 1 + std::max(height(x->left), height(x->right));
        y->height = 1 + std::max(height(y->left), height(y->right));

        return y;  // Retorna a nova raiz da subárvore
    }

    /**
     * Insere um novo nó na árvore AVL.
     *
     * @param node O nó atual em que a inserção será realizada.
     * @param value O valor a ser inserido na árvore.
     * @return O nó atualizado após a inserção e as rotações.
     */
    Node<T>* insertNode(Node<T>* node, const T& value) {
        if (node == nullptr) return new Node<T>(value);  // Caso base, se node for nulo, retorna um novo nó.

        if (value < node->data) {
            node->left = insertNode(node->left, value);
        } else if (value > node->data) {
            node->right = insertNode(node->right, value);
        } else {
            return node;  // Se o valor já existe, retorna o nó.
        }

        node->height = 1 + std::max(height(node->left), height(node->right));  // Atualiza a altura do nó.

        int balance = balanceFactor(node);  // Calcula o fator de balanceamento do nó.

        // Agora, verificamos se o nó está desbalanceado e se é necessário realizar rotações.

        // Caso esquerda-esquerda
        // Se o fator de balanceamento for maior que 1 e o valor for menor que o filho esquerdo do nó,
        // então é necessário realizar uma rotação à direita.
        if (balance > 1 && value < node->left->data) {
            return rightRotate(node);
        }
        /*
            Como o fator de balanceamento é 1, significa que a árvore está desbalanceada para a esquerda.
            Se o valor for menor que o filho esquerdo do nó, então é necessário realizar uma rotação à direita, pois
            o valor inserido está na subárvore esquerda do filho esquerdo do nó.
        */

        // Caso direita-direita
        // Se o fator de balanceamento for menor que -1 e o valor for maior que o filho direito do nó,
        // então é necessário realizar uma rotação à esquerda.
        if (balance < -1 && value > node->right->data) {
            return leftRotate(node);
        }
        /*
            Como o fator de balanceamento é -1, significa que a árvore está desbalanceada para a direita.
            Se o valor for maior que o filho direito do nó, então é necessário realizar uma rotação à esquerda, pois
            o valor inserido está na subárvore direita do filho direito do nó.
        */

        // Caso esquerda-direita
        // Se o fator de balanceamento for maior que 1 e o valor for maior que o filho esquerdo do nó,
        // então é necessário realizar uma rotação à esquerda no filho esquerdo e uma rotação à direita no nó.
        if (balance > 1 && value > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        /*
            Como o fator de balanceamento é 1, significa que a árvore está desbalanceada para a esquerda.
            Se o valor for maior que o filho esquerdo do nó, então é necessário realizar uma rotação à esquerda no filho
            esquerdo e uma rotação à direita no nó, pois o valor inserido está na subárvore direita do filho esquerdo do nó.
        */

        // Caso direita-esquerda
        // Se o fator de balanceamento for menor que -1 e o valor for menor que o filho direito do nó,
        // então é necessário realizar uma rotação à direita no filho direito e uma rotação à esquerda no nó.
        if (balance < -1 && value < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        /*
            Como o fator de balanceamento é -1, significa que a árvore está desbalanceada para a direita.
            Se o valor for menor que o filho direito do nó, então é necessário realizar uma rotação à direita no filho
            direito e uma rotação à esquerda no nó, pois o valor inserido está na subárvore esquerda do filho direito do nó.
        */

        return node;  // Retorna o nó após a inserção e as rotações.
    }

    /**
     * Retorna o nó com o menor valor na subárvore enraizada no nó passado como parâmetro.
     *
     * @param node O nó raiz da subárvore.
     * @return O nó com o menor valor na subárvore.
     */
    Node<T>* minValueNode(Node<T>* node) {
        Node<T>* current = node;  // Inicializa o nó atual com o nó passado como parâmetro.

        while (current->left != nullptr) {  // Enquanto houver um filho esquerdo, atualiza o nó atual.
            current = current->left;
        }

        return current;  // Retorna o nó com o menor valor.
    }

    /**
     * Função responsável por deletar um nó com a chave especificada em uma árvore AVL.
     *
     * @param root O ponteiro para a raiz da árvore.
     * @param key A chave do nó a ser deletado.
     * @return O ponteiro para a raiz da árvore após a deleção e as rotações.
     */
    Node<T>* deleteNode(Node<T>* root, const T& key) {
        if (root == nullptr) return root;  // Caso base, se o nó for nulo, retorna o nó.

        // Se a chave for menor que o valor do nó, então a chave está na subárvore esquerda.
        if (key < root->data) {
            root->left = deleteNode(root->left, key);  // Deleta o nó na subárvore esquerda.
        }
        // Se a chave for maior que o valor do nó, então a chave está na subárvore direita.
        else if (key > root->data) {
            root->right = deleteNode(root->right, key);  // Deleta o nó na subárvore direita.
        }
        // Se a chave for igual, então este nó será deletado
        else {
            // Caso 1: O nó tem nenhum ou 1 filho
            if (root->left == nullptr || root->right == nullptr) {
                Node<T>* temp = root->left ? root->left : root->right;  // Salva o filho não nulo do nó
                // Se não houver filho, então o nó é deletado
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                // Se houver um filho, então o conteúdo do filho é copiado para o nó
                else {
                    *root = *temp;  // Copia o conteúdo do filho não nulo para o nó
                }

            }
            // Caso 2: O nó tem 2 filhos
            else {
                Node<T>* temp = minValueNode(root->right);          // Encontra o nó com o menor valor na subárvore direita
                root->data = temp->data;                            // Copia o valor do nó encontrado para o nó atual
                root->right = deleteNode(root->right, temp->data);  // Deleta o nó com o menor valor na subárvore direita
            }
        }

        if (root == nullptr) return root;  // Se a árvore tiver apenas um nó, retorna o nó.

        root->height = 1 + std::max(height(root->left), height(root->right));  // Atualiza a altura do nó

        int balance = balanceFactor(root);  // Calcula o fator de balanceamento do nó

        // Agora, verificamos se o nó está desbalanceado e se é necessário realizar rotações.
        if (balance > 1) {
            // Caso esquerda-esquerda
            if (balanceFactor(root->left) >= 0) {
                return rightRotate(root);
            }
            // Caso esquerda-direita
            else {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
        } else if (balance < -1) {
            // Caso direita-direita
            if (balanceFactor(root->right) <= 0) {
                return leftRotate(root);
            }
            // Caso direita-esquerda
            else {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
        }

        return root;  // Retorna o nó após a deleção e as rotações.
    }

   public:
    /**
     * @brief Classe que representa uma árvore AVL.
     *
     * A árvore AVL é uma árvore binária de busca balanceada, onde a diferença de altura entre as subárvores
     * esquerda e direita de cada nó é no máximo 1. Isso garante que a árvore esteja sempre balanceada e
     * mantém a complexidade das operações de busca, inserção e remoção em O(log n).
     */
    AVLTree() = default;

    /**
     * Insere um valor na árvore AVL.
     *
     * @param value O valor a ser inserido na árvore.
     */
    void insert(const T& value) {
        m_root = insertNode(m_root, value);
    }

    /**
     * Remove um valor da árvore AVL.
     *
     * @param value O valor a ser removido.
     */
    void remove(const T& value) {
        m_root = deleteNode(m_root, value);
    }
};

#endif  // AVLTREE_HPP