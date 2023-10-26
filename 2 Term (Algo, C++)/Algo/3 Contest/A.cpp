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

int Islands(int n, const int m, std::vector<int>& parent, std::vector<int>& size) {
  for (int i = 0; i < m; ++i) {
    int begin = 0;
    int end = 0;
    std::cin >> begin >> end;
    if (FindSet(begin, parent) != FindSet(end, parent)) {
      Union(begin, end, parent, size);
      --n;
      if (n == 1) {
        return i + 1;
      }
    }
  }
  return m;
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<int> parent(n);
  std::vector<int> size(n, 1);
  std::iota(parent.begin(), parent.end(), 0);
  std::cout << Islands(n, m, parent, size);
  return 0;
}