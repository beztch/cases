#pragma once
#include "point.h"
#include "i_shape.h"
#include <vector>

namespace geometry {

class Polygon : public IShape {
 public:
  std::vector<Point> polygon_;
  Polygon() = default;
  explicit Polygon(const std::vector<Point>&);
  Polygon& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Polygon* Clone() const override;
  std::string ToString() const override;
};

}