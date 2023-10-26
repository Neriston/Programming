#include <iostream>
#include <vector>

struct Query {
  Query() : s(' '), l(0), r(0) {
  }
  Query(const char s, const int l, const int r) : s(s), l(l), r(r) {
  }
  char s = ' ';
  int l = 0;
  int r = 0;
};

void PrefixSum(std::vector<int64_t>& prefix, const std::vector<int64_t>& values) {
  prefix[0] = values[0];
  for (size_t i = 1; i < values.size(); ++i) {
    prefix[i] = values[i] + prefix[i - 1];
  }
}

std::istream& operator>>(std::istream& is, std::vector<int64_t>& vector) {
  for (size_t i = 0; i < vector.size(); ++i) {
    is >> vector[i];
  }
  return is;
}

std::istream& operator>>(std::istream& is, Query& q) {
  is >> q.s >> q.l >> q.r;
  return is;
}

std::istream& operator>>(std::istream& is, std::vector<Query>& vector) {
  for (size_t i = 0; i < vector.size(); ++i) {
    is >> vector[i];
  }
  return is;
}

void Update(std::vector<int64_t>& fenwick, int index, int delta) {
  for (size_t i = index; i < fenwick.size(); i = i | (i + 1)) {
    fenwick[i] += delta;
  }
}

int64_t QueryFunc(const std::vector<int64_t>& fenwick, int r) {
  int64_t sum = 0;
  for (int i = r; i >= 0; i = (i & (i + 1)) - 1) {
    sum += fenwick[i];
  }
  return sum;
}

int64_t QueryFunc(const std::vector<int64_t>& fenwick, int l, int r) {
  return QueryFunc(fenwick, r) - QueryFunc(fenwick, l - 1);
}

void BuildFenwick(std::vector<int64_t>& fenwick, const std::vector<int64_t>& values) {
  for (size_t i = 0; i < values.size(); ++i) {
    int64_t x = 0;
    int64_t y = static_cast<int>((i & (i + 1))) - 1;
    if (y >= 0) {
      x = values[(i & (i + 1)) - 1];
    }
    fenwick[i] = values[i] - x;
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  int64_t k = 0;
  std::cin >> n;
  std::vector<int64_t> values(n, 0);
  std::vector<int64_t> prefix(n, 0);
  std::vector<int64_t> fenwick(n, 0);
  std::cin >> values;
  std::cin >> k;
  PrefixSum(prefix, values);
  BuildFenwick(fenwick, prefix);
  for (int i = 0; i < k; ++i) {
    Query q;
    std::cin >> q;
    if (q.s == 's') {
      std::cout << QueryFunc(fenwick, q.l - 1, q.r - 1) << ' ';
    } else {
      Update(fenwick, q.l - 1, -values[q.l - 1]);
      Update(fenwick, q.l - 1, q.r);
      values[q.l - 1] = q.r;
    }
  }
  return 0;
}