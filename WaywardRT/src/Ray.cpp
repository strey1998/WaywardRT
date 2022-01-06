// WaywardRT/WaywardRT/src/Ray.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Ray.h"

namespace WaywardRT {

Ray::Ray(const Vec3& origin, const Vec3& direction)
  : m_Origin(origin), m_Direction(direction) { }

const Vec3& Ray::origin() const { return m_Origin; }
const Vec3& Ray::direction() const { return m_Direction;}

Vec3 Ray::at(double t) const {
  return m_Origin + t*m_Direction;
}

std::ostream& operator<<(std::ostream& os, const Ray& r) {
  return os << "Ray(" << r.origin() << ", " << r.direction() << ")";
}

}  // namespace WaywardRT
