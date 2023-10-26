#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

struct Edge {
  int begin = 0;
  int end = 0;
  int volume = 0;
  int flow = 0;
  Edge() = default;
  Edge(const int& begin, const int& end, const int& volume) : begin(begin), end(end), volume(volume) {
  }
};

struct Graph {
  int n = 0;
  int m = 0;
  std::vector<Edge> edges;
  std::vector<std::vector<int>> values;
  Graph() = default;
  Graph(const int& n, const int& m) : n(n), m(m) {
    values.resize(n + 1);
    edges.resize(1);
  }
  friend std::istream& operator>>(std::istream&, Graph&);
};

std::istream& operator>>(std::istream& is, Graph& graph) {
  for (int i = 0; i < graph.m; ++i) {
    int begin = 0;
    int end = 0;
    int volume = 0;
    is >> begin >> end >> volume;
    graph.edges.emplace_back(begin, end, volume);
    graph.edges.emplace_back(end, begin, 0);
    graph.values[begin].emplace_back(graph.edges.size() - 2);
    graph.values[end].emplace_back(graph.edges.size() - 1);
  }
  return is;
}

bool DFS(Graph& graph, std::vector<int>& parent, int start, int finish) {
  std::queue<int> queue;
  queue.emplace(start);
  while (!queue.empty()) {
    int begin = queue.front();
    queue.pop();
    for (const auto& neighbour : graph.values[begin]) {
      Edge edge = graph.edges[neighbour];
      if (parent[edge.end] == 0 && edge.end != start && edge.volume > edge.flow) {
        parent[edge.end] = neighbour;
        queue.emplace(edge.end);
        if (edge.end != finish) {
          continue;
        }
        return true;
      }
    }
  }
  return false;
}

int MaxFlow(Graph& graph, const int& start, const int& finish) {
  int ans = 0;
  std::vector<int> parent(graph.n + 1, 0);
  while (DFS(graph, parent, start, finish)) {
    int temp_flow = 1e9;
    int temp_finish = finish;
    while (temp_finish != start) {
      Edge edge = graph.edges[parent[temp_finish]];
      temp_flow = std::min(temp_flow, edge.volume - edge.flow);
      temp_finish = edge.begin;
    }
    temp_finish = finish;
    while (temp_finish != start) {
      graph.edges[parent[temp_finish]].flow += temp_flow;
      graph.edges[parent[temp_finish] + 1].flow -= temp_flow;
      temp_finish = graph.edges[parent[temp_finish]].begin;
    }
    ans += temp_flow;
    std::fill(parent.begin(), parent.end(), 0);
  }
  return ans;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  int start = 1;
  int finish = n;
  Graph graph(n, m);
  std::cin >> graph;
  std::cout << MaxFlow(graph, start, finish);
  return 0;
}