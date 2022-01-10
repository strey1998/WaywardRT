// WaywardRT/WaywardRT/src/Renderers/Renderer3D.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Renderers/Renderer3D.h"

#include <utility>

namespace WaywardRT {

Renderer3D::Renderer3D(
  uint16_t width,
  uint16_t height,
  uint16_t samples,
  uint16_t depth,
  Color background,
  HittableList world,
  Camera lcamera,
  Camera rcamera)
    : m_Width(width), m_Height(height),
      m_LeftRenderer(width, height, samples, depth, background, world, lcamera),
      m_RightRenderer(width, height, samples, depth, background, world, rcamera)
  { }

Renderer3D::Renderer3D(
  uint16_t width,
  uint16_t height,
  uint16_t samples,
  uint16_t depth,
  Color background,
  HittableList world,
  Camera lcamera,
  Camera rcamera,
  real t0,
  real t1)
    : m_Width(width), m_Height(height),
      m_LeftRenderer(width, height, samples, depth,
                     background, world, lcamera, t0, t1),
      m_RightRenderer(width, height, samples, depth,
                      background, world, rcamera, t0, t1) { }

void Renderer3D::render(uint8_t thread_count, bool use_BVH) const {
  m_LeftRenderer.render(thread_count, use_BVH);
  m_RightRenderer.render(thread_count, use_BVH);
}

void Renderer3D::write_image_data(Image& image, real gamma) const {
  const Color* left_data = m_LeftRenderer.image_data();
  const Color* right_data = m_RightRenderer.image_data();

  for (int j = 0; j < m_Height; ++j) {
    for (int i = 0; i < m_Width; ++i) {
      image.setPixel(i, j, left_data[i+m_Width*j].exp(1/gamma));
    }
  }

  for (int j = 0; j < m_Height; ++j) {
    for (int i = 0; i < m_Width; ++i) {
      image.setPixel(i+m_Width, j, right_data[i+m_Width*j].exp(1/gamma));
    }
  }
}

std::pair<Camera, Camera> Renderer3D::make_stereoscopic_pair(
    Vec3 look_from,
    Vec3 look_at,
    Vec3 v_up,
    real vfov,
    real aspect_ratio,
    real aperture,
    real focus_dist,
    real pd) {
  Vec3 right = cross(look_at - look_from, v_up).e();

  Camera lc(
    look_from - pd*right/2,
    look_at,
    v_up,
    vfov,
    aspect_ratio,
    aperture,
    focus_dist);

  Camera rc(
    look_from + pd*right/2,
    look_at,
    v_up,
    vfov,
    aspect_ratio,
    aperture,
    focus_dist);

  return std::make_pair(lc, rc);
}

}  // namespace WaywardRT
