//
// Created by Hasanga Ranasinghe on 2023-06-02.
//
#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Heap {
private:
    vector<T> heap;
    bool isBuildHeap = false;
    long size;

    void maxHeapify(long currentIndex) {
        long left = (currentIndex + 1) * 2 - 1;
        long right = (currentIndex + 1) * 2;
        long largest = currentIndex;
        if (left < size && heap[left] > heap[currentIndex]) {
            largest = left;
        }
        if (right < size && heap[right] > heap[largest]) {
            largest = right;
        }
        if (largest != currentIndex) {
            T temp = heap[currentIndex];
            heap[currentIndex] = heap[largest];
            heap[largest] = temp;
            maxHeapify(largest);
        }
    }

//    void maxHeapify(long currentIndex) {
//        while (heap[currentIndex] > heap[(currentIndex + 1) / 2 - 1] && currentIndex > 0)  {
//            T element = heap[currentIndex];
//            heap[currentIndex] = heap[(currentIndex + 1) / 2 - 1];
//            heap[(currentIndex + 1) / 2 - 1] = element;
//            currentIndex = (currentIndex + 1) / 2 - 1;
//        }
//    }

//    void minHeapify(long currentIndex) {
//        while (heap[currentIndex] < heap[(currentIndex + 1) / 2 - 1] && currentIndex > 0)  {
//            T element = heap[currentIndex];
//            heap[currentIndex] = heap[(currentIndex + 1) / 2 - 1];
//            heap[(currentIndex + 1) / 2 - 1] = element;
//            currentIndex = (currentIndex + 1) / 2 - 1;
//        }
//    }

    void buildHeap() {
        isBuildHeap = true;
        for (int i = size / 2 - 1; i > 0; i--) {
            maxHeapify(i);
        }
    }

public:
    Heap(T root) {
        heap.push_back(root);
        size++;
    }

    Heap() {}

    Heap(vector<T> arr) {
        this->heap = arr;
        this->size = arr.size();
    }

    void insert(T element) {
        size++;
        isBuildHeap = false;
        if (heap.size() == 0) {
            heap.push_back(element);
            return;
        }
        heap.push_back(element);
        int currentIndex = heap.size() - 1;

        while (heap[currentIndex] > heap[(currentIndex + 1) / 2 - 1] && currentIndex > 0)  {
            T element = heap[currentIndex];
            heap[currentIndex] = heap[(currentIndex + 1) / 2 - 1];
            heap[(currentIndex + 1) / 2 - 1] = element;
            currentIndex = (currentIndex + 1) / 2 - 1;
        }
    }

    T pop_front() {
        T temp = heap[0];
        heap[0] = heap[heap.size() - 1];
        heap.pop_back();
        size--;

        maxHeapify(0);

        return temp;
    }

    void clear() {
        heap.clear();
    }

    void print() {
        for (int i = 0;i < heap.size(); i++) {
            if (i != heap.size() - 1) {
                cout << heap[i] << ", ";
            }
            else {
                cout << heap[i] << endl;
            }
        }
    }

    vector<int> heapSort() {
        if (!isBuildHeap) {
            buildHeap();
        }

        for (int i = heap.size() - 1; i > 0; i--) {
            T temp = heap[i];
            heap[i] = heap[0];
            heap[0] = temp;
            size--;
            maxHeapify(0);
        }
        size = heap.size();
        return heap;
    }
};

int main() {
    Heap<int> *heap = new Heap<int>();
    heap->insert(16);
    heap->insert(15);
    heap->insert(8);
    heap->insert(10);
    heap->insert(20);
    heap->insert(18);
    heap->print();
    heap->pop_front();
    heap->print();

    vector<int> arr = heap->heapSort();

    for (int x: arr) {
        cout << x << " ";
    }
}