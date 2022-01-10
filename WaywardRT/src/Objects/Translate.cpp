// WaywardRT/WaywardRT/src/Translate.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Objects/Translate.h"

#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/Ray.h"
#include "WaywardRT/util.h"

namespace WaywardRT {

Translate::Translate(
  std::shared_ptr<Hittable> object,
  const Vec3& displacement)
  : m_Obj(object), m_Displacement(displacement) { }

bool Translate::hit(
    const Ray& r,
    real t_min,
    real t_max,
    HitRecord& rec) const {
  Ray offset_r(r.origin() - m_Displacement, r.direction(), r.time());

  if (!m_Obj->hit(offset_r, t_min, t_max, rec)) return false;

  rec.point += m_Displacement;

  return true;
}

bool Translate::bounding_box(real t0, real t1, BoundingBox& box) const {
  if (!m_Obj->bounding_box(t0, t1, box)) return false;

  box = BoundingBox(box.p0 + m_Displacement, box.p1 + m_Displacement);

  return true;
}

}  // namespace WaywardRT
