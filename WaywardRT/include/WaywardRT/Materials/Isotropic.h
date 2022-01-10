// WaywardRT/WaywardRT/include/WaywardRT/Materials/Isotropic.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_ISOTROPIC_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_ISOTROPIC_H_

#include "WaywardRT_export.h"

#include <memory>

#include "WaywardRT/Color.h"
#include "WaywardRT/Materials/Material.h"
#include "WaywardRT/Textures/SolidColor.h"
#include "WaywardRT/Textures/Texture.h"
namespace WaywardRT { struct HitRecord; }

namespace WaywardRT {
//////////////////////////////////////////////////////////////////////////////
/// Represents an isotropic material
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT Isotropic : public Material {
 private:
  std::shared_ptr<Texture> m_Albedo;

 public:
  //////////////////////////////////////////////////////////////////////////////
  /// @brief Construct a new Isotropic material with solid albedo a
  /// @param[in] c The color of the material
  //////////////////////////////////////////////////////////////////////////////
  explicit Isotropic(const Color& c);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Construct a new Isotropic material with texture albedo a
  /// @param[in] a The texture of the material
  //////////////////////////////////////////////////////////////////////////////
  explicit Isotropic(std::shared_ptr<Texture> a);

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

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_ISOTROPIC_H_
