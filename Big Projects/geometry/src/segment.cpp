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
    Segment::Segment() : first_p_(Point()), second_p_(Point()), dir_(Vector()) {
  }

  Segment::Segment(const Point& first, const Point& second) : first_p_(first), second_p_(second), dir_(Vector(first, second)) {
  }

  Segment::~Segment() = default;

  Point Segment::FirstP() const {
    return first_p_;
  }

  Point Segment::SecondP() const {
    return second_p_;
  }

  Vector Segment::Dir() const {
    return dir_;
  }

  IShape& Segment::Move(const Vector& first) {
    first_p_.Move(first);
    second_p_.Move(first);
    return *this;
  }

  bool Segment::ContainsPoint(const Point& point) const {
    Vector a_o(first_p_, point);
    Vector o_b(point, second_p_);
    return CrossProduct(a_o, o_b) == 0 && DotProduct(a_o, o_b) >= 0;
  }

  bool Segment::CrossesSegment(const Segment& segment) const {
    int64_t cp_1 = CrossProduct(dir_, Vector(first_p_, segment.FirstP()));
    int64_t cp_2 = CrossProduct(dir_, Vector(first_p_, segment.SecondP()));
    int64_t cp_3 = CrossProduct(segment.Dir(), Vector(segment.FirstP(), first_p_));
    int64_t cp_4 = CrossProduct(segment.Dir(), Vector(segment.FirstP(), second_p_));
    bool all_zero = (cp_1 == 0) && (cp_2 == 0) && (cp_3 == 0) && (cp_4 == 0);
    if (all_zero) {
      return (ContainsPoint(segment.FirstP()) || ContainsPoint(segment.SecondP())) ||
              segment.ContainsPoint(first_p_) || segment.ContainsPoint(second_p_);
    }
  return (cp_1 * cp_2 <= 0 && cp_3 * cp_4 <= 0);
  }

  IShape* Segment::Clone() const {
    auto new_segment = new Segment;
    *new_segment = *this;
    return new_segment;
  }

  std::string Segment::ToString() const {
    return "Segment(" + first_p_.ToString() + ", " + second_p_.ToString() + ")"; 
  }
}