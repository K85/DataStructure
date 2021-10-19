#include <stdlib.h>
#include <stdio.h>
#include <deque>
#include <queue>
#include <stack>
#include <type_traits>
#include <vector>
#include <algorithm>
using namespace std;
template <typename T> class BinaryTree {

public:
  class Node {
  public:
    T value;
    Node *left_child;
    Node *right_child;

  public:
    Node(T value) : value(value), left_child(nullptr), right_child(nullptr) {}
  };

public:
  Node *root = nullptr;

public:
  int size(Node *root) {
    return root ? max(size(root->left_child), size(root->right_child)) + 1 : 0;
  }

public:
  void destroy(Node *root) {
    if (root == nullptr)
      return;
    if (root->left_child != nullptr)
      destroy(root->left_child);
    if (root->right_child != nullptr)
      destroy(root->right_child);
    free(root); // similar to postorder walk.
  }

public:
  void insertNode(Node *&root, T value, bool on_left) {

    if (root == nullptr) {
      root = new Node(value);
      return;
    }

    Node *target = new Node(value);
    on_left ? root->left_child = target : root->right_child = target;
  }

public:
  void preorder_walk_recursive(Node *root) {
    if (root == nullptr)
      return;
    printf("%d ", root->value);
    if (root->left_child != nullptr)
      preorder_walk_recursive(root->left_child);
    if (root->right_child != nullptr)
      preorder_walk_recursive(root->right_child);
  }

public:
  void inorder_walk_recursive(Node *root) {
    if (root == nullptr)
      return;
    if (root->left_child != nullptr)
      inorder_walk_recursive(root->left_child);
    printf("%d ", root->value);
    if (root->right_child != nullptr)
      inoinorder_walk_recursive(root->right_child);
  }

public:
  void postorder_walk_recursive(Node *root) {
    if (root == nullptr)
      return;
    if (root->left_child != nullptr)
      postorder_walk_recursive(root->left_child);
    if (root->right_child != nullptr)
      postorder_walk_recursive(root->right_child);
    printf("%d ", root->value);
  }

  // compare code with preorder_walk_iteration.
  // you shouldn't pass a nullptr root !
public:
  void sequence_walk_iteration(Node *root) {
    queue<Node *> Q;
    Q.push(root);

    while (!Q.empty()) {
      Node *curNode = Q.front();
      Q.pop();
      printf("%d ", curNode->value);
      if (curNode->left_child != nullptr)
        Q.push(curNode->left_child);
      if (curNode->right_child != nullptr)
        Q.push(curNode->right_child);
    }
  }

public:
  void preorder_walk_iteration_with_stack(Node *root) {

    stack<Node *> S;
    S.push(root);

    while (!S.empty()) {

      Node *curNode = S.top();
      S.pop();

      printf("%d ", curNode->value);
      if (curNode->right_child != nullptr)
        S.push(curNode->right_child);
      if (curNode->left_child != nullptr)
        S.push(curNode->left_child);
    }
  }

public:
  void preorder_walk_iteration(Node *root) {

    stack<Node *> S; // it's no need to push first element.

    while (root != nullptr || !S.empty()) {

      // keep going left.
      while (root != nullptr) {
        printf("%d ", root->value); // move printf statement.

        S.push(root);
        root = root->left_child;
      }

      root = S.top();
      S.pop();

      // Addiction Action.
      root = root->right_child;
    }
  }

public:
  void inorder_walk_iteration(Node *root) {

    stack<Node *> S; // it's no need to push first element.

    while (root != nullptr || !S.empty()) {

      // keep going left.
      while (root != nullptr) {
        S.push(root);
        root = root->left_child;
      }

      root = S.top();
      S.pop();

      // Addictional Action.
      printf("%d ", root->value);
      root = root->right_child;
    }
  }

public:
  void postorder_walk_iteration(Node *root) {

    stack<Node *> S; // it's no need to push first element.

    Node *node = nullptr; // only for book.
    while (root != nullptr || !S.empty()) {

      // keep going to left child.
      while (root != nullptr) {
        S.push(root);
        root = root->left_child;
      }

      root = S.top();
      S.pop();

      // Addictional Action.
      if (root->right_child == nullptr || root->right_child == node) {
        printf("%d ", root->value);
        node = root; // update node.
        root = nullptr; // disconnect to get 1 element from stack.
      } else {
        S.push(root);
        root = root->right_child;
      }
    }
  }

public:
  void preorder_walk_morris(Node *root) {

    Node *p1 = root;
    Node *p2 = nullptr;

    while (p1 != nullptr) {
      p2 = p1->left_child;

      if (p2 != nullptr) {
        while (p2->right_child != nullptr && p2->right_child != p1) {
          p2 = p2->right->right_child;
        }

        if (p2->right_child == nullptr) {
          printf("%d ", p1->value);
          p2->right_child = p1;
          p1 = p1->left_child;
          continue;
        } else {
          p2->right_child = nullptr;
        }
      } else {
        printf("%d ", p1->value);
      }
      p1 = p1->right_child;
    }
  }

public:
  void inorder_walk_morris(Node *root) {

    Node *predecessor = nullptr;
    while (root != nullptr) {

      if (root->left_child != nullptr) {
        predecessor = root->left_child;
        while (predecessor->right_child != nullptr &&
               predecessor->right_child != root) {
          predecessor = predecessor->right_child;
        }
        if (predecessor->right_child == nullptr) {
          predecessor->right_child = root;
          root = root->left_child;
        } else {
          printf("%d ", root->value);
          predecessor->right = nullptr;
          root = root->right_child;
        }
      } else {
        printf("%d ", root->value);
        root = root->right_child;
      }
    }
  }

public:
  void postorder_walk_morris_aux(vector<int> &vec, Node *node) {
    int count = 0;
    while (node != nullptr) {
      count++;
      vec.push_back(node->value);
      node = node->right_child;
    }
    reverse(vec.end() - count, vec.end());
  }

public:
  void postorder_walk_morris(Node *root) {

    vector<T> res;
    Node *p1 = root;
    Node *p2 = nullptr;

    while (p1 != nullptr) {
      p2 = p1->left_child;
      if (p2 != nullptr) {
        while (p2->right_child != nullptr && p2->right_child != p1) {
          p2 = p2->right_child;
        }

        if (p2->right_child == nullptr) {
          p2->right_child = p1;
          p1 = p1->left_child;
          continue;
        } else {
          p2->right_child = nullptr;
          postorder_walk_morris_aux(res, p1->left);
        }
      }
      p1 = p1->right_child;
    }

    postorder_walk_morris_aux(res, root);

    for_each(res.begin(), res.end(), [](const T &obj) { printf("%d ", obj); });
  }
};

int main() {

  BinaryTree<int> bt;

  bt.insertNode(bt.root, 1, true);
  bt.insertNode(bt.root, 2, true);
  bt.insertNode(bt.root, 3, false);

  bt.insertNode(bt.root->left_child, 4, true);
  bt.insertNode(bt.root->left_child, 5, false);
  bt.insertNode(bt.root->left_child->left_child, 8, true);
  bt.insertNode(bt.root->left_child->left_child, 9, false);
  bt.insertNode(bt.root->left_child->right_child, 10, true);
  bt.insertNode(bt.root->right_child, 6, true);
  bt.insertNode(bt.root->right_child, 7, false);


  bt.preorder_walk_iteration(bt.root);
  return 0;
}
