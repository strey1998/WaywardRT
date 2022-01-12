// WaywardRT/WaywardRT/src/Materials/DiffuseLight.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Materials/DiffuseLight.h"

#include <memory>

#include "WaywardRT/Color.h"
#include "WaywardRT/Textures/SolidColor.h"
#include "WaywardRT/Textures/Texture.h"
#include "WaywardRT/util.h"
namespace WaywardRT { class Ray; }
namespace WaywardRT { class Vec3; }

namespace WaywardRT {

DiffuseLight::DiffuseLight(const Color& c)
  : m_Emit(std::make_shared<SolidColor>(c)) { }

DiffuseLight::DiffuseLight(std::shared_ptr<Texture> t) : m_Emit(t) { }

bool DiffuseLight::scatter(const Ray&, const HitRecord&, Ray&, Color&) const {
  return false;
}

Color DiffuseLight::emit(real u, real v , const Vec3& p) const {
  return m_Emit->value(u, v, p);
}

}  // namespace WaywardRT
