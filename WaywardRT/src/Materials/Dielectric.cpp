// WaywardRT/WaywardRT/src/Materials/Dielectric.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Materials/Dielectric.h"

#include <cmath>

#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/Ray.h"
#include "WaywardRT/util.h"

namespace WaywardRT {

Dielectric::Dielectric(real ir) : m_IR(ir) { }

bool Dielectric::scatter(
    const Ray& r,
    const HitRecord& rec,
    Ray& scattered,
    Color& attenuation) const {
  attenuation = Color(1.0, 1.0, 1.0);
  bool front_face = r.direction()*rec.normal < 0;
  real refraction_ratio = front_face ? (1.0/m_IR) : m_IR;

  Vec3 unit_direction = r.direction().e();

  real cosTheta
    = fmin(-unit_direction*(front_face ? rec.normal : -rec.normal), 1.0);
  real sinTheta = sqrt(1.0 - cosTheta*cosTheta);
  bool cannotRefract = refraction_ratio * sinTheta > 1.0;

  Vec3 direction;

  if (cannotRefract
    || reflectance(cosTheta, refraction_ratio) > random_real())
      direction = unit_direction.reflect(rec.normal);
  else
    direction = unit_direction.refract(
      front_face ? rec.normal : -rec.normal, refraction_ratio);

  scattered = std::move(Ray(rec.point, direction, r.time()));
  return true;
}

real Dielectric::reflectance(real cosTheta, real ri) {
  real r0 = (1-ri) / (1+ri);
  r0 = r0*r0;
  return r0 + (1-r0)*pow((1-cosTheta), 5);
}

}  // namespace WaywardRT
