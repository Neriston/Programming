#include <iostream>
#include <vector>

struct Graph {
  int n = 0;
  std::vector<std::vector<int>> edges;
  Graph() = default;
  explicit Graph(const int& n) : n(n) {
    edges.resize(n, std::vector<int>(n));
  }
  friend std::istream& operator>>(std::istream&, Graph&);
};

std::istream& operator>>(std::istream& is, Graph& graph) {
  for (int i = 0; i < graph.n; ++i) {
    for (int j = 0; j < graph.n; ++j) {
      int weight = 0;
      std::cin >> weight;
      graph.edges[i][j] = weight;
    }
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<int>>& vector) {
  for (const auto& string : vector) {
    for (const auto& elem : string) {
      std::cout << elem << ' ';
    }
    std::cout << '\n';
  }
  return os;
}

void FloydWarshall(Graph& graph) {
  for (int i = 0; i < graph.n; ++i) {
    for (int j = 0; j < graph.n; ++j) {
      for (int k = 0; k < graph.n; ++k) {
        int min = std::min(graph.edges[j][k], graph.edges[j][i] + graph.edges[i][k]);
        graph.edges[j][k] = min;
      }
    }
  }
}

int main() {
  int n = 0;
  std::cin >> n;
  Graph graph(n);
  std::cin >> graph;
  FloydWarshall(graph);
  std::cout << graph.edges;
}