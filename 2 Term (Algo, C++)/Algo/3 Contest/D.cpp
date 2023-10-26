#include <iostream>
#include <vector>
#include <numeric>

int FindSet(int num, std::vector<int>& parent) {
  if (num == parent[num]) {
    return num;
  }
  return parent[num] = FindSet(parent[num], parent);
}

void Union(int x, int y, std::vector<int>& parent, std::vector<int>& size) {
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
}

struct Edge {
  int begin = 0;
  int end = 0;
  size_t weight = 0;
  Edge() = default;
  Edge(const int& begin, const int& end, const size_t& weight) : begin(begin), end(end), weight(weight) {
  }
};

size_t Krascal(const int& m, std::vector<int>& parent, std::vector<int>& size, std::vector<Edge>& pairs) {
  for (int i = 0; i < m; ++i) {
    int begin = 0;
    int end = 0;
    size_t weight = 0;
    std::cin >> begin >> end >> weight;
    Edge edge(begin, end, weight);
    pairs[i] = edge;
  }
  size_t weight = 0;
  for (int i = 0; i < m; ++i) {
    if (FindSet(pairs[i].begin, parent) != FindSet(pairs[i].end, parent)) {
      Union(pairs[i].begin, pairs[i].end, parent, size);
      weight += pairs[i].weight;
    }
  }
  return weight;
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
  std::cout << Krascal(m, parent, size, pairs);
  return 0;
}