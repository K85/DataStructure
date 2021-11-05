// NOTE: rbt insert is ok, but delete has some problems !
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

// 红黑树
// 性质1: 节点是红色或黑色
// 性质2: 根节点是黑色的
// 性质3: 所有的 叶子节点 是黑色的(叶子节点指 NIL节点)
// 性质4: 每个红色节点 必须有2个黑色的子节点
// 性质5: 任何一个节点 到 它的每个叶子 的所有简单路径上都包含 相同数目的黑色节点
enum Color {
    RED, BLACK
};

template<typename T>
class RedBlackTree {

public:
    class BTreeNode {
    public:
        T value;
        Color color;
        BTreeNode *parent;
        BTreeNode *left_child;
        BTreeNode *right_child;

        // Constructors.
    public:
        BTreeNode(T value, Color color, BTreeNode *parent, BTreeNode *left_child, BTreeNode *right)
                : value(value), color(color), parent(parent), left_child(left_child), right_child(right) {
        }

        // BTreeNode Relations Aux Functinos. (Some safe functions.)
    public:
        BTreeNode(T value, Color color)
                : BTreeNode(value, color, nullptr, nullptr, nullptr) {}

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
      cout << root->value << "(" << root->color << ") ";
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
        this->ROOT = new BTreeNode(value, Color::BLACK);
        return;
      }

      // Case: not empty tree
      if (value < root->value) {
        if (root->left_child != nullptr) insert_node(root->left_child, value);
        else {
          auto *target_node = new BTreeNode(value, Color::RED);

          // link
          target_node->parent = root;
          root->left_child = target_node;// NODE: black node is EASY to rebalance.

          // maintain
          insert_case1(target_node);
        }
      } else if (value > root->value) {
        if (root->right_child != nullptr) insert_node(root->right_child, value);
        else {

          auto *target_node = new BTreeNode(value, Color::RED);

          // link
          target_node->parent = root;
          root->right_child = target_node;

          // maintain
          insert_case1(target_node);
        }
      }

    }

public:
    void insert_case1(BTreeNode *n) {
      // CASE: empty tree ?
      // PROMISE: n is not null (since n is the target node)
      if (n->parent == nullptr)
        n->color = Color::BLACK;
      else
        insert_case2(n);
    }

public:
    void insert_case2(BTreeNode *n) {
      // CASE: target node's parent's color is BLACK ?
      // PROMISE: n->parent is not null.
      if (n->parent->color == Color::BLACK)
        return;
      else
        insert_case3(n);
    }

public:
    void insert_case3(BTreeNode *n) {
      // PROMISE: target node's parent's color is RED.
      if (U(n) != nullptr && U(n)->color == Color::RED) {

        n->parent->color = Color::BLACK;
        U(n)->color = Color::BLACK;
        GP(n)->color = Color::RED;

        insert_case1(GP(n));
      } else
        insert_case4(n);
    }

public:
    void insert_case4(BTreeNode *n) {
      // PROMISE: target node's uncle's color is BLACK
      if (n == n->parent->right_child && n->parent == GP(n)->left_child) {
        rotate_left(n);
        n = n->left_child;
      } else if (n == n->parent->left_child && n->parent == GP(n)->right_child) {
        rotate_right(n);
        n = n->right_child;
      }

      insert_case5(n);
    }

public:
    void insert_case5(BTreeNode *n) {
      // NOTE: rotate according to n
      n->parent->color = Color::BLACK;
      GP(n)->color = Color::RED;
      if (n == n->parent->left_child && n->parent == GP(n)->left_child) {
        rotate_right(n->parent);
      } else { // NOTE: n == n->parent->right_child && n->parent == n->GP()->right_child
        rotate_left(n->parent);
      }
    }

public:
    void delete_case1(BTreeNode *n) {

      if (n->parent != nullptr)
        delete_case2(n);
    }

public:
    void delete_case2(BTreeNode *n) {
      BTreeNode *s = S(n);

      if (s->color == Color::RED) {
        n->parent->color = Color::RED;
        s->color = Color::BLACK;

        (n == n->parent->left_child) ?
        rotate_left(n->parent) : rotate_right(n->parent);
      }

      delete_case3(n);
    }

