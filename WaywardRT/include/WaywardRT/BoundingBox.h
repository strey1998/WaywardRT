// WaywardRT/WaywardRT/include/WaywardRT/BoundingBox.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_BOUNDINGBOX_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_BOUNDINGBOX_H_

#include "WaywardRT_export.h"

#include "WaywardRT/Vec3.h"
#include "WaywardRT/util.h"
namespace WaywardRT { class Ray; }

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// Represents a bounding box
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT BoundingBox {
 public:
  Vec3 p0;
  Vec3 p1;

 public:
  BoundingBox();

  BoundingBox(const Vec3& p0, const Vec3& p1);

  bool hit(const Ray& r, real t_min, real t_max) const;

  friend BoundingBox bb_union(const BoundingBox& b1, const BoundingBox& b2);
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_BOUNDINGBOX_H_
