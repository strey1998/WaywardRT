// WaywardRT/WaywardRT/src/Color.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Color.h"

#include <cmath>
#include <iomanip>
#include <ostream>
#include <stdexcept>

#include "WaywardRT/util.h"

namespace WaywardRT {

Color::Color() : r(0.0), g(0.0), b(0.0) { }

Color::Color(float r, float g, float b) : r(r), g(g), b(b) { }

Color Color::lerp(const Color& other, double t) const {
  if (t < 0.0 || t > 1.0) throw std::out_of_range(
    "Linear interpolation parameter must be between 0.0 and 1.0 (inclusive)");

  return (1.0-t)*(*this) + other;
}

Color Color::exp(double e) const {
  return Color(
    pow(r, e),
    pow(g, e),
    pow(b, e));
}

Color Color::operator+(const Color& other) const {
  return Color(
    WaywardRT::clamp(r + other.r, 0.0, 1.0),
    WaywardRT::clamp(g + other.g, 0.0, 1.0),
    WaywardRT::clamp(b + other.b, 0.0, 1.0));
}

Color Color::operator-(const Color& other) const {
  return Color(
    WaywardRT::clamp(r - other.r, 0.0, 1.0),
    WaywardRT::clamp(g - other.g, 0.0, 1.0),
    WaywardRT::clamp(b - other.b, 0.0, 1.0));
}

Color Color::operator*(const Color& other) const {
  return Color(
    r * other.r,
    g * other.g,
    b * other.b
  );
}

Color Color::operator*(double other) const {
  return Color(
    WaywardRT::clamp(r*other, 0.0, 1.0),
    WaywardRT::clamp(g*other, 0.0, 1.0),
    WaywardRT::clamp(b*other, 0.0, 1.0));
}

Color operator*(double factor, const Color& color) {
  return color*factor;
}

Color Color::operator/(double other) const {
  return Color(r/other, g/other, b/other);
}

Color& Color::operator+=(const Color& other) {
  return (*this = *this + other);
}

Color& Color::operator-=(const Color& other) {
  return (*this = *this - other);
}

Color& Color::operator*=(double other) {
  return (*this = *this * other);
}

Color& Color::operator/=(double other) {
  return (*this = *this / other);
}


std::ostream& operator<<(std::ostream& os, const Color& v) {
  return os << std::setprecision(2)
    << "Color("
    << v.r << ", "
    << v.g << ", "
    << v.b << ")";
}

}  // namespace WaywardRT
