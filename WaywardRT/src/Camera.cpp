// WaywardRT/WaywardRT/src/Camera.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Camera.h"

#include <cmath>

#include "WaywardRT/log.h"
#include "WaywardRT/util.h"

namespace WaywardRT {

Camera::Camera()
  : Camera(Vec3(0, 0, 0), Vec3(0, 0, 1), Vec3(0, 1, 0), 20, 16.0/9.0, 0.0) { }

Camera::Camera(
  Vec3 look_from,
  Vec3 look_at,
  Vec3 v_up,
  real vfov,
  real aspect_ratio,
  real aperture)
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
    real vfov,
    real aspect_ratio,
    real aperture,
    real focus_dist) : m_T0(0), m_T1(0) {

  WLOG_TRACE("Initializing camera");
  WLOG_TRACE("Camera look_from={}",         look_from.to_string());
  WLOG_TRACE("Camera look_at={}",           look_at.to_string());
  WLOG_TRACE("Camera v_up={}",              v_up.to_string());
  WLOG_TRACE("Camera vfov={:.1f}",          vfov);
  WLOG_TRACE("Camera aspect_ratio={:.1f}",  aspect_ratio);
  WLOG_TRACE("Camera aperture={:.1f}",      aperture);
  WLOG_TRACE("Camera focus_dist={:.1f}",    focus_dist);

  real theta = degrees_to_radians(vfov);
  real h = tan(theta/2);
  real view_height = 2.0 * h;
  real view_width = aspect_ratio * view_height;

  WLOG_TRACE("Camera view_height={:.1f}",  view_height);
  WLOG_TRACE("Camera view_width={:.1f}",   view_width);

  m_W = (look_from - look_at).e();
  m_U = cross(v_up, m_W).e();
  m_V = cross(m_W, m_U);

  WLOG_TRACE("Camera m_W={}", m_W.to_string());
  WLOG_TRACE("Camera m_U={}", m_U.to_string());
  WLOG_TRACE("Camera m_V={}", m_V.to_string());

  m_Origin = look_from;
  m_Horizontal = focus_dist * view_width * m_U;
  m_Vertical = focus_dist * view_height * m_V;
  m_LowerLeftCorner = m_Origin - m_Horizontal/2 - m_Vertical/2 - focus_dist*m_W;

  WLOG_TRACE("Camera m_Origin={}",           m_Origin.to_string());
  WLOG_TRACE("Camera m_Horizontal={}",       m_Horizontal.to_string());
  WLOG_TRACE("Camera m_Vertical={}",         m_Vertical.to_string());
  WLOG_TRACE("Camera m_LowerLeftCorner={}",  m_LowerLeftCorner.to_string());

  m_LensRadius = aperture / 2;

  WLOG_TRACE("Camera m_LensRadius={:.1f}", m_LensRadius);
}

Camera& Camera::set_ray_timing(real t) noexcept {
  return set_ray_timing(t, t);
}

Camera& Camera::set_ray_timing(real t0, real t1) noexcept {
  m_T0 = t0;
  m_T1 = t1;
  return *this;
}

Ray Camera::get_ray(real u, real v) const {
  if (m_LensRadius == 0.0)
    return Ray(
      m_Origin,
      m_LowerLeftCorner + u*m_Horizontal + v*m_Vertical - m_Origin);

  Vec3 rd = m_LensRadius * Vec3::random_in_unit_disk();
  Vec3 offset = m_U * rd.x + m_V * rd.y;
  return Ray(
    m_Origin + offset,
    m_LowerLeftCorner + u*m_Horizontal + v*m_Vertical - m_Origin - offset,
    random_real(m_T0, m_T1));
}

}  // namespace WaywardRT
