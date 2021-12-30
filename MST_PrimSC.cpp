#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
#include <limits.h>

using namespace std;

void output_prim(vector<vector<int>> &G, vector<int> mst_vertexes, vector<int> parent) {
  /* print MST vertexes */
  for (int i = 1; i < mst_vertexes.size(); i++) {
    printf("%d ", mst_vertexes[i]);
  }
  printf("\n");

  /* print MST */
  vector<vector<int>> MST(parent.size(), vector<int>(parent.size()));
  for (int i = 1; i < G.size(); i++) {
    printf("(%d, %d, %d)\n", parent[i], i, G[i][parent[i]]);
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

int min_key_index(vector<int> &keys, vector<bool> &mstSet) {
  // Initialize min_value
  int min_value = INT_MAX, min_index;

  for (int i = 0; i < keys.size(); i++)
    //  NOTE: find the min_value keys outside the mstSet
    if (!mstSet[i] && keys[i] < min_value)
      min_value = keys[i], min_index = i;

  return min_index;
}

void mst_prim(vector<vector<int>> &G, int root) {
  /* init */
  int V = G.size();
  vector<int> parents(V, 47);
  vector<int> keys(V, INT_MAX); // Key values used to pick minimum weight edge in cut
  vector<bool> mst_set(V, false); // to represent set of vertices not yet included in MST

  // NOTE: let vertex 0 as the root of MST
  keys[root] = 0; // Make keys 0 so that this vertex is picked as first vertex
  parents[root] = -1; // First node is always root of MST

  /* algo */
  // NOTE: mst_vertex_count - 1 < V - 1 => mst_vertex_count < V
  vector<int> selected_vertexes;
  for (int mst_vertex_count = 0; mst_vertex_count < V; mst_vertex_count++) {

    // Add the picked vertex to the MST Set
    int from = min_key_index(keys, mst_set);
    mst_set[from] = true;

    printf("choose vertex: %d\n",from);
    selected_vertexes.push_back(from);

    // update parents[] and keys[]
    for (int to = 0; to < V; to++) {
      /* Relaxation Operation */
      if (G[from][to] && !mst_set[to] && G[from][to] < keys[to]) {
        printf("G[%d][%d] = %d, keys[%d] = %d\n", from, to, G[from][to], to, keys[to]);
        parents[to] = from;
        // NOTE: set the dists to G[from][to] means the edge is reachable currently !
        keys[to] = G[from][to];
      }
    }
  }

  /* print the constructed MST */
  output_prim(G, selected_vertexes, parents);
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
  mst_prim(G, 0);
  return 0;
}
