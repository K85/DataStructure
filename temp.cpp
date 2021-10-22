#include <deque>
#include <iostream>
#include <queue>
#include <string.h>

using namespace std;
struct Position {
  int i;
  int j;
  int health;
  // BFS with PriorityQueue
  bool operator<(const Position &another) const {
    return this->health < another.health;
  }
};

int main() {

  // input map.
  int cols, rows;
  cin >> cols >> rows;
  
  int M[rows][cols];
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cin >> M[i][j];
    }
  }

  int startJ, startI;
  cin >> startJ >> startI; // attention: read startJ firstly.
  int startHealth;
  cin >> startHealth;

  // bfs.
  priority_queue<Position> Q;
  Q.push({startI, startJ, startHealth});

  int visited[rows][cols];
  memset(visited, 0, sizeof(visited));

  while (!Q.empty()) {
    const Position& cur_position = Q.top(); Q.pop();
    int cur_position_i = cur_position.i;
    int cur_position_j = cur_position.j;
    int cur_position_health = cur_position.health;

    // filter visited.
    if (visited[cur_position_i][cur_position_j]) continue;
    visited[cur_position_i][cur_position_j] = 1;
    
    // try all directions. (totally 4 directions.)
    int next_position_health;
    if (cur_position_j != cols - 1 && cur_position_health >= M[cur_position_i][cur_position_j + 1]) {
      next_position_health = cur_position_health - M[cur_position_i][cur_position_j + 1];
      Q.push({cur_position_i, cur_position_j + 1, next_position_health});

      // visited[cur_position_i][cur_position_j + 1] = 1;
    }
    if (cur_position_j != 0 && cur_position_health >= M[cur_position_i][cur_position_j - 1]) {
      next_position_health = cur_position_health - M[cur_position_i][cur_position_j - 1];
      Q.push({cur_position_i, cur_position_j - 1, next_position_health});

      // visited[cur_position_i][cur_position_j - 1] = 1;
    }
    if (cur_position_i != rows - 1 && cur_position_health >= M[cur_position_i + 1][cur_position_j]) {
      next_position_health = cur_position_health - M[cur_position_i + 1][cur_position_j];
      Q.push({cur_position_i + 1, cur_position_j, next_position_health});

      // visited[cur_position_i + 1][cur_position_j] = 1;
    }
    if (cur_position_i != 0 && cur_position_health >= M[cur_position_i - 1][cur_position_j]) {
      next_position_health = cur_position_health - M[cur_position_i - 1][cur_position_j];
      Q.push({cur_position_i - 1, cur_position_j, next_position_health});

      // visited[cur_position_i - 1][cur_position_j] = 1;
    }
  }

  // output map.
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << visited[i][j];
    }
    cout << endl;
  }

  return 0;
}
