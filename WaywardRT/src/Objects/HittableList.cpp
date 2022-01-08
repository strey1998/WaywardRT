// WaywardRT/WaywardRT/src/Objects/HittableList.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Objects/HittableList.h"

#include <memory>
#include <vector>

#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/Ray.h"
#include "WaywardRT/util.h"

namespace WaywardRT {

HittableList::HittableList() {
  m_Objects = std::vector<std::shared_ptr<Hittable>>();
}

HittableList::HittableList(std::shared_ptr<Hittable> object) : HittableList() {
  add(object);
}

const std::vector<std::shared_ptr<Hittable>>& HittableList::objects()
    const noexcept { return m_Objects; }

void HittableList::clear() {
  m_Objects.clear();
}

void HittableList::add(std::shared_ptr<Hittable> object) {
  m_Objects.push_back(object);
}

bool HittableList::hit(
    const Ray& r,
    real t_min,
    real t_max,
    HitRecord& rec) const {
  auto nearest_hit = t_max;
  HitRecord temp;
  for (const auto& object : this->m_Objects) {
    if (object->hit(r, t_min, nearest_hit, temp)) {
      nearest_hit = temp.t;
      rec = temp;
    }
  }

  return nearest_hit < t_max;
}


bool HittableList::bounding_box(
    real t_min,
    real t_max,
    BoundingBox& box) const {
  if (m_Objects.empty()) return false;

  BoundingBox temp;
  bool first = true;

  for (const auto& obj : m_Objects) {
    if (!obj->bounding_box(t_min, t_max, temp)) return false;
    box = first ? temp : bb_union(box, temp);
    first = false;
  }

  return true;
}

}  // namespace WaywardRT
