#include <cmath>
#include <iomanip>
#include <iostream>

struct Point {
  Point() : x(0), y(0) {
  }
  Point(const int &x, const int &y) : x(x), y(y) {
  }
  int x = 0;
  int y = 0;
};

struct Vector {
  Vector() : x(0), y(0) {
  }
  Vector(const int &x, const int &y) : x(x), y(y) {
  }
  int x;
  int y;
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
  int a;
  int b;
  int c;
};

int64_t ScalarProduct(const Vector &first, const Vector &second) {
  return first.x * second.x + first.y * second.y;
}

bool BelongsLine(const Point &point, const Line &line) {
  return line.a * point.x + line.b * point.y + line.c == 0;
}

bool BelongsBeam(const Point &point, const Line &line, const Vector &ab, const Vector &ac) {
  return ScalarProduct(ab, ac) >= 0 && BelongsLine(point, line);
}

bool BelongsSegment(const Point &point, const Line &line, const Vector &ab, const Vector &ac, const Vector &bc) {
  return ScalarProduct(ab, bc) <= 0 && BelongsBeam(point, line, ab, ac);
}

int main() {
  int a1, b1, c1, a2, b2, c2;
  std::cin >> c1 >> c2 >> a1 >> a2 >> b1 >> b2;
  Point first(a1, a2);
  Point second(b1, b2);
  Point point(c1, c2);
  Vector ab(b1 - a1, b2 - a2);
  Vector ac(c1 - a1, c2 - a2);
  Vector bc(c1 - b1, c2 - b2);
  Line line(first, second);
  if (BelongsLine(point, line)) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
  if (BelongsBeam(point, line, ab, ac)) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
  if (BelongsSegment(point, line, ab, ac, bc)) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
  return 0;
}