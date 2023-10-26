#include <iostream>
#include <vector>
#include <queue>

struct Graph {
  int n, m;
  std::vector<std::vector<std::pair<int, int>>> edges;
  Graph() : n(0), m(0), edges(0) {
  }
  friend std::istream& operator>>(std::istream&, Graph&);
};

std::istream& operator>>(std::istream& is, Graph& graph) {
  graph.edges.resize(graph.n + 1);
  for (int i = 0; i < graph.m; ++i) {
    int begin, finish, val;
    is >> begin >> finish >> val;
    graph.edges[begin].emplace_back(std::make_pair(finish, val));
  }
  return is;
}

int64_t Dist(const Graph& graph, const int& begin, const int& end) {
  std::vector<int64_t> dist(graph.n + 1);
  std::fill(dist.begin(), dist.end(), 10e9);
  dist[begin] = 0;
  int cnt = 1;
  int k = 30;
  std::vector<std::queue<int>> q(k);
  q[0].push(begin);
  while (cnt != 0) {
    int temp = 0;
    while (q[temp].empty()) {
      ++temp;
    }
    temp %= k;
    int v = q[temp].front();
    q[temp].pop();
    --cnt;
    for (const auto u : graph.edges[v]) {
      if (dist[v] == 10e9 || dist[u.first] > dist[v] + u.second) {
        dist[u.first] = dist[v] + u.second;
        q[dist[u.first] % k].push(u.first);
        ++cnt;
      }
    }
  }
  if (dist[end] == 10e9) {
    return -1;
  }
  return dist[end];
}

void Out(const Graph& graph, const int& begin, const int& end) {
  int64_t dist = Dist(graph, begin, end);
  if (dist != -1) {
    std::cout << dist << '\n';
  } else {
    std::cout << -1;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Graph graph;
  int begin, finish;
  std::cin >> graph.n >> graph.m >> begin >> finish;
  std::cin >> graph;
  Out(graph, begin, finish);
  return 0;
}