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
  is >> graph.n;
  graph.edges.resize(graph.n + 1);
  for (int i = 1; i < graph.n; ++i) {
    for (int j = i + 1; j <= graph.n; ++j) {
      char letter;
      std::cin >> letter;
      if (letter == 'R') {
        graph.edges[j].emplace_back(i);
      } else {
        graph.edges[i].emplace_back(j);
      }
    }
  }
  return is;
}

bool HasCycleDfs(const Graph& graph, const int& v, std::vector<int>& color) {
  color[v] = 1;  // 1 is gray
  for (const auto u : graph.edges[v]) {
    if (color[u] == 1 || (color[u] == 0 && HasCycleDfs(graph, u, color))) {
      return true;
    }
  }
  color[v] = 2;  // 2 is black
  return false;
}

bool HasCycle(const Graph& graph) {
  std::vector<int> color(graph.n + 1, 0);  // 0 is white
  for (int i = 1; i < graph.n + 1; ++i) {
    if (color[i] == 0 && HasCycleDfs(graph, i, color)) {
      return true;
    }
  }
  return false;
}

int main() {
  Graph graph;
  std::cin >> graph;
  if (HasCycle(graph)) {
    std::cout << "NO";
  } else {
    std::cout << "YES";
  }
  return 0;
}