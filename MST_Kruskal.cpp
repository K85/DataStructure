#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>


using namespace std;

/* UnionFindSet */
class UnionFindSet {

private:
    int capacity;
    vector<int> UF, rank;

public:
    explicit UnionFindSet(int capacity) {
      this->capacity = capacity;
      UF.resize(capacity);
      rank.resize(capacity);

      // UF starts from index 0.
      for (int i = 0; i < capacity; i++) {
        UF[i] = i;
        rank[i] = 1;
      }
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

/* Edge */
class Edge {
public:
    int from;
    int to;
    int weight;

public:
    Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}

    bool operator<(const Edge &rhs) const {
      return this->weight > rhs.weight;
    }
};

/* MST -> Kruskal */
int mst_kruskal(priority_queue<Edge> &PQ, int V) {
  /* Extra variables */
  int mst_cost = 0;
  int selected_edges = 0;

  /* Select V - 1 edges from PQ */
  UnionFindSet uf(V);
  while (!PQ.empty() && selected_edges < V - 1) {
    Edge edge = PQ.top();
    PQ.pop();
    if (uf.unite(edge.from, edge.to)) {
      printf("choose edge (%d, %d, %d)\n", edge.from, edge.to, edge.weight);

      /* Maintain extra variables */
      mst_cost += edge.weight;
      selected_edges++;
    }
  }
  return mst_cost;
}


int main() {
  // input graph
  int V, E;
  cin >> V >> E;
  priority_queue<Edge> PQ;
  for (int i = 0; i < E; i++) {
    int from, to, weight;
    cin >> from >> to >> weight;
    PQ.push(*new Edge(from, to, weight));
  }

  // algo
  mst_kruskal(PQ, V);
  return 0;
}
