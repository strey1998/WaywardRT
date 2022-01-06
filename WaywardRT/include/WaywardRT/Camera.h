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

 public:
  //////////////////////////////////////////////////////////////////////////////
  /// @brief Default camera
  /// @returns A default camera equal to Camera(2.0, 3.5556, 1.0)
  //////////////////////////////////////////////////////////////////////////////
  static Camera DEFAULT();

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Default ultrawide camera
  /// @returns A default camera equal to Camera(2.0, 4.7407, 1.0)
  //////////////////////////////////////////////////////////////////////////////
  static Camera DEFAULT_ULTRAWIDE();

  Camera() = delete;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initializer
  /// @param[in] view_height  The height of the camera's view
  /// @param[in] view_width   The width of the camera's view
  /// @param[in] focal_length The distance behind the camera to initiate the
  ///   rays
  //////////////////////////////////////////////////////////////////////////////
  Camera(double view_height, double view_width, double focal_length);

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
