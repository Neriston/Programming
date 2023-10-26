#ifndef RAY_H
#define RAY_H
#include "vector.h"
namespace geometry {
  class Ray : public IShape {
  Point point_;
  Vector dir_;
    
  public:
    Ray();
    Ray(const Point&, const Point&);
    Ray(const Point&, const Vector&);
    ~Ray() override;
    Point P() const;
    Vector Dir() const;
    IShape& Move(const Vector&) override;
    bool ContainsPoint(const Point&) const override;
    bool CrossesSegment(const Segment&) const override;
    IShape* Clone() const override;
    std::string ToString() const override;
  };
}
#endif
