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
enum Color { RED, BLACK };

template <typename T> class RedBlackTree {

public:
    class Node {
    public:
        T value;
        Color color;
        Node *parent;
        Node *left_child;
        Node *right_child;

        // Constructors.
    public:
        Node(T value, Color color, Node *parent, Node *left_child, Node *right)
                : value(value), color(color), parent(parent), left_child(left_child), right_child(right) {
        }

        // Node Relations Aux Functinos. (Some safe functions.)
    public:
        Node(T value, Color color)
                : Node(value, color, nullptr, nullptr, nullptr) {}

    private:
        static bool IS_NULL(Node * node)  {
            if (CHECK_NULL_NODE_WITH_NIL_NODE_FLAG) {
                return node->left_child == node->right_child; // PROMISE: all nodes inside 1 tree use the same NIL node.
            } else return node == nullptr;
        }

    private:
        Node * P() {
            if (IS_NULL(this)) return nullptr;
            return this->parent;
        }

    public:
        Node *GP() {
            return this->P()->P();
        }

    public:
        Node *U() {
            if(IS_NULL(this->GP())) return nullptr;
            return this->P()->S();
        }

    public:
        Node *S() {
            if (IS_NULL(this->P())) return nullptr;
            return this == this->P()->left_child ? this->P()->right_child
                                                    : this->P()->left_child;
        }

    };

public:
    Node *ROOT = nullptr; // use ROOT instead of root to avoid ambiguity.
    static const bool CHECK_NULL_NODE_WITH_NIL_NODE_FLAG = false;


public:
    void inorder_walk(Node *root) {
        if (root == nullptr)
            return;
        if (root->left_child != nullptr)
            inorder_walk(root->left_child);
        cout << root->value << "(" << root->color << ") ";
        if (root->right_child != nullptr)
            inorder_walk(root->right_child);
    }

public:
    void preorder_walk(Node *root) {
        if (root == nullptr)
            return;
        cout << root->value << " ";
        if (root->left_child != nullptr)
            preorder_walk(root->left_child);
        if (root->right_child != nullptr)
            preorder_walk(root->right_child);
    }

public:
    void postorder_walk(Node *root) {
        if (root == nullptr)
            return;
        if (root->left_child != nullptr)
            postorder_walk(root->left_child);
        cout << root->value << " ";
        if (root->right_child != nullptr)
            postorder_walk(root->right_child);
    }

public:
    Node *search_node(Node *root, T value) {
        if (root == nullptr)
            return nullptr;
        if (value == root->value)
            return root;
        return search_node(value < root->value ? root->left_child : root->right_child, value);
    }

public:
    void rotate_left(Node * pivot) {
        if (pivot->parent == nullptr) {
            this->ROOT = pivot;
            return;
        }

        // prepare
        Node * pivot$grand_parent = pivot->GP();
        Node * pivot$father = pivot->parent;
        Node * pivot$left = pivot->left_child;

        // relink
        pivot$father->right_child = pivot$left;
        if (pivot$left != nullptr)
            pivot$left->parent = pivot$father;

        pivot->left_child = pivot$father;
        pivot$father->parent = pivot;

        if (this->ROOT == pivot$father)
            this->ROOT = pivot;
        pivot->parent = pivot$grand_parent;
        if (pivot$grand_parent != nullptr) {
            (pivot$grand_parent->left_child == pivot$father) ? (pivot$grand_parent->left_child = pivot) :
            (pivot$grand_parent->right_child = pivot);
        }
    }

public:
    void rotate_right(Node * pivot) {
        Node * pivot$grande_parent = pivot->GP();
        Node * pivot$father = pivot->parent;
        Node * pivot$right = pivot->right_child;

        pivot$father->left_child = pivot$right;
        if (pivot$right != nullptr)
            pivot$right->parent = pivot$father;

        pivot->right_child = pivot$father;
        pivot$father->parent = pivot;

        if (this->ROOT == pivot$father) this->ROOT = pivot;
        pivot->parent = pivot$grande_parent;
        if (pivot$grande_parent != nullptr) {
            (pivot$grande_parent->left_child == pivot$father) ? (pivot$grande_parent->left_child = pivot) :
            (pivot$grande_parent->right_child = pivot);
        }
    }

public:
    void insert_node(Node *root, T value) {

        // Case: empty tree
        if (root == nullptr) {
            this->ROOT = new Node(value, Color::BLACK);
            return;
        }

        // Case: not empty tree
       if (value < root->value)  {
           if (root->left_child != nullptr) insert_node(root->left_child, value);
           else {
               Node *target_node = new Node(value, Color::RED);

               // link
               target_node->parent = root;
               root->left_child = new Node(value, Color::RED);// NODE: black node is EASY to rebalance.

               // rebalance
               insert_case1(target_node);
           }
       } else if(value > root->value) {
           if (root->right_child != nullptr) insert_node(root->right_child, value);
           else {

               Node *target_node = new Node(value, Color::RED);

               // link
               target_node->parent = root;
               root->right_child = target_node;

               // rebalance
               insert_case1(target_node);
           }
       }

    }

public:
    void insert_case1(Node *n) {
        // CASE: empty tree ?
        // PROMISE: n is not null (since n is the target node)
        if (n->parent == nullptr)
            n->color = Color::BLACK;
        else
            insert_case2(n);
    }

public:
    void insert_case2(Node *n) {
        // CASE: target node's parent's color is BLACK ?
        // PROMISE: n->parent is not null.
        if (n->parent->color == Color::BLACK)
            return;
        else
            insert_case3(n);
    }

public:
    void insert_case3(Node *n) {
        // PROMISE: target node's parent's color is RED.
        if (n->U() != nullptr && n->U()->color == Color::RED) {

            n->parent->color = Color::BLACK;
            n->U()->color = Color::BLACK;
            n->GP()->color = Color::RED;

            insert_case1(n->GP());
        } else
            insert_case4(n);
    }

public:
    void insert_case4(Node *n) {
        // PROMISE: target node's uncle's color is BLACK
        if (n == n->parent->right_child && n->parent == n->GP()->left_child) {
            rotate_left(n);
            n = n->left_child;
        } else if (n == n->parent->left_child && n->parent == n->GP()->right_child) {
            rotate_right(n);
            n = n->right_child;
        }

        insert_case5(n);
    }

public:
    void insert_case5(Node *n) {
        // NOTE: rotate according to n
        n->parent->color = Color::BLACK;
        n->GP()->color = Color::RED;
        if (n == n->parent->left_child && n->parent == n->GP()->left_child) {
            rotate_right(n->parent);
        } else { // NOTE: n == n->parent->right_child && n->parent == n->GP()->right_child
            rotate_left(n->parent);
        }
    }

public:
    void delete_case1(Node *n) {

        if (n->parent != nullptr)
            delete_case2(n);
    }

public:
    void delete_case2(Node *n) {
        Node *s = n->S();

        if (s->color == Color::RED) {
            n->parent->color = Color::RED;
            s->color = Color::BLACK;

            if (n == n->parent->left_child) {
                rotate_left(n->parent);
            } else
                rotate_right(n->parent);
        }

        delete_case3(n);
    }

public:
    void delete_case3(Node *n) {
        Node *s = n->S();

        if ((n->parent->color == Color::BLACK) && (s->color == Color::BLACK) &&
            (s->left_child->color == Color::BLACK) && (s->right_child->color == Color::BLACK)) {
            s->color = Color::RED;
            delete_case1(n->parent);
        } else
            delete_case4(n);
    }

public:
    void delete_case4(Node *n) {
        Node *s = n->S();
        if ((n->parent->color == Color::RED) && (s->color == Color::BLACK) &&
            (s->left_child->color == Color::BLACK) && (s->right_child->color == Color::BLACK)) {
            s->color = Color::RED;
            n->parent->color = Color::BLACK;
        } else
            delete_case5(n);
    }

public:
    void delete_case5(Node *n) {
        Node *s = n->S();

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
    void delete_case6(Node *n) {
        Node *s = n->S();
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
    Node *min_node(Node *root) {
        while (root->left_child != nullptr)
            root = root->left_child;
        return root;
    }

public:
    Node * max_node(Node * root) {
        while(root->right_child != nullptr) root = root->right_child;
        return root;
    }

public:
    void delete_tree(Node * root) {
        if (root == nullptr) return;
        delete_tree(root->left_child);
        delete_tree(root->right_child);
        delete root;
    }

public:
    void delete_node_with_at_most_one_child(Node * node) {

        /* Case: only 1 node's tree. */
        if (node->parent == nullptr && node->left_child == nullptr && node->right_child == nullptr) {
            this->ROOT = nullptr;
            return;
        }

        /* Case: node is the root of RBT? */
        // select the only only_child of node.
        Node * only_child = node->left_child ? node->left_child : node->right_child;

        if (node->parent == nullptr) {
            // free old ROOT.
            delete node;

            // set new ROOT.
            only_child->parent = nullptr;
            this->ROOT = only_child;
            this->ROOT->color = Color::BLACK;
            return;
        }

        // re-link and re-color
        if (node->parent->left_child == node) { // NOTE: just like we delete a node in DLL
            node->parent->left_child = only_child;
        } else {
            node->parent->right_child = only_child;
        }

        if (only_child != nullptr) {
            // ATTENTION: prevent npe.
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
    bool delete_node(Node * root, T value) {

        // locate delete node.
        if (value < root->value) {
            if (root->left_child == nullptr) return false;
            return delete_node(root->left_child, value);
        } else if (value > root->value) {
            if (root->right_child == nullptr) return false;
            return delete_node(root->right_child, value);
        } else if(value == root->value) {

            // Case1: has at most 1 childs?
            if (root->right_child == nullptr
            || root->left_child == nullptr) {
                delete_node_with_at_most_one_child(root);
                return true;
            }

            // Case2: has 2 childs.
            // swap the value between delete node and most node (In fact, we just cover value and convert delete case.)
            Node * most_node = max_node(root->left_child);
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

