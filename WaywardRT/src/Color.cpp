// WaywardRT/WaywardRT/src/Color.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Color.h"

#include <cmath>
#include <iomanip>
#include <ostream>
#include <stdexcept>

namespace WaywardRT {

Color Color::Random() {
  return Color(random_real(), random_real(), random_real());
}

Color::Color() : r(0.0), g(0.0), b(0.0) { }

Color::Color(real r, real g, real b) : r(r), g(g), b(b) { }

Color Color::lerp(const Color& other, real t) const {
  if (t < 0.0 || t > 1.0) throw std::out_of_range(
    "Linear interpolation parameter must be between 0.0 and 1.0 (inclusive)");

  return (1.0-t)*(*this) + other;
}

Color Color::exp(real e) const {
  return Color(
    pow(r, e),
    pow(g, e),
    pow(b, e));
}

Color Color::clamped() const {
  return Color(
    clamp(r, 0.0, 1.0),
    clamp(g, 0.0, 1.0),
    clamp(b, 0.0, 1.0));
}

Color Color::operator+(const Color& other) const {
  return Color(
    r + other.r,
    g + other.g,
    b + other.b);
}

Color Color::operator-(const Color& other) const {
  return Color(
    r - other.r,
    g - other.g,
    b - other.b);
}

Color Color::operator*(const Color& other) const {
  return Color(
    r * other.r,
    g * other.g,
    b * other.b);
}

Color Color::operator*(real other) const {
  return Color(
    r * other,
    g * other,
    b * other);
}

Color Color::operator/(real other) const {
  return Color(r/other, g/other, b/other);
}

Color& Color::operator+=(const Color& other) {
  return (*this = *this + other);
}

Color& Color::operator-=(const Color& other) {
  return (*this = *this - other);
}

Color& Color::operator*=(real other) {
  return (*this = *this * other);
}

Color& Color::operator/=(real other) {
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
