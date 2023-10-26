#include <cmath>
#include <iomanip>
#include <vector>
#include <iostream>

struct Point {
  Point() : x(0), y(0) {
  }
  Point(const int64_t &x, const int64_t &y) : x(x), y(y) {
  }
  int64_t x;
  int64_t y;
};

std::istream &operator>>(std::istream &io, Point &point) {
  io >> point.x >> point.y;
  return io;
}

struct Vector {
  Vector() : x(0), y(0) {
  }
  Vector(const int64_t &x, const int64_t &y) : x(x), y(y) {
  }
  Vector(const Point &first, const Point &second) : x(second.x - first.x), y(second.y - first.y) {
  }
  long double LenVec() const {
    return sqrt(static_cast<long double>(x * x + y * y));
  }
  int64_t x;
  int64_t y;
};

struct Polygon {
  int64_t size;
  std::vector<Point> points;
  std::vector<Vector> vectors;
};

Vector operator-(const Point &point1, const Point &point2) {
  Vector temp(point2, point1);
  return temp;
}

std::istream &operator>>(std::istream &io, Polygon &polygon) {
  io >> polygon.size;
  for (int i = 0; i < polygon.size; ++i) {
    Point point;
    io >> point;
    polygon.points.push_back(point);
  }
  for (int i = 0; i < polygon.size - 1; ++i) {
    Vector vector = polygon.points[i + 1] - polygon.points[i];
    polygon.vectors.push_back(vector);
  }
  Vector vector = polygon.points[0] - polygon.points[polygon.size - 1];
  polygon.vectors.push_back(vector);
  return io;
}

int LenVectorProduct(const Vector &first_vector, const Vector &second_vector) {
  int64_t cp = first_vector.x * second_vector.y - second_vector.x * first_vector.y;
  if (cp == 0) {
    return 0;
  }
  if (cp > 0) {
    return 1;
  }
  return -1;
}

bool Convex(const Polygon &polygon) {
  int cnt = 0;
  while (LenVectorProduct(polygon.vectors[cnt], polygon.vectors[cnt + 1]) == 0) {
    ++cnt;
  }
  int temp = LenVectorProduct(polygon.vectors[cnt], polygon.vectors[cnt + 1]);
  for (int i = cnt + 1; i < polygon.size - 1; ++i) {
    int64_t buf = LenVectorProduct(polygon.vectors[i], polygon.vectors[i + 1]);
    if (buf != 0 && buf != temp) {
      return false;
    }
  }
  int64_t buf = LenVectorProduct(polygon.vectors[polygon.size - 1], polygon.vectors[0]);
  return !(buf != 0 && buf != temp);
}

int main() {
  Polygon polygon;
  std::cin >> polygon;
  if (Convex(polygon)) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
  return 0;
}