#include "../vector.h"
#include <cmath>

namespace geometry {
Vector::Vector(int64_t x, int64_t y) : x_(x), y_(y) {
}

Vector::Vector(Point a, Point b) : x_(b.GetX() - a.GetX()), y_(b.GetY() - a.GetY()) {
}

int64_t Vector::GetX() const {
  return x_;
}

int64_t Vector::GetY() const {
  return y_;
}

int64_t Scal(Vector vector_1, Vector vector_2) {
  return (vector_1.x_ * vector_2.x_ + vector_1.y_ * vector_2.y_);
}

int64_t Kos(Vector vector_1, Vector vector_2) {
  return (vector_1.x_ * vector_2.y_ - vector_1.y_ * vector_2.x_);
}

double Vector::Length() {
  return sqrt(x_ * x_ + y_ * y_);
}

Vector operator+(Vector vector_1, Vector vector_2) {
  int64_t x_new = vector_1.x_ + vector_2.x_;
  int64_t y_new = vector_1.y_ + vector_2.y_;
  return Vector(x_new, y_new);
}

Vector operator-(Vector vector_1, Vector vector_2) {
  int64_t x_new = vector_1.x_ - vector_2.x_;
  int64_t y_new = vector_1.y_ - vector_2.y_;
  return Vector(x_new, y_new);
}

Vector operator+(Vector vector) {
  return vector;
}

Vector operator-(Vector vector) {
  return (Vector(-vector.x_, -vector.y_));
}

Vector operator*(Vector vector, int64_t k) {
  return (Vector(vector.x_ * k, vector.y_ * k));
}

Vector operator/(Vector vector, int64_t k) {
  if (k == 0) {
    return Vector();
  }
  return (Vector(vector.x_ / k, vector.y_ / k));
}

Vector& operator+=(Vector& vector, Vector other) {
  vector = vector + other;
  return vector;
}

Vector& operator-=(Vector& vector, Vector other) {
  vector = vector - other;
  return vector;
}

Vector& operator*=(Vector& vector, int64_t k) {
  vector = vector * k;
  return vector;
}

Vector& operator/=(Vector& vector, int64_t k) {
  vector = vector / k;
  return vector;
}

bool operator==(Vector vector_1, Vector vector_2) {
  return (vector_1.x_ == vector_2.x_ && vector_1.y_ == vector_2.y_);
}
}