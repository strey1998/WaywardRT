// WaywardRT/WaywardRT/src/Vec.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Vec3.h"

#include <cmath>
#include <iomanip>
#include <ostream>
#include <sstream>

#include "WaywardRT/util.h"

namespace WaywardRT {

Vec3 Vec3::random_unit() {
  real theta = random_real(0.0, 2*pi);
  real cosPhi = random_real(-1.0, 1.0);
  real sinPhi = sin(acos(cosPhi));
  real sinTheta = sin(theta);
  real cosTheta = cos(theta);

  return Vec3(
    sinPhi * cosTheta,
    sinPhi * sinTheta,
    cosPhi);
}

Vec3 Vec3::random_in_unit_sphere() {
  return pow(random_real(), 1/3.0)*random_unit();
}

Vec3 Vec3::random_in_unit_disk() {
  real r = sqrt(random_real());
  real theta = random_real(0, 2*pi);
  return r*Vec3(cos(theta), sin(theta), 0);
}

Vec3::Vec3() : x(0.0), y(0.0), z(0.0) { }

Vec3::Vec3(real x, real y, real z) : x(x), y(y), z(z) { }

Vec3::Vec3(const Vec3& other) : x(other.x), y(other.y), z(other.z) { }

Vec3& Vec3::operator=(const Vec3& other) {
  x = other.x;
  y = other.y;
  z = other.z;
  return *this;
}

Vec3 Vec3::e() const { return *this / len(); }
Vec3& Vec3::normalize() noexcept { return (*this /= len()); }
Vec3 Vec3::reflect(const Vec3& n) const { return (*this) - 2*((*this) * n)*n; }

Vec3 Vec3::refract(const Vec3& n, real e) const {
  real cosTheta = fmin(-(*this)*n, 1.0);
  Vec3 r_out_perp = e * ((*this) + cosTheta*n);
  Vec3 r_out_par = -sqrt(fabs(1.0 - r_out_perp.len_sq())) * n;
  return r_out_perp + r_out_par;
}

real& Vec3::operator[](int index) {
  switch (index) {
    case 0:
      return x;
      break;
    case 1:
      return y;
      break;
    case 2:
      return z;
      break;
    default:
      throw std::out_of_range("Vector index must be 0 (x); 1 (y); or 2 (z)");
  }
}

const real& Vec3::operator[](int index) const {
  switch (index) {
    case 0:
      return x;
      break;
    case 1:
      return y;
      break;
    case 2:
      return z;
      break;
    default:
      throw std::out_of_range("Vector index must be 0 (x); 1 (y); or 2 (z)");
  }
}

Vec3 Vec3::operator-() const { return Vec3(-x, -y, -z); }

Vec3 Vec3::operator+(const Vec3& other) const noexcept {
  return Vec3(x+other.x, y+other.y, z+other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const noexcept {
  return Vec3(x-other.x, y-other.y, z-other.z);
}

real Vec3::operator*(const Vec3& other) const noexcept {
  return x*other.x + y*other.y + z*other.z;
}


Vec3 Vec3::operator*(real other) const noexcept {
  return Vec3(x*other, y*other, z*other);
}

Vec3 Vec3::operator/(real other) const noexcept {
  return Vec3(x*(1/other), y*(1/other), z*(1/other));
}

Vec3 Vec3::cross(const Vec3& other) const noexcept {
  return Vec3(
    y*other.z - z*other.y,
    z*other.x - x*other.z,
    x*other.y - y*other.x);
}

Vec3& Vec3::operator+=(const Vec3& other) noexcept {
  *this = *this + other; return *this;
}

Vec3& Vec3::operator-=(const Vec3& other) noexcept {
  *this = *this - other; return *this;
}

Vec3& Vec3::operator*=(real other) noexcept {
  *this = *this * other; return *this;
}

Vec3& Vec3::operator/=(real other) noexcept {
  *this = *this / other; return *this;
}

std::string Vec3::to_string() const noexcept {
  std::stringstream ss;
  ss << std::setprecision(3) << std::fixed
     << "(" << x << ", " << y << ", " << z << ")";
  return ss.str();
}

bool Vec3::operator==(const Vec3& other) const noexcept {
  const real len_diff = (*this - other).len();
  const real divisor = sqrt(len_sq() + other.len_sq());
  if (divisor == 0) return true;
  return len_diff/divisor < pow(10, -FLOATING_POINT_EQUALITY_PRECISION);
}

bool Vec3::operator!=(const Vec3& other) const noexcept {
  return !(*this == other);
}

real Vec3::len() const { return sqrt(len_sq()); }
real Vec3::len_sq() const { return (*this)*(*this); }

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
  return os << v.to_string();
}

}  // namespace WaywardRT
