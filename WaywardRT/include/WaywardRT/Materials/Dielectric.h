// WaywardRT/WaywardRT/include/WaywardRT/Materials/Dielectric.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_DIELECTRIC_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_DIELECTRIC_H_

#include "WaywardRT_export.h"

#include "WaywardRT/Materials/Material.h"
#include "WaywardRT/util.h"
namespace WaywardRT { class Ray; }
namespace WaywardRT { struct Color; }
namespace WaywardRT { struct HitRecord; }

namespace WaywardRT {
//////////////////////////////////////////////////////////////////////////////
/// Represents a Dielectric material
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT Dielectric : public Material {
 private:
  real m_IR;
 public:
  //////////////////////////////////////////////////////////////////////////////
  /// @brief Contruct a new Dielectric material
  /// @param[in] ir The index of refraction of the material
  //////////////////////////////////////////////////////////////////////////////
  explicit Dielectric(real ir);

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDoc}
  //////////////////////////////////////////////////////////////////////////////
  bool scatter(
    const Ray& r,
    const HitRecord& rec,
    Ray& scattered,
    Color& attenuation) const override;

 private:
  static real reflectance(real cosTheta, real ri);
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_DIELECTRIC_H_
