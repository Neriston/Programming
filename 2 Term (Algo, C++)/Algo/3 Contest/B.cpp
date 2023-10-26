#include <iostream>
#include <vector>
#include <numeric>

int FindSet(int num, std::vector<int>& parent) {
  if (num == parent[num]) {
    return num;
  }
  return parent[num] = FindSet(parent[num], parent);
}

void Union(int x, int y, std::vector<int>& parent, std::vector<int>& size, std::vector<int>& weights,
           const int weight) {
  x = FindSet(x, parent);
  y = FindSet(y, parent);
  if (x == y) {
    weights[x] += weight;
  } else {
    if (size[x] < size[y]) {
      parent[x] = y;
      weights[y] += weights[x] + weight;
    } else if (size[y] < size[x]) {
      parent[y] = x;
      weights[x] += weights[y] + weight;
    } else {
      parent[x] = y;
      weights[y] += weights[x] + weight;
      ++size[y];
    }
  }
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
  std::vector<int> weights(n + 1, 0);
  for (int i = 0; i < m; ++i) {
    int operation = 0;
    std::cin >> operation;
    if (operation == 1) {
      int begin = 0;
      int end = 0;
      int weight = 0;
      std::cin >> begin >> end >> weight;
      Union(begin, end, parent, size, weights, weight);
    } else if (operation == 2) {
      int vertex = 0;
      std::cin >> vertex;
      int root = FindSet(vertex, parent);
      std::cout << weights[root] << '\n';
    }
  }
  return 0;
}