#pragma once
#include "i_shape.h"
#include "vector.h"

namespace geometry {
class Point : public IShape {
 private:
  int64_t x_;
  int64_t y_;

 public:
  Point() = default;
  Point(int64_t x, int64_t y);
  int64_t GetX() const;
  int64_t GetY() const;
  void SetX(int64_t);
  void SetY(int64_t);
  friend Vector operator-(const Point &, const Point &);
  Point &operator=(Point);
  bool operator==(const Point &) const;
  bool operator!=(const Point &) const;
  Point &Move(const Vector &) override;
  bool ContainsPoint(const Point &) const override;
  bool CrossesSegment(const Segment &) const override;
  Point *Clone() const override;
  std::string ToString() const override;
};

}