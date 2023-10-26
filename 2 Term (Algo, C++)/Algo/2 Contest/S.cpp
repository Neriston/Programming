#include <iostream>
#include <vector>
#include <algorithm>

struct Graph {
  int n, m;
  std::vector<std::vector<std::pair<int, int>>> edges;
  std::vector<std::pair<int, int>> edg;
  std::vector<int> degree;
  Graph() : n(0), m(0), edges(0), edg(0), degree(0) {
  }
  friend std::istream& operator>>(std::istream&, Graph&);
};

std::istream& operator>>(std::istream& is, Graph& graph) {
  is >> graph.n >> graph.m;
  graph.edges.resize(graph.n + 1);
  graph.degree.resize(graph.n + 1);
  for (int i = 1; i < graph.m + 1; ++i) {
    int begin, finish;
    is >> begin >> finish;
    graph.edges[begin].emplace_back(std::make_pair(finish, i));
    graph.edges[finish].emplace_back(std::make_pair(begin, i));
    graph.edg.emplace_back(std::make_pair(begin, finish));
    ++graph.degree[begin];
    ++graph.degree[finish];
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

int Cnt(const Graph& graph) {
  int cnt = 0;
  for (size_t i = 1; i < graph.edges.size(); ++i) {
    if (graph.edges[i].size() <= 1) {
      cnt += 2 - graph.edges[i].size();
    }
  }
  return cnt % 2 == 0 ? cnt / 2 : cnt / 2 + 1;
}

int OtherCnt(const Graph& graph, const std::vector<int>& bridges) {
  int cnt = 0;
  for (size_t i = 0; i < bridges.size(); ++i) {
    auto temp = graph.edg[bridges[i] - 1];
    if (graph.degree[temp.first] >= 3 && graph.degree[temp.second] >= 3) {
      ++cnt;
    }
  }
  return cnt;
}

int main() {
  Graph graph;
  std::cin >> graph;
  int time = 0;
  std::vector<int> bridges;
  std::vector<int> time_in(graph.n + 1, 0), time_out(graph.n + 1, 0);
  Dfs(graph, time, bridges, time_in, time_out);
  int cnt1 = Cnt(graph);
  int cnt2 = OtherCnt(graph, bridges);
  if (cnt1 >= 2 && cnt2 >= 1) {
    std::cout << cnt1;
  } else if (cnt2 >= 1) {
    ++cnt1;
    std::cout << cnt1;
  } else {
    std::cout << cnt1;
  }
  return 0;
}