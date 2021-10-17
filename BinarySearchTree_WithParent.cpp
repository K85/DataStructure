#include <cstddef>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

template <typename T> class BinarySearchTree {

public:
  class Node {
  public:
    T value;
    Node *parent;
    Node *left_child;
    Node *right_child;

  public:
    Node(T value)
        : value(value), parent(nullptr), left_child(nullptr),
          right_child(nullptr) {}
  };

public:
  Node *root = nullptr;

  // get size/height/depth of root
public:
  int size(Node *root) {
    return root ? max(size(root->left, root->right)) + 1 : 0;
  }

  // please make sure the value don't exist in tree.
public:
  void insert_node(Node *&root, T value) {

    Node *target_parent = nullptr;
    Node *aux_node = root;

    // construct target node.
    Node *target = new Node(value);

    // find insert position.
    while (aux_node != nullptr) {
      target_parent = aux_node;
      target->value < aux_node->value ? aux_node = aux_node->left_child
                                      : aux_node = aux_node->right_child;
    }

    // insert target node into y'left or right
    target->parent = target_parent;
    if (target_parent == nullptr)
      root = target;
    else
      target->value < target_parent->value
          ? target_parent->left_child = target
          : target_parent->right_child = target;
  }

public:
  Node *get_min(Node *root) {
    while (root->left_child != nullptr)
      root = root->left_child;
    return root;
  }

public:
  Node *get_max(Node *root) {
    while (root->right_child != nullptr)
      root = root->right_child;
    return root;
  }

public:
  Node *get_successor_node(Node *target) {
    if (target->right_child != nullptr)
      return get_min(target->right_child);
    Node *ans = target->parent;
    while (ans != nullptr && ans->left_child != target) {
      target = ans;
      ans = ans->parent;
    }
    return ans;
  }

public:
  void delete_node(Node *target) {

    Node *x;
    Node *y;

    // locate delete target
    if (target->left_child == nullptr || target->right_child == nullptr)
      y = target;
    else
      y = get_successor_node(target);

    //  get the child of y
    y->left_child != nullptr ? x = y->left_child : x = y->right_child;

    if (x != nullptr)
      x->parent = y->parent;

    if (y->parent == nullptr)
      root = x;
    else
      y == y->parent->left_child ? y->parent->left_child = x
                                 : y->parent->right_child = x;

    if (y != target)
      target->value = y->value;
    free(y);
  }

public:
  void preorder_walk(Node *root) {
    if (root == nullptr)
      return;

    printf("%d ", root->value);
    if (root->left_child != nullptr)
      preorder_walk(root->left_child);
    if (root->right_child != nullptr)
      preorder_walk(root->right_child);
  }

public:
  void inorder_walk(Node *root) {
    if (root == nullptr)
      return;

    if (root->left_child != nullptr)
      inorder_walk(root->left_child);
    printf("%d ", root->value);
    if (root->right_child != nullptr)
      inorder_walk(root->right_child);
  }

public:
  void postorder_walk(Node *root) {
    if (root == nullptr)
      return;
    if (root->left_child != nullptr)
      postorder_walk(root->left_child);
    if (root->right_child != nullptr)
      postorder_walk(root->right_child);
    printf("%d ", root->value);
  }

public:
  Node *find_node(Node *root, T value) {
    while (root != nullptr && value != root->value) {
      value < root->value ? root = root->left_child : root = root->right_child;
    }
    return root;
  }
};

int main() {

  BinarySearchTree<int> bst;

  bst.insert_node(bst.root, 100);
  bst.insert_node(bst.root, 400);
  bst.insert_node(bst.root, 200);
  bst.insert_node(bst.root, 500);
  bst.insert_node(bst.root, 300);
  bst.inorder_walk(bst.root);

  printf("\n");
  return 0;
}
