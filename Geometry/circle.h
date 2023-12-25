#pragma once
#include "i_shape.h"
#include "point.h"
namespace geometry {

class Circle : public IShape {
 private:
  Point o_;
  int64_t r_;

 public:
  Circle() = default;
  Circle(Point, int64_t);
  Point GetCenter() const;
  int64_t GetRadius() const;
  void SetCenter(Point);
  void SetRadius(int64_t);
  Circle& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Circle* Clone() const override;
  std::string ToString() const override;
};

}
