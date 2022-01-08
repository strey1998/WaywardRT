// WaywardRT/WaywardRT/src/Textures/Checkered.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Textures/Checkered.h"

#include <cmath>

#include "WaywardRT/Color.h"
#include "WaywardRT/Textures/SolidColor.h"
#include "WaywardRT/Textures/Texture.h"
#include "WaywardRT/Vec3.h"

namespace WaywardRT {

Checkered::Checkered(const Color& c1, const Color& c2)
  : m_Texture1(std::make_shared<SolidColor>(c1)),
    m_Texture2(std::make_shared<SolidColor>(c2)) { }

Checkered::Checkered(std::shared_ptr<Texture> t1, std::shared_ptr<Texture> t2)
  : m_Texture1(t1), m_Texture2(t2) { }

Color Checkered::value(real u, real v, const Vec3& p) const {
  real sines = sin(10*p.x)*sin(10*p.y)*sin(10*p.z);
  return sines < 0 ? m_Texture1->value(u, v, p)
                   : m_Texture2->value(u, v, p);
}

}  // namespace WaywardRT
