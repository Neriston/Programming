#include <cmath>
#include <iomanip>
#include <iostream>

struct Point {
  Point() = default;
  Point(double x, double y) : x(x), y(y) {
  }
  double x = 0;
  double y = 0;
};

struct Vector {
  Vector() = default;
  Vector(int x, int y) : x(x), y(y) {
  }
  int x = 0;
  int y = 0;
};

struct Line {
  Line() = default;
  Line(int x, int y, int c) : direct(x, y), c(c) {
  }
  Vector direct;
  int c;
};

double Len(const Vector &vector) {
  return sqrt(vector.x * vector.x + vector.y * vector.y);
}

double VectorProduct(const Vector &first_vector, const Vector &second_vector) {
  return first_vector.x * second_vector.y - second_vector.x * first_vector.y;
}

void Intersection(const Line &first_line, const Line &second_line, Point &intersect, double &len) {
  if (VectorProduct(first_line.direct, second_line.direct) == 0) {
    if (second_line.direct.x != 0) {
      len = fabs(-first_line.c + second_line.c * first_line.direct.x / second_line.direct.x) / Len(first_line.direct);
    } else {
      len = fabs(-first_line.c + second_line.c * first_line.direct.y / second_line.direct.y) / Len(first_line.direct);
    }
  } else {
    intersect.x = 1.0 * (second_line.c * (-first_line.direct.x) + first_line.c * second_line.direct.x) /
                  (VectorProduct(first_line.direct, second_line.direct));
    intersect.y = 1.0 * (second_line.direct.y * first_line.c - second_line.c * first_line.direct.y) /
                  (VectorProduct(first_line.direct, second_line.direct));
  }
}

int main() {
  Line first_line;
  Line second_line;
  Point intersect;
  double len = -1;
  int a1, b1, c1, a2, b2, c2;
  std::cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;
  first_line = {-b1, a1, c1};
  second_line = {-b2, a2, c2};
  Intersection(first_line, second_line, intersect, len);
  std::cout << std::fixed << std::setprecision(6);
  std::cout << 1.0 * first_line.direct.x << ' ' << 1.0 * first_line.direct.y << '\n';
  std::cout << 1.0 * second_line.direct.x << ' ' << 1.0 * second_line.direct.y << '\n';
  if (len == -1) {
    std::cout << intersect.x << ' ' << intersect.y;
  } else {
    std::cout << len;
  }
  return 0;
}