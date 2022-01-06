// WaywardRT/WaywardRT/src/Materials/Labertian.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Materials/Lambertian.h"

#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/Ray.h"

namespace WaywardRT {

Lambertian::Lambertian(const Color& a) : m_Albedo(a) { }

std::optional<Ray> Lambertian::scatter(
    const Ray&, const HitRecord& rec, Color& attenuation) const {
  Vec3 scatter_direction = rec.normal + Vec3::random_unit();
  if (scatter_direction == Vec3()) scatter_direction = rec.normal;
  attenuation = m_Albedo;
  return Ray(rec.point, scatter_direction);
}

}  // namespace WaywardRT
