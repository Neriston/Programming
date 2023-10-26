#include <iostream>
#include <vector>
#include <numeric>
#include <queue>

int FindSet(int num, std::vector<int>& parent) {
  if (num == parent[num]) {
    return num;
  }
  return parent[num] = FindSet(parent[num], parent);
}

void Union(int x, int y, std::vector<int>& parent, std::vector<int>& size, int& set_count) {
  x = FindSet(x, parent);
  y = FindSet(y, parent);
  if (x != y) {
    if (size[x] < size[y]) {
      parent[x] = y;
    } else if (size[y] < size[x]) {
      parent[y] = x;
    } else {
      parent[x] = y;
      ++size[y];
    }
  }
  --set_count;
}

struct Edge {
  int begin = 0;
  int end = 0;
  size_t weight = 0;
  Edge() = default;
  Edge(const int& begin, const int& end, const size_t& weight) : begin(begin), end(end), weight(weight) {
  }
  bool operator>(const Edge& other) const {
    return weight > other.weight;
  }
};

size_t Boruvka(std::vector<int>& parent, std::vector<int>& size, std::vector<Edge>& pairs) {
  size_t min_weight = 0;
  int set_count = static_cast<int>(size.size() - 1);
  while (set_count > 1) {
    std::vector<Edge> min_edges(parent.size(), Edge(0, 0, 1e9));
    for (const auto& edges : pairs) {
      int component_start = FindSet(edges.begin, parent);
      int component_end = FindSet(edges.end, parent);
      if (component_start != component_end) {
        if (edges.weight < min_edges[component_start].weight) {
          min_edges[component_start] = {edges.begin, edges.end, edges.weight};
        }
        if (edges.weight < min_edges[component_end].weight) {
          min_edges[component_end] = {edges.begin, edges.end, edges.weight};
        }
      }
    }
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> prior_queue;
    for (const auto& edge : min_edges) {
      if (edge.begin != 0) {
        prior_queue.emplace(edge);
      }
    }
    while (!prior_queue.empty()) {
      Edge edge = prior_queue.top();
      prior_queue.pop();
      int component_start = FindSet(edge.begin, parent);
      int component_end = FindSet(edge.end, parent);
      if (component_start != component_end) {
        Union(component_start, component_end, parent, size, set_count);
        min_weight += edge.weight;
        if (set_count <= 1) {
          break;
        }
      }
    }
  }
  return min_weight;
}

std::istream& operator>>(std::istream& is, std::vector<Edge>& pairs) {
  for (size_t i = 0; i < pairs.size(); ++i) {
    int begin = 0;
    int end = 0;
    size_t weight = 0;
    is >> begin >> end >> weight;
    pairs[i] = {begin, end, weight};
  }
  return is;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<int> parent(n + 1);
  std::iota(parent.begin(), parent.end(), 0);
  std::vector<int> size(n + 1, 1);
  std::vector<Edge> pairs(m);
  std::cin >> pairs;
  std::cout << Boruvka(parent, size, pairs);
  return 0;
}