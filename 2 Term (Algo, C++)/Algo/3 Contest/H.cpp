#include <iostream>
#include <queue>
#include <vector>
#include <limits>

struct Graph {
  int n = 0;
  int m = 0;
  std::vector<std::vector<std::pair<int, int>>> edges;
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
    int weight = 0;
    is >> begin >> end >> weight;
    graph.edges[begin].emplace_back(std::make_pair(end, weight));
  }
  return is;
}

struct Vertex {
  int city = 0;
  int number_night = 0;
  int cost = 0;
  Vertex() = default;
  Vertex(const int& city, const int& number_night, const int& cost)
      : city(city), number_night(number_night), cost(cost) {
  }
};

bool operator<(const Vertex& first, const Vertex& second) {
  return first.cost > second.cost;
}

size_t MinCost(const int& cnt_cities, const int& nights, const int& start, const int& finish, const Graph& graph) {
  const size_t inf = std::numeric_limits<size_t>::max();
  std::vector<std::vector<size_t>> dp(nights + 1, std::vector<size_t>(cnt_cities + 1, inf));
  dp[0][start] = 0;
  std::priority_queue<Vertex> prior_queue;
  prior_queue.emplace(start, 0, 0);
  while (!prior_queue.empty()) {
    Vertex vertex = prior_queue.top();
    prior_queue.pop();
    if (dp[vertex.number_night][vertex.city] >= static_cast<size_t>(vertex.cost)) {
      for (const auto& neighbour : graph.edges[vertex.city]) {
        int tomorrow_city = neighbour.first;
        size_t future_cost = static_cast<size_t>(neighbour.second) + static_cast<size_t>(vertex.cost);
        int future_night = vertex.number_night + 1;
        if (future_night <= nights && future_cost < dp[future_night][tomorrow_city]) {
          dp[future_night][tomorrow_city] = future_cost;
          prior_queue.emplace(tomorrow_city, future_night, future_cost);
        }
      }
    }
  }
  size_t min = inf;
  for (const auto& i : dp) {
    min = min > i[finish] ? i[finish] : min;
  }
  return min;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  int k = 0;
  int s = 0;
  int f = 0;
  const size_t inf = std::numeric_limits<size_t>::max();
  std::cin >> n >> m >> k >> s >> f;
  Graph graph(n, m);
  std::cin >> graph;
  size_t min = MinCost(n, k, s, f, graph);
  if (min != inf) {
    std::cout << min;
  } else {
    std::cout << "-1";
  }
  return 0;
}