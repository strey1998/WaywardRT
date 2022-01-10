// WaywardRT/WaywardRT/src/Box.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Objects/Box.h"

#include "WaywardRT/Objects/Rectangle.h"

namespace WaywardRT {

Box::Box(const Vec3& p0, const Vec3& p1, std::shared_ptr<Material> material)
    : m_P0(p0), m_P1(p1) {
  m_Sides.add(std::make_shared<RectangleXY>(
    m_P0.x, m_P1.x, m_P0.y, m_P1.y, m_P0.z, material));
  m_Sides.add(std::make_shared<RectangleXY>(
    m_P0.x, m_P1.x, m_P0.y, m_P1.y, m_P1.z, material));

  m_Sides.add(std::make_shared<RectangleXZ>(
    m_P0.x, m_P1.x, m_P0.y, m_P0.z, m_P1.z, material));
  m_Sides.add(std::make_shared<RectangleXZ>(
    m_P0.x, m_P1.x, m_P1.y, m_P0.z, m_P1.z, material));

  m_Sides.add(std::make_shared<RectangleYZ>(
    m_P0.x, m_P0.y, m_P1.y, m_P0.z, m_P1.z, material));
  m_Sides.add(std::make_shared<RectangleYZ>(
    m_P1.x, m_P0.y, m_P1.y, m_P0.z, m_P1.z, material));
}

bool Box::hit(
    const Ray& r,
    real t_min,
    real t_max,
    HitRecord& rec) const {
  return m_Sides.hit(r, t_min, t_max, rec);
}

bool Box::bounding_box(real t_min, real t_max, BoundingBox& box) const {
  return m_Sides.bounding_box(t_min, t_max, box);
}

}  // namespace WaywardRT
