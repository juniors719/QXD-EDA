// Questão 1 : Escreva pseudocódigos para os procedimentos minHeap - decreaseKey(A, i, newKey), minFixDown(A, i), minMoveUp(A, i), minHeap - increaseKey(A, i, newKey), minHeapInsert(A, key) e extractMinimum(A), que implementem uma fila de prioridade mínima com um heap de mínimo.Obs. : Note que todos esses procedimentos são versões similares às vistas em sala, só que aqui estou pedindo para uma fila de prioridades mínima.Estou pedindo pseudocódigo, não escreva implementações em linguagem de programação específica.

#include <iostream>
#include <stdexcept>
#include <vector>

class minHeap {
   private:
    std::vector<int> A;    // array de elementos
    unsigned heapSize{0};  // numero de elementos do heap

   public:
    minHeap() {
        A.push_back(0);
    }

    unsigned size() {
        return heapSize;
    }

    void minHeap_decreaseKey(std::vector<int>& A, int i, int newKey) {
        if (newKey > A[i])
            throw std::runtime_error("new key is greater than current key");
        A[i] = newKey;
        minMoveUp(i);
    }

    void minFixDown(int i) {
        int l = 2 * i;
        int r = 2 * i + 1;
        int smallest = i;
        if (l <= heapSize && A[l] < A[i])
            smallest = l;
        if (r <= heapSize && A[r] < A[smallest])
            smallest = r;
        if (smallest != i) {
            std::swap(A[i], A[smallest]);
            minFixDown(smallest);
        }
    }

    void minMoveUp(int i) {
        while (i > 1 && A[i / 2] > A[i]) {
            std::swap(A[i], A[i / 2]);
            i = i / 2;
        }
    }

    void minHeap_increaseKey(std::vector<int>& A, int i, int newKey) {
        if (newKey < A[i])
            throw std::runtime_error("new key is smaller than current key");
        A[i] = newKey;
        minFixDown(i);
    }

    void minHeapInsert(std::vector<int>& A, int key) {
        heapSize++;
        A.push_back(key);
        minMoveUp(heapSize);
    }

    int extractMinimum(std::vector<int>& A) {
        if (heapSize < 1)
            throw std::runtime_error("heap underflow");
        int min = A[1];
        A[1] = A[heapSize];
        heapSize--;
        minFixDown(1);
        return min;
    }
};