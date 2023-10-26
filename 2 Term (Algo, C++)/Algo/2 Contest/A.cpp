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
  graph.edges.resize(graph.n + 1);
  for (int i = 0; i < graph.m; ++i) {
    int begin, finish;
    is >> begin >> finish;
    graph.edges[begin].push_back(finish);
    graph.edges[finish].push_back(begin);
  }
  return is;
}

int64_t Dist(const Graph& graph, const int& begin, const int& end, std::vector<int>& parent) {
  std::vector<int64_t> dist(graph.n + 1);
  std::fill(dist.begin(), dist.end(), 10e9);
  dist[begin] = 0;
  std::queue<int> queue;
  queue.push(begin);
  while (!(queue.empty())) {
    int vertex = queue.front();
    queue.pop();
    for (const auto neigbour : graph.edges[vertex]) {
      if (dist[neigbour] == 10e9) {
        dist[neigbour] = dist[vertex] + 1;
        queue.push(neigbour);
        parent[neigbour] = vertex;
      }
    }
  }
  if (dist[end] == 10e9) {
    return -1;
  }
  return dist[end];
}

void Out(const Graph& graph, const int& begin, const int& end, std::vector<int>& parent) {
  int64_t dist = Dist(graph, begin, end, parent);
  if (dist != -1) {
    std::cout << dist << '\n';
    int temp = end;
    std::vector<int> temp_vec;
    while (temp != begin) {
      temp_vec.push_back(temp);
      temp = parent[temp];
    }
    temp_vec.push_back(temp);
    for (int i = static_cast<int>(temp_vec.size()) - 1; i >= 0; --i) {
      std::cout << temp_vec[i] << ' ';
    }
  } else {
    std::cout << -1;
  }
}

int main() {
  Graph graph;
  int begin, end;
  std::cin >> graph.n >> graph.m >> begin >> end >> graph;
  std::vector<int> parent(graph.n + 1);
  Out(graph, begin, end, parent);
}