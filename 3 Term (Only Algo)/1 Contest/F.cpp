#include <iostream>
#include <vector>

using Vec3 = std::vector<std::vector<std::vector<int>>>;
using Vec2 = std::vector<std::vector<int>>;
using Vec1 = std::vector<int>;

struct Point {
  int x = 0;
  int y = 0;
  int z = 0;
  int value = 0;
  Point() : x(0), y(0), z(0), value(0) {
  }
  Point(const int x, const int y, const int z, const int value) : x(x), y(y), z(z), value(value) {
  }
};

std::istream& operator>>(std::istream& is, Point& p) {
  is >> p.x >> p.y >> p.z;
  return is;
}

void Update(Vec3& fenwick, const Point& p) {
  for (size_t i = p.x; i < fenwick.size(); i = (i | (i + 1))) {
    for (size_t j = p.y; j < fenwick.size(); j = (j | (j + 1))) {
      for (size_t k = p.z; k < fenwick.size(); k = (k | (k + 1))) {
        fenwick[i][j][k] += p.value;
      }
    }
  }
}

int QuerF(const Vec3& fenwick, const Point& p) {
  int sum = 0;
  for (int i = p.x; i >= 0; i = (i & (i + 1)) - 1) {
    for (int j = p.y; j >= 0; j = (j & (j + 1)) - 1) {
      for (int k = p.z; k >= 0; k = (k & (k + 1)) - 1) {
        sum += fenwick[i][j][k];
      }
    }
  }
  return sum;
}

int QueryFunc(const Vec3& fenwick, const Point& p1, const Point& p2) {
  Point x2y2z1 = {p2.x, p2.y, p1.z - 1, 0};
  Point x1y2z2 = {p1.x - 1, p2.y, p2.z, 0};
  Point x1y2z1 = {p1.x - 1, p2.y, p1.z - 1, 0};
  Point x2y1z2 = {p2.x, p1.y - 1, p2.z, 0};
  Point x2y1z1 = {p2.x, p1.y - 1, p1.z - 1, 0};
  Point x1y1z2 = {p1.x - 1, p1.y - 1, p2.z, 0};
  Point x1y1z1 = {p1.x - 1, p1.y - 1, p1.z - 1, 0};
  return QuerF(fenwick, p2) - QuerF(fenwick, x2y2z1) - QuerF(fenwick, x1y2z2) + QuerF(fenwick, x1y2z1) -
         QuerF(fenwick, x2y1z2) + QuerF(fenwick, x2y1z1) - QuerF(fenwick, x1y1z1) + QuerF(fenwick, x1y1z2);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  Vec3 fenwick(n + 1, Vec2(n + 1, Vec1(n + 1, 0)));
  int q = 0;
  std::cin >> q;
  while (q != 3) {
    if (q == 1) {
      Point p;
      std::cin >> p >> p.value;
      Update(fenwick, p);
    } else if (q == 2) {
      Point p1;
      Point p2;
      std::cin >> p1 >> p2;
      std::cout << QueryFunc(fenwick, p1, p2) << '\n';
    }
    std::cin >> q;
  }
  return 0;
}