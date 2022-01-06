// WaywardRT/WaywardRT/include/WaywardRT/Objects/Sphere.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_SPHERE_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_SPHERE_H_

#include "WaywardRT_export.h"

#include <optional>

#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/Ray.h"

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// Represents a sphere
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT Sphere : public Hittable {
 private:
  Vec3 m_Center;
  double m_Radius;
  std::shared_ptr<Material> m_Material;

 public:
  Sphere() = delete;
  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initialize a sphere
  /// @param[in] center The center
  /// @param[in] radius The radius
  //////////////////////////////////////////////////////////////////////////////
  Sphere(Vec3 center, double radius, std::shared_ptr<Material> material);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Accessor for center
  /// @returns The center of the sphere
  //////////////////////////////////////////////////////////////////////////////
  const Vec3& center() const;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Accessor for radius
  /// @returns The radius of the sphere
  //////////////////////////////////////////////////////////////////////////////
  double radius() const;

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDoc}
  //////////////////////////////////////////////////////////////////////////////
  std::optional<HitRecord> hit(
    const Ray& r,
    double t_min,
    double t_max) const override;
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_SPHERE_H_
