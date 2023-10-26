#include <iostream>
#include <vector>
#include <queue>

struct Graph {
  int n = 0;
  int m = 0;
  std::vector<std::vector<std::pair<int, size_t>>> edges;
  Graph() = default;
  Graph(const int& n, const int& m) : n(n), m(m) {
    edges.resize(n + 1);
  }
  friend std::istream& operator>>(std::istream&, Graph&);
};

std::istream& operator>>(std::istream& is, Graph& graph) {
  for (int i = 0; i < graph.m; ++i) {
    int begin = 0;
    int end = 0;
    size_t weight = 0;
    std::cin >> begin >> end >> weight;
    graph.edges[begin].emplace_back(std::make_pair(end, weight));
    graph.edges[end].emplace_back(std::make_pair(begin, weight));
  }
  return is;
}

size_t Prim(const Graph& graph) {
  //  Start vertex is first
  const int start_vertex = 1;
  const int inf = 1e9;
  std::vector<size_t> dist(graph.n + 1, inf);
  std::vector<bool> visited(graph.n + 1, false);
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
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Graph graph(n, m);
  std::cin >> graph;
  std::cout << Prim(graph);
  return 0;
}