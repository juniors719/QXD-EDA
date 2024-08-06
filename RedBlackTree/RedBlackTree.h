#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>

#include "Node.h"

class RBTree {
   private:
    Node* m_root;
    Node* m_nil;

   public:
    RBTree() {
        m_root = m_nil = new Node(0, BLACK, nullptr, nullptr, nullptr);
        m_nil->left = m_nil->right = m_nil->parent = m_nil;
    }

    void insert(int value) {
        Node* atual = m_root;
        Node* pai_do_atual = m_nil;
        while (atual != m_nil) {
            pai_do_atual = atual;
            if (value < atual->key)
                atual = atual->left;
            else if (value > atual->key)
                atual = atual->right;
            else
                return;
        }
        Node* z = new Node(value, RED, pai_do_atual, m_nil, m_nil);
        if (pai_do_atual == m_nil)
            m_root = z;
        else if (value < pai_do_atual->key)
            pai_do_atual->left = z;
        else
            pai_do_atual->right = z;

        insert_fixup(z);
    }

    void insert_fixup(Node* z) {
    }
};

#endif  // RBTREE_H
