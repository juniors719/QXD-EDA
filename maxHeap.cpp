#include <iostream>

template <typename Type>
void getMax() {
    if (A.heapSize > 0) {
        return A[i];
    } else {
        throw std::runtime_error("Error");
    }
}

template <typename Type>
void maxHeap_increaseKey(Type A[], Type i, Type newKey) {
    if (newKey < A[i]) {
        throw std::runtime_error("invalid key");
    } else {
        A[i] = newKey;
        maxFixUp(A, i);
    }
}

template <typename Type>
void maxFixUp(Type A[], Type i) {
    Type p = i / 2;
    while (i > 1 && A[i / 2] < A[i]) {
        std::swap(A[p], A[i]);
        i = p;
        p /= 2;
    }
}

template <typename Type>
void maxHeap_decreaseKey(Type A[], Type i, Type newKey) {
    if (A[i] < newKey) {
        throw std::runtime_error("chave inexistente");
    }
    A[i] = newKey;
    maxFixDown(A, i);
}

/* template <typename Type>
void maxFixDown(Type A[], Type i) {
    Type l = 2 * i;
    Type r = 2 * i + 1;
    Type maior = i;
    if (l <= A.heapSize && A[l] > A[i]) {
        maior = l;
    }
    if (r <= A.heapSize && A[r] > A[maior]) {
        maior = r;
    }
    if (maior != i) {
        std::swap(A[i], A[maior]);
        maxFixDown(A, maior);
    }
} */

// Versão iterativa
template <typename Type>
void maxFixDown(Type A[], Type i) {
    while (2 * i <= A.heapSize) {
        Type l = 2 * i;
        Type r = 2 * i + 1;
        Type maior = i;
        if (l <= A.heapSize && A[l] > A[maior])
            maior = l;
        if (r <= A.heapSize && A[r] > A[maior])
            maior = r;
        if (maior != i) {
            std::swap(A[i], A[maior]);
            i = maior;
        } else
            break;
    }
}

template <typename Type>
void maxHeap_insert(Type A[], Type newKey) {
    if (A.heapSize >= A.length)
        throw std::runtime_error("heap overflow");
    A.heapSize++;
    A[A.heapSize] = newKey;
    maxFixUp(A, A.heapSize);
}
// complexidade O(log n)

template <typename Type>
void maxHeap_extractMax(Type A[]) {
    if (A.heapSize < 1)
        throw std::runtime_error("heap underflow");
    Type max = A[1];
    A[1] = A[A.heapSize];
    A.heapSize--;
    maxFixDown(A, 1);
    return max;
}

// Suponha que nos seja dado de início um vetor com n > 0 elementos. Como transformar este vetor em um heap máximo?
// int B[] = {4, 8, 2, 7, 6, 3, 5, 1, 9, 10};
/* void buildMaxHeap(int A[]) {
    for(int i = 2; i <= A.heapSize; i++) {
        maxFixUp(A, i);
    }
} */

int main() {
}