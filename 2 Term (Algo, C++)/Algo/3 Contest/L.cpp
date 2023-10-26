#include <iostream>
#include <vector>
#include <queue>

struct Edge {
  int vertex = 0;
  int weight = 0;
  Edge() = default;
  Edge(const int& vertex, const int& weight) : vertex(vertex), weight(weight) {
  }
  bool operator<(const Edge& other) const {
    return weight < other.weight;
  }
};

struct Graph {
  int n = 0;
  int m = 0;
  std::vector<std::vector<Edge>> edges;
  Graph() = default;
  Graph(const int& n, const int& m) : n(n), m(m) {
    edges.resize(n + 1);
  }
  friend std::istream& operator>>(std::istream&, Graph&);
};

std::istream& operator>>(std::istream& is, Graph& graph) {
  int begin = 0;
  int end = 0;
  int weight = 0;
  for (int i = 0; i < graph.n; ++i) {
    graph.edges[graph.n].emplace_back(i, 0);
  }
  for (int i = 0; i < graph.m; ++i) {
    is >> begin >> end >> weight;
    graph.edges[begin].emplace_back(end, weight);
  }
  return is;
}

void FloydWarshall(Graph& graph, std::vector<int>& dist) {
  dist[graph.n] = 0;
  for (int i = 1; i < graph.n; ++i) {
    for (int j = 0; j < graph.n + 1; ++j) {
      for (const auto& neighbour : graph.edges[j]) {
        dist[neighbour.vertex] = std::min(dist[neighbour.vertex], dist[j] + neighbour.weight);
      }
    }
  }
  for (int i = 0; i < graph.n; ++i) {
    for (auto& neighbour : graph.edges[i]) {
      neighbour.weight += (dist[i] - dist[neighbour.vertex]);
    }
  }
}

void Dijkstra(Graph& graph, const int begin, const std::vector<int> dist, int& max) {
  std::priority_queue<Edge> queue;
  std::vector<int> distance(graph.n + 1, -1e9);
  std::vector<bool> visited(graph.n + 1, false);
  queue.emplace(begin, dist[begin]);
  distance[begin] = 0;
  while (!queue.empty()) {
    Edge temp = queue.top();
    queue.pop();
    visited[temp.vertex] = true;
    for (const auto& neighbour : graph.edges[temp.vertex]) {
      if (!visited[neighbour.vertex] && distance[temp.vertex] > neighbour.weight + distance[neighbour.vertex]) {
        distance[neighbour.vertex] = distance[temp.vertex] - neighbour.weight;
        queue.emplace(neighbour.vertex, distance[neighbour.vertex]);
      }
    }
  }
  for (int i = 0; i < graph.n; ++i) {
    if (distance[i] != -1e9) {
      distance[i] = (dist[i] - dist[begin] - distance[i]);
      max = std::max(max, distance[i]);
    }
  }
}

int Johnson(Graph& graph) {
  std::vector<int> dist(graph.n + 1, 1e9);
  FloydWarshall(graph, dist);
  int max = 0;
  for (int i = 0; i < graph.n; ++i) {
    Dijkstra(graph, i, dist, max);
  }
  return max;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Graph graph(n, m);
  std::cin >> graph;
  std::cout << Johnson(graph);
}