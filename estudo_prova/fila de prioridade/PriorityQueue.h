#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdexcept>

class PriorityQueue {
   private:
    char* heap;
    int size;
    int capacity;

   public:
    PriorityQueue(int capacity) : capacity(capacity) {
        heap = new char[capacity];
        size = 0;
    }

    ~PriorityQueue() {
        delete[] heap;
    }

    //* Seleção de máximo *//

    // Complexidade: O(1)
    char getMax() {
        // Se a fila de prioridade estiver vazia, lança uma exceção
        if (size == 0)
            throw std::out_of_range("PriorityQueue is empty");

        return heap[0];  // Retorna o maior elemento (raiz da árvore)
    }

    //* Alteração de prioridade *//

    //* Aumentar a prioridade *//

    // Complexidade: O(1)
    void increaseKey(int i, int key) {
        if (key < heap[i])
            throw std::invalid_argument("New key is smaller than current key");

        heap[i] = key;
        maxFixUp(i);
    }

    // Complexidade: O(log n) - Esta complexidade é desta ordem no pior caso, pois o elemento pode ter que subir até a raiz
    // para manter a propriedade de heap máximo. Subir até a raiz significa subir log n níveis (altura da árvore).
    void maxFixUp(int i) {
        int p = i / 2;  // Pai
        while (p >= 0 && heap[i] > heap[p]) {
            std::swap(heap[i], heap[p]);
            i = p;
            p /= 2;
        }
    }

    //* Diminuir a prioridade *//

    void decreaseKey(int i, int key) {
        if (key > heap[i])
            throw std::invalid_argument("New key is greater than current key");

        heap[i] = key;
        maxFixDown(i);
    }

    // Complexidade: O(log n) - Esta complexidade é desta ordem no pior caso, pois o elemento pode ter que descer até a
    // última camada da árvore para manter a propriedade de heap máximo. Descer até a última camada significa descer log n níveis.
    void maxFixDown(int i) {
        while (2 * i + 1 < size) {                    // Enquanto o nó i tiver filhos
            int l = 2 * i + 1;                        // Filho da esquerda
            int r = 2 * i + 2;                        // Filho da direita
            int largest = i;                          // Inicialmente, o maior é o próprio nó i
            if (l < size && heap[l] > heap[largest])  // Se o filho da esquerda for maior que o nó i
                largest = l;
            if (r < size && heap[r] > heap[largest])  // Se o filho da direita for maior que o maior até agora
                largest = r;
            if (largest != i) {                     // Se o maior não for o nó i
                std::swap(heap[i], heap[largest]);  // Troca o nó i com o maior
                i = largest;                        // Atualiza o índice do nó i
            } else
                break;  // Se o nó i for maior que os filhos, a propriedade de heap máximo está satisfeita
        }
    }

    //* Inserção *//

    // Complexidade: O(log n) - Esta complexidade é desta ordem no pior caso, pois o elemento pode ter que subir até a
    // raiz para manter a propriedade de heap máximo. Subir até a raiz significa subir log n níveis (altura da árvore).
    void insert(int key) {
        if (size >= capacity)
            throw std::out_of_range("PriorityQueue is full");

        heap[size] = key;
        maxFixUp(size);
        size++;
    }

    //* Remoção *//

    // Complexidade: O(log n) - Esta complexidade é desta ordem no pior caso, pois o elemento pode ter que descer até a
    // última camada da árvore para manter a propriedade de heap máximo. Descer até a última camada significa descer log n níveis.
    char extractMax() {
        if (size == 0)
            throw std::out_of_range("PriorityQueue is empty");

        int max = heap[0];         // Maior elemento
        heap[0] = heap[size - 1];  // Substitui o maior elemento pelo último
        size--;                    // Decrementa o tamanho
        maxFixDown(0);             // Restaura a propriedade de heap máximo
        return max;                // Retorna o maior elemento
    }

    //* Construção *//

    void buildMaxHeap(int* array, int n) {
        if (n > capacity)
            throw std::out_of_range("PriorityQueue is full");

        for (int i = 0; i < n; i++)
            heap[i] = array[i];
        size = n;

        for (int i = size / 2; i >= 0; i--)
            maxFixDown(i);
    }
};

#endif  // PRIORITY_QUEUE_H