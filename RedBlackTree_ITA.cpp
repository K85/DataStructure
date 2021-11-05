#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

// 红黑树
// 性质1: 每个节点是红色或黑色
// 性质2: 根节点是黑色的
// 性质3: 所有的 叶子节点(NIL or nullptr) 是黑色的(叶子节点指 NIL节点)
// 性质4: 每个红色节点 必须有2个黑色的子节点
// 性质5: 任何一个节点 到 它的每个叶子 的所有简单路径上都包含 相同数目的黑色节点
enum Color { RED, BLACK };

template <typename T> class RedBlackTree {

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
    BTreeNode(T value, Color color, BTreeNode *parent, BTreeNode *left_child,
              BTreeNode *right)
        : value(value), color(color), parent(parent), left_child(left_child),
          right_child(right) {}

  public:
    BTreeNode(T value, Color color)
        : BTreeNode(value, color, nullptr, nullptr, nullptr) {}
  };

public:
  BTreeNode *REAL_ROOT =
      nullptr; // use ROOT instead of root to avoid ambiguity.

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

  /* ROTATE */
public:
  void rotate_left(BTreeNode *end) {
    // node orphan
    BTreeNode *pivot = end->right_child;

    end->right_child = pivot->left_child;
    if (pivot->left_child)
      pivot->left_child->parent = end;
    // node pivot
    pivot->parent = end->parent;
    // NOTE: the only difference is that we use NIL to replace nullptr
    if (end->parent == nullptr)
      REAL_ROOT = pivot;
    else if (end == end->parent->left_child)
      end->parent->left_child = pivot;
    else
      end->parent->right_child = pivot;
    // node end
    pivot->left_child = end;
    end->parent = pivot;
  }

public:
  void rotate_right(BTreeNode *end) {
    // node orphan
    BTreeNode *pivot = end->left_child;

    end->left_child = pivot->right_child;
    if (pivot->right_child)
      pivot->right_child->parent = end;
    // node pivot
    pivot->parent = end->parent;
    if (end->parent == nullptr)
      REAL_ROOT = pivot;
    else if (end == end->parent->left_child)
      end->parent->left_child = pivot;
    else
      end->parent->right_child = pivot;
    // node end
    pivot->right_child = end;
    end->parent = pivot;
  }

  /* INSERT */
public:
  void insert_node_fixup(BTreeNode *node) {

    while (node->parent && node->parent->color == Color::RED) {
      // L: node->parent is left child
      BTreeNode *node_uncle;
      if (node->parent == node->parent->parent->left_child) {

        // NOTE: node_uncle may be nullptr
        node_uncle = node->parent->parent->right_child;

        // CASE1
        if (node_uncle && node_uncle->color == Color::RED) {
          node->parent->color = Color::BLACK;
          node_uncle->color = Color::BLACK;
          node->parent->parent->color = Color::RED;
          node = node->parent->parent; // NOTE: move 2 levels up !
        } else if (node == node->parent->right_child) {
          // CASE2
          // NOTE: anyway, we just change right case to left case
          node = node->parent;
          rotate_left(node);
        } else {
          // CASE3
          // NOTE: prevent node->parent == nullptr
          node->parent->color = Color::BLACK;
          node->parent->parent->color = Color::RED;
          rotate_right(node->parent->parent);
        }

      } else if (node->parent == node->parent->parent->right_child) {
        // NOTE: else if (node->parent == node->parent->parent->right_child)
        node_uncle = node->parent->parent->left_child;

        // NOTE: since we use nullptr, node_uncle maybe nullptr. (think NIL's
        // color is BLACK, so it's ok to do so)
        if (node_uncle != nullptr && node_uncle->color == Color::RED) {
          node->parent->color = Color::BLACK;
          node_uncle->color = Color::BLACK;
          node->parent->parent->color = Color::RED;
          node = node->parent->parent;
        } else if (node == node->parent->left_child) {
          node = node->parent;
          rotate_right(node);
        } else {
          node->parent->color = Color::BLACK;
          node->parent->parent->color = Color::RED;
          rotate_left(node->parent->parent);
        }
      }
    }
    REAL_ROOT->color = Color::BLACK;
  }

public:
  void insert_node(BTreeNode *root, T value) {

    // Case: empty tree
    if (root == nullptr) {
      REAL_ROOT = new BTreeNode(value, Color::BLACK);
      return;
    }

    // Case: not empty tree
    if (value < root->value) {
      if (root->left_child != nullptr)
        insert_node(root->left_child, value);
      else {
        auto *target_node = new BTreeNode(value, Color::RED);

        // link
        target_node->parent = root;
        root->left_child = target_node; // NODE: red node is EASY to rebalance.

        // maintain
        insert_node_fixup(target_node);
      }
    } else if (value > root->value) {
      // NOTE: same code, just exchange "left" and "right"
      if (root->right_child != nullptr)
        insert_node(root->right_child, value);
      else {

        auto *target_node = new BTreeNode(value, Color::RED);

        // link
        target_node->parent = root;
        root->right_child = target_node;

        // maintain
        insert_node_fixup(target_node);
      }
    }
  }

  /* DELETE */
  // NOTE: min_node can work correctly when root is a leaf node.
