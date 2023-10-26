#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

struct Point {
  Point() : x(0), y(0) {
  }
  Point(const int64_t &x, const int64_t &y) : x(x), y(y) {
  }
  int64_t x = 0;
  int64_t y = 0;
};

struct Vector {
  Vector() : x(0), y(0) {
  }
  Vector(const int64_t &x, const int64_t &y) : x(x), y(y) {
  }
  Vector(const Point &point1, const Point &point2) : x(point2.x - point1.x), y(point2.y - point1.y) {
  }
  int64_t x;
  int64_t y;
};

struct Line {
  Line() : first(Point()), second(Point()), a(0), b(0), c(0) {
  }
  Line(const Point &first, const Point &second) : first(first), second(second) {
    a = second.y - first.y;
    b = first.x - second.x;
    c = second.x * first.y - first.x * second.y;
  }
  Point first;
  Point second;
  int64_t a;
  int64_t b;
  int64_t c;
};

struct Polygon {
  int64_t size;
  Point o;
  std::vector<Point> points;
  std::vector<Line> lines;
};

std::istream &operator>>(std::istream &io, Polygon &polygon) {
  io >> polygon.size >> polygon.o.x >> polygon.o.y;
  for (int i = 0; i < polygon.size; ++i) {
    Point point;
    io >> point.x >> point.y;
    polygon.points.push_back(point);
  }
  for (int i = 0; i < polygon.size - 1; ++i) {
    Line line = {polygon.points[i], polygon.points[i + 1]};
    polygon.lines.push_back(line);
  }
  Line line = {polygon.points[polygon.size - 1], polygon.points[0]};
  polygon.lines.push_back(line);
  return io;
}

int64_t ScalarProduct(const Vector &first, const Vector &second) {
  return first.x * second.x + first.y * second.y;
}

int64_t CrossProduct(const Vector &first, const Vector &second) {
  return first.x * second.y - second.x * first.y;
}

bool BelongsSegment(const Point &point, const Line &line) {
  Vector a_o(line.first, point);
  Vector o_b(point, line.second);
  return CrossProduct(a_o, o_b) == 0 && ScalarProduct(a_o, o_b) >= 0;
}

int Intersection(const Line &in, const Line &line) {
  if (line.a == 0) {
    return 0;
  }
  auto inter_x = static_cast<long double>(in.c * line.b - line.c * in.b) / static_cast<long double>((line.a * in.b));
  auto inter_y = static_cast<long double>(-in.c) / static_cast<long double>(in.b);
  if (inter_x >= static_cast<long double>(in.first.x) &&
      inter_y >= static_cast<long double>(std::min(line.first.y, line.second.y)) &&
      inter_y <= static_cast<long double>(std::max(line.first.y, line.second.y))) {
    if (inter_y == static_cast<long double>(std::min(line.first.y, line.second.y))) {
      return 0;
    }
    return 1;
  }
  return 0;
}

int main() {
  Polygon polygon;
  std::cin >> polygon;
  Point o1{polygon.o.x + 1, polygon.o.y};
  Line in{polygon.o, o1};
  bool on = false;
  int64_t cnt = 0;
  for (int i = 0; i < polygon.size; ++i) {
    if (!on && BelongsSegment(polygon.o, polygon.lines[i])) {
      on = true;
    }
    cnt += Intersection(in, polygon.lines[i]);
  }
  if (cnt % 2 == 0) {
    if (on) {
      std::cout << "YES";
    } else {
      std::cout << "NO";
    }
  } else {
    std::cout << "YES";
  }
  return 0;
}