#include <algorithm>
#include <cstddef>
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

    class Node {
    public:
        T value;
        Color color;
        Node *parent;
        Node *left;
        Node *right;

    public:
        Node(T value, Color color, Node *parent, Node *left, Node *right)
                : value(value), color(color), parent(parent), left(left), right(right) {
        }

    public:
        Node(T value, Color color)
                : Node(value, color, nullptr, nullptr, nullptr) {}

    public:
        Node *grand_parent() { return this->parent->parent; }

    public:
        Node *uncle() { return this->parent->sibling(); }

    public:
        Node *sibling() {
            return this == this->parent->left ? this->parent->right
                                              : this->parent->left;
        }
    };

public:
    Node *root = nullptr;
    // rank: 从 该root节点 到 叶子节点 路径中 黑色指针的数量
    // 结论: 从 path(root, leaf).length <= 2 * rank(root);
    // 结论: h(root) <= 2 * rank(root)
    // 结论: r <= log2(n + 1)
public:
    int rank(Node *root) { return -1; }

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
    Node *search_node(Node *root, T value) {
        if (root == nullptr)
            return nullptr;
        if (value == root->value)
            return root;
        return search_node(value < root->value ? root->left : root->right, value);
    }

public:
    void rotate_right(Node *p){
        Node *gp = p->grand_parent();
        Node *fa = p->parent;
        Node *y = p->right;

        fa->left= y;

        if(y != nullptr)
            y->parent = fa;
        p->right= fa;
        fa->parent = p;

        if(root == fa)
            root = p;
        p->parent = gp;

        if(gp != NULL){
            if(gp->left== fa)
                gp->left= p;
            else
                gp->right= p;
        }

    }

public:
    void rotate_left(Node *p){
        if(p->parent == NULL){
            root = p;
            return;
        }
        Node *gp = p->grand_parent();
        Node *fa = p->parent;
        Node *y = p->left;

        fa->right= y;

        if(y != nullptr)
            y->parent = fa;
        p->left= fa;
        fa->parent = p;

        if(root == fa)
            root = p;
        p->parent = gp;

        if(gp != NULL){
            if(gp->left== fa)
                gp->left= p;
            else
                gp->right= p;
        }
    }
public:
    Color get_color(Node *root) {
        if (root == nullptr)
            return Color::BLACK;
        return root->color;
    }

public:
    void insert_node(Node *&root, T value) {
        // construct target node.
        Node *target = new Node(value, Color::RED);

        // find insert position.
        Node *target_parent = nullptr;
        Node *aux_node = root;
        while (aux_node != nullptr) {
            target_parent = aux_node;
            target->value < aux_node->value ? aux_node = aux_node->left
                                            : aux_node = aux_node->right;
        }

        // insert target node into y'left or right
        target->parent = target_parent;
        if (target_parent == nullptr)
            root = target;
        else
            target->value < target_parent->value ? target_parent->left = target
                                                 : target_parent->right = target;

        // rebalance
        insert_case1(target);
    }

public:
    void insert_case1(Node *n) {
        printf("insert_case1\n");
        if (n->parent == nullptr)
            n->color = Color::BLACK;
        else
            insert_case2(n);
    }

public:
    void insert_case2(Node *n) {
        printf("insert_case2\n");
        if (n->parent->color == Color::BLACK)
            return;
        else
            insert_case3(n);
    }

public:
    void insert_case3(Node *n) {
        printf("insert_case3\n");
        if (n->uncle() != nullptr && n->uncle()->color == Color::RED) {

            n->parent->color = Color::BLACK;
            n->uncle()->color = Color::BLACK;
            n->grand_parent()->color = Color::RED;

            insert_case1(n->grand_parent());
        } else
            insert_case4(n);
    }

public:
    void insert_case4(Node *n) {
        printf("insert_case4\n");
        if (n == n->parent->right && n->parent == n->grand_parent()->left) {
            rotate_left(n);
            n = n->left;
        } else if (n == n->parent->left && n->parent == n->grand_parent()->right) {
            rotate_right(n);
            n = n->right;
        }

        insert_case5(n);
    }

public:
    void insert_case5(Node *n) {
        printf("insert_case5\n");
        n->parent->color = Color::BLACK;
        n->grand_parent()->color = Color::RED;
        if (n == n->parent->left && n->parent == n->grand_parent()->left) {
            rotate_right(n->parent);
        } else {
            rotate_left(n->parent);
        }
    }

public:
    void delete_case1(Node *n) {
        printf("delete_case1\n");
        if (n->parent != nullptr)
            delete_case2(n);
    }

public:
    void delete_case2(Node *n) {
        printf("delete_case2\n");
        Node *s = n->sibling();

        if (s->color == Color::RED) {
            n->parent->color = Color::RED;
            s->color = Color::BLACK;

            if (n == n->parent->left) {
                rotate_left(n->parent);
            } else
                rotate_right(n->parent);
        }

        delete_case3(n);
    }

public:
    void delete_case3(Node *n) {
        printf("delete_case3\n");
        Node *s = n->sibling();

        if ((n->parent->color == Color::BLACK) && (s->color == Color::BLACK) &&
            (s->left->color == Color::BLACK) && (s->right->color == Color::BLACK)) {
            s->color = Color::RED;
            delete_case1(n->parent);
        } else
            delete_case4(n);
    }

