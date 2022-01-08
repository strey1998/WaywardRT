// WaywardRT/WaywardRT/include/WaywardRT/scenes.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_SCENES_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_SCENES_H_

#include <utility>

#include "WaywardRT/Camera.h"
#include "WaywardRT/Objects/HittableList.h"

namespace WaywardRT {
namespace SCENES {

std::pair<HittableList, Camera> RANDOM_SPHERES(float aspect_ratio);
std::pair<HittableList, Camera> TWO_SPHERES(float aspect_ratio);

}  // namespace SCENES
}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_SCENES_H_
