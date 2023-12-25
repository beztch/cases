#pragma once
#include "i_shape.h"
#include "point.h"

namespace geometry {

class Ray : public IShape {
 private:
  Point a_;
  Point b_;

 public:
  Ray() = default;
  Ray(Point a, Point b);
  void SetA(Point&);
  void SetB(Point&);
  Point GetA() const;
  Point GetB() const;
  Ray& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Ray* Clone() const override;
  std::string ToString() const override;
};

}
