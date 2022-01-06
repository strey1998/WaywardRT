// WaywardRT/WaywardRT/include/WaywardRT/Materials/Labertian.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_LAMBERTIAN_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_LAMBERTIAN_H_

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
class WAYWARDRT_EXPORT Lambertian : public Material {
 private:
  Color m_Albedo;
 public:
  //////////////////////////////////////////////////////////////////////////////
  /// @brief Construct a new Lambertian material with albedo a
  /// @param[in] a The color of the material
  //////////////////////////////////////////////////////////////////////////////
  Lambertian(const Color& a);

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDoc}
  //////////////////////////////////////////////////////////////////////////////
  std::optional<Ray> scatter(
    const Ray& r, const HitRecord& rec, Color& attenuation) const override;
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_MATERIALS_LAMBERTIAN_H_
