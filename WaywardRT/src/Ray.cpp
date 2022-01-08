// WaywardRT/WaywardRT/src/Ray.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Ray.h"

#include "WaywardRT/util.h"

namespace WaywardRT {

Ray::Ray(const Vec3& origin, const Vec3& direction, real time)
  : m_Origin(origin), m_Direction(direction), m_Time(time) { }

const Vec3& Ray::origin() const { return m_Origin; }
const Vec3& Ray::direction() const { return m_Direction; }
real Ray::time() const { return m_Time; }

Vec3 Ray::at(real t) const {
  return m_Origin + t*m_Direction;
}

std::ostream& operator<<(std::ostream& os, const Ray& r) {
  return os << "Ray(" << r.origin() << ", " << r.direction() << ")";
}

}  // namespace WaywardRT
