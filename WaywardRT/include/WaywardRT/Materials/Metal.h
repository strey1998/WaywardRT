// WaywardRT/WaywardRT/include/WaywardRT/Materials/Metal.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_METAL_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_METAL_H_

#include "WaywardRT_export.h"

#include "WaywardRT/Color.h"
#include "WaywardRT/Materials/Material.h"
#include "WaywardRT/util.h"
namespace WaywardRT { class Ray; }
namespace WaywardRT { struct HitRecord; }

namespace WaywardRT {
//////////////////////////////////////////////////////////////////////////////
/// Represents a metal material
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT Metal : public Material {
 private:
  Color m_Albedo;
  real m_Fuzz;
 public:
  //////////////////////////////////////////////////////////////////////////////
  /// @brief Contruct a new Metal material
  /// @param[in] c The color of the material
  /// @param[in] f The fuzziness of the reflection
  //////////////////////////////////////////////////////////////////////////////
  explicit Metal(const Color& c, real f = 0.0);

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDoc}
  //////////////////////////////////////////////////////////////////////////////
  bool scatter(
    const Ray& r,
    const HitRecord& rec,
    Ray& scattered,
    Color& attenuation) const override;
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_METAL_H_
