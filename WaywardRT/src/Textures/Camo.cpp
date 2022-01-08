// WaywardRT/WaywardRT/src/Textures/Camo.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Textures/Camo.h"

#include <cmath>

#include "WaywardRT/Color.h"
#include "WaywardRT/Perlin.h"
#include "WaywardRT/util.h"
#include "WaywardRT/Vec3.h"

namespace WaywardRT {

Camo::Camo(real scale) : Camo(Color::BLACK(), Color::WHITE(), scale) { }
Camo::Camo(const Color& c0, const Color& c1, real scale)
  : m_C0(c0), m_C1(c1), m_Scale(scale) { }

Color Camo::value(real, real, const Vec3& p) const {
  real t = m_Noise.turb(m_Scale*p);
  return m_C0*(1-t) + m_C1*t;
}

}  // namespace WaywardRT
