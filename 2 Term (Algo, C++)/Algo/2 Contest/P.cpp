#include <iostream>
#include <vector>
#include <algorithm>

struct Graph {
  int n, m;
  std::vector<std::vector<std::pair<int, int>>> edges;
  Graph() : n(0), m(0), edges(0) {
  }
  friend std::istream& operator>>(std::istream&, Graph&);
};

std::istream& operator>>(std::istream& is, Graph& graph) {
  is >> graph.n >> graph.m;
  graph.edges.resize(graph.n + 1);
  for (int i = 1; i < graph.m + 1; ++i) {
    int begin, finish;
    is >> begin >> finish;
    graph.edges[begin].emplace_back(std::make_pair(finish, i));
    graph.edges[finish].emplace_back(std::make_pair(begin, i));
  }
  return is;
}

void DfsVisit(const Graph& graph, int& time, std::vector<int>& color, const int& v, const int& parent,
              std::vector<int>& bridges, std::vector<int>& time_in, std::vector<int>& time_out) {
  color[v] = 1;
  time_in[v] = time_out[v] = ++time;
  for (const auto u : graph.edges[v]) {
    if (u.first != parent) {
      if (color[u.first] == 1) {
        time_out[v] = std::min(time_out[v], time_in[u.first]);
      }
      if (color[u.first] == 0) {
        DfsVisit(graph, time, color, u.first, v, bridges, time_in, time_out);
        time_out[v] = std::min(time_out[u.first], time_out[v]);
        if (time_in[v] < time_out[u.first]) {
          int cnt = 0;
          for (const auto k : graph.edges[v]) {
            if (k.first == u.first) {
              ++cnt;
            }
          }
          if (cnt == 1) {
            bridges.emplace_back(u.second);
          }
        }
      }
    }
  }
  color[v] = 2;
}

void Dfs(const Graph& graph, int& time, std::vector<int>& bridges, std::vector<int>& time_in,
         std::vector<int>& time_out) {
  std::vector<int> color(graph.n + 1, 0);
  for (int i = 1; i < graph.n + 1; ++i) {
    if (color[i] == 0) {
      DfsVisit(graph, time, color, i, 0, bridges, time_in, time_out);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Graph graph;
  std::cin >> graph;
  int time = 0;
  std::vector<int> bridges;
  std::vector<int> time_in(graph.n + 1, 0), time_out(graph.n + 1, 0);
  Dfs(graph, time, bridges, time_in, time_out);
  std::cout << bridges.size() << '\n';
  std::sort(bridges.begin(), bridges.end());
  for (const auto v : bridges) {
    std::cout << v << '\n';
  }
  return 0;
}