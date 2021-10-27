#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

template<typename T>
class AVLTree {

public:
    class BTreeNode {
    public:
        T value;
        BTreeNode *left_child;
        BTreeNode *right_child;
        BTreeNode *parent; // add parent pointer for convience.
        int height{};

        // NOTE: the default value of height is 1
    public:
        BTreeNode(T value, BTreeNode *parent, BTreeNode *left_child, BTreeNode *right_child, int height) : value(value),
                                                                                                           parent(parent),
                                                                                                           left_child(
                                                                                                                   left_child),
                                                                                                           right_child(
                                                                                                                   right_child),
                                                                                                           height(height) {};


    public:
        explicit BTreeNode(T value) : BTreeNode(value, nullptr, nullptr, nullptr, 1) {};

    };

    // NOTE: ROOT is the real root of AVL Tree.
public:
    BTreeNode *ROOT = nullptr;

public:
    int height(BTreeNode *root) {
        // NOTE: prevent NPE
        if (root == nullptr) return 0;
        return root->height;
    }

public:
    int BF(BTreeNode *root) {
        return height(root->left_child) - height(root->right_child);
    }


public:
    BTreeNode *rotate_left(BTreeNode *end_node) {

        // prepare nodes.
        BTreeNode *end_node$right = end_node->right_child;
        BTreeNode *end_node$right$left = end_node->right_child->left_child;
        BTreeNode *end_node$parent = end_node->parent;

        // update ROOT.
        if (end_node == ROOT) {
            ROOT = end_node$right;
        }

        // update pointers.
        end_node->right_child = end_node$right$left;
        if (end_node$right$left != nullptr) {
            end_node$right$left->parent = end_node;
        }

        end_node$right->left_child = end_node;
        end_node->parent = end_node$right;

        if (end_node$parent != nullptr) {
            end_node == end_node$parent->left_child ? (end_node$parent->left_child = end_node$right)
                                                    : (end_node$parent->right_child = end_node$right);
        }
        end_node$right->parent = end_node$parent;

        // update heights.
        end_node->height = max(height(end_node->left_child), height(end_node->right_child)) + 1;
        end_node$right->height = max(height(end_node$right->left_child), height(end_node$right->right_child)) + 1;

        return end_node$right;
    }

public:
    BTreeNode *rotate_right(BTreeNode *end_node) {
        // prepare nodes.
        BTreeNode *end_node$left = end_node->left_child;
        BTreeNode *end_node$left$right = end_node->left_child->right_child;
        BTreeNode *end_node$parent = end_node->parent;

        // update ROOT
        if (end_node == ROOT) {
            ROOT = end_node$left;
        }

        // update pointers.
        end_node->left_child = end_node$left$right;
        if (end_node$left$right != nullptr) {
            end_node$left$right->parent = end_node;
        }

        end_node$left->right_child = end_node;
        end_node->parent = end_node$left;

        if (end_node$parent != nullptr) {
            end_node == end_node$parent->left_child ? (end_node$parent->left_child = end_node$left)
                                                    : (end_node$parent->right_child = end_node$left);
        }
        end_node$left->parent = end_node$parent;

        // update heights.
        end_node->height = max(height(end_node->left_child), height(end_node->right_child)) + 1;
        end_node$left->height = max(height(end_node$left->left_child), height(end_node$left->right_child)) + 1;

        return end_node$left;
    }

public:
    BTreeNode *LL(BTreeNode *node) {
        return rotate_right(node);
    }

public:
    BTreeNode *LR(BTreeNode *node) {
        RR(node->left_child);
        return LL(node);
    }

public:
    BTreeNode *RR(BTreeNode *node) {
        return rotate_left(node);
    }

public:
    BTreeNode *RL(BTreeNode *node) {
        LL(node->right_child);
        return RR(node);
    }

public:
    BTreeNode *min_node(BTreeNode *root) {
        return root->left_child ? min_node(root->left_child) : root;
    }

public:
    BTreeNode *max_node(BTreeNode *root) {
        return root->right_child ? max_node(root->right_child) : root;
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
                auto *target_node = new BTreeNode(value);

                // link
                target_node->parent = root;
                root->left_child = target_node;// NODE: black node is EASY to rebalance.
            }
        } else if (value > root->value) {
            if (root->right_child != nullptr) insert_node(root->right_child, value);
            else {

                auto *target_node = new BTreeNode(value);

                // link
                target_node->parent = root;
                root->right_child = target_node;
            }
        }


        /* maintain */
        root->height = max(height(root->left_child), height(root->right_child)) + 1;
        if (BF(root) > 1 && BF(root->left_child) > 0) LL(root);
        if (BF(root) > 1 && BF(root->left_child) < 0) LR(root);
        if (BF(root) < -1 && BF(root->right_child) < 0) RR(root);
        if (BF(root) < -1 && BF(root->right_child) > 0) RL(root);
    }


public:
    BTreeNode *delete_node(BTreeNode *root, T value) {
        if (root->left_child == nullptr && root->right_child == nullptr) {
            if (root == ROOT)
                ROOT = nullptr;
            delete root;
            return nullptr;
        }

        // NOTE: use the return value of recursion to write less code !
        if (value < root->value) {
            root->left_child = delete_node(root->left_child, value);
        } else if (value > root->value) {
            root->right_child = delete_node(root->right_child, value);
        } else {
            // NOTE: always delete the node with at most one child !
            BTreeNode *most_node;
            if (root->left_child != nullptr) {
                most_node = max_node(root->left_child);
                root->value = most_node->value;
                most_node->value = 0xDEAD;
                root->left_child = delete_node(root->left_child, most_node->value);
            } else {
                most_node = min_node(root->right_child);
                root->value = most_node->value;
                most_node->value = 0xDEAD;
                root->right_child = delete_node(root->right_child, most_node->value);
            }
        }

        // maintain.
        root->height = max(height(root->left_child), height(root->right_child)) + 1;
        if (BF(root) == 2 && BF(root->left_child) == 1) root = LL(root);
        if (BF(root) == 2 && BF(root->left_child) == -1) root = LR(root);
        if (BF(root) == 2 && BF(root->left_child) == 0) root = LL(root);
        if (BF(root) == -2 && BF(root->right_child) == -1) root = RR(root);
        if (BF(root) == -2 && BF(root->right_child) == 1) root = RL(root);
        if (BF(root) == -2 && BF(root->right_child) == 0) root = RR(root);
        return root;
    }

};


int main() {

    AVLTree<int> avl;
    avl.insert_node(avl.ROOT, 1000);
    avl.insert_node(avl.ROOT, 2000);
    avl.insert_node(avl.ROOT, 3000);
    avl.insert_node(avl.ROOT, 4000);
    avl.insert_node(avl.ROOT, 5000);
    avl.insert_node(avl.ROOT, 6000);
    avl.insert_node(avl.ROOT, 7000);
    avl.insert_node(avl.ROOT, 8000);
    avl.insert_node(avl.ROOT, 9000);

    avl.delete_node(avl.ROOT, 1000);
    avl.delete_node(avl.ROOT, 2000);
    avl.delete_node(avl.ROOT, 7000);
    avl.delete_node(avl.ROOT, 3000);

    return 0;
}