public:
    void delete_case3(BTreeNode *n) {
      BTreeNode *s = S(n);

      if ((n->parent->color == Color::BLACK) && (s->color == Color::BLACK) &&
          (s->left_child->color == Color::BLACK) && (s->right_child->color == Color::BLACK)) {
        s->color = Color::RED;
        delete_case1(n->parent);
      } else
        delete_case4(n);
    }

public:
    void delete_case4(BTreeNode *n) {
      BTreeNode *s = S(n);
      if ((n->parent->color == Color::RED) && (s->color == Color::BLACK) &&
          (s->left_child->color == Color::BLACK) && (s->right_child->color == Color::BLACK)) {
        s->color = Color::RED;
        n->parent->color = Color::BLACK;
      } else
        delete_case5(n);
    }

public:
    void delete_case5(BTreeNode *n) {
      BTreeNode *s = S(n);

      if (s->color == Color::BLACK) {
        if ((n == n->parent->left_child) && (s->right_child->color == Color::BLACK) &&
            (s->left_child->color == Color::RED)) {
          s->color = Color::RED;
          s->left_child->color = Color::BLACK;
          rotate_right(s);
        } else if ((n == n->parent->right_child) && (s->left_child->color == BLACK) &&
                   (s->right_child->color == RED)) {
          s->color = RED;
          s->right_child->color = BLACK;
          rotate_left(s);
        }
      }
      delete_case6(n);
    }

public:
    void delete_case6(BTreeNode *n) {
      BTreeNode *s = S(n);
      s->color = n->parent->color;
      n->parent->color = Color::BLACK;

      if (n == n->parent->left_child) {
        s->right_child->color = Color::BLACK;
        rotate_left(n->parent);
      } else {
        s->left_child->color = Color::BLACK;
        rotate_right(n->parent);
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
        this->ROOT->color = Color::BLACK;
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

      if (node->color == Color::BLACK) {
        // NOTE: it's just like you cover the value FROM only_child TO node. (and then delete only_child)
        if (only_child != nullptr && only_child->color == Color::RED) only_child->color = Color::BLACK;
        else delete_case1(only_child);
      }

      // free
      free(node);
    }

    // return: true if delete successfully.
public:
    bool delete_node(BTreeNode *root, T value) {

      // locate delete node.
      if (value < root->value) {
        if (root->left_child == nullptr) return false;
        return delete_node(root->left_child, value);
      } else if (value > root->value) {
        if (root->right_child == nullptr) return false;
        return delete_node(root->right_child, value);
      } else if (value == root->value) {

        // Case1: has at most 1 childs?
        if (root->right_child == nullptr
            || root->left_child == nullptr) {
          delete_node_with_at_most_one_child(root);
          return true;
        }

        // Case2: has 2 childs.
        // swap the value between delete node and most node (In fact, we just cover value and convert delete case.)
        BTreeNode *most_node = max_node(root->left_child);
        root->value = most_node->value;
        most_node->value = 0xDEAD;
        delete_node_with_at_most_one_child(most_node);
        return true;
      } else return false;
    }


};


int main() {

  // construct rbt and add elements.
  RedBlackTree<int> rbt;
  rbt.insert_node(rbt.ROOT, 1000);
  rbt.insert_node(rbt.ROOT, 2000);
  rbt.insert_node(rbt.ROOT, 3000);
  rbt.insert_node(rbt.ROOT, 4000);
  rbt.insert_node(rbt.ROOT, 5000);
  rbt.insert_node(rbt.ROOT, 6000);
  rbt.insert_node(rbt.ROOT, 7000);
  rbt.insert_node(rbt.ROOT, 8000);
  rbt.insert_node(rbt.ROOT, 9000);

  printf("After inserts: \n");
  rbt.inorder_walk(rbt.ROOT);
  printf("\n");

  // delete elements.
  rbt.delete_node(rbt.ROOT, 4000);
  rbt.delete_node(rbt.ROOT, 1000);
  rbt.delete_node(rbt.ROOT, 8000);
  return 0;
}
