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
        : value(value), left(left), right(right){};

  public:
    Node(T value) : Node(value, nullptr, nullptr){};
  };

public:
  Node *root = nullptr;

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
  Node *find_node(Node *root, T value) {
    while (root != nullptr && value != root->value) {
      if (value == root->value)
        return root;
      root = value < root->value ? root->left : root->right;
    }
    return nullptr;
  }

  // NOTE: you must make sure the elements in tree are unique.
  // NOTE: the param root must be *& for insert into empty tree.
public:
  void insert_node(Node *&root, T value) {

    // construct target node.
    Node *target_node = new Node(value);

    // find insert position.
    Node *p = root;
    Node *pp = nullptr; // record the parent of p
    while (p != nullptr) {
      pp = p;
      p = value < p->value
              ? p->left
              : p->right; // if you need to update same node, modify here.
    }

    // link pointers.
    if (root != nullptr) { // check: empty tree ?
      value < pp->value ? (pp->left = target_node) : (pp->right = target_node);
    } else
      root = target_node;
  }

public:
  void delete_node(Node *&root, T value) {

    // find delete position.
    Node *insert_node = root;
    Node *insert_node_parent = nullptr;
    while (insert_node != nullptr && value != insert_node->value) {
      insert_node_parent = insert_node;
      insert_node =
          value < insert_node->value ? insert_node->left : insert_node->right;
    }

    if (insert_node == nullptr) {
      // printf("sorry, can't find target node.\n");
      return;
    }

    /* delete cases. */

    /* case1: p has 2 childs. */
    if (insert_node->left != nullptr && insert_node->right != nullptr) {

      // find minest_node (it's ok to find maxest_node instead).
      Node *most_node = insert_node->left;
      Node *most_node_parent = insert_node;
      while (most_node->left != nullptr) {
        most_node_parent = most_node;
        most_node = most_node->left;
      }

      /* cover value. */
      // p->value = most_node->value;  why ?

      // re-link pointers.
      Node *target_node =
          new Node(most_node->value, insert_node->left, insert_node->right);
      if (insert_node_parent == nullptr)
        root = target_node;
      else
        insert_node == insert_node_parent->left
            ? (insert_node_parent->left = target_node)
            : (insert_node_parent->right = target_node);

      // find insert_node_parent
      insert_node_parent =
          (most_node_parent == most_node) ? target_node : most_node_parent;

      delete insert_node;
      insert_node = most_node;
    }

    /* case2 (from case1): p has at most 1 child. */
    Node *only_child;
    only_child =
        insert_node->left != nullptr ? insert_node->left : insert_node->right;

    // delete p
    if (insert_node == root)
      root = only_child;
    else {
      // re-link.
      insert_node == insert_node_parent->left
          ? (insert_node_parent->left = only_child)
          : (insert_node_parent->right = only_child);
      delete insert_node;
    }
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

  bst.delete_node(bst.root, 300);
  bst.inorder_walk(bst.root);
  printf("\n");

  return 0;
}
