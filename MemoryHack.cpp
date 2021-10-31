#include <algorithm>
#include <iostream>
#include <stdio.h>

using namespace std;

class Node {
public:
  int left_child;
  int right_child;

public:
  Node(int leftchild, int rightchild)
      : left_child(leftchild), right_child(rightchild) {}

public:
  void L() { printf("call L()\n"); }

public:
  void R() { printf("call R()\n"); }
};

int main() {

  printf("the address of main(): %d\n", main);
  Node *node = new Node(100, 200);
  printf("the address of L(): %d\n", &Node::L);
  printf("the address of R(): %d\n", &Node::R);
  printf("\n");

  printf("now we get the union of L() and R()\n");
  union {
    void *pv;
    void (Node::*pfn)();
  } u_L;
  u_L.pfn = &Node::L;

  union {
    void *pv;
    void (Node::*pfn)();
  } u_R{};
  u_R.pfn = &Node::R;

  printf("the address of u_L.pv = %d\n", u_L.pv);
  printf("the address of u_R.pv = %d\n", u_R.pv);
  printf("modify the address of u_L.pv\n");

  (node->*u_L.pfn)();
  //  memcpy(u_L.pv, u_R.pv, 5);
  //  node->L();

  //  printf("\n");
  //  printf("Call node->L() and node->R()\n");
  //  node->L();
  //  node->R();
  return 0;
}
