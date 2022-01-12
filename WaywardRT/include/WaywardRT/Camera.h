// WaywardRT/WaywardRT/include/WaywardRT/Camera.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_CAMERA_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_CAMERA_H_

#include "WaywardRT_export.h"

#include "WaywardRT/Vec3.h"
#include "WaywardRT/Ray.h"
#include "WaywardRT/util.h"

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// Represents a camera, from which images can be rendered
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT Camera {
 private:
  Vec3 m_Origin;
  Vec3 m_LowerLeftCorner;
  Vec3 m_Horizontal;
  Vec3 m_Vertical;
  Vec3 m_W, m_U, m_V;
  real m_LensRadius;
  real m_T0, m_T1;

 public:
  Camera();

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initializer
  /// @param[in] look_from    The point at which the camera is placed
  /// @param[in] look_at      The point at which the camera looks
  /// @param[in] v_up         The upward direction for the camera
  /// @param[in] vfov         The vertical field of view, in degrees
  /// @param[in] aspect_ratio The aspect ratio (horizontal/vertical)
  /// @param[in] aperture     The lens aperture size (default 0.0 - no blur)
  //////////////////////////////////////////////////////////////////////////////
  Camera(
    Vec3 look_from,
    Vec3 look_at,
    Vec3 v_up,
    real vfov,
    real aspect_ratio,
    real aperture = 0.0);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initializer
  /// @param[in] look_from    The point at which the camera is placed
  /// @param[in] look_at      The point at which the camera looks
  /// @param[in] v_up         The upward direction for the camera
  /// @param[in] vfov         The vertical field of view, in degrees
  /// @param[in] aspect_ratio The aspect ratio (horizontal/vertical)
  /// @param[in] aperture     The lens aperture size
  /// @param[in] focus_dist   The lens focus distance
  //////////////////////////////////////////////////////////////////////////////
  Camera(
    Vec3 look_from,
    Vec3 look_at,
    Vec3 v_up,
    real vfov,
    real aspect_ratio,
    real aperture,
    real focus_dist);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Sets the ray timing from this camera
  /// @param[in] t The time at which rays are sent
  /// @returns A reference to self
  //////////////////////////////////////////////////////////////////////////////
  Camera& set_ray_timing(real t) noexcept;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Sets the ray timing from this camera, for motion blur
  /// @param[in] t0 The open time of the lens (i.e. the earliest time for rays)
  /// @param[in] t0 The close time of the lens (i.e. the latest time for rays)
  /// @returns A reference to self
  //////////////////////////////////////////////////////////////////////////////
  Camera& set_ray_timing(real t0, real t1) noexcept;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Gets a ray corresponding to a particular direction
  /// @param[in] u How far across the viewport should the ray point
  /// @param[in] v How far up the viewport should the ray point
  /// @returns The ray pointing from the focal point through the point on the
  ///   viewport described by u and v
  //////////////////////////////////////////////////////////////////////////////
  [[nodiscard]] Ray get_ray(real u, real v) const;
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_CAMERA_H_
