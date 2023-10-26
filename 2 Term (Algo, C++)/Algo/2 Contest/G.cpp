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
  is >> graph.n >> graph.m;
  graph.edges.resize(graph.n + 1);
  for (int i = 0; i < graph.m; ++i) {
    int begin, finish;
    is >> begin >> finish;
    graph.edges[begin].emplace_back(finish);
  }
  return is;
}

bool HasCycleDfs(const Graph& graph, const int& vertex, std::vector<Color>& color, std::vector<int>& parent,
                 int& last) {
  color[vertex] = grey;  // 1 is grey
  for (const auto neighbour : graph.edges[vertex]) {
    if (color[neighbour] == 1 || (color[neighbour] == 0 && HasCycleDfs(graph, neighbour, color, parent, last))) {
      parent.emplace_back(vertex);
      if (last == 0) {
        last = neighbour;
      }
      return true;
    }
  }
  color[vertex] = black;  // 2 is black
  return false;
}

bool HasCycle(const Graph& graph, std::vector<int>& parent, int& last) {
  std::vector<Color> color(graph.n + 1, white);  // 0 is white
  for (int i = 1; i < graph.n + 1; ++i) {
    if (color[i] == white && HasCycleDfs(graph, i, color, parent, last)) {
      return true;
    }
    parent.clear();
  }
  return false;
}

int main() {
  Graph graph;
  std::cin >> graph;
  std::vector<int> parent;
  int last = 0;
  if (HasCycle(graph, parent, last)) {
    std::cout << "YES\n";
    size_t size = parent.size() - 1;
    while (parent[size] != last) {
      --size;
    }
    for (auto i = static_cast<int>(size); i >= 0; --i) {
      std::cout << parent[i] << ' ';
    }
  } else {
    std::cout << "NO";
  }
  return 0;
}