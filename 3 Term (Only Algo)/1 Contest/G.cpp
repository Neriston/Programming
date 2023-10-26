#include <iostream>
#include <vector>

using Pair = std::pair<int, int>;

Pair Union(const Pair& p1, const Pair& p2) {
  if (p1.first != p2.first) {
    return p1.first > p2.first ? p1 : p2;
  }
  return {p1.first, p1.second + p2.second};
}

void BuildSegTree(std::vector<Pair>& seg_tree, const std::vector<int>& series, int size_series) {
  for (int i = size_series; i < static_cast<int>(seg_tree.size()); ++i) {
    seg_tree[i] = {series[i - size_series], 1};
  }
  for (int i = size_series - 1; i > 0; --i) {
    seg_tree[i] = Union(seg_tree[2 * i], seg_tree[2 * i + 1]);
  }
}

Pair Max(const std::vector<Pair>& seg_tree, int l, int r) {
  Pair p = {0, 0};
  for (int i = l; i <= r; i /= 2, r /= 2) {
    if (i % 2 == 1) {
      if (p.first < seg_tree[i].first) {
        p = seg_tree[i];
      } else if (p.first == seg_tree[i].first) {
        p.second += seg_tree[i].second;
      }
      ++i;
    }
    if (r % 2 == 0) {
      if (p.first < seg_tree[r].first) {
        p = seg_tree[r];
      } else if (p.first == seg_tree[r].first) {
        p.second += seg_tree[r].second;
      }
      --r;
    }
  }
  return p;
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
  std::cin >> k;
  std::vector<Pair> seg_tree(2 * pow, {0, 0});
  BuildSegTree(seg_tree, series, pow);
  for (int i = 0; i < k; ++i) {
    Pair p = {0, 0};
    std::cin >> p.first >> p.second;
    p = Max(seg_tree, pow + p.first - 1, pow + p.second - 1);
    std::cout << p.first << ' ' << p.second << '\n';
  }
  return 0;
}