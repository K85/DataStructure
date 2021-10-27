#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class BinarySearchTree {

public:
    class BTreeNode {
    public:
        T value;
        BTreeNode *parent;
        BTreeNode *left_child;
        BTreeNode *right_child;

        // Constructors.
    public:
        BTreeNode(T value, BTreeNode *parent, BTreeNode *left_child, BTreeNode *right)
                : value(value), parent(parent), left_child(left_child), right_child(right) {
        }

    public:
        explicit BTreeNode(T value)
                : BTreeNode(value, nullptr, nullptr, nullptr) {}

    };

private:
    BTreeNode *P(BTreeNode *node) {
      if (node == nullptr) return nullptr;
      return node->parent;
    }

private:
    BTreeNode *GP(BTreeNode *node) {
      return P((P(node)));
    }

private:
    BTreeNode *S(BTreeNode *node) {
      if (P(node) == nullptr) return nullptr;
      return node == P(node)->left_child ? P(node)->right_child
                                         : P(node)->left_child;
    }

private:
    BTreeNode *U(BTreeNode *node) {
      if (GP(node) == nullptr) return nullptr;
      return S(P(node));
    }


public:
    BTreeNode *ROOT = nullptr; // use ROOT instead of root to avoid ambiguity.

public:
    void inorder_walk(BTreeNode *root) {
      if (root == nullptr)
        return;
      if (root->left_child != nullptr)
        inorder_walk(root->left_child);
      cout << root->value << " ";
      if (root->right_child != nullptr)
        inorder_walk(root->right_child);
    }

public:
    BTreeNode *search_node(BTreeNode *root, T value) {
      if (root == nullptr)
        return nullptr;
      if (value == root->value)
        return root;
      return search_node(value < root->value ? root->left_child : root->right_child, value);
    }

public:
    void rotate_left(BTreeNode *pivot_node) {
      if (pivot_node->parent == nullptr) {
        this->ROOT = pivot_node;
        return;
      }

      // prepare nodes.
      BTreeNode *pivot_node$grand_parent = GP(pivot_node);
      BTreeNode *pivot_node$father = pivot_node->parent;
      BTreeNode *pivot_node$left = pivot_node->left_child;

      // update ROOT.
      if (this->ROOT == pivot_node$father) this->ROOT = pivot_node;

      // update pointers and colors.
      pivot_node$father->right_child = pivot_node$left;
      if (pivot_node$left != nullptr) {
        pivot_node$left->parent = pivot_node$father;
      }

      pivot_node->left_child = pivot_node$father;
      pivot_node$father->parent = pivot_node;

      pivot_node->parent = pivot_node$grand_parent;
      if (pivot_node$grand_parent != nullptr) {
        (pivot_node$grand_parent->left_child == pivot_node$father) ? (pivot_node$grand_parent->left_child = pivot_node)
                                                                   :
        (pivot_node$grand_parent->right_child = pivot_node);
      }
    }

public:
    void rotate_right(BTreeNode *pivot_node) {
      // prepare nodes.
      BTreeNode *pivot_node$grande_parent = GP(pivot_node);
      BTreeNode *pivot_node$father = pivot_node->parent;
      BTreeNode *pivot_node$right = pivot_node->right_child;

      // update ROOT.
      if (this->ROOT == pivot_node$father) this->ROOT = pivot_node;

      // update pointers and colors.
      pivot_node$father->left_child = pivot_node$right;
      if (pivot_node$right != nullptr) {
        pivot_node$right->parent = pivot_node$father;
      }

      pivot_node->right_child = pivot_node$father;
      pivot_node$father->parent = pivot_node;

      pivot_node->parent = pivot_node$grande_parent;
      if (pivot_node$grande_parent != nullptr) {
        (pivot_node$grande_parent->left_child == pivot_node$father)
        ? (pivot_node$grande_parent->left_child = pivot_node) :
        (pivot_node$grande_parent->right_child = pivot_node);
      }
    }

