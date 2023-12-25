#pragma once

#include "i_shape.h"
#include "point.h"

namespace geometry {
class Line : public IShape {
  Point a_;
  Point b_;

 public:
  Line() = default;
  Line(Point, Point);
  Point GetA() const;
  Point GetB() const;
  void SetA(Point&);
  void SetB(Point&);
  double Distance(const Point&) const;
  Line& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Line* Clone() const override;
  std::string ToString() const override;
};

}