// WaywardRT/WaywardRT/include/WaywardRT/Objects/Box.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_BOX_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_BOX_H_

#include "WaywardRT_export.h"

#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/Objects/HittableList.h"
#include "WaywardRT/Ray.h"
#include "WaywardRT/util.h"

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// Represents a box
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT Box : public Hittable {
 private:
  Vec3 m_P0;
  Vec3 m_P1;
  HittableList m_Sides;

 public:
  Box() = delete;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initialize a box
  /// @param[in] p0       One vertex of the box
  /// @param[in] p1       The vertex opposite to p1
  /// @param[in] material The material of the rectangle
  //////////////////////////////////////////////////////////////////////////////
  Box(const Vec3& p0, const Vec3& p1, std::shared_ptr<Material> material);

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

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_BOX_H_
