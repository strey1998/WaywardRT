// WaywardRT/WaywardRT/src/Materials/Metal.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Materials/Metal.h"

#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/Ray.h"
#include "WaywardRT/util.h"

namespace WaywardRT {

Metal::Metal(const Color& a, real f) : m_Albedo(a), m_Fuzz(f < 1 ? f : 1) { }

bool Metal::scatter(
    const Ray& r,
    const HitRecord& rec,
    Ray& scattered,
    Color& attenuation) const {
  Vec3 reflected = r.direction().e().reflect(rec.normal);
  attenuation = m_Albedo;
  if (reflected*rec.normal > 0) {
    scattered = Ray(
      rec.point,
      reflected + m_Fuzz*Vec3::random_in_unit_sphere(),
      r.time());
    return true;
  }

  return false;
}

}  // namespace WaywardRT
