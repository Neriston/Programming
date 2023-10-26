#include <iostream>
#include <vector>
#include <queue>

using std::vector;

struct Graph {
  int n;
  vector<vector<int>> edges;
  explicit Graph(const int&);
};

Graph::Graph(const int& cnt) : n(cnt) {
  edges.resize(10000);
  for (int i = 1111; i < 10000; ++i) {
    if (i % 10 != 0 && (i % 100 - i % 10) != 0 && (i % 1000 - i % 100) != 0) {
      if (i / 1000 != 9) {
        edges[i].push_back(i + 1000);
      }
      if (i % 10 != 1) {
        edges[i].push_back(i - 1);
      }
      int temp = (i % 10) * 1000 + (i / 1000) * 100 + (i % 1000 - i % 100) / 10 + (i % 100 - i % 10) / 10;
      edges[i].push_back(temp);
      temp = (i / 1000) + (i % 10) * 10 + (i % 100 - i % 10) * 10 + (i % 1000 - i % 100) * 10;
      edges[i].push_back(temp);
    }
  }
}

int64_t Dist(const Graph& graph, const int& begin, const int& end, std::vector<int>& parent) {
  std::vector<int64_t> dist(10000);
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
        parent[neighbour] = vertex;
      }
    }
  }
  return dist[end];
}

int main() {
  int begin, finish;
  std::cin >> begin >> finish;
  const int cnt_of_numbers = 6561;
  Graph graph(cnt_of_numbers);
  std::vector<int> parent(10000);
  std::cout << Dist(graph, begin, finish, parent) + 1 << '\n';
  std::vector<int> temp_vector;
  int temp = finish;
  while (temp != begin) {
    temp_vector.push_back(temp);
    temp = parent[temp];
  }
  temp_vector.push_back(begin);
  for (int i = static_cast<int>(temp_vector.size()) - 1; i >= 0; --i) {
    std::cout << temp_vector[i] << '\n';
  }
}