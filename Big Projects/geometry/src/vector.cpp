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
  //VECTOR
  Vector::Vector() : x_(0), y_(0) {
  }

  Vector::Vector(const int& x, const int& y) : x_(x), y_(y) {
  }

  Vector::Vector(const Point& first, const Point& second) : x_(second.X() - first.X()), y_(second.Y() - first.Y()) {
  }

  Vector::Vector(const Point& point) : x_(point.X()), y_(point.Y()) {
  }

  int Vector::X() const {
    return x_;
  }

  int Vector::Y() const {
    return y_;
  }

  int Vector::Len2() const {
    return x_ * x_ + y_ * y_;
  }

  std::string Vector::ToString() const {
    return "Vector(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
  }

  Vector operator+(const Vector& first, const Vector& second) {
    return Vector(first.X() + second.X(), first.Y() + second.Y());
  }

  Vector operator+(const Vector& first) {
    return first;
  }
  
  Vector& operator+=(Vector& first, const Vector& second) {
    first.x_ += second.x_;
    first.y_ += second.y_;
    return first;
  }

  Vector operator-(const Vector& first, const Vector& second) {
    return Vector(first.X() - second.X(), first.Y() - second.Y());
  }

  Vector operator-(const Vector& first) {
    return Vector(-first.X(), -first.Y());
  }

  Vector& operator-=(Vector& first, const Vector& second) {
    first.x_ -= second.x_;
    first.y_ -= second.y_;
    return first;
  }

  Vector operator*(const Vector& first, const int& a) {
    return Vector(first.X() * a, first.Y() * a);
  }

  Vector operator*(const int& a, const Vector& first) {
    return Vector(first.X() * a, first.Y() * a);
  }

  Vector& operator*=(Vector& first, const int& a) {
    first.x_ *= a;
    first.y_ *= a;
    return first;
  }

  bool operator==(const Vector& first, const Vector& second) {
    return first.x_ * second.y_ == first.y_ * second.x_;
  }

  bool operator!=(const Vector& first, const Vector& second) {
  return !(first == second);
  }

  int DotProduct(const Vector& first, const Vector& second) {
    return first.X() * second.X() + first.Y() * second.Y();
  }

  int CrossProduct(const Vector& first, const Vector& second) {
    return first.X() * second.Y() - second.X() * first.Y();
  }
}