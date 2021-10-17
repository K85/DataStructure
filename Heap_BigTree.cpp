#include <cstdio>
#include <iostream>
#include <iterator>
#include <stdio.h>

using namespace std;

template <typename T> class Heap {

private:
  T *A;
  int A_size;
  int heap_size;

public:
  Heap(int capacity) {
    this->A_size = 2 * capacity;
    this->heap_size = 0;
    this->A = (T *)malloc(sizeof(T) * this->A_size);
  }

public:
  void push(T value) {
    // find the insert position.
    int ptr = ++heap_size;
    while (ptr != 1 && A[ptr / 2] < value) {
      A[ptr] = A[ptr / 2];
      ptr /= 2;
    }
    A[ptr] = value;
  }

public:
  void pop() {

    // free element.
    A[1].~T();

    // get last element.
    T last_element = A[heap_size--];

    int ptr = 1;
    int ptr_child = 2;
    while (ptr_child <= heap_size) {
      // heap[child] is the bigger in brothers.
      if (ptr_child < heap_size && A[ptr_child] < A[ptr_child + 1])
        ptr_child++;

      // can put last element in heap[ptr] ?
      if (last_element >= A[ptr_child])
        break;
      else {
        A[ptr] = A[ptr_child]; // move the child up
        ptr = ptr_child;       // find in the low
        ptr_child *= 2;
      }
    }
    A[ptr] = last_element;
  }

public:
  T top() { return A[1]; }

  // v means the vector of heap elements with null header.
  // length means the amonut of length.
public:
  void initialize(T *v, int length) {
    // build heap in [1:capacity]
    delete[] this->A;
    this->A = v;
    this->heap_size = length - 1;

    // heapify
    for (int root = heap_size / 2; root >= 1; root--) {
      T root_element = A[root];

      // find insert position.
      int child = 2 * root;
      while (child <= heap_size) {
        if (child < heap_size && A[child] < A[child + 1]) {
          child++;
        }

        // can put root element in heap[child / 2] ?
        if (root_element >= A[child])
          break;
        else {
          A[child / 2] = A[child];
          child *= 2;
        }
      }
      A[child / 2] = root_element;
    }
  }

public:
  void trace() {
    copy(A + 1, A + heap_size + 1, ostream_iterator<T>(cout, " "));
  }

public:
  bool empty() { return heap_size == 0; }

public:
  int size() { return this->heap_size; }
};

int main() {

  // construct heap.
  Heap<int> heap(100);
  // heap.push(56);
  // heap.push(62);
  // heap.push(80);
  // heap.push(77);
  int arr[] = {-1, 100, 200, 300};
  heap.initialize(arr, 4);
  heap.trace();
  printf("\n");

  // pop all elements.
  while (!heap.empty()) {
    heap.trace();
    printf("\n");
    int value = heap.top();
    heap.pop();
    printf("pop element: %d\n\n", value);
  }

  return 0;
}
