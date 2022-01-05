// WaywardRT/WaywardRT/src/Vec.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Vec3.h"

#include <cmath>
#include <iomanip>
#include <ostream>

namespace WaywardRT {

Vec3::Vec3() : m_Data{0, 0, 0} { }

Vec3::Vec3(double x, double y, double z) : m_Data{x, y, z} { }

Vec3::Vec3(const Vec3& other) : m_Data{other.x(), other.y(), other.z()} { }

Vec3& Vec3::operator=(const Vec3& other) {
  m_Data[0] = other.x();
  m_Data[1] = other.y();
  m_Data[2] = other.z();
  return *this;
}

double Vec3::x() const { return m_Data[0]; }
double Vec3::y() const { return m_Data[1]; }
double Vec3::z() const { return m_Data[2]; }

Vec3 Vec3::e() const noexcept { return *this / len(); }
Vec3& Vec3::normalize() noexcept { return (*this /= len()); }

double& Vec3::operator[](int index) { return m_Data[index]; }

Vec3 Vec3::operator-() const { return Vec3(-x(), -y(), -z()); }

Vec3 Vec3::operator+(const Vec3& other) const noexcept {
  return Vec3(x()+other.x(), y()+other.y(), z()+other.z());
}

Vec3 Vec3::operator-(const Vec3& other) const noexcept {
  return *this + (-other);
}

double Vec3::operator*(const Vec3& other) const noexcept {
  return x()*other.x() + y()*other.y() + z()*other.z();
}

Vec3 Vec3::operator*(double other) const noexcept {
  return Vec3(x()*other, y()*other, z()*other);
}

Vec3 operator*(double a, const Vec3& v) { return v*a; }

Vec3 Vec3::operator/(double other) const noexcept {
  return Vec3(x()*(1/other), y()*(1/other), z()*(1/other));
}

Vec3 Vec3::cross(const Vec3& other) const noexcept {
  return Vec3(
    y()*other.z() - z()*other.y(),
    z()*other.x() - x()*other.z(),
    x()*other.y() - y()*other.x());
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
            << v.x() << ", "
            << v.y() << ", "
            << v.z() << ")";
}

}  // namespace WaywardRT
