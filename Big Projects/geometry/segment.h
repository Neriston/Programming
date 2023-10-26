#ifndef SEGMENT_H
#define SEGMENT_H
#include "vector.h"
namespace geometry {
 class Segment : public IShape {
  Point first_p_, second_p_;
  Vector dir_;

  public:
   Segment();
   Segment(const Point&, const Point&);
   ~Segment() override;
   Point FirstP() const;
   Point SecondP() const;
   Vector Dir() const;
   IShape& Move(const Vector&) override;
   bool ContainsPoint(const Point&) const override;
   bool CrossesSegment(const Segment&) const override;
   IShape* Clone() const override;
   std::string ToString() const override;
 };
}
#endif