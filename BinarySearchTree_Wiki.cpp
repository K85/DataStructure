#include <iostream>
#include <stdio.h>

using namespace std;

template <typename T> class BinarySearchTree {

public:
  class Node {
  public:
    T value;
    Node *left;
    Node *right;

  public:
    Node(T value, Node *left, Node *right)
        : value(value), left(left), right(right) {}

  public:
    Node(T value) : Node(value, nullptr, nullptr) {}
  };

public:
  Node *root = nullptr;

public:
  Node *search_recursively(Node *root, T value) {
    if (value == root->value)
      return root;
    return search_iteratively(value < root->value ? root->left : root->right,
                              value);
  }

public:
  Node *search_iteratively(Node *root, T value) {
    while (root != nullptr && root->value != value) {
      root = value < root->value ? root->left : root->right;
    }
    return root;
  }

public:
  void inorder_walk(Node *root) {
    if (root == nullptr)
      return;
    if (root->left != nullptr)
      inorder_walk(root->left);
    cout << root->value << " ";
    if (root->right != nullptr)
      inorder_walk(root->right);
  }

public:
  void insert_node(Node *&root, T value) {
    if (root == nullptr) {
      root = new Node(value);
      return;
    }

    insert_node(value < root->value ? root->left : root->right, value);
  }

public:
  Node *min_node(Node *root) {
    return root->left ? min_node(root->left) : root;
  }

public:
  Node *max_node(Node *root) {
    return root->right ? max_node(root->right) : root;
  }

public:
  Node *replace_node_in_parent(Node *root, Node *child) {}

public:
  void delete_node(Node *root, T value) {

    // check nullptr.
    if (root == nullptr)
      return;

    // locate delete target.
    if (value == root->value) {

      if (root->left == nullptr && root->right == nullptr)
        root = nullptr;
      else if (root->left != nullptr) {
        root->value = max_node(root->left)->value;
        delete_node(root->left, root->value);
      } else {
        root->value = min_node(root->right)->value;
        delete_node(root->right, root->value);
      }

    } else
      delete_node(value < root->value ? root->left : root->right, value);
  }
};

int main() {

  BinarySearchTree<int> bst;
  bst.insert_node(bst.root, 100);
  bst.insert_node(bst.root, 200);
  bst.insert_node(bst.root, 400);
  bst.insert_node(bst.root, 300);

  bst.inorder_walk(bst.root);
  printf("\n");
  bst.delete_node(bst.root, 100);
  bst.inorder_walk(bst.root);
  printf("\n");

  return 0;
}