public:
    void insert_node(BTreeNode *root, T value) {

      // Case: empty tree
      if (root == nullptr) {
        this->ROOT = new BTreeNode(value);
        return;
      }

      // Case: not empty tree
      if (value < root->value) {
        if (root->left_child != nullptr) insert_node(root->left_child, value);
        else {
          // link
          auto *target_node = new BTreeNode(value);
          target_node->parent = root;
          root->left_child = new BTreeNode(value);// NODE: black node is EASY to rebalance.
        }
      } else if (value > root->value) {
        if (root->right_child != nullptr) insert_node(root->right_child, value);
        else {
          // link
          auto *target_node = new BTreeNode(value);
          target_node->parent = root;
          root->right_child = target_node;
        }
      }
    }

public:
    BTreeNode *min_node(BTreeNode *root) {
      while (root->left_child != nullptr)
        root = root->left_child;
      return root;
    }

public:
    BTreeNode *max_node(BTreeNode *root) {
      while (root->right_child != nullptr) root = root->right_child;
      return root;
    }

public:
    void delete_tree(BTreeNode *root) {
      if (root == nullptr) return;
      delete_tree(root->left_child);
      delete_tree(root->right_child);
      delete root;
    }

public:
    void delete_node_with_at_most_one_child(BTreeNode *node) {

      /* Case: only 1 node's tree. */
      if (node->parent == nullptr && node->left_child == nullptr && node->right_child == nullptr) {
        this->ROOT = nullptr;
        return;
      }

      /* Case: node is the root of RBT? */
      // select the only only_child of node.
      BTreeNode *only_child = node->left_child ? node->left_child : node->right_child;

      // update ROOT.
      if (node->parent == nullptr) {
        // free old ROOT.
        delete node;

        // set new ROOT.
        only_child->parent = nullptr;
        this->ROOT = only_child;
        return;
      }

      // update pointers and colors.
      if (node->parent->left_child == node) { // NOTE: just like we delete a node in DLL
        node->parent->left_child = only_child;
      } else {
        node->parent->right_child = only_child;
      }

      if (only_child != nullptr) {
        only_child->parent = node->parent;
      }

      // free
      free(node);
    }

    // return: true if delete successfully.
public:
    void delete_node(BTreeNode *root, T value) {
      // locate delete node.
      if (value < root->value) {
        if (root->left_child == nullptr) return;
        delete_node(root->left_child, value);
        return;
      } else if (value > root->value) {
        if (root->right_child == nullptr) return;
        delete_node(root->right_child, value);
        return;
      } else if (value == root->value) {

        // Case1: has at most 1 childs?
        if (root->right_child == nullptr
            || root->left_child == nullptr) {
          delete_node_with_at_most_one_child(root);
          return;
        }

        // Case2: has 2 childs.
        // swap the value between delete node and most node (In fact, we just cover value and convert delete case.)
        BTreeNode *most_node = max_node(root->left_child);
        root->value = most_node->value;
        most_node->value = 0xDEAD;
        delete_node_with_at_most_one_child(most_node);
        return;
      }
    }

};


int main() {

  // construct bst and add elements.
  BinarySearchTree<int> bst;
  bst.insert_node(bst.ROOT, 1000);
  bst.insert_node(bst.ROOT, 2000);
  bst.insert_node(bst.ROOT, 3000);
  bst.insert_node(bst.ROOT, 4000);
  bst.insert_node(bst.ROOT, 5000);
  bst.insert_node(bst.ROOT, 6000);
  bst.insert_node(bst.ROOT, 7000);
  bst.insert_node(bst.ROOT, 8000);
  bst.insert_node(bst.ROOT, 9000);

  printf("After inserts: \n");
  bst.inorder_walk(bst.ROOT);
  printf("\n");

  // delete elements.
  bst.delete_node(bst.ROOT, 4000);
  bst.delete_node(bst.ROOT, 1000);
  bst.delete_node(bst.ROOT, 8000);
  return 0;
}
