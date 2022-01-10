// WaywardRT/WaywardRT/include/WaywardRT/Objects/Translate.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_TRANSLATE_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_TRANSLATE_H_

#include "WaywardRT_export.h"

#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/Ray.h"
#include "WaywardRT/util.h"

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// Represents an object translated in space
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT Translate : public Hittable {
 private:
  std::shared_ptr<Hittable> m_Obj;
  Vec3 m_Displacement;

 public:
  Translate() = delete;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initialize a translated object
  /// @param[in] object       The object which should be translated
  /// @param[in] displacement The displacement to apply to the translated object
  //////////////////////////////////////////////////////////////////////////////
  Translate(std::shared_ptr<Hittable> object, const Vec3& displacement);

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

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_TRANSLATE_H_
