#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;
class UnionFindSet {

private:
  int capacity;
  vector<int> UF, rank;

public:
  UnionFindSet(int capacity) {
    capacity = capacity;
    UF.resize(capacity);
    rank.resize(capacity, 1);

    // UF starts from index 0.
    for (int i = 0; i < capacity; i++)
      UF[i] = i;
  }

public:
  int find(int x) {
    return UF[x] == x ? x : UF[x] = find(UF[x]); // sort by rank order.
  }

public:
  bool unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY)
      return false;
    else if (rank[rootX] < rank[rootY])
      swap(rootX, rootY);
    rank[rootX] += rank[rootY]; // with path compression.

    UF[rootY] = rootX;
    return true;
  }

public:
  bool same(int x, int y) { return find(x) == find(y); }
};

int main() {

  UnionFindSet UF(100);
  UF.unite(3, 4);
  UF.unite(4, 5);
  printf("same(3, 5) = %d\n", UF.same(3, 5));
  printf("root of 4: %d\n", UF.find(4));
  printf("root of 5: %d\n", UF.find(5));

  return 0;
}
