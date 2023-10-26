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
  is >> graph.n >> graph.m;
  graph.edges.resize(graph.n + 1);
  for (int i = 0; i < graph.m; ++i) {
    int begin, finish;
    is >> begin >> finish;
    graph.edges[begin].push_back(finish);
    graph.edges[finish].push_back(begin);
  }
  return is;
}

bool Color(const Graph& graph) {
  enum Color { white, black, red };
  std::vector<Color> colors(graph.n + 1);
  std::fill(colors.begin(), colors.end(), white);
  for (size_t i = 1; i < graph.edges.size(); ++i) {
    if (colors[i] == white) {
      colors[i] = black;
      std::queue<int> queue;
      queue.push(i);
      while (!(queue.empty())) {
        int vertex = queue.front();
        queue.pop();
        for (auto neighbour : graph.edges[vertex]) {
          if (colors[neighbour] == white) {
            if (colors[vertex] == black) {
              colors[neighbour] = red;
            } else {
              colors[neighbour] = black;
            }
            queue.push(neighbour);
          } else if (colors[vertex] == colors[neighbour]) {
            return false;
          }
        }
      }
    }
  }
  return true;
}

int main() {
  Graph graph;
  std::cin >> graph;
  if (Color(graph)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  return 0;
}