#include <iostream>
#include <vector>

struct Graph {
  int n;
  std::vector<std::vector<int>> edges;
  Graph() : n(0), edges(0) {
  }
  explicit Graph(const int& n) : n(n), edges(n + 1) {
  }
};

int main() {
  int n;
  std::cin >> n;
  Graph g(n);
  int k;
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    int comm;
    std::cin >> comm;
    if (comm == 1) {
      int u, v;
      std::cin >> u >> v;
      g.edges[u].emplace_back(v);
      g.edges[v].emplace_back(u);
    } else {
      int u;
      std::cin >> u;
      for (const auto v : g.edges[u]) {
        std::cout << v << ' ';
      }
      std::cout << '\n';
    }
  }
  return 0;
}