#include <iostream>
#include <vector>

void PrefixSum(std::vector<int64_t>& values) {
  for (size_t i = 2; i < values.size(); ++i) {
    values[i] += values[i - 1];
  }
}

std::istream& operator>>(std::istream& is, std::vector<int64_t>& vector) {
  for (size_t i = 1; i < vector.size(); ++i) {
    is >> vector[i];
  }
  return is;
}

std::istream& operator>>(std::istream& is, std::vector<std::pair<int64_t, int64_t>>& vector) {
  for (size_t i = 0; i < vector.size(); ++i) {
    int64_t l = 0;
    int64_t r = 0;
    is >> l >> r;
    vector[i] = {l, r};
  }
  return is;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  int64_t k = 0;
  std::cin >> n;
  std::vector<int64_t> values(n + 1);
  std::cin >> values;
  std::cin >> k;
  std::vector<std::pair<int64_t, int64_t>> query(k);
  std::cin >> query;
  PrefixSum(values);
  for (size_t i = 0; i < query.size(); ++i) {
    std::cout << values[query[i].second] - values[query[i].first - 1] << ' ';
  }
  return 0;
}