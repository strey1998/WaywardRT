// WaywardRT/WaywardRT/include/WaywardRT/Textures/Texture.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_TEXTURES_TEXTURE_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_TEXTURES_TEXTURE_H_

#include "WaywardRT_export.h"

#include "WaywardRT/Color.h"
#include "WaywardRT/util.h"
namespace WaywardRT { class Vec3; }


namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// Abstract class for textures
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT Texture {
 public:
  virtual ~Texture() = default;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Get color value at point
  /// @param[in] u
  /// @param[in] v
  /// @param[in] p
  //////////////////////////////////////////////////////////////////////////////
  virtual Color value(real u, real v, const Vec3& p) const = 0;
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_TEXTURES_TEXTURE_H_
