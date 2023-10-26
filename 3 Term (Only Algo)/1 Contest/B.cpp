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

void MaxDiffrence(std::vector<int64_t>& values, std::vector<int64_t>& ans) {
  int size = static_cast<int>(values.size());
  int64_t max = values[size - 1];
  int64_t diff = max - values[size - 2];
  int l = size - 2;
  int r_temp = size - 1;
  int r = size - 1;
  for (int i = static_cast<int>(size - 2); i >= 0; --i) {
    if (max - values[i] > diff) {
      diff = max - values[i];
      r = r_temp;
      l = i;
    }
    if (values[i] > max) {
      max = values[i];
      r_temp = i;
    }
  }
  ans[0] = l + 1;
  ans[1] = r;
  ans[2] = diff;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  std::vector<int64_t> values(n + 1, 0);
  std::cin >> values;
  PrefixSum(values);
  std::vector<int64_t> ans(3);
  MaxDiffrence(values, ans);
  for (const auto& i : ans) {
    std::cout << i << ' ';
  }
  return 0;
}