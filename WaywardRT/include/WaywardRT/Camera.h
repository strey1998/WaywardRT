// WaywardRT/WaywardRT/include/WaywardRT/Camera.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_CAMERA_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_CAMERA_H_

#include "WaywardRT_export.h"

#include "WaywardRT/Ray.h"

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
  double m_LensRadius;

 public:
  //////////////////////////////////////////////////////////////////////////////
  /// @brief Default camera
  /// @returns A default 16:9 camera
  //////////////////////////////////////////////////////////////////////////////
  static Camera DEFAULT();

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Default ultrawide camera
  /// @returns A default 21:9 camera
  //////////////////////////////////////////////////////////////////////////////
  static Camera DEFAULT_ULTRAWIDE();

  Camera() = delete;

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
    double vfov,
    double aspect_ratio,
    double aperture = 0.0);

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
    double vfov,
    double aspect_ratio,
    double aperture,
    double focus_dist);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Gets a ray corresponding to a particular direction
  /// @param[in] u How far across the viewport should the ray point
  /// @param[in] v How far up the viewport should the ray point
  /// @returns The ray pointing from the focal point through the point on the
  ///   viewport described by u and v
  //////////////////////////////////////////////////////////////////////////////
  [[nodiscard]] Ray get_ray(double u, double v) const;
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_CAMERA_H_
