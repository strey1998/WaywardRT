// WaywardRT/WaywardRT/include/WaywardRT/Image.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_IMAGE_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_IMAGE_H_

#include <cstdint>

#include "WaywardRT_export.h"
#include "WaywardRT/util.h"
namespace WaywardRT { struct Color; }

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// Represents an image
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT Image {
 public:
  //////////////////////////////////////////////////////////////////////////////
  /// Sets a pixel of the image to a particular color
  /// @param[in] x The horizontal coordinate of the pixel to change
  /// @param[in] y The vertical coordinate of the pixel to change
  ///   (top-to-bottom)
  /// @param[in] c The new color for the pixel
  //////////////////////////////////////////////////////////////////////////////
  virtual void setPixel(uint16_t x, uint16_t y, Color c) = 0;

  //////////////////////////////////////////////////////////////////////////////
  /// Writes the image out to a file. Will overwrite an existing file
  /// @param[in] fileName The file name of the output file
  /// @return True if successful, false if an error occurred
  //////////////////////////////////////////////////////////////////////////////
  virtual bool write(const char* fileName) const = 0;
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_IMAGE_H_
