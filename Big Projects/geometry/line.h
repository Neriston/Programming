#ifndef LINE_H
#define LINE_H
#include "vector.h"
namespace geometry {
  class Line : public IShape {
  int a_, b_, c_;
  Point p_first_, p_second_;
  Vector dir_;

  public:
    Line();
    Line(const Point&, const Point&);
    ~Line() override;
    int A() const;
    int B() const;
    int C() const;
    Vector Dir() const;
    IShape& Move(const Vector&) override;
    bool ContainsPoint(const Point&) const override;
    bool CrossesSegment(const Segment&) const override;
    IShape* Clone() const override;
    std::string ToString() const override;
  };
}
#endif
