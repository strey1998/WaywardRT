// WaywardRT/WaywardRT/include/WaywardRT/BMPImage.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_BMPIMAGE_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_BMPIMAGE_H_

#include <cstdint>

#include "WaywardRT_export.h"
#include "WaywardRT/Image.h"
namespace WaywardRT { struct Color; }

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// Represents a BMP image
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT BMPImage : public Image {
 private:
  uint16_t m_Width;
  uint16_t m_Height;
  uint8_t* m_Data;
  bool m_InvertY;

 public:
  BMPImage() = delete;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initializer
  /// Initializes a blank image
  /// @param[in] width   The width of the image
  /// @param[in] height  The height of the image
  /// @param[in] invertY Whether to invert the y-coordinate so indexeing starts
  ///   from bottom of image
  //////////////////////////////////////////////////////////////////////////////
  BMPImage(uint16_t width, uint16_t height, bool invertY = false);

  BMPImage(const BMPImage& other);
  BMPImage(BMPImage&& other) noexcept;
  BMPImage& operator=(BMPImage other) noexcept;
  void swap(BMPImage& other) noexcept;
  friend void swap(BMPImage& a, BMPImage& b) noexcept;
  ~BMPImage();

  //////////////////////////////////////////////////////////////////////////////
  /// Sets a pixel of the image to a particular color
  /// @param[in] x The horizontal coordinate of the pixel to change
  /// @param[in] y The vertical coordinate of the pixel to change
  ///   (top-to-bottom)
  /// @param[in] c The new color for the pixel
  //////////////////////////////////////////////////////////////////////////////
  void setPixel(uint16_t x, uint16_t y, Color c) noexcept override;

  //////////////////////////////////////////////////////////////////////////////
  /// Sets a pixel of the image to a particular color
  /// @param[in] x The horizontal coordinate of the pixel to change
  /// @param[in] y The vertical coordinate of the pixel to change
  ///   (top-to-bottom)
  /// @param[in] r The new red channel for the pixel (0-255)
  /// @param[in] g The new green channel for the pixel (0-255)
  /// @param[in] b The new blue channel for the pixel (0-255)
  //////////////////////////////////////////////////////////////////////////////
  void setPixel(
    uint16_t x, uint16_t y,
    uint8_t r, uint8_t g, uint8_t b) noexcept;

  //////////////////////////////////////////////////////////////////////////////
  /// Writes the image out to a file. Will overwrite an existing file
  /// @param[in] fileName The file name of the output file
  /// @return True if successful, false if an error occurred
  //////////////////////////////////////////////////////////////////////////////
  bool write(const char* fileName) const override;
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_BMPIMAGE_H_
