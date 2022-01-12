// WaywardRT/WaywardRT/src/Textures/SolidColor.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Textures/SolidColor.h"

#include "WaywardRT/Color.h"
namespace WaywardRT { class Vec3; }

namespace WaywardRT {

SolidColor::SolidColor() : m_Color(Color(0.0, 0.0, 0.0)) { }

SolidColor::SolidColor(const Color& color) : m_Color(color) { }

Color SolidColor::value(real, real, const Vec3&) const { return m_Color; }

}  // namespace WaywardRT
