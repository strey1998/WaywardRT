// WaywardRT/WaywardRT/src/ConstantMedium.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Objects/ConstantMedium.h"

#include <cmath>

#include "WaywardRT/Color.h"
#include "WaywardRT/log.h"
#include "WaywardRT/Materials/Isotropic.h"
#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/Ray.h"
#include "WaywardRT/Vec3.h"
#include "WaywardRT/util.h"
namespace WaywardRT { class BoundingBox; }
namespace WaywardRT { class Material; }
namespace WaywardRT { class Texture; }

namespace WaywardRT {

  std::shared_ptr<Hittable> m_Boundary;
  std::shared_ptr<Material> m_PhaseFn;
  real m_NegInvDensity;

ConstantMedium::ConstantMedium(
  std::shared_ptr<Hittable> boundary,
  real density,
  Color c)
  : m_Boundary(boundary),
    m_PhaseFn(std::make_shared<Isotropic>(c)),
    m_NegInvDensity(-1/density) { }

ConstantMedium::ConstantMedium(
  std::shared_ptr<Hittable> boundary,
  real density,
  std::shared_ptr<Texture> t)
  : m_Boundary(boundary),
    m_PhaseFn(std::make_shared<Isotropic>(t)),
    m_NegInvDensity(-1/density) { }

bool ConstantMedium::hit(
    const Ray& r,
    real t_min,
    real t_max,
    HitRecord& rec) const {

  HitRecord rec1, rec2;

    #if WAYWARDRT_ENABLE_LOGGING
  bool do_log = random_real() < 0.00001;
    #else
  bool do_log = false;
    #endif

  if (!m_Boundary->hit(r, -infinity, infinity, rec1)) return false;
  if (!m_Boundary->hit(r, rec1.t+0.0001, infinity, rec2)) return false;

  if (do_log) {
    WLOG_TRACE("Medium scatter: t_min={:.1f}, t_max={:.1f}", rec1.t, rec2.t);
  }

  if (rec1.t < t_min) rec1.t = t_min;
  if (rec2.t > t_max) rec2.t = t_max;

  if (rec1.t >= rec2.t) return false;

  if (rec1.t < 0) rec1.t = 0;

  const real ray_length = r.direction().len();
  const real dist_inside = (rec2.t - rec1.t) * ray_length;
  const real hit_dist = m_NegInvDensity * log(random_real());

  if (hit_dist > dist_inside) return false;

  rec.t = rec1.t + hit_dist / ray_length;
  rec.point = r.at(rec.t);

  if (do_log) {
    WLOG_TRACE("Medium scatter: d={:.1f}, t={:.1f}, p={}",
      hit_dist, rec.t, rec.point.to_string());
  }

  rec.normal = Vec3(1, 0, 0);  // Arbitrary
  rec.material = m_PhaseFn;

  return true;
}

bool ConstantMedium::bounding_box(real t0, real t1, BoundingBox& box) const {
  return m_Boundary->bounding_box(t0, t1, box);
}

}  // namespace WaywardRT
