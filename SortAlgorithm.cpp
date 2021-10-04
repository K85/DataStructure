#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

template <typename T> class SortAlgorithm {

public:
  void trace(vector<T> A) {
    for_each(A.begin(), A.end(), [](const T &obj) { cout << obj << " "; });
    cout << endl << endl;
  }

public:
  void insertionSort(vector<T> A) {

    for (int i = 1; i < A.size(); i++) {
      int pivot = A[i];
      int j = i - 1;

      while (j >= 0 && A[j] > pivot) {
        A[j + 1] = A[j];
        j--;
      }

      A[j + 1] = pivot;
      trace(A);
    }
  }

public:
  void insertionSort(vector<T> A, int G) {
    for (int i = G; i < A.size(); i++) {
      int pivot = A[i];
      int j = i - G;

      while (j >= 0 && A[j] > pivot) {
        A[j + G] = A[j];
        j -= G;
      }

      A[j + G] = pivot;
      trace(A);
    }
  }

public:
  void bubbleSort(vector<T> A) {
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
  void selectionSort(vector<T> A) {
    int i, j, t, min_j;

    for (int i = 0; i < A.size() - 1; i++) {

      min_j = i;
      for (j = i; j < A.size(); j++) {
        if (A[j] < A[min_j])
          min_j = j;
      }
      swap(A[i], A[min_j]);
      trace(A);
    }
  }

public:
  void shellSort(vector<T> A) {

    // generate G = {1, 4, 13, 40, 121, 364 ...}
    vector<int> G;
    for (int h = 1; h <= A.size(); h = 3 * h + 1) {
      G.push_back(h);
    }

    // sort with different G.
    for (int i = G.size() - 1; i >= 0; i--) {
      insertionSort(A, G[i]);
    }
  }

public:
  void merge(vector<T> &A, int left, int mid, int right) {

    static const int MAX = 5000;
    static const int SENTINEL = 20000000;
    static int L[MAX / 2 + 2];
    static int R[MAX / 2 + 2];

    int n1 = mid - left;
    int n2 = right - mid;

    for (int i = 0; i < n1; i++)
      L[i] = A[left + i];
    for (int i = 0; i < n2; i++)
      R[i] = A[mid + i];

    L[n1] = R[n2] = SENTINEL;
    int i = 0, j = 0;
    for (int k = left; k < right; k++) {
      L[i] <= R[j] ? A[k] = L[i++] : A[k] = R[j++];
    }
  }

public:
  void mergeSort(vector<T> A, int left, int right) {
    trace(A);

    if (left + 1 < right) {
      int mid = (left + right) / 2;
      mergeSort(A, left, mid);
      mergeSort(A, left, right);
      merge(A, left, mid, right);
    }
  }

public:
  int partition(vector<T> A, int p, int r) {
    int i, j;
    int t, x;
    x = A[r];
    i = p - 1;

    for (j = p; j < r; j++) {
      if (A[j] <= x) {
        i++;
        swap(A[i], A[j]);
      }
    }

    swap(A[i + 1], A[r]);
    return i + 1;
  }

public:
  void quickSort(vector<T> A, int p, int r) {

    trace(A);
    if (p < r) {
      int q = partition(A, p, r);
      quickSort(A, p, q - 1);
      quickSort(A, q + 1, r);
    }
  }

public:
  void countingSort(vector<T> A) {

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

  SA.insertionSort(A);

  return 0;
}
