#include <iostream>
#include <vector>
#include <unordered_map>

enum Color { white, black, grey };

struct Graph {
  int n, m;
  std::vector<std::vector<int>> edges;
  Graph() : n(0), m(0), edges(0) {
  }
  Graph(const int& n, const int& m) : n(n), m(m), edges(n + 1) {
  }
  friend std::istream& operator>>(std::istream&, Graph&);
};

bool HasCycleDfs(const Graph& graph, const int& vertex, std::vector<Color>& color, int parent = -1) {
  color[vertex] = grey;  // 1 is gray
  for (const auto neighbour : graph.edges[vertex]) {
    if (neighbour != parent) {
      if (color[neighbour] == grey || (color[neighbour] == white && HasCycleDfs(graph, neighbour, color, vertex))) {
        return true;
      }
    }
  }
  color[vertex] = black;  // 2 is black
  return false;
}

bool HasCycle(const Graph& graph, std::vector<Color>& color) {
  return HasCycleDfs(graph, 1, color);
}

bool Ans(const Graph& graph, const std::vector<int>& atoms) {
  bool flag = false;
  for (size_t i = 1; i < graph.edges.size(); ++i) {
    if (atoms[i] == 2) {
      if (graph.edges[i].size() > 1 || (graph.edges[i].size() == 1 && atoms[graph.edges[i][0]] == 2)) {
        flag = true;
      }
    } else {
      if (graph.edges[i].size() != 4) {
        flag = true;
      }
    }
    if (flag) {
      break;
    }
  }
  if (!flag) {
    std::vector<Color> color(graph.n + 1, white);
    flag = HasCycle(graph, color);
    if (!flag) {
      for (size_t i = 1; i < color.size(); ++i) {
        if (color[i] == 0) {
          flag = true;
          break;
        }
      }
    }
  }
  return flag;
}

void InitAtoms(std::vector<int>& atoms) {
  for (size_t i = 1; i < atoms.size(); ++i) {
    char atom;
    std::cin >> atom;
    if (atom == 'C') {
      atoms[i] = 1;  // C
    } else {
      atoms[i] = 2;  // H
    }
  }
}

bool InitGraph(Graph& graph) {
  std::vector<std::unordered_map<int, int>> map(graph.n + 1);
  for (int i = 0; i < graph.m; ++i) {
    int begin, finish;
    std::cin >> begin >> finish;
    if (map[begin][finish] == 0 && map[finish][begin] == 0) {
      ++map[begin][finish];
      ++map[finish][begin];
    } else {
      std::cout << "NO\n";
      return false;
    }
    graph.edges[begin].emplace_back(finish);
    graph.edges[finish].emplace_back(begin);
  }
  return true;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> atoms(n + 1, 0);
  InitAtoms(atoms);
  if (m == 0) {
    std::cout << "NO\n";
    return 0;
  }
  Graph graph(n, m);
  if (!InitGraph(graph)) {
    return 0;
  }
  if (Ans(graph, atoms)) {
    std::cout << "NO\n";
  } else {
    std::cout << "YES\n";
  }
  return 0;
}