#include <iostream>
#include <vector>
#include <algorithm>

void CalcZFunc(const std::vector<int>& string, std::vector<int>& z_func) {
  z_func[0] = 0;
  int left = 0;
  int right = 0;
  for (int i = 1; i < static_cast<int>(string.size()); ++i) {
    if (i < right) {
      z_func[i] = z_func[i - left] > right - i ? right - i : z_func[i - left];
    }
    while (i + z_func[i] < static_cast<int>(string.size()) && string[z_func[i]] == string[z_func[i] + i]) {
      ++z_func[i];
    }
    (i + z_func[i] > right) ? (right = i + z_func[i], left = i) : 0;
  }
}

std::istream& operator>>(std::istream& is, std::vector<int>& string) {
  for (size_t i = 0; i < string.size() / 2; ++i) {
    is >> string[i];
    string[string.size() - i - 1] = string[i];
  }
  return is;
}

void MirrorString(const std::vector<int>& z_func, const int& n) {
  int quantity_before_mirror = (n + 1) / 2;
  int start_pos = n % 2;
  while (start_pos < n - 1) {
    int diff = quantity_before_mirror - start_pos;
    if (z_func[n + start_pos] >= 2 * diff) {  // Also we can change 2 * diff to 1 * diff, because size of common block need bo be more diff (and it equals 2 * diff)
      std::cout << quantity_before_mirror << ' ';
    }
    ++quantity_before_mirror;
    start_pos += 2;
  }
  std::cout << n;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<int> str_and_reverse_str(2 * n);
  std::cin >> str_and_reverse_str;
  std::vector<int> z_func(2 * n, 0);
  CalcZFunc(str_and_reverse_str, z_func);
  MirrorString(z_func, n);
  return 0;
}