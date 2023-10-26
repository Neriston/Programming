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
  Vector(const Point &first, const Point &second) : x(second.x - first.x), y(second.y - first.y) {
  }
  int x;
  int y;
};

struct Line {
  Line() : first(Point()), second(Point()), a(0), b(0), c(0) {
  }
  Line(const Point &first, const Point &second) : first(first), second(second), dir(first, second) {
    a = second.y - first.y;
    b = first.x - second.x;
    c = second.x * first.y - first.x * second.y;
  }
  Point first;
  Point second;
  Vector dir;
  int a;
  int b;
  int c;
};

int64_t ScalarProduct(const Vector &first, const Vector &second) {
  return first.x * second.x + first.y * second.y;
}

int64_t CrossProduct(const Vector &first, const Vector &second) {
  return first.x * second.y - second.x * first.y;
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

long double LenVec(const Vector &vector) {
  return sqrt(static_cast<long double>(vector.x * vector.x + vector.y * vector.y));
}

long double DistLine(const Line &line, const Point &point) {
  Vector vector(line.first, point);
  return static_cast<long double>(std::abs(CrossProduct(vector, line.dir))) / LenVec(line.dir);
}

long double DistRay(const Line &line, const Point &point) {
  Vector vector(line.first, point);
  int64_t sp = ScalarProduct(vector, line.dir);
  if (sp <= 0) {
    return LenVec(vector);
  }
  return DistLine(line, point);
}

long double DistSeg(const Line &line, const Point &point) {
  Vector first_vector(line.first, point);
  Vector second_vector(line.second, point);
  int64_t sp = ScalarProduct(second_vector, line.dir);
  if (sp >= 0) {
    return LenVec(second_vector);
  }
  return DistRay(line, point);
}

int main() {
  int a1, b1, c1, a2, b2, c2;
  std::cin >> c1 >> c2 >> a1 >> a2 >> b1 >> b2;
  Point first(a1, a2);
  Point second(b1, b2);
  Point point(c1, c2);
  Line line(first, second);
  std::cout << std::fixed << std::setprecision(6);
  std::cout << DistLine(line, point) << "\n";
  std::cout << DistRay(line, point) << "\n";
  std::cout << DistSeg(line, point);
}