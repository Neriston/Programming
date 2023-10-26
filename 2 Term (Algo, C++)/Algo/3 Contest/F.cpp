#include <iostream>
#include <vector>
#include <queue>

struct Graph {
  int n = 0;
  int m = 0;
  std::vector<std::vector<std::pair<int, size_t>>> edges;
  Graph() = default;
  Graph(const int& n, const int& m) : n(n), m(m) {
    edges.resize(n + 2);
  }
  friend std::istream& operator>>(std::istream&, Graph&);
};

std::istream& operator>>(std::istream& is, Graph& graph) {
  for (int i = 1; i < graph.n + 1; ++i) {
    for (int j = 1; j < graph.n + 1; ++j) {
      size_t weight = 0;
      std::cin >> weight;
      if (i != j) {
        graph.edges[i].emplace_back(std::make_pair(j, weight));
      }
    }
  }
  for (int i = 1; i < graph.n + 1; ++i) {
    size_t weight = 0;
    std::cin >> weight;
    graph.edges[i].emplace_back(std::make_pair(graph.n + 1, weight));
    graph.edges[graph.n + 1].emplace_back(std::make_pair(i, weight));
  }
  return is;
}

size_t Prim(const Graph& graph) {
  //  Start vertex is first
  const int start_vertex = 1;
  const int inf = 1e9;
  std::vector<size_t> dist(graph.n + 2, inf);
  std::vector<bool> visited(graph.n + 2, false);
  dist[start_vertex] = 0;
  std::priority_queue<std::pair<size_t, int>, std::vector<std::pair<size_t, int>>, std::greater<std::pair<size_t, int>>>
      prior_queue;
  prior_queue.push(std::make_pair(0, start_vertex));
  size_t min_weight = 0;
  while (!prior_queue.empty()) {
    int vertex = prior_queue.top().second;
    size_t weight = prior_queue.top().first;
    prior_queue.pop();
    if (!visited[vertex]) {
      visited[vertex] = true;
      min_weight += weight;
      for (const auto& neighbour : graph.edges[vertex]) {
        if (!visited[neighbour.first] && dist[neighbour.first] > neighbour.second) {
          dist[neighbour.first] = neighbour.second;
          prior_queue.push(std::make_pair(neighbour.second, neighbour.first));
        }
      }
    }
  }
  return min_weight;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  int quantity_edges = (n * (n - 1)) / 2;
  Graph graph(n, quantity_edges);
  std::cin >> graph;
  std::cout << Prim(graph);
  return 0;
}