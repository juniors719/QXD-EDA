#include <iostream>

#include "Tree.hpp"

using namespace std;

int main() {
    Tree<int> tree;

    for (int i = 11; i <= 15; i++) {
        tree.add(i);
    }

    tree.inOrdem();
    cout << endl;

    tree.preOrdem();
    cout << endl;

    tree.posOrdem();
    cout << endl;

    if (tree.contains(18)) {
        cout << "18 está na árvore" << endl;
    } else {
        cout << "18 não está na árvore" << endl;
    }

    return 0;
}