#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

template <typename T> class LinearList {
public:
  T *A;
  int capacity;
  int size;
  double auto_expansion_factor;

public:
  LinearList(int capacity, double auto_expansion_factor) {
    this->capacity = capacity;
    this->size = 0;
    this->auto_expansion_factor = auto_expansion_factor;
    this->A = (T *)malloc(capacity * sizeof(T));
  }

public:
  LinearList(int capacity) : LinearList(capacity, 2.0){};

public:
  void append_element(T value) { this->A[size++] = value; }

public:
  int search_element(T value) { return find(A, A + size, value) - A; }

public:
  void insert_element(int index, T value) {
    memmove(&A[index + 1], &A[index], (size++ - index) * sizeof(T));
    A[index] = value;
  }

public:
  void remove_element(int index) {
    memmove(&A[index], &A[index + 1], (size-- - index - 1) * sizeof(T));
  }

public:
  void remove_elements(T value) { size = remove(A, &A[size], value) - A; }

public:
  void unique_elements() { size = unique(A, &A[size]) - A; }

public:
  void trace_elements() {
    for (int i = 0; i < size; i++)
      cout << A[i] << " ";
  }

public:
  bool is_full() { return size >= capacity; }

public:
  void append_element_safely(T value) {
    if (is_full())
      resize(capacity * auto_expansion_factor);
    append_element(value);
  }

public:
  void insert_element_safely(int index, T value) {
    if (is_full())
      resize(capacity * auto_expansion_factor);
    insert_element(index, value);
  }

private:
  void resize(int new_capacity) {
    T *target = (T *)realloc(A, new_capacity * sizeof(T));

    if (target == nullptr)
      target = (T *)malloc(new_capacity * sizeof(T));
    memcpy(target, A, size * sizeof(T));

    // update props
    printf("the linear list is full, auto expand capacity from %d to %d (new "
           "address: %p)\n",
           capacity, new_capacity, target);
    A = target;
    capacity = new_capacity;
  }
};

int main() {

  // Test
  LinearList<int> ll(1, 2.0);

  ll.append_element_safely(0);
  ll.append_element_safely(1);
  ll.append_element_safely(2);
  ll.append_element_safely(3);
  ll.append_element_safely(4);
  ll.append_element_safely(5);
  ll.append_element_safely(5);
  ll.append_element_safely(5);
  ll.append_element_safely(5);
  ll.append_element_safely(5);
  ll.append_element_safely(6);
  ll.append_element_safely(6);
  ll.append_element_safely(7);
  ll.append_element_safely(7);
  ll.append_element_safely(8);
  printf("\n\nafter insert elements: \n");
  ll.trace_elements();

  printf("\n\nafter remove element in index 1: \n");
  ll.remove_element(1);
  ll.trace_elements();

  printf("\n\nafter remove all element 6: \n");
  ll.remove_elements(6);
  ll.trace_elements();

  printf("\n\nafter unique all elements: \n");
  ll.unique_elements();
  ll.trace_elements();

  printf("\n\nafter insert in index 4 with value 100\n");
  ll.insert_element_safely(4, 100);
  ll.trace_elements();

  printf("\n\nthe first value 4 is at index: %d\n", ll.search_element(4));
  ll.trace_elements();
  printf("\n\n");
  return 0;
}
