// WaywardRT/WaywardRT/include/WaywardRT/Objects/Rotate.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_ROTATE_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_ROTATE_H_

#include "WaywardRT_export.h"

#include <memory>

#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/Quaternion.h"
#include "WaywardRT/util.h"
namespace WaywardRT { class BoundingBox; }
namespace WaywardRT { class Ray; }
namespace WaywardRT { class Vec3; }

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// Represents an object rotated in space
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT Rotate : public Hittable {
 private:
  std::shared_ptr<Hittable> m_Obj;
  Quaternion m_Rotation;

 public:
  Rotate() = delete;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initialize a rotated object
  /// @param[in] object The object which should be rotated
  /// @param[in] axis   The axis of rotation to apply to the rotated object
  ///   (NOTE: Expects a normalized vector)
  /// @param[in] angle  The angle of rotation in radians to apply to the rotated
  ///   object
  //////////////////////////////////////////////////////////////////////////////
  Rotate(std::shared_ptr<Hittable> object, const Vec3& axis, real angle);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initialize a rotated object
  /// @param[in] object       The object which should be rotates
  /// @param[in] displacement The rotation to apply to the rotates object
  //////////////////////////////////////////////////////////////////////////////
  Rotate(std::shared_ptr<Hittable> object, const Quaternion& rotation);

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
  bool bounding_box(real t0, real t1, BoundingBox& box) const override;
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_ROTATE_H_
