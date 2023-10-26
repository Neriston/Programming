#include <iostream>
#include <string>
#include <vector>
#include "../vector.h"
#include "../point.h"
#include "../line.h"
#include "../ray.h"
#include "../segment.h"
#include "../polygon.h"
#include "../circle.h"

namespace geometry {
  Point::Point() : x_(0), y_(0) {
  }

  Point::Point(const int& x, const int& y) : x_(x), y_(y) {
  }

  Point::Point(const Vector& vector) : x_(vector.X()), y_(vector.Y()) {
  }

  Point::~Point() = default;

  int Point::X() const {
    return x_;
  }

  int Point::Y() const {
    return y_;
  }

  IShape& Point::Move(const Vector& first) {
    x_ += first.X();
    y_ += first.Y();
    return *this;
  }

  bool Point::ContainsPoint(const Point& point) const {
    return x_ == point.x_ && y_ == point.y_;
  }

  bool Point::CrossesSegment(const Segment& segment) const {
    Vector a_o(segment.FirstP(), *this);
    Vector o_b(*this, segment.SecondP());
    return CrossProduct(a_o, o_b) == 0 && DotProduct(a_o, o_b) >= 0;
  }

  IShape* Point::Clone() const {
    auto new_point = new Point;
    *new_point = *this;
    return new_point;
  }

  std::string Point::ToString() const {
    return "Point(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
  }

  Vector operator-(const Point& first, const Point& second) {
    return Vector(second, first);
  }
}