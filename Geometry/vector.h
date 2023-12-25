#pragma once
#include <iostream>
#include <cmath>
#include "point.h"

namespace geometry {
class Vector {
 private:
  int64_t x_;
  int64_t y_;

 public:
  Vector() = default;
  Vector(int64_t x, int64_t y);
  Vector(Point a, Point b);
  int64_t GetX() const;
  int64_t GetY() const;
  double Length();
  friend int64_t Scal(Vector, Vector);
  friend int64_t Kos(Vector, Vector);
  friend Vector operator+(Vector, Vector);
  friend Vector operator-(Vector, Vector);
  friend Vector operator+(Vector);
  friend Vector operator-(Vector);
  friend Vector operator*(Vector, int64_t);
  friend Vector operator/(Vector, int64_t);
  friend Vector& operator+=(Vector&, Vector);
  friend Vector& operator-=(Vector&, Vector);
  friend Vector& operator*=(Vector&, int64_t);
  friend Vector& operator/=(Vector&, int64_t);
  friend bool operator==(Vector, Vector);
};

}