public:
  BTreeNode *min_node(BTreeNode *root) {
    while (root->left_child != nullptr)
      root = root->left_child;
    return root;
  }

public:
  BTreeNode *max_node(BTreeNode *root) {
    while (root->right_child != nullptr)
      root = root->right_child;
    return root;
  }

public:
  BTreeNode *find_node(BTreeNode *root, int value) {
    if (value == root->value)
      return root;
    return find_node(value < root->value ? root->left_child : root->right_child,
                     value);
  }

  // NOTE: should we free NIL as well ? (of course, or we'll get WA !)
public:
  BTreeNode *NIL;

  // NOTE: please note that NIL nodes only influence getters. (not setters)
public:
  BTreeNode *get_left_child(BTreeNode *root) {
    if (root->left_child)
      return root->left_child;
    //  NIL->parent = root; (it's not need to change NIL's parent. Instead, you
    //  should change this outside !)
    return NIL;
  }

public:
  BTreeNode *get_right_child(BTreeNode *root) {
    if (root->right_child)
      return root->right_child;
    //  NIL->parent = root;
    return NIL;
  }

  // use Node v to replace Node u
public:
  void transplant(BTreeNode *u, BTreeNode *v) {
    // NOTE: just like you link nodes in DDL.
    if (u->parent == nullptr)
      REAL_ROOT = (v == NIL ? nullptr : v);
    else if (u == u->parent->left_child) {
      // NOTE: most_node->left_child may be nullptr. (that's to say we don't
      // need to do anything when v is NIL!) NOTE: if v is NIL, we use nullptr
      // to replace it. (so that we can keep the semantics of transplant)
      u->parent->left_child = (v == NIL ? nullptr : v);
    } else {
      u->parent->right_child = (v == NIL ? nullptr : v);
    }
    // NOTE: v may be nullptr, but we have use NIL ! so, it's no need to care
    // about Runtime !
    v->parent = u->parent;
  }

public:
  void delete_node_fixup(BTreeNode *node) {

    // NOTE: special case for empty tree.
    // NOTE: it's a fault to write this code !
    //  if (node == NIL) return;

    // NOTE: recognise most_node AND only_child !!!
    // NOTE: node's color is right currently, but node's value should be
    // note->parent->value
    while (node != REAL_ROOT && node->color == Color::BLACK) {

      // LEFT
      // NOTE: here we can be sure that node->parent's right is not-nullptr if
      // left is nullptr
      if (node == get_left_child(node->parent)) {
        BTreeNode *node_sibling = get_right_child(node->parent);

        // case1
        if (node_sibling->color == Color::RED) {
          node_sibling->color = Color::BLACK;
          node->parent->color = Color::RED;
          rotate_left(node->parent);
          node_sibling = node->parent->right_child;
        }

        // case2
        // NOTE: only node_sibling->left_child may be nullptr, the right child
        // is not-nullptr !
        if (get_left_child(node_sibling)->color == Color::BLACK &&
            get_right_child(node_sibling)->color == Color::BLACK) {
          node_sibling->color = Color::RED;
          node = node->parent;
        } else {
          if (get_right_child(node_sibling)->color == Color::BLACK) {
            // case3
            node_sibling->left_child->color = Color::BLACK;
            node_sibling->color = Color::RED;
            rotate_right(node_sibling);
            node_sibling = node->parent->right_child;
          }
          // case4
          node_sibling->color = node->parent->color;
          node->parent->color = Color::BLACK;
          node_sibling->right_child->color = Color::BLACK;

          rotate_left(node->parent);
          node = REAL_ROOT;
        }
      } else if (node == get_right_child(node->parent)) {
        // RIGHT
        BTreeNode *node_sibling = get_left_child(node->parent);

        if (node_sibling->color == Color::RED) {
          node_sibling->color = Color::BLACK;
          node->parent->color = Color::RED;
          rotate_right(node->parent);
          node_sibling = node->parent->left_child;
        }

        if (get_left_child(node_sibling)->color == Color::BLACK &&
            get_right_child(node_sibling)->color == Color::BLACK) {
          node_sibling->color = Color::RED;
          node = node->parent;
        } else {
          if (get_left_child(node_sibling)->color == Color::BLACK) {
            node_sibling->right_child->color = Color::BLACK;
            node_sibling->color = Color::RED;
            rotate_left(node_sibling);
            node_sibling = node->parent->left_child;
          }
          node_sibling->color = node->parent->color;
          node->parent->color = Color::BLACK;
          node_sibling->left_child->color = Color::BLACK;
          rotate_right(node->parent);
          node = REAL_ROOT;
        }
      }
    }
    // NOTE: this statement may fixup some consecutive red nodes !
    node->color = Color::BLACK;
  }

