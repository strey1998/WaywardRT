// WaywardRT/WaywardRT/src/Textures/Marble.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Textures/Marble.h"

#include <cmath>

#include "WaywardRT/Color.h"
#include "WaywardRT/Perlin.h"
#include "WaywardRT/util.h"
#include "WaywardRT/Vec3.h"

namespace WaywardRT {

Marble::Marble(real scale) : Marble(Color::BLACK(), Color::WHITE(), scale) { }
Marble::Marble(const Color& c0, const Color& c1, real scale)
  : m_C0(c0), m_C1(c1), m_Scale(scale) { }

Color Marble::value(real, real, const Vec3& p) const {
  real t = 0.5 * (1 + sin(m_Scale*p.z + 10*m_Noise.turb(p)));
  return m_C0*(1-t) + m_C1*t;
}

}  // namespace WaywardRT
