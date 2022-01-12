// WaywardRT/WaywardRT/src/Rotate.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Objects/Rotate.h"

#include <cmath>

#include "WaywardRT/BoundingBox.h"
#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/Quaternion.h"
#include "WaywardRT/Ray.h"
#include "WaywardRT/util.h"
#include "WaywardRT/Vec3.h"

namespace WaywardRT {

Rotate::Rotate(std::shared_ptr<Hittable> object, const Vec3& axis, real angle)
  : m_Obj(object),
    m_Rotation(Quaternion(cos(angle/2), -sin(angle/2) * axis)) { }
// TODO(TS): WHY are rotations going the wrong way

Rotate::Rotate(std::shared_ptr<Hittable> object, const Quaternion& rotation)
  : m_Obj(object), m_Rotation(rotation) { }

bool Rotate::hit(
    const Ray& r,
    real t_min,
    real t_max,
    HitRecord& rec) const {

  Ray rotated(m_Rotation.apply_rotation(r.origin()),
              m_Rotation.apply_rotation(r.direction()),
              r.time());

  if (!m_Obj->hit(rotated, t_min, t_max, rec)) return false;

  rec.point = m_Rotation.apply_inverse_rotation(rec.point);
  rec.normal = m_Rotation.apply_inverse_rotation(rec.normal);

  return true;
}

// TODO(TS): This is probably not ideal
bool Rotate::bounding_box(real t0, real t1, BoundingBox& box) const {
  if (!m_Obj->bounding_box(t0, t1, box)) return false;

  Vec3 min(infinity, infinity, infinity);
  Vec3 max(-infinity, -infinity, -infinity);

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      for (int k = 0; k < 2; ++k) {
        Vec3 vertex(i*box.p0.x + (1-i)*box.p1.x,
                    j*box.p0.y + (1-j)*box.p1.y,
                    k*box.p0.z + (1-k)*box.p1.z);

        // TODO(TS): WHY INVERSE????
        Vec3 rotated = m_Rotation.apply_inverse_rotation(vertex);

        for (uint8_t n = 0; n < 3; ++n) {
          min[n] = fmin(min[n], rotated[n]);
          max[n] = fmax(max[n], rotated[n]);
        }
      }
    }
  }

  box = BoundingBox(min, max);

  return true;
}

}  // namespace WaywardRT
