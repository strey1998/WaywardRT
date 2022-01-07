// WaywardRT/WaywardRT/src/Materials/Labertian.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Materials/Lambertian.h"

#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/Ray.h"

namespace WaywardRT {

Lambertian::Lambertian(const Color& a) : m_Albedo(a) { }

bool Lambertian::scatter(
    const Ray&,
    const HitRecord& rec,
    Ray& scattered,
    Color& attenuation)  const {
  Vec3 scatter_direction = rec.normal + Vec3::random_unit();
  if (scatter_direction == Vec3()) scatter_direction = rec.normal;
  scattered = std::move(Ray(rec.point, scatter_direction));
  attenuation = m_Albedo;
  return true;
}

}  // namespace WaywardRT
