// WaywardRT/WaywardRT/include/WaywardRT/Scene.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_SCENE_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_SCENE_H_


#include <utility>

#include "WaywardRT_export.h"

#include "WaywardRT/Camera.h"
#include "WaywardRT/Color.h"
#include "WaywardRT/Objects/HittableList.h"

namespace WaywardRT {

struct WAYWARDRT_EXPORT Scene {
  HittableList world;
  Camera camera;
  Color background;

  static Scene RANDOM_SPHERES(float aspect_ratio);
  static Scene MIRRORED_SPHERES(float aspect_ratio);
  static Scene LIT_SPHERES(float aspect_ratio);
  static Scene TWO_SPHERES(float aspect_ratio);
  static Scene TWO_PERLIN_SPHERES(float aspect_ratio);
  static Scene EARTH(float aspect_ratio);
  static Scene SIMPLE_LIGHT(float aspect_ratio);
  static Scene CORNELL_BOX(float aspect_ratio);
  static Scene CORNELL_BOX_MEDIA(float aspect_ratio);
  static Scene ROTATION_TEST(float aspect_ratio);
  static Scene FINAL_SCENE_2(float aspect_ratio);
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_SCENE_H_
