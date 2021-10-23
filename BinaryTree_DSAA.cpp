#include <iostream>
#include <stdio.h>

using namespace std;

template <typename T> class BinaryTree {

public:
  int A_CAPACITY;
  int size;
  T *A; // dynamic malloc array. skip A[0], use A[1] as the root of tree.
  T NIL;

public:
  BinaryTree(int a_capacity, T nil) {
    this->A_CAPACITY = a_capacity;
    this->size = 0;
    this->NIL = nil;

    // malloc for tree array.
    A = (T *)new T(a_capacity);
    fill(A, A + a_capacity, nil);
  }

public:
  int parent(int node) { return node / 2; }

public:
  int left_child(int node) { return node * 2; }

public:
  int right_child(int node) { return node * 2 + 1; }

public:
  void print_array() {
    for (int i = 0; i < A_CAPACITY; i++) {
      cout << A[i] << " ";
    }
    cout << endl;
  }

public:
  bool valid_node(int index) { return index >= 1 && index <= size; }

public:
  void insert_node(int index, T value) { A[index] = value; }

public:
  void delete_node(int index) { A[index] = NIL; }

public:
  void preorder_walk(int root) {
    if (A[root] == NIL)
      return;
    cout << A[root] << " ";
    if (left_child(root) != NIL)
      preorder_walk(left_child(root));
    if (right_child(root) != NIL)
      preorder_walk(right_child(root));
  }

public:
  void inorder_walk(int root) {
    if (A[root] == NIL)
      return;
    if (left_child(root) != NIL)
      inorder_walk(left_child(root));
    cout << A[root] << " ";
    if (right_child(root) != NIL)
      inorder_walk(right_child(root));
  }

public:
  void postorder_walk(int root) {
    if (A[root] == NIL)
      return;
    if (left_child(root) != NIL)
      postorder_walk(left_child(root));
    if (right_child(root) != NIL)
      postorder_walk(right_child(root));
    cout << A[root] << " ";
  }
};

int main() {

  BinaryTree<int> bt(30, -1);
  bt.print_array();

  bt.insert_node(1, 100);
  bt.insert_node(2, 300);
  bt.insert_node(3, 200);

  bt.print_array();
  bt.preorder_walk(1);
  printf("\n");
  bt.inorder_walk(1);
  printf("\n");
  bt.postorder_walk(1);
  printf("\n");

  return 0;
}
