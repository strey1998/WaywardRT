// WaywardRT/WaywardRT/include/WaywardRT/Materials/Labertian.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_LAMBERTIAN_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_LAMBERTIAN_H_

#include "WaywardRT_export.h"

#include <memory>

#include "WaywardRT/Color.h"
#include "WaywardRT/Materials/Material.h"
#include "WaywardRT/Textures/SolidColor.h"
#include "WaywardRT/Textures/Texture.h"
namespace WaywardRT { struct HitRecord; }

namespace WaywardRT {
//////////////////////////////////////////////////////////////////////////////
/// Represents an hittable object
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT Lambertian : public Material {
 private:
  std::shared_ptr<Texture> m_Albedo;
 public:
  //////////////////////////////////////////////////////////////////////////////
  /// @brief Construct a new Lambertian material with solid albedo a
  /// @param[in] a The color of the material
  //////////////////////////////////////////////////////////////////////////////
  explicit Lambertian(const Color& a);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Construct a new Lambertian material with texture albedo a
  /// @param[in] a The color of the material
  //////////////////////////////////////////////////////////////////////////////
  explicit Lambertian(std::shared_ptr<Texture> a);

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

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_LAMBERTIAN_H_
