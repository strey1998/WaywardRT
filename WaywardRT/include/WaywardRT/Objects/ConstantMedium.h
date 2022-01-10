// WaywardRT/WaywardRT/include/WaywardRT/Objects/ConstantMedium.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_CONSTANTMEDIUM_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_CONSTANTMEDIUM_H_

#include "WaywardRT_export.h"

#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/Ray.h"
#include "WaywardRT/Textures/Texture.h"
#include "WaywardRT/util.h"

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// Represents a consant volumetric medium
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT ConstantMedium : public Hittable {
 private:
  std::shared_ptr<Hittable> m_Boundary;
  std::shared_ptr<Material> m_PhaseFn;
  real m_NegInvDensity;

 public:
  ConstantMedium() = delete;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initializer
  /// @param[in] boundary A HittableObject representing the boundary of this
  ///   medium
  /// @param[in] density  The density of this object (should be in (0, 1))
  /// @param[in] c        The color of this medium
  //////////////////////////////////////////////////////////////////////////////
  ConstantMedium(
    std::shared_ptr<Hittable> boundary,
    real density,
    Color c);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initializer
  /// @param[in] boundary A HittableObject representing the boundary of this
  ///   medium
  /// @param[in] density  The density of this object (should be in (0, 1))
  /// @param[in] p        A Texture representing the phase function
  //////////////////////////////////////////////////////////////////////////////
  ConstantMedium(
    std::shared_ptr<Hittable> boundary,
    real density,
    std::shared_ptr<Texture> t);

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDoc}
  //////////////////////////////////////////////////////////////////////////////
  bool hit(
    const Ray& r,
    real t_min,
    real t_max,
    HitRecord& rec) const override;

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDoc}
  //////////////////////////////////////////////////////////////////////////////
  bool bounding_box(real t0, real t1, BoundingBox& box) const override;
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_CONSTANTMEDIUM_H_
