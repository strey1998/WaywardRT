// WaywardRT/WaywardRT/src/BoundingBox.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/BoundingBox.h"

#include <cmath>

#include "WaywardRT/util.h"

namespace WaywardRT {

BoundingBox::BoundingBox() { }

BoundingBox::BoundingBox(const Vec3& p0, const Vec3& p1) : p0(p0), p1(p1) { }

#if 0
bool BoundingBox::hit(const Ray& r, real t_min, real t_max) const {
  for (int i = 0; i < 3; ++i) {
    real t0 = fmin(
      (p0[i] - r.origin()[i]) / r.direction()[i],
      (p1[i] - r.origin()[i]) / r.direction()[i]);
    real t1 = fmax(
      (p0[i] - r.origin()[i]) / r.direction()[i],
      (p1[i] - r.origin()[i]) / r.direction()[i]);

    t_min = fmax(t0, t_min);
    t_max = fmin(t1, t_max);

    if (t_max <= t_min) return false;
  }
  return true;
}
#else
bool BoundingBox::hit(const Ray& r, real t_min, real t_max) const {
  for (int i = 0; i < 3; ++i) {
    real inv_d = 1.0 / r.direction()[i];
    real t0 = (p0[i] - r.origin()[i]) * inv_d;
    real t1 = (p1[i] - r.origin()[i]) * inv_d;

    if (inv_d < 0.0) std::swap(t0, t1);

    t_min = t0 > t_min ? t0 : t_min;
    t_max = t1 < t_max ? t1 : t_max;

    if (t_max <= t_min) return false;
  }
  return true;
}
#endif

BoundingBox bb_union(const BoundingBox& b1, const BoundingBox& b2) {
  return BoundingBox(
    Vec3(
      fmin(b1.p0.x, b2.p0.x),
      fmin(b1.p0.y, b2.p0.y),
      fmin(b1.p0.z, b2.p0.z)),
    Vec3(
      fmax(b1.p1.x, b2.p1.x),
      fmax(b1.p1.y, b2.p1.y),
      fmax(b1.p1.z, b2.p1.z)));
}

}  // namespace WaywardRT
