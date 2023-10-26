#include <iostream>
#include <vector>
#include <queue>

struct Edge {
  int begin = 0;
  int end = 0;
  int weight = 0;
  Edge() = default;
  Edge(const int& begin, const int& end, const int& weight) : begin(begin), end(end), weight(weight) {
  }
};

struct Graph {
  int n = 0;
  int m = 0;
  std::vector<Edge> edges;
  Graph() = default;
  Graph(const int& n, const int& m) : n(n), m(m) {
    edges.resize(m);
  }
  friend std::istream& operator>>(std::istream&, Graph&);
};

std::istream& operator>>(std::istream& is, Graph& graph) {
  for (int i = 0; i < graph.m; ++i) {
    int begin = 0;
    int end = 0;
    int weight = 0;
    is >> begin >> end >> weight;
    graph.edges.emplace_back(begin, end, weight);
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, const std::vector<int> vector) {
  const int wrong_ans = 30000;
  for (size_t i = 1; i < vector.size(); ++i) {
    if (vector[i] != 1e9) {
      os << vector[i] << ' ';
    } else {
      os << wrong_ans << ' ';
    }
  }
  return os;
}

void Relax(const Edge& edge, std::vector<int>& dist) {
  if (dist[edge.end] > dist[edge.begin] + edge.weight && dist[edge.begin] != 1e9) {
    dist[edge.end] = dist[edge.begin] + edge.weight;
  }
}

void BellmanFord(const Graph& graph, std::vector<int>& dist) {
  dist[1] = 0;
  for (int i = 0; i < graph.n - 1; ++i) {
    for (const auto& edge : graph.edges) {
      Relax(edge, dist);
    }
  }
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Graph graph(n, m);
  std::cin >> graph;
  const int inf = 1e9;
  std::vector<int> dist(n + 1, inf);
  BellmanFord(graph, dist);
  std::cout << dist;
}