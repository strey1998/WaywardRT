// WaywardRT/WaywardRT/include/WaywardRT/Renderer.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_RENDERER_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_RENDERER_H_

#include "WaywardRT_export.h"

#include <memory>

#include "WaywardRT/Camera.h"
#include "WaywardRT/Color.h"
#include "WaywardRT/Image.h"
#include "WaywardRT/Objects/HittableList.h"
#include "WaywardRT/util.h"

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// A renderer
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT Renderer {
 private:
  uint16_t m_Width, m_Height;
  uint16_t m_Samples, m_Depth;
  HittableList m_World;
  Camera m_Camera;
  Color* m_ImageData;

 public:
  Renderer() = delete;
  Renderer(const Renderer&) = delete;
  Renderer(Renderer&&) = delete;
  Renderer& operator=(const Renderer&) = delete;
  Renderer& operator=(Renderer&&) = delete;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initializer
  /// @param[in] width  The width of the image to render
  /// @param[in] height The height of the image to render
  /// @param[in] world  The HittableList of objects of which to generate an
  ///   image
  /// @param[in] camera The camera from which to render the image
  //////////////////////////////////////////////////////////////////////////////
  Renderer(
    uint16_t width,
    uint16_t height,
    uint16_t samples,
    uint16_t depth,
    HittableList world,
    Camera camera);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Renders the image
  /// @param[in] threads The number of threads to use (default = 1)
  //////////////////////////////////////////////////////////////////////////////
  void render(uint8_t  = 1) const;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Renders a part of the image
  /// @param[in] xMin The leftmost pixel column to render
  /// @param[in] xMax The rightmost pixel column to render
  /// @param[in] yMin The bottommost pixel row to render
  /// @param[in] yMax The topmost pixel row to render
  //////////////////////////////////////////////////////////////////////////////
  void render_subimage(
    uint16_t xMin, uint16_t xMax, uint16_t yMin, uint16_t yMax) const;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Renders a part of the image
  /// @param[in] xMin The leftmost pixel column to render
  /// @param[in] xMax The rightmost pixel column to render
  /// @param[in] yMin The bottommost pixel row to render
  /// @param[in] yMax The topmost pixel row to render
  /// @param[out] progress The percent progress to completion, updated regularly
  //////////////////////////////////////////////////////////////////////////////
  void render_subimage(
    uint16_t xMin, uint16_t xMax, uint16_t yMin, uint16_t yMax,
    std::atomic<uint32_t>& progress) const;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Writes the image data to an image object
  /// @param[in] image The image to which to write the data
  /// @param[in] gamma Gamma correction factor
  /// @returns True on success, false on failure
  //////////////////////////////////////////////////////////////////////////////
  void write_image_data(Image& image, real gamma = 1.0) const;

  ~Renderer();

  static Color ray_color(const Ray& r, const Hittable& world, int depth);
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_RENDERER_H_
