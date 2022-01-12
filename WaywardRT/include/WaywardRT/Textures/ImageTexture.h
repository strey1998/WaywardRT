// WaywardRT/WaywardRT/include/WaywardRT/Textures/ImageTexture.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_TEXTURES_IMAGETEXTURE_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_TEXTURES_IMAGETEXTURE_H_

#include "WaywardRT_export.h"

#include <cstdint>

#include "WaywardRT/Color.h"
#include "WaywardRT/Textures/Texture.h"
#include "WaywardRT/util.h"
namespace WaywardRT { class Vec3; }

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// Abstract class for textures
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT ImageTexture : public Texture {
 private:
  uint8_t* m_Data;
  int m_Width, m_Height;
  int m_BytesPerScanline;

 public:
  static const uint8_t bytes_per_pixel = 3;

  ImageTexture();
  explicit ImageTexture(const char* filename);
  ~ImageTexture();

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDocs}
  //////////////////////////////////////////////////////////////////////////////
  Color value(real u, real v, const Vec3& p) const override;
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_TEXTURES_IMAGETEXTURE_H_
