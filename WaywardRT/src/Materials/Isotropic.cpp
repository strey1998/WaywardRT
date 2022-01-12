// WaywardRT/WaywardRT/src/Materials/Isotropic.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Materials/Isotropic.h"

#include <memory>

#include "WaywardRT/Color.h"
#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/Ray.h"
#include "WaywardRT/Textures/SolidColor.h"
#include "WaywardRT/Textures/Texture.h"
#include "WaywardRT/Vec3.h"

namespace WaywardRT {

Isotropic::Isotropic(const Color& c)
  : m_Albedo(std::make_shared<SolidColor>(c)) { }

Isotropic::Isotropic(std::shared_ptr<Texture> a) : m_Albedo(a) { }

bool Isotropic::scatter(
    const Ray& r,
    const HitRecord& rec,
    Ray& scattered,
    Color& attenuation) const {
  scattered = Ray(rec.point, Vec3::random_in_unit_sphere(), r.time());
  attenuation = m_Albedo->value(rec.u, rec.v, rec.point);
  return true;
}

}  // namespace WaywardRT
