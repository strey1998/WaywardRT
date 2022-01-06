// WaywardRT/WaywardRT/include/WaywardRT/Materials/Dielectric.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_DIELECTRIC_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_DIELECTRIC_H_

#include "WaywardRT_export.h"

#include "WaywardRT/Color.h"
#include "WaywardRT/Materials/Material.h"
namespace WaywardRT { struct HitRecord; }

namespace WaywardRT {
//////////////////////////////////////////////////////////////////////////////
/// Represents an hittable object
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT Dielectric : public Material {
 private:
  double m_IR;
 public:
  //////////////////////////////////////////////////////////////////////////////
  /// @brief Contruct a new Dielectric material
  /// @param[in] ir The index of refraction of the material
  //////////////////////////////////////////////////////////////////////////////
  explicit Dielectric(double ir);

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDoc}
  //////////////////////////////////////////////////////////////////////////////
  std::optional<Ray> scatter(
    const Ray& r, const HitRecord& rec, Color& attenuation) const override;

 private:
  static double reflectance(double cosTheta, double ri);
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_DIELECTRIC_H_
