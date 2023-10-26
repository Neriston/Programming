#include <iostream>
#include <vector>
#include <cmath>

std::istream& operator>>(std::istream& is, std::vector<int>& vector) {
  for (size_t i = 1; i < vector.size(); ++i) {
    is >> vector[i];
  }
  return is;
}

int RMQ(std::vector<std::vector<int>>& sparse_table, int l, int r) {
  const int bits = 31;
  int k = bits - __builtin_clz(r - l + 1);
  int pow_k = 1 << k;
  return std::min(sparse_table[k][l - 1], sparse_table[k][r - pow_k]);
}

void BuildST(std::vector<int>& series, std::vector<std::vector<int>>& sparse_table) {
  for (size_t i = 1; i < series.size(); ++i) {
    sparse_table[0].emplace_back(series[i]);
  }
  const int bits = 31;
  for (int k = 1; k <= bits - __builtin_clz(series.size() - 1); ++k) {
    int pow_k = 1 << (k - 1);
    for (size_t i = 0; i < sparse_table[k - 1].size() - pow_k; ++i) {
      sparse_table[k].emplace_back(std::min(sparse_table[k - 1][i], sparse_table[k - 1][i + pow_k]));
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int q = 0;
  std::cin >> n >> q;
  std::vector<int> series(n + 1, 0);
  std::cin >> series;
  const int bits = 31;
  int k = bits - __builtin_clz(n);
  std::vector<std::vector<int>> sparse_table(k + 1);
  BuildST(series, sparse_table);
  for (int i = 0; i < q; ++i) {
    int l = 0;
    int r = 0;
    std::cin >> l >> r;
    std::cout << RMQ(sparse_table, l, r) << '\n';
  }
  return 0;
}