#ifndef CIRCLE_H
#define CIRCLE_H
#include "vector.h"
namespace geometry {
  class Circle : public IShape {
  int r_;
  Point point_;
    
  public:
    Circle();
    Circle(const Point&, const int&);
    ~Circle() override;
    IShape& Move(const Vector&) override;
    bool ContainsPoint(const Point&) const override;
    bool CrossesSegment(const Segment&) const override;
    IShape* Clone() const override;
    std::string ToString() const override;
  };
}
#endif