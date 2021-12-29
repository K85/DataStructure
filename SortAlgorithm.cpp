#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;


template<typename T>
class Heap {

public:
    vector<T> H;
    int size;

public:
    bool empty() {
      return size == 0;
    }

public:
    void init(vector<T> values) {
      this->size = values.size();
      H = values;
      make_heap(H.begin(), H.end());
    }

public:
    T top() {
      return this->H[0];
    }

public:
    void pop() {
      pop_heap(H.begin(), H.begin() + size);
      this->size--;
    }

public:
    void push(T value) {
      this->H[this->size++] = value;
      push_heap(H.begin(), H.begin() + size);
    }
};


template<typename T>
class SortAlgorithm {

public:
    void trace(vector<T> A) {
      for_each(A.begin(), A.end(), [](const T &obj) { cout << obj << " "; });
      cout << endl << endl;
    }

public:
    void heap_sort(vector<T> A) {

      Heap<T> heap;
      heap.init(A);

      while (!heap.empty()) {
        trace(heap.H);
        heap.pop();
      }
    }

public:
    void insertion_sort(vector<T> A) {
      for (int i = 1; i < A.size(); i++) {
        int pivot = A[i];
        int j = i - 1;
        if (pivot > A[j]) continue;
        while (j >= 0 && A[j] > pivot) {
          A[j + 1] = A[j];
          j--;
        }

        A[j + 1] = pivot;
        trace(A);
      }
    }

public:
    void insertion_sort_sc(vector<T> A) {
      for (int i = 1; i < A.size(); i++) {
        int j = i;
        while (j - 1 >= 0 && A[j] < A[j - 1]) {
          swap(A[j], A[j - 1]);
          j--;
        }
        trace(A);
      }
    }

public:
    void insertion_sort_sc(vector<T> A, int g) {
      for (int i = g; i < A.size(); i++) {
        int j = i;
        while (j - g >= 0 && A[j] < A[j - g]) {
          swap(A[j], A[j - g]);
          j -= g;
        }
      }
      trace(A);
    }

public:
    void insertion_sort_inverse_sc(vector<T> A) {
      for (int i = A.size() - 2; i >= 0; i--) {
        int j = i;
        while (j + 1 < A.size() && A[j] > A[j + 1]) {
          swap(A[j], A[j + 1]);
          j++;
        }
        trace(A);
      }
    }


public:
    void insertion_sort_inverse(vector<T> A) {
      for (int i = A.size() - 2; i >= 0; i--) {
        int pivot = A[i];
        int j = i + 1;
        if (pivot < A[j]) continue;
        while (j < A.size() && A[j] < pivot) {
          A[j - 1] = A[j];
          j++;
        }
        A[j - 1] = pivot;
        trace(A);
      }
    }


public:
    void insertion_sort(vector<T> A, int g) {
      for (int i = g; i < A.size(); i++) {
        int pivot = A[i];
        int j = i - g;

        while (j >= 0 && A[j] > pivot) {
          A[j + g] = A[j];
          j -= g;
        }

        A[j + g] = pivot;
        trace(A);
      }
    }

public:
    void bubble_sort_inverse_sc(vector<T> A) {
      bool this_round_modified = true;
      for (int i = 0; this_round_modified; i++) {
        this_round_modified = false;
        for (int j = A.size() - 1; j >= i + 1; j--) {
          if (A[j] < A[j - 1]) {
            swap(A[j], A[j - 1]);
            this_round_modified = true;
          }
        }
        trace(A);
      }
    }

public:
    void bubble_sort_sc(vector<T> A) {
      bool this_round_modified = true;
      for (int i = 0; this_round_modified; ++i) {
        this_round_modified = false;
        for (int j = 0; j < A.size() - 1 - i; ++j) {
          if (A[j] > A[j + 1]) {
            swap(A[j], A[j + 1]);
            this_round_modified = true;
          }
        }
        trace(A);
      }
    }


public:
    void selection_sort(vector<T> A) {
      for (int i = 0; i < A.size() - 1; i++) {
        int j_min_index = i;
        for (int j = i; j < A.size(); j++) {
          if (A[j] < A[j_min_index])
            j_min_index = j;
        }
        swap(A[i], A[j_min_index]);
        trace(A);
      }
    }

public:
    void selection_sort_inverse(vector<T> A) {
      for (int i = A.size() - 1; i >= 0; i--) {
        int j_max_index = i;
        for (int j = i; j >= 0; j--) {
          if (A[j] > A[j_max_index])
            j_max_index = j;
        }
        swap(A[i], A[j_max_index]);
        trace(A);
      }
    }

public:
    void shell_sort(vector<T> A) {

      // generate G = {1, 4, 13, 40, 121, 364 ...}
      vector<int> G;
      for (int h = 1; h <= A.size(); h = 3 * h + 1) {
        G.push_back(h);
      }

      // sort with different G.
      for (int i = G.size() - 1; i >= 0; i--) {
        insertion_sort(A, G[i]);
      }
    }


public:
    void merge_sort(vector<T> A) {
      trace(A);

      for (int G = 2; G <= A.size() * 2; G *= 2) {
        for (int k = 0; true; k++) {
          int L = k * G;
          int R = k * G + (G - 1);
          int M = k * G + G / 2;

          // final round
          if (R >= A.size()) {
            if (M < A.size()) R = A.size() - 1;
            else break;
          }

          inplace_merge(A.begin() + L, A.begin() + M, A.begin() + R + 1);
        }
        trace(A);
      }
    }

public:
    void quick_sort_stl(vector<T> &A, typename vector<T>::iterator L, typename vector<T>::iterator R) {
      if (L == R) return;
      trace(A);
      T pivot = *L;
      auto M = std::stable_partition(L, R, [pivot](T val) {
          return pivot < val;
      });
      quick_sort_stl(A, L, M);
      quick_sort_stl(A, M + 1, R);
    }

public:
    int partition_front_back_pointer_method(vector<T> &A, int p, int r) {
      int pivot = A[r];
      int i = p - 1;
      int j;

      for (j = p; j < r; j++) {
        if (A[j] <= pivot) {
          i++;
          swap(A[i], A[j]);
        }
      }

      swap(A[i + 1], A[r]);
      return i + 1;
    }

public:
    int partition_double_pointer_method(vector<T> &A, int p, int r) {
      int pp = p;
      int rr = r;

      // choose the first element as the pivot
      int pivot_index = p;
      while (p < r) {
        while (p < r && A[r] >= A[pivot_index]) r--;
        while (p < r && A[p] <= A[pivot_index]) p++;
        swap(A[p], A[r]);
      }
      swap(A[pivot_index], A[r]);
      return p;
    }

public:
    void quick_sort_front_back_pointer_method(vector<T> &A, int p, int r) {
      if (p < r) {
        // choose the first element as the pivot
        int q = partition_front_back_pointer_method(A, p, r);
        quick_sort_front_back_pointer_method(A, p, q - 1);
        quick_sort_front_back_pointer_method(A, q + 1, r);
      }
      trace(A);
    }

public:
    void quick_sort_double_pointer_method(vector<T> &A, int p, int r) {
      if (p < r) {
        // choose the first element as the pivot
        int q = partition_double_pointer_method(A, p, r);
        quick_sort_double_pointer_method(A, p, q - 1);
        quick_sort_double_pointer_method(A, q + 1, r);
      }
      trace(A);
    }

public:
    void counting_sort(vector<T> A) {

      static const int MAXN = 10000 + 1;

      // construct C[]
      vector<T> C(A.size() + 1);
      for (int i = 0; i < A.size(); i++) {
        C[A[i + 1]]++;
      }

      // build C[]
      for (int i = 1; i <= A.size(); i++)
        C[i] = C[i] + C[i - 1];

      // construct B[]
      vector<T> B(A.size() + 1);
      for (int j = 1; j <= A.size(); j++) {
        B[C[A[j]]] = A[j];
        C[A[j]]--;
      }

      // print
      for (int i = 1; i <= A.size(); i++) {
        printf("%d ", B[i]);
      }
    }
};

int main() {
  vector<int> A = {3, 6, 2, 8, 5, 9, 1, 4, 7};

  SortAlgorithm<int> SA;

  printf("before sort: \n");
  SA.trace(A);

  printf("after sort\n");
  SA.quick_sort_double_pointer_method(A, 0, A.size() - 1);

  return 0;
}
