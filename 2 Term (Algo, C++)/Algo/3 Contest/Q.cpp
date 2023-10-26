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

bool BFS(Graph& graph, std::vector<int>& level, int start, int finish) {
  std::queue<int> queue;
  queue.emplace(start);
  while (!queue.empty()) {
    int begin = queue.front();
    queue.pop();
    for (const auto& neighbour : graph.values[begin]) {
      Edge edge = graph.edges[neighbour];
      if (level[edge.end] == 0 && edge.end != start && edge.volume > edge.flow) {
        level[edge.end] = level[begin] + 1;
        queue.emplace(edge.end);
      }
    }
  }
  return level[finish] != 0;
}

int ReverseFriend(const Graph& graph, const int& start, const int& finish) {
  for (auto& reverse_friend : graph.values[finish]) {
    if (graph.edges[reverse_friend].end == start && graph.edges[reverse_friend].begin == finish) {
      return reverse_friend;
    }
  }
  return -1;
}

int DFS(Graph& graph, std::vector<int>& level, std::vector<int>& parent, int start, int finish, int temp_flow) {
  if (start != finish && temp_flow != 0) {
    for (size_t i = parent[start]; i < graph.values[start].size(); ++i) {
      Edge& edge = graph.edges[graph.values[start][i]];
      if (level[edge.end] == level[start] + 1 && edge.flow < edge.volume) {
        int flow = DFS(graph, level, parent, edge.end, finish, std::min(temp_flow, edge.volume - edge.flow));
        if (flow <= 0) {
          continue;
        }
        edge.flow += flow;
        int reverse_friend = ReverseFriend(graph, start, edge.end);
        if (reverse_friend != -1) {
          graph.edges[reverse_friend].flow -= flow;
        }
        return flow;
      }
    }
    return 0;
  }
  return temp_flow;
}

int MaxFlow(Graph& graph, const int& start, const int& finish) {
  int ans = 0;
  std::vector<int> parent(graph.n + 1, 1);
  std::vector<int> level(graph.n + 1, 0);
  while (BFS(graph, level, start, finish)) {
    std::fill(parent.begin(), parent.end(), 0);
    int temp_flow = 1;
    while (temp_flow > 0) {
      temp_flow = DFS(graph, level, parent, start, finish, 1e9);
      if (temp_flow > 0) {
        ans += temp_flow;
      }
    }
    std::fill(level.begin(), level.end(), 0);
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