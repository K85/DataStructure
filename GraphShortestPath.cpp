#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;

/* Constants */
const int INF = 0x3f3f3f3f;

/* GraphShortestPath */
class GraphShortestPath {

public:
    void print_graph(vector<vector<int>> &G) {
      for (int i = 0; i < G.size(); i++) {
        for (int j = 0; j < G.size(); j++) {
          printf("%d ", G[i][j]);
        }
        printf("\n");
      }
    }

public:
// NOTE: this function can't solve when the graph only has 1 vertex !
    vector<int> sssp_dijkstra(vector<vector<int>> &G, int root) {

      /* init */
      vector<int> d(G.size(), INF);
      vector<int> p(G.size(), -1);

      d[root] = 0;
      priority_queue<pair<int, int>, vector<pair<int, int>>, greater<> > PQ;
      PQ.push(make_pair(d[root], root));

      /* select vertexes from PQ */
      while (!PQ.empty()) {

        int from = PQ.top().second;
        PQ.pop();

        /* relaxation operation (for the adj edge of from) */
        for (int to = 0; to < G.size(); to++) {
          if (from == to) continue;
          if (G[from][to] == INF) continue;

          if (d[to] > d[from] + G[from][to]) {
            d[to] = d[from] + G[from][to];
            p[to] = from;
            PQ.push(make_pair(d[to], to));
          }
        }
      }
      return d;
    }

public:
    vector<vector<int>> apsp_floyd_warshall(vector<vector<int>> &G) {
      /* init */
      vector<vector<int>> D = G;
      // NOTE: self's distance is 0 !!!
      for (int k = 0; k < D.size(); k++) D[k][k] = 0;

      /* dp */
      for (int k = 0; k < G.size(); ++k) {
        for (int i = 0; i < G.size(); ++i) {
          for (int j = 0; j < G.size(); ++j) {
            D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
          }
        }
      }

      return D;
    }
};

int main() {

  /* input */
  int V, E;
  cin >> V >> E;
  vector<vector<int>> G(V, vector<int>(V, INF));
  for (int i = 0; i < E; i++) {
    int from, to, weight;
    cin >> from >> to >> weight;
    G[from][to] = weight;
    G[to][from] = weight;
  }

  /* algo */
  GraphShortestPath gsp;
  auto ans = gsp.apsp_floyd_warshall(G);
  gsp.print_graph(ans);
  return 0;
}
