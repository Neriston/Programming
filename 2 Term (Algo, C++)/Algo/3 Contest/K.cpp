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
  std::vector<Edge> edges;
  Graph() = default;
  explicit Graph(const int& n) : n(n) {
  }
  friend std::istream& operator>>(std::istream&, Graph&);
};

std::istream& operator>>(std::istream& is, Graph& graph) {
  const int absence = 1e5;
  for (int i = 1; i < graph.n + 1; ++i) {
    graph.edges.emplace_back(i, 0, 0);
    for (int j = 1; j < graph.n + 1; ++j) {
      int weight = 0;
      is >> weight;
      if (weight != absence) {
        graph.edges.emplace_back(i, j, weight);
      }
    }
  }
  return is;
}

bool Relax(const Edge& edge, std::vector<int64_t>& dist, std::vector<int>& cycle) {
  if (dist[edge.end] > dist[edge.begin] + edge.weight) {
    dist[edge.end] = dist[edge.begin] + edge.weight;
    cycle[edge.end] = edge.begin;
    return true;
  }
  return false;
}

void FormReversedCorrectCycle(const std::vector<int>& cycle, std::vector<int>& ans) {
  int last = 0;
  for (size_t i = 0; i < cycle.size(); ++i) {
    last = cycle[last];
  }
  int copy_last = last;
  ans.emplace_back(last);
  last = cycle[last];
  while (last != copy_last) {
    ans.emplace_back(last);
    last = cycle[last];
  }
  ans.emplace_back(copy_last);
}

bool HasNegativeCycle(const Graph& graph, std::vector<int>& ans) {
  std::vector<int64_t> dist(graph.n + 1, 1e9);
  std::vector<int> cycle(graph.n + 1);
  for (int j = 0; j < graph.n; ++j) {
    for (const auto& edge : graph.edges) {
      Relax(edge, dist, cycle);
    }
  }
  for (const auto& edge : graph.edges) {
    if (Relax(edge, dist, cycle)) {
      FormReversedCorrectCycle(cycle, ans);
      return true;
    }
  }
  return false;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  Graph graph(n);
  std::cin >> graph;
  std::vector<int> cycle(n + 1);
  std::vector<int> ans;
  if (HasNegativeCycle(graph, ans)) {
    std::cout << "YES\n";
    std::cout << ans.size() << '\n';
    for (auto i = static_cast<int>(ans.size() - 1); i >= 0; --i) {
      std::cout << ans[i] << ' ';
    }
  } else {
    std::cout << "NO";
  }
  return 0;
}