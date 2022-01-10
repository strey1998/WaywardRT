// WaywardRT/WaywardRT/include/WaywardRT/Objects/Rectangle.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_RECTANGLE_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_RECTANGLE_H_

#include "WaywardRT_export.h"

#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/Ray.h"
#include "WaywardRT/util.h"

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// Represents a rectangle
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT Rectangle : public Hittable {
 private:
  Vec3 m_O;
  Vec3 m_U;
  Vec3 m_V;
  real m_UL;
  real m_VL;
  Vec3 m_N;
  std::shared_ptr<Material> m_Material;

 public:
  Rectangle() = delete;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initialize a rectangle
  /// @param[in] origin    The origin corner of the rectangle
  /// @param[in] side1     One side of the reactangle
  /// @param[in] side2     The other side of the rectangle (NOTE: MUST be
  ///   orthogonal to side1)
  /// @param[in] material  The material of the rectangle
  //////////////////////////////////////////////////////////////////////////////
  Rectangle(Vec3 origin,
    Vec3 side1,
    Vec3 side2,
    std::shared_ptr<Material> material);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Accessor for material
  /// @returns The material of the rectangle
  //////////////////////////////////////////////////////////////////////////////
  std::shared_ptr<Material> material() const noexcept;

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDoc}
  //////////////////////////////////////////////////////////////////////////////
  bool hit(
    const Ray& r,
    real t_min,
    real t_max,
    HitRecord& rec) const override;

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDoc}
  //////////////////////////////////////////////////////////////////////////////
  bool bounding_box(real t_min, real t_max, BoundingBox& box) const override;
};

class WAYWARDRT_EXPORT RectangleXY : public Hittable {
 private:
  real m_X0, m_X1, m_Y0, m_Y1, m_Z;
  std::shared_ptr<Material> m_Material;

 public:
  RectangleXY() = delete;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initialize a rectangle in a constant x plane
  /// @param[in] x0   The minimum x value of the rectangle
  /// @param[in] x1   The maximum x value of the rectangle
  /// @param[in] y0   The minimum y value of the rectangle
  /// @param[in] y1   The maximum y value of the rectangle
  /// @param[in] z    The z value of the rectangle
  /// @param[in] material  The material of the rectangle
  //////////////////////////////////////////////////////////////////////////////
  RectangleXY(
    real x0, real x1,
    real y0, real y1,
    real z,
    std::shared_ptr<Material> material);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Accessor for material
  /// @returns The material of the rectangle
  //////////////////////////////////////////////////////////////////////////////
  std::shared_ptr<Material> material() const noexcept;

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDoc}
  //////////////////////////////////////////////////////////////////////////////
  bool hit(
    const Ray& r,
    real t_min,
    real t_max,
    HitRecord& rec) const override;

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDoc}
  //////////////////////////////////////////////////////////////////////////////
  bool bounding_box(real t_min, real t_max, BoundingBox& box) const override;
};

class WAYWARDRT_EXPORT RectangleXZ : public Hittable {
 private:
  real m_X0, m_X1, m_Y, m_Z0, m_Z1;
  std::shared_ptr<Material> m_Material;

 public:
  RectangleXZ() = delete;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initialize a rectangle in a constant x plane
  /// @param[in] x0   The minimum x value of the rectangle
  /// @param[in] x1   The maximum x value of the rectangle
  /// @param[in] y    The y value of the rectangle
  /// @param[in] z0   The minimum z value of the rectangle
  /// @param[in] z1   The maximum z value of the rectangle
  /// @param[in] material  The material of the rectangle
  //////////////////////////////////////////////////////////////////////////////
  RectangleXZ(
    real x0, real x1,
    real y,
    real z0, real z1,
    std::shared_ptr<Material> material);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Accessor for material
  /// @returns The material of the rectangle
  //////////////////////////////////////////////////////////////////////////////
  std::shared_ptr<Material> material() const noexcept;

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDoc}
  //////////////////////////////////////////////////////////////////////////////
  bool hit(
    const Ray& r,
    real t_min,
    real t_max,
    HitRecord& rec) const override;

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDoc}
  //////////////////////////////////////////////////////////////////////////////
  bool bounding_box(real t_min, real t_max, BoundingBox& box) const override;
};

class WAYWARDRT_EXPORT RectangleYZ : public Hittable {
 private:
  real m_X, m_Y0, m_Y1, m_Z0, m_Z1;
  std::shared_ptr<Material> m_Material;

 public:
  RectangleYZ() = delete;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initialize a rectangle in a constant x plane
  /// @param[in] x    The x value of the rectangle
  /// @param[in] y0   The minimum y value of the rectangle
  /// @param[in] y1   The maximum y value of the rectangle
  /// @param[in] z0   The minimum z value of the rectangle
  /// @param[in] z1   The maximum z value of the rectangle
  /// @param[in] material  The material of the rectangle
  //////////////////////////////////////////////////////////////////////////////
  RectangleYZ(
    real x,
    real y0, real y1,
    real z0, real z1,
    std::shared_ptr<Material> material);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Accessor for material
  /// @returns The material of the rectangle
  //////////////////////////////////////////////////////////////////////////////
  std::shared_ptr<Material> material() const noexcept;

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDoc}
  //////////////////////////////////////////////////////////////////////////////
  bool hit(
    const Ray& r,
    real t_min,
    real t_max,
    HitRecord& rec) const override;

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDoc}
  //////////////////////////////////////////////////////////////////////////////
  bool bounding_box(real t_min, real t_max, BoundingBox& box) const override;
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_RECTANGLE_H_
