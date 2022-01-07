// WaywardRT/WaywardRT/include/WaywardRT/Objects/Hittable.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_HITTABLE_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_HITTABLE_H_

#include "WaywardRT_export.h"

#include <memory>

#include "WaywardRT/Ray.h"
namespace WaywardRT { class Material; }

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// Contains information about a hit
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
struct WAYWARDRT_EXPORT HitRecord {
  Vec3 point;
  Vec3 normal;
  std::shared_ptr<Material> material;
  double t;
};

//////////////////////////////////////////////////////////////////////////////
/// Represents an hittable object
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT Hittable {
 public:
  //////////////////////////////////////////////////////////////////////////////
  /// Check whether a ray hits the object(s)
  /// @param[in]  r     The ray
  /// @param[in]  t_min Minimum value of t at which to register a hit
  /// @param[in]  t_max Maximum value of t at which to register a hit
  /// @param[out] rec   HitRecord containing information about the hit
  /// @return True if a hit is recorded, false otherwise
  //////////////////////////////////////////////////////////////////////////////
  virtual bool hit(
    const Ray& r,
    double t_min,
    double t_max,
    HitRecord& rec) const = 0;
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_HITTABLE_H_
