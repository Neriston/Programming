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
 Line::Line() : a_(0), b_(0), c_(0), p_first_(Point()), p_second_(Point()), dir_(Vector()) {
  }

  Line::Line(const Point& first, const Point& second) : p_first_(first), p_second_(second), dir_(Vector(first, second)) {
    a_ = second.Y() - first.Y();
    b_ = first.X() - second.X();
    c_ = second.X() * first.Y() - first.X() * second.Y();
  }

  Line::~Line() = default;

  int Line::A() const {
    return a_;
  }

  int Line::B() const {
    return b_;
  }

  int Line::C() const {
    return c_;
  }

  Vector Line::Dir() const {
    return dir_;
  }

  IShape& Line::Move(const Vector& vector) {
    p_first_.Move(vector);
    p_second_.Move(vector);
    c_ -= a_ * vector.X() + b_ * vector.Y();
    return *this;
  }

  bool Line::ContainsPoint(const Point& point) const {
    return a_ * point.X() + b_ * point.Y() + c_ == 0;
  }

  bool Line::CrossesSegment(const Segment& segment) const {
    return (a_ * segment.FirstP().X() + b_ * segment.FirstP().Y() + c_) *
           (a_ * segment.SecondP().X() + b_ * segment.SecondP().Y() + c_) <= 0;
  }

  IShape* Line::Clone() const {
    auto new_line = new Line;
    *new_line = *this;
    return new_line;
  }

  std::string Line::ToString() const {
    return "Line(" + std::to_string(a_) + ", " + std::to_string(b_) + ", " + std::to_string(c_) + ")";
  }
  
}