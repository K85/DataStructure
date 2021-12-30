#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
#include <limits.h>

using namespace std;

const int INF = 0x3f3f3f3f;
void output(vector<vector<int>> &G, vector<int> mst_vertexes, vector<int> parent) {

  /* print MST vertexes */
  for (int i = 1; i < mst_vertexes.size(); i++) {
    printf("%d ", mst_vertexes[i]);
  }
  printf("\n");

  /* print MST */
  vector<vector<int>> MST(parent.size(), vector<int>(parent.size()));
  for (int i = 1; i < G.size(); i++) {
//    printf("(%d, %d, %d)\n", parent[i], i, G[i][parent[i]]);
    MST[parent[i]][i] = G[i][parent[i]];
    MST[i][parent[i]] = G[i][parent[i]];
  }

  for (int i = 0; i < MST.size(); i++) {
    for (int j = 0; j < MST.size(); j++) {
      printf("%d ", MST[i][j]);
    }
    printf("\n");
  }
}

vector<int> mst_prim(vector<vector<int>> &G, int V, int root) {
  /* init */
  vector<int> parents(V, 47);
  vector<int> dists(V, INF); // Key values used to pick minimum weight edge in cut

  // PQ and mst_set
  vector<bool> mst_set(V, false); // to represent set of vertices not yet included in MST
  auto cmp = [&](const pair<int, int> &lhs, const pair<int, int> &rhs) {
      return lhs.first > rhs.first;
  };
  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> PQ(cmp);

  // NOTE: let vertex 0 as the root of MST
  dists[root] = 0; // Make dists 0 so that this vertex is picked as first vertex
  PQ.push(make_pair(dists[root], root));
  parents[root] = -1; // First node is always root of MST

  /* algo */
  // NOTE: here we modify mst_vertex_count <= V - 1 (instead of < V - 1) to record the last vertex.
  vector<int> mst_vertexes;
  for (int mst_vertex_count = 0; mst_vertex_count <= V - 1; mst_vertex_count++) {

    // Add the picked vertex to the MST Set
    int from;
    do {
      from = PQ.top().second;
      PQ.pop();
    } while (mst_set[from]);
    mst_set[from] = true;

    // NOTE: record.
    mst_vertexes.push_back(from);

    // update parents[] and dists[]
    for (int to = 0; to < V; to++)
      if (G[from][to] && !mst_set[to] && G[from][to] < dists[to]) {
        dists[to] = G[from][to];
        PQ.push(make_pair(dists[to], to));
        parents[to] = from;
      }
  }

  /* print the constructed MST */
  output(G, mst_vertexes, parents);
  return mst_vertexes;
}

int main() {
  // input graph.
  int v, e;
  cin >> v >> e;
  vector<vector<int>> G(v, vector<int>(v));
  for (int i = 0; i < e; i++) {
    int from, to, weight;
    cin >> from >> to >> weight;
    G[from][to] = weight;
    G[to][from] = weight;
  }

  // algo
  mst_prim(G, v, 0);
  return 0;
}
