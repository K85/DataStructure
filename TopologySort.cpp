#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

vector<int> topology_sort(vector<vector<int>> &G) {
  vector<int> ans;
  vector<bool> topology_set(G.size(), false);

  /* Re-run the main-loop until all the vertexes are selected. */
  while (ans.size() != G.size()) {
    // find all the vertexes whose in-degree is 0
    for (int to = 0; to < G.size(); to++) {

      /* already exist in ans ? */
      if (topology_set[to]) continue;

      /* Count the in-degree of vertex to */
      bool ok = true;
      for (int from = 0; from < G.size(); from++) {
        if (topology_set[from]) continue;
        if (G[from][to]) {
          ok = false;
          break;
        }
      }

      if (ok) {
        printf("%d ", to);
        ans.push_back(to);
        topology_set[to] = true;
        // NOTE: break immediately if we have selected a new vertex.
        break;
      }
    }
  }

  return ans;
}

int main() {
  /* input */
  int V, E;
  cin >> V >> E;
  vector<vector<int>> G(V, vector<int>(V, 0));
  for (int i = 0; i < E; i++) {
    int from, to;
    cin >> from >> to;
    G[from][to] = 1;
  }

  /* algo */
  topology_sort(G);
  return 0;
}
