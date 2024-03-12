#ifndef MINHEAP_H
#define MINHEAP_H

#include <iostream>
#include <vector>

class MinHeap {
   public:
    MinHeap() {
        heap = std::vector<int>();
    }
    MinHeap(std::vector<int> &v) {
        heap = v;
        for (int i = (heap.size() - 1) / 2; i >= 0; i--) {
            minHeapify(i);
        }
    }
    ~MinHeap() {
        heap.clear();
    }

    void minHeapDecreaseKey(int i, int newKey) {
        if (newKey > heap[i]) {
            std::cout << "New key is greater than current key" << std::endl;
            return;
        }
        heap[i] = newKey;
        minMoveUp(i);
    }
    void minFixDown(int i) {
        minHeapify(i);
    }
    void minMoveUp(int i) {
        while (i > 0 && heap[parent(i)] > heap[i]) {
            std::swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }
    void minHeapIncreaseKey(int i, int newKey) {
        if (newKey < heap[i]) {
            std::cout << "New key is smaller than current key" << std::endl;
            return;
        }
        heap[i] = newKey;
        minFixDown(i);
    }
    void minHeapInsert(int key) {
        heap.push_back(key);
        minMoveUp(heap.size() - 1);
    }
    int extractMinimum() {
        if (heap.size() < 1) {
            std::cout << "Heap underflow" << std::endl;
            return -1;
        }
        int min = heap[0];
        heap[0] = heap[heap.size() - 1];
        heap.pop_back();
        minHeapify(0);
        return min;
    }

    void print();

   private:
    std::vector<int> heap;
    int parent(int i) {
        return (i - 1) / 2;
    }
    int left(int i) {
        return 2 * i + 1;
    }
    int right(int i) {
        return 2 * i + 2;
    }
    void minHeapify(int i) {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < heap.size() && heap[l] < heap[i]) {
            smallest = l;
        }
        if (r < heap.size() && heap[r] < heap[smallest]) {
            smallest = r;
        }
        if (smallest != i) {
            std::swap(heap[i], heap[smallest]);
            minHeapify(smallest);
        }
    }
};

#endif  // MINHEAP_H