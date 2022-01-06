// WaywardRT/WaywardRT/src/Camera.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Camera.h"

#include <cmath>

#include "WaywardRT/util.h"

namespace WaywardRT {

Camera Camera::DEFAULT() {
  return Camera(
    Vec3(0, 0, 0),
    Vec3(0, 0, -1),
    Vec3(0, 1, 0),
    90,
    16.0/9);
}

Camera Camera::DEFAULT_ULTRAWIDE() {
  return Camera(
    Vec3(0, 0, 0),
    Vec3(0, 0, -1),
    Vec3(0, 1, 0),
    90,
    21.0/9);
}

Camera::Camera(
    Vec3 look_from,
    Vec3 look_at,
    Vec3 v_up,
    double vfov,
    double aspect_ratio) {
  double theta = degrees_to_radians(vfov);
  double h = tan(theta/2);
  double view_height = 2.0 * h;
  double view_width = aspect_ratio * view_height;

  Vec3 w = (look_from - look_at).e();
  Vec3 u = cross(v_up, w).e();
  Vec3 v = cross(w, u);

  m_Origin = look_from;
  m_Horizontal = view_width * u;
  m_Vertical = view_height * v;
  m_LowerLeftCorner = m_Origin - m_Horizontal/2 - m_Vertical/2 - w;
}

Ray Camera::get_ray(double u, double v) const {
  return Ray(
    m_Origin,
    m_LowerLeftCorner + u*m_Horizontal + v*m_Vertical - m_Origin);
}

}  // namespace WaywardRT
