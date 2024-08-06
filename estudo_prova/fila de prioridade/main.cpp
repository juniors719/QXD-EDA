#include <iostream>

#include "BST.h"
#include "PriorityQueue.h"

int main() {
    BST bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    std::cout << bst.contains(5) << std::endl;  // Saída: 1
    std::cout << bst.contains(8) << std::endl;  // Saída: 0
}