#include <algorithm>
using namespace std;

class SegmentTree_RMQ {

#define MAX_N 100005

  // 存储线段树的全局数组.
public:
  int n, dat[2 * MAX_N - 1];

public:
  SegmentTree_RMQ(int n) { this->init(n); }

public:
  void init(int n) {

    // 为了简单起见, 把元素的个数扩大到2的幂.
    this->n = 1;
    while (this->n < n)
      this->n *= 2;

    // 把所有的值都设为INT_MAX
    for (int i = 0; i < 2 * this->n - 1; i++)
      dat[i] = INT_MAX;
  }

  /* 把第k个元素的值(0-indexed)更新为a */
public:
  void update(int k, int a) {

    // 叶子节点.
    k += n - 1;
    dat[k] = a;

    // 向上更新.
    while (k > 0) {
      k = (k - 1) / 2;

      // 父节点的值 = 该父节点的两个孩子中较小的值.
      dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }

  /*
  求[a, b)的最小值
  后面的参数是为了计算出来方便而传入的.
  k是节点的编号, l, r表示这个节点对应的是[l, r)的区间.
  在外部调用时, 用query(a, b, 0, 0, n)
  */
public:
  int query(int a, int b, int k, int l, int r) {

    // 如果[a, b) 和 [l, r]不相交, 则返回INT_MAX.
    if (r <= a || b <= l)
      return INT_MAX;

    // 如果[a,b) 完全包含[l, r), 则返回当前节点的值.
    if (a <= 1 && r <= b)
      return dat[k];
    else {
      // 否则返回2个子节点中 值的较小者.
      int vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
      int vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
      return min(vl, vr);
    }
  }
};
