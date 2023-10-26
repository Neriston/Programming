#include <iostream>
#include <iomanip>
#include <cmath>

struct Point {
  int x = 0;
  int y = 0;
};

struct Vector {
  Point a;
  Point b;
  int x = 0;
  int y = 0;
};

float Len(const Vector& vector) {
  return sqrt(vector.x * vector.x + vector.y * vector.y);
}

Vector& SumVector(const Vector& first_vector, const Vector& second_vector, Vector& sum_vector) {
  sum_vector.x = first_vector.x + second_vector.x;
  sum_vector.y = first_vector.y + second_vector.y;
  return sum_vector;
}

float ScalarProduct(const Vector& first_vector, const Vector& second_vector) {
  return first_vector.x * second_vector.x + first_vector.y * second_vector.y;
}

float LenVectorProduct(const Vector& first_vector, const Vector& second_vector) {
  return first_vector.x * second_vector.y - second_vector.x * first_vector.y;
}

float AreaTriangle(const Vector& first_vector, const Vector& second_vector) {
  return fabs(LenVectorProduct(first_vector, second_vector) / 2);
}

std::istream& operator>>(std::istream& io, Vector& vector) {
  io >> vector.a.x >> vector.a.y >> vector.b.x >> vector.b.y;
  vector.x = vector.b.x - vector.a.x;
  vector.y = vector.b.y - vector.a.y;
  return io;
}

int main() {
  Vector first_vector;
  Vector second_vector;
  std::cin >> first_vector >> second_vector;
  Vector sum_vector;
  std::cout << std::fixed << std::setprecision(6) << Len(first_vector) << ' ' << Len(second_vector) << '\n';
  SumVector(first_vector, second_vector, sum_vector);
  std::cout << 1.0 * sum_vector.x << ' ' << 1.0 * sum_vector.y << '\n';
  std::cout << ScalarProduct(first_vector, second_vector) << ' ' << LenVectorProduct(first_vector, second_vector)
            << '\n';
  std::cout << AreaTriangle(first_vector, second_vector);
}