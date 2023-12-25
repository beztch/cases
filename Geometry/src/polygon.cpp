#include "../polygon.h"
#include "../segment.h"

namespace geometry {
Polygon::Polygon(const std::vector<Point> &points) {
  for (size_t i = 0; i < points.size(); ++i) {
    polygon_.push_back(points[i]);
  }
}

Polygon &Polygon::Move(const Vector &vector) {
  for (size_t i = 0; i < polygon_.size(); ++i) {
    polygon_[i].Move(vector);
  }
  return *this;
}

Polygon *Polygon::Clone() const {
  auto clone = new Polygon(polygon_);
  return clone;
}

bool Polygon::ContainsPoint(const Point &point) const {
  Point far_away(point.GetX() + 1000000, point.GetY() + 1);
  Segment almost_ray(point, far_away);
  size_t k = 0;
  for (size_t i = 0; i < polygon_.size(); ++i) {
    Segment tmp(polygon_[i], polygon_[(i + 1) % polygon_.size()]);
    if (tmp.ContainsPoint(point)) {
      return true;
    }
    if (almost_ray.CrossesSegment(tmp)) {
      k++;
    }
  }
  return ((k % 2) == 1);
}

bool Polygon::CrossesSegment(const Segment &segment) const {
  for (size_t i = 0; i < polygon_.size(); ++i) {
    Segment tmp(polygon_[i], polygon_[(i + 1) % polygon_.size()]);
    if (tmp.CrossesSegment(segment)) {
      return true;
    }
  }
  return false;
}

std::string Polygon::ToString() const {
  std::string str = "Polygon(";
  for (size_t i = 0; i < polygon_.size(); ++i) {
    str += polygon_[i].ToString();
    if (polygon_[i] != *(polygon_.end() - 1)) {
      str += ", ";
    }
  }
  str += ")";
  return str;
}
}