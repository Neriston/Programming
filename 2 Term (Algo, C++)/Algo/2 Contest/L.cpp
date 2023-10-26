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
  }
  return is;
}

void TopSortDfs(const Graph& graph, const int& v, std::vector<int>& color, std::vector<int>& top_sorted) {
  color[v] = 1;
  for (const auto u : graph.edges[v]) {
    if (color[u] == 0) {
      TopSortDfs(graph, u, color, top_sorted);
    }
  }
  color[v] = 2;
  top_sorted.emplace_back(v);
}

void TopSort(const Graph& graph, std::vector<int>& top_sorted) {
  std::vector<int> color(graph.n + 1, 0);
  for (int i = 1; i < graph.n + 1; ++i) {
    if (color[i] == 0) {
      TopSortDfs(graph, i, color, top_sorted);
    }
  }
}

void DfsVisit(const Graph& graph, const int& v, std::vector<int>& color, std::vector<int>& components, int& comp) {
  color[v] = 1;
  components[v] = comp;
  for (const auto u : graph.edges[v]) {
    if (color[u] == 0) {
      DfsVisit(graph, u, color, components, comp);
    }
  }
  color[v] = 2;
}

void DFS(const Graph& graph, const std::vector<int>& order, std::vector<int>& components, int& comp) {
  std::vector<int> color(graph.n + 1, 0);
  for (auto i = static_cast<int>(order.size() - 1); i >= 0; --i) {
    if (color[order[i]] == 0) {
      DfsVisit(graph, order[i], color, components, comp);
      ++comp;
    }
  }
}

int main() {
  Graph graph, trans_graph;
  std::cin >> graph;
  trans_graph.edges.resize(graph.edges.size());
  trans_graph.n = graph.n + 1;
  for (size_t i = 0; i < graph.edges.size(); ++i) {
    for (size_t j = 0; j < graph.edges[i].size(); ++j) {
      trans_graph.edges[graph.edges[i][j]].emplace_back(i);
    }
  }
  std::vector<int> top_sorted, components(graph.n + 1);
  TopSort(graph, top_sorted);
  int comp = 1;
  DFS(trans_graph, top_sorted, components, comp);
  std::cout << comp - 1 << '\n';
  for (size_t i = 1; i < components.size(); ++i) {
    std::cout << components[i] << ' ';
  }
  return 0;
}