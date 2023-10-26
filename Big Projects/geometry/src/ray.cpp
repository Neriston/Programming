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
   Ray::Ray() : point_(Point()), dir_(Vector()) {
  }

  Ray::Ray(const Point& first, const Point& second) : point_(first), dir_(Vector(first, second)) {
  }

  Ray::Ray(const Point& point, const Vector& vector) : point_(point), dir_(vector) {
  }

  Ray::~Ray() = default;

  Point Ray::P() const {
    return point_;
  }

  Vector Ray::Dir() const {
    return dir_;
  }

  IShape& Ray::Move(const Vector& vector) {
    point_.Move(vector);
    return *this;
  }

  bool Ray::ContainsPoint(const Point& point) const {
    Vector a_o(point_, point);
    return CrossProduct(a_o, dir_) == 0 && DotProduct(a_o, dir_) >= 0;
  }

  bool Ray::CrossesSegment(const Segment& segment) const {
    Vector a_o(segment.FirstP(), point_);
    int64_t cp_1 = CrossProduct(a_o, segment.Dir());
    int64_t cp_2 = CrossProduct(dir_, segment.Dir());
    if (cp_1 * cp_2 == 0) {
      return ContainsPoint(segment.FirstP()) || ContainsPoint(segment.SecondP());
    }
    return cp_1 * cp_2 < 0;
  }

  IShape* Ray::Clone() const {
    auto new_ray = new Ray;
    *new_ray = *this;
    return new_ray;
  }

  std::string Ray::ToString() const {
    return "Ray(" + point_.ToString() + ", " + dir_.ToString() + ")";
  }

}