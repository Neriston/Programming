#ifndef VECTOR_H
#define VECTOR_H
namespace geometry {
  class Point;
  class Line;
  class Ray;
  class Segment;
  class Polygon;
  class Circle;
  class Vector {
  protected:
    int x_, y_;

  public:
    Vector();
    Vector(const int&, const int&);
    explicit Vector(const Point&);
    Vector(const Point&, const Point&);
    int X() const;
    int Y() const;
    int Len2() const;
    std::string ToString() const;
    friend Vector operator+(const Vector&, const Vector&);
    friend Vector operator+(const Vector&);
    friend Vector& operator+=(Vector&, const Vector&);
    friend Vector operator-(const Vector&, const Vector&);
    friend Vector operator-(const Vector&);
    friend Vector& operator-=(Vector&, const Vector&);
    friend Vector operator*(const Vector&, const int&);
    friend Vector operator*(const int&, const Vector&);
    friend Vector& operator*=(Vector&, const int&);
    friend bool operator==(const Vector&, const Vector&);
    friend bool operator!=(const Vector&, const Vector&);
    friend int DotProduct(const Vector&, const Vector&);
    friend int CrossProduct(const Vector&, const Vector&);
  };
  class IShape {
  public:
    virtual IShape& Move(const Vector&) = 0;
    virtual bool ContainsPoint(const Point&) const = 0;
    virtual bool CrossesSegment(const Segment&) const = 0;
    virtual IShape* Clone() const = 0;
    virtual ~IShape() = 0;
    virtual std::string ToString() const = 0;
  };
}
#endif