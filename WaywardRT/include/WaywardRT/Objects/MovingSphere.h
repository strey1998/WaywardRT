// WaywardRT/WaywardRT/include/WaywardRT/Objects/MovingSphere.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_MOVINGSPHERE_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_MOVINGSPHERE_H_

#include "WaywardRT_export.h"

#include <memory>

#include "WaywardRT/Objects/Sphere.h"
#include "WaywardRT/util.h"
#include "WaywardRT/Vec3.h"
namespace WaywardRT { class BoundingBox; }
namespace WaywardRT { class Material; }
namespace WaywardRT { class Ray; }
namespace WaywardRT { struct HitRecord; }

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// Represents a moving sphere
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT MovingSphere : public Sphere {
 private:
  Vec3 m_Velocity;

 public:
  MovingSphere() = delete;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initialize a sphere
  /// @param[in] center The center
  /// @param[in] radius The radius
  //////////////////////////////////////////////////////////////////////////////
  MovingSphere(
    Vec3 center,
    Vec3 velocity,
    real radius,
    std::shared_ptr<Material> material);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Accessor for velocity
  /// @returns The velocity of the sphere
  //////////////////////////////////////////////////////////////////////////////
  const Vec3& velocity() const;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Gets the center of the sphere at a particular time
  /// @param[in] t Time
  /// @returns The center of the sphere at time t
  //////////////////////////////////////////////////////////////////////////////
  Vec3 center(real t) const;

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
  bool bounding_box(real t_min, real t_max, BoundingBox& box) const override;
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_MOVINGSPHERE_H_
