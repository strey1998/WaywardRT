// WaywardRT/WaywardRT/include/WaywardRT/Renderers/RendererBasic.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_RENDERERS_RENDERERBASIC_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_RENDERERS_RENDERERBASIC_H_

#include "WaywardRT_export.h"

#include <memory>

#include "WaywardRT/BVHNode.h"
#include "WaywardRT/Camera.h"
#include "WaywardRT/Color.h"
#include "WaywardRT/Image.h"
#include "WaywardRT/Objects/HittableList.h"
#include "WaywardRT/Renderers/Renderer.h"
#include "WaywardRT/util.h"

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// A basic renderer
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT RendererBasic : public Renderer {
 private:
  uint16_t m_Width, m_Height;
  uint16_t m_Samples, m_Depth;
  Color m_Background;
  HittableList m_World;
  Camera m_Camera;
  Color* m_ImageData;
  BVHNode m_BVH;

 public:
  RendererBasic() = delete;
  RendererBasic(const RendererBasic&) = delete;
  RendererBasic(RendererBasic&&) = delete;
  RendererBasic& operator=(const RendererBasic&) = delete;
  RendererBasic& operator=(RendererBasic&&) = delete;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initializer
  /// @param[in] width      The width of the image to render
  /// @param[in] height     The height of the image to render
  /// @param[in] samples    The imaging samples per pixel
  /// @param[in] depth      The maximum ray scattering depth
  /// @param[in] background The background color
  /// @param[in] world      The HittableList of objects of which to generate an
  ///   image
  /// @param[in] camera     The camera from which to render the image
  //////////////////////////////////////////////////////////////////////////////
  RendererBasic(
    uint16_t width,
    uint16_t height,
    uint16_t samples,
    uint16_t depth,
    Color background,
    HittableList world,
    Camera camera);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initializer
  /// @param[in] width      The width of the image to render
  /// @param[in] height     The height of the image to render
  /// @param[in] samples    The imaging samples per pixel
  /// @param[in] depth      The maximum ray scattering depth
  /// @param[in] background The background color
  /// @param[in] world      The HittableList of objects of which to generate an
  ///   image
  /// @param[in] camera     The camera from which to render the image
  /// @param[in] t0         The minimum time for the BVH
  /// @param[in] t1         The maximum time for the BVH
  //////////////////////////////////////////////////////////////////////////////
  RendererBasic(
    uint16_t width,
    uint16_t height,
    uint16_t samples,
    uint16_t depth,
    Color background,
    HittableList world,
    Camera camera,
    real t0,
    real t1);

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDocs}
  //////////////////////////////////////////////////////////////////////////////
  void render(uint8_t thread_count = 1, bool use_BVH = true) const override;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Renders a part of the image
  /// @param[in] xMin The leftmost pixel column to render
  /// @param[in] xMax The rightmost pixel column to render
  /// @param[in] yMin The bottommost pixel row to render
  /// @param[in] yMax The topmost pixel row to render
  //////////////////////////////////////////////////////////////////////////////
  void render_subimage(
    uint16_t xMin, uint16_t xMax,
    uint16_t yMin, uint16_t yMax,
    bool use_BVH) const;

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
    std::atomic<uint32_t>& progress,
    bool use_BVH) const;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Gets a pointer to this renderer's image data
  /// @return A pointer to this RendererBasic's image data
  //////////////////////////////////////////////////////////////////////////////
  const Color* image_data() const noexcept;

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDocs}
  //////////////////////////////////////////////////////////////////////////////
  void write_image_data(Image& image, real gamma = 1.0) const override;

  ~RendererBasic();

  static Color ray_color(
    const Ray& r,
    const Color& background,
    const Hittable& world,
    int depth);
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_RENDERERS_RENDERERBASIC_H_
