// WaywardRT/WaywardRT/src/Materials/Dielectric.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Materials/Dielectric.h"

#include <cmath>

#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/Ray.h"
#include "WaywardRT/util.h"

namespace WaywardRT {

Dielectric::Dielectric(double ir) : m_IR(ir) { }

std::optional<Ray> Dielectric::scatter(
    const Ray& r, const HitRecord& rec, Color& attenuation) const {
  attenuation = Color(1.0, 1.0, 1.0);
  bool front_face = r.direction()*rec.normal < 0;
  double refraction_ratio = front_face ? (1.0/m_IR) : m_IR;

  Vec3 unit_direction = r.direction().e();

  double cosTheta
    = fmin(-unit_direction*(front_face ? rec.normal : -rec.normal), 1.0);
  double sinTheta = sqrt(1.0 - cosTheta*cosTheta);
  bool cannotRefract = refraction_ratio * sinTheta > 1.0;

  Vec3 direction;

  if (cannotRefract
    || reflectance(cosTheta, refraction_ratio) > random_double())
      direction = unit_direction.reflect(rec.normal);
  else
    direction = unit_direction.refract(
      front_face ? rec.normal : -rec.normal, refraction_ratio);

  return Ray(rec.point, direction);
}

double Dielectric::reflectance(double cosTheta, double ri) {
  double r0 = (1-ri) / (1+ri);
  r0 = r0*r0;
  return r0 + (1-r0)*pow((1-cosTheta), 5);
}

}  // namespace WaywardRT
