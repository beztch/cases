#pragma once
#include "point.h"
#include "i_shape.h"

namespace geometry {
class Segment : public IShape {
 private:
  Point a_;
  Point b_;

 public:
  Segment() = default;
  Segment(Point a, Point b);
  Point GetA() const;
  Point GetB() const;
  void SetA(Point&);
  void SetB(Point&);
  double Length();
  double Distance(const Point&) const;
  Segment& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Segment* Clone() const override;
  std::string ToString() const override;
};
}