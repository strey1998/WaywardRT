// WaywardRT/WaywardRT/include/WaywardRT/BVHNode.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_BVHNODE_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_BVHNODE_H_

#include "WaywardRT_export.h"

#include <vector>

#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/Objects/HittableList.h"
#include "WaywardRT/Ray.h"
#include "WaywardRT/Vec3.h"

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// Represents a BVH node
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT BVHNode : public Hittable {
 private:
  std::shared_ptr<Hittable> m_C1;
  std::shared_ptr<Hittable> m_C2;
  BoundingBox m_Box;

 public:
  BVHNode();

  BVHNode(const HittableList& list, real t0, real t1);

  BVHNode(
    const std::vector<std::shared_ptr<Hittable>>& src_objects,
    size_t start, size_t end, real t0, real t1);

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

using BVHierarchy = BVHNode;

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_BVHNODE_H_
