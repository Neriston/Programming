#include <iostream>
#include <vector>
#include <queue>

using std::vector;

struct Graph {
  int n, m;
  vector<vector<int>> edges;
  Graph();
  explicit Graph(const int&, const int&);
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph() : n(0), m(0), edges(0) {
}

Graph::Graph(const int& n, const int& m) : n(n), m(m) {
  edges.resize(n + 1);
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  graph.edges.resize(graph.n + 100000);
  for (int i = 0; i < graph.m; ++i) {
    int begin, finish, val;
    is >> begin >> finish >> val;
    int cnt = graph.n + 1;
    while (val > 1) {
      ++graph.n;
      graph.edges[begin].emplace_back(cnt);
      begin = cnt;
      ++cnt;
      --val;
    }
    graph.edges[begin].emplace_back(finish);
  }
  return is;
}

int64_t Dist(const Graph& graph, const int& begin, const int& end) {
  std::vector<int64_t> dist(graph.n + 1);
  std::fill(dist.begin(), dist.end(), 10e9);
  dist[begin] = 0;
  std::queue<int> queue;
  queue.push(begin);
  while (!(queue.empty())) {
    int vertex = queue.front();
    queue.pop();
    for (const auto neighbour : graph.edges[vertex]) {
      if (dist[neighbour] == 10e9) {
        dist[neighbour] = dist[vertex] + 1;
        queue.push(neighbour);
      }
    }
  }
  if (dist[end] == 10e9) {
    return -1;
  }
  return dist[end];
}

void Out(const Graph& graph, const int& begin, const int& end) {
  int64_t dist = Dist(graph, begin, end);
  if (dist != -1) {
    std::cout << dist << '\n';
  } else {
    std::cout << -1;
  }
}

int main() {
  Graph graph;
  int begin, end;
  std::cin >> graph.n >> graph.m >> begin >> end >> graph;
  Out(graph, begin, end);
  return 0;
}