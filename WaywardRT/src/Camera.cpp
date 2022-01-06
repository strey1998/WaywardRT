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
  double aspect_ratio,
  double aperture)
  : Camera(look_from,
           look_at,
           v_up,
           vfov,
           aspect_ratio,
           aperture,
           (look_from - look_at).len()) { }

Camera::Camera(
    Vec3 look_from,
    Vec3 look_at,
    Vec3 v_up,
    double vfov,
    double aspect_ratio,
    double aperture,
    double focus_dist) {
  double theta = degrees_to_radians(vfov);
  double h = tan(theta/2);
  double view_height = 2.0 * h;
  double view_width = aspect_ratio * view_height;

  m_W = (look_from - look_at).e();
  m_U = cross(v_up, m_W).e();
  m_V = cross(m_W, m_U);

  m_Origin = look_from;
  m_Horizontal = focus_dist * view_width * m_U;
  m_Vertical = focus_dist * view_height * m_V;
  m_LowerLeftCorner = m_Origin - m_Horizontal/2 - m_Vertical/2 - focus_dist*m_W;

  m_LensRadius = aperture / 2;
}

Ray Camera::get_ray(double u, double v) const {
  if (m_LensRadius == 0.0)
    return Ray(
      m_Origin,
      m_LowerLeftCorner + u*m_Horizontal + v*m_Vertical - m_Origin);

  Vec3 rd = m_LensRadius * Vec3::random_in_unit_disk();
  Vec3 offset = m_U * rd.x + m_V * rd.y;
  return Ray(
    m_Origin + offset,
    m_LowerLeftCorner + u*m_Horizontal + v*m_Vertical - m_Origin - offset);
}

}  // namespace WaywardRT
