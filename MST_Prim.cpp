#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
#include <limits.h>

using namespace std;

void output(vector<vector<int>> &G, vector<int> mst_vertexes,vector<int> parent) {

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

int min_key(vector<int> key, int v, vector<bool> mstSet) {
  // Initialize min_value
  int min_value = INT_MAX, min_index;

  for (int i = 0; i < v; i++)
    //  NOTE: find the min_value key outside the mstSet
    if (!mstSet[i] && key[i] < min_value)
      min_value = key[i], min_index = i;

  return min_index;
}

vector<int> mst_prim(vector<vector<int>> &G, int v, int root) {
  /* init */
  vector<int> parents(v, 47);
  vector<int> dists(v, INT_MAX); // Key values used to pick minimum weight edge in cut
  vector<bool> mst_set(v, false); // to represent set of vertices not yet included in MST

  // NOTE: let vertex 0 as the root of MST
  dists[root] = 0; // Make dists 0 so that this vertex is picked as first vertex
  parents[root] = -1; // First node is always root of MST

  /* algo */
  // NOTE: here we modify mst_vertex_count <= v - 1 (instead of < v - 1) to record the last vertex.
  vector<int> mst_vertexes;
  for (int mst_vertex_count = 0; mst_vertex_count <= v - 1; mst_vertex_count++) {

    // Add the picked vertex to the MST Set
    int u = min_key(dists, v, mst_set);
    mst_set[u] = true;

    // NOTE: record.
    mst_vertexes.push_back(u);

    // update parents[] and dists[]
    for (int i = 0; i < v; i++)
      if (G[u][i] && !mst_set[i] && G[u][i] < dists[i])
        parents[i] = u, dists[i] = G[u][i];
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
  mst_prim(G, v,  0);
  return 0;
}
