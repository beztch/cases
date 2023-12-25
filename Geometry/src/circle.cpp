#include "../circle.h"
#include "../segment.h"

namespace geometry {

Circle::Circle(Point point, int64_t r) : o_(point), r_(r) {
}

Point Circle::GetCenter() const {
  return o_;
}

int64_t Circle::GetRadius() const {
  return r_;
}

void Circle::SetCenter(Point point) {
  o_ = point;
}

void Circle::SetRadius(int64_t r) {
  r_ = r;
}

bool Circle::ContainsPoint(const Point &point) const {
  Vector vector = Vector(point, o_);
  return (double(r_) >= vector.Length());
}

bool Circle::CrossesSegment(const Segment &segment) const {
  double r_a = Vector(o_, segment.GetA()).Length();
  double r_b = Vector(o_, segment.GetB()).Length();
  return (segment.Distance(o_) <= r_ && (r_a >= r_ || r_b >= r_));
}

Circle &Circle::Move(const Vector &vector) {
  SetCenter(GetCenter().Move(vector));
  return *this;
}

Circle *Circle::Clone() const {
  auto clone = new Circle(GetCenter(), GetRadius());
  return clone;
}

std::string Circle::ToString() const {
  std::string str = "Circle(" + o_.ToString() + ", " + std::to_string(r_) + ")";
  return str;
}
}