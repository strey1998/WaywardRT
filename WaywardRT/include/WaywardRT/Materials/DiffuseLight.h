// WaywardRT/WaywardRT/include/WaywardRT/Materials/DiffuseLight.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_DIFFUSELIGHT_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_DIFFUSELIGHT_H_

#include "WaywardRT_export.h"

#include <memory>

#include "WaywardRT/Materials/Material.h"
#include "WaywardRT/Textures/Texture.h"
namespace WaywardRT { struct HitRecord; }

namespace WaywardRT {
//////////////////////////////////////////////////////////////////////////////
/// Represents a diffuse light-emitting material
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT DiffuseLight : public Material {
 private:
  std::shared_ptr<Texture> m_Emit;

 public:
  //////////////////////////////////////////////////////////////////////////////
  /// @brief Contruct a new DiffuseLight material
  /// @param[in] t A texture representing the light emitted by this material
  //////////////////////////////////////////////////////////////////////////////
  explicit DiffuseLight(std::shared_ptr<Texture> t);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Contruct a new DiffuseLight material
  /// @param[in] c A solid color emitted by this material
  //////////////////////////////////////////////////////////////////////////////
  explicit DiffuseLight(const Color& c);

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDoc}
  //////////////////////////////////////////////////////////////////////////////
  bool scatter(
    const Ray& r,
    const HitRecord& rec,
    Ray& scattered,
    Color& attenuation) const override;

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDoc}
  //////////////////////////////////////////////////////////////////////////////
  Color emit(real u, real v , const Vec3& p) const override;

 private:
  static real reflectance(real cosTheta, real ri);
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_DIFFUSELIGHT_H_
