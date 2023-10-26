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
   Circle::Circle() : r_(0), point_(Point()) {
  }

  Circle::Circle(const Point& point, const int& r) : r_(r), point_(point) {
  }

  Circle::~Circle() = default;

  IShape& Circle::Move(const Vector& vector) {
    point_.Move(vector);
    return *this;
  }

  bool Circle::ContainsPoint(const Point& point) const {
    Vector o_a(point_, point);
    return o_a.Len2() <= r_ * r_;
  }

  bool Circle::CrossesSegment(const Segment& segment) const {
    Vector a_o(segment.FirstP(), point_);
    Vector b_o(segment.SecondP(), point_);
    auto square = static_cast<int64_t>(std::abs(CrossProduct(a_o, segment.Dir())));
    auto temp = static_cast<int64_t>(r_);
    auto temp1 = temp * temp * static_cast<int64_t>(segment.Dir().Len2());

    return square * square <= temp1 && (a_o.Len2() >= temp * temp || b_o.Len2() >= temp * temp);
  }

  IShape* Circle::Clone() const {
    auto new_circle = new Circle;
    *new_circle = *this;
    return new_circle;
  }

  std::string Circle::ToString() const {
    return "Circle(" + point_.ToString() + ", " + std::to_string(r_) + ")";
  }
}