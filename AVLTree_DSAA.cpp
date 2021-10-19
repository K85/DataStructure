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
      Node * node_left = node->left_child;
      Node * node_left_right = node->left_child->right;
      Node * node_parent = node->parent; 

      // update pointers.
      node->left_child = node_left_right;
      if (node_left_right != nullptr) {
        node_left_right->parent = node;
      }

      node_left->right_child = node;
      node->parent = node_left;

      node == node_parent->left_child ? (node_parent->left_child = node_left) : (node_parent->right_child = node_left);
      node_left->parent = node_parent;

      return node_left;
    }

  public:
    Node * LR(Node * node) {
      return LL(RR(node->left_child));
    }

  public:
    Node * RR(Node * node){

      // prepare nodes.
      Node * node_right = node->right_child;
      Node * node_right_left = node->right_child->left;
      Node * node_parent = node->parent;

      // update pointers.
      node->right_child = node_right_left;
      if (node_right_left != nullptr) {
        node_right_left->parent = node;
      }      

      node_right->left_child = node;
      node->parent = node_right; 

      node == node_parent->left_child ? (node_parent->left_child = node_right) : (node_parent->right_child = node_right);
      node_right->parent = node_parent;

      return node_right;
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

      } else if(BF > 1 && balance_factor(min_imbalance_tree_root->left_child) < 0) {
        // LR case

      } else if (BF < -1 && balance_factor(min_imbalance_tree_root->right_child < 0)) {
        // RR case

      } else if (BF < -1 && balance_factor(min_imbalance_tree_root->right_child > 0)) {
        // RL case

      }

    }


    // TODO avl delete.

};
