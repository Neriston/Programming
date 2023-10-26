#include <iostream>
#include <vector>

struct Query {
  char category = ' ';
  int l = 0;
  int r = 0;
  int add = 0;
  Query() : category(' '), l(0), r(0), add(0) {
  }
  Query(char category, int l, int r, int add = 0) : category(category), l(l), r(r), add(add) {
  }
};

std::istream& operator>>(std::istream& is, Query& query) {
  is >> query.category >> query.l >> query.r;
  if (query.category == 'm') {
    return is;
  }
  is >> query.add;
  return is;
}

std::istream& operator>>(std::istream& is, std::vector<int>& vector) {
  for (size_t i = 0; i < vector.size(); ++i) {
    is >> vector[i];
  }
  return is;
}

void BuildSegTree(std::vector<int>& values, std::vector<std::pair<int, int>>& segment_tree, int vertex, int tl,
                  int tr) {
  if (tl == tr) {
    segment_tree[vertex].first = values[tl];
  } else {
    int tm = (tl + tr) / 2;
    BuildSegTree(values, segment_tree, vertex * 2, tl, tm);
    BuildSegTree(values, segment_tree, vertex * 2 + 1, tm + 1, tr);
    segment_tree[vertex].first = std::max(segment_tree[vertex * 2].first, segment_tree[vertex * 2 + 1].first);
  }
}

void Push(std::vector<std::pair<int, int>>& segment_tree, int vertex) {
  segment_tree[vertex].first += segment_tree[vertex].second;
  segment_tree[vertex * 2].second += segment_tree[vertex].second;
  segment_tree[vertex * 2 + 1].second += segment_tree[vertex].second;
  segment_tree[vertex].second = 0;
}

int Max(int vertex, int tl, int tr, std::vector<std::pair<int, int>>& segment_tree, Query& query) {
  if (query.l > query.r) {
    return 0;
  }
  if (query.l == tl && query.r == tr) {
    return segment_tree[vertex].first + segment_tree[vertex].second;
  }
  Push(segment_tree, vertex);
  int tm = (tl + tr) / 2;
  Query query1('a', query.l, std::min(query.r, tm), query.add);
  Query query2('a', std::max(query.l, tm + 1), query.r, query.add);
  int left = Max(vertex * 2, tl, tm, segment_tree, query1);
  int right = Max(vertex * 2 + 1, tm + 1, tr, segment_tree, query2);
  return std::max(left, right);
}

void Add(int vertex, int tl, int tr, std::vector<std::pair<int, int>>& segment_tree, Query& query) {
  if (query.l > query.r) {
    return;
  }
  if (query.l == tl && query.r == tr) {
    segment_tree[vertex].second += query.add;
  } else {
    Push(segment_tree, vertex);
    int tm = (tl + tr) / 2;
    Query query1('a', query.l, std::min(query.r, tm), query.add);
    Query query2('a', std::max(query.l, tm + 1), query.r, query.add);
    Query query3('a', tl, tm, 0);
    Query query4('a', tm + 1, tr, 0);
    Add(vertex * 2, tl, tm, segment_tree, query1);
    Add(vertex * 2 + 1, tm + 1, tr, segment_tree, query2);
    segment_tree[vertex].first =
        std::max(Max(vertex * 2, tl, tm, segment_tree, query3), Max(vertex * 2 + 1, tm + 1, tr, segment_tree, query4));
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  std::vector<std::pair<int, int>> segment_tree(4 * n, {0, 0});
  std::vector<int> values(n, 0);
  std::cin >> values;
  BuildSegTree(values, segment_tree, 1, 0, n - 1);
  int m = 0;
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    Query query;
    std::cin >> query;
    --query.l;
    --query.r;
    if (query.category == 'm') {
      std::cout << Max(1, 0, n - 1, segment_tree, query) << ' ';
    } else {
      Add(1, 0, n - 1, segment_tree, query);
    }
  }
  return 0;
}