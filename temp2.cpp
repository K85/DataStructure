#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;

const int dij4[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

struct Position {
  int posI;
  int posJ;
  int health;

  // BFS with PriorityQueue
  bool operator<(const Position &another) const {
    return this->health < another.health; // higher health means shorter path !
  }
};

vector<vector<int>> visited; // 1 = visted, 0 = not visited.
void bfs(const vector<vector<int>> &G, int startI, int startJ,
         int startHealth) {
  // prepare bfs
  priority_queue<Position> Q;

  Q.push((Position){startI, startJ, startHealth});
  visited[startI][startJ] = 1;

  while (!Q.empty()) {
    Position curPos = Q.top(); // it's amazing if we use const Position &, then
                               // we will get WA.
    Q.pop();

    // try all directions.
    for (int k = 0; k < 4; k++) {
      // get next pos.
      int ti = curPos.posI + dij4[k][0];
      int tj = curPos.posJ + dij4[k][1];

      // out of bounds?
      if (ti < 0 || tj < 0 || ti >= G.size() || tj >= G[0].size())
        continue;

      // visted ?
      if (visited[ti][tj])
        continue;

      // has enough health ?
      if (curPos.health < G[ti][tj])
        continue;

      // go !
      visited[ti][tj] = 1; // attention: must book or TLE
      Q.push((Position){ti, tj, curPos.health - G[ti][tj]});
    }
  }
}

int main() {

  // input map.
  int cols, rows;
  cin >> cols >> rows;

  vector<vector<int>> G(rows, vector<int>(cols));
  visited.resize(rows, vector<int>(cols, 0));
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cin >> G[i][j];
    }
  }

  int startI, startJ;
  cin >> startJ >> startI;
  int startHealth;
  cin >> startHealth;

  // bfs.
  bfs(G, startI, startJ, startHealth);

  // output map.
  for (int i = 0; i < visited.size(); i++) {
    for (int j = 0; j < visited[0].size(); j++) {
      cout << visited[i][j];
    }
    cout << endl;
  }
  return 0;
}
