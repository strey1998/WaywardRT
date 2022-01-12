// WaywardRT/Samples/src/Sample.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include <cmath>
#include <optional>
#include <utility>

#include "WaywardRT/BMPImage.h"
#include "WaywardRT/Camera.h"
#include "WaywardRT/log.h"
#include "WaywardRT/Objects/HittableList.h"
#include "WaywardRT/Renderers/RendererBasic.h"
#include "WaywardRT/Scene.h"
#include "WaywardRT/Timer.h"
#include "WaywardRT/Vec3.h"

int main(int, const char**) {
  // SETTINGS
  constexpr int IMAGE_WIDTH = 360;
  constexpr int IMAGE_HEIGHT = 360;
  constexpr int SAMPLES = 10;
  constexpr int DEPTH = 50;

  // LOG
  WLOG_SET_LEVEL(WLOG_LEVEL_TRACE);

  // IMAGE
  WaywardRT::BMPImage image(IMAGE_WIDTH, IMAGE_HEIGHT, true);

  // SCENE
  auto scene = WaywardRT::Scene::FINAL_SCENE_2(
    static_cast<float>(IMAGE_WIDTH) / IMAGE_HEIGHT);

  // RENDER
  WaywardRT::RendererBasic renderer(
    IMAGE_WIDTH, IMAGE_HEIGHT,
    SAMPLES, DEPTH,
    scene.background, scene.world, scene.camera);

  WLOG_INFO("Starting render");
  WaywardRT::Timer timer;
  renderer.render(12);
  WLOG_INFO("Render complete in {:.1f}s", timer.elapsed());

  renderer.write_image_data(image, 2.0);
  if (!image.write("out.bmp")) {
    WLOG_ERROR("An error occurred");
    return -1;
  }

  return 0;
}
