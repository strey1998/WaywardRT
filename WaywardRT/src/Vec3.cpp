// WaywardRT/WaywardRT/src/Vec.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Vec3.h"

#include <cmath>
#include <iomanip>
#include <ostream>

#include "WaywardRT/util.h"

namespace WaywardRT {

Vec3 Vec3::random_unit() {
  double theta = random_double(0.0, 2*pi);
  double cosPhi = random_double(-1.0, 1.0);
  double sinPhi = sin(acos(cosPhi));
  double sinTheta = sin(theta);
  double cosTheta = cos(theta);

  return Vec3(
    sinPhi * cosTheta,
    sinPhi * sinTheta,
    cosPhi);
}

Vec3 Vec3::random_in_unit_sphere() {
  return random_double()*random_unit();
}

// TODO(TS): This is probably much slower than it needs to be
Vec3 Vec3::random_in_unit_disk() {
  Vec3 unit = random_unit();
  Vec3 unit_in_disk(unit.x, unit.y, 0);
  return random_double()*unit_in_disk.e();
}

Vec3::Vec3() : x(0.0), y(0.0), z(0.0) { }

Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) { }

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

Vec3 Vec3::refract(const Vec3& n, double e) const {
  double cosTheta = fmin(-(*this)*n, 1.0);
  Vec3 r_out_perp = e * ((*this) + cosTheta*n);
  Vec3 r_out_par = -sqrt(fabs(1.0 - r_out_perp.len_sq())) * n;
  return r_out_perp + r_out_par;
}

double& Vec3::operator[](int index) {
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
  return *this + (-other);
}

double Vec3::operator*(const Vec3& other) const noexcept {
  return x*other.x + y*other.y + z*other.z;
}

Vec3 Vec3::operator*(double other) const noexcept {
  return Vec3(x*other, y*other, z*other);
}

Vec3 operator*(double a, const Vec3& v) { return v*a; }

Vec3 Vec3::operator/(double other) const noexcept {
  return Vec3(x*(1/other), y*(1/other), z*(1/other));
}

Vec3 Vec3::cross(const Vec3& other) const noexcept {
  return Vec3(
    y*other.z - z*other.y,
    z*other.x - x*other.z,
    x*other.y - y*other.x);
}

Vec3 cross(const Vec3& v1, const Vec3& v2) noexcept {
  return v1.cross(v2);
}

Vec3& Vec3::operator+=(const Vec3& other) noexcept {
  *this = *this + other; return *this;
}

Vec3& Vec3::operator-=(const Vec3& other) noexcept {
  *this = *this - other; return *this;
}

Vec3& Vec3::operator*=(double other) noexcept {
  *this = *this * other; return *this;
}

Vec3& Vec3::operator/=(double other) noexcept {
  *this = *this / other; return *this;
}

bool Vec3::operator==(const Vec3& other) const noexcept {
  return ((*this - other).len() < pow(10, -DOUBLE_PRECISION));
}

bool Vec3::operator!=(const Vec3& other) const noexcept {
  return !(*this == other);
}

double Vec3::len() const { return sqrt(len_sq()); }
double Vec3::len_sq() const { return (*this)*(*this); }

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
  return os << std::setprecision(6)
            << "Vec3("
            << v.x << ", "
            << v.y << ", "
            << v.z << ")";
}

}  // namespace WaywardRT
