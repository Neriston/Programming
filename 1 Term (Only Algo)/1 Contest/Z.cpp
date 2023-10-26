#include <iostream>

int Min(int a, int b) {
  if (a > b) {
    return b;
  }
  return a;
}

int Max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

int main() {
  int64_t n;
  int64_t m;
  int64_t k;
  std::cin >> n >> m >> k;
  auto ans = new int64_t[k]{};
  int64_t gor = int(n / k) * m;
  int64_t vert = int(m / k) * (n % k);
  int new_gor = n % k;
  int new_vert = m % k;
  int cnt_diag = new_gor + new_vert - 1;
  int max = Max(new_gor, new_vert);
  int min = Min(new_gor, new_vert);
  int l = 1;
  for (int64_t i = 0; i < cnt_diag; ++i) {
    int64_t cnt;
    if (i < min) {
      cnt = i + 1;
    } else if (i < max) {
      cnt = min;
    } else {
      cnt = min - l;
      ++l;
    }
    ans[i % k] += cnt;
  }
  for (int64_t i = 0; i < k; ++i) {
    std::cout << ans[i] + vert + gor << ' ';
  }
  delete[] ans;
  return 0;
}