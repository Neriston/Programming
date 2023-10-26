#include <iostream>
#include <vector>

int Gcd(int first, int second) {
  while (first != 0 && second != 0) {
    if (first > second) {
      first %= second;
    } else {
      second %= first;
    }
  }
  if (first == 0) {
    return second;
  }
  return first;
}

void BuildSegTree(std::vector<int>& seg_tree, const std::vector<int>& series, int size_series) {
  for (int i = size_series; i < static_cast<int>(seg_tree.size()); ++i) {
    seg_tree[i] = series[i - size_series];
  }
  for (int i = size_series - 1; i > 0; --i) {
    seg_tree[i] = Gcd(seg_tree[2 * i], seg_tree[2 * i + 1]);
  }
}

int GcdQuery(const std::vector<int>& seg_tree, int l, int r) {
  int gcd = seg_tree[l];
  for (int i = l; i <= r; i /= 2, r /= 2) {
    if (i % 2 == 1) {
      gcd = Gcd(gcd, seg_tree[i]);
      ++i;
    }
    if (r % 2 == 0) {
      gcd = Gcd(gcd, seg_tree[r]);
      --r;
    }
  }
  return gcd;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int k = 0;
  std::cin >> n;
  int pow = 1 << (32 - __builtin_clz(n));
  std::vector<int> series(pow, 0);
  for (int i = 0; i < n; ++i) {
    std::cin >> series[i];
  }
  for (int i = n; i < pow; ++i) {
    series[i] = series[n - 1];
  }
  std::cin >> k;
  std::vector<int> seg_tree(2 * pow, 0);
  BuildSegTree(seg_tree, series, pow);
  for (int i = 0; i < k; ++i) {
    int l = 0;
    int r = 0;
    std::cin >> l >> r;
    std::cout << GcdQuery(seg_tree, pow + l - 1, pow + r - 1) << '\n';
  }
  return 0;
}