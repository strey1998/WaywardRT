// WaywardRT/WaywardRT/include/WaywardRT/Renderers/Renderer.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_RENDERERS_RENDERER_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_RENDERERS_RENDERER_H_

#include "WaywardRT_export.h"

#include <memory>

#include "WaywardRT/BVHNode.h"
#include "WaywardRT/Camera.h"
#include "WaywardRT/Color.h"
#include "WaywardRT/Image.h"
#include "WaywardRT/Objects/HittableList.h"
#include "WaywardRT/util.h"

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// Abstract class for renderers
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT Renderer {
 public:
  //////////////////////////////////////////////////////////////////////////////
  /// @brief Renders the image
  /// @param[in] thread_count The number of threads to use (default = 1)
  //////////////////////////////////////////////////////////////////////////////
  virtual void render(uint8_t thread_count = 1, bool use_BVH = true) const = 0;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Writes the image data to an image object
  /// @param[in] image The image to which to write the data
  /// @param[in] gamma Gamma correction factor
  /// @returns True on success, false on failure
  //////////////////////////////////////////////////////////////////////////////
  virtual void write_image_data(Image& image, real gamma = 1.0) const = 0;
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_RENDERERS_RENDERER_H_
