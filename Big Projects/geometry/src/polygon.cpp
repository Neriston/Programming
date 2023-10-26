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
    Polygon::Polygon() : size_(0) {
  }

  Polygon::Polygon(const std::vector<Point>& points) {
    size_ = points.size();
    point_.resize(points.size());
    segment_.resize(points.size());
    for (int i = 0; i < size_; ++i) {
      point_[i] = points[i];
    }
    for (int i = 0; i < size_ - 1; ++i) {
      segment_[i] = Segment(point_[i], point_[i + 1]);
    }
    segment_[size_ - 1] = Segment(point_[size_ - 1], point_[0]);
  }

  Polygon::~Polygon() = default;

  int Polygon::Size() const {
    return size_;
  }

  IShape& Polygon::Move(const Vector& vector) {
    for (int i = 0; i < size_; ++i) {
      point_[i].Move(vector);
      segment_[i].Move(vector);
    }
    return *this;
  }

  IShape* Polygon::Clone() const {
    auto* new_polygon = new Polygon;
    *new_polygon = *this;
    return new_polygon;
  }
  
  bool Polygon::ContainsPoint(const Point& point) const {
    int max_x = point_[0].X();
    for (int i = 0; i < size_; ++i) {
      if (max_x < point_[i].X()) {
        max_x = point_[i].X();
      }
    }
    Segment segment(point, Point(max_x + 1, point.Y()));
    bool flag = false;
    std::vector<Point>points;
    points.push_back(point_[size_ - 1]);
    for (int i = 1; i < size_ + 1; ++i) {
      points.push_back(point_[i - 1]);
    }
    points.push_back(point_[0]);
    int cnt = 0;
    for (int i = 1; i < size_ + 1; ++i) {
      if (segment_[i - 1].ContainsPoint(point)) {
        flag = true;
        break;
      }
      if (segment.ContainsPoint(points[i])) {
        if (points[i - 1].Y() < points[i].Y()) {
          ++cnt;
        }
        if (points[i + 1].Y() < points[i].Y()) {
          ++cnt;
        }
      } else if (segment_[i - 1].CrossesSegment(segment) &&
                 !((segment.ContainsPoint(points[i + 1])))) {
        ++cnt;
      }
    }
    if (flag) {
      return flag;
    }
    return cnt % 2;
  }

  bool Polygon::CrossesSegment(const Segment& segmnet) const {
    for (int i = 0; i < size_; ++i) {
      if (segment_[i].CrossesSegment(segmnet)) {
        return true;
      }
    }
    return false;
  }

  std::string Polygon::ToString() const {
    std::string str = "Polygon(";
    for (int i = 0; i < size_ - 1; ++i) {
      str += point_[i].ToString() + ", ";
    }
    str += point_[size_ - 1].ToString() + ")";
    return str;
  }
}