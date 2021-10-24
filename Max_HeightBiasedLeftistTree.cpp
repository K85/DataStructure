#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <functional>
#include <algorithm>
#include <numeric>
#include <queue>

using namespace std;

template<typename T>
class Max_HeightBiasedLeftistTree {

public:
    class Node {

    public:
        pair<int, T> element; // NOTE: int means the height.
        Node * left_child;
        Node * right_child;

    public:
        Node(pair<int, T> value, Node * left_child, Node * right_child) : element(value), left_child(left_child),
                                                                          right_child(right_child){}

    public:
        Node(pair<int, T> value) : Node(value, nullptr, nullptr){};

    };

public:
    Node * ROOT;
    int tree_size;


public:
    int height(Node * root) {
        return root ? max(height(root->left_child), height(root->right_child)) + 1 : 0;
    }


    // return: new tree's ROOT is x
public:
    void meld(Node *  x, Node * y) {
        // one of them is empty tree ?
        if (y == nullptr) return;
        if (x == nullptr) {
            x = y;
            return;
        }

        // swap tree root if necessary.
        if (x->element.second < y->element.second)
            swap(x, y);

        meld(x->right_child, y);

        // if necessary, swap x's childs.
        if (x->left_child == nullptr) {
            x->left_child = x->right_child;
            x->right_child = nullptr;
            x->element.first = 1;
        } else {
            // NOTE: make sure x's left child has higher height.
            if (x->left_child->element.first < x->right_child->element.first)
                swap(x->left_child, x->right_child);

            x->element.first = x->right_child->element.first + 1;
        }
    }


public:
    void meld(Max_HeightBiasedLeftistTree<T>& hblt) {
        // melt *this AND hblt
        meld(this->ROOT, hblt.ROOT);
        this->tree_size += hblt.tree_size;
        hblt.ROOT = nullptr;
        hblt.tree_size = 0;
    }

public:
    void push(const T & value) {
        Node * only_one_node_tree = new Node(1, value);
        meld(this->ROOT, only_one_node_tree);
        this->tree_size++;
    }

public:
    void pop() {
        // empty tree ?
        if (this->ROOT == nullptr) return;

        Node * ROOT$left = this->ROOT->left_child;
        Node * ROOT$right = this->ROOT->right_child;
        delete this->ROOT;
        this->tree_size--;

        this->ROOT = ROOT$left; // NOTE: make ROOT's left child as new ROOT (since this is HBLT)
        meld(this->ROOT, ROOT$right);
    }

public:
    void init(T * elements_array, int array_size) {

        queue<Node *> Q;
        // erase

        // create the forest: every tree has only 1 node.
        for (int i = 1; i < array_size; i++) {
            // NOTE: we don't use elements_array[0]
            Q.push(new Node(1, elements_array[i]));
        }

        // choose 2 and combine them.
        while(Q.size() > 1) {
            Node * tree_a = Q.front(); Q.pop();
            Node * tree_b = Q.front(); Q.pop();
            melc(tree_a, tree_b);
            Q.push(tree_a);
        }

        // set finally ROOT
        this->ROOT = Q.front();
        this->tree_size = array_size - 1;
    }

};
