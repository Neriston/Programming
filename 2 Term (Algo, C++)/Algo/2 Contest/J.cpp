#include <iostream>
#include <vector>

struct Graph {
  int n, m;
  std::vector<std::vector<int>> edges;
  Graph() : n(0), m(0), edges(0) {
  }
  friend std::istream& operator>>(std::istream&, Graph&);
};

std::istream& operator>>(std::istream& is, Graph& graph) {
  is >> graph.n >> graph.m;
  graph.edges.resize(graph.n + 1);
  for (int i = 0; i < graph.m; ++i) {
    int begin, finish;
    is >> begin >> finish;
    graph.edges[begin].emplace_back(finish);
  }
  return is;
}

bool TopSortDfs(const Graph& graph, const int& v, std::vector<int>& color, std::vector<int>& top_sorted) {
  color[v] = 1;
  for (const auto u : graph.edges[v]) {
    if (color[u] == 1 || (color[u] == 0 && !TopSortDfs(graph, u, color, top_sorted))) {
      return false;
    }
  }
  color[v] = 2;
  top_sorted.emplace_back(v);
  return true;
}

bool TopSort(const Graph& graph, std::vector<int>& top_sorted) {
  std::vector<int> color(graph.n + 1, 0);
  for (int i = 1; i < graph.n + 1; ++i) {
    if (color[i] == 0 && !TopSortDfs(graph, i, color, top_sorted)) {
      return false;
    }
  }
  return true;
}

int main() {
  Graph graph;
  std::cin >> graph;
  std::vector<int> top_sorted;
  if (TopSort(graph, top_sorted)) {
    for (auto i = static_cast<int>(top_sorted.size() - 1); i >= 0; --i) {
      std::cout << top_sorted[i] << ' ';
    }
  } else {
    std::cout << -1;
  }
  return 0;
}