// WaywardRT/WaywardRT/src/Materials/Lambertian.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Materials/Lambertian.h"

#include <memory>

#include "WaywardRT/Color.h"
#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/Ray.h"
#include "WaywardRT/Textures/SolidColor.h"
#include "WaywardRT/Textures/Texture.h"
#include "WaywardRT/Vec3.h"

namespace WaywardRT {

Lambertian::Lambertian(const Color& a)
  : Lambertian(std::make_shared<SolidColor>(a)) { }

Lambertian::Lambertian(std::shared_ptr<Texture> a) : m_Albedo(a) { }

bool Lambertian::scatter(
    const Ray& r,
    const HitRecord& rec,
    Ray& scattered,
    Color& attenuation)  const {
  Vec3 scatter_direction = rec.normal + Vec3::random_unit();
  if (scatter_direction == Vec3()) scatter_direction = rec.normal;
  scattered = Ray(rec.point, scatter_direction, r.time());
  attenuation = m_Albedo->value(rec.u, rec.v, rec.point);
  return true;
}

}  // namespace WaywardRT
