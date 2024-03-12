#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
#include <stdexcept>
#include <vector>

/**
 * @brief Classe que implementa uma fila de prioridade de máximo.
 * Para que ela funcione com o seu tipo T, o tipo T tem que
 * sobrecarregar o operador <
 *
 */
template <typename T, typename Comparator>
class PriorityQueue {
   private:
    std::vector<T> A;      // array de elementos
    unsigned heapSize{0};  // numero de elementos do heap
    Comparator compara;

   public:
    /**
     * @brief Construct a new Priority Queue object
     *
     * Construtor padrão
     *
     */
    PriorityQueue() {
        A.push_back(T());
    }

    /**
     * @brief Retorna o tamanho da fila de prioridade
     *
     * @return unsigned
     */
    unsigned size() {
        return heapSize;
    }

    /**
     * @brief Retorna o elemento de maior prioridade
     *
     * @return T
     */
    T top() {
        if (heapSize == 0)
            throw std::runtime_error("empty queue");
        return A[1];
    }

    /**
     * @brief Recebe um valor e insere ele na fila de prioridade
     *
     * @param v Valor a ser inserido
     */
    void push(const T& v) {
        A.push_back(v);
        heapSize++;
        maxFixUp(heapSize);
    }

    void print() {
        for (unsigned i = 1; i <= heapSize; i++) {
            std::cout << A[i] << " ";
        }
        std::cout << std::endl;
    }

    /**
     * @brief remove o elemento de maior prioridade
     *
     */
    T pop() {
        if (heapSize == 0)
            throw std::runtime_error("empty queue");
        T aux = A[1];
        A[1] = A[heapSize];
        heapSize--;
        maxFixDown(1);
        return aux;
    }

   private:
    void maxFixUp(unsigned index) {
        if (index > 1 && compara(A[index], A[index / 2])) {
            T aux = A[index];
            A[index] = A[index / 2];
            A[index / 2] = aux;
            maxFixUp(index / 2);
        }
    }

    void maxFixDown(unsigned index) {
        unsigned left = 2 * index;                                           // filho esquerdo
        unsigned largest = index;                                            // maior elemento, inicialmente é o pai
        while (left <= heapSize) {                                           // enquanto tiver filho
            if (compara(A[left], A[largest]))                                // se o filho é maior que o pai
                largest = left;                                              // maior elemento é o filho
            if ((left + 1 <= heapSize) && compara(A[left + 1], A[largest]))  // se o filho da direita é maior que o maior elemento
                largest = left + 1;                                          // maior elemento é o filho da direita
            if (largest != index) {                                          // se o maior elemento não é o pai
                std::swap(A[index], A[largest]);                             // troca o pai com o maior elemento
                index = largest;                                             // atualiza o índice do pai
                left = 2 * index;                                            // atualiza o índice do filho
            } else                                                           // se o maior elemento é o pai
                break;                                                       // termina o loop
        }
    }
};

#endif  // PRIORITY_QUEUE_H