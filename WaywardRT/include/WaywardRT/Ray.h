// WaywardRT/WaywardRT/include/WaywardRT/Ray.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_RAY_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_RAY_H_

#include <iosfwd>

#include "WaywardRT_export.h"
#include "WaywardRT/Vec3.h"
#include "WaywardRT/util.h"

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// Represents a ray with an origin point and a direction
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT Ray {
 private:
  Vec3 m_Origin;
  Vec3 m_Direction;
  real m_Time = 0;

 public:
  Ray() = default;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initializes a ray with origin at (0, 0, 0)
  /// @param[in] direction The direction of the ray
  /// @param[in] time      The time at which the ray exists
  //////////////////////////////////////////////////////////////////////////////
  explicit Ray(const Vec3& direction, real time = 0.0);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initializes a ray
  /// @param[in] origin    The origin point of the ray
  /// @param[in] direction The direction of the ray
  /// @param[in] time      The time at which the ray exists
  //////////////////////////////////////////////////////////////////////////////
  Ray(const Vec3& origin, const Vec3& direction, real time = 0.0);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Accessor for origin
  /// @return A const reference to the origin Vec3
  //////////////////////////////////////////////////////////////////////////////
  const Vec3& origin() const;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Accessor for direction
  /// @return A const reference to the direction Vec3
  //////////////////////////////////////////////////////////////////////////////
  const Vec3& direction() const;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Accessor for time
  /// @return The time at which the ray exists
  //////////////////////////////////////////////////////////////////////////////
  real time() const;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Point calculation along ray
  /// @param[in] t Parametrizer variable
  /// @return A new Vec3 equal to (this.origin) + t*(this.direction). This is a
  ///   vector representing the point t*magnitude(direction) distance away from
  ///   the origin point along the direction vector.
  //////////////////////////////////////////////////////////////////////////////
  Vec3 at(real t) const;

  friend WAYWARDRT_EXPORT std::ostream& operator<<(
    std::ostream& os, const Ray& r);
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_RAY_H_
