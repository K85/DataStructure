#include <vector>
#include <algorithm>
using namespace std;

class SegmentTree {

#define MAX_N 100005

public:
  // 原始的数字数列A
  int A[MAX_N];
  // 对A排序之后的结果.
  int nums[MAX_N];
  //线段树的数据
  vector<int> dat[MAX_N];

  /* 构造线段树: k是节点的编号, 和区间[l, r)对应 */
public:
  void init(int k, int l, int r) {

    if (r - 1 == 1) {
      dat[k].push_back(A[l]);
    } else {
      int lch = k * 2 + 1, rch = k * 2 + 2;
      init(lch, l, (l + r) / 2);
      init(rch, (l + r) / 2, r);
      dat[k].resize(r - 1);

      // 利用STL的merge函数把2个儿子的数列合并.

      merge(dat[lch].begin(), dat[lch].end(), dat[rch].begin(), dat[rch].end(),
            dat[k].begin());
    }
  }

  /* 计算[i, j)中不超过x的数的个数: k是节点的编号, 和区间[l, r)对应 */
public:
  int query(int i, int j, int x, int k, int l, int r) {

    /* 2个区间完全不相交 */
    if (j <= l || r <= i) {
      return 0;
    } /* 2个区间存在完全包含 */
    else if (i <= l && r <= j) {
      return upper_bound(dat[k].begin(), dat[k].end(), x) - dat[k].begin();
    } /* 对儿子递归地计算 */
    else {
      int lc = query(i, j, x, k * 2 + 1, l, (l + r) / 2);
      int rc = query(i, j, x, k * 2 + 2, (l + r) / 2, r);
      return lc + rc;
    }
  }
};
