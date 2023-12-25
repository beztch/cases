#include "../segment.h"
#include "../vector.h"
#include "../line.h"

namespace geometry {
Segment::Segment(Point a, Point b) : a_(a), b_(b) {
}

Point Segment::GetA() const {
  return a_;
}

Point Segment::GetB() const {
  return b_;
}

void Segment::SetA(Point& point) {
  a_ = point;
}

void Segment::SetB(Point& point) {
  b_ = point;
}

double Segment::Length() {
  Vector napr = Vector(GetB().GetX() - GetA().GetX(), GetB().GetY() - GetA().GetY());
  return napr.Length();
}

double Segment::Distance(const Point& point) const {
  if (Scal(Vector(a_, point), Vector(a_, b_)) <= 0) {
    return Segment(a_, point).Length();
  }
  if (Scal(Vector(b_, point), Vector(b_, a_)) <= 0) {
    return Segment(b_, point).Length();
  }
  return Line(a_, b_).Distance(point);
}

bool Segment::ContainsPoint(const Point& point) const {
  if (GetA() == GetB()) {
    return (GetA() == point);
  }
  return point.CrossesSegment(*this);
}

Segment& Segment::Move(const Vector& vector) {
  SetA(GetA().Move(vector));
  SetB(GetB().Move(vector));
  return *this;
}

bool Segment::CrossesSegment(const Segment& s) const {
  if ((GetA() == GetB()) || (s.GetB() == s.GetA())) {
    return (s.ContainsPoint(GetA()) || ContainsPoint(s.GetA()));
  }
  if (s.ContainsPoint(GetA()) || s.ContainsPoint(GetB()) || ContainsPoint(s.GetA()) ||
    ContainsPoint(s.GetB())) {
    return true;
  }
  Vector napr_1 = Vector(GetA(), GetB());
  Vector napr_2 = Vector(s.GetA(), s.GetB());
  Vector vector_ac = Vector(GetA(), s.GetA());
  Vector vector_ad = Vector(GetA(), s.GetB());
  Vector vector_ca = Vector(s.GetA(), GetA());
  Vector vector_cb =  Vector(s.GetA(), GetB());
  return (Kos(napr_1, vector_ac) * Kos(napr_1, vector_ad) < 0 &&
          Kos(napr_2, vector_ca) * Kos(napr_2, vector_cb) < 0);
}

Segment* Segment::Clone() const {
  auto clone = new Segment(GetA(), GetB());
  return clone;
}

std::string Segment::ToString() const {
  std::string str = "Segment(" + GetA().ToString() + ", " + GetB().ToString() + ")";
  return str;
}
}