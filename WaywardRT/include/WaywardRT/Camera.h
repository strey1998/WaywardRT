// WaywardRT/WaywardRT/include/WaywardRT/Camera.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_CAMERA_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_CAMERA_H_

#include "WaywardRT_export.h"

#include "WaywardRT/Ray.h"

namespace WaywardRT {

class WAYWARDRT_EXPORT Camera {
 private:
  Vec3 m_Origin;
  Vec3 m_LowerLeftCorner;
  Vec3 m_Horizontal;
  Vec3 m_Vertical;

 public:
  static Camera DEFAULT();

  Camera() = delete;
  Camera(double view_height, double view_width, double focal_length);

  [[nodiscard]] Ray get_ray(double u, double v) const;
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_CAMERA_H_
