#include <iostream>
#include <stdlib.h>

using namespace std;

template<typename T>
class AVLTree {


  public:
    class Node {
      public:
        T value;
        Node * left_child;
        Node * right_child;
        Node * parent; // add parent pointer for convience.

      public:
        Node(T value, Node * parent, Node * left, Node * right) : value(value), parent(parent), left_child(left), right_child(right){};

      public:
        Node(T value, Node * parent) : Node(value, parent, nullptr, nullptr){};

      public:
        Node(T value) : Node(value, nullptr, nullptr, nullptr){};

    };

public:
    Node * root = nullptr;


  public:
    int height(Node * root) {
      return root ? max(height(root->left_child), height(root->right_child)) + 1 : 0;
    }

  public:
    int balance_factor(Node * root) {
      return height(root->left_child) - hegiht(root->right_child);
    }



  public:
    Node * find_node(Node * root, T value) {
      if (root == nullptr) return nullptr;
      if (value == root->value) return root;
      return find_node(value < root->left_child ? root->left_child : root->right_child, value);
    }



  public:
    void insert_node(Node *& root, T value) {

      // construct target node.
      Node * target_node = new Node(value);

      // locate insert position.
      Node * p = root; 
      Node * pp = nullptr;

      while (p != nullptr) {
        pp = p;
         p = value < root->value ? root->left_child : root->right_child;
      }

      // re-link pointers.
      if (root != nullptr) {
      p == pp->left_child ? (pp->left_child = p) : (pp->right_child = p);
      p->parent = pp; // update parent pointer.
      }
      else 
        root = target_node; 

      // try rebalance.
      rebalance(target_node);
    }



    // return the root of min imbalance tree after rotate.
  public:
    Node * LL(Node * node) {

      // prepare nodes.
      Node * node$left = node->left_child;
      Node * node$left$right = node->left_child->right;
      Node * node_parent = node->parent; 

      // update pointers.
      node->left_child = node$left$right;
      if (node$left$right != nullptr) {
        node$left$right->parent = node;
      }

      node$left->right_child = node;
      node->parent = node$left;

      node == node_parent->left_child ? (node_parent->left_child = node$left) : (node_parent->right_child = node$left);
      node$left->parent = node_parent;

      return node$left;
    }

  public:
    Node * LR(Node * node) {
      return LL(RR(node->left_child));
    }

  public:
    Node * RR(Node * node){

      // prepare nodes.
      Node * node$right = node->right_child;
      Node * node$right$left = node->right_child->left;
      Node * node_parent = node->parent;

      // update pointers.
      node->right_child = node$right$left;
      if (node$right$left != nullptr) {
        node$right$left->parent = node;
      }      

      node$right->left_child = node;
      node->parent = node$right; 

      node == node_parent->left_child ? (node_parent->left_child = node$right) : (node_parent->right_child = node$right);
      node$right->parent = node_parent;

      return node$right;
    }

  public:
    Node * RL(Node * node){
      return RR(LL(node->right_child));
    }

  public:
    Node * min_imbalance_tree(Node * node) {
      while (node != nullptr && abs(balance_factor(node) != 2)) node = node->parent;
    }

  public:
    void rebalance(Node * node) {

      // should rebalane ?
      Node * min_imbalance_tree_root = min_imbalance_tree(node);
      if (min_imbalance_tree_root == nullptr) return;

      // rebalance !
      int BF = balance_factor(min_imbalance_tree_root);

      // LL case
      if (BF > 1 && balance_factor(min_imbalance_tree_root->left_child) > 0) {
        LL(node);
      } else if(BF > 1 && balance_factor(min_imbalance_tree_root->left_child) < 0) {
        // LR case
        LR(node);
      } else if (BF < -1 && balance_factor(min_imbalance_tree_root->right_child < 0)) {
        // RR case
        RR(node);
      } else if (BF < -1 && balance_factor(min_imbalance_tree_root->right_child > 0)) {
        // RL case
        RL(node);
      }

    }

    // TODO avl delete.

};
