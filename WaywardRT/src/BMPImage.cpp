// WaywardRT/WaywardRT/src/BMPImage.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/BMPImage.h"

#include <algorithm>
#include <cstdlib>
#include <cstdint>
#include <utility>

#include "stb/stb_image_write.h"

#include "WaywardRT/Color.h"

namespace WaywardRT {

BMPImage::BMPImage(uint16_t width, uint16_t height, bool invertY)
    : m_Width(width), m_Height(height), m_InvertY(invertY) {
  m_Data = reinterpret_cast<uint8_t*>(malloc(3 * m_Width * m_Height));
}

BMPImage::BMPImage(const BMPImage& other)
    : m_Width(other.m_Width), m_Height(other.m_Height) {
  this->m_Data = reinterpret_cast<uint8_t*>(malloc(3 * m_Width * m_Height));
  std::copy(
    other.m_Data,
    other.m_Data + (3 * m_Width * m_Height),
    this->m_Data);
}

BMPImage::BMPImage(BMPImage&& other) noexcept
    : m_Width(other.m_Width), m_Height(other.m_Height) {
  this->m_Data = other.m_Data;
  other.m_Width = 0;
  other.m_Height = 0;
  other.m_Data = nullptr;
}

BMPImage& BMPImage::operator=(BMPImage other) noexcept {
  other.swap(*this);
  return *this;
}

BMPImage::~BMPImage() {
  free(m_Data);
}

void BMPImage::swap(BMPImage& other) noexcept {
  std::swap(m_Width, other.m_Width);
  std::swap(m_Height, other.m_Height);
  std::swap(m_Data, other.m_Data);
}

void swap(BMPImage& a, BMPImage& b) noexcept {
  a.swap(b);
}

void BMPImage::setPixel(uint16_t x, uint16_t y, Color c) noexcept {
  setPixel(x, y, 255.999*c.r, 255.999*c.g, 255.999*c.b);
}

void BMPImage::setPixel(
    uint16_t x, uint16_t y,
    uint8_t r, uint8_t g, uint8_t b)
    noexcept {
  uint16_t yy = m_InvertY ? m_Height - 1 - y : y;

  m_Data[3*(x+yy*m_Width)]   = r;
  m_Data[3*(x+yy*m_Width)+1] = g;
  m_Data[3*(x+yy*m_Width)+2] = b;
}

bool BMPImage::write(const char* fileName) const {
  return stbi_write_bmp(fileName, m_Width, m_Height, 3, m_Data);
}


}  // namespace WaywardRT
