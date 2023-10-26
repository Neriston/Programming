#include <iostream>
#include <vector>
#include <queue>
#include <limits>

struct Graph {
  int n = 0;
  int m = 0;
  std::vector<std::vector<std::pair<int, size_t>>> edges;
  Graph() = default;
  Graph(const int& n, const int& m) : n(n), m(m) {
    edges.resize(n);
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

void Dijkstra(const Graph& graph, const int& vertex, std::vector<size_t>& dist) {
  dist[vertex] = 0;
  std::priority_queue<std::pair<size_t, int>, std::vector<std::pair<size_t, int>>, std::greater<std::pair<size_t, int>>>
      prior_queue;
  prior_queue.emplace(0, vertex);
  while (!prior_queue.empty()) {
    int vertex = prior_queue.top().second;
    size_t weight = prior_queue.top().first;
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
  int k = 0;
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    int n = 0;
    int m = 0;
    std::cin >> n >> m;
    Graph graph(n, m);
    std::cin >> graph;
    int vertex = 0;
    std::cin >> vertex;
    const size_t wrong_ans = 2009000999;
    std::vector<size_t> dist(n, wrong_ans);
    Dijkstra(graph, vertex, dist);
    for (const auto& interval : dist) {
      std::cout << (interval == wrong_ans ? wrong_ans : interval) << ' ';
    }
    std::cout << '\n';
  }
  return 0;
}