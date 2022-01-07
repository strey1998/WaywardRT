// WaywardRT/WaywardRT/src/Objects/HittableList.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Objects/HittableList.h"

#include <memory>
#include <optional>
#include <vector>

#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/Ray.h"

namespace WaywardRT {

HittableList::HittableList() {
  m_Objects = std::vector<std::shared_ptr<Hittable>>();
}

HittableList::HittableList(std::shared_ptr<Hittable> object) : HittableList() {
  add(object);
}

void HittableList::clear() {
  m_Objects.clear();
}

void HittableList::add(std::shared_ptr<Hittable> object) {
  m_Objects.push_back(object);
}

bool HittableList::hit(
    const Ray& r,
    double t_min,
    double t_max,
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

}  // namespace WaywardRT
