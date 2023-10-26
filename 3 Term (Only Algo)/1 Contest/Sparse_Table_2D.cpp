#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using Vector2d = std::vector<std::vector<int64_t>>;
using Vector3d = std::vector<Vector2d>;
using Vector4d = std::vector<Vector3d>;

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
  for (size_t i = 0; i < vector.size(); ++i) {
    for (size_t j = 0; j < vector[i].size(); ++j) {
      is >> vector[i][j];
    }
  }
  return is;
}

void BuildST(Vector4d& sparse_table, const Vector2d& values, int n, int m) {
  int log_n = 31 - __builtin_clz(n);
  int log_m = 31 - __builtin_clz(m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      sparse_table[i][j][0][0] = values[i][j];
    }
  }
  for (int k1 = 1; k1 <= log_n; ++k1) {
    int pow_k1 = 1 << (k1 - 1);
    for (int i = 0; i < n - pow_k1; ++i) {
      for (int j = 0; j < m; ++j) {
        sparse_table[i][j][k1][0] = std::min(sparse_table[i][j][k1 - 1][0], sparse_table[i + pow_k1][j][k1 - 1][0]);
      }
    }
  }
  for (int k2 = 1; k2 <= log_m; ++k2) {
    int pow_k2 = 1 << (k2 - 1);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m - pow_k2; ++j) {
        sparse_table[i][j][0][k2] = std::min(sparse_table[i][j][0][k2 - 1], sparse_table[i][j + pow_k2][0][k2 - 1]);
      }
    }
  }
  for (int k1 = 1; k1 <= log_n; ++k1) {
    for (int k2 = 1; k2 <= log_m; ++k2) {
      int pow_k1 = 1 << (k1 - 1);
      int pow_k2 = 1 << (k2 - 1);
      for (int i = 0; i < n - pow_k1; ++i) {
        for (int j = 0; j < m - pow_k2; ++j) {
          sparse_table[i][j][k1][k2] =
              std::min(std::min(sparse_table[i][j][k1 - 1][k2 - 1], sparse_table[i + pow_k1][j][k1 - 1][k2 - 1]),
                       std::min(sparse_table[i][j + pow_k2][k1 - 1][k2 - 1],
                                sparse_table[i + pow_k1][j + pow_k2][k1 - 1][k2 - 1]));
        }
      }
    }
  }
}

int64_t RMQ(const Vector4d& sparse_table, const Query& query) {
  int k1 = 31 - __builtin_clz(query.x2 - query.x1 + 1);
  int k2 = 31 - __builtin_clz(query.y2 - query.y1 + 1);
  int pow_k1 = 1 << k1;
  int pow_k2 = 1 << k2;
  int64_t ans1 = sparse_table[query.x1 - 1][query.y1 - 1][k1][k2];
  int64_t ans2 = sparse_table[query.x2 - pow_k1][query.y1 - 1][k1][k2];
  int64_t ans3 = sparse_table[query.x1 - 1][query.y2 - pow_k2][k1][k2];
  int64_t ans4 = sparse_table[query.x2 - pow_k1][query.y2 - pow_k2][k1][k2];
  return std::min(std::min(ans1, ans2), std::min(ans3, ans4));
}

int main() {
  const int64_t inf = std::numeric_limits<int64_t>::max();
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Vector2d values(n, std::vector<int64_t>(m, 0));
  std::cin >> values;
  int k1 = 31 - __builtin_clz(n);
  int k2 = 31 - __builtin_clz(m);
  Vector4d sparse_table(n, Vector3d(m, Vector2d(k1 + 1, std::vector<int64_t>(k2 + 1, inf))));
  BuildST(sparse_table, values, n, m);
  int q = 0;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    Query query;
    std::cin >> query;
    std::cout << RMQ(sparse_table, query) << '\n';
  }
  return 0;
}