public:
    void delete_case4(Node *n) {
        printf("delete_case4\n");
        Node *s = n->sibling();
        if ((n->parent->color == Color::RED) && (s->color == Color::BLACK) &&
            (s->left->color == Color::BLACK) && (s->right->color == Color::BLACK)) {
            s->color = Color::RED;
            n->parent->color = Color::BLACK;
        } else
            delete_case5(n);
    }

public:
    void delete_case5(Node *n) {
        printf("delete_case5\n");
        Node *s = n->sibling();

        if (s->color == Color::BLACK) {
            if ((n == n->parent->left) && (s->right->color == Color::BLACK) &&
                (s->left->color == Color::RED)) {
                s->color = Color::RED;
                s->left->color = Color::BLACK;
                rotate_right(s);
            } else if ((n == n->parent->right) && (s->left->color == BLACK) &&
                       (s->right->color == RED)) {
                s->color = RED;
                s->right->color = BLACK;
                rotate_left(s);
            }
        }
        delete_case6(n);
    }

public:
    void delete_case6(Node *n) {
        printf("delete_case6\n");
        Node *s = n->sibling();
        s->color = n->parent->color;
        n->parent->color = Color::BLACK;

        if (n == n->parent->left) {
            s->right->color = Color::BLACK;
            rotate_left(n->parent);
        } else {
            s->left->color = Color::BLACK;
            rotate_right(n->parent);
        }
    }

public:
    Node *min_node(Node *root) {
        while (root->left != nullptr)
            root = root->left;
        return root;
    }

public:
    Node *delete_min(Node *root) {
        if (root->left == nullptr)
            return root->right;
        root->left = delete_min(root->left);
        return root;
    }

public:
    bool delete_value(T value){
        return delete_node(this->root, value);
    }

public:
    void delete_tree(Node * root) {
        if (root == nullptr) return;
        delete_tree(root->left);
        delete_tree(root->right);
        delete root;
    }



public:
    void replace_node(Node * node, Node * child) {
        // case: the tree is only 1 node.
        if (node == this->root && node->left == nullptr && node->right == nullptr) {
            this->root = nullptr;
            return;
        }

        // link parents
        if (node->parent->left == node) {
            node->parent->left = child;
        } else {
            node->parent->right = child;
        }
        child->parent = node->parent;
    }


public:
    void delete_only_child(Node * node) {

        // find the only child of node.
        Node * node_child = node->left == nullptr ? node->right : node->left;

        if(node->parent == nullptr && node->left== nullptr && node->right== nullptr){
            node = nullptr;
            this->root = node;
            return;
        }

        // replace node and the only child of node.
//        replace_node(node, node_child);
        if(node->parent == nullptr){
            delete  node;
            node_child->parent = nullptr;
            this->root = node_child;
            this->root->color = Color::BLACK;
            return;
        }

        if(node->parent->left== node){
           node->parent->left= node_child;
        } else {
            node->parent->right= node_child;
        }

        // is node_child nullptr ?
        // TODO delete 
        if (node_child != nullptr) {
            node_child->parent = node->parent;

            // color
            if (node->color == Color::BLACK) {
                if (node_child->color == Color::RED) node_child->color = Color::BLACK;
                else delete_case1(node_child);
            }

            // free node
            delete node;
        }

    }

public:
  void rotate_left_V2(Node *root) {
    Node *root_right = root->right;
    Node *root_right_left = root->right->left;
    Node *root_parent = root->parent;

    root_right->left = root;
    root_right->parent = root_parent; // link parent
    root->right = root_right_left;

    // link parent
    if (root_parent->left == root) {
      root_parent->left = root_right;
    } else {
      root_parent->right = root_right;
    }
  }

public:
  void rotate_right_V2(Node *root) {
    Node *root_left = root->left;
    Node *root_left_right = root->left->right;
    Node *root_parent = root->parent;

    root_left->right = root;
    root_left->parent = root_parent; // link parent.
    root->left = root_left_right;

    // link parent.
    if (root_parent->left == root) {
      root_parent->left = root_left;
    } else {
      root_parent->right = root_left;
    }
  }

public:
    void delete_node(Node * root, T value) {
        // can't locate delete position.
        if (root == nullptr) return ;


        // locate delete position.
        if (value < root->value) {
            delete_node(root->left, value);
        } else if (value > root->value) {
            delete_node(root->right, value);
        } else if (value == root->value) {

            // why check right ?
            if (root->right == nullptr) {
                delete_only_child(root);
                return;
            }

            Node * smallest = min_node(root->right);
            swap(root->value, smallest->value);

            delete_only_child(smallest);
        }

    }


};


int main() {

    // construct rbt and add elements.
    RedBlackTree<int> rbt;
    rbt.insert_node(rbt.root, 400);
    rbt.insert_node(rbt.root, 300);
    rbt.insert_node(rbt.root, 100);
    rbt.insert_node(rbt.root, 200);

    rbt.inorder_walk(rbt.root);
    printf("\n");

    // delete elements.
    rbt.delete_node(rbt.root, 200);
    rbt.inorder_walk(rbt.root);
    return 0;
}
