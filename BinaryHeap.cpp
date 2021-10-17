#include <iterator>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

// heap is a complete binary tree.
// the heap is a min tree.
template<typename T>
class Heap {


  public:
    vector<T> H;

  public:
    Heap() {
      // keep v[0] as sentinel.
      H.resize(1);
    }

  public:
    bool empty() {
      return true;
    }

  public:
    int size() {
      return H.size() - 1;
    }


  public:
    void push(T value) {
      H.push_back(value);

      int i = H.size() - 1;
      while (i > 1 && H[i / 2] < H[i]) {
        swap(H[i], H[i / 2]);
        i /= 2;
      }
    }

  public:
    void pop() {
      if (H.size() <= 1) return;

      H[1] = H[H.size() - 1];
      H.pop_back();

      min_heapify(1);
    }

  public:
    void min_heapify(int i) {
      int l, r, most;
      l = 2 * i;
      r = l + 1;

      printf("i = %d, size = %d\n", i, H.size() );

      // find the most node 
      if (l <= H.size() && H[i] < H[l]) most = i;
      else most = l;
      if (r <= H.size() && H[most] > H[r]) most = r;

      if (most != i) {
        printf("swap i = %d, most = %d\n", i , most);
        swap(H[i], H[most]);
        min_heapify(most);
      }
    }

  public:
    void trace() {
      copy(H.begin() + 1, H.end(), ostream_iterator<T>(cout, " "));
    }

};


int main() {

  Heap<int> heap;

  heap.push(3);
  heap.push(4);
  heap.push(1);
  heap.push(2);

  heap.trace();

  heap.pop();
  heap.trace();

  heap.pop();
  heap.trace();
  
  return 0;
}

