#include <iostream>
#include <vector>

enum Color { white, grey, black };

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
  for (int i = 1; i < graph.n + 1; ++i) {
    int v;
    is >> v;
    graph.edges[i].emplace_back(v);
  }
  return is;
}

bool HasCycleDfs(const Graph& graph, const int& vertex, std::vector<Color>& color) {
  bool flag = false;
  color[vertex] = grey;  // 1 is gray
  for (const auto neighbour : graph.edges[vertex]) {
    if (color[neighbour] == grey || (color[neighbour] == white && HasCycleDfs(graph, neighbour, color))) {
      flag = true;
    }
  }
  color[vertex] = black;  // 2 is black
  return flag;
}

int64_t HasCycle(const Graph& graph) {
  int64_t cnt = 0;
  std::vector<Color> color(graph.n + 1, white);  // 0 is white
  for (int i = 1; i < graph.n + 1; ++i) {
    if (color[i] == white && HasCycleDfs(graph, i, color)) {
      ++cnt;
    }
  }
  return cnt;
}

int main() {
  Graph graph;
  std::cin >> graph;
  std::cout << HasCycle(graph);
  return 0;
}