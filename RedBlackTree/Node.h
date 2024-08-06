#ifndef NODE_H
#define NODE_H

#include <iostream>

#define RED false
#define BLACK true

struct Node {
    int key;
    bool color;
    Node* parent;
    Node* left;
    Node* right;

    Node(int k, bool c, Node* p, Node* l, Node* r)
        : key(k), color(c), parent(p), left(l), right(r) {}

    ~Node() {
        std::cout << "deleted: " << key << std::endl;
    }
};

#endif  // NODE_H