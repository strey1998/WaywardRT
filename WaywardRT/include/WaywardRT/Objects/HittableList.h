// WaywardRT/WaywardRT/include/WaywardRT/Objects/HittableList.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_HITTABLELIST_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_HITTABLELIST_H_

#include "WaywardRT_export.h"

#include <memory>
#include <vector>

#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/util.h"
namespace WaywardRT { class BoundingBox; }
namespace WaywardRT { class Ray; }

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// Represents a list of hittable objects
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT HittableList : public Hittable {
 private:
  std::vector<std::shared_ptr<Hittable>> m_Objects;

 public:
  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initialize an empty list of hittable objects
  //////////////////////////////////////////////////////////////////////////////
  HittableList();

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Initialize a singleton list of hittable objects
  /// @param[in] object The single initial object
  //////////////////////////////////////////////////////////////////////////////
  explicit HittableList(std::shared_ptr<Hittable> object);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Accessor for the objects in this list
  /// @return A const reference to this HittableList's std::vector of objects
  //////////////////////////////////////////////////////////////////////////////
  const std::vector<std::shared_ptr<Hittable>>& objects() const noexcept;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Clear the list
  //////////////////////////////////////////////////////////////////////////////
  void clear();

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Add an object to the list
  /// @param[in] object The new object
  //////////////////////////////////////////////////////////////////////////////
  void add(std::shared_ptr<Hittable> object);

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

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_OBJECTS_HITTABLELIST_H_
