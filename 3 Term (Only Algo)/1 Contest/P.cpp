#include <iostream>
#include <vector>

struct Node {
  size_t value = 0;
  int64_t promise = 0;
  size_t cnt = 0;
  Node() : value(0), promise(0), cnt(0) {
  }
  Node(size_t value, int64_t promise, size_t cnt) : value(value), promise(promise), cnt(cnt) {
  }
};

struct SegmentTree {
  size_t size;
  std::vector<Node> st;

  SegmentTree() : size(0), st(0){};

  explicit SegmentTree(size_t n) : size(4 * (n + 1)) {
    st.resize(size);
    Build(1, 1, n);
  }

  void Build(size_t vertex, size_t l, size_t r) {
    if (l == r) {
      st[vertex].cnt = 1;
      return;
    }
    size_t mid = (l + r) / 2;
    Build(2 * vertex, l, mid);
    Build(2 * vertex + 1, mid + 1, r);
    st[vertex].cnt = st[2 * vertex].cnt + st[2 * vertex + 1].cnt;
  }

  void Push(size_t vertex) {
    st[vertex].value += st[vertex].cnt * st[vertex].promise;
    if (2 * vertex < size) {
      st[2 * vertex].promise += st[vertex].promise;
    }
    if (2 * vertex + 1 < size) {
      st[2 * vertex + 1].promise += st[vertex].promise;
    }
    st[vertex].promise = 0;
  }

  void Update(size_t vertex, size_t l, size_t r, size_t now_l, size_t now_r, int64_t add) {
    if (now_l >= l && now_r <= r) {
      st[vertex].promise += add;
      return;
    }
    if (now_l > r || now_r < l) {
      return;
    }
    Push(vertex);
    size_t now_mid = (now_l + now_r) / 2;
    Update(2 * vertex, l, r, now_l, now_mid, add);
    Update(2 * vertex + 1, l, r, now_mid + 1, now_r, add);
    size_t ls = QuerySum(2 * vertex, now_l, now_mid, now_l, now_mid);
    size_t rs = QuerySum(2 * vertex + 1, now_mid + 1, now_r, now_mid + 1, now_r);
    st[vertex].value = ls + rs;
  }

  size_t QuerySum(size_t vertex, size_t l, size_t r, size_t now_l, size_t now_r) {
    if (now_l >= l && now_r <= r) {
      return st[vertex].value + st[vertex].promise * st[vertex].cnt;
    }
    if (now_l > r || now_r < l) {
      return 0;
    }
    Push(vertex);
    size_t now_mid = (now_l + now_r) / 2;
    size_t ls = QuerySum(2 * vertex, l, r, now_l, now_mid);
    size_t rs = QuerySum(2 * vertex + 1, l, r, now_mid + 1, now_r);
    return ls + rs;
  }
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  SegmentTree st(n);
  for (int i = 0; i < m; ++i) {
    size_t query = 0;
    std::cin >> query;
    if (query == 2) {
      size_t l = 0;
      size_t r = 0;
      std::cin >> l >> r;
      std::cout << st.QuerySum(1, l + 1, r, 1, n) << ' ';
    } else {
      size_t l = 0;
      size_t r = 0;
      int64_t add = 0;
      std::cin >> l >> r >> add;
      st.Update(1, l + 1, r, 1, n, add);
    }
  }
  return 0;
}