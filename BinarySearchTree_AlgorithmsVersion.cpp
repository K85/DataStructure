#include <cstddef>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

template <typename T> class BinarySearchTree {

  // Node
public:
  class Node {
  public:
    T value;
    Node *left_child;
    Node *right_child;

  public:
    Node(T value, Node *left_child, Node *right_child)
        : value(value), left_child(left_child), right_child(right_child) {}
  };

public:
  Node *root = new Node(0, nullptr, nullptr);

  // get size/height/depth of root
public:
  int size(Node *root) {
    if (root == nullptr)
      return 0;

    int leftCount = size(root->left_child);
    int rightCount = size(root->right_child);

    return leftCount > rightCount ? leftCount + 1 : rightCount + 1;
  }

public:
  Node *find(Node *root, T value) {
    if (root == nullptr)
      return nullptr;

    if (value < root->value)
      return find(root->left_child, value);
    else if (value > root->value)
      return find(root->right_child, value);
    return root;
  }

public:
  Node *min(Node *root) {
    return root->left_child == nullptr ? root : min(root->left_child);
  }

public:
  Node *floor(Node *root, T value) {
    if (root == nullptr)
      return nullptr;
    if (value < root->value)
      floor(root->left_child, value);
    else if (value == root->value)
      return value;

    Node *t = floor(root->right_child, value);
    return t != nullptr ? t : root;
  }

public:
  Node *select(Node *root, int k) {
    if (root == nullptr)
      return nullptr;

    int t = size(root->left_child);
    if (t > k)
      return select(root->left_child, k);
    else if (t < k)
      return select(root->right_child, k);
    return root;
  }

public:
  int rank(Node *root, T value) {
    if (root == nullptr)
      return 0;

    if (value < root->value)
      return rank(root->left_child, value);
    else if (value > root->value)
      return (1 + size(root->left_child)) + rank(root->right_child, value);
    return size(root->left_child);
  }

public:
  Node *deleteMin(Node *root) {
    if (root->left_child == nullptr)
      return root->right_child;
    root->left_child = deleteMin(root->left_child);
    return root;
  }

public:
  Node *insertNode(Node *root, T value) {

    if (root == nullptr)
      return new Node(value, nullptr, nullptr);
    if (value < root->value)
      root->left_child = insertNode(root->left_child, value);
    else if (value > root->value)
      root->right_child = insertNode(root->right_child, value);

    return root;
  }

public:
  Node *deleteNode(Node *root, T value) {

    if (root == nullptr)
      return nullptr;

    // locate target Node.
    if (value < root->value)
      root->left_child = deleteNode(root->left_child, value);
    else if (value > root->value)
      root->right_child = deleteNode(root->right_child, value);
    else {
      if (root->right_child == nullptr)
        return root->left_child;
      if (root->left_child == nullptr)
        return root->right_child;

      Node *t = root;
      root = min(t->right_child);
      root->right_child = deleteMin(t->right_child);
      root->left_child = t->left_child;
    }

    // return root.
    return root;
  }

public:
  queue<T> keys(Node *root, const T &low_value, const T &high_value) {
    queue<T> ans;
    keys(root, ans, low_value, high_value);
    return ans;
  }

public:
  void keys(Node *root, queue<T> &ans, const T &low_value,
            const T &high_value) {

    if (root == nullptr)
      return;
    if (low_value < root->value)
      keys(root->left_child, ans, low_value, high_value);
    if (low_value <= root->value && high_value >= root->value)
      ans.push(root);
    if (high_value > root->value)
      keys(root->right_child, ans, low_value, high_value);
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
};

int main() {

  BinarySearchTree<int> bst;

  bst.root->value = 4;
  //bst.insertNode(bst.root, 4);
  bst.insertNode(bst.root, 7);
  bst.insertNode(bst.root, 2);
  bst.insertNode(bst.root, 6);
  bst.insertNode(bst.root, 3);
  bst.insertNode(bst.root, 1);
  bst.insertNode(bst.root, 8);
  bst.insertNode(bst.root, 5);
  bst.insertNode(bst.root, 10);
  bst.insertNode(bst.root, 9);
  bst.insertNode(bst.root, 11);
  bst.preorder_walk(bst.root);

  return 0;
}
