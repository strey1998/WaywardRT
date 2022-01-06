// WaywardRT/WaywardRT/src/Camera.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Camera.h"

namespace WaywardRT {

Camera Camera::DEFAULT() {
  return Camera(2.0, 4.7407, 1.0);
}

Camera::Camera(double view_height, double view_width, double focal_length) {
  m_Origin = Vec3(0, 0, 0);
  m_Horizontal = Vec3(view_width, 0, 0);
  m_Vertical = Vec3(0, view_height, 0);
  m_LowerLeftCorner
    = m_Origin - m_Horizontal/2 - m_Vertical/2 - Vec3(0, 0, focal_length);
}

Ray Camera::get_ray(double u, double v) const {
  return Ray(
    m_Origin,
    m_LowerLeftCorner + u*m_Horizontal + v*m_Vertical - m_Origin);
}

}  // namespace WaywardRT
