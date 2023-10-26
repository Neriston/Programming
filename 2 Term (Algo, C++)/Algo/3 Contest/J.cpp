#include <iostream>
#include <vector>
#include <queue>
#include <limits>

struct Graph {
  int n = 0;
  std::vector<std::vector<std::pair<int, int>>> edges;
  Graph() = default;
  explicit Graph(const int& n) : n(n) {
    edges.resize(n + 1);
  }
  friend std::istream& operator>>(std::istream&, Graph&);
};

std::istream& operator>>(std::istream& is, Graph& graph) {
  for (int i = 1; i < graph.n + 1; ++i) {
    for (int j = 1; j < graph.n + 1; ++j) {
      int weight = 0;
      is >> weight;
      if (weight > 0) {
        graph.edges[i].emplace_back(std::make_pair(j, weight));
      }
    }
  }
  return is;
}

void Dijkstra(const Graph& graph, const int& vertex, std::vector<int>& dist) {
  dist[vertex] = 0;
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>>
      prior_queue;
  prior_queue.emplace(0, vertex);
  while (!prior_queue.empty()) {
    int vertex = prior_queue.top().second;
    int weight = prior_queue.top().first;
    prior_queue.pop();
    if (weight <= dist[vertex]) {
      for (const auto& neighbour : graph.edges[vertex]) {
        if (dist[neighbour.first] > dist[vertex] + neighbour.second) {
          dist[neighbour.first] = dist[vertex] + neighbour.second;
          prior_queue.emplace(dist[neighbour.first], neighbour.first);
        }
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int s = 0;
  int t = 0;
  std::cin >> n >> s >> t;
  Graph graph(n);
  std::cin >> graph;
  const int inf = 1e9;
  std::vector<int> dist(n + 1, inf);
  Dijkstra(graph, s, dist);
  std::cout << (dist[t] == 1e9 ? -1 : dist[t]);
  return 0;
}