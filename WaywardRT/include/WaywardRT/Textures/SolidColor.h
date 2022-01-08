// WaywardRT/WaywardRT/include/WaywardRT/Textures/SolidColor.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_TEXTURES_SOLIDCOLOR_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_TEXTURES_SOLIDCOLOR_H_

#include "WaywardRT_export.h"

#include "WaywardRT/Color.h"
#include "WaywardRT/Textures/Texture.h"
#include "WaywardRT/util.h"
#include "WaywardRT/Vec3.h"

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// Abstract class for textures
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT SolidColor : public Texture {
 private:
  Color m_Color;
 public:
  SolidColor();
  explicit SolidColor(const Color& color);

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDocs}
  //////////////////////////////////////////////////////////////////////////////
  Color value(real u, real v, const Vec3& p) const override;
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_TEXTURES_SOLIDCOLOR_H_
