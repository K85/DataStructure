#include <stdio.h>
#include <stdlib.h>
using namespace std;

template <typename T> class BinarySearchTree {

public:
  class Node {

  public:
    T value;
    Node *left;
    Node *right;

  public:
    Node(T value) : value(value), left(nullptr), right(nullptr){};
  };

public:
  Node *root = nullptr;

public:
  void inorder_walk(Node *root) {
    if (root == nullptr)
      return;
    if (root->left != nullptr)
      inorder_walk(root->left);
    printf("%d ", root->value);
    if (root->right != nullptr)
      inorder_walk(root->right);
  }

  // use Node * & to change BST's root.
public:
  void insert(Node *&root, T value) {

    // is empty tree ?
    if (root == nullptr) {
      root = new Node(value);
      return;
    }

    // find insert position.
    if (value == root->value)
      return;
    insert(value < root->value ? root->left : root->right, value);
  }

public:
  Node *find(Node *root, T value) {

    if (root == nullptr)
      return;

    if (value == root->value)
      return root;
    find(value < root->value ? root->left : root->right, value);
  }

public:
  Node *findMin(Node *root) {
    return root->left == nullptr ? root : findMin(root->left);
  }

public:
  Node *findMax(Node *root) {
    return root->right == nullptr ? root : findMax(root->right);
  }

  // use Node * & to delete Node.
public:
  void deleteNode(Node *&root, T value) {
    // is empty tree ?
    if (root == nullptr)
      return;

    // find target node.
    if (value == root->value) {

      // target node has no childs.
      if (root->left == nullptr && root->right == nullptr)
        root = nullptr;
      else if (root->left != nullptr) {
        // target node has left child.
        Node *pre = findMax(root->left);
        root->value = pre->value;
        deleteNode(root->left, root->value);
      } else {
        // otherwise.
        Node *post = findMin(root->right);
        root->value = post->value;
        deleteNode(root->right, root->value);
      }

    } else if (value < root->value)
      deleteNode(root->left, value);
    else
      deleteNode(root->right, value);
  }
};

int main() {

  BinarySearchTree<int> bst;
  bst.insert(bst.root, 100);
  bst.insert(bst.root, 200);
  bst.insert(bst.root, 400);
  bst.insert(bst.root, 300);

  bst.inorder_walk(bst.root);
  printf("\n");
  bst.deleteNode(bst.root, 100);
  bst.inorder_walk(bst.root);
  printf("\n");

  return 0;
}
