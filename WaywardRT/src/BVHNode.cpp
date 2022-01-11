// WaywardRT/WaywardRT/src/BVHNode.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/BVHNode.h"

#include <algorithm>

#include "WaywardRT/log.h"
#include "WaywardRT/util.h"

namespace WaywardRT {

static inline bool box_compare(
  const std::shared_ptr<Hittable> a,
  const std::shared_ptr<Hittable> b,
  int axis);

static bool box_x_compare(
  const std::shared_ptr<Hittable> a,
  const std::shared_ptr<Hittable> b);

static bool box_y_compare(
  const std::shared_ptr<Hittable> a,
  const std::shared_ptr<Hittable> b);

static bool box_z_compare(
  const std::shared_ptr<Hittable> a,
  const std::shared_ptr<Hittable> b);

BVHNode::BVHNode()
  : BVHNode(std::vector<std::shared_ptr<Hittable>>(), 0, 0, 0.0, 0.0) { }

BVHNode::BVHNode(const HittableList& list, real t0, real t1)
  : BVHNode(list.objects(), 0, list.objects().size(), t0, t1) { }

BVHNode::BVHNode(
    const std::vector<std::shared_ptr<Hittable>>& src_objects,
    size_t start, size_t end, real t0, real t1) {
  auto objects = src_objects;

  uint8_t axis = random_int(0, 2);
  auto comparator = (axis == 0) ? box_x_compare
                  : (axis == 1) ? box_y_compare
                                : box_z_compare;

  size_t n_objects = end - start;

  if (n_objects <= 0) {
    return;
  } else if (n_objects == 1) {
    m_C1 = m_C2 = objects[start];
  } else if (n_objects == 2) {
    if (comparator(objects[start], objects[start+1])) {
      m_C1 = objects[start];
      m_C2 = objects[start+1];
    } else {
      m_C1 = objects[start+1];
      m_C2 = objects[start];
    }
  } else {
    std::sort(objects.begin() + start, objects.begin() + end, comparator);

    auto mid = start + n_objects/2;
    m_C1 = std::make_shared<BVHNode>(objects, start, mid, t0, t1);
    m_C2 = std::make_shared<BVHNode>(objects, mid, end, t0, t1);
  }

  BoundingBox b1, b2;

  if (!m_C1->bounding_box(t0, t1, b1) || !m_C2->bounding_box(t0, t1, b2)) {
    WLOG_ERROR("No bounding box in BVHNode construction");
  }

  m_Box = bb_union(b1, b2);
}

bool BVHNode::hit(
    const Ray& r,
    real t_min,
    real t_max,
    HitRecord& rec) const {
  if (!m_Box.hit(r, t_min, t_max)) return false;

  bool hit1 = m_C1->hit(r, t_min, t_max, rec);
  bool hit2 = m_C2->hit(r, t_min, hit1 ? rec.t : t_max, rec);

  return hit1 || hit2;
}

bool BVHNode::bounding_box(real, real, BoundingBox& box) const {
  box = m_Box;
  return true;
}

static inline bool box_compare(
    const std::shared_ptr<Hittable> a,
    const std::shared_ptr<Hittable> b,
    int axis) {
  BoundingBox box_a, box_b;

  if (!a->bounding_box(0, 0, box_a) || !b->bounding_box(0, 0, box_b)) {
    WLOG_ERROR("No bounding box in BVHNode construction");
  }

  return box_a.p0[axis] < box_b.p0[axis];
}

static bool box_x_compare(
    const std::shared_ptr<Hittable> a,
    const std::shared_ptr<Hittable> b) {
  return box_compare(a, b, 0);
}

static bool box_y_compare(
    const std::shared_ptr<Hittable> a,
    const std::shared_ptr<Hittable> b) {
  return box_compare(a, b, 1);
}

static bool box_z_compare(
    const std::shared_ptr<Hittable> a,
    const std::shared_ptr<Hittable> b) {
  return box_compare(a, b, 2);
}

}  // namespace WaywardRT
