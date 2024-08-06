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

    // Função que divide um nó cheio
    void split_child(Bnode* x, int i){
        Bnode* y = x->child[i];
        Bnode* z = new Bnode(m_degree, y->leaf);
        z->n = m_degree - 1;
        for(int j = 0; j < m_degree-2; ++j){
            z->key[j] = y->key[m_degree + j];
            z->child[j] = y->child[m_degree + j];
        }
        z->child[m_degree-1] = y->child[2*m_degree-1];
        for (int j = x->n-1; j >= i; j--) {
            x->key[j+1] = x->key[j];
        }
        for (int j = x->n; j >= i+1; j--) {
            x->child[j+1] = x->child[j];
        }
        x->key[i] = y->key[m_degree-1];
        x->child[i+1] = z;
        x->n++;
        y->n = m_degree-1;
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

    void insert(int k){
        if(m_root->n == 2*m_degree-1){ // caso raiz cheia
            Bnode* s = new Bnode(m_degree, false);
            s->child[0] = m_root;
            m_root = s;
            split_child(m_root, 0);
            insert_non_full(m_root, k);
        }else{ // caso raiz não cheia
            insert_non_full(m_root, k);
        }
    }


};

#endif  // BTREE_H
