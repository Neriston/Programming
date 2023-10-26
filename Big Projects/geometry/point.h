#ifndef POINT_H
#define POINT_H
#include "vector.h"
namespace geometry {
  class Point : public IShape {
  int x_, y_;
  
  public:
    Point();
    Point(const int&, const int&);
    explicit Point(const Vector&);
    ~Point() override;
    int X() const;
    int Y() const;
    IShape& Move(const Vector&) override;
    bool ContainsPoint(const Point&) const override;
    bool CrossesSegment(const Segment&) const override;
    IShape* Clone() const override;
    std::string ToString() const override;
    friend Vector operator-(const Point&, const Point&);
  };
}
#endif