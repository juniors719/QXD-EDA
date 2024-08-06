#ifndef BTREE_H
#define BTREE_H

#include <utility>

#include "Bnode.h"

class Btree {
   private:
    int m_degree;   // grau mínimo da árvore
    Bnode* m_root;  // ponteiro para a raiz da árvore

    void clear(Bnode* node) {
        if (node->leaf) delete node;

        for (int i = 0; i < node->n; i++) {
            clear(node->child[i]);
        }
        delete node;
    }

    std::pair<Bnode*, int> search(Bnode* x, int key) {
        int i = 0;
        while (i < x->n && key > x->key[i]) i++;
        if (i < x->n && key == x->key[i])
            return {x, i};
        else if (x->leaf)
            return {nullptr, -1};
        else
            return search(x->child[i], key);
    }

   public:
    /**
     * @brief Construtor da classe Btree
     *
     * @param degree
     */
    Btree(int degree) : m_degree(degree) {
        m_root = new Bnode(m_degree, true);
    }

    /**
     * @brief Destrutor da classe Btree
     *
     */
    ~Btree() {
        clear(m_root);
    }

    bool contains(int key) {
        return search(m_root, key).first != nullptr;
    }
};

#endif  // BTREE_H