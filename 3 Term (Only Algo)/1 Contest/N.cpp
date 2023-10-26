#include <iostream>
#include <vector>
#include <limits>

using Vector2d = std::vector<std::vector<int64_t>>;

struct Query {
  int x1 = 0;
  int y1 = 0;
  int x2 = 0;
  int y2 = 0;
  Query() : x1(0), y1(0), x2(0), y2(0) {
  }
  Query(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {
  }
};

std::istream& operator>>(std::istream& is, Query& query) {
  is >> query.x1 >> query.y1 >> query.x2 >> query.y2;
  return is;
}

std::istream& operator>>(std::istream& is, Vector2d& vector) {
  for (size_t i = 1; i < vector.size(); ++i) {
    for (size_t j = 1; j < vector[i].size(); ++j) {
      is >> vector[i][j];
    }
  }
  return is;
}

void BuildTreeY(Vector2d& segment_tree, const Vector2d& values, int tl, int tr, int vertex, size_t line_y) {
  if (tl == tr) {
    segment_tree[line_y][vertex] = values[line_y][tl];
  } else {
    int tm = (tl + tr) / 2;
    int lc = 2 * vertex;
    int rc = lc + 1;
    BuildTreeY(segment_tree, values, tl, tm, lc, line_y);
    BuildTreeY(segment_tree, values, tm + 1, tr, rc, line_y);
    segment_tree[line_y][vertex] = std::min(segment_tree[line_y][lc], segment_tree[line_y][rc]);
  }
}

void BuildTree2D(Vector2d& segment_tree, const Vector2d& segment_tree_y, int tl, int tr, int vertex) {
  if (tl == tr) {
    for (size_t i = 1; i < segment_tree_y[tl].size(); ++i) {
      segment_tree[vertex][i] = segment_tree_y[tl][i];
    }
  } else {
    int tm = (tl + tr) / 2;
    int lc = 2 * vertex;
    int rc = lc + 1;
    BuildTree2D(segment_tree, segment_tree_y, tl, tm, lc);
    BuildTree2D(segment_tree, segment_tree_y, tm + 1, tr, rc);
    for (size_t i = 1; i < segment_tree[0].size(); ++i) {
      segment_tree[vertex][i] = std::min(segment_tree[lc][i], segment_tree[rc][i]);
    }
  }
}

int64_t QueryX(const Vector2d& segment_tree_2d, int vertex_x, int vertex_y, int start, int end, int x1, int x2) {
  if ((x1 < start && x2 < start) || (x1 > end && x2 > end)) {
    return std::numeric_limits<int64_t>::max();
  }
  if (start >= x1 && end <= x2 && x1 <= x2) {
    return segment_tree_2d[vertex_x][vertex_y];
  }
  int tm = (start + end) / 2;
  int64_t left = QueryX(segment_tree_2d, 2 * vertex_x, vertex_y, start, tm, x1, x2);
  int64_t right = QueryX(segment_tree_2d, 2 * vertex_x + 1, vertex_y, tm + 1, end, x1, x2);
  return std::min(left, right);
}

int64_t QueryY(const Vector2d& segment_tree_2d, int vertex_y, int start, int end, int y1, int y2, int x1, int x2,
               int n) {
  if ((y1 < start && y2 < start) || (y1 > end && y2 > end)) {
    return std::numeric_limits<int64_t>::max();
  }
  if (start >= y1 && end <= y2 && y1 <= y2) {
    return QueryX(segment_tree_2d, 1, vertex_y, 1, n, x1, x2);
  }
  int tm = (start + end) / 2;
  int64_t left = QueryY(segment_tree_2d, 2 * vertex_y, start, tm, y1, y2, x1, x2, n);
  int64_t right = QueryY(segment_tree_2d, 2 * vertex_y + 1, tm + 1, end, y1, y2, x1, x2, n);
  return std::min(left, right);
}

int main() {
  const int64_t inf = std::numeric_limits<int64_t>::max();
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Vector2d values(n + 1, std::vector<int64_t>(m + 1, 0));
  std::cin >> values;
  Vector2d segment_tree_y(n + 1, std::vector<int64_t>(4 * m, inf));
  Vector2d segment_tree_2d(4 * n, std::vector<int64_t>(4 * m, inf));
  for (size_t line_y = 1; line_y < values.size(); ++line_y) {
    BuildTreeY(segment_tree_y, values, 1, m, 1, line_y);
  }
  BuildTree2D(segment_tree_2d, segment_tree_y, 1, n, 1);
  int q = 0;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    Query query;
    std::cin >> query;
    std::cout << QueryY(segment_tree_2d, 1, 1, m, query.y1, query.y2, query.x1, query.x2, n);
    std::cout << '\n';
  }
  return 0;
}