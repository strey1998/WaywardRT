// WaywardRT/WaywardRT/include/WaywardRT/Renderers/Renderer3D.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_RENDERERS_RENDERER3D_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_RENDERERS_RENDERER3D_H_

#include "WaywardRT_export.h"

#include <cstdint>
#include <utility>

#include "WaywardRT/Renderers/Renderer.h"
#include "WaywardRT/Renderers/RendererBasic.h"
#include "WaywardRT/util.h"
namespace WaywardRT { class Camera; }
namespace WaywardRT { class HittableList; }
namespace WaywardRT { class Image; }
namespace WaywardRT { class Vec3; }
namespace WaywardRT { struct Color; }

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// A renderer
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT Renderer3D : public Renderer {
 private:
  uint16_t m_Width;
  uint16_t m_Height;
  RendererBasic m_LeftRenderer;
  RendererBasic m_RightRenderer;

 public:
  Renderer3D() = delete;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initializer
  /// @param[in] width   The width of the image to render (NOTE: This is
  ///   doubled!)
  /// @param[in] height  The height of the image to render
  /// @param[in] samples The imaging samples per pixel
  /// @param[in] depth   The maximum ray scattering depth
  /// @param[in] background The background color
  /// @param[in] world   The HittableList of objects of which to generate an
  ///   image
  /// @param[in] lcamera The camera from which to render the left image
  /// @param[in] rcamera The camera from which to render the right image
  //////////////////////////////////////////////////////////////////////////////
  Renderer3D(
    uint16_t width,
    uint16_t height,
    uint16_t samples,
    uint16_t depth,
    Color background,
    HittableList world,
    Camera lcamera,
    Camera rcamera);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initializer
  /// @param[in] width   The width of the image to render (NOTE: This is
  ///   doubled!)
  /// @param[in] height  The height of the image to render
  /// @param[in] samples The imaging samples per pixel
  /// @param[in] depth   The maximum ray scattering depth
  /// @param[in] background The background color
  /// @param[in] world   The HittableList of objects of which to generate an
  ///   image
  /// @param[in] lcamera The camera from which to render the left image
  /// @param[in] rcamera The camera from which to render the right image
  //////////////////////////////////////////////////////////////////////////////
  Renderer3D(
    uint16_t width,
    uint16_t height,
    uint16_t samples,
    uint16_t depth,
    Color background,
    HittableList world,
    Camera lcamera,
    Camera rcamera,
    real t0,
    real t1);

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDocs}
  //////////////////////////////////////////////////////////////////////////////
  void render(uint8_t thread_count = 1, bool use_BVH = true) const override;

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDocs}
  //////////////////////////////////////////////////////////////////////////////
  void write_image_data(Image& image, real gamma = 1.0) const override;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Creates a stereoscopic pair of cameras for 3D rendering
  /// @param[in] look_from    The center point between the two cameras
  /// @param[in] look_at      The point at which the cameras look
  /// @param[in] v_up         The upward direction for the cameras
  /// @param[in] vfov         The vertical field of view, in degrees
  /// @param[in] aspect_ratio The aspect ratio (horizontal/vertical)
  /// @param[in] aperture     The lens aperture size
  /// @param[in] focus_dist   The lens focus distance
  /// @param[in] pd           The distance between the cameras
  /// @return An std::pair containing the two cameras (left first, right second)
  //////////////////////////////////////////////////////////////////////////////
  static std::pair<Camera, Camera> make_stereoscopic_pair(
      Vec3 look_from,
      Vec3 look_at,
      Vec3 v_up,
      real vfov,
      real aspect_ratio,
      real aperture,
      real focus_dist,
      real pd);
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_RENDERERS_RENDERER3D_H_
