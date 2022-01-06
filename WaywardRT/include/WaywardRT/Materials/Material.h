// WaywardRT/WaywardRT/include/WaywardRT/Materials/Material.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_MATERIAL_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_MATERIAL_H_

#include "WaywardRT_export.h"

#include <optional>

#include "WaywardRT/Ray.h"

namespace WaywardRT { struct HitRecord; }

namespace WaywardRT {
//////////////////////////////////////////////////////////////////////////////
/// Represents an hittable object
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT Material {
 public:
  //////////////////////////////////////////////////////////////////////////////
  /// @brief Scatter a ray off the material, or absorb it
  /// @param[in]  r           The incoming ray
  /// @param[in]  rec         The HitRecord for the hit
  /// @param[out] attenuation The attenuated color for the scatter
  /// @return The scattered ray, if it exists
  //////////////////////////////////////////////////////////////////////////////
  virtual std::optional<Ray> scatter(
    const Ray& r, const HitRecord& rec, Color& attenuation) const = 0;
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_MATERIAL_H_
