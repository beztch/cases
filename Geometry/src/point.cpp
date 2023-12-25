#include "../point.h"
#include "../vector.h"
#include "../segment.h"

namespace geometry {

Point::Point(int64_t x, int64_t y) : x_(x), y_(y) {
}

int64_t Point::GetX() const {
  return x_;
}

int64_t Point::GetY() const {
  return y_;
}

void Point::SetX(int64_t x_new) {
  x_ = x_new;
}

void Point::SetY(int64_t y_new) {
  y_ = y_new;
}

Point &Point::Move(const Vector &vector) {
  SetX(GetX() + vector.GetX());
  SetY(GetY() + vector.GetY());
  return *this;
}

bool Point::ContainsPoint(const Point &point) const {
  return (GetX() == point.GetX() && GetY() == point.GetY());
}

Vector operator-(const Point &a, const Point &b) {
  return Vector(a.GetX() - b.GetX(), a.GetY() - b.GetY());
}

Point &Point::operator=(Point point) {
  if (ContainsPoint(point)) {
    return *this;
  }
  SetX(point.GetX());
  SetY(point.GetY());
  return *this;
}

bool Point::CrossesSegment(const Segment &segment) const {
  Vector first = Vector(segment.GetA(), *this);
  Vector second = Vector(segment.GetB(), *this);
  Vector napr = Vector(segment.GetA(), segment.GetB());
  return (Kos(first, napr) == 0 && Scal(napr, first) >= 0 && Scal(-napr, second) >= 0);
}

Point *Point::Clone() const {
  auto copy = new Point(GetX(), GetY());
  return copy;
}

bool Point::operator==(const Point &point) const {
  return (GetX() == point.GetX() && GetY() == point.GetY());
}

bool Point::operator!=(const Point &point) const {
  return (GetX() != point.GetX() || GetY() != point.GetY());
}

std::string Point::ToString() const {
  std::string str = "Point(" + std::to_string(GetX()) + ", " + std::to_string(GetY()) + ")";
  return str;
}
}