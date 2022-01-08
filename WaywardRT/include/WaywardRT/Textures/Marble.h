// WaywardRT/WaywardRT/include/WaywardRT/Textures/Marble.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_TEXTURES_MARBLE_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_TEXTURES_MARBLE_H_

#include "WaywardRT_export.h"

#include "WaywardRT/Color.h"
#include "WaywardRT/Perlin.h"
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
class WAYWARDRT_EXPORT Marble : public Texture {
 private:
  Perlin m_Noise;
  Color m_C0, m_C1;
  real m_Scale;

 public:
  explicit Marble(real scale = 1.0);
  Marble(const Color& c0, const Color& c1, real scale = 1.0);

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDocs}
  //////////////////////////////////////////////////////////////////////////////
  Color value(real u, real v, const Vec3& p) const override;
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_TEXTURES_MARBLE_H_
