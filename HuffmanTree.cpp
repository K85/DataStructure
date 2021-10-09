struct BTreeNode {
  int value{0};
  BTreeNode *left_child{nullptr};
  BTreeNode *right_child{nullptr};
  BTreeNode(int value) { this->value = value; }
  BTreeNode() { this->value = 0; }
};

#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

// cmp for Node
template <typename T> struct cmp {
  bool operator()(const T &o1, const T &o2) { return o1->value > o2->value; }
};

BTreeNode *create_huffman_tree(const vector<int> &values) {
  // construct nodes.
  priority_queue<BTreeNode *, vector<BTreeNode *>, cmp<BTreeNode *>> pq;
  for (auto &value : values) {
    pq.push(new BTreeNode(value));
  }

  // combine 2 nodes into 1 node.
  while (pq.size() > 1) {
    // get the 2 min values.
    BTreeNode *a_node = pq.top();
    pq.pop();
    BTreeNode *b_node = pq.top();
    pq.pop();

    // construct parent node.
    int parent_value = a_node->value + b_node->value;
    printf("parent node = %d, a node = %d, b node = %d\n", parent_value,
           a_node->value, b_node->value);
    BTreeNode *parent_node = new BTreeNode(parent_value);
    parent_node->left_child =
        a_node; // note that a_node must be lesser than b_node (since we use proirity_queue)!
    parent_node->right_child = b_node;

    // push the parent node into pq again !!!
    pq.push(parent_node);
  }

  // well, now we get the root node of huffman tree.
  return pq.top();
}

void preorder_walk(BTreeNode *root) {
  if (root == nullptr)
    return;
  printf("%d ", root->value);
  if (root->left_child != nullptr)
    preorder_walk(root->left_child);
  if (root->right_child != nullptr)
    preorder_walk(root->right_child);
}

int main() {
  vector<int> v = {7, 5, 2, 4};
  printf("create huffman tree of {7, 5, 2, 5}\n\n");
  BTreeNode *root = create_huffman_tree(v);

  printf("root value = %d\n", root->value);
  printf("preorder_walk(root): \n");
  preorder_walk(root);
  printf("\n");
  return 0;
}
