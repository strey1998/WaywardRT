// WaywardRT/WaywardRT/src/Objects/Rectangle.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Objects/Rectangle.h"

#include "WaywardRT/log.h"
#include "WaywardRT/Ray.h"
#include "WaywardRT/Vec3.h"
#include "WaywardRT/util.h"

namespace WaywardRT {

Rectangle::Rectangle(Vec3 origin,
    Vec3 side1,
    Vec3 side2,
    std::shared_ptr<Material> material) : m_O(origin), m_Material(material) {
  m_U = side1.e();
  m_V = side2.e();
  m_UL = side1.len();
  m_VL = side2.len();
  m_N = cross(side1, side2).e();
}

std::shared_ptr<Material> Rectangle::material() const noexcept {
  return m_Material;
}

bool Rectangle::hit(
    const Ray& r,
    real t_min,
    real t_max,
    HitRecord& rec) const {
  real r_dot_n = m_N * r.direction();

  if (r_dot_n == 0) return false;  // Ray is parallel to plane, never hits

  real t = m_N*(m_O - r.origin()) / r_dot_n;

  if (t < t_min || t > t_max) return false;  // Outside t bounds

  Vec3 inf_hit = r.at(t);

  real hit_dot_u = (inf_hit - m_O) * m_U;
  real hit_dot_v = (inf_hit - m_O) * m_V;

  if (hit_dot_u < 0 || hit_dot_u > m_UL) return false;  // Outside u bounds
  if (hit_dot_v < 0 || hit_dot_v > m_VL) return false;  // Outside v boundss

  rec.point = inf_hit;
  rec.normal = r_dot_n > 0 ? -m_N : m_N;
  rec.material = m_Material;
  rec.t = t;
  rec.u = hit_dot_u / m_UL;
  rec.v = hit_dot_v / m_VL;

  return true;
}

bool Rectangle::bounding_box(real, real, BoundingBox& box) const {
  box.p0 = m_O;
  box.p1 = m_O + m_UL*m_U + m_VL*m_V;

  Vec3 v = box.p1 - box.p0;

  if (v.x == 0) {
    box.p0 -= Vec3(0.0001, 0, 0);
    box.p1 += Vec3(0.0001, 0, 0);
  }

  if (v.y == 0) {
    box.p0 -= Vec3(0, 0.0001, 0);
    box.p1 += Vec3(0, 0.0001, 0);
  }

  if (v.z == 0) {
    box.p0 -= Vec3(0, 0, 0.0001);
    box.p1 += Vec3(0, 0, 0.0001);
  }


  return true;
}

RectangleXY::RectangleXY(
  real x0, real x1,
  real y0, real y1,
  real z,
  std::shared_ptr<Material> material)
    : m_X0(x0), m_X1(x1),
      m_Y0(y0), m_Y1(y1),
      m_Z(z),
    m_Material(material) { }

std::shared_ptr<Material> RectangleXY::material() const noexcept {
  return m_Material;
}

bool RectangleXY::hit(
    const Ray& r,
    real t_min,
    real t_max,
    HitRecord& rec) const {
  if (r.direction().z == 0) return false;

  real t = (m_Z-r.origin().z) / r.direction().z;
  if (t < t_min || t > t_max) return false;

  real x = r.origin().x + t*r.direction().x;
  real y = r.origin().y + t*r.direction().y;
  if (x < m_X0 || x > m_X1) return false;
  if (y < m_Y0 || y > m_Y1) return false;

  rec.point = Vec3(x, y, m_Z);
  rec.normal = r.direction().z > 0 ? Vec3(0, 0, -1) : Vec3(0, 0, 1);
  rec.material = m_Material;
  rec.t = t;
  rec.u = (x-m_X0)/(m_X1-m_X0);
  rec.v = (y-m_Y0)/(m_Y1-m_Y0);

  return true;
}

bool RectangleXY::bounding_box(real, real, BoundingBox& box) const {
  box = BoundingBox(
    Vec3(m_X0, m_Y0, m_Z - 0.0001),
    Vec3(m_X1, m_Y1, m_Z + 0.0001));
  return true;
}

RectangleXZ::RectangleXZ(
  real x0, real x1,
  real y,
  real z0, real z1,
  std::shared_ptr<Material> material)
  : m_X0(x0), m_X1(x1),
    m_Y(y),
    m_Z0(z0), m_Z1(z1),
    m_Material(material) { }

std::shared_ptr<Material> RectangleXZ::material() const noexcept {
  return m_Material;
}

bool RectangleXZ::hit(
    const Ray& r,
    real t_min,
    real t_max,
    HitRecord& rec) const {
  if (r.direction().y == 0) return false;

  real t = (m_Y-r.origin().y) / r.direction().y;
  if (t < t_min || t > t_max) return false;

  real x = r.origin().x + t*r.direction().x;
  real z = r.origin().z + t*r.direction().z;
  if (x < m_X0 || x > m_X1) return false;
  if (z < m_Z0 || z > m_Z1) return false;

  rec.point = Vec3(x, m_Y, z);
  rec.normal = r.direction().y > 0 ? Vec3(0, -1, 0) : Vec3(0, 1, 0);
  rec.material = m_Material;
  rec.t = t;
  rec.u = (x-m_X0)/(m_X1-m_X0);
  rec.v = (z-m_Z0)/(m_Z1-m_Z0);

  return true;
}

bool RectangleXZ::bounding_box(real, real, BoundingBox& box) const {
  box = BoundingBox(
    Vec3(m_X0, m_Y-0.0001, m_Z0),
    Vec3(m_X1, m_Y+0.0001, m_Z1));
  return true;
}

RectangleYZ::RectangleYZ(
  real x,
  real y0, real y1,
  real z0, real z1,
  std::shared_ptr<Material> material)
  : m_X(x),
    m_Y0(y0), m_Y1(y1),
    m_Z0(z0), m_Z1(z1),
    m_Material(material) { }

std::shared_ptr<Material> RectangleYZ::material() const noexcept {
  return m_Material;
}

bool RectangleYZ::hit(
    const Ray& r,
    real t_min,
    real t_max,
    HitRecord& rec) const {
  if (r.direction().x == 0) return false;

  real t = (m_X-r.origin().x) / r.direction().x;
  if (t < t_min || t > t_max) return false;

  real y = r.origin().y + t*r.direction().y;
  real z = r.origin().z + t*r.direction().z;
  if (y < m_Y0 || y > m_Y1) return false;
  if (z < m_Z0 || z > m_Z1) return false;

  rec.point = Vec3(m_X, y, z);
  rec.normal = r.direction().x > 0 ? Vec3(-1, 0, 0) : Vec3(1, 0, 0);
  rec.material = m_Material;
  rec.t = t;
  rec.u = (y-m_Y0)/(m_Y1-m_Y0);
  rec.v = (z-m_Z0)/(m_Z1-m_Z0);

  return true;
}

bool RectangleYZ::bounding_box(real, real, BoundingBox& box) const {
  box = BoundingBox(
    Vec3(m_X-0.0001, m_Y0, m_Z0),
    Vec3(m_X+0.0001, m_Y1, m_Z1));
  return true;
}

}  // namespace WaywardRT
