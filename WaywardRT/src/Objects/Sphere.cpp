// WaywardRT/WaywardRT/src/Objects/Sphere.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Objects/Sphere.h"

#include <cmath>

#include "WaywardRT/Ray.h"
#include "WaywardRT/Vec3.h"
#include "WaywardRT/util.h"

namespace WaywardRT {

Sphere::Sphere(Vec3 center, real radius, std::shared_ptr<Material> material)
  : m_Center(center), m_Radius(radius), m_Material(material) { }

const Vec3& Sphere::center() const noexcept {
  return m_Center;
}

real Sphere::radius() const noexcept {
  return m_Radius;
}

std::shared_ptr<Material> Sphere::material() const noexcept {
  return m_Material;
}

bool Sphere::hit(
    const Ray& r,
    real t_min,
    real t_max,
    HitRecord& rec) const {
  Vec3 oc = r.origin() - center();
  real a = r.direction().len_sq();
  real bh = oc*r.direction();
  real c = oc.len_sq() - radius()*radius();
  real d = bh*bh - a*c;

  if (d < 0) return false;

  real sqrtd = sqrt(d);

  real root = (-bh - sqrtd) / a;
  if (root < t_min || t_max < root) {
    root = (-bh + sqrtd) / a;
    if (root < t_min || t_max < root) return false;
  }

  rec.point = r.at(root);
  rec.normal = (rec.point - center()) / radius();
  rec.material = m_Material;
  rec.t = root;

  return true;
}

bool Sphere::bounding_box(real, real, BoundingBox& box) const {
  box.p0 = m_Center - Vec3(m_Radius, m_Radius, m_Radius);
  box.p1 = m_Center + Vec3(m_Radius, m_Radius, m_Radius);
  return true;
}

}  // namespace WaywardRT
