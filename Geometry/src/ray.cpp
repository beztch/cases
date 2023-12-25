#include "../ray.h"
#include "../point.h"
#include "../segment.h"

namespace geometry {

Ray::Ray(Point a, Point b) : a_(a), b_(b) {
}

Point Ray::GetA() const {
  return a_;
}

Point Ray::GetB() const {
  return b_;
}

void Ray::SetA(Point &a) {
  a_ = a;
}

void Ray::SetB(Point &point) {
  b_ = point;
}


Ray &Ray::Move(const Vector &vector) {
  SetA(GetA().Move(vector));
  SetB(GetB().Move(vector));
  return *this;
}

Ray *Ray::Clone() const {
  auto clone = new Ray(GetA(), GetB());
  return clone;
}

bool Ray::ContainsPoint(const Point &point) const {
  Vector napr = Vector(GetA(), GetB());
  Vector to_point = Vector(GetA(), point);
  return (Kos(napr, to_point) == 0 && Scal(napr, to_point) >= 0);
}

bool Ray::CrossesSegment(const Segment &segment) const {
  if (segment.ContainsPoint(GetA()) || segment.ContainsPoint(GetB()) ||
      ContainsPoint(segment.GetA()) || ContainsPoint(segment.GetB())) {
    return true;
  }
  Vector napr = Vector(GetA(), GetB());
  Vector vector_ac = Vector(GetA(), segment.GetA());
  Vector vector_ad = Vector(GetA(), segment.GetB());
  Vector napr_segment = Vector(segment.GetA(), segment.GetB());
  return (Kos(napr, vector_ac) * Kos(napr, vector_ad) <= 0 &&
          Kos(-vector_ac, napr_segment) * Kos(napr, napr_segment) <= 0);
}


std::string Ray::ToString() const {
  Vector napr = Vector(GetA(), GetB());
  std::string str = "Ray(" + GetA().ToString() + ", Vector(" + std::to_string(napr.GetX()) +
                    ", " + std::to_string(napr.GetY()) + "))";
  return str;
}

}