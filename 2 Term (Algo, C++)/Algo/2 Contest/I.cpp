#include <iostream>
#include <vector>

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

void DfsVisit(const Graph& graph, std::vector<int>& color, const int& v, int& num, std::vector<int>& table) {
  color[v] = 1;
  ++num;
  for (const auto u : graph.edges[v]) {
    if (color[u] == 0) {
      table.emplace_back(u);
      DfsVisit(graph, color, u, num, table);
    }
  }
  color[v] = 2;
}

int64_t DFS(const Graph& graph, std::vector<int>& number, std::vector<std::vector<int>>& table) {
  int64_t cnt = 0;
  std::vector<int> color(graph.n + 1, 0);
  for (int i = 1; i < graph.n + 1; ++i) {
    if (color[i] == 0) {
      table.emplace_back(std::vector<int>(1, i));
      int num = 0;
      DfsVisit(graph, color, i, num, table[table.size() - 1]);
      number.emplace_back(num);
      ++cnt;
    }
  }
  return cnt;
}

int main() {
  Graph graph;
  std::cin >> graph;
  std::vector<int> number;
  std::vector<std::vector<int>> table;
  int count = DFS(graph, number, table);
  std::cout << count << '\n';
  for (auto i = 0; i < count; ++i) {
    std::cout << number[i] << '\n';
    for (const auto v : table[i]) {
      std::cout << v << ' ';
    }
    std::cout << '\n';
  }
  return 0;
}