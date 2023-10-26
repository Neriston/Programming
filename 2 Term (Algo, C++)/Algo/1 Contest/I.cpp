#include <iostream>
#include <iomanip>
#include <cmath>

struct Point {
  int64_t x = 0;
  int64_t y = 0;
};

struct Vector {
  Vector(const Point &point1, const Point &point2) : a(point1), p(point2) {
  }
  Point a;
  Point p;
  int64_t x = p.x - a.x;
  int64_t y = p.y - a.y;
};

struct Polygon {
  explicit Polygon(const int64_t &count) : cnt(count) {
  }
  int64_t cnt;
  Point *points = new Point[cnt]{};
  ~Polygon() {
    delete[] points;
  }
  Polygon(const Polygon &) = default;
  Polygon &operator=(const Polygon &other) = default;
};

long double LenVectorProduct(const Vector &vector1, const Vector &vector2) {
  return vector1.x * vector2.y - vector2.x * vector1.y;
}

std::istream &operator>>(std::istream &io, Point &point) {
  io >> point.x >> point.y;
  return io;
}

long double Square(const Polygon &polygon) {
  long double square = 0.0;
  for (int i = 1; i < polygon.cnt - 1; ++i) {
    Vector vector1(polygon.points[0], polygon.points[i]);
    Vector vector2(polygon.points[0], polygon.points[i + 1]);
    square += LenVectorProduct(vector1, vector2);
  }
  return std::abs(square) / 2;
}

int main() {
  int n;
  std::cin >> n;
  Polygon polygon(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> polygon.points[i];
  }
  std::cout << std::fixed << std::setprecision(1);
  std::cout << Square(polygon);
  return 0;
}