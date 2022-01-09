// WaywardRT/WaywardRT/src/Materials/Material.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Materials/Material.h"

#include "WaywardRT/Color.h"
#include "WaywardRT/Vec3.h"

namespace WaywardRT {

Color Material::emit(real, real, const Vec3&) const { return Color(0, 0, 0); }

}  // namespace WaywardRT
