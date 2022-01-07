// WaywardRT/WaywardRT/src/Objects/Sphere.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Objects/Sphere.h"

#include <cmath>

#include "WaywardRT/Ray.h"
#include "WaywardRT/Vec3.h"

namespace WaywardRT {

Sphere::Sphere(Vec3 center, double radius, std::shared_ptr<Material> material)
  : m_Center(center), m_Radius(radius), m_Material(material) { }

const Vec3& Sphere::center() const {
  return m_Center;
}

double Sphere::radius() const {
  return m_Radius;
}

bool Sphere::hit(
    const Ray& r,
    double t_min,
    double t_max,
    HitRecord& rec) const {
  Vec3 oc = r.origin() - center();
  double a = r.direction().len_sq();
  double bh = oc*r.direction();
  double c = oc.len_sq() - radius()*radius();
  double d = bh*bh - a*c;

  if (d < 0) return false;

  double sqrtd = sqrt(d);

  double root = (-bh - sqrtd) / a;
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

}  // namespace WaywardRT
