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

std::istream &operator>>(std::istream &io, Point &point) {
  io >> point.x >> point.y;
  return io;
}

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

struct Segment {
  Point first_p, second_p;
  Vector dir;
  Segment() : first_p(Point()), second_p(Point()), dir(Vector()) {
  }
  Segment(const Point &first, const Point &second) : first_p(first), second_p(second), dir(first, second) {
  }
};

int64_t CrossProduct(const Vector &first, const Vector &second) {
  return first.x * second.y - second.x * first.y;
}

int64_t DotProduct(const Vector &first, const Vector &second) {
  return first.x * second.x + first.y * second.y;
}

bool ContainsPoint(const Segment &segment, const Point &point) {
  Vector a_o(segment.first_p, point);
  Vector o_b(point, segment.second_p);
  return CrossProduct(a_o, o_b) == 0 && DotProduct(a_o, o_b) >= 0;
}

bool CrossesSegment(const Segment &segment_first, const Segment &segment_second) {
  int64_t cp_1 = CrossProduct(segment_first.dir, Vector(segment_first.first_p, segment_second.first_p));
  int64_t cp_2 = CrossProduct(segment_first.dir, Vector(segment_first.first_p, segment_second.second_p));
  int64_t cp_3 = CrossProduct(segment_second.dir, Vector(segment_second.first_p, segment_first.first_p));
  int64_t cp_4 = CrossProduct(segment_second.dir, Vector(segment_second.first_p, segment_first.second_p));
  bool all_zero = (cp_1 == 0) && (cp_2 == 0) && (cp_3 == 0) && (cp_4 == 0);
  if (all_zero) {
    return (ContainsPoint(segment_first, segment_second.first_p)) ||
           ContainsPoint(segment_first, segment_second.second_p) ||
           ContainsPoint(segment_second, segment_first.first_p) ||
           ContainsPoint(segment_second, segment_first.second_p);
  }
  return (cp_1 * cp_2 <= 0 && cp_3 * cp_4 <= 0);
}

int main() {
  Point a, b, c, d;
  std::cin >> a >> b >> c >> d;
  Segment a_b(a, b);
  Segment c_d(c, d);
  if (CrossesSegment(a_b, c_d)) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
}