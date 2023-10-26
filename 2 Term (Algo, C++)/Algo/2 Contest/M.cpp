#include <iostream>
#include <vector>
#include <algorithm>

struct Graph {
  int n, m;
  std::vector<std::vector<int>> edges;
  Graph() : n(0), m(0), edges(0) {
  }
  friend std::istream& operator>>(std::istream&, Graph&);
};

std::istream& operator>>(std::istream& is, Graph& graph) {
  is >> graph.n >> graph.m;
  graph.edges.resize(graph.n + 1);
  for (int i = 0; i < graph.m; ++i) {
    int begin, finish;
    is >> begin >> finish;
    graph.edges[begin].emplace_back(finish);
    graph.edges[finish].emplace_back(begin);
  }
  return is;
}

void DfsVisit(const Graph& graph, int& time, std::vector<int>& color, const int& v, std::vector<int>& articulation,
              std::vector<int>& time_in, std::vector<int>& time_out, bool flag = true) {
  color[v] = 1;
  time_in[v] = time_out[v] = ++time;
  int n = 0;
  for (const auto u : graph.edges[v]) {
    if (color[u] == 1) {
      time_out[v] = std::min(time_out[v], time_in[u]);
    }
    if (color[u] == 0) {
      ++n;
      DfsVisit(graph, time, color, u, articulation, time_in, time_out, false);
      time_out[v] = std::min(time_out[u], time_out[v]);
      if (!flag && time_in[v] <= time_out[u]) {
        articulation[v] = 1;
      }
    }
  }
  if (flag && n > 1) {
    articulation[v] = 1;
  }
  color[v] = 2;
}

void Dfs(const Graph& graph, int& time, std::vector<int>& articulation, std::vector<int>& time_in,
         std::vector<int>& time_out) {
  std::vector<int> color(graph.n + 1, 0);
  for (int i = 1; i < graph.n + 1; ++i) {
    DfsVisit(graph, time, color, i, articulation, time_in, time_out);
  }
}

int main() {
  Graph graph;
  std::cin >> graph;
  int time = 0;
  std::vector<int> articulation(graph.n + 1), time_in(graph.n + 1, 0), time_out(graph.n + 1, 0);
  Dfs(graph, time, articulation, time_in, time_out);
  std::vector<int> ans;
  for (int i = 1; i < graph.n + 1; ++i) {
    if (articulation[i] != 0) {
      ans.emplace_back(i);
    }
  }
  std::sort(ans.begin(), ans.end());
  std::cout << ans.size() << '\n';
  for (size_t i = 0; i < ans.size(); ++i) {
    std::cout << ans[i] << '\n';
  }
  return 0;
}