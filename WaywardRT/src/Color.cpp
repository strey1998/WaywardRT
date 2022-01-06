// WaywardRT/WaywardRT/src/Color.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Color.h"

#include <iomanip>
#include <ostream>
#include <stdexcept>

namespace WaywardRT {

Color::Color(float r, float g, float b) : r(r), g(g), b(b) { }

Color Color::lerp(const Color& other, double t) const {
  if (t < 0.0 || t > 1.0) throw std::out_of_range(
    "Linear interpolation parameter must be between 0.0 and 1.0 (inclusive)");

  return Color(
    (1.0-t)*r + t*other.r,
    (1.0-t)*g + t*other.g,
    (1.0-t)*b + t*other.b);
}

std::ostream& operator<<(std::ostream& os, const Color& v) {
  return os << std::setprecision(2)
    << "Color("
    << v.r << ", "
    << v.g << ", "
    << v.b << ")";
}

}  // namespace WaywardRT