public:
  void delete_node(BTreeNode *root, T value) {

    // NODE: special case for only 1 node's tree. (or we'll get Runtime)
    if (root->left_child == nullptr && root->right_child == nullptr) {
      REAL_ROOT = nullptr;
      delete root;
      return;
    }

    // locate delete node.
    BTreeNode *target_node = find_node(root, value);
    BTreeNode *most_node = target_node;
    BTreeNode *only_child;
    Color most_node_original_color = most_node->color;

    // CASE1: has at most 1 child.
    if (target_node->left_child == nullptr) {
      // NOTE: the only child may be nullptr ! (here we use virtual NIL to
      // replace nullptr)
      only_child = get_right_child(target_node);
      // NOTE: if target_node only has at most 1 child, then it's ok to use
      // transplant() to relink pointers. (in this case, we don't need to modify
      // other pointers outside the transplant())
      transplant(target_node, get_right_child(target_node));
    } else if (target_node->right_child == nullptr) {
      // ...
      only_child = get_left_child(target_node);
      transplant(target_node, get_left_child(target_node));
    } else {
      // CASE2: has 2 childs.
      most_node = max_node(target_node->left_child);
      most_node_original_color = most_node->color;

      // relink pointers.
      // only_child is the only child of most_node
      // NOTE: with left and right exchanged (different from ITA)
      only_child = get_left_child(most_node);
      if (most_node->parent == target_node) {

        // NOTE: only_child maybe nullptr (if we don't use NIL)
        // ATTENTION: we should set NIL's parent (because delete_node_fixup will
        // use NIL to traceback !)
        only_child->parent = most_node;

      } else {
        // NOTE: we change min_node (the way ITA use) to max_node, so we
        // exchanged left and right here
        transplant(most_node, get_left_child(most_node));
        most_node->left_child = target_node->left_child;
        most_node->left_child->parent = most_node;
      }

      transplant(target_node, most_node);
      most_node->right_child = target_node->right_child;
      most_node->right_child->parent = most_node;
      most_node->color = target_node->color;
    }

    // NOTE: here the node we should delete is target_node ! (most_node is not
    // value cover, it's relink pointers !)
    // NOTE: in fact, the ITA version use transplant() to change the relation by
    // relink pointers. so, it's pointers relink, not value cover. the final
    // node that we should delete is target_node ! (since most_node has change
    // its pointers by using transplant())
    delete target_node;

    // should fixup ?
    // NOTE: it's no need to fixup after we delete a red node
    if (most_node_original_color == Color::BLACK) {
      // NOTE: only_child may be the only child of most_node OR NIL (whose
      // parent is most_node) NOTE: here we use virtual NIL to keep
      // delete_node_fixup() easy to write.
      delete_node_fixup(only_child);
    }
  }
};

int main() {

  // construct rbt and add elements.
  RedBlackTree<int> rbt;
  rbt.insert_node(rbt.REAL_ROOT, 1000);
  rbt.insert_node(rbt.REAL_ROOT, 2000);
  rbt.insert_node(rbt.REAL_ROOT, 3000);
  rbt.insert_node(rbt.REAL_ROOT, 4000);
  rbt.insert_node(rbt.REAL_ROOT, 5000);
  rbt.insert_node(rbt.REAL_ROOT, 6000);
  rbt.insert_node(rbt.REAL_ROOT, 7000);
  rbt.insert_node(rbt.REAL_ROOT, 8000);
  rbt.insert_node(rbt.REAL_ROOT, 9000);
  rbt.insert_node(rbt.REAL_ROOT, 3100);
  rbt.insert_node(rbt.REAL_ROOT, 2900);
  rbt.insert_node(rbt.REAL_ROOT, 2800);
  rbt.insert_node(rbt.REAL_ROOT, 3500);
  rbt.insert_node(rbt.REAL_ROOT, 1200);
  rbt.insert_node(rbt.REAL_ROOT, 4200);
  rbt.insert_node(rbt.REAL_ROOT, 5300);
  rbt.insert_node(rbt.REAL_ROOT, 3100);
  rbt.insert_node(rbt.REAL_ROOT, 1300);
  rbt.insert_node(rbt.REAL_ROOT, 1900);

  printf("after inserts: \n");
  rbt.inorder_walk(rbt.REAL_ROOT);
  printf("\n");

  // delete elements.
  rbt.delete_node(rbt.REAL_ROOT, 4000);
  rbt.delete_node(rbt.REAL_ROOT, 1000);
  rbt.delete_node(rbt.REAL_ROOT, 8000);
  return 0;
}
