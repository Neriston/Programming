
#include <iostream>
#include <vector>
#include <deque>

using std::vector;

struct Vert {
  int num, val;
  Vert() : num(0), val(0) {
  }
  Vert(const int& num, const int& val) : num(num), val(val) {
  }
};

struct Graph {
  int n, m;
  vector<vector<Vert>> edges;
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
    graph.edges[begin].emplace_back(Vert(finish, 0));
    bool flag = true;
    for (const auto v : graph.edges[finish]) {
      if (v.num == begin && v.val == 0) {
        flag = false;
        break;
      }
    }
    if (flag) {
      graph.edges[finish].emplace_back(Vert(begin, 1));
    }
  }
  return is;
}

int Dist(const int& begin, const int& end, const Graph& graph) {
  std::vector<int> dist(graph.n + 1, 10e8);
  dist[begin] = 0;
  std::deque<int> deque;
  deque.push_front(begin);
  while (!(deque.empty())) {
    int vertex = deque.front();
    deque.pop_front();
    for (const auto neighbour : graph.edges[vertex]) {
      if (neighbour.val == 0) {
        if ((dist[vertex] < dist[neighbour.num])) {
          deque.push_front(neighbour.num);
          dist[neighbour.num] = dist[vertex];
        }
      } else if (neighbour.val == 1) {
        if (dist[vertex] + 1 < dist[neighbour.num]) {
          deque.push_back(neighbour.num);
          dist[neighbour.num] = dist[vertex] + 1;
        }
      }
    }
  }
  if (dist[end] == 10e8) {
    return -1;
  }
  return dist[end];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  Graph graph;
  std::cin >> graph;
  int k;
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    int begin, end;
    std::cin >> begin >> end;
    std::cout << Dist(begin, end, graph) << '\n';
  }
}