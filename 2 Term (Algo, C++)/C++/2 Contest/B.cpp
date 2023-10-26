#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  int n;
  std::cin >> n;
  std::vector<int64_t> table(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> table[i];
  }
  int m;
  std::cin >> m;
  std::pair<std::vector<int64_t>::iterator, std::vector<int64_t>::iterator> p;
  for (int i = 0; i < m; ++i) {
    int color;
    std::cin >> color;
    p = std::equal_range(table.begin(), table.end(), color);
    std::cout << p.second - p.first << '\n';
  }
  return 0;
}