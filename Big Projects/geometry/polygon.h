#ifndef POLYGON_H
#define POLYGON_H
#include "vector.h"
namespace geometry {
  class Polygon : public IShape {
  int size_;
  std::vector<Point> point_;
  std::vector<Segment> segment_;
    
  public:
    Polygon();
    explicit Polygon(const std::vector<Point>&);
    ~Polygon() override;
    int Size() const;
    IShape& Move(const Vector&) override;
    bool ContainsPoint(const Point&) const override;
    bool CrossesSegment(const Segment&) const override;
    IShape* Clone() const override;
    std::string ToString() const override;
  };
}
#endif