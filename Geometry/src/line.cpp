#include "../line.h"
#include "../point.h"
#include "../segment.h"
#include "../vector.h"

namespace geometry {

Line::Line(Point a, Point b) : a_(a), b_(b) {
}

Point Line::GetA() const {
  return a_;
}

Point Line::GetB() const {
  return b_;
}

void Line::SetA(Point &point) {
  a_ = point;
}

void Line::SetB(Point &point) {
  b_ = point;
}

Line &Line::Move(const Vector &vector) {
  SetA(GetA().Move(vector));
  SetB(GetB().Move(vector));
  return *this;
}

bool Line::ContainsPoint(const Point &point) const {
  Vector first = Vector(a_, b_);
  Vector second = Vector(a_, point);
  return (Kos(first, second) == 0);
}

bool Line::CrossesSegment(const Segment &segment) const {
  Vector napr = Vector(GetA(), GetB());
  Vector first = Vector(segment.GetA(), GetA());
  Vector second = Vector(segment.GetB(), GetA());
  return (Kos(napr, first) * Kos(napr, second) <= 0);
}

double Line::Distance(const Point &point) const {
  if (ContainsPoint(point)) {
    return 0;
  }
  Vector vector(point, GetA());
  Vector napr(GetA(), GetB());
  return (std::abs(double(Kos(vector, napr)) / napr.Length()));
}

Line *Line::Clone() const {
  auto tmp = new Line(GetA(), GetB());
  return tmp;
}

std::string Line::ToString() const {
  int64_t a = GetB().GetY() - GetA().GetY();
  int64_t b = GetA().GetX() - GetB().GetX();
  int64_t c = GetB().GetX() * GetA().GetY() - GetA().GetX() * GetB().GetY();
  std::string str =
      "Line(" + std::to_string(a) + ", " + std::to_string(b) + ", " + std::to_string(c) + ")";
  return str;
}
}