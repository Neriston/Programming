#include <iostream>
#include <vector>
#include <queue>

struct Point {
  int x, y, val;
  bool flag;
  Point() : x(0), y(0), val(0), flag(false) {
  }
  Point(const int& x, const int& y, const int& val) : x(x), y(y), val(val), flag(false) {
  }
};

struct Graph {
  int n, m;
  std::vector<std::vector<Point>> city;
  Graph() = default;
  explicit Graph(const int& n, const int& m) : n(n), m(m), city(n + 1, std::vector<Point>(m + 1)) {
  }
};

void Dist(Graph& graph, std::vector<std::vector<int>>& ans) {
  std::queue<Point> queue;
  for (int i = 1; i < graph.n + 1; ++i) {
    for (int j = 1; j < graph.m + 1; ++j) {
      int val;
      std::cin >> val;
      if (val == 1) {
        queue.push(Point(j, i, 1));
        ans[i][j] = 0;
      } else {
        ans[i][j] = 10e8;
      }
      graph.city[i][j] = {j, i, val};
    }
  }
  while (!(queue.empty())) {
    Point p = queue.front();
    queue.pop();
    if (p.x - 1 >= 1 && !graph.city[p.y][p.x - 1].flag && graph.city[p.y][p.x - 1].val != 1) {
      graph.city[p.y][p.x - 1].flag = true;
      ans[p.y][p.x - 1] = ans[p.y][p.x] + 1;
      queue.push(graph.city[p.y][p.x - 1]);
    }
    if (p.x + 1 <= graph.m && !graph.city[p.y][p.x + 1].flag && graph.city[p.y][p.x + 1].val != 1) {
      graph.city[p.y][p.x + 1].flag = true;
      ans[p.y][p.x + 1] = ans[p.y][p.x] + 1;
      queue.push(graph.city[p.y][p.x + 1]);
    }
    if (p.y - 1 >= 1 && !graph.city[p.y - 1][p.x].flag && graph.city[p.y - 1][p.x].val != 1) {
      graph.city[p.y - 1][p.x].flag = true;
      ans[p.y - 1][p.x] = ans[p.y][p.x] + 1;
      queue.push(graph.city[p.y - 1][p.x]);
    }
    if (p.y + 1 <= graph.n && !graph.city[p.y + 1][p.x].flag && graph.city[p.y + 1][p.x].val != 1) {
      graph.city[p.y + 1][p.x].flag = true;
      ans[p.y + 1][p.x] = ans[p.y][p.x] + 1;
      queue.push(graph.city[p.y + 1][p.x]);
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph(n, m);
  std::vector<std::vector<int>> ans(n + 1, std::vector<int>(m + 1));
  Dist(graph, ans);
  for (int i = 1; i < n + 1; ++i) {
    for (int j = 1; j < m + 1; ++j) {
      std::cout << ans[i][j] << ' ';
    }
    std::cout << '\n';
  }
  return 0;
}