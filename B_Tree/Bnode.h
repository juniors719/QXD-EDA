#ifndef BNODE_H
#define BNODE_H

struct Bnode {
    int n;
    bool leaf;
    int* key;
    Bnode** child;

    Bnode(int degree, bool is_leaf) : leaf(is_leaf), n(0) {
        key = new int[2 * degree - 1];   // alocamos memória para as chaves, no máximo 2 * degree - 1
        child = new Bnode*[2 * degree];  // alocamos memória para os filhos, no máximo 2 * degree
    }

    ~Bnode() {
        delete[] key;
        delete[] child;
    }
};

#endif  // BNODE_H