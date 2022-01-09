// WaywardRT/WaywardRT/src/Textures/ImageTexture.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Textures/ImageTexture.h"

#include <cmath>

#include "stb/stb_image.h"

#include "WaywardRT/Color.h"
#include "WaywardRT/log.h"
#include "WaywardRT/Textures/Texture.h"
#include "WaywardRT/util.h"
#include "WaywardRT/Vec3.h"

namespace WaywardRT {

ImageTexture::ImageTexture()
  : m_Data(nullptr), m_Width(0), m_Height(0), m_BytesPerScanline(0) { }

ImageTexture::ImageTexture(const char* filename) {
  int components_per_pixel = bytes_per_pixel;

  m_Data = stbi_load(
    filename,
    &m_Width,
    &m_Height,
    &components_per_pixel,
    components_per_pixel);

  if (!m_Data) {
    m_Width = 0;
    m_Height = 0;
    WLOG_ERROR("Failed to load texture {}: {}",
      filename,
      stbi_failure_reason());
    return;
  }

  m_BytesPerScanline = bytes_per_pixel * m_Width;

  WLOG_TRACE("Loaded texture {}", filename);
}

ImageTexture::~ImageTexture() {
  delete m_Data;
}

Color ImageTexture::value(real u, real v, const Vec3& p) const {
  if (m_Data == nullptr) {
    real sines = sin(5*p.x)*sin(5*p.y)*sin(5*p.z);
    return sines < 0 ? Color::MAGENTA()
                     : Color::BLACK();
  }

  u = clamp(u, 0.0, 1.0);
  v = 1.0 - clamp(v, 0.0, 1.0);

  uint16_t i = static_cast<uint16_t>(u * m_Width);
  uint16_t j = static_cast<uint16_t>(v * m_Height);

  if (i >= m_Width)  i = m_Width - 1;
  if (j >= m_Height) j = m_Height - 1;

  const auto color_scale = 1.0 / 255.0;
  auto pixel = m_Data + j*m_BytesPerScanline + i*bytes_per_pixel;

  return Color(
    color_scale*pixel[0],
    color_scale*pixel[1],
    color_scale*pixel[2]);
}

}  // namespace WaywardRT
