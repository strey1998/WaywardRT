// WaywardRT/WaywardRT/include/WaywardRT/Objects/Hittable.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_HITTABLE_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_HITTABLE_H_

#include "WaywardRT_export.h"

#include <optional>

#include "WaywardRT/Ray.h"


namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// Contains information about a hit
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
struct WAYWARDRT_EXPORT HitRecord {
  Vec3 p;
  Vec3 n;
  double t;

  HitRecord() = delete;
  HitRecord(Vec3 p, Vec3 n, double t) : p(p), n(n), t(t) { }
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
  /// @param r     The ray
  /// @param t_min Minimum value of t at which to register a hit
  /// @param t_max Maximum value of t at which to register a hit
  /// @return A HitRecord containing information about the hit, if it exists
  //////////////////////////////////////////////////////////////////////////////
  virtual std::optional<HitRecord> hit(
    const Ray& r,
    double t_min,
    double t_max) const = 0;
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_HITTABLE_H_
