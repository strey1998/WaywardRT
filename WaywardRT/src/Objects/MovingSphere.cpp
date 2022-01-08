// WaywardRT/WaywardRT/src/Objects/MovingSphere.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Objects/MovingSphere.h"

#include <cmath>

#include "WaywardRT/Ray.h"
#include "WaywardRT/Vec3.h"
#include "WaywardRT/util.h"

namespace WaywardRT {

MovingSphere::MovingSphere(
  Vec3 center,
  Vec3 velocity,
  real radius,
  std::shared_ptr<Material> material)
  : Sphere(center, radius, material),
    m_Velocity(velocity) { }

const Vec3& MovingSphere::MovingSphere::velocity() const { return m_Velocity; }

Vec3 MovingSphere::center(real t) const {
  return m_Center + t*m_Velocity;
}

//////////////////////////////////////////////////////////////////////////////
/// {@inheritDoc}
//////////////////////////////////////////////////////////////////////////////
bool MovingSphere::hit(
    const Ray& r,
    real t_min,
    real t_max,
    HitRecord& rec) const {
  Vec3 oc = r.origin() - center(r.time());
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
  }  // TODO(TS): Wtf ^^^^^^^^

  rec.point = r.at(root);
  rec.normal = (rec.point - center(r.time())) / radius();
  rec.material = m_Material;
  rec.t = root;

  return true;
}

}  // namespace WaywardRT