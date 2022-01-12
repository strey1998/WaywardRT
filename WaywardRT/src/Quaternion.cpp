// WaywardRT/WaywardRT/src/Quaternion.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Quaternion.h"

#include <cmath>
#include <iomanip>
#include <ostream>
#include <sstream>

#include "WaywardRT/util.h"

namespace WaywardRT {

Quaternion::Quaternion() : Quaternion(0, 0, 0, 0) { }

Quaternion::Quaternion(const Vec3& v) : Quaternion(0, v) { }

Quaternion::Quaternion(real x, const Vec3& v)
  : m_RealPart(x), m_VectorPart(v) { }

Quaternion::Quaternion(real a, real b, real c, real d)
  : m_RealPart(a), m_VectorPart(Vec3(b, c, d)) { }

Quaternion::Quaternion(const Quaternion& other)
  : m_RealPart(other.m_RealPart), m_VectorPart(other.m_VectorPart) { }

Quaternion& Quaternion::operator=(const Quaternion& other) {
  this->m_RealPart = other.m_RealPart;
  this->m_VectorPart = other.m_VectorPart;
  return *this;
}

real& Quaternion::operator[](uint8_t index) {
  if (index == 0) return m_RealPart;
  return m_VectorPart[index-1];
}

const real& Quaternion::operator[](uint8_t index) const {
  if (index == 0) return m_RealPart;
  return m_VectorPart[index-1];
}

real Quaternion::real_part() const noexcept { return m_RealPart; }

const Vec3& Quaternion::vector_part() const noexcept { return m_VectorPart; }


Quaternion& Quaternion::normalize() noexcept {
  real norm_ = this->norm();
  this->m_RealPart /= norm_;
  this->m_VectorPart /= norm_;  // TODO(TS): This is probably bad (copy?)
  return *this;
}

Quaternion Quaternion::normalized() const noexcept {
  real norm_ = this->norm();
  return Quaternion(m_RealPart / norm_, m_VectorPart / norm_);
}

Quaternion Quaternion::inverse() const {
  Quaternion result = conjugate();
  result /= norm_sq();
  return result;
}

Quaternion Quaternion::conjugate() const {
  return Quaternion(m_RealPart, -m_VectorPart);
}

real Quaternion::norm() const {
  return sqrt(norm_sq());
}

real Quaternion::norm_sq() const {
  return m_RealPart*m_RealPart + m_VectorPart*m_VectorPart;
}

Vec3 Quaternion::apply_rotation(const Vec3& v) const {
  return ((*this)*v*this->conjugate()).to_Vec3();
}

Vec3 Quaternion::apply_inverse_rotation(const Vec3& v) const {
  return (this->conjugate()*v*(*this)).to_Vec3();
}

Quaternion Quaternion::operator-() const {
  return Quaternion(-m_RealPart, -m_VectorPart);
}

Quaternion Quaternion::operator+(const Quaternion& other) const noexcept {
  return Quaternion(this->m_RealPart + other.m_RealPart,
                    this->m_VectorPart + other.m_VectorPart);
}

Quaternion Quaternion::operator-(const Quaternion& other) const noexcept {
  return Quaternion(this->m_RealPart - other.m_RealPart,
                    this->m_VectorPart - other.m_VectorPart);
}

Quaternion Quaternion::operator*(const Quaternion& other) const noexcept {
  return Quaternion(this->m_RealPart*other.m_RealPart
                      - this->m_VectorPart*other.m_VectorPart,
                    this->m_RealPart*other.m_VectorPart
                      + other.m_RealPart*this->m_VectorPart
                      + cross(this->m_VectorPart, other.m_VectorPart));
}

Quaternion Quaternion::operator*(real other) const noexcept {
  return Quaternion(other*m_RealPart, other*m_VectorPart);
}

Quaternion Quaternion::operator/(real other) const noexcept {
  return Quaternion(m_RealPart/other, m_VectorPart/other);
}

Quaternion Quaternion::operator*(const Vec3& other) const noexcept {
  return (*this)*Quaternion(other);
}

Quaternion& Quaternion::operator+=(const Quaternion& other) noexcept {
  this->m_RealPart += other.m_RealPart;
  this->m_VectorPart += other.m_VectorPart;
  return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& other) noexcept {
  m_RealPart -= other.m_RealPart;
  m_VectorPart -= other.m_VectorPart;
  return *this;
}

Quaternion& Quaternion::operator*=(real other) noexcept {
  m_RealPart *= other;
  m_VectorPart *= other;
  return *this;
}

Quaternion& Quaternion::operator/=(real other) noexcept {
  m_RealPart /= other;
  m_VectorPart /= other;
  return *this;
}

std::string Quaternion::to_string() const noexcept {
  std::stringstream ss;
  ss << std::setprecision(3) << std::fixed << "("
     << m_RealPart << ", "
     << m_VectorPart.x << ", "
     << m_VectorPart.y << ", "
     << m_VectorPart.z << ")";
  return ss.str();
}

bool Quaternion::operator==(const Quaternion& other) const noexcept {
  return (fabs(this->m_RealPart - other.m_RealPart)
            < FLOATING_POINT_EQUALITY_PRECISION)
         && (this->m_VectorPart == other.m_VectorPart);
}
bool Quaternion::operator!=(const Quaternion& other) const noexcept {
  return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Quaternion& v) {
    return os << v.to_string();
}

Vec3 Quaternion::to_Vec3() {
  return m_VectorPart;
}

}  // namespace WaywardRT
